#ifndef __BSP_UART_H__
#define __BSP_UART_H__
#include "stm32f1xx_hal.h"

#define LED_01()                HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2)
#define TX_BUFFER_SIZE          (COUNTOF(tx_buffer) - 1)
#define RX_BUFFER_SIZE          TX_BUFFER_SIZE
#define COUNTOF(__BUFFER__)     (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))


void test(void);

#endif
