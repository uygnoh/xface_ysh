#ifndef __COMMON_H__
#define __COMMON_H__

#include "stm32f1xx_hal.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"

  #if ITM_DEBUG
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
        //注意下面第一个参数是&huart1，因为cubemx配置了串口1自动生成的
        HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        return ch;
        }
  #endif
#endif
