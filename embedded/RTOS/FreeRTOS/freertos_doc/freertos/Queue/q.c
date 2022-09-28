/*******************************************************************************
                              FreeRTOS-队列创建
1 判断队列需要多在内存， xQueueSizeInBytes = uxQueueLength * uxItemSize
2 为队列申请内存，申请多大？ sizeof(Queue_t)队列结构体大小 + xQueueSizeInBytes队列大小  
3 判断内存是否申请成功？ 如果成功的话计算出队列存储区的首地址。
4 调用prvInitialiseNewQueue(),初始化新的队列pxNewQueue;
*******************************************************************************/
QueueHandle_t xQueueGenericCreate(
        const UBaseType_t uxQueueLength, 
        const UBaseType_t uxItemSize, 
        const uint8_t ucQueueType)
{
        Queue_t *pxNewQueue;
        size_t xQueueSizeInBytes;
        uint8_t *pucQueueStorage;
        
        //判断一下队列项是不是 == 0
        //它对应的是信号量
        if (uxItemSize == (UBaseType_t)0) {
                xQueueSizeInBytes = (size_t)0;
        //统计队列总字节数， 它对应的是队列
        } else {
                xQueueSizeInBytes = (size_t)(uxQueueLength * uxItemSize);
        }  
        pxNewQueue = (Queue_t *)pvPortMalloc(sizeof(Queue_t) + xQueueSizeInBytes);
        if (pxNewQueue != NULL) {
                //计算队列存储区的首地址
                pucQueueStorage = ((uint8_t *)pxNewQueue) + sizeof(Queue_t);
        }
        
        #if (configSUPPOrT_STATIC_ALLOCATION == 1)
        pxNewQueue->ucStaticallyAllocated = pdFALSE;
        #endif
        
        prvInitialiseNewQueue(uxQueueLength, uxItemSize, pucQueueStorage, ucQueueType, pxNewQueue);
        
        return pxNewQueue;
}



/*******************************************************************************
                              FreeRTOS-队列初始化
1 初始化队列结构体相关成员变量
2 调用xQueueGenericReset()复位队列
*******************************************************************************/
prvInitialiseNewQueue(
        uxQueueLength, uxItemSize, pucQueueStorage, ucQueueType, pxNewQueue)
{
        //用于信号量
        if (uxItemSize == (UBaseType_t)0) {
                pxNewQueue->pcHead = (int8_t *)pxNewQueue;
        //用于队列
        } else {
                pxNewQueue->pcHead = (int8_t *)pucQueueStorage;
        }
        
        pxNewQueue->uxLength = uxQueueLength;
        pxNewQueue->uxItemSize = uxItemSize;
        (void)xQueueGenericReset(pxNewQueue, pdTRUE);
}



/*******************************************************************************
                              FreeRTOS-队列复位函数
1 初始化其它队结构体成员变量
2 判断要复位的队列是否为新创建的队列，如果不是需要处理相应的列表xTaskWaitingToSend
3 如果要复位的是新创建的队列，初始化列表xTasksWaitingToSend和xTasksWaitingToReceive
*******************************************************************************/
BaseType_t xQueueGenericReset(QueueHandle_t xQueue, BaseType_t xNewQueue)
{
        Queue_t *const pxQueue = (Queue_t *)xQueue;
        taskENTER_CRITICAL();
        pxQueue->pcTail = pxQueue->pcHead + (pxQueue->uxLength * pxQueue->uxItemSize);
        pxQueue->uxMessagesWaiting = (UBaseType_t)0U;
        pxQueue->pcWriteTo = pxQueue->pcHead;
        pxQueue->u.pcReadFrom = pxQueue->pcHead + ((pxQueue->uxLength - (UBaseType_t)1U)); //?????
        pxQueue->cRxLock = queueUNLOCKED;
        pxQueue->cTxLock = queueUNLOCKED;
        
        //如果不是新创建的队列, 需要处理相关的列表
        if (xNewQueue == pdFALSE) {
                if (listLIST_IS_EMPTY(&(pxQueue->xTaskWaitingToSend)) == pdFALSE) {
                        if (xTaskRemoveFromEventList(&(pxQueue->xTasksWaitingToSend)) != pdFALSE）
                                qeueYIELD_IF_USING_PREEMPTINON();
                }
        //如果是新创建的队列
        } else {
                vListInitialise(&(pxQueue->xTasksWaitingToSend));
                vListInitialise(&(pxQueue->xTasksWaitingToReceive));
        }
        taskEXIT_CRITICAL();
        return pdPASS;
}



/*******************************************************************************
                              FreeRTOS-队列的上锁和解锁
注意！ 队列的上锁和解锁只能由FreeRTOS内核调用，用户不能调用！
*******************************************************************************/
//将接收和发送都设置为queueLOCKED_UNMODIFIED， 表示上锁
//cRxLock出队， 也就是从队列中获取消息， 当上锁以后就不能从队列中获取消息了
//cTxLock入队， 也就是从队列中发送消息， 当上锁发后就不能从队列中发送消息了
#define prvLockQueue(pxQueue)                                   \
        taskENTER_CRITICAL(); {                                 \
        if ((pxQueue)->cRxLock == queueUNLOCKED) {              \
                (pxQueue)->cRxLock = queueLOCKED_UNMODIFIED;    \
        }                                                       \
        if ((pxQueue)->cTxLock == queueUNLOCKED) {              \
                (pxQueue)->cTxLock = queueLOCKED_UNMODIFIED;    \
        }                                                       \
}       taskEXIT_CRITICAL();                                    \



1 队列解锁， 先处理cTxLock
___________________________________________________________
//判断是否有任务在上锁期间因为队列为空而导致获取消息失败挂载到列表xTaskWaitingToReceive上。
  有的话就在队列解锁的时候就需要移出掉。
//如果从列表xTaskWaitingToReceive上移出的任务其优先级大于当前正在运行的任务，就需要进行任务切换
//任务切换处理过程, 调用vTaskMissedYield() => xYieldPending=pdTURE。 
  函数xTaskIncrementTick()会处理xYieldPending, 如果xYieldPending=pdTURE，就将
  xSwitchRequired也赋值为pdTURE。 返回xSwitchRequired这个值。 等效于vTaskMissedYield()让
  xTaskIncrementTick()返回pdTURE。 最终在函数xPortSysTichHandler()进行任务切换。
//pxQueue->cTxLock = queueUNLOCKED;
2 队列解锁， 再处理cRxLock, 与cTxLock相似
___________________________________________________________
static void prvUnlockQueue(Queue *const pxQueue)
{
        taskENTER_CRITICAL();
        int8_t cTxLock = pxQueue->cTxLock;
        //判断是否有中断向队列发送了消息，如果在中断中，当队列上锁的话那么向队列
        //发送消息成功以后会将入队计数器“cTxLock加1”
        while (cTxLock > queueLOCKED_UNMOKIFIED) {
                if (listLIST_IS_EMPTY(&(pxQueue->xTasksWaitingToReceive)) == pdFALSE) {
                        if (xTaskRemovFromEventList(&(pxQueue->xTasksWaitingToReceive)) != pdFALSE)
                                vTaskMissedYield();
                } else {
                        break;
                }
                --cTxLock;
        }
        pxQueue->cTxLock = queueUNLOCKED;
        taskEXIT_CRITICAL();
        
        
        
        taskENTER_CRITICAL();
        int8_t cRxLock = pxQueue->cRxLock;
        while (cRxLock > queueLOCKED_UNMOKIFIED) {
                if (listLIST_IS_EMPTY(&(pxQueue->xTasksWaitingToSend)) == pdFALSE) {
                        if (xTaskRemovFromEventList(&(pxQueue->xTasksWaitingToSend)) != pdFALSE)
                                vTaskMissedYield();
                } else {
                        break;
                }
                --cRxLock;
        }
        pxQueue->cRxLock = queueUNLOCKED;
        taskEXIT_CRITICAL();        
}



/*******************************************************************************
                              FreeRTOS-队列入队
??? 猜测 ???
        将数据复制到队列存储区中
        判断是否有任务因为队列为空，而进入阻塞态，如果有的话将它恢复
        如果队列为满，则入队失败。 如果设置了入队阻塞时间的话就将入队的任务阻塞
1 判断队列是否已经满了？
  如果未满的话， 使用函数prvCopyDataToQueue()复制数据到队列中
2 检查是否有任务因为队列为空而进入阻塞态。 如果有的话就解除阻塞态。
  此功能通过函数xTaskRemoveFromEventList()来完成。 如果任务调度器没有挂起，
  从相应的事件列表和状态列表中移出，并且将任务添加到就绪列表中
3 如果任务调度器挂起， 不会从状态列表中移出， 并且将任务添加到xPendingReadyList列表中
  当通过函数xTaskResumeAll()恢复任务调度器的时候，添加到xPengdingReadyList列表中
  任务就会被处理。
4 如果队列满的话，如果阻塞时间为“0”的话直接返回，返回错误值为errQUEUE_FULL
5 如果队列满的话，且阻塞时间不为“0”的话，通过函数vTaskPlaceOnEventList()将任务添加
  到相应的事件列表和延时列表中
*******************************************************************************/
//中断级入队函数
1 判断队列是否已经满？
2 如果队列没有满，使用函数prvCopyDataToQueue()拷贝数据到队列中
3 如果队列没有上锁，那就正常处理。 
  检查是否有任务因为队列为“空”而进入阻塞态。 如果有的话就解除阻塞态。
  此功能通过函数xTaskRemoveFromEventList()来完成。 如果任务调度器
  没有被挂起，从相应的事件列表和状态列表中移除。 并且添加到就绪列表中。
  如果任务调度器被挂起，不会从状态列表中移出，并且将任务添加到xPendingReadyList列表中。
  当通过函数xTaskResumeAll()恢复任务调度器的时候，添加到xPendingReadyList列表中的任务会被处理。
4 如果队列上锁， “cTxLock加1”， 表示在队列上锁期间入队的消息数量
5 如果队列满了，直接返回errQUEUE_FULL, 表示队列满！ 原因很简单，中断服务函数不是任务！！
  所以没有任务添加列表这一说法
BaseType_t xQueueGenericSend( 
        QueueHandle_t xQueue, 
        const void * const pvItemToQueue, 
        TickType_t xTicksToWait, 
        const BaseType_t xCopyPosition )
{
        BaseType_t xEntryTimeSet = pdFALSE, xYieldRequired;
        TimeOut_t xTimeOut;
        Queue_t * const pxQueue = ( Queue_t * ) xQueue;


        for ( ;; ) {
                taskENTER_CRITICAL();
                
                //如果队列没有满___________________________________________________
                //uxMessagesWaiting表示当前队列的消息数
                //xCopyPosition表示覆写， 如果是覆写的话不管消息队列有没有满
                if ((pxQueue->uxMessagesWaiting < pxQueue->uxLength) || 
                                (xCopyPosition == queueOVERWRITE)) {
                        xYieldRequired = prvCopyDataToQueue( pxQueue, pvItemToQueue, xCopyPosition );
                        
                        
                        if (listLIST_IS_EMPTY(&(pxQueue->xTaskWaitingToReceive)) == pdFALSE) {
                                if (xTaskRemoveFromEventList(&(pxQueue->xTaskWaitingToReceive)) 
                                != pdFALSE) {
                                        queueYIELD_IF_USING_PREEMPTION();
                                }
                        } else if (xYieldRequired != pdFALSE) {
                                queueYIELD_IF_USING_PREEMPTION();
                        } else {
                        }
                        taskEXIT_CRITICAL();
                        return pdPASS;
                   
                //如果队列满的话___________________________________________________
                } else {        //xTicksToWait入队阻塞时间为“0”
                        if (xTicksToWait == (TickType)0) {
                                taskEXIT_CRITICAL();
                                return errQUEUE_FULL;
                        } else if (xEntryTimeSet = pdFALSE) {
                        //the queue was full and a block time was specified
                        //so configure the timeout struct.
                                vTaskSetTimeOutState(&xTimeOut);
                                xEntryTimeSet = pdTRUE;
                        } else {
                        }
                        
                        
                        taskEXIT_CRITICAL();
                
                        vTaskSuspendAll();
                        prvLockQueue(pxQueue);
                        
                        //确定一下阻塞时间， 如果阻塞时间没有到的话
                        if (xTaskCheckForTimeOut(&xTimeOut, &xTicksToWait) == pdFALSE) {
                                //如果队列是满的话，把队列放到事件列表中
                                if (prvIsQueueFull(pxQueue) != pdFALSE) {
                                        vTaskPlaceOnEventList(&(pxQueue->xTasksWaitingToSend), xTicksToWait);
                                        //解锁队列
                                        prvUnlockQueue(pxQueue);
                                        if (xTaskResumeAll() == pdFALSE)
                                                protYIELD_WITHIN_API();
                                } else {
                                        prvUnlickQueue(pxQueue);
                                        (void)xTaskResumeAll();
                                }
                        }
                        prvUnlockQueue(pxQueue);
                        (void)xTaskResumeAll();
                        return errQUEUE_FULL;
                }
        }
}



static BaseType_t prvCopyDataToQueue(
        Queue_t * const pxQueue, 
        const void *pvItemToQueue,      //要拷贝的数据
        const xCopyPosition)            //数据拷贝方式
{
        BaseType_t xReturn = pdFALSE;
        UBaseType_t uxMessageWaiting;
        
        uxMessagesWaiting = pxQueue->uxMessagesWaiting;
        
        //说明这个队列用于信号量
        if (pxQueue->uxItemSize == (UBaseType_t)0) {
                #if (configUSE_MUTEXES == 1)
                if (pxQueue->uxQueueType == queueQUEUE_IS_MUTEX) {
                        xReturn = xTaskPriorityDisinherit((void *)pxQueue->pxMutexHolder);
                        pxQueue->pxMutexHolder = NULL
                }
                #endif
        //如果是从后面入队的话
        } else if (xPosition == queueSEND_TO_BACK) {
                (void)memcpy((void *)pxQueue->pcWriteTo, pvItemToQueue, (size_t)ux
                pxQueue->pcWriteTo += pxQueue->uxItemSize;
                if (pxQueue->pcWriteTo >= pxQueue->pcTail) 
                        pxQueue->pcWirteTo = pxQueue->pcHead;
        //如果从前面入队的话
        } else {
                (void)memcpy((void *)pxQueue->u.pcReadFrom, pvItemToQueue, (size_t)pxQueue
                pxQueue->u.pcReadFrom -= pxQueue->uxItemSize;
                if (pxQueue->u.pxReadFrom < pxQueue->pcHead)
                        pxQueue->u.pcReadFrom = (pxQueue->pcTail - pxQueue->ItemSize);
                        
                //如果是覆写的话       
                if (xPosition == queueOVERWRITE) {
                        if (uxMessagesWaiting > (UBaseType)0)
                                --uxMessagesWaiting;
                }
        }
        pxQueue->uxMessagesWaiting = uxMessagesWaiting + 1;
        return xReturn;
}

BaseType_t xTaskRemoveFromEventList(cosnt List_t *const pxEventList)
{
        TCB_t *pxUnblockedTCB;
        BaseType_t xReturn;
        
        //
        pxUnblockedTCB = (TCB *)listGET_OWNER_OF_HEAD_EMTRY(pxEventList);
        (void)uxListRemove(&(pxUnblockedTCB->xEventListItem));
        
        //如果任务调度器没有被挂起
        if (uxSchedulerSuspended == (UBAseType_t)pdFALSE) {
                (void)uxListRemove(&(pxUnblockedTCB->xStateListItem));
                prvAddTaskToReadyList(pxUnblockedTCB);
        //如果任务调度器被挂起的话
        } else {
                vListInsertEnd(&(xPendingReadyLIst), &(pxUnblockedTCB->xEventListItem));
        }
}


void vTaskPlaceOnEventList(List_t *const pxEventList, const TickType_t xTicksToWait
{
        vListInsert(pxEventList(xTicksToWait, pdTRUE);
        prvAddCurrentTaskToDelayedList(xTicksToWait, pdTRUE);
}



/*******************************************************************************
                              FreeRTOS-队列出队
xQueueReceive()
        从队列中读取队列项（消息）， 并且读取完以后删除掉队列项（消息）         
xQueuePeek()
        从队列中读取队列项（消息）， 并且读取完以后不删除掉队列项（消息）
        
xQueueReceiveFromISR()
        从队列中读取队列项（消息）， 并且读取完以后删除掉队列项（消息）
        用于中断服务函数中
xQueuePeekFromISR()
        从队列中读取队列项（消息）， 并且读取完以后不删除掉队列项（消息）
        用于中断服务函数中
*******************************************************************************/
//任务通用出队函数详解 xQueueGenericReceive()
___________________________________________________________
1 判断队列是否为“空”
2 如果队列不为空，使用函数prvCopyDataFromQueue()从队列中拷贝消息
3 检查是否有任务因为“队列满而进入阻塞态”，如果有的话就解除阻塞态。 此功能通过
  函数xTaskRemoveFromEventList()来完成。 如果任务调度器没有挂起，从相应的
  事件列表和状态列表中移除， 并且将任务添加到就绪列表中。 
  如果任务调度器挂起的话， 不会从状态列表中移除， 并且将任务添加到xPendingReadyList列表中。 
  当通过函数xTaskResumeAll()恢复任务调度器的时候， 添加到xPendingReadyList列表中的任务就会被处理。
4 如果队列空了，当阻塞时间为“0”的话直接返回，返回错误传值为errQUEUE_EMPTY
5 如果队列空，而且阻塞时间不为“0”，通过函数vTaskPlaceOnEventList()将任务添加到相应的
  事件列表和延时列表中。


//中断通用出队函数详解 xQueueReceiveFromISR()
___________________________________________________________
1 判断队列是否为空？
2 如果不为空，使用函数 prvCopyDataFromQueue从队列中拷贝消息
3 如果队列没有上锁，那就正常处理。 检查是否有任务因为队列满而进入阻塞态，如果有的话就解除阻塞态。
  此功能通过函数xTaskRemoveFromEventList()来完成。 如果调度器没有挂起，从相应的事件列表和
  状态列表中移除，并且将任务添加到就绪列表中。
  如果任务调度器挂起的话，不会从状态列表中移除， 并且将任务添加到xPendingReadyList列表中，
  当通过函数xTaskResumeAll()恢复任务调度器的时候，添加到xPendingReadyList列表中的任务就会被处理。
4 如果队列上锁，“cRxLock加1”，表示在队列上锁期间出队的消息数量
5 如果队列为空，直接返回pdFALT, 表示队列为空！ 原因很简单， 中断服务函数不是任务！！
  所以没有任务添加列表这一说法。





