#include "interrupt.h"


/*
  | stm32f10x 设置中断优先级分组和设置相应的中断优先级
  |_______________________________________.
  | GRP  | SCB->AIRC[10:8] |   xIP[7:4]   |           分配结果
  |______|_________________|______________|_____________________________.
  |  0   |       111       |     0:4      |  0位抢占优先级 | 4位响应优先级  |  7
  |  1   |       110       |     1:3      |  1位抢占优先级 | 3位响应优先级  |  6
  |  2   |       101       |     2:2      |  2位抢占优先级 | 2位响应优先级  |  5
  |  3   |       100       |     3:1      |  3位抢占优先级 | 1位响应优先级  |  4
  |  4   |       011       |     4:0      |  4位抢占优先级 | 0位响应优先级  |  3
  |______|_________________|______________|______________________________.
*/
void interrupt_setup(void)
{            
        // 设置Cortex-M中断优先级分组
        //_____________________________________________________________
        // 写入访问钥匙，并设置优先级分组(4位抢占优先级, 0位响应优先级)
        SCB->AIRCR = (0x05FA0000U | 0x00000300U);

        
        // 设置Cortex-M内核异常优先级
        //_____________________________________________________________
        // 设置SysTick的优先级为15，它属于系统异常，所以它的优先级在SCB->SHP里设置
        SCB->SHP[11U] = 0xF0U;
        
        
        // 设置外设中断优先级别
        //_____________________________________________________________
        NVIC->IP[28U] = 0xF0U;          //TIM2, 中断优先级设置为（F = 16）
        
        
        // 设置外设中断使能位
        // 0  % 32 = 0 //
        // 1  % 32 = 1 //
        // 2  % 32 = 2 //
        // 32 % 32 = 0 //
        // 32 % 33 = 1 //
        // 33 % 33 = 1 //
        //_____________________________________________________________
        NVIC->ISER[0U] |= (1UL << 28U); //TIM2_IRQn(28) 中断使能
}



