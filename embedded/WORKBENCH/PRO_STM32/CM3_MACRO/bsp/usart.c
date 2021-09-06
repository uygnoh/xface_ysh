#include "usart.h"

void afio_swd_setup(void)
{
	/* 使能AFIO时钟， 禁用JTAG, 开启SWD */
	m_afio_clock_enable();
	AFIO->MAPR   &= (uint32_t)(0xF0FFFFFF);
	AFIO->MAPR   |= (uint32_t)(0x02000000);
}


void usart_setup(void)
{
	/* 2位抢占优先级, 2位响应优先级 */
	nvic_set_priority_group();
	/* 设置USART1的先占优先级为4，从优先级为4 */
	/* STM32F10x的中断优先级高4位有效 */
	uint8_t pri_mask = 0xF0;
	uint8_t priority = 0xF0;
	nvic_set_irq_priority(USART1_IRQ_N, (uint8_t)(pri_mask & priority));

	/* 使能外设时钟 */
	m_gpioa_clock_enable();
	m_usart1_clock_enable();
	
	/* usart1—gpio基本配置(uint32_t)类型数据 */
	/* Tx(PA.09)_复用推挽输出(50MHz)   Rx(PA.10)_浮空输入 */
	GPIOA->CRH &= (uint32_t)(0xFFFFF00F);
	GPIOA->CRH |= (uint32_t)(0x000000B0);
	GPIOA->CRH |= (uint32_t)(0x00000400);
	
	/* usart1基本配置(uint16_t)类型数据 */
	USART1->CR1 |= m16_set_bit_13;      /* USART模块使能 */
	USART1->CR1 &= ~m16_set_bit_12;     /* 1个起始位, 8个数据位 */
	USART1->CR2 &= (uint16_t)(0xCFFF); /* 1个停止位(bit13, bit12) */
	USART1->CR1 |= m16_set_bit_03;      /* 发送使能 */
	USART1->CR1 |= m16_set_bit_02;      /* 接收使能 */
	USART1->BRR = 0x0271;               /* 72MHz@115200 */			
}



