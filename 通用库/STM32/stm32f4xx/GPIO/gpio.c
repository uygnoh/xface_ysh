void gpio_setup(void)
{
        // 1: resets IO port A
        RCC_AHB1RSTR    |=  BIT_00;
        RCC_AHB1RSTR    &= ~BIT_00;
        
        // 1: IO port A clock enabled
        RCC_AHB1ENR     |=  BIT_00;
        
        // 00:  Input (reset state)
        // 01:  General purpose output mode
        // 10:  Alternate function mode
        // 11:  Analog mode
        GPIOA_MODER     |=  (uint32_t)(1 << (5  * 2));
        
        // 0:   Output push-pull (reset state)
        // 1:   Output open-drain
        GPIOA_OTYPER    &= ~BIT_05;
}

int main(void)
{
        // 位清除，位设置（高16位用于位清除，低16位用于位设置）
        // 写（1）有效， 写（0）无作用
        GPIOA_BSRR      &= 0xFF2FFFFFUL;
        HAL_Delay(100);
        GPIOA_BSRR      |= 0x00000020UL;
        HAL_Delay(100);
}
