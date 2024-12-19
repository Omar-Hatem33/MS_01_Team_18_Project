#include "pico/stdlib.h"
#include "motor_driver.h"
#include "ir_driver.h"
#include <stdio.h>

#define LED_PIN1 12
#define LED_PIN2 13
#define BUZZ_PIN 21

#define pin1 27
#define pin2 28
#define pin3 29

#define MOTOR_PWM_PIN MOTOR_A_PWM
#define MOTOR_DIRECTION_PIN1 MOTOR_A_IN1
#define MOTOR_DIRECTION_PIN2 MOTOR_A_IN2

typedef enum
{
    TILT_NONE,
    TILT_FORWARD,
    TILT_BACKWARD,
    TILT_LEFT,
    TILT_RIGHT
} TiltDirection;

volatile TiltDirection current_tilt = TILT_NONE;
volatile bool turning = false;

void setInput()
{
    int var1 = gpio_get(pin1);
    int var2 = gpio_get(pin2);
    int var3 = gpio_get(pin3);
    if (var1 == 0 && var2 == 0 && var3 == 0)
    {
        current_tilt = TILT_NONE;
    }
    else if (var1 == 1 && var2 == 1 && var3 == 1)
    {
        current_tilt = TILT_FORWARD;
    }
    else if (var1 == 0 && var2 == 0 && var3 == 1)
    {
        current_tilt = TILT_BACKWARD;
    }
    else if (var1 == 1 && var2 == 0 && var3 == 0)
    {
        current_tilt = TILT_LEFT;
    }
    else if (var1 == 0 && var2 == 1 && var3 == 0)
    {
        current_tilt = TILT_RIGHT;
    }

    switch (current_tilt)
    {
    case TILT_NONE:
        printf("Tilt: NONE\n");
        break;
    case TILT_FORWARD:
        printf("Tilt: FORWARD\n");
        break;
    case TILT_BACKWARD:
        printf("Tilt: BACKWARD\n");
        break;
    case TILT_LEFT:
        printf("Tilt: LEFT\n");
        break;
    case TILT_RIGHT:
        printf("Tilt: RIGHT\n");
        break;
    default:
        printf("Tilt: UNKNOWN\n");
        break;
    }
}

void direction_control()
{
    // if (turning) return;  // Don't change direction while turning

    switch (current_tilt)
    {
    case TILT_FORWARD:
        motor_set_direction("forward");
        motor_set_speed(128); // 50% speed forward
        printf("moving forward\n");
        break;
    case TILT_BACKWARD:
        motor_set_direction("backward");
        motor_set_speed(128); // 50% speed backward
        gpio_put(BUZZ_PIN, 1);
        gpio_put(LED_PIN1, 1);
        gpio_put(LED_PIN2, 1);
        printf("buzzing & led on\n");
        printf("moving backward\n");
        break;
    case TILT_RIGHT:
        motor_set_direction("right");
        motor_set_speed(128); // 25% speed for turning
        printf("turning right\n");
        break;
    case TILT_LEFT:
        motor_set_direction("left");
        motor_set_speed(128); // 25% speed for turning
        printf("turning left\n");
        break;
    case TILT_NONE:
        motor_stop();
        printf("stopping\n");
        break;
    default:
        motor_stop();
        printf("default state\n");
        break;
    }

    if (current_tilt != TILT_BACKWARD)
    {
        gpio_put(BUZZ_PIN, 0);
        gpio_put(LED_PIN1, 0);
        gpio_put(LED_PIN2, 0);
        printf("buzzing & led off\n");
    }
}

void on_ir_interrupt(uint gpio, uint32_t events)
{
    if (gpio == IR_SENSOR_PIN)
    {
        if (ir_sensor_read(IR_SENSOR_PIN))
        {
            motor_stop();
        }
        else
        {
            direction_control();
        }
    }
}

int main()
{
    stdio_init_all();

    motor_pwm_init();

    ir_sensor_init(IR_SENSOR_PIN);
    // gpio_set_irq_enabled_with_callback(IR_SENSOR_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &on_ir_interrupt);

    gpio_init(LED_PIN1);
    gpio_set_dir(LED_PIN1, GPIO_OUT);
    gpio_init(LED_PIN2);
    gpio_set_dir(LED_PIN2, GPIO_OUT);
    gpio_init(BUZZ_PIN);
    gpio_set_dir(BUZZ_PIN, GPIO_OUT);
    gpio_put(BUZZ_PIN, 0);
    gpio_put(LED_PIN1, 0);
    gpio_put(LED_PIN2, 0);

    gpio_init(pin1);
    gpio_init(pin2);
    gpio_init(pin3);
    gpio_set_dir(pin1, GPIO_IN);
    gpio_set_dir(pin2, GPIO_IN);
    gpio_set_dir(pin3, GPIO_IN);

    while (true)
    {

        int x = gpio_get(IR_SENSOR_PIN);

        if (x)
        {

            setInput();
            direction_control();
            sleep_ms(1);
        }
        else
        {
            motor_stop();
        }
    }

    return 0;
}
