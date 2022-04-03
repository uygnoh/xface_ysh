#include "gpio.h"

void gpio_setup(void)
{
        RCC->APB2RSTR |=  (BIT_00 + BIT_02;     // 复位（AFIO，GPIO）
        RCC->APB2RSTR &= ~(BIT_00 + BIT_02;     // 停止复位（AFIO，GPIO）
        AFIO_CLOCK_ENABLE();                    // AFIO复用功能开启
        GPIOA_CLOCK_ENABLE();                   // GPIOA时钟开启
        GPIOA->CRH  &= ((uint32_t)0xFFFFF00F); // USART1，清除相关的位
                                                // Tx/PA.09/复用推挽输出_50MHz
	GPIOA->CRH  |= ((uint32_t)0x000004B0); // Rx/PA.10/浮空输入，也可上拉输入
}
