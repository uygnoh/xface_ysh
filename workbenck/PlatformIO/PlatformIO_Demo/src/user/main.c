#include "stm32f10x.h"

void led_blink(void)
{
        uint8_t i;
        GPIOA_CLOCK_ENABLE();                   //打开GPIOA时钟
        GPIOA->CRL  &= (uint32_t)(0xFFFFF0FF);  //清除相关的位
	GPIOA->CRL  |= (uint32_t)(0xFFFFF3FF);  //PA2__推挽输出
        for (i = 0; i < 6; i++) {               //循环 6 次
                GPIOA->ODR |= BIT_02;
                __delay_ms(500);
                GPIOA->ODR &= ~BIT_02;
                __delay_ms(500);
        }
}

int main(void)
{
        uint8_t i;
        led_blink();
        usart1_setup();
        uint8_t tx_buf[]  = "hello, world!\n";
        uint8_t tx_buf1[] = "-------------\n";
        for (i = 0; i < 255; i++) {
                usart_send_string(tx_buf1);
                usart_send_string(tx_buf);
        }
        GPIOA->ODR |= BIT_02;
        return 0;
}
