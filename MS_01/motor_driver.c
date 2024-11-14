#include "motor_driver.h"
#include "hardware/clocks.h"

// Function to initialize the motor and PWM
void motor_pwm_init()
{
    // Set motor control pins to output mode
    gpio_init(MOTOR_A_IN1);
    gpio_set_dir(MOTOR_A_IN1, GPIO_OUT);
    gpio_init(MOTOR_A_IN2);
    gpio_set_dir(MOTOR_A_IN2, GPIO_OUT);

    // Set motor PWM pin to PWM mode
    gpio_set_function(MOTOR_A_PWM, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(MOTOR_A_PWM);
    uint pwm_range = 255; // 8-bit resolution (0-255)
    pwm_set_wrap(slice_num, pwm_range);

    // Set the PWM frequency using the system clock
    pwm_set_clkdiv(slice_num, (float)clock_get_hz(clk_sys) / 1000 / pwm_range); // Adjust this for desired frequency
    pwm_set_enabled(slice_num, true);                                           // Enable PWM output
}

// Function to set the motor direction
void motor_set_direction(bool forward)
{
    if (forward)
    {
        gpio_put(MOTOR_A_IN1, 1);
        gpio_put(MOTOR_A_IN2, 0);
    }
    else
    {
        gpio_put(MOTOR_A_IN1, 0);
        gpio_put(MOTOR_A_IN2, 1);
    }
}

// Function to set the motor speed (PWM duty cycle: 0-255)
void motor_set_speed(uint8_t speed)
{
    // Clamp speed to be between 0 and 255
    speed = (speed > 255) ? 255 : speed;

    uint slice_num = pwm_gpio_to_slice_num(MOTOR_A_PWM);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(MOTOR_A_PWM), speed);
}

// Function to stop the motor
void motor_stop()
{
    gpio_put(MOTOR_A_IN1, 0);
    gpio_put(MOTOR_A_IN2, 0);
    motor_set_speed(0); // Set PWM to 0 (no speed)
}

// Function to initialize PWM on a specific pin
void pwm_init_on_pin(uint pin, uint frequency, uint32_t duty_cycle)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint pwm_range = 255; // Adjust this for your desired resolution

    pwm_set_wrap(slice_num, pwm_range);
    pwm_set_clkdiv(slice_num, (float)clock_get_hz(clk_sys) / frequency / pwm_range);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), duty_cycle);
    pwm_set_enabled(slice_num, true);
}

// Function to change the duty cycle of the PWM
void pwm_set_duty_cycle(uint pin, uint32_t duty_cycle)
{
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), duty_cycle);
}

// Function to stop PWM on a pin
void pwm_stop(uint pin)
{
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice_num, false); // Disable PWM on the pin
}
