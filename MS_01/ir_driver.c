#include "ir_driver.h"

// Function to initialize the infrared sensor
void ir_sensor_init(uint pin)
{
    gpio_init(pin);             // Initialize the pin
    gpio_set_dir(pin, GPIO_IN); // Set the pin as an input
    gpio_pull_up(pin);          // Enable the internal pull-up resistor (optional)
}

// Function to read the infrared sensor state
bool ir_sensor_read(uint pin)
{
    return gpio_get(pin); // Returns the state of the pin (true/false)
}
