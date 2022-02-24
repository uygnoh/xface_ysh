#ifndef __COMMON_H__
#define __COMMON_H__
#include "M32.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"



#include "reg_uart.h"
#include "reg_ds18b20.h"
#include "reg_systick.h"



/*******************************************************************************
        => STM32F103__内部温度传感器__
*******************************************************************************/
void adc1_16_conf(void);
uint16_t get_adc1_16_value(uint8_t channel);
uint16_t get_adc1_16_average(uint8_t channel, uint8_t number);
void get_temperature(void);
#endif
