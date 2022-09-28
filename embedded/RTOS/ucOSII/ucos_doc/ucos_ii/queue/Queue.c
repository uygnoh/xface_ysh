/*******************************************************************************
        => 创建队列
*******************************************************************************/
//      TCB指向ECB
//      ECT指向QCB
//      QCB指向Message
//_____________________________________________________________
OS_EVENT *OSQCreate( void **start,
                     INT16U  size)
{
        OS_EVENT *pevent;               // 指向事件控制块的指针
        OS_Q     *pq;                   // 指向队列控制块的指针
        
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #ifdef OS_SAFETY_CRITICAL_IEC61508
        #if (OSSafetyCriticalStartFlag == OS_TRUE) {
                OS_SAFETY_CRITICAL_EXCEPTION();
        }
        #endif
        if (OSIntNesting > 0u) {
                return ((OS_EVENT *)0);
        }
        
        OS_ENTER_CRITICAL();
        pevent = OSEventFreeList;       // 从事件控制块的空闲链表中摘出一个事件控制块
        if (OSEventFreeList != (OS_EVENT *)0) {
                OSEventFreeList = (OS_EVENT *)OSEVentFreeList->OSEventPtr;
        }
        OS_EXIT_CRITICAL();
        if (pevent != (OS_EVENT *)0) {
                OS_ENTER_CRITICAL();
                pq = OSQFreeList;       // 从队列控制块的空闲链表中摘出一个链表来
                if (pq != (OS_Q *)0) {  // 拿到了队列控制块
                        OSQFreeList         = OSQFreeList->OSQPtr;
                        OS_EXIT_CRITICAL();
                        pq->OSQStart        = start;            // 消息队列起始位置
                        // &start[size] 表示最后一个元素的下一个地址
                        // pq->OSQEnd   它不是真正消息队列结束的位置
                        pq->OSQEnd          = &start[size];     // 消息队列结束位置
                        pq->OSQIn           = start;            // 入口
                        pq->OSQOut          = start;            // 出口
                        pq->OSQSize         = size;             // 大小
                        pq->OSEntries       = 0u;               // 入口数目
                        pevent->OSEventType = OS_EVENT_TYPE_Q;  // 事件类型（Q）
                        pevent->OSEventCnt  = 0u;               // 消息队列中（不使用）
                        pevent->OSEventPtr  = pq;               // 指向消息队列
                #if OS_EVENT_NAME_EN > 0u
                        pevent->OSEventName = (INT8U *)(void *)"?";
                #endif
                        OS_EventWaitListInit(pevent); // Initialize the wait list
                } else {
                        // 拿不到队列控制块（归还事件控制块到空闲链表中）
                        pevent->OSEventPtr = (void *)OSEventFreeList;
                        OSEventFreeList = pevent;
                        OS_EXIT_CRITICAL();
                        pevent = (OS_EVENT *)0;
                }
        }
        return (pevent);
}   



/*******************************************************************************
        => 申请消息队列
*******************************************************************************/
// TCB -> ECB -> QCB -> Message
// 任务通过事件控制块找到 => 队列控制块 => 再通过队列控制块去找到消息队列
//_____________________________________________________________
void *OSQPend( 
                OS_EVENT        *pevnet,        //事件控制块指针
                INT32U          timeout,
                INT8U           *perr)
{
        void    *pmsg;  //指向那条消息
        OS_Q    *pq;    //指向队列控制块
        
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #ifdef OS_SAFETY_CRITICAL
        if (perr == (INT8U *)0) {
                OS_SAFETY_CRITICAL_EXCEPTION();
        }
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0) {
                *perr = OS_ERR_PEVENT_NULL;
                return ((void *)0);
        }
        #endif
        if (pevent->OSEventType != OS_EVENT_TYPE_Q) {
                *perr = OS_ERR_EVENT_TYPE;
                return ((void *)0);
        }
        if (OSIntNesting > 0u) {
                *perr = OS_ERR_PEND_ISR;
                return ((void *)0);
        }
        if (OSLockNesting > 0u) {
                *perr = OS_ERR_PEND_LOCKED;
                return ((void *)0);
        }
        
        OS_ENTER_CRITICAL();
                                                // Point at queue control block
        pq = (OS_Q *)pevent->OSEventPtr;        // 拿到队列控制块的指针
        
        //如果消息队列中有可用的消息
        //_____________________________________________________
        if (pq->OSQEnteries > 0u) {             //See if any message in the queue
                                                //Yes, extract oldest message from the queue
                pmsg = *pq->OSQOut++;           //（首先拿到一条消息）然后再把OUT向后移一个位置
                                                //Update the number of entries int the queue
                pq->OSQEntries--;               //把消息数量减一个
                
                // Wrap OUT pointer if we are at hte end of the queue
                // pq->OSQEnd它指向消息队列的最后一个元素的（下一个），它不属于消息队列的范围了
                // 所以就把它赋值为（pq->OSQOut = pq->OSQStart;）
                if (pq->OSQOut == pq->OSQEnd) { 
                        pq->OSQOut = pq->OSQStart;
                }
                OS_EXIT_CRITICAL();
                *perr = OS_ERR_NONE;
                return (pmsg);
        }
        
        
        // 否则，消息队列中没有可以用的消息
        //_____________________________________________________
        //Task will have to pend for a message to be posted
        OSTCBCur->OSTCBStat     |= OS_STAT_Q;
        //
        OSTCBCur->OSTCBStatPend  = OS_STAT_PEND_OK;
        //Load timeout into TCB
        OSTCBCur->OSTCBDly       = timeout;
        //Suspend task until event or timeout occurs
        OS_EventTaskWait(pevent);
        
        OS_EXIT_CRITICAL();
        OS_Sched();
        OS_ENTER_CRITICAL();
        
        switch (OSTCBCur->OSTCBStatPend) {
        case OS_STAT_PEND_OK:
                 pmsg = OSTCBCur->OSTCBMsg;
                *perr = OS_ERR_NONE;
                break;
        case OS_STAT_PEND_ABORT:
                 pmsg = (void *)0;
                *perr = OS_ERR_PEND_ABORT;
                break;
        case OS_STAT_PEND_TO:
        default:
                OS_EventTaskRemove(OSTCBCur, pevent);
                pmsg  = (void *)0;
                *perr = OS_ERR_TIMEOUT;
                break;
        }
        
        // 任务控制块和事件控制块关系解除
        OSTCBCur->OSTCBStat             = OS_STAT_RDY;
        OSTCBCur->OsTCBStatPend         = OS_STAT_PEND_OK;
        OSTCBCur->OSTCBEventPtr         = (OS_EVENT *)0;
        #if (OS_EVENT_MULTI_EN > 0u)
        OsTCBCur->OSTCBEventMultiPtr    = (OS_EVENT **)0;
        #endif
        OSTCBCur->OSTCBMsg              = (void *)0;
        OS_EXIT_CRITICAL();
        return (pmsg);
}



/*******************************************************************************
        => 消息队列释放
*******************************************************************************/
INT8U OSQPost( OS_EVENT *pevnet,        //事件控制块
               void     *pmsg)          //要写入的消息
{
        OS_Q    *pq;
        
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0u) {
                return (OS_ERR_PEVENT_NULL);
        }
        #endif
        if (pevent->OSEventType != OS_EVENT_TYPE_Q) {
                return (OS_ERR_EVENT_TYPE);
        }
        
        OS_ENTER_CRITICAL();
                                        //如果有任务在等待这条消息，那么我就把这条消息给它
                                        //______________________________________
        if (pevent->OSEventGrp != 0u) { //See if any task pending on queue
                                        //Ready highest priority task waiting on event
                (void)OS_EventTaskRdy(pevent, pmsg, OS_STAT_Q, OS_STAT_PEND_OK);
                OS_EXIT_CRITICAL();
                OS_Sched();
                return (OS_ERR_NONE);
        }
                                        //如果没有任务在等待消息
                                        //______________________________________
        qp = (OS_Q *)pevent->OSEventPtr;        //Point to queue control block
        if (qp->OSQEntries >= pq->OSQSize) {    //判断消息队列消息是否为（满）
                OS_EXIT_CRITICAL();             //消息队列满
                return (OS_ERR_Q_FULL);
        }
        *pq->OSQIn++ = pmsg;                    //写入消息
        pq->OSQEntries++;                       //消息数目加（1）
        if (pq->OSQIn == pq->OSQEnd) {          //判断消息队列消息是否为（满）
                qp->OSQIn = pq->OSQStart;       //消息队列满（跳转到消息队列入口）
        }
        OS_EXIT_CRITICAL();
        return (OS_ERR_NONE);
}



/*******************************************************************************
        => 释放队列 OSQPostFront
*******************************************************************************/
// 这个函数释放的是 => 插入在队列的开头
//_____________________________________________________________
INT8U OSQPostFront( OS_EVENT *pevent,
                    void     *pmsg)
{
        OS_Q    *pq;
        
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_PEVENT *)0) {
                return (OS_ERR_PEVENT_NULL);
        }
        if (pevent->OSEventType != OS_EVENT_TYPE_Q) {
                return (OS_ERR_EVENT_TYPE);
        }
        
        OS_EVENT_CRITICAL();
        if (pevent->OSEventGrp != 0u) {
                (void)OS_EventTaskRdy(pevent, pmsg, OS_STAT_Q, OS_STAT_PEND_OK);
                OS_EXIT_CRITICAL();
                OS_Sched();
                return (OS_ERR_NONE);
        }
        pq = (OS_Q *)pevent->OSEvenetPtr;
        if (qp->OSQEnteries >= pq->OSQSize) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_Q_FULL);
        }

        //插入到下一个要出队的位置
        if (qp->OSQout == qp->OSQStart) {
                pq->OSQOut = qp->OSQEnd;
        }
        qp->OSQOut--;
        *pq->OSQOut = pmsg;
        pq->OSQEntries++;
        OS_EXIT_CRITICAL();
        return (OS_ERR_NONE);
}



/*******************************************************************************
        => OSQPostOpt
*******************************************************************************/
        #define OS_POST_OPT_NONE        0x00    // 没有选项
        #define OS_POST_OPT_BROADCAST   0x01    // 广播选项
        #define OS_POST_OPT_FRONT       0x02    // FRONT
        #define OS_POST_OPT_NO_SCHED    0x04    // 不要作调度
INT8U OSQPostOpt( OS_EVENT *pevent,
                  void     *pmsg,
                  INT8U     opt)
{
        OS_Q    *pq;
        
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0) {
                return (OS_ERR_PEVENT_NULL);
        }
        #endif
        if (pevent->OSEventType != OS_EVENT_TYPE_Q) {
                return (OS_ERR_EVENT_TYPE);
        }
        
        OS_ENTER_CRITICAL();
        if (pevent->OSEventGrp != 0x00u) {
                
                if ((opt & OS_POST_OPT_BROADCAST) != 0x00u) {
                        // 告诉所有申请（消息队列的任务）全部就绪
                        while (pevent->OSEventGrp != 0u) {
                                (void)OS_EventTaskRdy(pevent, pmsg, 
                                                OS_STAT_Q, OS_STAT_PEND_OK);
                        }
                } else {
                        // 告诉申请（消息队列的任务）优先级最高的任务就绪
                        (void)OS_EventTaskRdy(pevent, pmsg, OS_STAT_Q, 
                                                OS_STAT_PEND_OK);
                }
                OS_EXIT_CRITICAL();
                if ((opt & OS_POST_OPT_NO_SCHED) == 0x00u) {
                        OS_Sched();
                }
                return (OS_ERR_NONE);
        }
        
        // 没有任务申请这个消息
        pq = (OS_Q *)pevent->OSEventPtr;
        if (pq->OSQEntries >= pq->OSQSize) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_Q_FULL);
        }
        if ((opt & OS_POST_OPT_FRONT) != 0x00u) {
                if (pq->OSQOut == pq->OSQStart) {
                        pq->OSQOut = pq->OSQEnd;
                }
                qp->OSQOut--;
                *pq->OSQOut = pmsg;
        } else {
                *pq->OSQIn++ = pmsg;
                if (pq->OSQIn == pq->OSQEnd) {
                        pq->OSQIn = pq->OSQStart;
                }
        }
        qp->OSQEntries++;
        OS_EXIT_CRITICAL();
        return (OS_ERR_NONE);
}



/*******************************************************************************
        => 删除队列
*******************************************************************************/
OS_EVENT *OSQDel( OS_EVENT *pevent, 
                  INT8U     opt,
                  INT8U    *perr)
{
        BOOLEAN          tasks_waiting;
        OS_EVENT        *pevent_return;
        OS_Q            *pq;
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #ifdef OS_SAFETY_CRITICAL
        if (perr == (INT8U *)0) {
                OS_SAFETY_CRITICAL_EXCEPTION();
        }
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0) {
                *perr = OS_ERR_PEVENT_NULL;
                return (pevent);
        }
        #endif
        if (pevent->OSEventType != OS_EVENT_TYPE_Q) {
                *perr = OS_ERR_EVENT_TYPE;
                return (pevent);
        }
        if (OSIntNesting > 0u) {
                *perr = OS_ERR_DEL_ISR;
                return (pevent);
        }
        
        OS_ENTER_CRITICAL();
        if (pevent->OSEventGrp != 0u) {
                tasks_waiting = OS_TRUE;
        } else {
                tasks_waiting = OS_FALSE;
        }
        
        switch (opt) {
        // 如果没有任务在等，我在删除
        // ______________________
        case OS_DEL_NO_PEND:
                if (tasks_waiting == OS_FALSE) {
                        #if OS_EVENT_NAME_EN > 0u
                        pevent->OSEventName     = (INT8U *)(void *)"?";
                        #endif
                        // 归还队列控制块
                        pq                      = (OS_Q *)pevent->OSEventPtr;
                        pq->OSQPtr              = OSQFreeList;
                        OSQFreeList             = pq;
                        // 归还事件控制块
                        pevent->OSEventType     = OS_EVENT_TYPE_UNUSED;
                        pevent->OSEventPtr      = OSEventFreeList;
                        pevnet->OSEventCnt      = 0u;
                        OSEventFreeList         = pevent;
                        OS_EXIT_CRITICAL();
                        *perr                   = OS_ERR_NONE;
                        pevent_return           = (OS_EVENT *)0;
                } else {
                        OS_EXIT_CRITICAL();
                        *perr                   = OS_ERR_TASK_WAITING;
                        pevent_return           = pevnet;
                }
                break;
        // 不管有没有任务在等，都删除它
        // ______________________
        case OS_DEL_ALWAYS:
                while (pevent->OSEventGrp != 0) {
                                (void *)OS_EventTaskRdy(pevent, (void *)0, 
                                                OS_STAT_Q, OS_STAT_PEND_OK);
                }
                #if OS_EVENT_NAME_EN > 0u
                pevent->OSEventName     = (INT8U *)(void *)"?";
                #endif
                pq                      = (OS_Q *)pevent->OSEvenetPtr;
                pq->OSQPtr              = OSQFreeList;
                OSQFreeList             = pq;
                pevnet->OSEventType     = OS_EVENT_TYPE_UNUSED;
                pevent->OSEventPtr      = OSEventFreeList;
                pevnet->OSEventCnt      = 0u;
                OSEventFreeList         = pevent;
                OS_EXIT_CRITICAL();
                if (asks_waiting == OS_ERR_TRUE) {
                        OS_Sched();
                }
                *peer           = OS_ERR_NONE;
                pevnet_return   = (OS_EVENT *)0;
                break;    
        default:
                  OS_EXIT_CRITICAL();
                  *perr = OS_ERR_INVALID_OPT;
                  pevent_return = pevent;
                  break;
        }
        return (pevnet_return);
}



/*******************************************************************************
        => 清空消息队列
*******************************************************************************/
INT8U OSQFlush( OS_EVENT *pevent)
{
        OS_Q    *pq;
        #if OS_CRITICAL_METHOD == 3u;
        OS_CPU_SR cpu_sr = 0u;
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0) {
                return (OS_ERR_PEVENT_NULL);
        }
        if (pevent->OSEventType != OS_EVENT_TYPE_Q) {
                return (OS_ERR_EVENT_TYPE);
        }
        #endif
        
        OS_ENTER_CRITICAL();
        pq             = (OS_Q *)pevent->OSEventPtr;
        pq->OSQIn      = pq->OSQStart;
        pq->OSQOut     = pq->OSQStart;
        pq->OSQEntries = 0u;
        OS_EXIT_CRITICAL();
        return (OS_ERR_NONE);
}
