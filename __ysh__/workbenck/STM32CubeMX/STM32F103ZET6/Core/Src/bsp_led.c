#include "bsp_led.h"

/*******************************************************************************
        => 回调函数（中间层函数）
*******************************************************************************/
//私有函数声明
static void bsp_ledx(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T));

//公有变量定义
LED_STRUCT_T LED = {
        bsp_ledx,
};

//私有函数
static void bsp_ledx(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T))
{
        (*callback_fun)(led_number);
}



/*******************************************************************************
        => 回调函数（底层函数）
*******************************************************************************/
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
