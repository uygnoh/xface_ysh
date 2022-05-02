#ifndef __STM32F4_REG_H__
#define __STM32F4_REG_H__

#include "stm32f4xx_hal.h"


/*******************************************************************************
        => STM32F4 外设基地址
*******************************************************************************/
// GPIO
//_____________________________________________________________
#define GPIOA_ADDRESS           0x40020000UL
#define GPIOB_ADDRESS           0x40020400UL     
#define GPIOC_ADDRESS           0x40020800UL
#define GPIOD_ADDRESS           0x40020C00UL
#define GPIOE_ADDRESS           0x40021000UL
#define GPIOF_ADDRESS           0x40021400UL
#define GPIOG_ADDRESS           0x40021800UL
#define GPIOH_ADDRESS           0x40021C00UL
#define GPIOI_ADDRESS           0x40022000UL
#define GPIOJ_ADDRESS           0x40022400UL
#define GPIOK_ADDRESS           0x40022800UL


// RCC SYSCFG CRC
//_____________________________________________________________
#define RCC_ADDRESS             0x40023800UL
#define SYSCFG_ADDRESS          0x40013800UL
#define CRC_ADDRESS             0x40023000UL
#define FLASH_ADDRESS           0x40023C00UL
#define EXTI_ADDRESS            0x40013C00UL


// SPI
//_____________________________________________________________
#define SPI1_ADDRESS            0x40013000UL


// TIM
//_____________________________________________________________
#define TIM1_ADDRESS            0x40010000UL
#define TIM8_ADDRESS            0x40010400UL
#define TIM2_ADDRESS            0x40000000UL
#define TIM3_ADDRESS            0x40000400UL
#define TIM4_ADDRESS            0x40000800UL
#define TIM5_ADDRESS            0x40000C00UL


// USART
//_____________________________________________________________
#define USART1_ADDRESS          0x40011000UL
#define USART2_ADDRESS          0x40004400UL
#define USART3_ADDRESS          0x40004800UL
#define USART4_ADDRESS          0x40004C00UL
#define USART5_ADDRESS          0x40005000UL



/*******************************************************************************
        => STM32F4 通用输入输出端口
*******************************************************************************/
// 00:  Input (reset state)
// 01:  General purpose output mode
// 10:  Alternate function mode
// 11:  Analog mode
#define GPIOA_MODER             (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x00UL))



// 0:   Output push-pull (reset state)
// 1:   Output open-drain
#define GPIOA_OTYPER            (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x04UL))



// 00:  Low speed
// 01:  Medium speed
// 10:  Fast speed
// 11:  High speed
#define GPIOA_OSPEEDR           (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x08UL))



// 00:  No pull-up, pull-down
// 01:  Pull-up
// 10:  Pull-down
// 11:  Reserved
#define GPIOA_PUPDR             (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x0CUL))



// 输入数据寄存器
#define GPIOA_IDR               (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x10UL))
// 输出数据寄存器
#define GPIOA_ODR               (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x14UL))



// 位清除，位设置（高16位用于位清除，低16位用于位设置）
// 写（1）有效， 写（0）无作用
#define GPIOA_BSRR              (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x18UL))



// 端口锁定寄存器
#define GPIOA_LCKR              (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x1CUL))



//      STM32F411RE
//      0000: AF0       // system
//      0001: AF1       // TIM1/TIM2
//      0010: AF2       // TIM3..5
//      0011: AF3       // TIM9..11
//      0100: AF4       // I2C1..3
//      0101: AF5       // SPI1..4
//      0110: AF6       // SPI3..3
//      0111: AF7       // USART1..2
//      1000: AF8       // USART6
//      1001: AF9       // I2C2..3
//      1010: AF10      // OTG_FS
//      1011: AF11      // 
//      1100: AF12      // SDIO
//      1101: AF13      //
//      1110: AF14      //
//      1111: AF15      // EVENTOUT
// GPIO复用功能寄存器的低位（0 ~ 7）
#define GPIOA_AFRL              (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x20UL))
// GPIO复用功能寄存器的高位（8 ~ 15）
#define GPIOA_AFRH              (*(volatile uint32_t *)(GPIOA_ADDRESS + 0x24UL))





/*******************************************************************************
        => STM32F4_时钟系统
*******************************************************************************/
// RCC 时钟控制寄存器
#define RCC_CR                  (*(volatile uint32_t *)(RCC_ADDRESS + 0x00UL))



// RCC PLL configuration register
#define RCC_PLLCFGR             (*(volatile uint32_t *)(RCC_ADDRESS + 0x04UL))



// RCC clock configuration register
#define RCC_CFGR                (*(volatile uint32_t *)(RCC_ADDRESS + 0x08UL))


// RCC clock interrupt register
#define RCC_CIR                 (*(volatile uint32_t *)(RCC_ADDRESS + 0x0CUL))



// 时钟复位寄存器
// RCC AHB1 peripheral reset register
#define RCC_AHB1RSTR            (*(volatile uint32_t *)(RCC_ADDRESS + 0x10UL))
// RCC AHB2 peripheral reset register
#define RCC_AHB2RSTR            (*(volatile uint32_t *)(RCC_ADDRESS + 0x14UL))
// RCC APB1 peripheral reset register
#define RCC_APB1RSTR            (*(volatile uint32_t *)(RCC_ADDRESS + 0x20UL))
// RCC APB2 peripheral reset register
#define RCC_APB2RSTR            (*(volatile uint32_t *)(RCC_ADDRESS + 0x24UL))



// 时钟使能寄存器
// RCC AHB1 peripheral clock enable register
#define RCC_AHB1ENR             (*(volatile uint32_t *)(RCC_ADDRESS + 0x30UL))
// RCC AHB2 peripheral clock enable register
#define RCC_AHB2ENR             (*(volatile uint32_t *)(RCC_ADDRESS + 0x34UL))
// RCC APB1 peripheral clock enable register
#define RCC_APB1ENR             (*(volatile uint32_t *)(RCC_ADDRESS + 0x40UL))
// RCC APB2 peripheral clock enable register
#define RCC_APB2ENR             (*(volatile uint32_t *)(RCC_ADDRESS + 0x44UL))



// 低功耗时钟使能寄存器
// RCC AHB1 peripheral clock enable in low power mode register
#define RCC_AHB1LPENR           (*(volatile uint32_t *)(RCC_ADDRESS + 0x50UL))
// RCC AHB2 peripheral clock enable in low power mode register
#define RCC_AHB2LPENR           (*(volatile uint32_t *)(RCC_ADDRESS + 0x54UL))
// RCC APB1 peripheral clock enable in low power mode register
#define RCC_APB1LPENR           (*(volatile uint32_t *)(RCC_ADDRESS + 0x60UL))
// RCC APB2 peripheral clock enable in low power mode register
#define RCC_APB2LPENR           (*(volatile uint32_t *)(RCC_ADDRESS + 0x64UL))



// RCC Backup domain control register
#define RCC_BDCR                (*(volatile uint32_t *)(RCC_ADDRESS + 0x70UL))
// RCC clock control & status register
#define RCC_CSR                 (*(volatile uint32_t *)(RCC_ADDRESS + 0x74UL))
// RCC spread spectrum clock generation register
#define RCC_SSCGR               (*(volatile uint32_t *)(RCC_ADDRESS + 0x80UL))
// RCC PLLI2S configuration register
#define RCC_PLLI2SCFGR          (*(volatile uint32_t *)(RCC_ADDRESS + 0x84UL))
// RCC Dedicated Clocks Configuration Register
#define RCC_DCKCFGR             (*(volatile uint32_t *)(RCC_ADDRESS + 0x8CUL))



/*******************************************************************************
        => STM32F4_系统配置
*******************************************************************************/
// 存储器重映射寄存器
// SYSCFG memory remap register Bit[1:0]
// 00:  Main Flash memory mapped at 0x0000 0000
// 01:  System Flash memory mapped at 0x0000 0000
// 10:  FSMC Bank1 (NOR/PSRAM 1 and 2) mapped at 0x0000 0000
// 11:  Embedded SRAM (SRAM1) mapped at 0x0000 0000
#define SYSCFG_MEMRMP           (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x00UL))



// SYSCFG peripheral mode configuration register
#define SYSCFG_PMC              (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x04UL))



// 外部中断寄存器配置1
// SYSCFG external interrupt configuration register 1
// Bits 15:0         EXTIx[3:0]:        EXTI x configuration (x = 0 to 3)
//      0000:        PA[x] pin
//      0001:        PB[x] pin
//      0010:        PC[x] pin
//      0011:        PD[x] pin
//      0100:        PE[x] pin
//      0101:        PF[x] pin
//      0110:        PG[x] pin
//      0111:        PH[x] pin
//      1000:        PI[x] pin
#define SYSCFG_EXTICR1          (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x08UL))
// 外部中断寄存器配置2
// SYSCFG external interrupt configuration register 2
// Bits 15:0         EXTIx[3:0]:        EXTI x configuration (x = 4 to 7)
//      0000:        PA[x] pin
//      0001:        PB[x] pin
//      0010:        PC[x] pin
//      0011:        PD[x] pin
//      0100:        PE[x] pin
//      0101:        PF[x] pin
//      0110:        PG[x] pin
//      0111:        PH[x] pin
//      1000:        PI[x] pin
#define SYSCFG_EXTICR2          (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x0CUL))
// 外部中断寄存器配置3
// SYSCFG external interrupt configuration register 3
// Bits 15:0         EXTIx[3:0]:        EXTI x configuration (x = 8 to 11)
//      0000:        PA[x] pin
//      0001:        PB[x] pin
//      0010:        PC[x] pin
//      0011:        PD[x] pin
//      0100:        PE[x] pin
//      0101:        PF[x] pin
//      0110:        PG[x] pin
//      0111:        PH[x] pin
//      1000:        PI[x] pin
#define SYSCFG_EXTICR3          (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x10UL))
// 外部中断寄存器配置4
// SYSCFG external interrupt configuration register 4
// Bits 15:0         EXTIx[3:0]:        EXTI x configuration (x = 12 to 15)
//      0000:        PA[x] pin
//      0001:        PB[x] pin
//      0010:        PC[x] pin
//      0011:        PD[x] pin
//      0100:        PE[x] pin
//      0101:        PF[x] pin
//      0110:        PG[x] pin
//      0111:        PH[x] pin
//      1000:        PI[x] pin
#define SYSCFG_EXTICR4          (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x14UL))



// 补偿单元控制寄存器
// Compensation cell control register ()
#define SYSCFG_CMPCR            (*(volatile uint32_t *)(SYSCFG_ADDRESS + 0x20UL))



/*******************************************************************************
        => STM32F4_外部中断和事件控制器
*******************************************************************************/
// EXTI0[3:0]  bits in the SYSCFG_EXTICR1 register
// EXTI1[3:0]  bits in the SYSCFG_EXTICR1 register
// ...............................................
// EXTI15[3:0] bits in the SYSCFG_EXTICR4 register
// EXTI line 16 is connected to the PVD output
// EXTI line 17 is connected to the RTC Alarm event
// EXTI line 18 is connected to the USB OTG FS Wakeup event
// EXTI line 19 is connected to the Ethernet Wakeup event
// EXTI line 20 is connected to the USB OTG HS (configured in FS) Wakeup event
// EXTI line 21 is connected to the RTC Tamper and TimeStamp events
// EXTI line 22 is connected to the RTC Wakeup event



// 中断屏蔽寄存器
// Interrupt mask register
#define EXTI_IMR                (*(volatile uint32_t *)(EXTI_ADDRESS + 0x00UL))



// 事件屏蔽寄存器
// Event mask register
#define EXTI_EMR                (*(volatile uint32_t *)(EXTI_ADDRESS + 0x04UL))



// 上升沿触发选择寄存器
// Rising trigger selection register
#define EXTI_RTSR               (*(volatile uint32_t *)(EXTI_ADDRESS + 0x08UL))



// 下降沿触发选择寄存器
// Falling trigger selection register
#define EXTI_FTSR               (*(volatile uint32_t *)(EXTI_ADDRESS + 0x0CUL))



// 软件中断事件寄存器
// Software interrupt event register
#define EXTI_SWIER              (*(volatile uint32_t *)(EXTI_ADDRESS + 0x10UL))



// 挂起寄存器
// Pending register
#define EXTI_PR                 (*(volatile uint32_t *)(EXTI_ADDRESS + 0x14UL))




/*******************************************************************************
        => STM32F4_FLASH存储器控制
*******************************************************************************/

// Flash 访问控制寄存器
// Flash access control register
#define FLASH_ACR               (*(volatile uint32_t *)(FLASH_ADDRESS + 0x00UL))



// Flash 密钥寄存器
// Flash key register
// a)   KEY1 = 0x45670123
// b)   KEY2 = 0xCDEF89AB
#define FLASH_KEYR              (*(volatile uint32_t *)(FLASH_ADDRESS + 0x04UL))



// Flash 选项密钥寄存器
// Flash option key register
// a)   OPTKEY1 = 0x08192A3B
// b)   OPTKEY2 = 0x4C5D6E7F
#define FLASH_OPTKEYR           (*(volatile uint32_t *)(FLASH_ADDRESS + 0x08UL))



// Flash 状态寄存器
// Flash status register
#define FLASH_SR                (*(volatile uint32_t *)(FLASH_ADDRESS + 0x0CUL))


// Flash 控制寄存器
// Flash control register
#define FLASH_CR                (*(volatile uint32_t *)(FLASH_ADDRESS + 0x10UL))



// Flash 选项控制寄存器
// Flash option control register
#define FLASH_OPTCR             (*(volatile uint32_t *)(FLASH_ADDRESS + 0x14UL))



/*******************************************************************************
        => STM32F4_CM4内核寄存器
*******************************************************************************/
// 系统滴答定时器
// STCSR SysTick Control and Status Register
#define SYSTICK_CSR             (*(volatile uint32_t *)(0xE000E010UL))
// STRVR SysTick Reload Value Register
#define SYSTICK_RVR             (*(volatile uint32_t *)(0xE000E014UL))
// STCVR SysTick Current Value Register
#define SYSTICK_CVR             (*(volatile uint32_t *)(0xE000E018UL))



// 向量表偏移寄存器
// VTOR Vector Table Offset Register
#define SYS_VTOR                (*(volatile uint32_t *)(0xE000ED08UL))
// AIRCR Application Interrupt and Reset Control Register.
// LDR  R0, =0xE000ED0C         ; 应用程序中断及复位控制寄存器
// LDR  R1, =0x05FA0500         ; 使用优先级组（5）
// STR  R1, [R0]                ; 设置优先级组
#define SYS_AIRCR               (*(volatile uint32_t *)(0xE000ED0CUL))



// STM32F4 系统异常优先级
// SHPR1 System Handler Priority Register 1
// 0xE000_ED18          存储器管理 fault 的优先级
// 0xE000_ED19          总线 fault 的优先级
// 0xE000_ED1A          用法 fault 的优先级
#define SYS_SHPR1               (*(volatile uint32_t *)(0xE000ED18UL))
// SHPR1 System Handler Priority Register 2
// 0xE000_ED1F          SVC 优先级
#define SYS_SHPR2               (*(volatile uint32_t *)(0xE000ED1CUL))
// SHPR1 System Handler Priority Register 3
// 0xE000_ED20          调试监视器的优先级
// 0xE000_ED22          PendSV  的优先级
// 0xE000_ED23          SysTick 的优先级
#define SYS_SHPR3               (*(volatile uint32_t *)(0xE000ED20UL))



// STIR Software Triggered Interrupt Register
// 8:0 INTID W ‐ 影响编号为 INTID 的外部中断,其悬起位被置位。
// 例如,写入 8,则悬起 IRQ #8
#define SYS_STIR               (*(volatile uint32_t *)(0xE000EF00UL))



// NVIC 中断使能寄存器
// Interrupt Set-Enable Registers
// [0xE000E100 - 0xE000E11C]    NVIC_ISER0 - NVIC_ISER7 
#define NVIC_ISER0              (*(volatile uint32_t *)(0xE000E100UL))  // 0   ~ 31
#define NVIC_ISER1              (*(volatile uint32_t *)(0xE000E104UL))  // 32  ~ 63
#define NVIC_ISER2              (*(volatile uint32_t *)(0xE000E108UL))  // 64  ~ 95
#define NVIC_ISER3              (*(volatile uint32_t *)(0xE000E10CUL))  // 96  ~ 127
#define NVIC_ISER4              (*(volatile uint32_t *)(0xE000E110UL))  // 128 ~ 159
#define NVIC_ISER5              (*(volatile uint32_t *)(0xE000E114UL))  // 160 ~ 191
#define NVIC_ISER6              (*(volatile uint32_t *)(0xE000E118UL))  // 192 ~ 223
#define NVIC_ISER7              (*(volatile uint32_t *)(0xE000E11CUL))  // 224 ~ 255

// NVIC 中断清除寄存器
// Interrupt Clear-Enable Registers
// [0xE000E180 - 0xE000E19C]    NVIC_ICER0 - NVIC_ICER7
#define NVIC_ICER0              (*(volatile uint32_t *)(0xE000E180UL))  // 0   ~ 31
#define NVIC_ICER1              (*(volatile uint32_t *)(0xE000E184UL))  // 32  ~ 63
#define NVIC_ICER2              (*(volatile uint32_t *)(0xE000E188UL))  // 64  ~ 95
#define NVIC_ICER3              (*(volatile uint32_t *)(0xE000E18CUL))  // 96  ~ 127
#define NVIC_ICER4              (*(volatile uint32_t *)(0xE000E190UL))  // 128 ~ 159
#define NVIC_ICER5              (*(volatile uint32_t *)(0xE000E194UL))  // 160 ~ 191
#define NVIC_ICER6              (*(volatile uint32_t *)(0xE000E198UL))  // 192 ~ 223
#define NVIC_ICER7              (*(volatile uint32_t *)(0xE000E19CUL))  // 224 ~ 255

// NVIC 中断请求设置寄存器
// Interrupt Set-Pending Registers
// [0xE000E200 - 0xE000E21C]    Interrupt Set-Pending Registers
#define NVIC_ISPR0              (*(volatile uint32_t *)(0xE000E200UL))  // 0   ~ 31
#define NVIC_ISPR1              (*(volatile uint32_t *)(0xE000E204UL))  // 32  ~ 63
#define NVIC_ISPR2              (*(volatile uint32_t *)(0xE000E208UL))  // 64  ~ 95
#define NVIC_ISPR3              (*(volatile uint32_t *)(0xE000E20CUL))  // 96  ~ 127
#define NVIC_ISPR4              (*(volatile uint32_t *)(0xE000E210UL))  // 128 ~ 159
#define NVIC_ISPR5              (*(volatile uint32_t *)(0xE000E214UL))  // 160 ~ 191
#define NVIC_ISPR6              (*(volatile uint32_t *)(0xE000E218UL))  // 192 ~ 223
#define NVIC_ISPR7              (*(volatile uint32_t *)(0xE000E21CUL))  // 224 ~ 255

// NVIC 中断请求清除寄存器
// Interrupt Clear-Pending Registers
// [0xE000E280- 0xE000E29C]     NVIC_ICPR0 - NVIC_ICPR7
#define NVIC_ICPR0              (*(volatile uint32_t *)(0xE000E280UL))  // 0   ~ 31
#define NVIC_ICPR1              (*(volatile uint32_t *)(0xE000E284UL))  // 32  ~ 63
#define NVIC_ICPR2              (*(volatile uint32_t *)(0xE000E288UL))  // 64  ~ 95
#define NVIC_ICPR3              (*(volatile uint32_t *)(0xE000E28CUL))  // 96  ~ 127
#define NVIC_ICPR4              (*(volatile uint32_t *)(0xE000E290UL))  // 128 ~ 159
#define NVIC_ICPR5              (*(volatile uint32_t *)(0xE000E294UL))  // 160 ~ 191
#define NVIC_ICPR6              (*(volatile uint32_t *)(0xE000E298UL))  // 192 ~ 223
#define NVIC_ICPR7              (*(volatile uint32_t *)(0xE000E29CUL))  // 224 ~ 255



// NVIC 中断活动寄存器
// Interrupt Active Bit Register
// [0xE000E300 - 0xE000E31C]    NVIC_IABR0 - NVIC_IABR7



// NVIC 中断优先级寄存器
// Interrupt Priority Register
// [0xE000E400- 0xE000E4EC]     NVIC_IPR0 - NVIC_IPR59
#define NVIC_IPR0               (*(volatile uint32_t *)(0xE000E400UL)   // 0   ~ 3
#define NVIC_IPR1               (*(volatile uint32_t *)(0xE000E404UL)   // 4   ~ 7
#define NVIC_IPR2               (*(volatile uint32_t *)(0xE000E408UL)   // 8   ~ 11
#define NVIC_IPR3               (*(volatile uint32_t *)(0xE000E40CUL)   // 12  ~ 15
#define NVIC_IPR4               (*(volatile uint32_t *)(0xE000E410UL)   // 16  ~ 19
#define NVIC_IPR5               (*(volatile uint32_t *)(0xE000E414UL)   // 20  ~ 23
#define NVIC_IPR6               (*(volatile uint32_t *)(0xE000E418UL)   // 24  ~ 27
#define NVIC_IPR7               (*(volatile uint32_t *)(0xE000E41CUL)   // 28  ~ 31
#define NVIC_IPR8               (*(volatile uint32_t *)(0xE000E420UL)   // 32  ~ 35
#define NVIC_IPR9               (*(volatile uint32_t *)(0xE000E424UL)   // 36  ~ 39
#define NVIC_IPR10              (*(volatile uint32_t *)(0xE000E428UL)   // 40  ~ 43
#define NVIC_IPR11              (*(volatile uint32_t *)(0xE000E42CUL)   // 44  ~ 47
#define NVIC_IPR12              (*(volatile uint32_t *)(0xE000E430UL)   // 48  ~ 51
#define NVIC_IPR13              (*(volatile uint32_t *)(0xE000E434UL)   // 52  ~ 55
#define NVIC_IPR14              (*(volatile uint32_t *)(0xE000E438UL)   // 56  ~ 59
#define NVIC_IPR15              (*(volatile uint32_t *)(0xE000E43CUL)   // 60  ~ 63
#define NVIC_IPR16              (*(volatile uint32_t *)(0xE000E440UL)   // 64  ~ 69
#define NVIC_IPR17              (*(volatile uint32_t *)(0xE000E444UL)   // 70  ~ 73



/*******************************************************************************
        => STM32F4_USART
*******************************************************************************/


#endif
