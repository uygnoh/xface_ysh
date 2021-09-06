#ifndef __TASK_H__
#define __TASK_H__
#include <string.h>
#include "stm32f103xe.h"
#include "list.h"

/******************************************************************************/
/*                                                                            */
/*                                    栈                                      */
/*                                                                            */
/******************************************************************************/
/* 定义特殊寄存器 */
#define INITIAL_XPSR			(0x01000000)
#define START_ADDRESS_MASK		((uint32_t)(0xfffffffeUL))

/* 定义任务1 栈 */
#define task1_stack_size		128
uint32_t task1_stack[task1_stack_size];
/* 定义任务2 栈 */
#define task2_stack_size		128
uint32_t task2_stack[task2_stack_size];


/******************************************************************************/
/*                                                                            */
/*                               任务控制块                                     */
/*                                                                            */
/******************************************************************************/
#define MAX_TASK_NAME_LEN		16

struct task_control_block {
	volatile uint32_t 	*top_stack;		//栈顶指针
	list_item_t 		state_list_item;	//任务节点(状态)
	uint32_t 		*stack;			//任务栈起始地址
	char 			*name[MAX_TASK_NAME_LEN];//任务名称
};
typedef struct task_control_block tcb_t;


/******************************************************************************/
/*                                                                            */
/*                               数据类型                                      */
/*                                                                            */
/******************************************************************************/
tcb_t task1_tcb;
tcb_t task2_tcb;
typedef void *task_handle_t;
typedef void (*task_function_t)(void *);


/******************************************************************************/
/*                                                                            */
/*                               就绪任务列表                                   */
/*                                                                            */
/******************************************************************************/
//最大支持5个优先级
#define MAX_PRIORITY			5
list_t ready_task_list[MAX_PRIORITY];

//KERNEL_INTERRUPT_PRIORITY


//创建任务
task_handle_t task_create(
	task_function_t 	task_entry,	//任务入口
	const char * const 	task_name,	//任务名称
	const uint32_t		task_stack_size,//任务栈大小
	void * const 		task_parameter,	//任务形参
	uint32_t * const 	task_stack_addr,//任务栈起始地址
	tcb_t * const 		tcb_ptr);	//任务控制块指针
//任务初始化
static void task_initialize(
	task_function_t 	task_entry,	//任务入口
	const char * const 	task_name,	//任务名称
	const uint32_t 	task_stack_size,//任务栈大小
	void * const 		task_parameter,	//任务形参
	task_handle_t * const 	task_handle,	//任务句柄
	tcb_t *			new_tcb);	//任务控制块指针
void task_exit_error(void);
//任务栈初始化
uint32_t *task_stack_initialize(
	uint32_t *top_stack,
	task_function_t task_entry,
	void *task_parameter);
//任务列表初始化
void task_list_initialize(void);
//启动任务调度器
void task_start_scheduler(void);
#endif
