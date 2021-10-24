#ifndef __CM_PRINT_H__
#define __CM_PRINT_H__

/******************************************************************************/
/*                                                                            */
/*                     STM32CubeIDE使用串口调式程序                              */
/*                                                                            */
/******************************************************************************/
//#include <string.h>
//#include <stdio.h>

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/*
PUTCHAR_PROTOTYPE
{
    //注意下面第一个参数是&huart1，因为cubemx配置了串口1自动生成的 
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
*/
/* 这是一个测试程序
int main(void)
{
	char *strs = "Hello World\r\n";
	while (1) {
		HAL_UART_Transmit(&huart1, strs, strlen(strs), 100);
		HAL_Delay(500);
		printf("Test1\r\n");
	}
}
*/




/******************************************************************************/
/*                                                                            */
/*                     STM32CubeIDE使用ITM调式调式程序                           */
/*                                                                            */
/******************************************************************************/
/*
#include "stdio.h"
int _write(int file, char *ptr, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
        ITM_SendChar((*ptr++));
    return len;
}
*/
/* 这是一个测试程序
int main(void)
{
	uint8_t count = 0;
	while (1) {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		count++;
		printf("hello world conut = %d \n", count);
		HAL_Delay(250);
	}

}
*/


#endif
