#ifndef __USART_H__
#define __USART_H__
#include "common.h"

void usart_setup(uint32_t brr);
void uart_send_string(void);
#endif
