#ifndef __BSP_DEBUG_H__
#define __BSP_DEBUG_H__

#include "stm32f1xx_hal.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"

#define __TIM_DEBUG__           0

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
        //第一个参数是串口（全局结构体huart1）
        //第二个参数是串口（）
        //第三个参数是串口（）
        //第四个参数是串口（最大延时时间）
        HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        return ch;
        }
        #endif
#endif
