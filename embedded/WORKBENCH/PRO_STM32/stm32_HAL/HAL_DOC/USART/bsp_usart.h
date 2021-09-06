#ifndef __BSP_USART_H__
#define __BSP_USART_H__
#include "stm32f1xx.h"

void UART1_Config(void);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);

#endif


