/*******************************************************************************
        => OSInit() 系统初始化函数
*******************************************************************************/
void OSInit(void)
{
        // 钩子函数给应用开发人员留下一个口子
        // 钩子函数用于留给应用开发人员编写特殊的处理程序
        // 可以把应用开发人员开发的程序，钩到uCOS-II操作系统中
        OSInitHookBegin();

        // 初始化杂项函数
        OS_InitMisc();

        // 初始化(就绪表, 就绪组)
        OS_InitRdyList();

        // 初始化TCB的空闲链表
        OS_InitTCBList();
        
        // 初始化结束钩子函数
        OSInitHookEnd();
}



/*******************************************************************************
        => 初始化杂项函数
*******************************************************************************/
void OS_InitMisc(void)
{
        OSIntNesting    = 0u;   // 中断嵌套的层数 (0表示中断没有嵌套)
        OSLockNesting   = 0u;   // 调度器锁计数器 (0表示调度器没有上锁)
        
        OSTaskCtr       = 0u;   // 任务计数器 (消除任务计数器)
        OSRunning       = OS_FALSE;//操作系统是否在运行
        
        OSCtxSwCtr      = 0u;   // 上下文切换计数器
        OSIdleCtr       = 0u;   // 空闲任务计数器
}



/*******************************************************************************
        => 初始化(就绪表, 就绪组， 任务优先级， 任务优先级指针)
*******************************************************************************/
void OS_InitRdyList(void)
{
        INT8U i;
        
        // 清除就绪组， 清除就绪表（OS_RDY_TBl_SIZE = 8）
        OSRdyGrp      = 0u;
        for (i = 0u; i < OS_RDY_TBl_SIZE; i++) {
                OSRdyTbl[i] = 0u;
        }
        
        // 当前正在执行任务的优先级
        OSPrioCur     = 0u;
        // 在就绪列表中，当前已经处于就绪状态的最高优先级的任务
        OSPrioHighRdy = 0u;
        
        // 最高就绪块中的TCB指针
        OSTCBHighRdy  = (OS_TCB *)0;
        // 当前正在运行正在运行任务的TCB指针
        OSTCBCur      = (OS_TCB *)0;
}



/*******************************************************************************
        => 初始化操作系统__空闲链表
*******************************************************************************/
void OS_InitTCBList(void)
{
        INT8U    ix;
        INT8U    ix_next;
        OS_TCB  *ptcb1;
        OS_TCB  *ptcb2;
        
        // 清除系统所有OS_TCB块（OSTCBTbl【】它是TCB的一个表格）
        // 它使用数组方式实现（TCB的空闲链表）
        OS_MemClr((INT8U *)&OSTCBTbl[0], sizeof(OSTCBTbl));
        // 清除系统所有OS_TCB优先级表
        OS_MemClr((INT8U *)&OSTCBPrioTbl[0], sizeof(OSTCBPrioTbl));
        
        // 初始化任务空闲链表
        for (ix = 0u; ix < (OS_MAX_TASKS + OS_N_SYS_TASKS - 1u); ix++) {
                ix_next = ix + 1u;
                ptcb1   = &OSTCBTbl[ix];
                ptcb2   = &OSTCBTbl[ix_next];
                ptcb1->OSTCBNext = ptcb2;
        }
        ptcb1           = &OSTCBTbl[ix];
        pcb1->OSTCBNext = (OS_TCB *)0;
        
        OSTCBList       = (OS_TCB*)0;
        OSTCBFreeList   = &OSTCBTbl[0];
}

void OS_MemClr(INT8U *pdest, INT16U size)
{
        while (size > 0u) {
                *pdest++ = (INT8U)0;
                size--;
        }
}



/*******************************************************************************
        => OS_TCBInit() 系统任务控制块初始化
*******************************************************************************/
INT8U OS_TCBInit(
                INT8U    prio,          // 任务的优先级
                OS_STK  *ptos,          // 指向栈顶指针
                OS_STK  *pbos,          // 指向栈底指针
                INT16U   id,            // 任务id
                INT32U   stk_size,      // 堆栈大小
                void    *pext,          //
                INT16    opt)           // 可选项
{
        OS_TCB  *ptcb;
        
        #if OS_CRITICAL_METHOD == 3u
                OS_CPU_SR cpu_sr = 0u;
        #endif
        
        OS_ENTER_CRITICAL();
        // Get a free TCB from the free TCB lis
        // 从空闲链表中摘出一个TCB块
        ptcb = OSTCBFreeList;
        
        // 如果空闲链表中有TCB块，则执行下面的语句
        if (ptcb != (OS_TCB *)0) {
                // Update pointer to free TCB list
                OSTCBFreeList       = ptcb->OSTCBNext;
                OS_EXIT_CRITICAL();
                
                ptcb->OSTCBStkPtr   = ptops;      //Load Stack pointer in TCB
                ptcb->OSTCBPrio     = prio;       //Load task priority into TCB
                ptcb->OSTCBStat     = OS_STAT_RDY;     // Task is ready to run
                ptcb->OSTCBStatPend = OS_STAT_PEND_OK; // clear pend status
                ptcb->OSTCBDly      = 0u;              // task is not delayed
                
                // 以下5条语句是没有任何意义操作，只是为了抑制警告！！！
                pext                = pext;
                stk_size            = stk_size;
                pbos                = pbos;
                otp                 = opt;
                id                  = id;
        //_____________________________________________________________
        //任务就绪掩码计算( 64位优先级只用到“6”位二进制数 ) （高3位 + 低3位）
        // 00     111     111
        //_____________________________________________________________
                #if OS_LOWEST_PRIO <= 63u
                // 高“3”位对应就绪表中的行 | 也对应(INT8U OSRdyGrp)就绪组中的“位号”
                // 低“3”位对应就绪表中的列 
                ptcb->OSTCBY       = (INT8U)(prio >> 3u);  //取出优先级高3位(行)索引
                ptcb->OSTCBX       = (INT8U)(prio & 0x07u);//取出优先级低3位(列)索引
                #endif
                // OSTCBBitY: 就绪组中位的掩码
                // OSTCBBitX: 就绪表中，以就绪就绪组中位的掩码为索引，对应位的掩码
                ptcb->OSTCBBitY     = (OS_PRIO)(1uL << ptcb->OSTCBY);
                ptcb->OSTCBBitX     = (OS_PRIO)(1uL << ptcb->OSTCBX);
                
                
                OSTCBInitHook(ptcb);
                OSTaskCreateHook(ptcb); // Call user defined hook
                
                
                OS_ENTER_CRITICAL();
                // 任务的ptcb赋值给OSTCBPrioTbl[prio]
                OSTCBPrioTbl[prio]   = ptcb;
                // 使用头插法，插入一个节点
                ptcb->OSTCBNext      = OSTCBList;
                ptcb->OSTCBPrev      = (OS_TCB *)0;
                // 如果链表中不只一个节点的话
                if (OSTCBList != (OS_TCB *)0) {
                        OSTCBList->OSTCBPrev = ptcb;
                }
                OSTCBList             = ptcb;
                
                
                // 让任务处于就绪状态_________________________
                OSRdyGrp               |= ptcb->OSTCBBitY;
                OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
                OSTaskCtr++;
                OS_EXIT_CRITICAL();
                return (OS_ERR_NONE);
        }
        OS_EXIT_CRITICAL();
        
        return (OS_ERR_TASK_NO_MORE_TCB);
}



/*******************************************************************************
        => ARM-CM3 任务栈初始化
        => 在任务第一次初始化的时候模拟CPU保存栈帧的顺序
*******************************************************************************/
OS_STK *OSTaskStkInit(
                void (*task)(void *p_arg), 
                void *p_arg, 
                OS_STK *ptos,
                INT16U opt)
{
        OS_STK *stk;
        
        (void)opt;
        stk             = ptos;
        
        // Registers stacked as if auto-saved on exception
        *(stk)          = (INT32U)0x01000000L;    // xPSR
        *(--stk)        = (INT32U)task;           // R15( PC )
        *(--stk)        = (INT32U)0xFFFFFFFEL;
        *(--stk)        = (INT32U)0x12121212L;
        *(--stk)        = (INT32U)0x03030303L;
        *(--stk)        = (INT32U)0x02020202L;
        *(--stk)        = (INT32U)0x01010101L;
        *(--stk)        = (INT32U)p_arg;          // R0
        
        // Remaining registers saved on process stack
        *(--stk)        = (INT32U)0x11111111L;
        *(--stk)        = (INT32U)0x10101010L;
        *(--stk)        = (INT32U)0x09090909L;
        *(--stk)        = (INT32U)0x08080808L;
        *(--stk)        = (INT32U)0x07070707L;
        *(--stk)        = (INT32U)0x06060606L;
        *(--stk)        = (INT32U)0x05050505L;
        *(--stk)        = (INT32U)0x04040404L;
        
        return (stk);
}


/*******************************************************************************
        => uCOS-II 创建任务
*******************************************************************************/
/*
 创建任务可以在uCOS-II启动时创建任务，也可以是被一个正在运行的任务创建
        一个任务不可以在中断服务程序(ISR)中创建!!!
        每一个任务都被分配一个唯一的优先级号!!!
        优先级号码越低，优先级越高!!!
*/

INT8U OSTaskCreate(void   (*task)(void *p_arg),
                   void   *p_arg;
                   OS_STK *ptos,
                   INT8U   prio)
{
        OS_STK  *psp;
        INT8U    err;

        OS_ENTER_CRITICAL();
        // (OSIntNesting > 0u)表示当前正在中断服务程序中
        if (OSIntNesting > 0u) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_CREATE_ISR);
        }
        
        // 如果正在创建的那个任务的优先级的TCB指针为空指针
        // 那就表示这个任务不存在，那么就可以创建这个任务
        if (OSTCBPrioTbl[prio] == (OS_TCB *)0) {
                // OS_TCB_RESERVED = (OS_TCB *)1; 先占个位置
                OSTCBPrioTbl[prio] = OS_TCB_RESERVED;
                
                OS_EXIT_CRITICAL();
                // 初始化任务栈帧
                psp = OSTaskStkInit(task, p_arg, ptos, 0u);
                // 初始化TCB块
                err = OS_TCBInit(prio, psp, (OS_STK *)0, 0u, 0u, (void *)0, 0u);
                
                // 如果有多余的TCB块
                if (err == OS_ERR_NONE) {
                        if (OSRunning == OS_TRUE) {
                                OS_Sched();
                        }
                // 如果没有多余的TCB块
                } else {
                        OS_ENTER_CRITICAL();
                        OSTCBPrioTbl[prio] = (OS_TCB *)0;
                        OS_EXIT_CRI_CRITICAL();
                }
                return (err);
        }
        OS_EXIT_CRITICAL();
        return (OS_ERR_PRIO_EXIST);
}


/*******************************************************************************
        => uCOS-II 删除任务
*******************************************************************************/
/*
Descriptions:
        正在运行的任务可以删除它自己，通过指定它自己的优先级号码
        删除的任务转换为休眠态，通过再次创建它，它可以被重新激活
        你可以明确的删除当前的任务，你可以不需要知道当前任务的优
        先级别号码. 通过设置“OS_PRIO_SELF(255)”这个宏来删除它自己。

Task Return status： 
        OS_ERR_NONE          成功执行
        OS_ERR_TASK_DEL_IDLE 不能删除空闲任务
        OS_ERR_PRIO_INVALID  任务优先级无效
        OS_ERR_TASK_DEL      如果这个任务被分配到 互斥进程提升
        OS_ERR_NOT_EXIST     任务不存在
        OS_ERR_TASK_DEL_ISR  不能从中断服务程序中删除任务

Notes   :
        1) 为了减少中断的延时，它可以禁用这个任务
                a）你可以让你要禁用的任务处于“不就绪状态”
                b）把它从任何的等待列表中移出
                c）通过阻止OSTimeTick(), 不让它运行
           这个任务可以通过从杂项中的数据结构与它解除掉
        2) OS_Dummy()在退出临界区前被调用，是因为大多数处
           理器在退出临界区可能会改变中断的状态，开中断的下
           一条指令通常在大多数处理器上会忽略掉。
        3) 这个任务不能从中断中删除
        4) 这个嵌套中断锁会加“1”，当这个任务自己删除自己时。
           如果当前任务要删除自身，那么需要用“调度器上锁”来阻止任务调度
           因为任务删除自身，再也不会被任务调度了，它回不来了，但是这个
           任务后面还有一部分代码没有被执行，那么任务就不能删除干净了。
*/

INT8U OSTaskDel(INT8U prio)
{
        OS_TCB  *ptcb;
        
        // 判断是否在中断服务函数中
        if (OSIntNesting > 0u) {
                return (OS_ERR_TASK_DEL_ISR);
        }
        // 判断是否为空闲任务
        if (prio == OS_TASK_IDLE_PRIO) {
                return (OS_ERR_TASK_DEL_IDLE);
        }
        // 判断优先级号码是否合法
        if (prio >= OS_LOWEST_PRIO) {
                if (prio != PRIO_SELF) {
                        return (OS_ERR_PRIO_INVALID);
                }
        }
        OS_ENTER_CRITICAL();
        // 判断是否是删除自己
        if (prio == OS_PRIO_SELF) {
                prio = OSTCBCur->OSTCBPrio;
        }
        ptcb = OSTCBPrioTbl[prio];
        // 判断TCB块指针是否为空，如果为空表示删除的任务不存在
        if (ptcb == (OS_TCB *)0) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_NOT_EXIST);
        }
        // 判断TCB指针是否分配给了进程提升优先级(Mutex PIP)
        if (ptcb == OS_TCB_RESERVED) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_DEL);
        }
        
        
        // 要让删除的任务处于非就绪态( 清除要删除任务的就绪表和就绪组 )
        OSRdyTbl[ptcb->OSTCBY] &= (OS_PRIO)~ptcb->OSTCBBitX;
        if (OSRdyTabl[ptcb->OSTCBY] == 0u) {
                OSRdyGrp       &= (OS_PRIO)~ptcb->OSTCBBitY;
        }
        
        // 把TCB字段设置为相应的状态
        ptcb->OSTCBDly          = 0u;             // Prevent OSTimeTick() from updating
        ptcb->OSTCBStat         = OS_STAT_RDY;    // Prevent task from beging resumed
        ptcb->OSTCBStatPend     = OS_STAT_PEND_OK;
        
        // 为了防止任务调度
        if (OSLockNesting < 255u) {     // Make sure we don't context switch
                OSLockNesting++;
        }
        OS_EXIT_CRITICAL();             // Enabling INT. ignores next instruc.
        OS_Dummy();                     // ... Dummy ensures that INTs will be
        OS_ENTRY_CRITICAL();            // .... disabled HERE!
        if (OSLockNesting > 0u) {       // Remove context switch lock
                OSLockNesting--;
        }
        OSTaskDelHook(ptcb);
        OSTaskCtr--;
        OSTCBPrioTbl[prio] = (OS_TCB *)0;
        
        // 从任务TCB的就绪链表还给任务TCB空闲链表
        // 如果要删除的链表是第一个的话
        if (ptcb->OSTCBPrev == (OS_TCB *)0) {
                ptcb->OSTCBNext->OSTCBPrev = (OS_TCB *)0;
                OSTCBList                  = ptcb->OSTCBNext;
        } else {
                ptcb->OSTCBPrev->OSTCBNext = ptcb->OSTCBNext;
                ptcb->OSTCBNext->OSTCBPrev = ptcb->OSTCBPrev;
        }
        ptcb->OSTCBNext = OSTCBFreeList;
        OSTCBFreeList   = ptcb;
        OS_EXIT_CRITICAL();
        if (OSRunning == OS_TRUE) {
                OS_Sched();             // Find new highest priority task
        }
        return (OS_ERR_NONE);
}



/*******************************************************************************
        => uCOS-II 任务挂起
*******************************************************************************/
/*
Description:
        这个任务挂起函数，可以挂起自己，也可以挂起其它的任务
Returns:
        OS_ERR_NONE     
        OS_ERR_TASK_SUSPEND_IELE        不能挂起空闲任务
        OS_ERR_PRIO_INVALID             挂起的任务优先级号不合法
        OS_ERR_TASK_SUSPEND_PRIO        这个要挂起的任务不存在
        OS_ERR_TASK_NOT_EXITS           如果这个任务分配给了进程提升优先级
                                        (if the task is assigned to a Mutex PIP)   
Note:
        你使用这个OSTaskSuspend函数要特别的小心， 如果你挂起的任务在等待事件
        (例如：消息，信号量。。。)， 即使你等待的事件到了，它也会阻止它运行。
*/

INT8U OSTaskSuspend(INT8U prio)
{
        BOOLEAN         self;
        OS_TCB          *ptcb;
        INT8U           y;
        
        // 判断是不是空闲任务
        if (prio == OS_TASK_IDLE_PRIO) {
                return (OS_ERR_TASK_SUSPEND_IDLE);
        }
        // 判断优先给是否合法
        if (prio >= OS_LOWEST_PRIO) {
                if (prio != OS_PRIO_SELF) {
                        return (OS_ERR_PRIO_INVALID);
                }
        }
        OS_ENTER_CRITICAN();
        // 判断优先级号码是不是255
        if (prio == PRIO_SELF) {
                prio = OSTCBCur->OSTCBPrio;
                self = OS_TRUE;
        // 判断是否是自己的优先级号码
        } else if (prio == OSTCBCur->OSTCBPrio) {
                self = OS_TRUE;
        } else {
                self = OS_FALSE;
        }
        
        ptcb = OSTCBPrioTbl[prio];
        // 判断要挂起的任务是否存在
        if (ptcb == (OS_TCB *)0) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_SUSPEND_PRIO);
        }
        // 判断TCB指针是否分配给了进程提升优先级(Mutex PIP)
        if (ptcb == OS_TCB_RESERVED) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_NOT_EXIST);
                
        }
        
        
        // 删除要挂起任务的： 就绪组和就绪表对应的位清零
        y           &= ptcb->OSTCBY;
        OSRdyTbl[y] &= (OS_PRIO)~ptcb->OSTCBBitx;
        if (OSRdyTbl[y] == 0u) {
                OSRdyGrp &= (OS_PRIO)~ptcb->OSTCBBitY;
        }
        
        // 设置要挂起的任务为： 挂起状态
        ptcb->OSTCBStat |= OS_STAT_SUSPEND;
        OS_EXIT_CRITICAL();
        if (self == OS_TRUE) {
                OS_Sched();
        }
        
        return (OS_ERR_NONE);
}



/*******************************************************************************
        => uCOS-II 任务恢复
*******************************************************************************/
/*
Description:
        只有任务挂起了，才能使用这个函数，任务不能自己恢复自己
returns:
        OS_ERR_NONE                   任务恢复成功执行  
        OS_ERR_PRIO_INVALID           要恢复任务优先级号码是非法的  
        OS_ERR_TASK_RESUME_PRIO       要恢复任务的优先级不存在
        OS_ERR_TASK_NOT_EXIST         if the task to assigne to a Muttex PIP
        OS_ERR_TASK_NOT_SUSPENDED     if the task to resume has not been suspended
*/

INT8U OSTaskResume(INT8U prio)
{
        OS_TCB  *ptcb;
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        
        if (prio >= OS_LOWEST_PRIO) {
                return (OS_ERR_PRIO_INVALID);
        }
        OS_ENTER_CRITICAL();
        ptcb = OSTCBPrioTbl[prio];
        if (ptcb == (OS_TCB *)0) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_RESUME_PRIO);
        }
        if (ptcb == OS_TCB_RESERVED) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_NOT_EXIST);
        }
        
        // 如果任务被挂起 //
        if ((ptcb->OSTCBStat & OS_STAT_SUPEND) != OS_STAT_RDY) {
                ptcb->OSTCBStat &= (INT8U)~(INT8U)OS_STAT_SUPEND;
                if (ptcb->OSTCBStat == OS_STAT_RDY) {
                        if (ptcb->OSTCBDly == 0u) {
                        //设置就绪组，就绪表，使任务处于就绪状态
                                OSRdyGrp               |= ptcb->OSTCBBitY;
                                OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
                                OS_EXIT_CRITICAL();
                                if (OSRunning == OS_TRUE) {
                                        OS_Sched();
                                }
                        } else {
                                OS_EXIT_CRITICAL();
                        }
                } else {
                        OS_EXIT_CRITICAL();
                }
                return (OS_ERR_NONE);
        }
        // 如果这个任务没有挂起 //
        OS_EXIT_CRITICAL();
        return (OS_ERR_TASK_NOT_SUSPENDED);
}



/*******************************************************************************
        => OSStart() 系统启动
*******************************************************************************/
/*
Description:
        这个函数用于启动多任务进程，助于管理uCOS-II创建的任务
        在调用OSStart()函数之前，必须先调用OSInit()函数
        你至少创建一个任务
Note:
        OSStartHighRdy() 必须要：
        1) Call OSTaskSwHook()
        2) Set OSrunning to OS_TRUC.
        3) Load the context of the task pointed to by OSTCBHighRdy.
        4) Execte the task
*/
void OSStart(void)
{
        if (OSRunning == OS_FALSE) {
                // 查找最高优先级任务的（优先级号码）
                OS_SchedNew();
                OSPrioCur = OSPrioHighRdy;
                // Point to highest priority task ready to run
                OSTCBHihgRdy = OSTCBPrioTbl[OSPrioHighRdy];
                OSTCBCur = OSTCBHighRdy;
                // Execute target specific code to start task
                OSStartHighRdy();
        }
}



/*******************************************************************************
        => OS_SchedNew() 
*******************************************************************************/
1. 这个函数是内部函数，你的应用程序不应该调用它
2. 在调用这个函数时，假定中断是被禁用的
// 查找uCOS-II系统当前就绪表中那个优先级最高， 返回那个最高优先级的号码
// 它是一个静态函数，只能在文件内部被调用（你的应用程序不应该调用它！！！）
// 下面用的( uCOS-II 优先级判定表算法 ), 只能支持 0~63 个任务优先级
static void OS_SchedNew(void)
{
        INT8U y;
        // 1) 以就绪组中的内容为索引，去查“y”值
        y             = OSUnMapTbl[OSRdyGrp];
        // 2) {【然后以“y”值为索引，去把就绪表中的那一行那过来】
        //     , 以此作为索引查OSUnMapTbl[x].} + (y<<3) 
        OSPrioHighRdy = (INT8U)((y << 3u) + OSUnMapTbl[OSRdyTbl[y])
}
