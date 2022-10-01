#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__



/*******************************************************************************
        => 内核配置
*******************************************************************************/
#define RT_THREAD_PRIORITY_MAX          32      // RT-Thread 支持多少个优先级
#define RT_TICK_PER_SECOND              1000    // 操作系统每秒钟有多少个操作系
                                                // 统的时钟周期，默认为 1000
#define RT_ALIGN_SIZE                   4       // CPU 处理的数据需要多少个字节对齐
#define RT_NAME_MAX                     8       // 内核对象名字的最大长度
#define RT_USING_COMPONENTS_INIT                // 使用 RT-Thread 组件初始化，
                                                // 默认使能


#define RT_USING_USER_MAIN                      // 使用用户 main 函数，默认打开
#define RT_MAIN_THREAD_STACK_SIZE       512     // main 线程栈大小，单位为字节，
                                                // 默认为 512
                                                

                   
/*******************************************************************************
        => 调试配置
*******************************************************************************/                                  


//#define RT_DEBUG                              // Default: enable kernel 
                                                // debug configuration

#define RT_DEBUG_INIT                   0       // enable components initialization 
                                                // debug configuration<0-1>
                                                // Default: 0


//#define RT_USING_OVERFLOW_CHECK               // thread stack over flow detect :
                                                // Diable Thread stack over flow detect
                                                
                                                
                                                
/*******************************************************************************
        => HOOK
*******************************************************************************/ 
//#define RT_USING_HOOK                         // 钩子函数配置
//#define RT_USING_IDLE_HOOK                    // 空闲线程钩子函数配置


#define RT_USING_TIMER_SOFT             0       // 软件定时器配置
#if RT_USING_TIMER_SOFT == 0
#undef RT_USING_TIMER_SOFT
#endif



/*******************************************************************************
        => 软件定时器
*******************************************************************************/ 
#define RT_TIMER_THREAD_PRIO            4       // The priority level of timer thread <0-31>
                                                // Default: 4

#define RT_TIMER_THREAD_STACK_SIZE 512          // The stack size of timer thread <0-8192>
                                                // Default: 512


#define RT_TIMER_TICK_PER_SECOND 100            // The soft-timer tick per second <0-1000>
                                                // Default: 100



/*******************************************************************************
        => IPC(Inter-process communication) 内部通信配置
*******************************************************************************/ 

#define RT_USING_SEMAPHORE                      // 信号量
//#define RT_USING_MUTEX                        // 互斥量
//#define RT_USING_EVENT                        // 事件
#define RT_USING_MAILBOX                        // 邮箱
#define RT_USING_MESSAGEQUEUE                   // 消息队列



/*******************************************************************************
        => Memory Management Configuration  内存管理配置
*******************************************************************************/

//#define RT_USING_MEMPOOL                      // 是否使用内存池
#define RT_USING_HEAP                           // 表示是否使用堆，使用动态内存时需要开启
#define RT_USING_SMALL_MEM                      // 是否使用小内存
//#define RT_USING_TINY_SIZE                    // 是否使用极小内存




/*******************************************************************************
        => Console Configuration  控制台配置
*******************************************************************************/
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE              128     // the buffer size of console <1-1024>
                                                // the buffer size of console
                                                // Default: 128 (128Byte)

#define RT_CONSOLE_DEVICE_NAME          “uart1” // <s>The device name for console
                                                // <i>The device name for console
                                                // <i>Default: uart1
                                                
                                                
//------------------------------------------------------------------------------                                     
#if defined(RTE_FINSH_USING_MSH)                // FINSH 配置
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_USING_MSH_ONLY

                                                // the priority of finsh thread
#define __FINSH_THREAD_PRIORITY         5       // the priority of finsh thread <1-7>
                                                // Default: 6

#define FINSH_THREAD_PRIORITY   (RT_THREAD_PRIORITY_MAX / 8 * __FINSH_THREAD_PRIORITY + 1)



#define FINSH_THREAD_STACK_SIZE         512     // the stack of finsh thread <1-4096>
                                                // the stack of finsh thread
                                                // Default: 4096 (4096Byte)



#define FINSH_HISTORY_LINES             1       // the history lines of finsh thread <1-32>
                                                // the history lines of finsh thread
                                                // Default: 5



#define FINSH_USING_SYMTAB                      // Using symbol table in finsh shell
                                                // Using symbol table in finsh shell

#endif
//------------------------------------------------------------------------------



#if defined(RTE_USING_DEVICE)                   // 设备配置
#define RT_USING_DEVICE
#endif                                             
                                                

#endif
