#include <stdint.h>
//#include <stdio.h>
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)


void my_task(void *pvParam);
TaskHandle_t my_handle;
void task00(void *pvParam);
TaskHandle_t task00_handle;
int main(void)
{
        hardware_init();
        xTaskCreate(
                (TaskFunction_t)my_task,                //任务函数
                (char *        )"MY_TASK",              //任务名称
                (uint16_t      )1024,                   //任务栈大小
                (void *        )NULL,                   //任务参数
                (UBaseType_t   )2,                      //任务优先级
                (TaskHandle_t *)&my_handle      );      //任务句柄
        xTaskCreate(
                (TaskFunction_t)task00,                 //任务函数
                (char *        )"TASK00",               //任务名称
                (uint16_t      )1024,                   //任务栈大小
                (void *        )NULL,                   //任务参数
                (UBaseType_t   )2,                      //任务优先级
                (TaskHandle_t *)&task00_handle  );      //任务句柄
        vTaskStartScheduler();
}
void my_task(void *pvParam)
{
        for (;;) {
                uint8_t string[] = "my_task!\n";
                print(string);
                vTaskDelay(1000 / portTICK_PERIOD_MS);

        }
}
void task00(void *pvParam)
{
        for (;;) {
                uint8_t string[] = "task00!\n";
                print(string);
                vTaskDelay(2000 / portTICK_PERIOD_MS);

        }
}

PUTCHAR_PROTOTYPE
{
        USART_SendData(USART1, (uint8_t)ch);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {
                ;
        }
        return ch;
}
