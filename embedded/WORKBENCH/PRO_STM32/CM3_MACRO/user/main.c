#include "stm32f10x.h"

void led_test(void)
{
	m_gpioc_clock_enable();
	/* gpioc_13@50MHz_push-pull */
	GPIOC->CRH &= ((uint32_t)0xFF0FFFFF);
	GPIOC->CRH |= ((uint32_t)0x00300000);
	while (1) {
		m32_pc_out(13) = 0;
		delay_ms(100);
		m32_pc_out(13) = 1;
		delay_ms(100);
	}
}

void debug_usart(void)
{
	uint8_t i;
	char *strs = "Hello World\r\n";
	for (i = 0;  i < 11; i++) {
		while (!(USART1->SR & 0x40))
			USART1->DR = *strs++;
	}
	delay_ms(500);

}

int main(void)
{
	usart_setup();
	debug_usart();
	led_test();
}
