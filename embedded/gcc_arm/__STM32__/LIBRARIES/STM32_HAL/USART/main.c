

// USART1中断服务程序
/**************************************************************************/
// 如果串口接收到数据， 标志位置“1”
extern uint8_t rx_flag;
// 串口接收到数据临时存放的地方
extern uint8_t rx_tmp;

void USART1_IRQHandler(void)
{
    //uint8_t ch = 0;
    // 如果串口有数据
    if ( __HAL_UART_GET_FLAG( &uart_handle, UART_FLAG_RXNE) != RESET )
    {
        // 读出DR寄存器中的内容
        //ch = (uint16_t)READ_REG(uart_handle.Instance->DR);
        // 把ch中的数据写入DR寄存器中
        //WRITE_REG(uart_handle.Instance->DR, ch);
        
        rx_flag = 1;
        HAL_UART_Receive(&uart_handle, (uint8_t *)&rx_tmp, 1, 100);
    }
    
    HAL_UART_IRQHandler(&uart_handle);
}
/**************************************************************************/



int main(void)
{
    uint8_t rx_buf[16];
    uint8_t rx_count;
    
    HAL_Init();
    SystemClock_Config();
    
    
    
    usart_setup();
    
    while (1)
    {
        // 将USART1中的数据，分析并处理
        if (rx_flag)
        {
            if (rx_count < sizeof(rx_buf)
                rx_buf[rx_count++] = rx_tmp;
            else
                rx_count = 0;
        }
        
        // 简单的通信协议，遇到回车换行认为是“1”个命令帧，
        // 遇到换行字符，认为接收到一个命令
        if (rx_tmp == 0x0A) // 换行字符
        {
            // 检测到有回车字符就把数据返回给上位机
            HAL_UART_Transmit(&uart_handle, (uint8_t *)rx_buf, rx_count);
            rx_count = 0;
        }
    } 
}



