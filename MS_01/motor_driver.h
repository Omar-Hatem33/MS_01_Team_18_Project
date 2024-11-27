#ifndef MOTOR_PWM_DRIVER_H
#define MOTOR_PWM_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Motor Pin Configuration (you can change these pins as per your wiring)
#define MOTOR_A_IN1 25 // IN1 Pin for motor A
#define MOTOR_A_IN2 15 // IN2 Pin for motor A
#define MOTOR_A_PWM 16 // ENA Pin for PWM speed control of motor A

#define MOTOR_B_IN1 17 // IN1 Pin for motor A
#define MOTOR_B_IN2 18 // IN1 Pin for motor A
#define MOTOR_B_PWM 19 // ENA Pin for PWM speed control of motor A

// #define MOTOR_A_IN1 2 // IN1 Pin for motor A
// #define MOTOR_A_IN2 3 // IN2 Pin for motor A
// #define MOTOR_A_PWM 4 // ENA Pin for PWM speed control of motor A

// #define MOTOR_B_IN1 6 // IN1 Pin for motor A
// #define MOTOR_B_IN2 7 // IN1 Pin for motor A
// #define MOTOR_B_PWM 8 // ENA Pin for PWM speed control of motor A

// Function to initialize the motor and PWM
void motor_pwm_init();

// Function to set the motor direction
void motor_set_direction(bool forward);

// Function to set the motor speed using PWM (0-255)
void motor_set_speed(uint8_t speed);

// Function to stop the motor
void motor_stop();

// Function to initialize PWM on a specific pin
void pwm_init_on_pin(uint pin, uint frequency, uint32_t duty_cycle);

// Function to change the duty cycle of the PWM
void pwm_set_duty_cycle(uint pin, uint32_t duty_cycle);

// Function to stop PWM on a pin
void pwm_stop(uint pin);

#endif // MOTOR_PWM_DRIVER_H
