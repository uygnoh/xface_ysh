#include "stm32f1xx_hal.h"


//高级定时器时钟打开
#define ADCANCED_TIMx                           TIM1
#define ADVANCED_TIM_RCC_CLK_ENABLE()           __HAL_RCC_TIM1_CLK_ENABLE()
#define ADVANCED_TIM_RCC_CLK_DISABLE()          __HAL_RCC_TIM1_CLK_DISABLE()
//GPIO时钟打开
#define ADVANCED_TIM_RCC_GPIO_CLK_ENABLE()      {                              \
        __HAL_RCC_GPIOA_CLK_ENABLE();                                          \
        __HAL_RCC_GPIOB_CLK_ENABLE();                                          \
                                                }


//高级定时器通道 (3个上桥臂)
#define ADVANCED_TIM_CH1_PORT           GPIOA
#define ADVANCED_TIM_CH1_PIN            GPIO_PIN_8
#define ADVANCED_TIM_CH2_PORT           GPIOA
#define ADVANCED_TIM_CH2_PIN            GPIO_PIN_9
#define ADVANCED_TIM_CH3_PORT           GPIOA
#define ADVANCED_TIM_CH3_PIN            GPIO_PIN_10
//高级定时器互补通道 (3个下桥臂)
#define ADVANCED_TIM_CH1N_PORT          GPIOB
#define ADVANCED_TIM_CH1N_PIN           GPIO_PIN_13
#define ADVANCED_TIM_CH2N_PORT          GPIOB
#define ADVANCED_TIM_CH2N_PIN           GPIO_PIN_14
#define ADVANCED_TIM_CH3N_PORT          GPIOB
#define ADVANCED_TIM_CH3N_PIN           GPIO_PIN_15
//高级定时器刹车功能
#define ADVANCED_TIM_BKIN_PORT          GPIOB
#define ADVANCED_TIM_BKIN_PIN           GPIO_PIN_12


//定时器频率为72MHz
//定义定时器预分频， 定时器实际时钟频率为： 72MHz/(ADVANCEDx_PRESCALER + 1)
#define ADVANCED_TIM_PRESCALER          0       


//PWM频率 20K 
#define ADVANCED_TIM_PWM_FREQ           20000


//定义定时器周期
//当定时器开始计数到TIM1_PERIOD值并且重复计数寄存器为“0”时, 更新定时器并生成对应事件和中断
#define ADVANCED_TIM_PERIOD                                                    \
        (SystemCoreClock / (ADVANCED_TIM_PRESCALER + 1) / ADVANCED_TIM_PWM_FREQ)

//定义高级定时器重复计数寄存器值
#define ADVANCED_TIM_REPETITIONCOUNTER  0


//定义全局句柄结构体
extern TIM_HandleTypeDef                htimx_BLDC;
extern TIM_OC_InitTypeDef               sPWMConfig1, sPWMConfig2, sPWMConfig3;
