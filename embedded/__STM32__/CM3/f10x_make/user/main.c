#include "stm32f10x.h"

/*******************************************************************************
  函数名称: usart1_setup()
  输入参数: 无
  输出参数: 无
  函数功能: USART1初始化设置 72MHz@115200 1N8
*******************************************************************************/
void usart1_setup(void)
{   
        GPIOA_CLOCK_ENABLE();                   //打开GPIOA时钟
        USART1_CLOCK_ENABLE();                  //打开USART1时钟
	GPIOA->CRH  &= (uint32_t)(0xFFFFF00F);  //
	GPIOA->CRH  |= (uint32_t)(0x000000B0);  //TX(PA.09)复用推挽输出(50MHz)
	GPIOA->CRH  |= (uint32_t)(0x00000400);  //RX(PA.10)浮空输入
	USART1->CR1 |= BIT_13;                  //USART模块使能
	USART1->CR1 &= ~BIT_12;                 //1个起始位, 8个数据位
	USART1->CR2 &= ~(BIT_13 + BIT_12);      //1个停止位(bit13=0, bit12=0)
	USART1->CR1 |= BIT_03 + BIT_02;         //发送使能 | 接收使能 
	USART1->BRR  = 0x0271;                  //72MHz@115200 			
}
/*******************************************************************************
  函数名称: usart_send_string()
  输入参数: 无
  输出参数: 无
  函数功能: USART1初始化设置 72MHz@115200 1N8
*******************************************************************************/
void usart_send_string(void)
{
        uint8_t i = 0;
        uint8_t tx_buf[] = "hello, world!\n";
        while (tx_buf[i] != '\0') {
                USART1->SR &= ~BIT_06;
                USART1->DR  = tx_buf[i];
                i++;
                while ((USART1->SR & 0x40) == 0);
        }
}




int main(void)
{
        uint8_t i;
        usart1_setup();
        for (i = 0; i < 16; i++)
                usart_send_string();
        return 0;
}
