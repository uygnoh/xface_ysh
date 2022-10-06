#include "gpio.h"


void gpio_setup(void)
{
        #if USE_GPIOA
        GPIOA->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8);
        GPIOA->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8);
        #endif
}
