//高级定时器初始化
void TIM1_MspPostInit(void)
{
        GPIO_InitTypeDef GPIO_InitStruct;
        
        /* 定时器通道功能引脚端口时钟使能 */
        TIM1_RCC_GPIO_CLK_ENABLE();


        /* 定时器通道1功能引脚IO初始化 */
        GPIO_InitStruct.Pin     = TIM1_CH1_PIN;
        GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(TIM1_CH1_PORT, &GPIO_InitStruct);
        /* 定时器通道1互补通道功能引脚IO初始化 */
        GPIO_InitStruct.Pin     = TIM1_CH1N_PIN;
        HAL_GPIO_Init(TIM1_CH1N_PORT, &GPIO_InitStruct);


        /* 定时器通道2功能引脚IO初始化 */
        GPIO_InitStruct.Pin     = TIM1_CH1_PIN;
        GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(TIM1_CH2_PORT, &GPIO_InitStruct);
        /* 定时器通道2互补通道功能引脚IO初始化 */
        GPIO_InitStruct.Pin     = TIM1_CH1N_PIN;
        HAL_GPIO_Init(TIM1_CH2N_PORT, &GPIO_InitStruct);


        /* 定时器通道3功能引脚IO初始化 */
        GPIO_InitStruct.Pin     = TIM1_CH1_PIN;
        GPIO_InitStruct.Mode    = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(TIM1_CH3_PORT, &GPIO_InitStruct);
        /* 定时器通道3互补通道功能引脚IO初始化 */
        GPIO_InitStruct.Pin     = TIM1_CH1N_PIN;
        HAL_GPIO_Init(TIM1_CH3N_PORT, &GPIO_InitStruct);


        /* 定时器制动功能引脚初始化IO */
        GPIO_InitStruct.Pin     = TIM1_BKIN_PIN;
        GPIO_InitStruct.Mode    = GPIO_MODE_AF_INPUT;
        GPIO_InitStruct.Pull    = GPIO_PULLDOWN;
        HAL_GPIO_Init(TIM1_BKIN_PORT, &GPIO_InitStruct);    
}


void TIM_MspPostInit(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
    
    /* 高级定时器时钟开启 */
    TIM1_RCC_CLK_ENABLE();
    /* 高级定时器引脚初始化 */
    TIM_MspPostInit();
    
    
    /* 高级定时器PWM1配置 */
    TIMER_BLDC.Instance                     = TIM1;
    TIMER_BLDC.Init.Prescaler               = TIM1_PRESCALER;
    TIMER_BLDC.Init.CounterMode             = TIM_COUNTERMODE_UP;
    TIMER_BLDC.Init.Period                  = TIM1_PERIOD - 1;
    TIMER_BLDC.Init.ClockDivision           = TIM_CLOCKDIVSION_DIV1;
    TIMER_BLDC.Init.RepetitionCounter       = TIM1_REPETITIONCOUNTER;
    HAL_TIM_PWM_Init(&TIMER_BLDC);
    
    
    /* 高级定时时钟源选择 */
    sClockSourceConfig.ClockSource          = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&TIMER_BLDC, &sClockSourceConfig);
    
    
    /* 高级定时器刹车功能配置 */
    sBreakDeadTimeConfig.OffStateRunMode    = TIM_OSSR_ENABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode   = TIM_OSSI_ENABLE;
    sBreakDeadTimeConfig.LockLevel          = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime           = 5;
    sBreakDeadTimeConfig.BreakState         = TIM_BREAK_DISABLE;        //刹车输入关闭
    sBreakDeadTimeConfig.BreakPolarity      = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOuput     = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&TIMER_BLDC, &sBreakDeadTimeConfig);


    /* 高级定时器通道1配置 */    
    PWM_CH1.OCMode                      = TIM_OCMODE_PWM1;
    PWM_CH1.Pulse                       = 0;
    PWM_CH1.OCPolarity                  = TIM_OCPOLARITY_HIGH;
    PWM_CH1.OCNPolarity                 = TIM_OCNPOLARITY_HIGH;
    PWM_CH1.OCFastMode                  = TIM_OCFAST_DISABLE;
    PWM_CH1.OCIdleState                 = TIM_OCIDLESTATE_SET;
    PWM_CH1.OCNIdleState                = TIM_OCNIDLESTATE_SET;
    HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
    /* 高级定时器通道2配置 */ 
    PWM_CH2 = PWM_CH1;
    HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
    /* 高级定时器通道3配置 */ 
    PWM_CH_3 = PWM_CH1;
    HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);   
    
    
    /* 初始化6路PWM为： 关闭状态 */
    HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);      
}
