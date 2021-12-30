/*******************************************************************************
        => 时间管理数据结构
*******************************************************************************/
volatile INT32U         OSTime;         //任务控制块TCB中的OSTCBDly



/*******************************************************************************
        => 空闲任务
*******************************************************************************/
void OS_TaskIdle(void *p_arg)
{
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        
        p_arg = p_arg;          // 解除编译器警告
        for (;;) {
                OS_ENTER_CRITICAL();
                OSIdleCtr++;
                OS_EXIT_CRITICAL();
                OSTaskIdleHook();
        }
}


/*******************************************************************************
        => 统计任务
*******************************************************************************/
// 计算CPU的使用率
_________________________________________________________________
                            OSIdleCtr
OSCPUUsage = 100 * (1 -   -------------)    (uinits are in %)
                           OSIdleCtrMax
_________________________________________________________________
// 这个任务的优先级略高于空闲任务, 你可以通过配置文件来禁止它运行
//你需要至少 2/10 secconds 的延时时间。来让空闲任务建立计数时间。                          
void OS_TaskStat(void *p_arg)
{
        //Prevent compiler warning for not using 'p_arg'
        p_arg = p_arg;
        while (OSStatRdy == OS_FALSE) {
                // 等待统计任务准备就绪
                OSTimeDly(2u * OS_TICKS_PER_SEC / 10u); 
        }
        
        //最在空闲任务数缩小100
        OSIdleCtrMax /= 100uL;
        
        if (OSIdleCtrlMax == 0uL) {
                OSCPUUsage = 0u;
                for (;;) {
                        OSTimeDly(OS_TICKS_PER_SEC);
                }
        }
        for (;;) {
                OS_ENTER_CRITICAL();
                OSIdleCtrRun = OSIdleCtr; //获取上一秒空闲计数器的值
                OSIdleCtr    = 0u;        //重置下一秒的空闲计数器
                OS_EXIT_CRITICAL();
                OSCPUUsage   = (INT8U)(100uL - OSIdleCtrRun / OSIdleCtrMax);
                OSTaskStatHook();         //调用用户可定义的钩子      

                //在接下来的1/10秒内累积OSIdleCtr
                OSTimeDly(OS_TICKS_PER_SEC / 10);
        }
        
}

/*******************************************************************************
        => OSTimeDly()
*******************************************************************************/
void OSTimeDly(INT32U ticks)
{
        INT8U           y;
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        
        if (OSIntNesting > 0u) {        //See if trying to call from ISR
                return;
        }
        if (OSLockNesting > 0u) {       //See if called with scheduler locked
                return;
        }
        if (ticks > 0u) {               //0 means no delay
                OS_ENTER_CRITICAL();
                y            = OSTCBCur->OSTCBY; //Delay current task
                OSRdyTbl[y] &= (OS_PRIO)~OSTCBCur->OSTCBBitX;
                if (OSRdyTbl[y] == 0u) {
                        OSRdyGrp &= (OS_PRIO)~OSTCBCur->OSTCBBitY;
                }
                OSTCBCur->OSTCBDly = ticks;     //Load ticks in TCB
                OS_EXIT_CRITICAL();
                OS_Sched();                     //Find next task to run
        }
}

/*******************************************************************************
        => OSTimeDlyHMSM() 小时，分钟，秒，毫秒
*******************************************************************************/
INT8U OSTimeDlyHMSM (
                INT8U hours,
                INT8U minutes,
                INT8U seconds,
                INT8U ms)
{
        INT32U  ticks;
        
        if (OSIntNesting > 0u) {                //See fi trying to call from ISR
                return (OS_ERR_TIME_DLY_ISR);
        }
        if (OSLockNesting > 0u) {               //See if called with scheduler locked
                return (OS_ERR_SCHED_LOCKED);
        }
        
#if OS_ARG_CHK_EN > 0u
        if (hours == 0) {
                if (minutes == 0u) {
                        if (seconds == 0u) {
                                if (ms == 0u) {
                                        return (OS_ERR_TIME_ZERO_DLY);
                                }
                        }
                }
        }
        if (minutes > 59) {     //Validate arguments to be within range
                return (OS_ERR_TIME_INVALID_MINUTES);
        }
        if (seconds > 59) {
                return (OS_ERR_TIME_INVALID_SECONDS);
        }
        if (ms > 999u) {
                return (OS_ERR_TIME_INVALID_MS);
        }
#endif
        //compute the total number of clock ticks required ...
        //...(rounded to the nearest tick)返回一比较近似的时钟滴答数值
        //使用“500uL”这个数值，利用四舍五入法
        ticks = ((INT32U)houurs   * 3600uL              + \
                 (INT32U)minutes  * 60uL                + \
                 (INT32U)seconds) * OS_TICKS_PER_SEC    + \
        OS_TICKS_PER_SEC * ((INT32U)ms + 500uL / OS_TICKS_PER_SEC) / 1000uL;
        
        return (OS_ERR_NONE);              
}

/*******************************************************************************
        => OSTimeTick()
*******************************************************************************/
void OSTimeTick(void)
{
        OS_TCB          *ptcb;
        #if OS_TICK_STEP_EN > 0u
        BOOLEAN         step;
        #endif
        
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0;
        #endif
        
        #if OS_TIME_TICK_HOOK_EN > 0u
        OSTimeTickHook();
        #endif
        
        #if OS_TIME_GET_SET_EN > 0u
        OS_ENTER_CRITICAL();
        OSTime++;
        OS_EXIT_CRITICAL();
        #endif
        
        if (OSRunning == OS_TRUE) {
        #if OS_TICK_STEP_EN > 0
                switch (OSTickStepState) {
                case OS_TICK_STEP_DIS:
                        step            = OS_TRUE;
                        break;
                case OS_TICK_STEP_WAIT:
                        step            = OS_FALSE;
                        break;
                case OS_TICK_STEP_ONCE:
                        step            = OS_TRUE;
                        OSTickStepState = OS_TICK_STEP_WAIT;
                        break;
                default:
                        step            = OS_TRUE
                        OSTickStepState = OS_TICK_STEP_DIS;
                        break;
                }
                if (step == OS_FALSE) {
                        return;
                }
        #endif
        
                ptcb = OSTCBList;
                while (ptcb->OSTCBPrio != OS_TASK_IDLE_PRIO) {
                        OS_ENTER_CRITICAL();
                        if (ptcb->OSTCBDly != 0) {
                                ptcb->OSTCBDly--;
                                if (ptcb->OSTCBDly == 0u) {
                                
                                        if ((ptcb->OSTCBStat & OS_STAT_PEND_ANY) != OS_STAT_RDY) {
                                                ptcb->OSTCBStat &= (INT8U)~(INT8U)OS_STAT_PEND_ANY;
                                                ptcb->OSTCBStatPend = OS_STAT_PEND_TO;
                                        } else {
                                                ptcb->OSTCBStatPend = OS_STAT_PEND_OK;
                                        }
                                        if ((ptcb->OSTCBStat &OS_SATA_SUSPEND) == OS_STAT_RDY) {
                                                OSRdyGrp               |= ptcb->OSTCBBitY;
                                                OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
                                                
                                        }
                                        
                                }
                        }
                        ptcb = ptcb->OSTCBNext;
                        OS_EXIT_CRITICAL();
                }
        }           
}

/*******************************************************************************
        => OSTimeDlyResume()
*******************************************************************************/
// 可以强制让任务从阻塞态变成就绪态
INT8U OSTimeDlyResume(INT8U prio)
{
        OS_TCB  *ptcb;
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        
        //判断优先级是否合法，任务不能自己恢复自己
        //prio=255 忽略
        if (prio >= OS_LOWEST_PRIO) {
                return (OS_ERR_PRIO_INVALID);
        }
        OS_ENTER_CRITICAL();
        ptcb = OSTCBPrioTbl[prio];
        //参数检查
        if (ptcb == (OS_TCB *)0) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_NOT_EXIST);
        }
        // #define OS_TCB_RESERVED ((OS_TCB *)1)
        if (ptcb == OS_TCB_RESERVED) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TASK_NOT_EXIST);
        }
        if (ptcb->OSTCBDly == 0u) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_TIME_NOT_DLY);
        }
        
        ptcb->OSTCBDly = 0;             //Clear the time delay
        if ((ptcb->OSTCBStat & OS_STAT_PEND_ANY) != OS_STAT_RDY) {
                ptcb->OSTCBStat         &= ~OS_STAT_PEND_ANY; //Yes, Clear status flag
                ptcb->OSTCBStatPend      = OS_STAT_PEND_TO;   //Indicate PEND timeout
        } else {
                ptcb->OSTCBStatPend = OS_STAT_PEND_OK;
        }
        //判断任务是否被挂起，下面是处理任务没有挂起的代码
        if ((ptcb->OSTCBStat & OS_STAT_SUSPEND) == OS_STAT_RDY) { //Is task suspended?
                OSRdyGrp               |= ptcb->OSTCBBitY;        //NO, Make ready
                OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
                OS_EXIT_CRITICAL();
                OS_Sched();             //See if thid if new highest priority                       
        } else {
                OS_EXIT_CRITICAL();     //Task may be suspended
        }
        return (OS_ERR_NONE);
}