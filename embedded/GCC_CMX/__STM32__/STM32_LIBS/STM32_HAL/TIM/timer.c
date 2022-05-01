
TIM_HandleTypeDef htim2;

/*******************************************************************************
        => （定时器2）作为输入捕获__PA15_TIM2-CH1__利用功能推挽输出
        => （PA5输出）作为一个普通的GPIO端口输出， 它连接PA15， 用于测量PA5输出的脉冲宽度
*******************************************************************************/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_base)
{
        GPIO_InitTypeDef Y;
        if (tim_base == &htim2) {
                __HAL_RCC_TIM2_CLK_ENABLE();    //定时器2时钟开启
                __HAL_RCC_GPIOA_CLK_ENABLE();   //GPIOA时钟开启
                
                
                //（定时器2_通道1）作为输入捕获引脚
                //（定时器2_通道1）重映射到（PA15）
                //（PA15） ------> （PA2）
                //（PA2）作为输出的脉冲源
                //（PA15）它用于测量（PA2）引脚上的频率
                Y.Pin       = GPIO_PIN_15;
                Y.Mode      = GPIO_MODE_AF_PP;  //输入模式（因为使用复用功能）
                Y.Pull      = GPio_PULLDOWN;    //上升沿检测，一般配置为（下拉模式）
                Y.Alternate = GPIO_AF1_TIM2;    //定时器的复用引脚
                HAL_GPIO_Init(GPIOA, &Y);
                
                
                //（GPIO__PA2）作为脉冲的输出，被测量源
                Y.Pin   = GPIO_PIN_2;
                Y.Mode  = GPIO_MODE_OUTPUT_PP;  //输出模式
                Y.Speed = GPIO_SPEED_FREQ_HIGH;
                Y.Pull  = GPIO_PULLUP;
                Y.Alternate = 0;
                HAL_GPIO_Init(GPIOA, &Y);
                
                //（定时器2）中断优先级
                HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
                HAL_NVIC_EnableIRQ(TIM2_IRQn);
        }
}


//设置定时器2的输入频率为（72MHz）
void timer2_setup(void)
{
        TIM_ClockConfigTypeDef sClockSourceConfig;
        TIM_MasterConfigTypeDef sMasterConfig;
        TIM_IC_InitTypeDef sConfigIC;
        //打开定时器2时钟
        __HAL_RCC_TIM2_CLK_ENABLE();
        
        //TIM2__基本配置
        htim2.Instance           = TIM2;                        //定时器选择
        htim2.Init.Prescaler     = 0;                           //预分频
        htim2.Init.CounterMode   = TIM_COUNTERMODE_UP;          //向上计数
        htim2.Init.Period        = 0xFFFF;                      //周期
        htim2.Init.ClockDivision = TIM_CLOCKDIVSION_DIV1;       //1分频
        HAL_TIM_Base_Init(&htim2);
        
        //TIM2__使用内部时钟
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
        
        //TIM2从模式__触发输出禁用
        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
        HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);
        
        //TIM2__输入捕获通道 1 配置（用于检测脉冲的宽度）
        sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING; //上升沿检测
        sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;       //直接连接（TI1 <===> IC1）
        sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;                 //不分频
        sConfigIC.ICFilter = 0;                                 //不滤波
        HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1);
}

__IO struct_capture strCapture = {0, 1, 0, 0, 0};
__IO uint32_t uwTick;
int32_t Toggle_Pulse = 0;
__IO int32_t ulCcr;
double fFreq;
int32_t ulTimClk;

int main(void)
{
        //获取定时器时钟频率
        ulTimClk = 72000000;
        //使能定时器更新中断并且启动定时器
        HAL_TIM_Base_Start_IT(&htim2);
        //启动（定时器2输入捕获通道1）并开启中断
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
        
        Toggle_Pulse = 4000;    //40ms翻转一次，输出125Hz的脉冲
        
        strCapture.ucFinishFlag = 0;
        strCapture.ucStartFlag  = 0;
        
        while (1) {
                //完成测量高电平脉宽
                if (strCapture.ucFinishFlag == 1) {
                }
        }
}


HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
{
        //使能定时器更新中断
        __HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);
        //使能定时器外设
        __HAL_TIM_ENABLE(htim);
}


//使能定时器2输入捕获通道1中断
HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
        switch (Channel) {
        case TIM_CHANNEL_1:
                __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
        }
}

GENERAL_TIM_IT_CC1      TIM_IT_CC1
//定时器2中断函数入口
void TIM2_IRQHandler(void)
{
        HAL_TIM_IRQHandler(&htim2);
}

//非阻塞模式下定时器的回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
        if (strCapture.ucStatFlag == 1)
                strCapture.sPeriod++;
}

//滴答定时器中断回调函数
void HAL_SYSTICK_Callback()
{
        if ((uwTick % Toggle_Pulse) == 0)
                HAL_GPIO_TogglePin(GPIOA, LED_01);
}
