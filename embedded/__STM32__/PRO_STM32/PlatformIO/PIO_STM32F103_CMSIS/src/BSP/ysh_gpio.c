#include "ysh_gpio.h"

void gpio_init(void)
{
    /* PC_13端口配置 (通用推挽输出, 速度: 50MHz) */
    GPIOC->CRH = (uint32_t)0x00300000;
}


void gpio_led_test(void)
{
    /* 端口位设置/清除寄存器(GPIOx_BSRR) */
    GPIOC->BSRR = (uint32_t)GPIO_BSRR_BS13;
    delay_ms(500);
    GPIOC->BSRR = (uint32_t)GPIO_BSRR_BR13;
    delay_ms(500);
}