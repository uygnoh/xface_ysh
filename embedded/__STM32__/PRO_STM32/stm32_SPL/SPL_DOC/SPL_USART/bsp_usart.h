#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"
void rcc_init(void);
void nvic_init(void);
void gpio_init(void);
void usart_init(void);
#endif
