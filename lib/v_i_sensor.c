#include "v_i_sensor.h"

const int SAMPLES = 100;

float getSensitivity(int model) {
    switch (model) {
        case 5: return 0.185;
        case 10: return 0.100;
        case 30: return 0.066;
        default: return 0;
    }
}

float readSensor(Sensor sensor) {
    float sum = 0;
    float squareSum = 0;

    for (int i = 0; i < SAMPLES; i++) {
        int adc = analogRead(sensor.common.pin);
        float vout = adc * (sensor.common.vref / sensor.common.adcRes);

        float value = 0;

        if (sensor.type == SENSOR_TYPE_VOLTAGE) {
            float r1 = sensor.spec.voltage.r1;
            float r2 = sensor.spec.voltage.r2;
            value = vout * ((r1 + r2) / r2);
        } 
        else if (sensor.type == SENSOR_TYPE_CURRENT) {
            float voffset = sensor.spec.current.voffSet;
            float sensitivity = getSensitivity(sensor.spec.current.model);
            if (sensitivity == 0) return 0;
            value = (vout - voffset) / sensitivity;
        }

        sum += value;
        squareSum += value * value;
        delay(1);
    }

    if (sensor.signal == SIGNAL_AC) {
        return sqrt(squareSum / SAMPLES);  // Return RMS
    } else {
        return sum / SAMPLES;              // Return average (DC)
    }
}


float CalcPower(float voltage, float current, PowerType type ) {
    if (type == POWER_AC) {
        return voltage * current;  // For AC, this is a simplified calculation
    } else {
        return voltage * current;  // For DC, this is also a simplified calculation
    }
}