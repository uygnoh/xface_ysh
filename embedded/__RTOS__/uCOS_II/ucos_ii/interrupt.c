/*******************************************************************************
        => 中断处理流程
*******************************************************************************/
1. 开始
2. 调用（OSIntEnter()）将__OSIntNeating加“1”
3. 保存CPU寄存器内容到当前堆栈
4. 运行中断服务程序
5. 调用（OSIntExit()）将__OSIntNeating减“1”
6. 返回
/*******************************************************************************
        => 中断进入
*******************************************************************************/
void OSIntEnter(void)
{
        if (OSRunning == OS_TRUE) {
                if (OSIntNesting < 255u) {
                        OSIntNesting++;
                }
        }
}
/*******************************************************************************
        => 中断退出
*******************************************************************************/
void OSIntExit(void)
{
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        
        if (OSRunning == OS_TRUE) {
                OS_ENTER_CRITICAL();
                if (OSIntNesting > 0u) {
                        OSIntNesting--;
                }
                // 表示此中断已经是最外面一层了，系统中的中断服务程序全部执行完成
                if (OSIntNesting == 0u) {
                        // 如果这个调度器没有上锁，可以调度了
                        if (OSLockNesting == 0u) {
                                //找到当前就绪表中最高优先级的号码，并把它写在OSPrioHighRdy
                                OS_SchedNew();
                                //然后以OSPrioHighRdy为索引，找到就绪表中最高优先级的TCB指针
                                OSTCBHighRdy = OSTCBPrioTbl[OSPrioHighRdy];
                                
                                //如果最就绪表中最高优先级号码和当前任务的优先级号码不相等
                                if (OSPrioHighRdy != OSPrioCur) {
                                #if OS_TASK_PROFILE_EN > 0u
                                        OSTCBHighRdy->OSTCBCtxSwCtr++;
                                #endif
                                        //上下文计数器加1
                                        OSCtxSwCtr++;
                                        //触发PendSV异常，执行上下文切换
                                        OSIntCtxSw();
                                }
                        }
                }
                OS_EXIT_CRITICAL();
        }
}

