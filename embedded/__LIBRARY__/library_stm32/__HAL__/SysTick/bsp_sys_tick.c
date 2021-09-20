
static __IO uint32_t sys_tick_counter;


/* 
 * 文件位置：stm32f1xx_hal_cortex.c
 * uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb)
 * {
 *      return SysTick_Config(TicksNumb);
 * }
 
 * 文件位置：core_cm3.h
 * __STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks);
 *
 */
void sys_tick_init(void)
{
    /* SystemFrequency / 1000           1ms中断一次
     * SystemFrequency / 100000         10us中断一次
     * SystemFrequency / 1000000        1us中断一次
     */
    if ( HAL_SYSTICK_Config(SystemCoreClock / 1000000) )
    {
        /* Capture error */
        while (1);
    }
}


/*
 * SysTick微秒级延时程序
 * 1us为一个单位
 *
 */
void sys_tick_delay_us(__IO uint32_t nus)
{
    sys_tick_counter = nus;
    while (sys_tick_counter != 0);
}

/*
 * 获取节拍程序
 * 在 SysTick 中断函数 SysTick_Handler()中调用
 *
 */
void sys_tick_decrement(void)
{
    if (sys_tick_counter != 0x00)
        sys_tick_counter--;
}

