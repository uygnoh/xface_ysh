/*******************************************************************************
        => 1 函数我名字可以作为参数使用
        => 2 如果一个函数的名字被当作参数来使用，那么这个函数就可以称之为（回调函数）
        => 3 回调函数（不是说这个函数有特别之处，只是被当做参数使用而已）
        
        UART_HandleTypeDef *huart;
        void (* AbortCpltCallback)(struct __UART_HandleTypeDef *huart);
        huart->AbortCpltCallback(huart);
        
        typedef struct __UART_HandleTypeDef {
        void (* MspInitCallback)(struct __UART_HandleTypeDef *huart);
        } UART_HandleTypeDef;
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define USE_LED         0

#if (USE_LED > 0)
typedef enum {
        LED_01 = 1,
        LED_02 = 2,
        LED_03 = 3
} led_enum_t;

typedef struct __led_struct_def {
        void (*led_fun_ptr)(led_enum_t, void (*callback_fun)(led_enum_t));
} led_struct_def;


//实现中间函数功能（它只起到一个调用的作用）
//_____________________________________________________________
void led_fun_ptrx(led_enum_t led_number, void (*callback_fun)(led_enum_t))
{
        (*callback_fun)(led_number);
}

//底层驱动函数
//_____________________________________________________________
void led_on(led_enum_t led_number)
{
        switch (led_number) {
        case LED_01: printf("CALLBACK-01__ON\n"); break;
        case LED_02: printf("CALLBACK-02__ON\n"); break;
        case LED_03: printf("CALLBACK-03__ON\n"); break;
        default: break;
        }
}

//底层驱动函数
//_____________________________________________________________
void led_off(led_enum_t led_number)
{
        switch (led_number) {
        case LED_01: printf("CALLBACK-01__OFF\n"); break;
        case LED_02: printf("CALLBACK-02__OFF\n"); break;
        case LED_03: printf("CALLBACK-03__OFF\n"); break;
        default: break;
        }
}



//应用层函数
//_____________________________________________________________
int main(void)
{
        //初始化（定义了个中间函数）
        led_struct_def LED = {led_fun_ptrx};
        
        LED.led_fun_ptr(LED_01, led_on);
        LED.led_fun_ptr(LED_01, led_off);
}
#else
        
typedef struct __UART_HandleTypeDef {
        int a;
        int b;
        void (* MspInitCallback)(struct __UART_HandleTypeDef *huart);
} UART_HandleTypeDef;

void MspInitCallback(struct __UART_HandleTypeDef *huart) 
{
        printf("MspInitCallback\n");
}
int main(void) 
{
        UART_HandleTypeDef *huart;
        huart->MspInitCallback(huart);
}
        


#endif
