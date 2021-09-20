#include "bsp_exti.h"

void exti_key_config(void)
{
    GPIO_InitTypeDef PORT;
    
    /* 打开按键GPIO的时钟 */
    KEY1_INT_GPIO_CLK_ENABLE();
    KEY2_INT_GPIO_CLK_ENABLE();
    
    
    PORT.Pin  = KEY1_INT_GPIO_PIN;      /* 选择按键1的引脚 */
    PORT.Mode = GPIO_MODE_IT_RISING     /* 设置引脚为输入模式，中断上升沿 */
    PORT.Pull = GPIO_NOPULL;            /* 设置引脚不上拉也不下拉 */
    
    /* 使用上面的结构体初始化按键 */
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &PORT);
    /* 配置 EXTI 中断源到KEY1引脚， 配置中断优先级 */
    HAL_NVIC_SetPriority(KEY1_INT_EXTI_IRQ, 0, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY1_INT_EXTI_IRQ);
    
    /* 选择按键2的引脚 */
    PORT.Pin  = KEY2_INT_GPIO_PIN;      
    /* 使用上面的结构体初始化按键 */
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &PORT);
    /* 配置 EXTI 中断源到KEY1引脚， 配置中断优先级 */
    HAL_NVIC_SetPriority(KEY2_INT_EXTI_IRQ, 0, 0);
    /* 使能中断 */
    HAL_NVIC_EnableIRQ(KEY2_INT_EXTI_IRQ);
}

