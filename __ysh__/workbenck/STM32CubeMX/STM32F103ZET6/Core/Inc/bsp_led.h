#ifndef __BSP_LED_H__
#define __BSP_LED_H__
#include "stm32f1xx_hal.h"

typedef enum {
        LED_01 = (uint8_t)0x01,
        LED_02 = (uint8_t)0x02,
        LED_03 = (uint8_t)0x03
} led_enum_t;

typedef struct {
        void (*bsp_led)(led_enum_t, void (*callback_fun)(led_enum_t));
} led_struct_t;


led_struct_t LED;
void bsp_led(led_enum_t led_number, void (*callback_fun)(led_enum_t));
void led_on(led_enum_t led_number);
void led_off(led_enum_t led_number);

#endif
