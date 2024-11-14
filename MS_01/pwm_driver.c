#include "pwm_driver.h"
#include "hardware/clocks.h"

// Example code for PWM setup:
void pwm_init(uint gpio_pin, uint frequency)
{
    // Set up the GPIO pin for PWM
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

    // Set the PWM range (number of steps for PWM, e.g., 255 for 8-bit PWM)
    uint pwm_range = 255; // Can be adjusted based on your resolution needs
    pwm_set_wrap(slice_num, pwm_range);

    // Calculate the clock divider based on system clock and desired frequency
    pwm_set_clkdiv(slice_num, (float)clock_get_hz(clk_sys) / frequency / pwm_range);

    pwm_set_enabled(slice_num, true); // Enable PWM
}

// Function to change the duty cycle of the PWM
void pwm_set_duty_cycle(uint pin, uint32_t duty_cycle)
{
    uint slice_num = pwm_gpio_to_slice_num(pin);                         // Get the PWM slice number for the pin
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), duty_cycle); // Set the new duty cycle
}

// Function to stop PWM on a pin
void pwm_stop(uint pin)
{
    uint slice_num = pwm_gpio_to_slice_num(pin); // Get the PWM slice number for the pin
    pwm_set_enabled(slice_num, false);           // Disable PWM on the pin
}
