#include "systick.h"

/*******************************************************************************
  函数名称: void delay_us(uint32_t nus)
  输入参数: 无
  输出参数: 无
  函数功能: 延时1us
          设置系统时钟为72MHz, SysTick定时器时钟频率为“72MHz / 8 = 9MHz”
          SysTick是一个“24”位的递减计数器， SysTick->LOAD为自动重装载计数器
          如果SysTick使用外部时钟源： SysTick_Clock = FCLK / 8
******************************* ***********************************************/
// SysTick->CTRL(addr:0xE000_E010)      // SysTick控制及状态寄存器
// ____________________________________________________________
//        ENABLE [0]                    // SysTick 定时器的使能位
//        TICKINT[1]                    // =1   // (SysTick 倒数到0时产生SysTick异常请求)
//                                      // =0   // (数到 0 时无动作)
//      CLKSOURCE[2]                    // =0   // 外部时钟源(STCLK) / 8
//                                      // =1   // 内核时钟(FCLK)
//     COUNTFLAG[16]                    // =1   // SysTick 计数到零
//                                      // 如果读取该位,该位将自动清零
void delay_us(uint32_t nus)
{
        uint32_t status;
        SysTick->LOAD = 9 * nus;        // 设置自动重装载寄存器的数值
        SysTick->VAL  = 0x00;           // 清空计数器，使用“/8”时钟源
        SysTick->CTRL = 0x01;           // 启动SysTick
        // 判断 ENABLE[0] 位， COUNTFLAG[16]位
        do {                            
                status = SysTick->CTRL;
        } while ((status & 0x01) && (!(status & (1 << 16))));
        SysTick->CTRL = 0x00;           // 关闭SysTick定时器
        SysTick->VAL  = 0x00;           // 清空计数器
}
/*******************************************************************************
  函数名称: void delay_ms(uint32_t nms)
  输入参数: 无
  输出参数: 无
  函数功能: 延时1ms
          设置系统时钟为72MHz, SysTick定时器时钟频率为“72MHz / 8 = 9MHz”
          SysTick是一个“24”位的递减计数器， SysTick->LOAD为自动重装载计数器
*******************************************************************************/
void delay_ms(uint32_t nms)
{
        uint32_t status;
        SysTick->LOAD = 9000 * nms;
        SysTick->VAL  = 0x00;
        SysTick->CTRL = 0x01;
        do {
                status = SysTick->CTRL;
        } while ((status & 0x01) && (!(status & (1 << 16))));
        SysTick->CTRL = 0x00;
        SysTick->VAL  = 0X00;
}
