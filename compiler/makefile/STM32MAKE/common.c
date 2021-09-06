#include "common.h"

void delay_us(u32 us)
{
	 u32 temp;
	 SysTick->LOAD = 9*us; 
	 SysTick->VAL  = 0X00; 
	 SysTick->CTRL = 0X01; 
	 do {
		temp = SysTick->CTRL; 
	 } while((temp&0x01) && (!(temp&(1<<16))));
	 SysTick->CTRL = 0x00; 
	 SysTick->VAL  = 0X00; 
}

void delay_ms(u32 ms)
{
	 u32 temp;
	 SysTick->LOAD = 9000*ms;
	 SysTick->VAL  = 0X00; 
	 SysTick->CTRL = 0X01; 
	 do {
		temp = SysTick->CTRL; 
	 } while((temp&0x01) && (!(temp&(1<<16)))); 
	 SysTick->CTRL = 0x00; 
	 SysTick->VAL  = 0X00; 
}

