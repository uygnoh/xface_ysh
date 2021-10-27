/*******************************************************************************
        => （定时器2）作为输入捕获__PA15_TIM2-CH1__利用功能推挽输出
        => （PA5输出）作为一个普通的GPIO端口输出， 它连接PA15， 用于测量PA5输出的脉冲宽度
*******************************************************************************/
//设置定时器2的输入频率为（72MHz）
void timer2_setup(void)
{
        TIM_ClockConfigTypeDef sClockSourceConfig;
        TIM_MasterConfigTypeDef sMasterConfig;
        TIM_IC_InitTypeDef sConfigIC;
        //打开定时器2时钟
        __HAL_RCC_TIM2_CLK_ENABLE();
        
        htim2.Instance           = TIM2;
        htim2.Init.Prescaler     = 0;
        htim2.Init.CounterMode   = TIM_COUNTERMODE_UP;
        htim2.Init.Period        = 0xFFFF;
        htim2.Init.ClockDivision = TIM_CLOCKDIVSION_DIV1;
}
