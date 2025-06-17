#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Arduino.h>

typedef enum {
    SENSOR_TYPE_VOLTAGE,
    SENSOR_TYPE_CURRENT
} SensorType;

typedef enum {
    SIGNAL_DC,
    SIGNAL_AC
} SignalType;

typedef struct {
    int pin;
    float adcRes;
    float vref;
} CommonConfig;

typedef struct {
    float r1;
    float r2;
} VoltageConfig;

typedef struct {
    int model;
    float voffSet;
} CurrentConfig;

typedef struct {
    SensorType type;
    SignalType signal;
    CommonConfig common;
    union {
        VoltageConfig voltage;
        CurrentConfig current;
    } spec;
} Sensor;

typedef enum  
        {
         POWER_DC,
         POWER_AC 
        }PowerType;

float readSensor(Sensor sensor);
float CalcPower(float voltage, float current, PowerType type );

#ifdef __cplusplus
}
#endif
