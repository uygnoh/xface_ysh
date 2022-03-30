#ifndef __BSP_LED_H__
#define __BSP_LED_H__
#include "stm32f1xx_hal.h"

typedef enum {
        LED_01 = (uint8_t)0x01,
        LED_02 = (uint8_t)0x02,
        LED_03 = (uint8_t)0x03
} LED_ENUM_T;

typedef struct {
        void (*bsp_led)(LED_ENUM_T, void (*callback_fun)(LED_ENUM_T));
} LED_STRUCT_T LED;


extern LED_STRUCT_T LED;
void bsp_led(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T));
void led_on(LED_ENUM_T led_number);
void led_off(LED_ENUM_T led_number);

#endif
