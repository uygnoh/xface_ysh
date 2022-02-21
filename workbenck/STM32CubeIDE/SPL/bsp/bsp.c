#include "bsp.h"

void bsp_init(void)
{
        //4bit都用来表示抢占优先级（0~15）
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
        //led_setup();
        //usart_setup();
}
