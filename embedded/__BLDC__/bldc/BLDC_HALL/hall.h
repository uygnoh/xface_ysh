#include "stm32f1xx_hal.h"

//霍尔传感器使用“定时器3”
#define HALL_TIMx                       TIM3
#define HALL_TIM_RCC_CLK_ENABLE()       __HAL_RCC_TIM3_CLK_ENABLE()
#define HALL_TIM_RCC_CLK_DISABLE()      __HAL_RCC_TIM3_CLK_DISABLE()

//开启引脚重映射功能
#define HALL_TIM_AFIO_REMAP()           __HAL_AFIO_REMAP_TIM3_ENABLE()
#define HALL_TIM_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define HALL_TIM_CH1_GPIO               GPIOC
#define HALL_TIM_CH1_PIN                GPIO_PIN_6
#define HALL_TIM_CH1_GPIO               GPIOC
#define HALL_TIM_CH1_PIN                GPIO_PIN_7
#define HALL_TIM_CH1_GPIO               GPIOC
#define HALL_TIM_CH1_PIN                GPIO_PIN_8

//定义定时器预分频， 定时器实际时钟为： 72MHz / (HALL_TIMx_PRESCALER + 1)
#define HALL_TIM_PRESCALER              71

//定义定时器周期， 当定时器计数到HALL_TIMx_PERIOD值时更新定时器并生成对应事件和中断
#define HALL_TIM_PERIOD                 0xFFFF

#define HALL_TIM_IRQn                   TIM3_IRQn
#define HALL_TIM_IRQHANDLER             TIM3_IRQHandler

extern TIM_HandleTypeDef TIMER_HALL;

