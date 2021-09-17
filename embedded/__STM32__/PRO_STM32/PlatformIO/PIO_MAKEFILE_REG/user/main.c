#include "stm32f10x.h"

int main(void)
{
    rcc_init();
    gpio_init();

    while (1)
    {
        gpio_led_test();
    }

    return 0;
}
