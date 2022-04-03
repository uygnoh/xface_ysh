#ifndef __COMMON_H__
#define __COMMON_H__

#include "stm32f10x.h"
#include "m32.h"



/******************************************************************************/
/*                                                                            */
/*                              BitBand                                       */
/*                                                                            */
/******************************************************************************/
#define GPIOA_IDR_A             (GPIOA_BASE + 0x08)
#define GPIOA_ODR_A             (GPIOA_BASE + 0x0C)
#define GPIOB_IDR_B             (GPIOB_BASE + 0x08)
#define GPIOB_ODR_B             (GPIOB_BASE + 0x0C)
#define GPIOC_IDR_C             (GPIOC_BASE + 0x08)
#define GPIOC_ODR_C             (GPIOC_BASE + 0x0C)
#define GPIOD_IDR_D             (GPIOD_BASE + 0x08)
#define GPIOD_ODR_D             (GPIOD_BASE + 0x0C)
#define GPIOE_IDR_E             (GPIOE_BASE + 0x08)
#define GPIOE_ODR_E             (GPIOE_BASE + 0x0C)
#define GPIOF_IDR_F             (GPIOF_BASE + 0x08)
#define GPIOF_ODR_F             (GPIOF_BASE + 0x0C)
#define GPIOG_IDR_G             (GPIOG_BASE + 0x08)
#define GPIOG_ODR_G             (GPIOG_BASE + 0x0C)

#define BIT_BAND(addr, bit_num)  *((volatile unsigned long *)   \
  ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bit_num << 2)))

#define PA_IN(number)           BIT_BAND(GPIOA_IDR_A, number)
#define PA_OUT(number)          BIT_BAND(GPIOA_ODR_A, number)
#define PB_IN(number)           BIT_BAND(GPIOB_IDR_B, number)
#define PB_OUT(number)          BIT_BAND(GPIOB_ODR_B, number)
#define PC_IN(number)           BIT_BAND(GPIOC_IDR_C, number)
#define PC_OUT(number)          BIT_BAND(GPIOC_ODR_C, number)
#define PD_IN(number)           BIT_BAND(GPIOD_IDR_D, number)
#define PD_OUT(number)          BIT_BAND(GPIOD_ODR_D, number)
#define PE_IN(number)           BIT_BAND(GPIOE_IDR_E, number)
#define PE_OUT(number)          BIT_BAND(GPIOE_ODR_E, number)
#define PF_IN(number)           BIT_BAND(GPIOF_IDR_F, number)
#define PF_OUT(number)          BIT_BAND(GPIOF_ODR_F, number)
#define PG_IN(number)           BIT_BAND(GPIOG_IDR_G, number)
#define PG_OUT(number)          BIT_BAND(GPIOG_ODR_G, number)

#endif
