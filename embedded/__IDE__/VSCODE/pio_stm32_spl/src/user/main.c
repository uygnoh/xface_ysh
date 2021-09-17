#include "stm32f10x.h"


/* 
 * @brief stm32f103c8t6, PC13端口测试
 * @param  None
 * @retval None
 */
void port_pc13_test(void)
{
    uint8_t i;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef PORT;
    PORT.GPIO_Pin      = GPIO_Pin_13;
    PORT.GPIO_Speed    = GPIO_Speed_50MHz;
    PORT.GPIO_Mode     = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &PORT);

    for (i = 0; i < 9; i++)
    {
        PC_OUT(13) = 0;
        delay_ms(1000);
        PC_OUT(13) = 1;
        delay_ms(1000);
    }

}

int main(void)
{
    port_pc13_test();
    while (1) 
    {
    }
    return 0;
}

