#include "stm32f10x.h"

int main(void)
{
    rcc_init();
    nvic_init();
    gpio_init();
    tim2_init();
    GPIOC->BSRR = (uint32_t)GPIO_BSRR_BS13;
    while (1)
    {
        //gpio_led_test();
    }

    return 0;
}
