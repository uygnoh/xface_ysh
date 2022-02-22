#include "bsp_usart.h"

void gpio_setup(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        /* USART1_Tx 发送模式配置 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        /* USART1_Rx 接收模式配置 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void usart_setup(void)
{
        USART_InitTypeDef USART_InitStructure;
        USART_DeInit(USART1);
        USART_InitStructure.USART_BaudRate = 115200;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStructure);

        /* Enable USART1 Receive and Transmit interrupts */
        //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

        /* Enable the USART1 */
        USART_Cmd(USART1, ENABLE);
}


void print(uint8_t string[])
{
        uint8_t i = 0;
        uint16_t timeout = 50000;
        while (string[i] != '\0') {                     //如果字符不是（尾0）
                USART1->DR  = string[i++];              //写入要发送的内容
                while ((USART1->SR & 0x40) == 0) {      //等待一个字符发送完成
                        if (timeout-- == 0) {
                                return;
                        }
                }
                timeout = 50000;
        }
}
