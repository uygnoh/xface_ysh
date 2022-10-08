#include "clock"
#include "interrupt.h"
#include "gpio.h"


int hse_status = -9;

void hardware_initialize(void)
{
        hse_status = rcc_hse_setup();   // 设置外部晶体振荡器
        apb_ahb_clock_reset();          // 复位外设时钟
        apb_ahb_clock_enable();         // 打开外设时钟
                                        //
        nvic_setup();                   // 初始化中断系统
        gpio_setup();                   // 初始化IO系统
}

