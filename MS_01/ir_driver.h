#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include "pico/stdlib.h"

// Infrared Sensor Pin Configuration (change as per your wiring)
#define IR_SENSOR_PIN 26

// Function to initialize the infrared sensor
void ir_sensor_init(uint pin);

// Function to read the infrared sensor state
bool ir_sensor_read(uint pin);

#endif // INFRARED_SENSOR_H
