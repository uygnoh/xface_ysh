
#include "os.h"

#define TASK00_PRIO                             3
#define TASK00_STACK_SIZE                       512
OS_STK  task00_stack[TASK00_STACK_SIZE];
void task00(void *pdata);

void task00(void *pdata)
{
        //进入任务前，设置系统时钟参数
        OS_CPU_SysTickInitFreq(100*1000*1000);
        pdata = pdata;
        for (;;) {
                //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                OSTimeDly(100);
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                OSTimeDly(100);
        }
}


int main(void)
{

        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_USART2_UART_Init();


        OSInit();
        OSTaskCreate(
                task00,                                 //任务入口
                (void *)0,                              //任务参数
                &task00_stack[TASK00_STACK_SIZE - 1],   //任务栈顶
                TASK00_PRIO	);                      //任务优先级别
        OSStart();

        while (1) {

        }

}

