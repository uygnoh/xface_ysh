


// Debug Exception and Monitor Control Register.
#define DEM_CR          (*(uint32_t *)0xE000EDFC)
#define TRCENA          (1 << 24)                       // DEMCR的DWT使能位

// The Debug Watchpoint and Trace (DWT) unit
#define DWT_CTRL        (*(uint32_t *)0xE0001000)
#define CYCCNTENA       (1 << 0)                        // DWT的SYCCNT使能位

// Cycle Count register
#define DWT_CYCCNT      (*(uint32_t *)0xE0001004)       // 显示或设置处理器的周期计数值



// 1 先使能DWT外设，这个由另外内核调试寄存器DEMCR的位24控制，写1使能
// 2 使能CYCCNT寄存器之前，先清0。
// 3 使能CYCCNT寄存器，这个由DWT的CYCCNTENA 控制，也就是DWT控制寄存器的位0控制，写1使能
void dwt_init(void)
{
        DEM_CR          |= (uint32_t)TRCENA;
        DWT_CYCCNT      |= (uint32_t)0;
        DWT_CTRL        |= (uint32_t)CYCCNTENA;
}

uint32_t get_dwt_counter(void)
{
        return (uint32_t)(DWT_CYCCNT);
}

#define CYCCNT_US               (SystemCoreClock / (1000*1000))
void dwt_delay_us(uint32_t us)
{
        dwt_init();
        uint32_t tmp = (uint32_t)(DWT_CYCCNT) + us*CYCCNT_US;
        while ((uint32_t)(DWT_CYCCNT) < tmp);
}

void dwt_delay_ms(uint32_t ms)
{
        dwt_delay_us(ms * 1000);
}
