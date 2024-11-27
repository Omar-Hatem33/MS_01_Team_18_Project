#include "pico/stdlib.h"
#include "motor_driver.h"
#include "ir_driver.h"

// Define the motor pins for better visibility
#define MOTOR_PWM_PIN MOTOR_A_PWM
#define MOTOR_DIRECTION_PIN1 MOTOR_A_IN1
#define MOTOR_DIRECTION_PIN2 MOTOR_A_IN2

// Define the LED pin
#define LED_PIN 20  // GPIO pin for LED
#define BUZZ_PIN 21 // GPIO pin for Buzzer

int main()
{
    stdio_init_all();

    // Initialize the GPIOs and PWM for the motor
    motor_pwm_init();

    // Initialize the IR sensor
    ir_sensor_init(IR_SENSOR_PIN);

    // Initialize the LED and Buzzer
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUZZ_PIN);
    gpio_set_dir(BUZZ_PIN, GPIO_OUT);

    // Start time for the first loop
    absolute_time_t start_time = get_absolute_time();

    // Loop for 5 seconds
    while (absolute_time_diff_us(start_time, get_absolute_time()) < 5000000)
    {
        bool ir_state = ir_sensor_read(IR_SENSOR_PIN);

        motor_set_direction(true); // Motor moves forward
        motor_set_speed(128);      // Set speed to 50% (128/255)

        if (!ir_state)
        {
            motor_stop(); // Stop the motor if IR sensor is not triggered
        }
    }

    // Start time for the second loop
    start_time = get_absolute_time();

    // Reverse motor direction and blink LED with buzzer for 5 seconds
    while (absolute_time_diff_us(start_time, get_absolute_time()) < 5000000)
    {
        motor_set_direction(false); // Motor moves backward
        motor_set_speed(128);       // Set speed to 50% (128/255)

        gpio_put(LED_PIN, 1); // Turn LED on

        // Toggle Buzzer every 1 second
        if (absolute_time_diff_us(start_time, get_absolute_time()) % 2000000 < 1000000)
        {
            gpio_put(BUZZ_PIN, 1); // Turn Buzzer on
        }
        else
        {
            gpio_put(BUZZ_PIN, 0); // Turn Buzzer off
        }

        sleep_ms(100); // Small delay to prevent overloading the processor
    }

    motor_stop();          // Stop the motor after 1 second
    gpio_put(BUZZ_PIN, 0); //
    gpio_put(LED_PIN, 0);

    return 0; // End of program
}
