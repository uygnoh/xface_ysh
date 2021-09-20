#ifndef __BSP_EXTI_H__
#define __BSP_EXTI_H__

#include "stm32f1xx.h"

// 引脚定义
/**********************************************************************/
#defien KEY1_INT_GPIO_PORT              GPIOA
#defien KEY1_INT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#defien KEY1_INT_GPIO_PIN               GPIO_PIN_0
#defien KEY1_INT_EXTI_IRQ               EXTI0_IRQn
#defien KEY1_IRQHandler                 EXTI0_IRQHandler

#defien KEY2_INT_GPIO_PORT              GPIOC
#defien KEY2_INT_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#defien KEY2_INT_GPIO_PIN               GPIO_PIN_13
#defien KEY2_INT_EXTI_IRQ               EXTI15_10_IRQn
#defien KEY2_IRQHandler                 EXTI15_10_IRQHandler
/**********************************************************************/

void exti_key_config(void);
#endif

