#include "clock.h"


/*
   外设时钟设置
*/
void peripheral_clock_setup(void)
{
        // APB1 总线时钟 36MHz
        // ____________________________________________________________
        //RCC->APB1RSTR |=  (BIT_00 );  // 开始复位 TIM2
        //RCC->APB1RSTR &= ~(BIT_00 );  // 停止复位 TIM2
        //RCC->APB1ENR  |=  (BIT_00 );  // 打开时钟 TIM2


        // APB2 总线时钟 72MHz
        // ____________________________________________________________
        RCC->APB2RSTR |=  (BIT_00);     // 开始复位 AFIO
        RCC->APB2RSTR &= ~(BIT_00);     // 停止复位 AFIO
        RCC->APB2ENR  |=  (BIT_00);     // 打开时钟 AFIO
}



/*
  系统时钟由外部高速8MHz晶振 -> 经过PLL倍频到72MHz -> 供给系统
*/
void clock_setup_xtal_8mhz_to_72mhz(void)
{
        __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
        // SYSCLK, HCLK, PCLK2 and PCLK1 配置
        // Enable HSE 
        RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
        // Wait till HSE is ready and if Time out is reached exit
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


                // HCLK = SYSCLK        => AHB总线 72MHz
                RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

                // PCLK2 = HCLK         => APB2总线 72MHz
                RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

                // PCLK1 = HCLK / 2     => APB2总线 36MHz
                RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

  
                // PLL configuration: PLLCLK = HSE * 9 = 72 MHz
                RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | 
                                                   RCC_CFGR_PLLXTPRE |
                                                   RCC_CFGR_PLLMULL));
                RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);


                // Enable PLL
                RCC->CR |= RCC_CR_PLLON;

                // Wait till PLL is ready
                while((RCC->CR & RCC_CR_PLLRDY) == 0) {
                }

                // Select PLL as system clock source
                RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
                RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

                // Wait till PLL is used as system clock source */
                while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) {
                }
                
                // 打开时钟监控系统
                RCC->CR |= BIT_19;
        } else { 
                /* If HSE fails to start-up, the application will have wrong clock 
                configuration. User can add here some code to deal with this error */
        }
}



/*
  将系统时钟设置为内部8MHz—RC振荡器（默认状态）
*/
void clock_setup_hsi_8mhz(void)
{
        // Set HSION bit
        RCC->CR |= (uint32_t)0x00000001;

        // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
        RCC->CFGR &= (uint32_t)0xF0FF0000;


        // Reset HSEON, CSSON and PLLON bits
        RCC->CR &= (uint32_t)0xFEF6FFFF;

        // Reset HSEBYP bit
        // 0: 外部3-25MHz振荡器没有旁路
        // 1: 外部3-25MHz外部晶体振荡器被旁路
        // 如果使用有源晶振作为外部时钟源的话，我们应该配置为HSE旁路模式，而不是HSE晶体模式
        RCC->CR &= (uint32_t)0xFFFBFFFF;

        // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
        RCC->CFGR &= (uint32_t)0xFF80FFFF;


        // Disable all interrupts and clear pending bits
        RCC->CIR = (uint32_t)0x009F0000;
}
