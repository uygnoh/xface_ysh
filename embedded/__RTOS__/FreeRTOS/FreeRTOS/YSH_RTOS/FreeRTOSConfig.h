#ifndef __FREERTOS_CONFIG_H__
#define __FREERTOS_CONFIG_H__

#include "stm32f103xe.h"



//针对不同的编译器调用不同的stdint.h文件
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif


//断言
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)



/*******************************************************************************
                          FreeRTOS基础配置配置选项 
*******************************************************************************/
//置1_(RTOS使用抢占式调度器)
//置0_(RTOS使用协作式调度器（时间片）)
#define configUSE_PREEMPTION			1

//置1_(使能时间片调度, 默认是使能的)
#define configUSE_TIME_SLICING			1		

/* FreeRTOS支持2种，获取当前要运行任务的方法
 * 
 * 通用方法：
 *      1.configUSE_PORT_OPTIMISED_TASK_SELECTION设置为_0
 *      2.可以用于所有FreeRTOS支持的硬件
 *      3.完全用C实现，效率略低于特殊方法。
 *      4.不强制要求限制最大可用优先级数目
 * 特殊方法：
 *      1.必须将configUSE_PORT_OPTIMISED_TASK_SELECTION设置为_1
 *      2.依赖一个或多个特定架构的汇编指令（一般是类似计算前导零[CLZ]指令）。
 *      3.比通用方法更高效
 *      4.一般强制限定最大可用优先级数目为32
 * 一般是硬件计算前导零指令，如果所使用的，MCU没有这些硬件指令的话此宏应该设置为0！
 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION		1

                                                            
//置1_(使能低功耗tickless模式) 
//置0_(保持系统节拍（tick）中断一直运行)
#define configUSE_TICKLESS_IDLE						0   

//配置CPU内核时钟频率，也就是CPU指令执行频率
#define configCPU_CLOCK_HZ					(SystemCoreClock)

//FreeRTOS系统节拍中断的频率
//表示操作系统每1秒钟产生多少个tick，tick即是操作系统节拍的时钟周期
//即一秒中断的次数，每次中断RTOS都会进行任务调度
#define configTICK_RATE_HZ					((TickType_t)1000)

//可使用的最大优先级
#define configMAX_PRIORITIES				(32)

//空闲任务使用的堆栈大小
#define configMINIMAL_STACK_SIZE			((unsigned short)128)
  
//任务名字字符串长度
#define configMAX_TASK_NAME_LEN				(16)

//系统节拍计数器变量数据类型
//1(表示为16位无符号整形); 0(表示为32位无符号整形)
#define configUSE_16_BIT_TICKS				0                      

//空闲任务放弃CPU使用权给其他同优先级的用户任务
#define configIDLE_SHOULD_YIELD				1           

//启用队列
#define configUSE_QUEUE_SETS				1    

//开启任务通知功能，默认开启
#define configUSE_TASK_NOTIFICATIONS		1   

//使用互斥信号量
#define configUSE_MUTEXES					1    

//使用递归互斥信号量                                            
#define configUSE_RECURSIVE_MUTEXES			1   

//使用计数信号量
#define configUSE_COUNTING_SEMAPHORES		1

//设置可以注册的信号量和消息队列个数
//用户可以根据自己需要修改即可，RAM小的芯片尽量裁剪得小一些
#define configQUEUE_REGISTRY_SIZE			(10)

//                                                                     
#define configUSE_APPLICATION_TASK_TAG		0                       
                      


/*******************************************************************************
              FreeRTOS与内存申请有关配置选项                                               
*******************************************************************************/
//支持动态内存
#define configSUPPORT_DYNAMIC_ALLOCATION	1
   
//支持静态内存
#define configSUPPORT_STATIC_ALLOCATION		0
				
//FreeRTOS内核总计可用的有效的RAM大小
//不能超过芯片的RAM大小，一般来说用户可用的
//内存大小会小于configTOTAL_HEAP_SIZE定义的大小，因为系统本身就需要内存
#define configTOTAL_HEAP_SIZE				((size_t)(36*1024))    



/*******************************************************************************
                       FreeRTOS与钩子函数有关的配置选项                                            
*******************************************************************************/
//置1_(使用空闲钩子（Idle Hook类似于回调函数）)
//置0_(忽略空闲钩子)
#define configUSE_IDLE_HOOK					0      

//置1_(使用时间片钩子（Tick Hook）)
//置0_(忽略时间片钩子)
#define configUSE_TICK_HOOK					0           

//使用内存申请失败钩子函数
#define configUSE_MALLOC_FAILED_HOOK		0 

//大于0时启用堆栈溢出检测功能，如果使用此功能 
//用户必须提供一个栈溢出钩子函数，如果使用的话
//此值可以为1或者2，因为有两种栈溢出检测方法
#define configCHECK_FOR_STACK_OVERFLOW		0   



/*******************************************************************************
                   FreeRTOS与运行时间和任务状态收集有关的配置选项   
*******************************************************************************/
//启用运行时间统计功能
#define configGENERATE_RUN_TIME_STATS			0

 //启用可视化跟踪调试
#define configUSE_TRACE_FACILITY				0

/* 与宏configUSE_TRACE_FACILITY同时为1时会编译下面3个函数
 * prvWriteNameToBuffer()
 * vTaskList(),
 * vTaskGetRunTimeStats()
 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1                       
                                                          

                                                     
/*******************************************************************************
                     FreeRTOS与协程有关的配置选项                                                
*******************************************************************************/
//启用协程，启用协程以后必须添加文件croutine.c
#define configUSE_CO_ROUTINES				0

//协程的有效优先级数目
#define configMAX_CO_ROUTINE_PRIORITIES		(2)                   



/*******************************************************************************
                FreeRTOS与软件定时器有关的配置选项      
*******************************************************************************/
//启用软件定时器
#define configUSE_TIMERS					1

//软件定时器优先级
#define configTIMER_TASK_PRIORITY			(configMAX_PRIORITIES-1)

//软件定时器队列长度
#define configTIMER_QUEUE_LENGTH			10

//软件定时器任务堆栈大小
#define configTIMER_TASK_STACK_DEPTH		(configMINIMAL_STACK_SIZE*2)

   

/*******************************************************************************
                           FreeRTOS可选函数配置选项                                                     
*******************************************************************************/
#define INCLUDE_xTaskGetSchedulerState			1
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			1
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_eTaskGetState					1
#define INCLUDE_xTimerPendFunctionCall			1
//#define INCLUDE_xTaskGetCurrentTaskHandle		1
//#define INCLUDE_uxTaskGetStackHighWaterMark	0
//#define INCLUDE_xTaskGetIdleTaskHandle		0



/*******************************************************************************
                          FreeRTOS与中断有关的配置选项                                                 
*******************************************************************************/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS								__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS								4   
#endif
//中断最低优先级
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15

//系统可管理的最高中断优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5

#define configKERNEL_INTERRUPT_PRIORITY \
( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )/* 240 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )



/*******************************************************************************
                       FreeRTOS与中断服务函数有关的配置选项                         
*******************************************************************************/
#define xPortPendSVHandler			PendSV_Handler
#define vPortSVCHandler				SVC_Handler


// 以下为使用Percepio Tracealyzer需要的东西，
// 不需要时将 configUSE_TRACE_FACILITY 定义为 0 
#if ( configUSE_TRACE_FACILITY == 1 )
  #include "trcRecorder.h"
  // 启用一个可选函数（该函数被 Trace源码使用，默认该值为0 表示不用）
  #define INCLUDE_xTaskGetCurrentTaskHandle	1
#endif


#endif /* FREERTOS_CONFIG_H */

