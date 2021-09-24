#ifndef _COMMON_H
#define _COMMON_H
#include "stm32f10x.h"

/******************************************************************************/
//位绑定区域( SRAM:0x2000_0000 ~ 0x200F_FFFF 片上外设:0x4000_0000 ~ 0x400F_FFFF )
//alias_addr = 0x2200_0000 + ((A - 0x2000_0000)*8 + n)*4
//           = 0x2200_0000 + (A - 0x2000_0000)*32 + n*4
/******************************************************************************/
#define BIT_BAND(addr, bit_num)  *(                                     \
        (volatile unsigned long *)                                      \
                ((addr & 0xF0000000) + 0x02000000 +                     \
                        ((addr & 0x000FFFFF) << 5) + (bit_num << 2))    \
        )
        
#define GPIOA_ODR_A     (GPIOA_BASE + 0x0C)
#define GPIOA_IDR_A     (GPIOA_BASE + 0x08)
#define GPIOB_ODR_B     (GPIOB_BASE + 0x0C)
#define GPIOB_IDR_B     (GPIOB_BASE + 0x08)
#define GPIOC_ODR_C     (GPIOC_BASE + 0x0C)
#define GPIOC_IDR_C     (GPIOC_BASE + 0x08)
#define GPIOD_ODR_D     (GPIOD_BASE + 0x0C)
#define GPIOD_IDR_D     (GPIOD_BASE + 0x08)
#define GPIOE_ODR_E     (GPIOE_BASE + 0x0C)
#define GPIOE_IDR_E     (GPIOE_BASE + 0x08)
#define GPIOF_ODR_F     (GPIOF_BASE + 0x0C)
#define GPIOF_IDR_F     (GPIOF_BASE + 0x08)
#define GPIOG_ODR_G     (GPIOG_BASE + 0x0C)
#define GPIOG_IDR_G     (GPIOG_BASE + 0x08)

#define PA_OUT(n)       BIT_BAND(GPIOA_ODR_A, n)
#define PA_IN(n)        BIT_BAND(GPIOA_IDR_A, n)
#define PB_OUT(n)       BIT_BAND(GPIOB_ODR_B, n)
#define PB_IN(n)        BIT_BAND(GPIOB_IDR_B, n)
#define PC_OUT(n)       BIT_BAND(GPIOC_ODR_C, n)
#define PC_IN(n)        BIT_BAND(GPIOC_IDR_C, n)
#define PD_OUT(n)       BIT_BAND(GPIOD_ODR_D, n)
#define PD_IN(n)        BIT_BAND(GPIOD_IDR_D, n)
#define PE_OUT(n)       BIT_BAND(GPIOE_ODR_E, n)
#define PE_IN(n)        BIT_BAND(GPIOE_IDR_E, n)
#define PF_OUT(n)       BIT_BAND(GPIOF_ODR_F, n)
#define PF_IN(n)        BIT_BAND(GPIOF_IDR_F, n)
#define PG_OUT(n)       BIT_BAND(GPIOG_ODR_G, n)
#define PG_IN(n)        BIT_BAND(GPIOG_IDR_G, n)
/******************************************************************************/


//stm32f10x系统SysTick定时器延时函数
void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif
