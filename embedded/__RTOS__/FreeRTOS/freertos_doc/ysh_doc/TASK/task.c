#include "task.h"

//创建任务
task_handle_t task_create(
        task_function_t         task_entry,              //任务入口
        const char * const      task_name,              //任务名称
        const uint32_t          task_stack_size,        //任务栈大小
        void * const            task_parameter, 	 //任务形参
        uint32_t * const        task_stack_addr,        //任务栈起始地址
        tcb_t * const           tcb_ptr)                //任务控制块指针
{
	tcb_t *new_tcb;
	//定义一个任务句柄task_handle，任务句柄用于指向任务的TCB
	task_handle_t task_handle;
	
	if ((task_stack_addr != NULL) && (tcb_ptr != NULL)) {
		new_tcb = (tcb_t *)tcb_ptr;
		new_tcb->stack = (uint32_t *)task_stack_addr;
	
		//任务初始化
		task_initialize(
			task_entry,		//任务入口
			task_name,		//任务名称
			task_stack_size,	//任务栈大小
			task_parameter,		//任务形参
			&task_handle,		//任务句柄
			new_tcb);		//任务控制块指针
		
	} else {
		task_handle = NULL;
	}
	
	/* 返回任务句柄，如果任务创建成功，此时 task_handle 应该指向任务控制块 */
	return task_handle;
}

/* 任务初始化 */
static void task_initialize(
	task_function_t 	task_entry,	//任务入口
	const char * const 	task_name,	//任务名称
	const uint32_t		task_stack_size,//任务栈大小
	void * const 		task_parameter,	//任务形参
	task_handle_t * const 	task_handle,	//任务句柄
	tcb_t *			new_tcb)	//任务控制块指针
{
	uint32_t *top_stack;
	uint32_t x;
	
	//获取栈顶指针
	top_stack = new_tcb->stack + (task_stack_size - (uint32_t)1);
	//向下做8字节对齐
	top_stack = (uint32_t *)(((uint32_t)top_stack) & (~((uint32_t)0x0007)));
	//将任务的名字存储在TCB(任务控制块)中
	for (x = (uint32_t)0; x < (uint32_t)MAX_TASK_NAME_LEN; x++) {
		new_tcb->name[x] = task_name[x];
		if (task_name[x] == 0x00)
			break;
	}
	//任务名字长度不能超过MAX_TASK_NAME
	new_tcb->name[MAX_TASK_NAME_LEN - 1] = '\0';
	
	//初始化TCB中的state_list_item节点
	list_item_initialize(&(new_tcb->state_list_item));
	//设置state_list_item节点的拥有者
	SET_LIST_ITEM_OWNER(&(new_tcb->state_list_item), new_tcb);
	
	//初始化任务栈
	new_tcb->top_stack = task_stack_initialize(
		top_stack,
		task_entry,
		task_parameter);
	//让任务句柄指向任务控制块
	if ((void *)task_handle != NULL)
		*task_handle = (task_handle_t)new_tcb;
}

/* 任务通常是不会返回的，如果返回，就会进入到这里 */
void task_exit_error(void)
{
	for (;;);
}

/* 任务栈初始化 */
uint32_t *task_stack_initialize(
	uint32_t *top_stack,
	task_function_t task_entry,
	void *task_parameter)
{
	//异常发生时，自动加载到CPU寄存器的内容
	top_stack--;
	//xPSR的bit24必须置1，即0x01000000
	*top_stack = INITIAL_XPSR;
	top_stack--;
	//任务的入口地址
	*top_stack = ((uint32_t)task_entry) & START_ADDRESS_MASK;
	top_stack--;
	//任务的返回地址，通常任务是不会返回的，如果返回了就跳转到task_exit_error， 
	//该函数是一个无限循环
	*top_stack = (uint32_t)task_exit_error;
	//R12, R3, R2 and R1 默认初始化为0
	top_stack -= 5;
	*top_stack = (uint32_t)task_parameter;
	
	//异常发生时，手动加载到CPU寄存器的内容
	top_stack -= 8;
	
	//返回栈顶指针
	return top_stack;
}

/* 就绪任务列表初始化 */
void task_list_initialize(void)
{
	uint32_t priority;
	for (priority = (uint32_t)0U;
		priority < (uint32_t)MAX_PRIORITY;
			priority++)
		list_initialize(&ready_task_list[priority]);
}

void task_start_scheduler(void)
{
	//手动指定第一个运行的任务
	global_current_tcb = &task1_tcb;
	//启动调度器
	if (strat_scheduler() != FALSE) {
	//调度器启动成功，则不会返回，即不会来到这里
	}
}

/*
*参考资料《STM32F10xxx Cortex-M3 编程手册》4.4.3，百度搜索“PM0056”即可找到这个文档
* 在Cortex-M中，内核外设SCB中SHPR3寄存器用于设置SysTick和PendSV的异常优先级
* System handler priority register 3 (SCB_SHPR3) SCB_SHPR3：[0xE000_ED20]
* Bits 31:24 PRI_15[7:0]: Priority of system handler 15, SysTick异常
* Bits 23:16 PRI_14[7:0]: Priority of system handler 14, PendSV异常
*/
#define NVIC_SYSPRI2_REG	(*((volatile uint32_t *)0xe000ed20))
#define NVIC_PENDSV_PRI		(((uint32_t)KERNEL_INTERRUPT_PRIORITY) << 16UL)
#define NVIC_SYSTICK_PRI	(((uint32_t)KERNEL_INTERRUPT_PRIORITY) << 24UL)
uint32_t start_scheduler(void)
{
	//配置PendSV 和 SysTick 的中断优先级为最低
	NVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
	NVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;

	//启动第一个任务，不再返回
	strat_first_task();
	//不应该运行到这里
	return 0;
}

/*
* 参考资料《STM32F10xxx Cortex-M3 编程手册》4.4.3，百度搜索“PM0056”即可找到这个文档
* 在Cortex-M中，内核外设SCB的地址范围为：0xE000ED00-0xE000ED3F
* 0xE000ED008为SCB外设中SCB_VTOR这个寄存器的地址，里面存放的是向量表的起始地址，即MSP的地址
*/
static void start_first_task(void)
{
	__asm volatile (
		" ldr r0, =0xE000ED08 \n"//使用NVIC偏移寄存器定位堆栈
		" ldr r0, [r0]        \n"
		" ldr r0, [r0]        \n"
		" msr msp, r0         \n"//设置主栈指针msp的值
		" cpsie i             \n"//使能全局中断
		" cpsie f             \n"
		" dsb                 \n"
		" isb                 \n"
		" svc 0               \n"//调用SVC去启动第一个任务
		" nop                 \n"
		" .ltorg              \n"
		);
}







