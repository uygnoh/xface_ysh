/*******************************************************************************
                               BLDCM_TIMER 1
*******************************************************************************/
#include "stm32f1xx_hal.h"


//高级定时器时钟配置
#define ADVANCED_TIM_RCC_CLK_ENABLE()       __HAL_RCC_TIM1_CLK_ENABLE()
#define ADVANCED_TIM_RCC_CLK_DISABLE()      __HAL_RCC_TIM1_CLK_DISABLE()
//高级定时器GPIO时钟配置
#define ADVANCED_TIM_RCC_GPIO_CLK_ENABLE()      \
        {__HAL_RCC_GPIOA_CLK_ENABLE();__HAL_RCC_GPIOB_CLK_ENABLE();}


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


///定时器频率为72MHz
//定义定时器预分频， 定时器实际时钟频率为： 72MHz/(ADVANCEDx_PRESCALER + 1)
#define ADVANCED_TIM_PRESCALER          0       
//定义高级定时器重复计数寄存器值
#define ADVANCED_TIM_REPETITIONCOUNTER  0


//PWM频率 20K 
#define ADVANCED_TIM_PWM_FREQ           20000
/* 定义定时器周期，当定时器开始计数到TIM1_PERIOD值并且重复计数寄存器为“0”时
   更新定时器并生成对应事件和中断 */
#define ADVANCED_TIM_PERIOD (SystemCoreClock/(ADVANCED_TIM_PRESCALER+1)/ADVANCED_TIM_PWM_FREQ)


//定义全局句柄结构体
extern TIM_HandleTypeDef                htimx_BLDC;
extern TIM_OC_InitTypeDef               sPWMConfig1, sPWMConfig2, sPWMConfig3;



/*******************************************************************************
                               输出6路PWM波形
*******************************************************************************/
//高级定时器初始化
void ADVANCED_TIM_MspPostInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    /* 定时器通道功能引脚端口时钟使能 */
    ADVANCED_TIM_RCC_GPIO_CLK_ENABLE();
    
    
    /* 定时器通道1功能引脚IO初始化 */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_CH1_PIN;
    GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ADVANCED_TIM_CH1_PORT, &GPIO_InitStruct);
    /* 定时器通道1互补通道功能引脚IO初始化 */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_CH1N_PIN;
    HAL_GPIO_Init(ADVANCED_TIM_CH1N_PORT, &GPIO_InitStruct);


    /* 定时器通道2功能引脚IO初始化 */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_CH1_PIN;
    GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ADVANCED_TIM_CH2_PORT, &GPIO_InitStruct);
    /* 定时器通道2互补通道功能引脚IO初始化 */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_CH1N_PIN;
    HAL_GPIO_Init(ADVANCED_TIM_CH2N_PORT, &GPIO_InitStruct);
    
    
    /* 定时器通道3功能引脚IO初始化 */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_CH1_PIN;
    GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ADVANCED_TIM_CH3_PORT, &GPIO_InitStruct);
    /* 定时器通道3互补通道功能引脚IO初始化 */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_CH1N_PIN;
    HAL_GPIO_Init(ADVANCED_TIM_CH3N_PORT, &GPIO_InitStruct);
    
    
    /* 定时器制动功能引脚初始化IO */
    GPIO_InitStruct.Pin     = ADVANCED_TIM_BKIN_PIN;
    GPIO_InitStruct.Mode    = GPIO_MODE_AF_INPUT;
    GPIO_InitStruct.Pull    = GPIO_PULLDOWN;
    HAL_GPIO_Init(ADVANCED_TIM_BKIN_PORT, &GPIO_InitStruct);    
}


void TIM1_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
    
    /* 高级定时器时钟开启 */
    ADVANCED_TIM_RCC_CLK_ENABLE();
    
    /* 高级定时器引脚初始化 */
    ADVANCED_TIM_MspPostInit();
    
    
    /* 高级定时器PWM1配置 */
    htimx_BLDC.Instance                     = TIM1;
    htimx_BLDC.Init.Prescaler               = ADVANCED_TIM_PRESCALER;
    htimx_BLDC.Init.CounterMode             = TIM_COUNTERMODE_UP;
    htimx_BLDC.Init.Period                  = ADVANCED_TIM_PERIOD-1;
    htimx_BLDC.Init.ClockDivision           = TIM_CLOCKDIVSION_DIV1;
    htimx_BLDC.Init.RepetitionCounter       = ADVANCED_TIM_REPETITIONCOUNTER;
    HAL_TIM_PWM_Init(&htimx_BLDC);
    
    
    /* 高级定时时钟源选择 */
    sClockSourceConfig.ClockSource          = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htimx_BLDC, &sClockSourceConfig);
    
    
    /* 高级定时器刹车功能配置 */
    sBreakDeadTimeConfig.OffStateRunMode    = TIM_OSSR_ENABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode   = TIM_OSSI_ENABLE;
    sBreakDeadTimeConfig.LockLevel          = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime           = 0;
    sBreakDeadTimeConfig.BreakState         = TIM_BREAK_ENABLE;
    sBreakDeadTimeConfig.BreakPolarity      = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOuput     = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&htimx_BLDC, &sBreakDeadTimeConfig);


    /* 高级定时器通道1配置 */    
    sPWMConfig1.OCMode                      = TIM_OCMODE_PWM1;
    sPWMConfig1.Pulse                       = 0;
    sPWMConfig1.OCPolarity                  = TIM_OCPOLARITY_HIGH;
    sPWMConfig1.OCNPolarity                 = TIM_OCNPOLARITY_HIGH;
    sPWMConfig1.OCFastMode                  = TIM_OCFAST_DISABLE;
    sPWMConfig1.OCIdleState                 = TIM_OCIDLESTATE_SET;
    sPWMConfig1.OCNIdleState                = TIM_OCNIDLESTATE_SET;
    HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig1, TIM_CHANNEL_1);
    /* 高级定时器通道2配置 */ 
    sPWMConfig2 = sPWMConfig1;
    HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig2, TIM_CHANNEL_2);
    /* 高级定时器通道3配置 */ 
    sPWMConfig3 = sPWMConfig1;
    HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig3, TIM_CHANNEL_3);   
    
    
    /* 初始化6路PWM为： 关闭状态 */
    HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_3);      
}



__IO uint8_t uwStep      = 0;
__IO uint16_t speed_duty = 15;

void SystemClock_config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_clkInitTypeDef RCC_ClkInitStruct;
    
    /* 使用外部高速8MHz晶振，得到72MHz主频 */
    RCC_OscInitStruct.OscillatorType    = RCC_OSCILLATORTYPE_HSE; // 外部晶振，8MHz
    RCC_OscInitStruct.HSEState          = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState      = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource     = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL        = RCC_PLL_MUL9;             // 9倍频，得到72MHz主频
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
    
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSTEM \
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2; 
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;   // 系统时钟72MHz
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;          // AHB时钟72MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;           // APB1时钟36MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;           // APB2时钟72MHz
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
    
    
    /* 启用时钟安全系统 */
    HAL_RCC_EnableCSS();
    
    
    // HAL_RCC_GetHCLKFreq()/1000       1ms中断一次
    // HAL_RCC_GetHCLKFreq()/100000     10us中断一次
    // HAL_RCC_GetHCLKFreq()/1000000    1us中断一次
    /* 配置并启用系统滴答定时器 */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    /* 系统滴答定时器时钟源 */
    HAL_SYSTICk_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    /* 系统滴答定时器中断优先级配置 */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

int main(void)
{
    /* 复位所有外设，初始化Flash接口和系统滴答定时器 */
    HAL_Init();
    /* 系统时钟配置 */
    SystemClock_Config();
    /* 高级定时器初始化并配置PWM输出功能 */
    TIM1_Init();
    
    uwStep = 5;
    
    while (1)
    {
        BLDC_PHASE_CHANGE();
        HAL_Delay(4);
    }
}

/* 4 5 1 3 2 6 */
void BLDC_PHASE_CHANGE(void)
{
    switch (uwStep)
    {
    case 4:                                                 /* B+ C- */
        /* 通道1关闭 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道2配置 B+*/
        sPWMConfig2.Pulse   = ADVANCED_TIM_PERIOD*Speed_duty/100;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig2, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htimx_BLDC, TIM_CHANNEL_2);
        /* 通道3(互补通道)配置 C-*/
        sPWMConfig3.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig3, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_3);
        /* 执行下一步操作 */
        uwStep = 5;
        break;
        
        
    case 5:                                                 /* B+ A- */
        /* 通道3关闭 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_3);
        /* 通道1(互补通道)配置 A-*/
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig1, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道2配置 B+*/
        sPWMConfig2.Pulse   = ADVANCED_TIM_PERIOD*Speed_duty/100;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig2, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htimx_BLDC, TIM_CHANNEL_2);
        /* 执行下一步操作 */
        uwStep = 1;
        break;
        
        
    case 1:                                                 /* C+ A- */
        /* 通道2关闭 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_2);
        /* 通道1(互补通道)配置 A-*/
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig1, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道3配置 C+*/
        sPWMConfig3.Pulse   = ADVANCED_TIM_PERIOD*Speed_duty/100;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig3, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htimx_BLDC, TIM_CHANNEL_3);
        /* 执行下一步操作 */
        uwStep = 3;
        break;
        
        
    case 3:                                                 /* C+ B- */
        /* 通道1关闭 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道2(互补通道)配置 B-*/
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig2, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_2);
        /* 通道3配置 C+*/
        sPWMConfig3.Pulse   = ADVANCED_TIM_PERIOD*Speed_duty/100;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig3, TIM_CHANNEL_3);
        HAL_TIM_PWM_Start(&htimx_BLDC, TIM_CHANNEL_3);
        /* 执行下一步操作 */
        uwStep = 2;
        break;
        
        
    case 2:                                                 /* A+ B- */
        /* 通道3关闭 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_3);
        /* 通道1配置 A+*/
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD*Speed_duty/100;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道2(互补通道)配置 B-*/
        sPWMConfig2.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig2, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_2);
        /* 执行下一步操作 */
        uwStep = 6;
        break;
        
        
    case 6:                                                 /* A+ C- */
        /* 通道2关闭 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_2);
        /* 通道1配置 A+*/
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD*Speed_duty/100;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道2(互补通道)配置 C-*/
        sPWMConfig3.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig3, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_3);
        /* 执行下一步操作 */
        uwStep = 4;
        break;
        
        
    default:
        /* 6个PWM波全部关断 */
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_2);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_2);
        HAL_TIM_PWM_Stop(&htimx_BLDC, TIM_CHANNEL_3);
        HAL_TIMEx_PWMN_Stop(&htimx_BLDC, TIM_CHANNEL_3); 
    }
}
