void HALL_TIMx_Init(void)
{
        GPIO_InitTypeDef                GPIO_InitStruct;
        TIM_OC_InitTypeDef              sOCConfig;
        TIM_HallSensor_InitTypeDef      sHallSensorConfig;
        
        HALL_TIM_RCC_CLK_ENABLE();
        HALL_TIM_GPIO_CLK_ENABLE();
        
                //定时器“通道1”功能引脚IO初始化
        GPIO_InitStruct.Pin             =HALL_TIM_CH1_PIN;
        GPIO_InitStruct.Mode            =GPIO_MODE_AF_INPUT;
        GPIO_InitStruct.Pull            =GPIO_PULLUP;
        HAL_GPIO_Init(HALL_TIM_CH1_GPIO, &GPIO_InitStruct);
        
                //定时器“通道2”功能引脚IO初始化
        GPIO_InitStruct.Pin             =HALL_TIM_CH2_PIN;
        GPIO_InitStruct.Mode            =GPIO_MODE_AF_INPUT;
        GPIO_InitStruct.Pull            =GPIO_PULLUP;
        HAL_GPIO_Init(HALL_TIM_CH2_GPIO, &GPIO_InitStruct);
        
                //定时器“通道3”功能引脚IO初始化
        GPIO_InitStruct.Pin             =HALL_TIM_CH3_PIN;
        GPIO_InitStruct.Mode            =GPIO_MODE_AF_INPUT;
        GPIO_InitStruct.Pull            =GPIO_PULLUP;
        HAL_GPIO_Init(HALL_TIM_CH3_GPIO, &GPIO_InitStruct);
        
        //定时器引脚重映射
        HALL_TIM_AFIO_REMAP();
        
        htimx_HALL.Instance             =HALL_TIMx;
        htimx_HALL.Init.Prescaler       =HALL_TIM_PRESCALER;
        htimx_HALL.Init.CounterMode     =TIM_COUNTERMODE_UP;
        htimx_HALL.Init.Period          =HALL_TIM_PERIOD;
        htimx_HALL.Init.ClockDivision   =TIM_CLOCKDIVISION_DIV1;
        
        sHallSensorConfig.IC1Prescaler  =TIM_ICPSC_DIV1;
        sHallSensorConfig.IC1Polarity   =TIM_ICPOLARITY_RISING;
        sHallSensorConfig.IC1Filter     =10;
        sHallSensorConfig.commutation_Delay=0;
        HAL_TIMEx_HallSensor_Init(&htimx_HALL, &sHallSensorConfig);
        
        sOCConfig.OCMode                =TIM_OCMODE_TIMING;
        sOCConfig.Pulse                 =0xFFFF;
        sOCConfig.OCPolarity            =TIM_OCPOLARITY_HIGH;
        sOCConfig.OCfastMode            =TIM_OCFAST_DISABLE;
        sOCConfig.OCIdleState           =TIM_OCIDLESTATE_SET;
        HAL_TIM_OC_ConfigChannel(&htimx_HALL, &sOCConfig, TIM_CHANNEL_4);
        TIM_CCxChannelCmd(HALL_TIMx, TIM_CHANNEL_4, TIM_CCx_ENABLE);
        
        HAL_NVIC_SetPriority(HALL_TIM_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(HALL_TIM_IRQn);
}
