#ifndef __BSP_USART_H__
#define __BSP_USART_H__
#include "stm32f10x.h"
void gpio_setup(void);
void usart_setup(void);
void print(uint8_t string[]);
#endif
