// FreeRTOS
//_____________________________________________________________
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


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


//空闲任务内存分配
//_____________________________________________________________
static StackType_t      IdleTaskStack[configMINIMAL_STACK_SIZE];
static StaticTask_t     IdleTaskTCB;

//定时器任务内存分配
//_____________________________________________________________
static StackType_t      TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
static StaticTask_t     TimerTaskTCB;

//  任务__00
//_____________________________________________________________
#define TASK00_STACK_SIZE                       1024
#define TASK00_PRIO                             3
TaskHandle_t task00_handle = NULL;
StackType_t task00_stack[TASK00_STACK_SIZE];
StaticTask_t task00_tcb;

//  任务__11
//_____________________________________________________________
#define TASK11_STACK_SIZE                       1024
#define TASK11_PRIO                             3
TaskHandle_t task11_handle = NULL;
StackType_t task11_stack[TASK11_STACK_SIZE];
StaticTask_t task11_tcb;

//  任务__22
//_____________________________________________________________
#define TASK22_STACK_SIZE                       512
#define TASK22_PRIO                             3
TaskHandle_t task22_handle = NULL;
StackType_t task22_stack[TASK22_STACK_SIZE];
StaticTask_t task22_tcb;


void task00(void *parameters);
void task11(void *parameters);
void task22(void *parameters);
void SystemClock_Config(void);


//      => 空闲任务
//_____________________________________________________________
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t  **ppxIdleTaskStackBuffer,
                                    uint32_t      *pulIdleTaskStackSize)
{
        *ppxIdleTaskTCBBuffer   = &IdleTaskTCB;
        *ppxIdleTaskStackBuffer = IdleTaskStack;
        *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}

//      => 定时器任务
//_____________________________________________________________
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t  **ppxTimerTaskStackBuffer,
                                     uint32_t      *pulTimerTaskStackSize)
{
        *ppxTimerTaskTCBBuffer   = &TimerTaskTCB;
        *ppxTimerTaskStackBuffer = TimerTaskStack;
        *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}

//      => 任务 00
//_____________________________________________________________
void task00(void *parameters)
{
        for (;;) {
                taskENTER_CRITICAL();
                task11_handle = xTaskCreateStatic(
                                (TaskFunction_t)task11,
                                (char *)"TASK11",
                                (uint32_t)TASK11_STACK_SIZE,
                                (void *)NULL,
                                (UBaseType_t)TASK11_PRIO,
                                (StackType_t *)task11_stack,
                                (StaticTask_t *)&task11_tcb
                                );
                if (task11_handle == NULL) {
                        Error_Handler();
                }
                task22_handle = xTaskCreateStatic(
                                (TaskFunction_t)task22,
                                (char *)"TASK22",
                                (uint32_t)TASK22_STACK_SIZE,
                                (void *)NULL,
                                (UBaseType_t)TASK22_PRIO,
                                (StackType_t *)task22_stack,
                                (StaticTask_t *)&task22_tcb
                                );
                if (task22_handle == NULL) {
                        Error_Handler();
                }
                vTaskDelete(task00_handle);
                printf("TASK00 Delete ...\n");
                taskEXIT_CRITICAL();
        }
}


//      => 任务 11
//_____________________________________________________________
void task11(void *parameters)
{
        const portTickType xDelay = 500 / portTICK_RATE_MS;
        for (;;) {
                printf("TASK_11\n");
                vTaskDelay(xDelay);
        }
}

//      => 任务 22
//_____________________________________________________________
void task22(void *parameters)
{
        const portTickType xDelay = 500 / portTICK_RATE_MS;
        for (;;) {
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                vTaskDelay(xDelay);
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                vTaskDelay(xDelay);
                printf("TASK_22\n");
        }
}

int main(void)
{
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_USART2_UART_Init();

        task00_handle = xTaskCreateStatic(
                        (TaskFunction_t)task00,
                        (char *)"TASK00",
                        (uint32_t)TASK00_STACK_SIZE,
                        (void *)NULL,
                        (UBaseType_t)TASK00_PRIO,
                        (StackType_t *)task00_stack,
                        (StaticTask_t *)&task00_tcb
                        );
        if (task00_handle == NULL) {
                Error_Handler();
        }

        vTaskStartScheduler();

        while (1) {

        }
}

