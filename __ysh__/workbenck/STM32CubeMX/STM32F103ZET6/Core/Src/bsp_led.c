#include "bsp_led.h"

/*******************************************************************************
        => 回调函数（中间层函数）
*******************************************************************************/
//函数声明
void HOS(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T));
//函数功能
void HOS(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T))
{
        (*callback_fun)(led_number);
}

//定义（LED_STRUCT_T LED）结构体，申请空间并初始化它
LED_STRUCT_T LED = { HOS };

//定义（LED_STRUCT_T *）结构体指针，并没有初始化指针
LED_STRUCT_T *BSP;



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
