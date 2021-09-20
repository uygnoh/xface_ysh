#include "bsp_led.h"

void key_gpio_init(void)
{
    GPIO_InitTypeDef PORT;
    
    /* GPIO时钟打开 */
    KEY1_GPIO_CLK_ENABLE()
    
    PORT.Mode   = GPIO_MODE_OUTPUT_PP;      /* 推挽输出模式 */
    PORT.Pin    = GPIO_PIN_0;               /* 引脚配置 */
    PORT.Pull   = GPIO_NOPULL;              /* 上拉，下拉配置 */
    PORT.Speed  = GPIO_SPEED_FREQ_LOW;      /* 速度配置 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &PORT);   /* 初始化结构体成员变量 */
    
    PORT.Pin    = GPIO_PIN_6;
    HAL_GPIO_Init(KEY2_GPIO_PORT, &PORT);
}


uint8_t key_scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /* 判断按键是否被按下 */
    if ( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET )
    {
        /* 按键被按下 */
        while ( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET );
        return KEY_ON;
    }
    else
    {
        /* 否则按键未被按下 */
        return KEY_OFF;
    }
}

