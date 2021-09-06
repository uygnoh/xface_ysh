#include "bsp_usart.h"

UART_HandleTypeDef uart_handle;


void UART1_Config(void)
{
    uart_handle.Instance             = USART1;
    uart_handle.Init.BaudRate        = 115200;
    uart_handle.Init.WordLength      = UART_WORDLENGTH_8B;
    uart_handle.Init.StopBits        = UART_STOPBITS_1;
    uart_handle.Init.Parity          = UART_PARITY_NONE;
    uart_handle.Init.Mode            = UART_MODE_TX_RX;
    uart_handle.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    uart_handle.Init.OverSampling    = UART_OVERSAMPLING_16;
    HAL_UART_Init(&uart_handle);
    
    if (HAL_UART_Init(&uart_handle) != HAL_OK)
    {
        Error_Handler();
    }
    
    // 使能串口接收中断
    __HAL_UART_ENABLE_IT(&uart_handle, UART_IT_RXNE);   
}


void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef PORT;
    
    if (huart->Instance == USART1)
    {
        /* 打开usart时钟， gpio引脚时钟 */
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
       
        /* Tx <===> PA9 */
        /* 配置TX为引脚复用功能 */
        PORT.Pin   = GPIO_PIN_9;
        PORT.Mode  = GPIO_MODE_AF_PP;
        PORT.Pull  = GPIO_PULLUP;
        PORT.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &PORT);
        /* Rx <===> PA10 */
        /* 配置RX为引脚复用功能 */
        PORT.Pin   = GPIO_PIN_10;
        PORT.Mode  = GPIO_MODE_AF_INPUT;
        HAL_GPIO_Init(GPIOA, &PORT);

        /* 抢占优先级0，子优先级0 */
        HAL_NVIC_SetPriority(USART1_IRQ, 0, 0);
        /* 使能USART1中断通道 */
        HAL_NVIC_EnableIRQ(USART1_IRQ);
    }
}





