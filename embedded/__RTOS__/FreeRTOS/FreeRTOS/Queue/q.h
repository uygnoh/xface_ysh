/*******************************************************************************
                                   Queue 队列
*******************************************************************************/
typedef struct QueueDefinition {
        int8_t *pcHead;         //指向队列存储区开始地址
        int8_t *pcTail;         //指向队列存储区最后一个字节
        int8_t *pcWriteTo;      //指向存储区中下一个空闲区域
        
        union { //当用作队列的时候指向最后一个出队的队列项首地址
                int8_t *pcReadFrom;
                //当用作递归互斥量的时候用来记录递归互斥量被调用的次数
                UBaseType_t uxRecursiveCallCount;
        } u;
        
        //等待发送任务列表， 那些因为队列满导致入队失败而进入阻塞态的任务就会挂到此列表上
        List_t xTasksWaitToSend;
        //等待接收任务列表， 那些因为队列空导致出队失败而进入阻塞态的任务就会挂到此列表上
        List_t xTasksWaitToReceive;
        
        //队列中当前队列项数量， 也就是消息数
        volatile UBaseType_t uxMessageWaitint;
        //创建队列时指定的队列长度，也就是队列中最大允许的队列项（消息）数量
        UBaseType_t uxLength;
        //创建队列时指定每个队列项（消息）最大长度，单位字节
        UBaseType_t uxItemSize;
        
        //当队列上锁后用来统计从队列中接收到的队列项数量，也就是
        //出队的队列项数量，当队列没有上锁的话此字段为“queueUNLOCKED”
        volatile int8_t cRxLock;
        //当队列上锁以后用来统计从队列中接收到的队列项数量，也就是
        //入队的队列项数量，当队列没有上锁的话此字段为“queueUNLOCKED”
        volatile int8_t cTxLock;
        
        //如果使用静态存储的话，此字段设置为“pdTURE”
        #if((configSUPPORT_STATIC_ALLOCATION  == 1) && \
            (configSUPPORT_DYNAMIC_ALLOCATION == 1))   \
            uint8_t ucStaticallyAllocated;
        #endif
        //队列集相关宏
        #if(configUSE_QUEUE_SET == 1)
        struct QueueDefinition *pxQueueSetContainer;
        #endif
        //跟踪调试相关宏
        #if(configUSE_TRACE_FACILITY == 1)
        UBaseType_t uxQueueNumber;
        uint8_t ucQueueType;
        #endif
} xQUEUE;
typedef xQUEUE  Queue_t;

#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
#define xQueueCreate(uxQueueLength, uxItemSize)                 \
        xQueueGenericCreate((uxQueueLength), (uxItemSize), (queueQUEUE_TYPE_BASE));



