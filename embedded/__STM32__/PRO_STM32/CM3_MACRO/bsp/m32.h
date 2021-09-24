#ifndef __M32_H__
#define __M32_H__
#include "stm32f10x.h"
/******************************************************************************/
/*                                                                            */
/*                                M16 | M32                                   */
/*                                                                            */
/******************************************************************************/
#define M16_00              ((uint16_t)0x0001)
#define M16_01              ((uint16_t)0x0002)
#define M16_02              ((uint16_t)0x0004)
#define M16_03              ((uint16_t)0x0008)
#define M16_04              ((uint16_t)0x0010)
#define M16_05              ((uint16_t)0x0020)
#define M16_06              ((uint16_t)0x0040)
#define M16_07              ((uint16_t)0x0080)
#define M16_08              ((uint16_t)0x0100)
#define M16_09              ((uint16_t)0x0200)
#define M16_10              ((uint16_t)0x0400)
#define M16_11              ((uint16_t)0x0800)
#define M16_12              ((uint16_t)0x1000)
#define M16_13              ((uint16_t)0x2000)
#define M16_14              ((uint16_t)0x4000)
#define M16_15              ((uint16_t)0x8000)
#define M32_00              ((uint32_t)0x00000001)
#define M32_01              ((uint32_t)0x00000002)
#define M32_02              ((uint32_t)0x00000004)
#define M32_03              ((uint32_t)0x00000008)
#define M32_04              ((uint32_t)0x00000010)
#define M32_05              ((uint32_t)0x00000020)
#define M32_06              ((uint32_t)0x00000040)
#define M32_07              ((uint32_t)0x00000080)
#define M32_08              ((uint32_t)0x00000100)
#define M32_09              ((uint32_t)0x00000200)
#define M32_10              ((uint32_t)0x00000400)
#define M32_11              ((uint32_t)0x00000800)
#define M32_12              ((uint32_t)0x00001000)
#define M32_13              ((uint32_t)0x00002000)
#define M32_14              ((uint32_t)0x00004000)
#define M32_15              ((uint32_t)0x00008000)
#define M32_16              ((uint32_t)0x00010000)
#define M32_17              ((uint32_t)0x00020000)
#define M32_18              ((uint32_t)0x00040000)
#define M32_19              ((uint32_t)0x00080000)
#define M32_20              ((uint32_t)0x00100000)
#define M32_21              ((uint32_t)0x00200000)
#define M32_22              ((uint32_t)0x00400000)
#define M32_23              ((uint32_t)0x00800000)
#define M32_24              ((uint32_t)0x01000000)
#define M32_25              ((uint32_t)0x02000000)
#define M32_26              ((uint32_t)0x04000000)
#define M32_27              ((uint32_t)0x08000000)
#define M32_28              ((uint32_t)0x10000000)
#define M32_29              ((uint32_t)0x20000000)
#define M32_30              ((uint32_t)0x40000000)
#define M32_31              ((uint32_t)0x80000000)
/******************************************************************************/
/*                                                                            */
/*                     STM32F10X___GPIO___位带操作                             */
/*                                                                            */
/******************************************************************************/
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
#define BIT_BAND(Addr, BitNum)  *((volatile unsigned long *)\
    ((Addr & 0xF0000000) + 0x2000000 + ((Addr & 0xFFFFF) << 5) + (BitNum << 2)))
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
/*                                                                            */
/*                                GPIO_MODE                                   */
/*                                                                            */
/******************************************************************************/
/* ____________________________________________________________________________
                //GPIOx_CRL {CNFy[1:0] MODEx[1:0]} x|y 0~7 
                //GPIOx_CRH {CNFy[1:0] MODEx[1:0]} x|y 8~15
                0 0 0 0     (0)模拟输入
                0 1 0 0     (4)浮空输入(复位后的状态) 
                1 0 0 0     (8)下拉输入(PxODR = 0)
                1 0 0 0     (8)上拉输入(PxODR = 1)
                1 1 0 0     (C)保留

                0 0 0 1     (1)推挽输出(10MHz)
                0 0 1 0     (2)推挽输出(02MHz)
                0 0 1 1     (3)推挽输出(50MHz)
                0 1 0 1     (5)开漏输出(10MHz)
                0 1 1 0     (6)开漏输出(02MHz)
                0 1 1 1     (7)开漏输出(02MHz)
                1 0 0 1     (9)复用推挽输出(10MHz)
                1 0 1 0     (A)复用推挽输出(02MHz)
                1 0 1 1     (B)复用推挽输出(50MHz)
                1 1 0 1     (D)复用开漏输出(10MHz)
                1 1 1 0     (E)复用开漏输出(02MHz)
                1 1 1 1     (F)复用开漏输出(50MHz)
____________________________________________________________________________ */
/******************************************************************************/
/*                                                                            */
/*                     AHB外设时钟使能寄存器___RCC_AHBENR                        */
/*                                                                            */
/******************************************************************************/
#define DMA1_CLOCK_ENABLE()     do {RCC->AHBENR |= BIT_00;} while (0)
#define DMA2_CLOCK_ENABLE()     do {RCC->AHBENR |= BIT_01;} while (0)
/******************************************************************************/
/*                                                                            */
/*                     APB2外设时钟使能寄存器___RCC_APB2ENR                      */
/*                                                                            */
/******************************************************************************/
#define AFIO_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_00;} while (0)
#define GPIOA_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_02;} while (0)
#define GPIOB_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_03;} while (0)
#define GPIOC_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_04;} while (0)
#define GPIOD_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_05;} while (0)
#define GPIOE_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_06;} while (0)
#define GPIOF_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_07;} while (0)
#define GPIOG_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_08;} while (0)
#define ADC1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_09;} while (0)
#define ADC2_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_10;} while (0)
#define TIM1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_11;} while (0)
#define SPI1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_12;} while (0)
#define TIM8_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_13;} while (0)
#define USART1_CLOCK_ENABLE()   do {RCC->APB2ENR |= BIT_14;} while (0)
#define ADC3_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_15;} while (0)
/******************************************************************************/
/*                                                                            */
/*                     APB1外设时钟使能寄存器___RCC_APB1ENR                      */
/*                                                                            */
/******************************************************************************/
#define TIM2_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_00;} while (0)
#define TIM3_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_01;} while (0)
#define TIM4_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_02;} while (0)
#define TIM5_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_03;} while (0)
#define TIM6_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_04;} while (0)
#define TIM7_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_05;} while (0)
#define WWDG_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_11;} while (0)
#define SPI2_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_14;} while (0)
#define SPI3_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_15;} while (0)
#define USART2_CLOCK_ENABLE()   do {RCC->APB2ENR |= BIT_17;} while (0)
#define USART3_CLOCK_ENABLE()   do {RCC->APB2ENR |= BIT_18;} while (0)
#define USART4_CLOCK_ENABLE()   do {RCC->APB2ENR |= BIT_19;} while (0)
#define USART5_CLOCK_ENABLE()   do {RCC->APB2ENR |= BIT_20;} while (0)
#define I2C1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_21;} while (0)
#define I2C2_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_22;} while (0)
#define USB_CLOCK_ENABLE()      do {RCC->APB2ENR |= BIT_23;} while (0)
#define CAn_CLOCK_ENABLE()      do {RCC->APB2ENR |= BIT_25;} while (0)
#define BKP_CLOCK_ENABLE()      do {RCC->APB2ENR |= BIT_27;} while (0)
#define PWR_CLOCK_ENABLE()      do {RCC->APB2ENR |= BIT_28;} while (0)
#define DAC_CLOCK_ENABLE()      do {RCC->APB2ENR |= BIT_29;} while (0)
/******************************************************************************/
/*                                                                            */
/*                                                                           */
/*                                                                            */
/******************************************************************************/
#endif
