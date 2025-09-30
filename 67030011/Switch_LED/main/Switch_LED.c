#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define SWITCH1_PIN 15
#define LED1_PIN 17
#define SWITCH2_PIN 16
#define LED2_PIN 18

void setup_pins(void)
{
    gpio_set_direction(SWITCH1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SWITCH2_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);
    
    gpio_set_level(LED1_PIN, 0);
    gpio_set_level(LED2_PIN, 0);
}

int is_switch1_pressed(void)
{
    return gpio_get_level(SWITCH1_PIN) == 0;
}

int is_switch2_pressed(void)
{
    return gpio_get_level(SWITCH2_PIN) == 0;
}

void turn_led1_on(void)
{
    gpio_set_level(LED1_PIN, 1);
}

void turn_led1_off(void)
{
    gpio_set_level(LED1_PIN, 0);
}

void turn_led2_on(void)
{
    gpio_set_level(LED2_PIN, 1);
}

void turn_led2_off(void)
{
    gpio_set_level(LED2_PIN, 0);
}

void app_main(void)
{
    int led1_is_on = 0;
    int led2_is_on = 0;
    int switch1_was_pressed = 0;
    int switch2_was_pressed = 0;
    
    setup_pins();
    
    while(1)
    {
        if (is_switch1_pressed() && !switch1_was_pressed)
        {
            if (led1_is_on)
            {
                turn_led1_off();
                led1_is_on = 0;
            }
            else
            {
                turn_led1_on();
                led1_is_on = 1;
            }
        }
        
        if (is_switch2_pressed() && !switch2_was_pressed)
        {
            if (led2_is_on)
            {
                turn_led2_off();
                led2_is_on = 0;
            }
            else
            {
                turn_led2_on();
                led2_is_on = 1;
            }
        }
        
        switch1_was_pressed = is_switch1_pressed();
        switch2_was_pressed = is_switch2_pressed();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
