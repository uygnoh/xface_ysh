#include "bsp_led.h"

void led_gpio_init(void)
{
    GPIO_InitTypeDef PORT;
    
    /* GPIOB时钟打开 */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    PORT.Mode   = GPIO_MODE_OUTPUT_PP;      /* 推挽输出模式 */
    PORT.Pin    = GPIO_PIN_0 | GPIO_PIN_1;  /* 引脚配置 */
    PORT.Pull   = GPIO_NOPULL;              /* 上拉，下拉配置 */
    PORT.Speed  = GPIO_SPEED_FREQ_LOW;      /* 速度配置 */
    HAL_GPIO_Init(GPIOB, &PORT);            /* 初始化结构体成员变量 */
}

