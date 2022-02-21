#ifndef __BSP_LED_H__
#define __BSP_LED_H__
#include "stm32f1xx_hal.h"

//声明一个枚举类型
typedef enum {
        LED_01 = (uint8_t)0x01,
        LED_02 = (uint8_t)0x02,
        LED_03 = (uint8_t)0x03,
} LED_ENUM_T;

//声明一个结构体类型（它并没有分配存储空间）
//HOS（它是一个函数指针） =>
//它指向{HOS(LED_ENUM_T led_number, void (*callback_fun)(LED_ENUM_T))}
typedef struct {
        void (*HOS)(LED_ENUM_T, void (*callback_fun)(LED_ENUM_T));
} LED_STRUCT_T;



//外部变量
extern LED_STRUCT_T LED;
extern LED_STRUCT_T *BSP;

//外部函数
extern void led_on(LED_ENUM_T led_number);
extern void led_off(LED_ENUM_T led_number);


#endif



