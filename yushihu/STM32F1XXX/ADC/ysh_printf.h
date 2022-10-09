#ifndef __YSH_PRINTF_H__
#define __YSH_PRINTF_H__
#include <string.h>
#include <stdio.h>
#include "usart.h"
#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
        // 注意下面第一个参数是&huart1，因为cubemx配置了串口1自动生成的
        HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        return ch;
}


#endif
