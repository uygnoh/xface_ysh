#ifndef _COMMON_H
#define _COMMON_H
#include "stm32f10x.h"


/* stm32位带操作宏定义文件开始 */
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
#define PA_OUT(n)     BitBand(GPIOA_ODR_A,n)
#define PA_IN(n)      BitBand(GPIOA_IDR_A,n)
#define PB_OUT(n)     BitBand(GPIOB_ODR_B,n)
#define PB_IN(n)      BitBand(GPIOB_IDR_B,n)
#define PC_OUT(n)     BitBand(GPIOC_ODR_C,n)
#define PC_IN(n)      BitBand(GPIOC_IDR_C,n)
#define PD_OUT(n)     BitBand(GPIOD_ODR_D,n)
#define PD_IN(n)      BitBand(GPIOD_IDR_D,n)
#define PE_OUT(n)     BitBand(GPIOE_ODR_E,n)
#define PE_IN(n)      BitBand(GPIOE_IDR_E,n)
#define PF_OUT(n)     BitBand(GPIOF_ODR_F,n)
#define PF_IN(n)      BitBand(GPIOF_IDR_F,n)
#define PG_OUT(n)     BitBand(GPIOG_ODR_G,n)
#define PG_IN(n)      BitBand(GPIOG_IDR_G,n)
/* stm32位带操作宏定义文件结束 */


/* stm32系统SysTick定时器延时函数 */
void delay_ms(u32 nms);
void delay_us(u32 nus);


#endif


