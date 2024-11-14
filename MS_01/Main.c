#include "pico/stdlib.h"

#define RED_LED_PIN 25   // D2
#define GREEN_LED_PIN 15 // D3
#define BLUE_LED_PIN 16  // D4
#define BUTTON_1_PIN 17  // D5
#define BUTTON_2_PIN 18  // D6

int main()
{
    // // Initialize serial port for debugging (optional)
    // stdio_init_all();

    // LEDS
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    // Buttons
    gpio_init(BUTTON_1_PIN);
    gpio_set_dir(BUTTON_1_PIN, GPIO_IN);

    gpio_init(BUTTON_2_PIN);
    gpio_set_dir(BUTTON_2_PIN, GPIO_IN);

    gpio_put(RED_LED_PIN, 0);
    gpio_put(GREEN_LED_PIN, 0);
    gpio_put(BLUE_LED_PIN, 1);

    while (true)
    {
        int button1State = gpio_get(BUTTON_1_PIN);
        int button2State = gpio_get(BUTTON_2_PIN);

        if (button1State == 1)
        {
            gpio_put(RED_LED_PIN, 1);
            gpio_put(GREEN_LED_PIN, 1);
        }
        else
        {
            gpio_put(RED_LED_PIN, 0);
            gpio_put(GREEN_LED_PIN, 0);
        }

        if (button2State == 1)
        {
            gpio_put(BLUE_LED_PIN, 1);
        }
        else
        {
            gpio_put(BLUE_LED_PIN, 0);
        }

        sleep_ms(10);
    }
}
