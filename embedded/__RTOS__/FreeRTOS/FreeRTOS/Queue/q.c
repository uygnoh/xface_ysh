/*******************************************************************************
                              FreeRTOS-队列创建
1 判断队列需要多在内存， xQueueSizeInBytes = uxQueueLength * uxItemSize
2 为队列申请内存，申请多大？ sizeof(Queue_t)队列结构体大小 + xQueueSizeInBytes队列大小  
3 判断内存是否申请成功？ 如果成功的话计算出队列存储区的首地址。
4 调用prvInitialiseNewQueue(),初始化新的队列pxNewQueue;
*******************************************************************************/
QueueHandle_t xQueueGenericCreate(
        const UBaseType_t uxQueueLength, 
        const
        )
{
        Queue_t *pxNewQueue;
        size_t xQueueSizeInBytes;
        uint8_t *pucQueueStorage;
        
        //判断一下队列项是不是 == 0
        //它对应的是信号量
        if (uxItemSize == (UBaseType_t)0) 
                xQueueSizeInBytes = (size_t)0;
        //统计队列总字节数， 它对应的是队列
        else
                xQueueSizeInBytes = (size_t)(uxQueueLength * uxItemSize);
                
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
