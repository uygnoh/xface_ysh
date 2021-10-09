#include "bsp_usart.h"

void rcc_init(void)
{
	  /* 使能GPIOA时钟 */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA);
	  /* 使能USART1时钟 */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1);
}

void nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 先占优先级4位, 从优先级0位 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	/* 使能USART1全局中断, 配置先占优先级为:15, 从优先级为:0 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure(&NVIC_InitStructure);
}

void gpio_init(void)
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

void usart_init(void)
{
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);
}
