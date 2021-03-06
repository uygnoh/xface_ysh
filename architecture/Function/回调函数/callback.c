/*******************************************************************************
        => STM32__回调函数__
*******************************************************************************/
//回调函数就是一个通过函数指针调用的函数。 
  如果你把函数的地址传递给（中间函数的形参），
 （中间函数）通过函数指针调用其所指向的函数时，我们就说这是回调函数。
|_________________________________________________________|
|                                                         |
|       fun_00() {                                        |
|               fun_01(fun_02);                           |
|       }                                                 |
|_________________________________________________________|
1) fun_00()     //应用层
2) fun_01()     //中间层（中间函数）
3) fun_02()     //硬件层（回调函数）
//函数fun_00()=>调用函数fun_01()， 同时函数fun_02()作为参数传递给函数fun_01()


1 函数我名字可以作为参数使用
2 如果一个函数的名字被当作参数来使用，那么这个函数就可以称之为（回调函数）
3 回调函数（不是说这个函数有特别之处，只是被当做参数使用而已）



/*******************************************************************************
        => STM32__回调函数主程序__
*******************************************************************************/
//________________________________________________________|
//      LED.H                                             |
//________________________________________________________|
//定义枚举类型
typedef enum {
        LED_01 = (uint8_t)0x01,
        LED_02 = (uint8_t)0x02,
        LED_03 = (uint8_t)0x03,
} led_enum_t;


//////// 定义中间层 ////////
//led_fun_ptr:函数指针类型
//第一个形参：LED灯的编号
//第二个形参：它是一个指针，它用来调用底层函数
typedef struct {
        void (*led_fun_ptr)(led_enum_t, void (*callback_fun)(led_enum_t));
} led_struct_t;


extern led_struct_t     LED;
extern void             led_on(led_enum_t);
extern void             led_off(led_enum_t);


//________________________________________________________|
//      LED.C                                             |
//________________________________________________________|
void (*led_fun_ptr)(led_enum_t, void (*callback_fun)(led_enum_t));
//初始化（定义了个中间函数）
led_struct_t LED = { led_fun_ptrx };

//实现中间函数功能（它只起到一个调用的作用）
void led_fun_ptrx(led_enum_t led_number, void (*callback_fun)(led_enum_t))
{
        (*callback_fun)(led_number);
}

//底层驱动函数
void led_on(led_enum_t led_number)
{
        switch (led_number) {
        case LED_01: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET); break;
        case LED_02: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); break;
        case LED_03: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); break;
        default: break;
        }
}
//底层驱动函数
void led_off(led_enum_t led_number)
{
        switch (led_number) {
        case LED_01: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET); break;
        case LED_02: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); break;
        case LED_03: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); break;
        default: break;
        }
}


//________________________________________________________|
//      MAIN.C                                            |
//________________________________________________________|
//应用层函数
int main(void)
{
        LED.led_fun_ptr(LED_01, led_on);
}
