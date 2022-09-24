#include "ysh_systick.h"



/*******************************************************************************
  函数名称: void delay_us(uint32_t nus)
  输入参数: 无
  输出参数: 无
  函数功能: 延时1us
          设置系统时钟为72MHz, SysTick定时器时钟频率为（72MHz / 8 = 9MHz）
          SysTick->LOAD                         SysTick 自动重装载计数器
          SysTick->VAL                          SysTick 当前数值寄存器
                                                SysTick 是一个“24”位的递减计数器
                                                
          SysTick->CTRL.CLKSOURCE[2]  == 0      外部时钟源就是HCLK（AHB总线时钟的1/8）
          SysTick->CTRL.CLKSOURCE[2]  == 1      内核时钟是HCLK时钟
          SysTick->CTRL.COUNTFLAG[16]           计数器状态标志位
          
          SysTick->CTRL.ENABLE[0]     == 0      关闭 SysTick
          SysTick->CTRL.ENABLE[0]     == 1      使能 SysTick
          
*******************************************************************************/
void delay_us(uint32_t nus)
{
        uint32_t status;
        SysTick->LOAD = 9 * nus;        // 设置自动重装载寄存器的数值
        SysTick->VAL  = 0x00;           // 读取时返回当前倒计数的值, 写它则使之清零
        SysTick->CTRL = 0x01;           // 打开SysTick定时器
        do {                            // 获取SysTick定时器的状态
                status = SysTick->CTRL; // 判断第（0 和 16）位
        } while ((status & 0x01) && (!(status & (1 << 16))));
        SysTick->CTRL = 0x00;           // 关闭SysTick定时器
        SysTick->VAL  = 0x00;           // 清空计数器
}
/*******************************************************************************
  函数名称: void delay_us(uint32_t nms)
  输入参数: 无
  输出参数: 无
  函数功能: 延时1ms
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
