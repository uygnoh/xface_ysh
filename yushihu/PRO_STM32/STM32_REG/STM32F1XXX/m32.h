#ifndef __M32_H__
#define __M32_H__
#include "stm32f10x.h"
/*
 *      更新日期: 2022/10/06
 */
/******************************************************************************/
/*                                                                            */
/*                              M16                                           */
/*                                                                            */
/******************************************************************************/
#define M16_00                  ((uint16_t)0x0001)
#define M16_01                  ((uint16_t)0x0002)
#define M16_02                  ((uint16_t)0x0004)
#define M16_03                  ((uint16_t)0x0008)
#define M16_04                  ((uint16_t)0x0010)
#define M16_05                  ((uint16_t)0x0020)
#define M16_06                  ((uint16_t)0x0040)
#define M16_07                  ((uint16_t)0x0080)
#define M16_08                  ((uint16_t)0x0100)
#define M16_09                  ((uint16_t)0x0200)
#define M16_10                  ((uint16_t)0x0400)
#define M16_11                  ((uint16_t)0x0800)
#define M16_12                  ((uint16_t)0x1000)
#define M16_13                  ((uint16_t)0x2000)
#define M16_14                  ((uint16_t)0x4000)
#define M16_15                  ((uint16_t)0x8000)
/******************************************************************************/
/*                                                                            */
/*                              BIT32                                         */
/*                                                                            */
/******************************************************************************/
#define BIT_00                  ((uint32_t)0x00000001)
#define BIT_01                  ((uint32_t)0x00000002)
#define BIT_02                  ((uint32_t)0x00000004)
#define BIT_03                  ((uint32_t)0x00000008)
#define BIT_04                  ((uint32_t)0x00000010)
#define BIT_05                  ((uint32_t)0x00000020)
#define BIT_06                  ((uint32_t)0x00000040)
#define BIT_07                  ((uint32_t)0x00000080)
#define BIT_08                  ((uint32_t)0x00000100)
#define BIT_09                  ((uint32_t)0x00000200)
#define BIT_10                  ((uint32_t)0x00000400)
#define BIT_11                  ((uint32_t)0x00000800)
#define BIT_12                  ((uint32_t)0x00001000)
#define BIT_13                  ((uint32_t)0x00002000)
#define BIT_14                  ((uint32_t)0x00004000)
#define BIT_15                  ((uint32_t)0x00008000)
#define BIT_16                  ((uint32_t)0x00010000)
#define BIT_17                  ((uint32_t)0x00020000)
#define BIT_18                  ((uint32_t)0x00040000)
#define BIT_19                  ((uint32_t)0x00080000)
#define BIT_20                  ((uint32_t)0x00100000)
#define BIT_21                  ((uint32_t)0x00200000)
#define BIT_22                  ((uint32_t)0x00400000)
#define BIT_23                  ((uint32_t)0x00800000)
#define BIT_24                  ((uint32_t)0x01000000)
#define BIT_25                  ((uint32_t)0x02000000)
#define BIT_26                  ((uint32_t)0x04000000)
#define BIT_27                  ((uint32_t)0x08000000)
#define BIT_28                  ((uint32_t)0x10000000)
#define BIT_29                  ((uint32_t)0x20000000)
#define BIT_30                  ((uint32_t)0x40000000)
#define BIT_31                  ((uint32_t)0x80000000)
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

#define __PA_IN(number)         BIT_BAND(GPIOA_IDR_A, number)
#define __PA_OUT(number)        BIT_BAND(GPIOA_ODR_A, number)
#define __PB_IN(number)         BIT_BAND(GPIOB_IDR_B, number)
#define __PB_OUT(number)        BIT_BAND(GPIOB_ODR_B, number)
#define __PC_IN(number)         BIT_BAND(GPIOC_IDR_C, number)
#define __PC_OUT(number)        BIT_BAND(GPIOC_ODR_C, number)
#define __PD_IN(number)         BIT_BAND(GPIOD_IDR_D, number)
#define __PD_OUT(number)        BIT_BAND(GPIOD_ODR_D, number)
#define __PE_IN(number)         BIT_BAND(GPIOE_IDR_E, number)
#define __PE_OUT(number)        BIT_BAND(GPIOE_ODR_E, number)
#define __PF_IN(number)         BIT_BAND(GPIOF_IDR_F, number)
#define __PF_OUT(number)        BIT_BAND(GPIOF_ODR_F, number)
#define __PG_IN(number)         BIT_BAND(GPIOG_IDR_G, number)
#define __PG_OUT(number)        BIT_BAND(GPIOG_ODR_G, number)
#endif
