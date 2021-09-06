#ifndef __M32_H__
#define __M32_H__
#include "stm32f10x.h"

/******************************************************************************/
/*                                                                            */
/*                                M16 | M32                                   */
/*                                                                            */
/******************************************************************************/
#define m16_set_bit_00              ((uint16_t)0x0001)
#define m16_set_bit_01              ((uint16_t)0x0002)
#define m16_set_bit_02              ((uint16_t)0x0004)
#define m16_set_bit_03              ((uint16_t)0x0008)
#define m16_set_bit_04              ((uint16_t)0x0010)
#define m16_set_bit_05              ((uint16_t)0x0020)
#define m16_set_bit_06              ((uint16_t)0x0040)
#define m16_set_bit_07              ((uint16_t)0x0080)
#define m16_set_bit_08              ((uint16_t)0x0100)
#define m16_set_bit_09              ((uint16_t)0x0200)
#define m16_set_bit_10              ((uint16_t)0x0400)
#define m16_set_bit_11              ((uint16_t)0x0800)
#define m16_set_bit_12              ((uint16_t)0x1000)
#define m16_set_bit_13              ((uint16_t)0x2000)
#define m16_set_bit_14              ((uint16_t)0x4000)
#define m16_set_bit_15              ((uint16_t)0x8000)
#define m32_set_bit_00              ((uint32_t)0x00000001)
#define m32_set_bit_01              ((uint32_t)0x00000002)
#define m32_set_bit_02              ((uint32_t)0x00000004)
#define m32_set_bit_03              ((uint32_t)0x00000008)
#define m32_set_bit_04              ((uint32_t)0x00000010)
#define m32_set_bit_05              ((uint32_t)0x00000020)
#define m32_set_bit_06              ((uint32_t)0x00000040)
#define m32_set_bit_07              ((uint32_t)0x00000080)
#define m32_set_bit_08              ((uint32_t)0x00000100)
#define m32_set_bit_09              ((uint32_t)0x00000200)
#define m32_set_bit_10              ((uint32_t)0x00000400)
#define m32_set_bit_11              ((uint32_t)0x00000800)
#define m32_set_bit_12              ((uint32_t)0x00001000)
#define m32_set_bit_13              ((uint32_t)0x00002000)
#define m32_set_bit_14              ((uint32_t)0x00004000)
#define m32_set_bit_15              ((uint32_t)0x00008000)
#define m32_set_bit_16              ((uint32_t)0x00010000)
#define m32_set_bit_17              ((uint32_t)0x00020000)
#define m32_set_bit_18              ((uint32_t)0x00040000)
#define m32_set_bit_19              ((uint32_t)0x00080000)
#define m32_set_bit_20              ((uint32_t)0x00100000)
#define m32_set_bit_21              ((uint32_t)0x00200000)
#define m32_set_bit_22              ((uint32_t)0x00400000)
#define m32_set_bit_23              ((uint32_t)0x00800000)
#define m32_set_bit_24              ((uint32_t)0x01000000)
#define m32_set_bit_25              ((uint32_t)0x02000000)
#define m32_set_bit_26              ((uint32_t)0x04000000)
#define m32_set_bit_27              ((uint32_t)0x08000000)
#define m32_set_bit_28              ((uint32_t)0x10000000)
#define m32_set_bit_29              ((uint32_t)0x20000000)
#define m32_set_bit_30              ((uint32_t)0x40000000)
#define m32_set_bit_31              ((uint32_t)0x80000000)



/******************************************************************************/
/*                                                                            */
/*                     STM32F10X___GPIO___位带操作                             */
/*                                                                            */
/******************************************************************************/
#define  GPIOA_ODR_A                (GPIOA_BASE + 0x0C)
#define  GPIOA_IDR_A                (GPIOA_BASE + 0x08)
#define  GPIOB_ODR_B                (GPIOB_BASE + 0x0C)
#define  GPIOB_IDR_B                (GPIOB_BASE + 0x08)
#define  GPIOC_ODR_C                (GPIOC_BASE + 0x0C)
#define  GPIOC_IDR_C                (GPIOC_BASE + 0x08)
#define  GPIOD_ODR_D                (GPIOD_BASE + 0x0C)
#define  GPIOD_IDR_D                (GPIOD_BASE + 0x08)
#define  GPIOE_ODR_E                (GPIOE_BASE + 0x0C)
#define  GPIOE_IDR_E                (GPIOE_BASE + 0x08)
#define  GPIOF_ODR_F                (GPIOF_BASE + 0x0C)
#define  GPIOF_IDR_F                (GPIOF_BASE + 0x08)
#define  GPIOG_ODR_G                (GPIOG_BASE + 0x0C)
#define  GPIOG_IDR_G                (GPIOG_BASE + 0x08)
#define BitBand(Addr, BitNum)  *((volatile unsigned long *)\
    ((Addr & 0xF0000000) + 0x2000000 + ((Addr & 0xFFFFF) << 5) + (BitNum << 2)))
#define m32_pa_in(n)                 BitBand(GPIOA_IDR_A, n)
#define m32_pa_out(n)                BitBand(GPIOA_ODR_A, n)
#define m32_pb_in(n)                 BitBand(GPIOB_IDR_B, n)
#define m32_pb_out(n)                BitBand(GPIOB_ODR_B, n)
#define m32_pc_in(n)                 BitBand(GPIOC_IDR_C, n)
#define m32_pc_out(n)                BitBand(GPIOC_ODR_C, n)
#define m32_pd_in(n)                 BitBand(GPIOD_IDR_D, n)
#define m32_pd_out(n)                BitBand(GPIOD_ODR_D, n)
#define m32_pe_in(n)                 BitBand(GPIOE_IDR_E, n)
#define m32_pe_out(n)                BitBand(GPIOE_ODR_E, n)
#define m32_pf_in(n)                 BitBand(GPIOF_IDR_F, n)
#define m32_pf_out(n)                BitBand(GPIOF_ODR_F, n)
#define m32_pg_in(n)                 BitBand(GPIOG_IDR_G, n)
#define m32_pg_out(n)                BitBand(GPIOG_ODR_G, n)



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
INPUT
INPUT_PULLUP
INPUT_PULLDOWN
INPUT_ANALOG
INPUT_PULLUP_GPIO_ODR_0

OUTPUT_PUSHPULL
OUTPUT_OPENDRAIN
ALTERNATE_PUSHPULL
ALTERNATE_OPENDRAIN
OUTPUT_SPEED_2MHZ
OUTPUT_SPEED_10MHZ
OUTPUT_SPEED_50MHZ

config_gpio_mode();
gpio_set(GPIOA, PIN_0);
/******************************************************************************/
/*                                                                            */
/*                     AHB外设时钟使能寄存器___RCC_AHBENR                        */
/*                                                                            */
/******************************************************************************/
#define m_dma1_clock_enable()     do {RCC->AHBENR |= m32_set_bit_00;} while (0)
#define m_dma2_clock_enable()     do {RCC->AHBENR |= m32_set_bit_01;} while (0)



/******************************************************************************/
/*                                                                            */
/*                     APB2外设时钟使能寄存器___RCC_APB2ENR                      */
/*                                                                            */
/******************************************************************************/
#define m_afio_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_00;} while (0)
#define m_gpioa_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_02;} while (0)
#define m_gpiob_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_03;} while (0)
#define m_gpioc_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_04;} while (0)
#define m_gpiod_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_05;} while (0)
#define m_gpioe_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_06;} while (0)
#define m_gpiof_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_07;} while (0)
#define m_gpiog_clock_enable()    do {RCC->APB2ENR |= m32_set_bit_08;} while (0)
#define m_adc1_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_09;} while (0)
#define m_adc2_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_10;} while (0)
#define m_tim1_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_11;} while (0)
#define m_spi1_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_12;} while (0)
#define m_tim8_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_13;} while (0)
#define m_usart1_clock_enable()   do {RCC->APB2ENR |= m32_set_bit_14;} while (0)
#define m_adc3_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_15;} while (0)



/******************************************************************************/
/*                                                                            */
/*                     APB1外设时钟使能寄存器___RCC_APB1ENR                      */
/*                                                                            */
/******************************************************************************/
#define m_tim2_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_00;} while (0)
#define m_tim3_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_01;} while (0)
#define m_tim4_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_02;} while (0)
#define m_tim5_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_03;} while (0)
#define m_tim6_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_04;} while (0)
#define m_tim7_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_05;} while (0)
#define m_wwdg_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_11;} while (0)
#define m_spi2_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_14;} while (0)
#define m_spi3_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_15;} while (0)
#define m_usart2_clock_enable()   do {RCC->APB2ENR |= m32_set_bit_17;} while (0)
#define m_usart3_clock_enable()   do {RCC->APB2ENR |= m32_set_bit_18;} while (0)
#define m_usart4_clock_enable()   do {RCC->APB2ENR |= m32_set_bit_19;} while (0)
#define m_usart5_clock_enable()   do {RCC->APB2ENR |= m32_set_bit_20;} while (0)
#define m_i2c1_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_21;} while (0)
#define m_i2c2_clock_enable()     do {RCC->APB2ENR |= m32_set_bit_22;} while (0)
#define m_usb_clock_enable()      do {RCC->APB2ENR |= m32_set_bit_23;} while (0)
#define m_can_clock_enable()      do {RCC->APB2ENR |= m32_set_bit_25;} while (0)
#define m_bkp_clock_enable()      do {RCC->APB2ENR |= m32_set_bit_27;} while (0)
#define m_pwr_clock_enable()      do {RCC->APB2ENR |= m32_set_bit_28;} while (0)
#define m_dac_clock_enable()      do {RCC->APB2ENR |= m32_set_bit_29;} while (0)


/******************************************************************************/
/*                                                                            */
/*                               GPIO                                         */
/*                                                                            */
/******************************************************************************/



#endif
