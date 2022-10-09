#include "ysh_init.h"


int hse_status = 0;     // 设置外部高速晶体振荡器返回码

void hardware_initialize(void)
{
                                        // 第一步: 时钟系统设置
//     hse_status = rcc_hse_setup();   // 设置外部晶体振荡器
        apb_ahb_clock_reset();          // 复位外设时钟
        apb_ahb_clock_enable();         // 打开外设时钟
                                        //
        nvic_setup();                   // 第二步: 中断系统设置
                                        //
        gpio_setup();                   // 第三步: IO系统设置
}

