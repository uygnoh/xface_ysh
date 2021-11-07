#ifndef __BSP_DEBUG_H__
#define __BSP_DEBUG_H__

#include "stm32f10x.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"

#if __ITM_DEBUG__
        uint32_t _write(int file, char *ptr, int len) {
                int DataIdx;
                for (DataIdx = 0; DataIdx < len; DataIdx++) {
                        ITM_SendChar(*ptr++);
                }
                return len;
        }
#else
        #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
        PUTCHAR_PROTOTYPE {
        USART_SendData(USART1, (uint8_t)ch);
        return ch;
        }
#endif
#endif
