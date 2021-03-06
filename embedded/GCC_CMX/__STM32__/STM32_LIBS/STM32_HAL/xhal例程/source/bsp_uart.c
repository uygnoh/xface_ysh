#include "bsp_uart.h"
#include "usart.h"

__IO ITStatus                   uart_ready;
uint8_t                         tx_buffer[] = " ****UART_TwoBoards_ComIT**** ";
uint8_t                         rx_buffer[RX_BUFFER_SIZE];

void test(void)
{
        if (HAL_UART_Transmit_IT(&huart1, (uint8_t *)tx_buffer, TX_BUFFER_SIZE) != HAL_OK) {
                Error_Handler();
        }
        while (uart_ready != SET) {
                LED_01();
                HAL_Delay(100);
        }
        //Reset transmission flag
        uart_ready = RESET;


        if (HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_buffer, RX_BUFFER_SIZE) != HAL_OK) {
                Error_Handler();
        }
        while (uart_ready != SET) {
                LED_01();
                HAL_Delay(100);
                break;
        }
        //Reset transmission flag
        uart_ready = RESET;
}



/*****************************************************************************/
/*      => STM32F103__回调函数__                                              */
/*****************************************************************************/
//UART__发送完成（中断）回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart1)
{
        uart_ready = SET;      //设置传输完成标志位（SET传输完成）
}
//UART__接收完成（中断）回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart1)
{
        uart_ready = SET;      //设置传输完成标志位（SET传输完成）
}
//UART__出错（中断）回调函数
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart1)
{
}
