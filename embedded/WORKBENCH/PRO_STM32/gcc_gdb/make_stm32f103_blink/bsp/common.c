#include "common.h"


void delay_us(uint32_t nus)
{
	 uint32_t temp;
	 
	 SysTick->LOAD = 9*nus; 
	 SysTick->VAL  = 0X00; 
	 SysTick->CTRL = 0X01;
	 
	 do
	 {
		temp = SysTick->CTRL; 
	 }
	 while((temp&0x01) && (!(temp&(1<<16))));
	 
	 SysTick->CTRL = 0x00; 
	 SysTick->VAL  = 0X00; 
}


void delay_ms(uint32_t nms)
{
	 uint32_t temp;
	 
	 SysTick->LOAD = 9000*nms;
	 SysTick->VAL  = 0X00; 
	 SysTick->CTRL = 0X01;
	 
	 do
	 {
		temp = SysTick->CTRL; 
	 }
	 while((temp&0x01) && (!(temp&(1<<16)))); 
	 
	 SysTick->CTRL = 0x00; 
	 SysTick->VAL  = 0X00; 
}


