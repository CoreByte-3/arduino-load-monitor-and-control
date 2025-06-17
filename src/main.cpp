#include <Arduino.h>
#include "v_i_sensor.h"

// load line control  
#define loadPin 2

const float overloadThreshold = 15.0; //watts 
//printing interval 
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 1000;

//add voltage and current sensor structures for multiple load lines
Sensor voltageSensor;   
Sensor currentSensor;

void setup() {
    Serial.begin(9600);

    voltageSensor.type = SENSOR_TYPE_VOLTAGE;
    voltageSensor.signal = SIGNAL_DC;  // Change to SIGNAL_AC for AC
    voltageSensor.common = {A0, 1023.0, 5.0};// pin, adc resolution, vref
    voltageSensor.spec.voltage = {29770.0, 7430.0};  // R1, R2 Voltage divider resistors

    currentSensor.type = SENSOR_TYPE_CURRENT;
    currentSensor.signal = SIGNAL_DC;  // Change to SIGNAL_AC for AC
    currentSensor.common = {A1, 1023.0, 5.0};// pin, adc_resolution, vref
    currentSensor.spec.current = {30, 2.5};  // Model: 5 | 20 | 30A, offset: 2.5V

    pinMode(loadPin, OUTPUT);  

}

void loop() {
    float voltage = readSensor(voltageSensor);
    float current = readSensor(currentSensor);
    float power = CalcPower(voltage, current, POWER_DC);  

    if (power > overloadThreshold) {
        digitalWrite(loadPin, LOW);
        Serial.println(" Overload ");
    }

    if (millis() - lastPrintTime >= printInterval) {
        lastPrintTime = millis();

        Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
        Serial.print("Current: "); Serial.print(current); Serial.println(" A");
        Serial.print("Power: "); Serial.print(power); Serial.println(" W");
        Serial.println("-----------------------");
    }
}



