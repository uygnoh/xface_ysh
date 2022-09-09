
#include "main.h"
#include "usart.h"
#include "gpio.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "time.h"
#include "math.h"
//_____________________________________________________________
void SystemClock_Config(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
PUTCHAR_PROTOTYPE
{
        // 第一个参数: 串口句柄
        // 第二个参数: 要发送的数据
        // 第三个参数: 数据长度
        // 第四个参数: 超时时间
        HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        return ch;
}



uint8_t rx_data;                // 定义接收到数据
uint8_t rx_buffer[256];         // 定义接收缓冲区
uint8_t rx_buffer_pos = 0;     // 指向缓冲区数据的位置



int main(void)
{
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_USART1_UART_Init();


        if (HAL_UART_Receive_IT(&huart1, &rx_data, 1) != HAL_OK) {
          Error_Handler();
        }

        while (1);


}


// STM32F103ZET6(使用外部高速8MHz晶振)
// 经过PLL9倍频， 得到（72000000）Hz主时钟频率
//_____________________________________________________________
void SystemClock_Config(void)
{
        RCC_OscInitTypeDef RCC_OscInitStruct = {0};
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

        /** Initializes the RCC Oscillators according to the specified parameters
        * in the RCC_OscInitTypeDef structure.
        */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
                Error_Handler();
        }

        /** Initializes the CPU, AHB and APB buses clocks
        */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
                Error_Handler();
        }
}

        


/*      => HAL_UART_Receive_IT() -> USART1 启用中断接收
                1. UART_Start_Receive_IT()      
                        设置标志位： huart->RxState = HAL_UART_STATE_BUSY_RX;                            
                        打开USART1接收中断
                
        => USART1_IRQHandler()   -> USART1 中断服务函数
                1. HAL_UART_IRQHandler()
                2. UART_Receive_IT(huart)
                        关闭USART1接收中断
                        设置标志位： huart->RxState = HAL_UART_STATE_READY;
                3. HAL_UART_RxCpltCallback(huart);
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
        // 处理收到的数据
        if (rx_data == '\n') {
                int op1, op2;
                char operator;
                rx_buffer[rx_buffer_pos] = '\0';
                // sscanf() 字符串格式化扫描
                if (sscanf((const char *)rx_buffer, "%d%c%d", &op1, &operator, &op2) == 3) {
                        printf("[Debug info] Expression receive: %d%c%d\r\n", op1, operator, op2);
                        printf("[Debug info] Operator is %c", operator);
                        switch(operator) {
                        case '+':
                                printf("=%d\r\n", op1 + op2);
                                break;
                        case '-':
                                printf("=%d\r\n", op1 - op2);
                                break;
                        case '*':
                                printf("=%d\r\n", op1 * op2);
                                break;
                        case '/':
                                printf("=%d\r\n", op1 / op2);
                                break;
                        default:
                                printf("[Debug info] Invalid operator %c\r\n", operator);
                                break;
                        }
                } else {
                        printf("[Debug info] Invalid expressino: %d%c%d\r\n", op1, operator, op2);
                }
                // 清除位置
                rx_buffer_pos = 0;
        } else {
                if (rx_buffer_pos < 255) {
                        rx_buffer[rx_buffer_pos++] = rx_data;
                }
        }

        // 循环接收数据， 每次接收（1个字节）
        if (HAL_UART_Receive_IT(&huart1, &rx_data, 1) != HAL_OK) {
                Error_Handler();
        }
}


void Error_Handler(void)
{
        __disable_irq();
        while (1) {
        }
}
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif

