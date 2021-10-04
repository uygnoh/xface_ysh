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


void TIM_MspPostInit(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
    
    /* 高级定时器时钟开启 */
    ADVANCED_TIM_RCC_CLK_ENABLE();
    /* 高级定时器引脚初始化 */
    TIM_MspPostInit();
    
    
    /* 高级定时器PWM1配置 */
    htimx_BLDC.Instance                     = ADVANCED_TIMx;
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
