#include "bsp_led.h"

//定义结构体类型数据（此时已经分配了存储空间）
led_struct_t *LED = {bsp_ledx};


void bsp_ledx(led_enum_t led_number, void (*callback_fun)(led_enum_t))
{
        (*callback_fun)(led_number);
}

void led_on(led_enum_t led_number)
{
        switch (led_number) {
        case LED_01: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); break;
        case LED_02: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); break;
        case LED_03: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); break;
        default: break;
        }
}

void led_off(led_enum_t led_number)
{
        switch (led_number) {
        case LED_01: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); break;
        case LED_02: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); break;
        case LED_03: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); break;
        default: break;
        }
}
