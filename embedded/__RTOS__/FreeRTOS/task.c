/******************************************************************************/
/*                    FreeRTOS动态任务创建框架                                   */
/*                   1. 设计 3 个任务， start_task, task1, task2                */
/*                   2. start_task用来创建（task1, task2）                      */
/*                   3. start_task调用函数vTaskDelete()删除自己                  */
/******************************************************************************/

// start_task(起始任务)
//_______________________________________________________//
#define START_TASK_PRIORITY      (1)    //定义任务优先级
#define START_TASK_STACK_SIZE    (120)  //定义任务堆栈大小
TaskHandle_t start_task_handle;         //定义起始任务句柄
void start_task(void *pvParameters);    //开始任务函数声明
//_______________________________________________________//

// task1(任务1)
//_______________________________________________________//
#define TASK1_PRIORITY      (1)    //定义任务优先级
#define TASK1_STACK_SIZE    (120)  //定义任务堆栈大小
TaskHandle_t task1_handle;         //定义起始任务句柄
void task1(void *pvParameters);    //开始任务函数声明
//_______________________________________________________//

// task2(任务2)
//_______________________________________________________//
#define TASK2_PRIORITY      (1)    //定义任务优先级
#define TASK2_STACK_SIZE    (120)  //定义任务堆栈大小
TaskHandle_t task2_handle;         //定义起始任务句柄
void task2(void *pvParameters);    //开始任务函数声明
//_______________________________________________________//
int main(void)
{
        xTaskCreate((TaskFunction_t )start_task,            //任务函数入口
                    (char *         )"start_task",          //任务名称
                    (uint16_t       )START_TASK_STACK_SIZE, //任务堆栈大小
                    (void *         )NULL,                  //任务参数
                    (UBaseType_t    )START_TASK_PRIORITY,   //任务优先级
                    (TaskHandle_t * )&start_task_handle);   //任务句柄

        vTaskStartScheduler(); //打开任务调度器
}
/*******************************************************************************
  函数名称: start_task()
  输入参数: pvParameters
  输出参数: 无
  函数功能: 
*******************************************************************************/
void start_task(void *pvParameters)
{
        xTaskCreate((TaskFunction_t )task1,            //任务1函数入口
                    (char *         )"task1",          //任务1名称
                    (uint16_t       )TASK1_STACK_SIZE, //任务1堆栈大小
                    (void *         )NULL,             //任务1参数
                    (UBaseType_t    )TASK1_PRIORITY,   //任务1优先级
                    (TaskHandle_t * )&task1_handle);   //任务1句柄
        xTaskCreate((TaskFunction_t )task2,            //任务2函数入口
                    (char *         )"task2",          //任务2名称
                    (uint16_t       )TASK2_STACK_SIZE, //任务2堆栈大小
                    (void *         )NULL,             //任务2参数
                    (UBaseType_t    )TASK2_PRIORITY,   //任务2优先级
                    (TaskHandle_t * )&task2_handle);   //任务2句柄

        vTaskDelete(start_task_handle); //删除任务自己也可以用“NULL”
}
/*******************************************************************************
  函数名称: task1()
  输入参数: pvParameters
  输出参数: 无
  函数功能: 点灯程序
*******************************************************************************/
void task1(void *pvParameters)
{
        for (;;) {
                LED0 = ~LED0;
                vTaskDelay(500);
        }
}
/*******************************************************************************
  函数名称: task2()
  输入参数: pvParameters
  输出参数: 无
  函数功能: 点灯程序
*******************************************************************************/
void task2(void *pvParameters)
{
        for (;;) {
                LED1 = 0;
                vTaskDelay(200);
                LED0 = 1;
                vTaskDelay(800);
        }
}




/******************************************************************************/
/*                          FreeRTOS静态任务创建框架                             */
/*                                                                            */
/*                   1. 配置configSUPPORT_STATIC_ALLICATION == 1               */
/*                   2. start_task创建（task1, task2）                          */
/*                                                                            */
/******************************************************************************/

// start_task(起始任务)
//_______________________________________________________//
#define START_TASK_PRIORITY      (1)    //定义任务优先级
#define START_TASK_STACK_SIZE    (120)  //定义任务堆栈大小
TaskHandle_t start_task_handle;         //定义起始任务句柄
StackType_t START_TASK_STACK[START_TASK_STACK_SIZE];//定义任务堆栈内存
StaticTask_t START_TASK_TCB;            //定义任务控制块内存
void start_task(void *pvParameters);    //开始任务函数声明
//_______________________________________________________//
// task1(任务1)
//_______________________________________________________//
#define TASK1_PRIORITY      (1)    //定义任务优先级
#define TASK1_STACK_SIZE    (120)  //定义任务堆栈大小
TaskHandle_t task1_handle;         //定义起始任务句柄
StackType_t TASK1_STACK[TASK1_STACK_SIZE];//定义任务堆栈内存
StaticTask_t TASK1_TCB;            //定义任务控制块内存
void task1(void *pvParameters);    //开始任务函数声明
//_______________________________________________________//
// task2(任务2)
//_______________________________________________________//
#define TASK2_PRIORITY      (1)    //定义任务优先级
#define TASK2_STACK_SIZE    (120)  //定义任务堆栈大小
TaskHandle_t task2_handle;         //定义起始任务句柄
StackType_t TASK2_STACK[TASK2_STACK_SIZE];//定义任务堆栈内存
StaticTask_t TASK2_TCB;            //定义任务控制块内存
void task2(void *pvParameters);    //开始任务函数声明
//_______________________________________________________//



//_______________________________________________________//
//空闲任务
static StaticTask_t IdleTaskTCB;
static StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];
//定时器任务
static StaticTask_t TimerTaskTCB;
static StackType_t TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
//_______________________________________________________//
//                  空闲任务所需要内存                      //
//_______________________________________________________//
vodi vApplicationGetIdleTaskMemory(
        StaticTask_t **ppxIdleTaskTCBBuffer,   //空闲任务的“任务控制块内存”
        StackType_t  **ppxIdleTaskStackBuffer, //堆栈内存
        uint32_t      *pulIdleTaskStackSize)   //堆栈大小
{
        *ppxIdleTaskTCBBuffer   = &IdleTaskTCB;
        *ppxIdleTaskStackBuffer =  IdleTaskStack;
        *pulIdleTaskStackSize   =  configMINIMAL_STACK_SIZE;
}
//_______________________________________________________//
//                  定时器任务所需内存                      //
//_______________________________________________________//
vodi vApplicationGetTimerTaskMemory(
        StaticTask_t **ppxTimerTaskTCBBuffer,   //空闲任务的“任务控制块内存”
        StackType_t  **ppxTimerTaskStackBuffer, //堆栈内存
        uint32_t      *pulTimerTaskStackSize)   //堆栈大小
{
        *ppxTimerTaskTCBBuffer   = &TimerTaskTCB;
        *ppxTimerTaskStackBuffer =  TimerTaskStack;
        *pulTimerTaskStackSize   =  configTIMER_TASK_STACK_DEPTH;
}
int main(void)
{
        start_task_handle = xTaskCreateStatic(
                (TaskFunction_t )start_task,            //任务函数入口   
                (char *         )"start_task",          //任务名称
                (uint32_t       )START_TASK_STACK_SIZE, //任务堆栈大小
                (void *         )NULL,                  //任务参数
                (UBaseType_t    )START_TASK_PRIORITY,   //任务优先级
                (StackType_t *  )START_TASK_STACK,      //任务堆栈内存分配
                (StaticTask_t * )&START_TASK_TCB);      //任务控制块内存分配
        vTaskStartScheduler(); //打开任务调度器
}
/*******************************************************************************
  函数名称: start_task()
  输入参数: pvParameters
  输出参数: 无
  函数功能: 
*******************************************************************************/
void start_task(void *pvParameters)
{
        task1_handle = xTaskCreateStatic(
                (TaskFunction_t )task1,                 //任务函数入口
                (char *         )"task1",               //任务名称
                (uint32_t       )TASK1_STACK_SIZE,      //任务堆栈大小
                (void *         )NULL,                  //任务参数
                (UBaseType_t    )TASK1_PRIORITY,        //任务优先级
                (StackType_t *  )TASK1_STACK,           //任务堆栈内存分配
                (StaticTask_t * )&TASK1_TCB);           //任务控制块内存分配
        task2_handle = xTaskCreateStatic(
                (TaskFunction_t )task2,                 //任务函数入口
                (char *         )"task2",               //任务名称
                (uint32_t       )TASK2_STACK_SIZE,      //任务堆栈大小
                (void *         )NULL,                  //任务参数
                (UBaseType_t    )TASK2_PRIORITY,        //任务优先级
                (StackType_t *  )TASK2_STACK,           //任务堆栈内存分配
                (StaticTask_t * )&TASK2_TCB);           //任务控制块内存分配
        vTaskDelete(start_task);
}

/*******************************************************************************
  函数名称: task1()
  输入参数: pvParameters
  输出参数: 无
  函数功能: 点灯程序
*******************************************************************************/
void task1(void *pvParameters)
{
        for (;;) {
                LED0 = ~LED0;
                vTaskDelay(500);
        }
}
/*******************************************************************************
  函数名称: task2()
  输入参数: pvParameters
  输出参数: 无
  函数功能: 点灯程序
*******************************************************************************/
void task2(void *pvParameters)
{
        for (;;) {
                LED1 = 0;
                vTaskDelay(200);
                LED0 = 1;
                vTaskDelay(800);
        }
}