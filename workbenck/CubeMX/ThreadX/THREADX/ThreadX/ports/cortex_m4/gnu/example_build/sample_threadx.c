#include "tx_api.h"
#include "gpio.h"

// SWV调试系统
//_____________________________________________________________
#include "stdio.h"
int _write(int file, char *ptr, int len)
{
        int i = 0;
        for (i = 0; i < len; i++) {
            ITM_SendChar((*ptr++));
        }
        return len;
}

// 线程__00
//_____________________________________________________________
#define THREAD00_PARAM                          0u      //线程参数
#define THREAD00_PRIO                           2u      //线程优先级别
#define THREAD00_PRIORITY                       2u      //线程抢占阈值
#define THREAD00_STACK_SIZE                     4096u   //线程栈大小
static TX_THREAD thread00_tcb;
static uint64_t thread00_stack[THREAD00_STACK_SIZE / 8];

// 线程__11
//_____________________________________________________________
#define THREAD11_PARAM                          0u      //线程参数
#define THREAD11_PRIO                           2u      //线程优先级别
#define THREAD11_PRIORITY                       2u      //线程抢占阈值
#define THREAD11_STACK_SIZE                     4096u   //线程栈大小
static TX_THREAD thread11_tcb;
static uint64_t thread11_stack[THREAD11_STACK_SIZE / 8];

// 线程__Function
//_____________________________________________________________
void tx_application_define(void *first_unused_memory);
void thread00_entry(ULONG thread_input);
void thread11_entry(ULONG thread_input);


void tx_application_define(void *first_unused_memory)
{
        tx_thread_create(
                &thread00_tcb,          //线程控制块地址
                "THREAD00_NAME",        //线程名称
                thread00_entry,         //线程入口函数
                THREAD00_PARAM,         //线程参数
                &thread00_stack[0],     //线程栈起始地址
                THREAD00_STACK_SIZE,    //线程栈大小
                THREAD00_PRIO,          //线程优先级
                THREAD00_PRIORITY,      //线程抢占阈值
                TX_NO_TIME_SLICE,       //不开启时间片
                TX_AUTO_START   );      //创建后立即启动
        tx_thread_create(
                &thread11_tcb,          //线程控制块地址
                "THREAD11_NAME",        //线程名称
                thread11_entry,         //线程入口函数
                THREAD11_PARAM,         //线程参数
                &thread11_stack[0],     //线程栈起始地址
                THREAD11_STACK_SIZE,    //线程栈大小
                THREAD11_PRIO,          //线程优先级
                THREAD11_PRIORITY,      //线程抢占阈值
                TX_NO_TIME_SLICE,       //不开启时间片
                TX_AUTO_START   );      //创建后立即启动
        printf("9999911 ...\n");
}
void thread00_entry(ULONG thread_input)
{
        while (1) {
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                tx_thread_sleep(100);
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                tx_thread_sleep(100);
        }
}
void thread11_entry(ULONG thread_input)
{
        while (1) {
                printf("THREADX 11 ...\n");
                tx_thread_sleep(100);
        }
}



int main_user(void)
{

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
    return 0;
}
