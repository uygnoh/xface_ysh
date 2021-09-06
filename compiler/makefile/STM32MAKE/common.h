#ifndef __COMMON_H__
#define __COMMON_H__
#include "stm32f10x.h"

void delay_us(u32 nus);
void delay_ms(u32 nms);

/* gpio 端口地址宏定义 */
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

/* gpio 位带绑定算法 */
#define BitBand(Addr,BitNum)  *((volatile unsigned long *)\
	((Addr&0xF0000000)+0x2000000+((Addr&0xFFFFF)<<5)+(BitNum<<2)))

/* gpio 位输入输出定义宏 */
#define pa_out(n) 	BitBand(GPIOA_ODR_A,n)
#define pa_in(n) 	BitBand(GPIOA_IDR_A,n)
#define pb_out(n) 	BitBand(GPIOB_ODR_B,n)
#define pb_in(n) 	BitBand(GPIOB_IDR_B,n)
#define pc_out(n) 	BitBand(GPIOC_ODR_C,n)
#define pc_in(n) 	BitBand(GPIOC_IDR_C,n)
#define pd_out(n) 	BitBand(GPIOD_ODR_D,n)
#define pd_in(n) 	BitBand(GPIOD_IDR_D,n)
#define pe_out(n) 	BitBand(GPIOE_ODR_E,n)
#define pe_in(n) 	BitBand(GPIOE_IDR_E,n)
#define pf_out(n) 	BitBand(GPIOF_ODR_F,n)
#define pf_in(n) 	BitBand(GPIOF_IDR_F,n)
#define pg_out(n) 	BitBand(GPIOG_ODR_G,n)
#define pg_in(n) 	BitBand(GPIOG_IDR_G,n)

#endif


