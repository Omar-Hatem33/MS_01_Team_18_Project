#include "motor_driver.h"
#include "hardware/clocks.h"

// Function to initialize the motors and PWM
void motor_pwm_init()
{
    // Set Motor A control pins to output mode
    gpio_init(MOTOR_A_IN1);
    gpio_set_dir(MOTOR_A_IN1, GPIO_OUT);
    gpio_init(MOTOR_A_IN2);
    gpio_set_dir(MOTOR_A_IN2, GPIO_OUT);

    // Set Motor B control pins to output mode
    gpio_init(MOTOR_B_IN1);
    gpio_set_dir(MOTOR_B_IN1, GPIO_OUT);
    gpio_init(MOTOR_B_IN2);
    gpio_set_dir(MOTOR_B_IN2, GPIO_OUT);

    // Set Motor A PWM pin to PWM mode
    gpio_set_function(MOTOR_A_PWM, GPIO_FUNC_PWM);
    uint slice_a = pwm_gpio_to_slice_num(MOTOR_A_PWM);
    uint pwm_range = 255; // 8-bit resolution (0-255)
    pwm_set_wrap(slice_a, pwm_range);
    pwm_set_clkdiv(slice_a, (float)clock_get_hz(clk_sys) / 1000 / pwm_range); // Adjust for desired frequency
    pwm_set_enabled(slice_a, true);

    // Set Motor B PWM pin to PWM mode
    gpio_set_function(MOTOR_B_PWM, GPIO_FUNC_PWM);
    uint slice_b = pwm_gpio_to_slice_num(MOTOR_B_PWM);
    pwm_set_wrap(slice_b, pwm_range);
    pwm_set_clkdiv(slice_b, (float)clock_get_hz(clk_sys) / 1000 / pwm_range); // Adjust for desired frequency
    pwm_set_enabled(slice_b, true);
}

// Function to set the motor direction
void motor_set_direction(bool forward)
{
    if (forward)
    {
        // Forward Direction
        gpio_put(MOTOR_A_IN1, 1);
        gpio_put(MOTOR_A_IN2, 0);
        gpio_put(MOTOR_B_IN1, 1);
        gpio_put(MOTOR_B_IN2, 0);
    }
    else
    {
        // Reverse Direction
        gpio_put(MOTOR_A_IN1, 0);
        gpio_put(MOTOR_A_IN2, 1);
        gpio_put(MOTOR_B_IN1, 0);
        gpio_put(MOTOR_B_IN2, 1);
    }
}

bool motor_get_direction()
{
    return gpio_get(MOTOR_A_IN1);
}

// Function to set the motor speed (PWM duty cycle: 0-255)
void motor_set_speed(uint8_t speed)
{
    // Clamp speed to 0-255
    speed = (speed > 255) ? 255 : speed;

    uint slice_a = pwm_gpio_to_slice_num(MOTOR_A_PWM);
    uint slice_b = pwm_gpio_to_slice_num(MOTOR_B_PWM);

    pwm_set_chan_level(slice_a, pwm_gpio_to_channel(MOTOR_A_PWM), speed);
    pwm_set_chan_level(slice_b, pwm_gpio_to_channel(MOTOR_B_PWM), speed);
}

// Function to stop the motors
void motor_stop()
{
    gpio_put(MOTOR_A_IN1, 0);
    gpio_put(MOTOR_A_IN2, 0);
    gpio_put(MOTOR_B_IN1, 0);
    gpio_put(MOTOR_B_IN2, 0);

    motor_set_speed(0); // Set PWM to 0 (stop speed)
}

// Function to initialize PWM on a specific pin
void pwm_init_on_pin(uint pin, uint frequency, uint32_t duty_cycle)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);
    uint pwm_range = 255;

    pwm_set_wrap(slice, pwm_range);
    pwm_set_clkdiv(slice, (float)clock_get_hz(clk_sys) / frequency / pwm_range);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(pin), duty_cycle);
    pwm_set_enabled(slice, true);
}

// Function to change the duty cycle of the PWM
void pwm_set_duty_cycle(uint pin, uint32_t duty_cycle)
{
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(pin), duty_cycle);
}

// Function to stop PWM on a pin
void pwm_stop(uint pin)
{
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_set_enabled(slice, false);
}
