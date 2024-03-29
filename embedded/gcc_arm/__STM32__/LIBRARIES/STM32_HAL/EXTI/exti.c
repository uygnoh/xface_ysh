/*******************************************************************************
        => 外部中断线
*******************************************************************************/
// 外部中断线引脚配置
//_________________________________________________________
void exti_gpio_setup(void)
{
        GPIO_InitTypeDef Y;
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        Y.Pin   = GPIO_PIN_0;           //PA_0
        Y.Mode  = GPIO_MODE_IT_RISING;  //上升沿触发（中断）
        Y.Pull  = GPIO_PULLDOWN;        //下拉
        Y.Speed = GPIO_SPEED_HIGH;      //高速
        HAL_GPIO_Init(GPIOA, &Y);
        
        Y.Pin   = GPIO_PIN_1;           //PA_1
        Y.Mode  = GPIO_MODE_IT_RISING;  //上升沿触发（中断）
        Y.Pull  = GPIO_PULLDOWN;        //下拉
        Y.Speed = GPIO_SPEED_HIGH;      //高速
        HAL_GPIO_Init(GPIOA, &Y);
        
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);
        HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
        
        HAL_NVIC_EnableIRQ(EXTI1_IRQn);
        HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
}

//中断处理函数__0__
//_________________________________________________________
void EXTI0_IRQHandler(void)
{
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

//中断处理函数__1__
//_________________________________________________________
void EXTI1_IRQHandler(void)
{
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

//中断回调函数
//_________________________________________________________
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
        switch (GPIO_Pin) {
        case GPIO_PIN_0:
                LED_01 = ON;
                break;
        case GPIO_PIN_1:
                LED_02 = OFF;
                break;
        default:
                break;
        }
}
