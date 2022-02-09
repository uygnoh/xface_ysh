/*******************************************************************************
        => 消息邮箱只能保存一条消息
        => 消息邮箱创建
*******************************************************************************/
//pmsg传递消息的内容
OS_EVENT *OSMboxCreate(void *pmsg)
{
        OS_EVENT *pevent;
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u;
        #endif
        
        #ifdef OS_SAFETY_CRITICAL_IEC61508
        if (OSSafetyCriticalStartFlag == OS_TRUE) {
                OS_SAFETY_CRITICAL_EXCEPTION();
        }
        if (OSIntNesting > 0u) {
                return ((OS_EVENT *)0);
        }
        
        OS_ENTER_CRITICAL();
        pevent = OSEventFreeList;               //Get next free event control block
        if (OSEventFreeList != (OS_Event *)0) { //See if pool of free ECB pool was empty
                OSEventFreeList = (OS_Event *)OSEventFreeList->OSEventPtr;
        }
        OS_EXIT_CRITICAL();
        if (pevnet != (OS_EVENT *)0) {
                pevent->OSEeventType    = OS_EVENT_TYPE_MBOX;
                pevent->OSEventCnt      = 0u;
                pevent->OSEventPtr      = pmsg; //Deposit message in event control block
        #if OS_EVENT_NAME_EN > 0u
                pevent->OSEventName     = (INT8U *)(void *)"?";
        #endif
                OS_EventWaitListInit(pevent);
        }
        return (pevent); //Return pointer to event control block
}

#if (OS_EVENT_EN)
void OS_EventWaitListInit(OS_EVENT *pevent)
{
        INT8U i;
        pevent->OSEventGrp = 0u; //No task waiting on event
        for (i = 0; i < OS_EVENT_TBL_SIZE; i++) {
                pevent->OSEvnetTbl[i] = 0u;
        }
}

/*******************************************************************************
        => 消息邮箱申请
*******************************************************************************/
void *OSMboxPend( OS_EVENT *pevent, 
                  INT32U timeout, 
                  INT8U *perr)
{
        void *pmsg;
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u
        #endif
        #ifndef OS_SAFETY_CRITICAL
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
        if (pevnet->OSEventType != OS_EVENT_TYPE_MBOX) {
                *perr = OS_ERR_EVENT_TYPE;
                return ((void *)0);
        }
        if (OSIntNesting > 0u) {
                *perr = OS_ERR_PEND_ISR;
                return ((void *)0);
        }
        
        OS_ENTER_CRITICAL();
        pmsg = pevent->OSEventPtr;
        //如果消息邮箱有消息， 那么把里面的消息取走
        if (pmsg != (void *)0) {                //see if there is already a message
                pevent->OSEventPtr = (void *)0; //Clear the mailbox
                OS_EXIT_CRITICAL();
                *perr = OS_ERR_NONE;
                return (pmsg);
        }
        //否则，我申请的消息不存在，那么把当前任务阻塞掉
        OSTCBCur->OSTCBStat     |= OS_STAT_MBOX;
        OSTCBCur->OSTCBStatPend  = OS_STAT_PEND_OK;
        OSTCBCur->OSTCB          = timeout;
        OS_EventTaskWait(pevent);
        OS_EXIT_CRITICAL();
        OS_Sched();
        OS_ENTER_CRITICAL();
        switch (OSTCBCur->OSTCBStatPend) {
        case OS_STAT_PEND_OK:                   //消息等到了
                 pmsg = OSTCBCur->OSTCBMsg;
                *perr = OS_ERR_NONE;
                break;
        case OS_STAT_PEND_ABORT:                //强行终止了
                 pmsg = (void *)0;
                *perr = OS_ERR_PEND_ABORT;
                break;
        case OST_STAT_PEND_TO:                  //超时
        default:
                OS_EventTaskRemove(OSTCBCur, pevent);
                 pmsg = (void *)0;
                *perr = OS_ERR_TIMEOUT;
                break;
        }
        //解除当前任务与那个事件的关系
        OSTCBCur->OSTCBStat     = OS_STAT_RDY;
        OSTCBCur->OSTCBStatPend = OS_STAT_PEND_OK;
        OSTCBCur->OSTCBEventPtr = (OS_EVENT *)0;
        #if (OS_EVENT_MULTI_EN > 0u)
        OSTCBCur->OSTCBEventMultiPtr = (OS_EVENT **)0;
        #endif
        OSTCBCur->OSTCBMsg      = (void *)0;    //clear received message
        return (pmsg);                          //Return received message      
}

/*******************************************************************************
        => 消息邮箱释放
*******************************************************************************/
INT8U OSMboxPost(OS_EVNET *pevnet, void *pmsg)
{
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cpu_sr = 0u
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0) {
                return (OS_ERR_PEVENT_NULL);
        }
        if (pmsg == (void *)0) {
                return (OS_ERR_POST_NUL_PTR);
        }
        #endif
        if (pevnet->OSEventType != OS_EVENT_MBOX) {
                return (OS_ERR_EVENT_TYPE);
        }
        
        OS_ENTER_CRITICAL();
        //如果有别的任务在申请这个消息邮箱， 那么把这条消息给它
        if (pevent->OSEventGrp !=0) {
                (void)OS_EventTaskRdy(pevent, pmsg, OS_STAT_MBOX, OS_STAT_PEND_OK);
                OS_EXIT_CRITICAL();
                OS_Sched();
                return (OS_ERR_NONE);
        }
        //如果这条消息没有被取走，那么不能写入这条消息
        if (pevnet->OSEvnetPtr != (void *)0) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_MBOX_FULL);
        }
        //消息邮箱中没有消息，那么就写入这条消息
        pevnet->OSEventPtr = pmsg;
        OS_EXIT_CRITICAL();
        return (OS_ERR_NONE);
}

/*******************************************************************************
        => 消息邮箱释放Opt
*******************************************************************************/
INT8U OSMboxPostOpt(OS_EVENT *pevent
                    void *pmsg,
                    INT8U opt)
{
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR cp_sr = 0u;
        #endif
        #if OS_ARG_CHK_EN > 0
        if (pevent == (OS_EVENT *)0) {
                return (OS_ERR_PEVENT_NULL):
        }
        if (pmsg == (void *)0) {
                return (OS_ERR_POST_NULL_PTR);
        }
        #endif
        
        if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {
                return (OS_ERR_EVENT_TYPE);
        }
        OS_ENTER_CRITICAL();
        //表明有任务在申请我所释放的这条消息
        if (pevent ->OSEventGrp != 0) {
                //广播方式通知所有申请这个消息的任务
                if ((opt & OS_POST_OPT_BROADCAST) != 0x00u) {
                        while (pevent->OSEventGrp != 0u) {
                                (void)OS_EventTaskRdy(pevnet, pmsg, OS_STAT_MBOX, OS_STAT_PEND_OK);
                        }
                } else {
                        (void)OS_EventTaskRdy(pevent, pmsg, OS_STAT_MBOX, OS_STAT_PEND_OK);
                }
                OS_EXIT_CRITICAL();
                if ((opt & OS_POST_OPT_NO_SCHED) == 0u) {
                        OS_Sched();
                }
                return (OS_ERR_NONE);
        }
        if (pevent->OSEvent != (void *)0) {
                OS_EXIT_CRITICAL();
                return (OS_ERR_MBOX_FULL);
        }
        pevnet->OSEventPtr = pmsg;      //Place message in mailbox
        OS_EXIT_CRITICAL();
        return (OS_ERR_NONE);
}

/*******************************************************************************
        => 消息邮箱删除
*******************************************************************************/
OS_EVENT *OSMboxDel(OS_EVENT *pevnet,
                    INT8U opt,
                    INT8U *perr)
{
        BOOLEAN tasks_waiting;
        OS_EVENT *pevent_return;
        #if OS_CRITICAL_METHOD == 3u
        OS_CUP_SR cpu_sr = 0u;
        #endif
        
        #ifdef OS_SAFETY_CRITICAL
        if (perr == (INT8U *)0) {
                OS_SAFETY_CRITICAL_EXCEPTION();
        }
        #endif
        #if OS_ARG_CHK_EN > 0u
        if (pevent == (OS_EVENT *)0u) {
                *perr = OS_ERR_PEVENT_NULL;
                return (pevent);
        }
        #endif
        
        if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {
                *perr = OS_ERR_EVENT_TYPE;
                return (pevent);
        }
        if (OSIntNesting > 0u){
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
        case OS_DEL_NO_PEND:    //没有任务申请的时候我在删除
                if (tasks_waiting == OS_FALSE) {
                #if OS_EVENT_NAME_EN > 0u
                        pevent->OSEventName = (INT8U *)(void *)"?";
                #endif
                        pevent->OSEventType = OS_EVENT_TYPE_UNUSED;
                        pevnet->OSEventPtr  = OSEventFreeList;
                        pevnet->OSEventCnt  = 0u;
                        OSEventFreeLsit     = pevent;
                        OS_EXIT_CRITICAL();
                        *perr               = OS_ERR_NONE;
                        pevnet_return       = (OS_EVENT *)0;
                } else {
                        OS_EXIT_CRITICAL();
                        *perr               = OS_ERR_TASK_WAITING;
                        pevent_return       = pevent;
                }
                break;
        case OS_DEL_ALWAYS:     //不管有没有任务在申请我都删除它
                while (pevent->oSEventGrp != 0u) {
                        (void)OS_EventTaskRdy(pevent, (void *)0, OS_STAT_MBOX, OS_STAT_PEND_OK);
                }
                #if OS_EVENT_NAME_EN > 0u
                        pevent->OSEventName = (INT8U *)(void *)"?";
                #endif
                pevent->OSEventType         = OS_EVENT_TYPE_UNUSED;
                pevent->OSEventPtr          = OSEventFreeList;
                pevnet->OSEventCnt          = 0u;
                OSEventFreeList             = pevent;
                OS_EXIT_CRITICAL();
                if (task_waiting == OS_TRUE) {
                        OS_Sched();
                }
                *perr         = OS_ERR_NONE;
                pevent_return = (OS_EVENT *)0;
                break
        default:        //参数错误
                OS_EXIT_CRITICAL();
                *perr         = OS_ERR_INVALID_OPT;
                pevent_return = pevent;
                break;
        }
        return (pevent_return);
}
