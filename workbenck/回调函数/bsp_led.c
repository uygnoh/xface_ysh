#include "bsp_led.h"

LED_STRUCT_T LED = { bsp_led };

void bsp_led(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T))
{
        (*callback_fun)(led_number);
}

// LED_STRUCT_T *led;
// led = &LED;
// LED.bsp(LED_01,  led_on);
// led->bsp(LED_01, led_on);

void led_on(LED_ENUM_T led_number)
{
        switch (led_number) {
        case LED_01: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); break;
        case LED_02: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); break;
        case LED_03: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); break;
        default: break;
        }
}

void led_off(LED_ENUM_T led_number)
{
        switch (led_number) {
        case LED_01: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); break;
        case LED_02: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); break;
        case LED_03: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); break;
        default: break;
        }
}
