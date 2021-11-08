#ifndef __COMMON_H__
#define __COMMON_H__
#include "M32.h"
#include "stm32f1xx_hal.h"

/*******************************************************************************
        => STM32F103__SysTic__
*******************************************************************************/
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
/*******************************************************************************
        => STM32F103__串口1__
*******************************************************************************/
void uart_conf(uint32_t brr);
void uart_send_string(void);
/*******************************************************************************
        => STM32F103__内部温度传感器__
*******************************************************************************/

#endif