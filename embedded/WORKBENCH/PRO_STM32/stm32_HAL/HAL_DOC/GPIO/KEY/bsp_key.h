#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "stm32f1xx.h"

// 引脚宏定义
/*****************************************************************/
#define KEY1_PIN                    GPIO_PIN_0
#define KEY1_GPIO_PORT              GPIOA
#define KEY1_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define KEY2_PIN                    GPIO_PIN_6
#define KEY2_GPIO_PORT              GPIOB
#define KEY2_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
/*****************************************************************/


/*
按键按下为高电平，设置KEY_ON=1
按键按下为低电平，设置KEY_OFF=0
*/
#define KEY_ON          1
#define KEY_OFF         0


void key_gpio_init(void);
uint8_t key_scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif

