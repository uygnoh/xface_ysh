void HALL_TIMx_Init(void)
{
        GPIO_InitTypeDef                PORT;
        //使用“定时器3”的通道“4”，用于超时检测
        TIM_OC_InitTypeDef              TIMEOUT_OCC4;
        //使用“定时器3”的通道“1”， 配置为霍尔传感器模式
        TIM_HallSensor_InitTypeDef      HALL_SENSOR;
        //配置霍尔传感器模式
        TIM_HandleTypeDef               TIMER_HALL;
        
        //GPIO和定时器时钟开启
        HALL_TIM_RCC_CLK_ENABLE();
        HALL_TIM_GPIO_CLK_ENABLE();
        
        //定时器3“通道1”功能引脚IO初始化
        PORT.Pin        = HALL_TIM_CH1_PIN;
        PORT.Mode       = GPIO_MODE_AF_INPUT;
        PORT.Pull       = GPIO_PULLUP;
        HAL_GPIO_Init(HALL_TIM_CH1_GPIO, &PORT);
        //定时器3“通道2”功能引脚IO初始化
        PORT.Pin        = HALL_TIM_CH2_PIN;
        PORT.Mode       = GPIO_MODE_AF_INPUT;
        PORT.Pull       = GPIO_PULLUP;
        HAL_GPIO_Init(HALL_TIM_CH2_GPIO, &PORT);
        //定时器3“通道3”功能引脚IO初始化
        PORT.Pin        = HALL_TIM_CH3_PIN;
        PORT.Mode       = GPIO_MODE_AF_INPUT;
        PORT.Pull       = GPIO_PULLUP;
        HAL_GPIO_Init(HALL_TIM_CH3_GPIO, &PORT);
        
        
        //定时器引脚重映射
        HALL_TIM_AFIO_REMAP();
        
        
        //配置定时器3， 霍尔传感器模式
        TIMER_HALL.Instance             = TIM3;
        TIMER_HALL.Init.Prescaler       = HALL_TIM_PRESCALER;
        TIMER_HALL.Init.CounterMode     = TIM_COUNTERMODE_UP;
        TIMER_HALL.Init.Period          = HALL_TIM_PERIOD;
        TIMER_HALL.Init.ClockDivision   = TIM_CLOCKDIVISION_DIV1;
        //配置霍尔传感器， 定时器3的输入通道“1”
        HALL_SENSOR.IC1Prescaler        = TIM_ICPSC_DIV1;
        HALL_SENSOR.IC1Polarity         = TIM_ICPOLARITY_RISING;
        HALL_SENSOR.IC1Filter           = 10;
        HALL_SENSOR.commutation_Delay   = 0;
        HAL_TIMEx_HallSensor_Init(&TIMER_HALL, &HALL_SENSOR);
        
        
        //配置定时器3的输入通道“4”， 配置为基本计数功能， 作为超时检测
        //用于电机堵转, 如果电机堵转，让电机停止
        TIMEOUT_OCC4.OCMode             = TIM_OCMODE_TIMING;
        TIMEOUT_OCC4.Pulse              = 0xFFFF;
        TIMEOUT_OCC4.OCPolarity         = TIM_OCPOLARITY_HIGH;
        TIMEOUT_OCC4.OCfastMode         = TIM_OCFAST_DISABLE;
        TIMEOUT_OCC4.OCIdleState        = TIM_OCIDLESTATE_SET;
        HAL_TIM_OC_ConfigChannel(&TIMER_HALL, &TIMEOUT_OCC4, TIM_CHANNEL_4);
        TIM_CCxChannelCmd(HALL_TIMx, TIM_CHANNEL_4, TIM_CCx_ENABLE);
        
        HAL_NVIC_SetPriority(HALL_TIM_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(HALL_TIM_IRQn);
}
