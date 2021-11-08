#ifndef __COMMON_H__
#define __COMMON_H__
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"
#include "stm32f4xx_hal.h"
uint32_t _write(int file, char *ptr, int len)
{
        int DataIdx;
        for (DataIdx = 0; DataIdx < len; DataIdx++) {
                ITM_SendChar(*ptr++);
        }
        return len;
}
#endif