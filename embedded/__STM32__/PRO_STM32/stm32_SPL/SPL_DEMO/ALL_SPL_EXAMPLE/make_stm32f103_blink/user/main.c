#include "stm32f10x_conf.h"

/**
 * @brief  led_pc13_test
 * @param  None
 * @retval None
 */
void test(void);
void test(void)
{
    uint8_t i;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin      = GPIO_Pin_13;
    gpio_init.GPIO_Speed    = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode     = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &gpio_init);
    
    for (i = 0; i < 9; i++)
    {
        pcout(13) = 0;
        delay_ms(1000);
        pcout(13) = 1;
		delay_ms(1000);
    }
    
}

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin      = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
    gpio_init.GPIO_Speed    = GPIO_Speed_2MHz;
    gpio_init.GPIO_Mode     = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &gpio_init);

    oled_init();
    
    while(1)
    {
        test();
        oled_clear();
        delay_ms(500);
        oled_full();
        delay_ms(500);
    }
    
    return 0;
}




