#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"
#include <string.h>

// I2C Configuration for MPU6050 (on i2c0)
#define MPU6050_I2C_PORT i2c0
#define MPU6050_SDA_PIN 4
#define MPU6050_SCL_PIN 5

// I2C Configuration for ESP32 (on i2c1)
#define ESP32_I2C_PORT i2c1
#define ESP32_SDA_PIN 6
#define ESP32_SCL_PIN 7
#define ESP32_I2C_ADDRESS 0x55

#define TILT_THRESHOLD 0.5

// Function to determine the tilt direction
void determine_tilt(float *accel, char *tilt_code)
{
    if (accel[1] > TILT_THRESHOLD)
    {
        strcpy(tilt_code, "00"); // Forward tilt
    }
    else if (accel[1] < -TILT_THRESHOLD)
    {
        strcpy(tilt_code, "10"); // Backward tilt
    }
    else if (accel[0] > TILT_THRESHOLD)
    {
        strcpy(tilt_code, "01"); // Right tilt
    }
    else if (accel[0] < -TILT_THRESHOLD)
    {
        strcpy(tilt_code, "11"); // Left tilt
    }
    else
    {
        strcpy(tilt_code, "  "); // No significant tilt
    }
}

int main()
{
    // Initialize stdio
    stdio_init_all();

    // Initialize I2C for MPU6050
    i2c_init(MPU6050_I2C_PORT, 400 * 1000); // 400kHz I2C
    gpio_set_function(MPU6050_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(MPU6050_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(MPU6050_SDA_PIN);
    gpio_pull_up(MPU6050_SCL_PIN);

    // Initialize MPU6050
    mpu6050_init();

    // Initialize I2C for ESP32 (master mode)
    i2c_init(ESP32_I2C_PORT, 100 * 1000); // 100kHz I2C
    gpio_set_function(ESP32_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(ESP32_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(ESP32_SDA_PIN);
    gpio_pull_up(ESP32_SCL_PIN);

    // Buffers for raw and converted data
    int16_t raw_accel[3], raw_gyro[3], raw_temp;
    float accel[3], gyro[3];
    char tilt_code[3] = "  ";

    // Print a startup message
    printf("Starting tilt detection system (Master mode)...\n");

    // Main loop
    while (true)
    {
        // Read raw data from MPU6050
        mpu6050_read_raw(raw_accel, raw_gyro, &raw_temp);

        // Convert raw data to meaningful values
        convert_raw_data(raw_accel, raw_gyro, accel, gyro);

        // Determine tilt direction
        determine_tilt(accel, tilt_code);

        // Print the determined tilt code
        printf("Determined Tilt Code: %s\n", tilt_code);

        // Send tilt code to ESP32
        int bytes_written = i2c_write_blocking(ESP32_I2C_PORT, ESP32_I2C_ADDRESS, (uint8_t *)tilt_code, 2, false);
        if (bytes_written == PICO_ERROR_GENERIC)
        {
            printf("Failed to send data to ESP32\n");
        }
        else
        {
            printf("Sent %d bytes to ESP32\n", bytes_written);
        }

        // Delay for stability
        sleep_ms(100);
    }

    return 0;
}
