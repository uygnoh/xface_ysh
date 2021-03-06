#include "systick.h"



/*
   SysTick 延时1微秒
   设置系统时钟为72MHz, SysTick定时器时钟频率为（72MHz / 8 = 9MHz）
   SysTick是一个“24”位的递减计数器， SysTick->LOAD为自动重装载计数器
*/
void systick_delay_us(uint32_t nus)
{
        uint32_t status;
        SysTick->LOAD = 9 * nus;        //设置自动重装载寄存器的数值
        SysTick->VAL  = 0x00;           //清空计数器，使用“/8”时钟源
        SysTick->CTRL = 0x01;           //打开SysTick定时器
        do {                            //获取SysTick定时器的状态
                status = SysTick->CTRL;
        } while ((status & 0x01) && (!(status & (1<<16))));
        SysTick->CTRL = 0x00;           //关闭SysTick定时器
        SysTick->VAL  = 0x00;           //清空计数器
}



/*
   SysTick 延时1毫秒
   设置系统时钟为72MHz, SysTick定时器时钟频率为（72MHz / 8 = 9MHz）
   SysTick是一个“24”位的递减计数器， SysTick->LOAD为自动重装载计数器
*/
void systick_delay_ms(uint32_t nms)
{
        uint32_t status;
        SysTick->LOAD = 9000 * nms;
        SysTick->VAL  = 0x00;
        SysTick->CTRL = 0x01;
        do {
                status = SysTick->CTRL;
        } while ((status & 0x01) && (!(status & (1<<16))));
        SysTick->CTRL = 0x00;
        SysTick->VAL  = 0X00;
}
