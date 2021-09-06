#ifndef _COMMON_H
#define _COMMON_H
#include "stm32f10x.h"



#define  GPIOA_ODR_A  (GPIOA_BASE + 0x0C)
#define  GPIOA_IDR_A  (GPIOA_BASE + 0x08)
#define  GPIOB_ODR_B  (GPIOB_BASE + 0x0C)
#define  GPIOB_IDR_B  (GPIOB_BASE + 0x08)
#define  GPIOC_ODR_C  (GPIOC_BASE + 0x0C)
#define  GPIOC_IDR_C  (GPIOC_BASE + 0x08)
#define  GPIOD_ODR_D  (GPIOD_BASE + 0x0C)
#define  GPIOD_IDR_D  (GPIOD_BASE + 0x08)
#define  GPIOE_ODR_E  (GPIOE_BASE + 0x0C)
#define  GPIOE_IDR_E  (GPIOE_BASE + 0x08)
#define  GPIOF_ODR_F  (GPIOF_BASE + 0x0C)
#define  GPIOF_IDR_F  (GPIOF_BASE + 0x08)
#define  GPIOG_ODR_G  (GPIOG_BASE + 0x0C)
#define  GPIOG_IDR_G  (GPIOG_BASE + 0x08)


#define BitBand(Addr,BitNum)  *((volatile unsigned long *)\
	((Addr&0xF0000000)+0x2000000+((Addr&0xFFFFF)<<5)+(BitNum<<2)))

#define paout(n) 	BitBand(GPIOA_ODR_A,n)
#define pain(n) 	BitBand(GPIOA_IDR_A,n)
#define pbout(n) 	BitBand(GPIOB_ODR_B,n)
#define pbin(n) 	BitBand(GPIOB_IDR_B,n)
#define pcout(n) 	BitBand(GPIOC_ODR_C,n)
#define pcin(n) 	BitBand(GPIOC_IDR_C,n)
#define pdout(n) 	BitBand(GPIOD_ODR_D,n)
#define pdin(n) 	BitBand(GPIOD_IDR_D,n)
#define peout(n) 	BitBand(GPIOE_ODR_E,n)
#define pein(n) 	BitBand(GPIOE_IDR_E,n)
#define pfout(n) 	BitBand(GPIOF_ODR_F,n)
#define pfin(n) 	BitBand(GPIOF_IDR_F,n)
#define pgout(n) 	BitBand(GPIOG_ODR_G,n)
#define pgin(n) 	BitBand(GPIOG_IDR_G,n)


void delay_ms(u32 nms);
void delay_ms(u32 nms);


#endif 
