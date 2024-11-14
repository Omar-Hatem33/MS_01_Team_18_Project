#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Function to initialize the PWM on a specific pin
void pwm_init_on_pin(uint pin, uint frequency, uint32_t duty_cycle);

// Function to change the duty cycle of the PWM
void pwm_set_duty_cycle(uint pin, uint32_t duty_cycle);

// Function to stop PWM on a pin
void pwm_stop(uint pin);

#endif // PWM_DRIVER_H
