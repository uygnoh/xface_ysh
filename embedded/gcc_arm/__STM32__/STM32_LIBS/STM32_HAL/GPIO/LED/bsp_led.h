#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f1xx.h"

/* LED灯打开 */
#define LED_RED_ON()  do {                                  \
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin_5, GPIO_PIN_RESET);   \
} while (0)
/* LED灯关闭 */
#define LED_RED_OFF() do {                                  \
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin_5, GPIO_PIN_SET);     \
} while (0)
/* LED灯翻转 */
#define LED_RED_TOOGLE() do {                               \
    HAL_GPIO_TooglePin(GPIOB, GPIO_Pin_5);                  \
} while (0)


void led_gpio_init(void);
#endif

