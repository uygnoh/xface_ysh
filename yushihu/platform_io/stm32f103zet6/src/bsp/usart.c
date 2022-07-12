#include "common.h"

/*******************************************************************************
  函数名称: usart1_setup()
  输入参数: 无
  输出参数: 无
  函数功能: USART1初始化设置(   72MHz@115200 1N8  )
*******************************************************************************/
void usart1_setup(void)
{   
        GPIOA_CLOCK_ENABLE();                   //打开GPIOA时钟
        USART1_CLOCK_ENABLE();                  //打开USART1时钟
	GPIOA->CRH  &= (uint32_t)(0xFFFFF00F);  //清除相关的位
	GPIOA->CRH  |= (uint32_t)(0x000000B0);  //TX(PA.09)复用推挽输出(50MHz)
	GPIOA->CRH  |= (uint32_t)(0x00000400);  //RX(PA.10)浮空输入
	USART1->CR1 |= BIT_13;                  //USART模块使能
	USART1->CR1 &= ~BIT_12;                 //1个起始位, 8个数据位
	USART1->CR2 &= ~(BIT_13 + BIT_12);      //1个停止位(bit13=0, bit12=0)
	USART1->BRR  = 0x0271;                  //72MHz@115200 			
}
/*******************************************************************************
  函数名称: usart_send_string()
  输入参数: 无
  输出参数: 无
  函数功能: 串口向上位机发送一串字符
*******************************************************************************/
void usart_send_string(uint8_t *tx_buf)
{
        uint16_t timeout = 50000;
        USART1->CR1 |= BIT_03;                          //发送使能
        while (*tx_buf != '\0') {                       //如果字符不是（尾0）
                while ((USART1->SR & 0x80) == 0) {      //等待发送数据寄存器空
                        if (timeout-- == 0) {
                                return;
                        }
                }
                USART1->DR  = *tx_buf++;
                timeout = 50000;
        }
        while ((USART1->SR & 0x40) == 0) {              //等待发送完成
                if (timeout-- == 0) {
                        return;
                }
        }
}
/*******************************************************************************
  函数名称: void led_blink(void)
  输入参数: 无
  输出参数: 无
  函数功能: 测试程序
*******************************************************************************/
void led_blink(void)
{
        uint8_t i;
        GPIOA_CLOCK_ENABLE();                   //打开GPIOA时钟
        GPIOA->CRL  &= (uint32_t)(0xFFFFF0FF);  //清除相关的位
	GPIOA->CRL  |= (uint32_t)(0xFFFFF3FF);  //PA2__推挽输出
        for (i = 0; i < 6; i++) {               //循环 6 次
                GPIOA->ODR |= BIT_02;
                __delay_ms(500);
                GPIOA->ODR &= ~BIT_02;
                __delay_ms(500);
        }
}