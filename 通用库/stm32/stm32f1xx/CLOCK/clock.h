#ifndef __CLOCK_H__
#define __CLOCK_H__
#include "common.h"

/*******************************************************************************
        => STM32F10x_RCC_AHBENR
*******************************************************************************/
#define DMA1_CLOCK_ENABLE()     do {RCC->AHBENR |= BIT_00; } while (0)  // 0_DMA1
#define DMA2_CLOCK_ENABLE()     do {RCC->AHBENR |= BIT_01; } while (0)  // 1_DMA2
#define SRAM_CLOCK_ENABLE()     do {RCC->AHBENR |= BIT_02; } while (0)  // 2_SRAM
#define FLITF_CLOCK_ENABLE()    do {RCC->AHBENR |= BIT_04; } while (0)  // 4_FLITF
#define CRC_CLOCK_ENABLE()      do {RCC->AHBENR |= BIT_06; } while (0)  // 6_CRC
#define SDIO_CLOCK_ENABLE()     do {RCC->AHBENR |= BIT_10; } while (0)  //10_SDIO



/*******************************************************************************
        => STM32F10x_RCC_APB2ENR
*******************************************************************************/
#define AFIO_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_00;} while (0)  // 0_AFIO
#define GPIOA_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_02;} while (0)  // 2_GPIOA
#define GPIOB_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_03;} while (0)  // 3_GPIOB
#define GPIOC_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_04;} while (0)  // 4_GPIOC
#define GPIOD_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_05;} while (0)  // 5_GPIOD
#define GPIOE_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_06;} while (0)  // 6_GPIOE
#define GPIOF_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_07;} while (0)  // 7_GPIOF
#define GPIOG_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_08;} while (0)  // 8_GPIOG
#define ADC1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_09;} while (0)  // 9_ADC1
#define ADC2_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_10;} while (0)  //10_ADC2
#define TIM1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_11;} while (0)  //11_TIM1
#define SPI1_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_12;} while (0)  //12_SPI1
#define TIM8_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_13;} while (0)  //13_TIM8
#define USART1_CLOCK_ENABLE()   do {RCC->APB2ENR |= BIT_14;} while (0)  //14_USART1
#define ADC3_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_15;} while (0)  //15_ADC3
#define TIM9_CLOCK_ENABLE()     do {RCC->APB2ENR |= BIT_19;} while (0)  //19_TIM9
#define TIM10_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_19;} while (0)  //20_TIM10
#define TIM11_CLOCK_ENABLE()    do {RCC->APB2ENR |= BIT_19;} while (0)  //21_TIM11



/*******************************************************************************
        => STM32F10x_RCC_APB1ENR
*******************************************************************************/
#define TIM2_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_00;} while (0)  // 0_TIM2
#define TIM3_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_01;} while (0)  // 1_TIM3
#define TIM4_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_02;} while (0)  // 2_TIM4
#define TIM5_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_03;} while (0)  // 3_TIM5
#define TIM6_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_04;} while (0)  // 4_TIM6
#define TIM7_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_05;} while (0)  // 5_TIM7
#define TIM12_CLOCK_ENABLE()    do {RCC->APB1ENR |= BIT_06;} while (0)  // 6_TIM12
#define TIM13_CLOCK_ENABLE()    do {RCC->APB1ENR |= BIT_07;} while (0)  // 7_TIM13
#define TIM14_CLOCK_ENABLE()    do {RCC->APB1ENR |= BIT_08;} while (0)  // 8_TIM14
#define WWDG_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_11;} while (0)  //11_WWDG
#define SPI2_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_14;} while (0)  //14_SPI2
#define SPI3_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_15;} while (0)  //15_SPI3
#define USART2_CLOCK_ENABLE()   do {RCC->APB1ENR |= BIT_17;} while (0)  //17_USART2
#define USART3_CLOCK_ENABLE()   do {RCC->APB1ENR |= BIT_18;} while (0)  //18_USART3
#define USART4_CLOCK_ENABLE()   do {RCC->APB1ENR |= BIT_19;} while (0)  //19_USART4
#define USART5_CLOCK_ENABLE()   do {RCC->APB1ENR |= BIT_20;} while (0)  //20_USART5
#define I2C1_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_21;} while (0)  //21_I2C1
#define I2C2_CLOCK_ENABLE()     do {RCC->APB1ENR |= BIT_22;} while (0)  //22_I2C2
#define USB_CLOCK_ENABLE()      do {RCC->APB1ENR |= BIT_23;} while (0)  //23_USB
#define CAN_CLOCK_ENABLE()      do {RCC->APB1ENR |= BIT_25;} while (0)  //25_CAN
#define BKP_CLOCK_ENABLE()      do {RCC->APB1ENR |= BIT_27;} while (0)  //27_BKP
#define PWR_CLOCK_ENABLE()      do {RCC->APB1ENR |= BIT_28;} while (0)  //28_PWR
#define DAC_CLOCK_ENABLE()      do {RCC->APB1ENR |= BIT_29;} while (0)  //29_DAC

#endif
