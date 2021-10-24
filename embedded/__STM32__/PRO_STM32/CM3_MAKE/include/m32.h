#ifndef __M32_H__
#define __M32_H__
#include "stm32f10x.h"
/******************************************************************************/
/*                                                                            */
/*                               M32                                          */
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
/*                     STM32F10x___GPIO___位带操作                             */
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
#define BIT_BAND(ADDR, X)  *((volatile unsigned long *)\
    ((ADDR & 0xF0000000) + 0x02000000 + ((ADDR & 0xFFFFF) << 5) + (X << 2)))
#define PA_IN(Y)                BIT_BAND(GPIOA_IDR_A, Y)
#define PA_OUT(Y)               BIT_BAND(GPIOA_ODR_A, Y)
#define PB_IN(Y)                BIT_BAND(GPIOB_IDR_B, Y)
#define PB_OUT(Y)               BIT_BAND(GPIOB_ODR_B, Y)
#define PC_IN(Y)                BIT_BAND(GPIOC_IDR_C, Y)
#define PC_OUT(Y)               BIT_BAND(GPIOC_ODR_C, Y)
#define PD_IN(Y)                BIT_BAND(GPIOD_IDR_D, Y)
#define PD_OUT(Y)               BIT_BAND(GPIOD_ODR_D, Y)
#define PE_IN(Y)                BIT_BAND(GPIOE_IDR_E, Y)
#define PE_OUT(Y)               BIT_BAND(GPIOE_ODR_E, Y)
#define PF_IN(Y)                BIT_BAND(GPIOF_IDR_F, Y)
#define PF_OUT(Y)               BIT_BAND(GPIOF_ODR_F, Y)
#define PG_IN(Y)                BIT_BAND(GPIOG_IDR_G, Y)
#define PG_OUT(Y)               BIT_BAND(GPIOG_ODR_G, Y)
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
/*                               GPIO                                         */
/*                                                                            */
/******************************************************************************/


#endif
