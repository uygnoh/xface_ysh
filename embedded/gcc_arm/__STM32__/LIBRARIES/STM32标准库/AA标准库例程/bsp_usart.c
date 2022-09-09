#include "bsp_usart.h"
//数据发送过程
	1. 设置 USART_CR1寄存器中 UE位置位 来激活USART
	2. 设置 USART_CR1寄存器中 的M位    来定义字长
	3. 设置 USART_CR2寄存器中 编写停止位位数
	*  如果采用多缓冲器通信，配置 USART_CR3寄存器中的 DMA使能位(DMAT)
	4. 设置 USART_CR1中的 TE位，发送一个空闲帧作为第一次数据的发送
	5. 设置 USART_BRR寄存器，设定要求的波特率
	6. 把发送的数据写进 USART_DR寄存器 (此动作自动清除 TXE位)。
	   -----在只有一个缓冲器的情况下，对每个待发送的数据重复此步骤
//数据接收过程
	1. 设置 USART_CR1寄存器中 UE位置位 来激活USART
	2. 设置 USART_CR1寄存器中 的M位    来定义字长
	3. 设置 USART_CR2寄存器中 编写停止位位数
	*  如果采用多缓冲器通信，配置 USART_CR3寄存器中的 DMA使能位(DMAT)
	4. 设置 USART_BRR寄存器，设定要求的波特率
	5. 设置 USART_CR1中的 RE位，激活接收器，使他开始寻找起始位
//当一个字符被接收时
	RXNE位被置位。它表明移位寄存器的内容被转移到 RDR.
	RXNEIE位被置位。则产生中断信号.
	在接收期间如果检测到帧错误，噪音或溢出错误，错误标志将被置起.
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
