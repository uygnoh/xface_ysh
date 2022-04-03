#include "gpio.h"

void gpio_setup(void)
{
        // 设置 TX-PA.09 | 复用推挽输出-50MHz
        // 设置 RX-PA.10 | 浮空输入，也可以上拉输入
        GPIOA->CRH  &= (0xFFFFF00FU);
	GPIOA->CRH  |= (0x000004B0U);
	
	// ADC1 
        GPIOA->CRL    &= 0XFFFFFF0F;            //PA1__模拟输入
}
