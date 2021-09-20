#ifndef __BSP_INIT__
#define __BSP_INIT__
#include "stm32f10x.h"

void rcc_init(void);
void nvic_init(void);
void gpio_init(void);
void tim2_init(void);
#endif
