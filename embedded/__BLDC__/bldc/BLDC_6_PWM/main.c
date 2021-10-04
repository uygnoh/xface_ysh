/*******************************************************************************
                6步PWM---该工程只用于六步PWM信号生成， 不能用于电机测试！！！
                上桥臂PWM， 下桥臂ON
*******************************************************************************/
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
        sPWMConfig2.Pulse   = ADVANCED_TIM_PERIOD * Speed_duty / 100;
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
        /* 通道1(互补通道)配置 A- */
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD;
        HAL_TIM_PWM_ConfigChannel(&htimx_BLDC, &sPWMConfig1, TIM_CHANNEL_1);
        HAL_TIMEx_PWMN_Start(&htimx_BLDC, TIM_CHANNEL_1);
        /* 通道2配置 B+ */
        sPWMConfig2.Pulse   = ADVANCED_TIM_PERIOD * Speed_duty / 100;
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
        sPWMConfig3.Pulse   = ADVANCED_TIM_PERIOD * Speed_duty / 100;
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
        sPWMConfig3.Pulse   = ADVANCED_TIM_PERIOD * Speed_duty / 100;
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
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD * Speed_duty / 100;
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
        sPWMConfig1.Pulse   = ADVANCED_TIM_PERIOD * Speed_duty / 100;
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

