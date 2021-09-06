#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"
#define USART1_IRQ_N                    USART1_IRQn

void afio_swd_setup(void);
void usart_setup(void);
#endif
