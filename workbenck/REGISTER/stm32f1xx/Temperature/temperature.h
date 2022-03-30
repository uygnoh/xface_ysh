#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__


/*******************************************************************************
        => STM32F103__内部温度传感器__
*******************************************************************************/
void adc1_16_conf(void);
uint16_t get_adc1_16_value(uint8_t channel);
uint16_t get_adc1_16_average(uint8_t channel, uint8_t number);
void get_temperature(void);


#endif
