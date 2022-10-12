#include <stdint.h>
#include "stdio.h"
#include "stm32f10x.h"
#include "stm32f10x_conf.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



/*============================================================================*/
/*                              printf                                        */
/*============================================================================*/
int __io_putchar(int ch)
{
        USART_SendData(USART1, (uint8_t) ch);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){
                // Loop
        }
        return ch;
}
void usart_setup(void)
{
        GPIO_InitTypeDef        GPIO_InitStructure;
        USART_InitTypeDef       USART_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        // USART1_TX ---> PA9
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        // USART1_RX ---> PA10
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);


        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        USART_InitStructure.USART_BaudRate = 9600;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStructure);
        // Enable the USART1
        USART_Cmd(USART1, ENABLE);
}



void blink(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        // GPIOA Periph clock enable
        // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        // Configure PA0 and PA2 in output pushpull mode
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        for (;;) {
                // Set   PA0 and PA2
                GPIOA->BSRR = 0x00000005;
                // Reset PA0 and PA2
                GPIOA->BRR  = 0x00000005;
                printf("\n\rUSART Printf Example: retarget the C library printf function to the USART\n\r");
                printf("\n\r-------------------------------------------------------------------------\n\r");
        }
}



/*============================================================================*/
/*                              main()                                        */
/*============================================================================*/
int main(void)
{
        // SystemInit() -> SetSysClock() -> SetSysClockTo72();
        // 系统运行到这里， 时钟配置为（HSE）外部高速晶体振荡器
        // 经过PLL倍频到（72MHz）, APB1 = 72MHz / 2, APB2 = 72MHz / 1
        
        usart_setup();
        blink();
        return (0);
}



/*============================================================================*/
/*                              assert                                        */
/*============================================================================*/
// stm3210x_conf.h
void assert_failed(uint8_t* file, uint32_t line)
{ 
        while (1) {
        }
}
