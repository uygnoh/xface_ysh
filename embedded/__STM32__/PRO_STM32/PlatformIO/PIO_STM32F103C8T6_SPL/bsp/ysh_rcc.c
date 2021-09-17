#include "ysh_rcc.h"

void rcc_init(void)
{
    /* 开启“AFIO”时钟(辅助功能IO时钟使能) */
    //RCC->APB2ENR |= (uint32_t)RCC_APB2ENR_AFIOEN;

    /* 开启“GPIOC”时钟 */
    RCC->APB2ENR |= (uint32_t)RCC_APB2ENR_IOPCEN;

    /* 开启“通用定时器2”时钟 */
    //RCC->APB1ENR |= (uint32_t)RCC_APB1ENR_TIM2EN;
}



void rcc_default(void)
{
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;
    
    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    /* (MCO: 微控制器时钟输出)   (ADCPRE[1:0]:ADC预分频) */
    /* (PPRE2[2:0]: 高速APB预分频APB2) (PPRE1[2:0]:低速APB预分频APB1)*/
    /* (HPRE [3:0]: AHB预分频) */
    /* (SWS  [1:0]: 系统时钟切换状态) (SW[1:0]:系统时钟切换) */
    RCC->CFGR &= (uint32_t)0xF8FF0000;
    
    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit (0:外部4-16MHz振荡器没有旁路) */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;
    
    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
}



void set_clock_72(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;


    /* Enable HSE */    
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;  
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }  


    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    


        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
          
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;


        /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);

         /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
    }
    else
    { /* If HSE fails to start-up, the application will have wrong clock 
             configuration. User can add here some code to deal with this error */
    }
}
