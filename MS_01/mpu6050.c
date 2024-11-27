#include "mpu6050.h"

// Write a single byte to a register on the MPU6050
void mpu6050_write_register(uint8_t reg, uint8_t value)
{
    uint8_t buffer[2] = {reg, value};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, buffer, 2, false);
}

// Read multiple bytes from registers on the MPU6050
void mpu6050_read_registers(uint8_t reg, uint8_t *data, size_t length)
{
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, data, length, false);
}

// Initialize the MPU6050
void mpu6050_init()
{
    // Initialize I2C
    i2c_init(I2C_PORT, 100 * 1000); // 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Wake up the MPU6050 by writing 0 to the power management register
    mpu6050_write_register(MPU6050_REG_PWR_MGMT_1, 0x00);
}

// Read raw accelerometer, gyroscope, and temperature data from the MPU6050
void mpu6050_read_raw(int16_t *gyro, int16_t *accel, int16_t *temp)
{
    uint8_t buffer[14];
    mpu6050_read_registers(MPU6050_REG_ACCEL_XOUT_H, buffer, 14);

    // Gyroscope values
    gyro[0] = (buffer[0] << 8) | buffer[1]; // X
    gyro[1] = (buffer[2] << 8) | buffer[3]; // Y
    gyro[2] = (buffer[4] << 8) | buffer[5]; // Z

    // Accelerometer values
    accel[0] = (buffer[8] << 8) | buffer[9];   // X
    accel[1] = (buffer[10] << 8) | buffer[11]; // Y
    accel[2] = (buffer[12] << 8) | buffer[13]; // Z

    // Temperature value
    *temp = (buffer[6] << 8) | buffer[7];
}

// Convert raw data to meaningful accelerometer (g) and gyroscope (°/s) values
void convert_raw_data(int16_t *raw_accel, int16_t *raw_gyro, float *accel, float *gyro)
{
    accel[0] = raw_accel[0] / 16384.0f;
    accel[1] = raw_accel[1] / 16384.0f;
    accel[2] = raw_accel[2] / 16384.0f;

    gyro[0] = raw_gyro[0] / 131.0f;
    gyro[1] = raw_gyro[1] / 131.0f;
    gyro[2] = raw_gyro[2] / 131.0f;
}
