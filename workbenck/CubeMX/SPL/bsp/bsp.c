#include "bsp.h"
static void clock_setup(void);
static void nvic_setup(void);

/*******************************************************************************
        => STM32F10x__RCC__设置外部高速时钟__72MHz__
*******************************************************************************/
static void clock_setup(void)
{
        RCC_DeInit();                                         //初始化为缺省值
        RCC_HSEConfig(RCC_HSE_ON);                            //使能外部高速时		
        while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);  //等待外部高速时钟稳定
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //enable prefetch buffer
        FLASH_SetLatency(FLASH_Latency_2);                    //flash 2 wait state
        RCC_HCLKConfig(RCC_SYSCLK_Div1);                      //HCLK   = SYSCLK
        RCC_PCLK2Config(RCC_HCLK_Div1);                       //PCLK2  = HCLK
        RCC_PCLK1Config(RCC_HCLK_Div2);                       //PCLK1  = HCLK/2
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //PLLCLK = 8MHz*9 =72MHz
        RCC_PLLCmd(ENABLE);                                   //enable PLLCLK
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);  //wait till  PLLCLK is ready
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //select PPLL as system clock
        while (RCC_GetSYSCLKSource() != 0x08); //wait till PLL is used as system clock source
        //外设时钟开启
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

static void nvic_setup(void)
{
        //NVIC配置
        //4bit都用来表示抢占优先级（0~15）
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

/*******************************************************************************
        => STM32F10x__硬件初始化__
*******************************************************************************/
void hardware_init(void)
{
        nvic_setup();
        clock_setup();
        gpio_setup();
        usart_setup();
}
