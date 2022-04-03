#ifndef __ADC_H__
#define __ADC_H__
#include "common.h"

void adc_setup(void);
uint16_t get_adc_value(uint8_t channel);
#endif
