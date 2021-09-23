/*******************************************************************************
                                  任务控制块
*******************************************************************************/
typedef struct tskTaskControlBlock {
        volatile StackType_t    *pxTopOfStack;  //栈顶
        ListItem_t              xStateListItem; //状态列表项
        ListItem_t              xEventListItem; //事件列表项
        UBaseType_t             uxPriority;     //任务优先级
        StackType_t             *pxStack;       //任务栈起始地址
        char                    pcTaskName[configMAX_TASK_NAME_LEN];//任务名称
} tskTCB;
typedef tskTCB TCB_t;


// 定义任务栈
#define TASK1_STACK_SIZE			20
StackType_t Task1Stack[TASK1_STACK_SIZE];
#define TASK2_STACK_SIZE			20
StackType_t Task2Stack[TASK2_STACK_SIZE];


// 定义任务控制块
TCB_t Task1TCB;
TCB_t Task2TCB;


// 定义任务句柄
typedef void * TaskHandle_t;
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;


// 定义当前正在运行的任务控制块
TCB_t * volatile pxCurrentTCB = NULL;

