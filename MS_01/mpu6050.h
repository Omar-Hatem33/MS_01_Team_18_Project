#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

// I2C Configuration
#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

// MPU6050 Registers
#define MPU6050_ADDR 0x68
#define MPU6050_REG_PWR_MGMT_1 0x6B
#define MPU6050_REG_ACCEL_XOUT_H 0x3B
#define MPU6050_REG_TEMP_OUT_H 0x41
#define MPU6050_REG_GYRO_XOUT_H 0x43

// Function Prototypes
void mpu6050_init();
void mpu6050_read_raw(int16_t *accel, int16_t *gyro, int16_t *temp);
void convert_raw_data(int16_t *raw_accel, int16_t *raw_gyro, float *accel, float *gyro);

#endif   // MPU6050_H