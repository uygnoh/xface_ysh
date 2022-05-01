#include "stm32f1xx_hal.h"

//高级定时器时钟
#define TIM1_RCC_CLK_ENABLE()           __HAL_RCC_TIM1_CLK_ENABLE();
#define TIM1_RCC_CLK_DISABLE()          __HAL_RCC_TIM1_CLK_DISABLE();
//GPIO时钟打开
#define TIM1_RCC_GPIO_CLK_ENABLE() {    \
        __HAL_RCC_GPIOA_CLK_ENABLE();   \
        __HAL_RCC_GPIOB_CLK_ENABLE();   \
}


//“高级定时器1”通道 (3个上桥臂)
#define TIM1_CH1_PORT                   GPIOA
#define TIM1_CH1_PIN                    GPIO_PIN_8
#define TIM1_CH2_PORT                   GPIOA
#define TIM1_CH2_PIN                    GPIO_PIN_9
#define TIM1_CH3_PORT                   GPIOA
#define TIM1_CH3_PIN                    GPIO_PIN_10
//“高级定时器1”互补通道 (3个下桥臂)
#define TIM1_CH1N_PORT                  GPIOB
#define TIM1_CH1N_PIN                   GPIO_PIN_13
#define TIM1_CH2N_PORT                  GPIOB
#define TIM1_CH2N_PIN                   GPIO_PIN_14
#define TIM1_CH3N_PORT                  GPIOB
#define TIM1_CH3N_PIN                   GPIO_PIN_15
//高级定时器刹车功能
#define TIM1_BKIN_PORT                  GPIOB
#define TIM1_BKIN_PIN                   GPIO_PIN_12


//定时器频率为72MHz
//定义定时器预分频， 定时器实际时钟频率为： 72MHz/(ADVANCEDx_PRESCALER + 1)
#define TIM1_PRESCALER                  0       


//PWM频率 20K 
#define TIM1_PWM_FREQ                   20000


//定义定时器周期
//当定时器开始计数到TIM1_PERIOD值并且重复计数寄存器为“0”时, 更新定时器并生成对应事件和中断
#define TIM1_PERIOD                                                    \
        (SystemCoreClock / (TIM1_PRESCALER + 1) / TIM1_PWM_FREQ)


//定义高级定时器重复计数寄存器值
#define TIM1_REPETITIONCOUNTER          0


//定义全局句柄结构体
extern TIM_HandleTypeDef                TIMER_BLDC;
extern TIM_OC_InitTypeDef               PWM_CH1, PWM_CH2, PWM_CH3;
