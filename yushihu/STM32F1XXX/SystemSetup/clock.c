#include "clock.h"


/*******************************************************************************
        => APB | AHB 外设时钟复位
*******************************************************************************/
void apb_ahb_clock_reset(void)
{
        // 外设时钟复位
        // ____________________________________________________






        #if RCC_AHBRSTR_XXX
        // AHB外设时钟复位寄存器(RCC_AHBRSTR) // 复位值 :  0x0000 0000 //
        #endif
        

        #if RCC_APB2RSTR_XXX
        // APB2 外设复位寄存器(RCC_APB2RSTR) // 复位值 :  0x0000 0000 //
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_AFIORST);     // AFIO --->Reset
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_AFIORST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPARST);     // GPIOA
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPARST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPBRST);     // GPIOB
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPBRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPCRST);     // GPIOC
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPCRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPDRST);     // GPIOD
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPDRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPERST);     // GPIOE
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPERST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPFRST);     // GPIOF
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPFRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPGRST);     // GPIOG
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPGRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_ADC1RST);     // ADC1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_ADC1RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_ADC2RST);     // ADC2
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_ADC2RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_TIM1RST);     // TIM1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_TIM1RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_SPI1RST);     // SPI1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_SPI1RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_SPI1RST);     // USART1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_USART1RST);   // ^0
        #endif
        
        
        #if RCC_APB1RSTR_XXX
        // APB1 外设复位寄存器(RCC_APB1RSTR) // 复位值 :   0x0000 0000 //
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART2RST);   // USART2 --->Reset
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART2RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART3RST);   // USART3
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART3RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART4RST);   // USART4
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART4RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART5RST);   // USART5
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART5RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_I2C1RST);     // I2C1
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_I2C1RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_I2C2RST);     // I2C2
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_I2C2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_SPI2RST);     // SPI2
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_SPI2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_SPI3RST);     // SPI3
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_SPI3RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM2RST);     // TIM2
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM3RST);     // TIM3
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM3RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM4RST);     // TIM4
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM4RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM5RST);     // TIM5
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM6RST);     // TIM6
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM6RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM7RST);     // TIM7
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM7RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_CAN1RST);     // CAN1
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_CAN1RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_DACRST);      // DAC
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_DACRST);      // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_BKPRST);      // BKP
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_BKPRST);      // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_PWRRST);      // PWR
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_PWRRST);      // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_WWDGRST);     // WWDG
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_WWDGRST);     // ^0
        #endif   
}
/*******************************************************************************
        => APB | AHB 外设时钟使能
*******************************************************************************/
void apb_ahb_clock_enable(void)
{
        // 外设时钟使能
        // ____________________________________________________
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPAEN);       // GPIOA






        #if RCC_AHBENR_XXX
        // AHB外设时钟使能寄存器(RCC_AHBENR) // 复位值:0x0000 0014 //
        RCC->AHBENR     |=  (RCC_AHBENR_DMA1EN);        // DMA1
        RCC->AHBENR     |=  (RCC_AHBENR_DMA2EN);        // DMA2
        RCC->AHBENR     |=  (RCC_AHBENR_CRCEN);         // CRC
        #endif
        
        #if RCC_APB2ENR_XXX
        // APB2 外设时钟使能寄存器(RCC_APB2ENR) // 复位值: 0x0000 0000 //
        RCC->APB2ENR    |=  (RCC_APB2ENR_AFIOEN);       // AFIO
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPAEN);       // GPIOA
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPBEN);       // GPIOB
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPCEN);       // GPIOC
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPDEN);       // GPIOD
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPEEN);       // GPIOE
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPFEN);       // GPIOF
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPGEN);       // GPIOG
        RCC->APB2ENR    |=  (RCC_APB2ENR_ADC1EN);       // ADC1
        RCC->APB2ENR    |=  (RCC_APB2ENR_ADC2EN);       // ADC2
        RCC->APB2ENR    |=  (RCC_APB2ENR_TIM1EN);       // TIM1
        RCC->APB2ENR    |=  (RCC_APB2ENR_SPI1EN);       // SPI1
        RCC->APB2ENR    |=  (RCC_APB2ENR_USART1EN);     // USART1
        #endif
        
        #if RCC_APB1ENR_XXX
        // APB1 外设时钟使能寄存器(RCC_APB1ENR) // 复位值: 0x0000 0000 //
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART2EN);     // USART2
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART3EN);     // USART3
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART4EN);     // USART4
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART5EN);     // USART5
        RCC->APB1ENR    |=  (RCC_APB1ENR_I2C1EN);       // I2C1
        RCC->APB1ENR    |=  (RCC_APB1ENR_I2C2EN);       // I2C2
        RCC->APB1ENR    |=  (RCC_APB1ENR_SPI2EN);       // SPI2
        RCC->APB1ENR    |=  (RCC_APB1ENR_SPI3EN);       // SPI3
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM2EN);       // TIM2
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM3EN);       // TIM3
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM4EN);       // TIM4
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM5EN);       // TIM5
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM6EN);       // TIM6
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM7EN);       // TIM7
        RCC->APB1ENR    |=  (RCC_APB1ENR_CAN1EN);       // CAN1
        RCC->APB1ENR    |=  (RCC_APB1ENR_CAN2EN);       // CAN2
        RCC->APB1ENR    |=  (RCC_APB1ENR_BKPEN);        // BKP
        RCC->APB1ENR    |=  (RCC_APB1ENR_PWREN);        // PWR
        RCC->APB1ENR    |=  (RCC_APB1ENR_DACEN);        // DAC
        RCC->APB1ENR    |=  (RCC_APB1ENR_WWDGEN);       // WWDG
        #endif
}
/*******************************************************************************
        => 内部高速时钟重新初始化
*******************************************************************************/
void rcc_hsi_setup(void)
{
        // Set HSION bit
        RCC->CR         |= (0x00000001);

        // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
        // (MCO: 微控制器时钟输出)   (ADCPRE[1:0]:ADC预分频)
        // (PPRE2[2:0]: 高速APB预分频APB2) (PPRE1[2:0]:低速APB预分频APB1)
        // (HPRE [3:0]: AHB预分频)
        // (SWS  [1:0]: 系统时钟切换状态) (SW[1:0]:系统时钟切换)
        RCC->CFGR       &= (0xF8FF0000);

        // Reset HSEON, CSSON and PLLON bits
        RCC->CR         &= (0xFEF6FFFF);

        // Reset HSEBYP bit (0:外部4-16MHz振荡器没有旁路)
        RCC->CR         &= (0xFFFBFFFF);

        // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
        RCC->CFGR       &= (0xFF80FFFF);

        // Disable all interrupts and clear pending bits
        RCC->CIR        =  (0x009F0000);
}
/*******************************************************************************
        => 设置系统时钟为72MHz
        => 在外部高速时钟晶体振荡器为[ 8MHz ]的情况下
*******************************************************************************/
int rcc_hse_setup(void)
{
        __IO uint32_t StartUpCounter = 0, HSEStatus = 0;


        // HSE_ON[16]   // 打开外部高速晶体振荡器
        RCC->CR         |= RCC_CR_HSEON;

        // 等待外部高速晶体振荡器稳定， 如果超时， 则退出
        do {
                HSEStatus = RCC->CR & RCC_CR_HSERDY;
                StartUpCounter++;  
        } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
        if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
                HSEStatus = (uint32_t)0x01;
        } else {
                HSEStatus = (uint32_t)0x00;
        }  


        if (HSEStatus == (uint32_t)0x01) {
                // Enable Prefetch Buffer
                FLASH->ACR |= FLASH_ACR_PRFTBE;
                // Flash 2 wait state
                FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
                FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    


                // HPRE[7:4]    // AHB预分频， HCLK 不分频
                RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

                // PPRE1[10:8]  // 低速APB预分频(APB1)， HCLK 2分频
                RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
                
                // PPRE2[13:11] // 高速APB预分频(APB2)， HCLK 不分频
                RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;


                // 配置PLL: PLLCLK = HSE * 9 = 72 MHz
                // ^0   RCC_CFGR_PLLSRC    [16]     
                // ^0   RCC_CFGR_PLLXTPRE  [17]
                // ^0   RCC_CFGR_PLLMULL   [21:18]
                RCC->CFGR &= (0xFFC0FFFF);
                RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);

                // 使能PLL
                RCC->CR |= RCC_CR_PLLON;

                // 等待PLL稳定
                while((RCC->CR & RCC_CR_PLLRDY) == 0) {
                }

                // 选择 PLL 作为系统时钟源
                // ^0           RCC_CFGR_SW[1:0]
                RCC->CFGR &= (0xFFFFFFFC);
                RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

                // Wait till PLL is used as system clock source
                // ^STATUS      SWS[3:2]: 系统时钟切换状态 : 10: PLL输出作为系统时钟
                while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) {
                }
                
                return (80);
        } else { 
                // If HSE fails to start-up, the application will have wrong clock
                // configuration. User can add here some code to deal with this error
                return (-1);
        }
}
