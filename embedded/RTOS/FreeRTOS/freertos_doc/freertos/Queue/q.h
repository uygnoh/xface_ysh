/*******************************************************************************
        => FreeRTOS-Queue 队列结构体
*******************************************************************************/
typedef struct QueueDefinition {
        int8_t *pcHead;         // 指向队列存储区起始位置,即第一个队列项
        int8_t *pcTail;         // 指向队列存储区最后一个字节
        int8_t *pcWriteTo;      // 指向存储区中下一个空闲区域
        
        union { // 当用作队列的时候指向最后一个出队的队列项首地址
                int8_t *pcReadFrom;
                // 当用作递归互斥量的时候用来记录递归互斥量被调用的次数
                UBaseType_t uxRecursiveCallCount;
        } u;
        
        // 等待发送任务列表， 那些因为队列满导致入队失败而进入阻塞态的任务就会挂到此列表上
        List_t xTasksWaitToSend;
        // 等待接收任务列表， 那些因为队列空导致出队失败而进入阻塞态的任务就会挂到此列表上
        List_t xTasksWaitToReceive;
        
        // 队列中当前队列项数量， 也就是消息数
        volatile UBaseType_t uxMessageWaiting;
        // 创建队列时指定的队列长度，也就是队列中最大允许的队列项（消息）数量
        UBaseType_t uxLength;
        // 创建队列时指定每个队列项（消息）最大长度，单位字节
        UBaseType_t uxItemSize;
        
        // 当队列上锁后用来统计从队列中接收到的队列项数量，也就是
        // 出队的队列项数量，当队列没有上锁的话此字段为“queueUNLOCKED”
        volatile int8_t cRxLock;
        // 当队列上锁以后用来统计从队列中接收到的队列项数量，也就是
        // 入队的队列项数量，当队列没有上锁的话此字段为“queueUNLOCKED”
        volatile int8_t cTxLock;
        
        // 如果使用静态存储的话，此字段设置为“pdTURE”
        #if((configSUPPORT_STATIC_ALLOCATION  == 1) && \
            (configSUPPORT_DYNAMIC_ALLOCATION == 1))   \
            uint8_t ucStaticallyAllocated;
        #endif
        // 队列集相关宏
        #if(configUSE_QUEUE_SET == 1)
        struct QueueDefinition *pxQueueSetContainer;
        #endif
        // 跟踪调试相关宏
        #if(configUSE_TRACE_FACILITY == 1)
        UBaseType_t uxQueueNumber;
        uint8_t ucQueueType;
        #endif
} xQUEUE;
typedef xQUEUE  Queue_t;

#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
#define xQueueCreate(uxQueueLength, uxItemSize) \
        xQueueGenericCreate((uxQueueLength), (uxItemSize), (queueQUEUE_TYPE_BASE));
#endif



/*******************************************************************************
        => FreeRTOS-Queue 队列数据结构
*******************************************************************************/
// QueueHandle_t xQueueGenericCreate
___________________________________________________________
uxQueueLength   // 队列项数目
uxItemSize      // 每个队列项的大小
pucQueueStorage // 使用静态分配队列时才使用，指向定义队列存储空间，
                // 如果使用动态分配队列空间（默认），向这个参数传递NULL。
pxStaticQueue   // 使用静态分配队列时才使用，指向队列控制结构体，
                // 如果使用动态分配队列空间（默认），向这个参数传递NULL。
ucQueueType     // 类型。可能的值为
                // ucQueueType队列类型
                queueQUEUE_TYPE_BASE                    // 表示队列
                queueQUEUE_TYPE_SET                     // 表示队列集合 
                queueQUEUE_TYPE_MUTEX                   // 表示互斥量
                queueQUEUE_TYPE_COUNTING_SEMAPHORE      // 表示计数信号量
                queueQUEUE_TYPE_BINARY_SEMAPHORE        // 表示二进制信号量
                queueQUEUE_TYPE_RECURSIVE_MUTEX         // 表示递归互斥量
                
                
                
/*******************************************************************************
        => FreeRTOS-Queue 队列函数
*******************************************************************************/
// 任务级入队函数
___________________________________________________________
xQueueSend()            //发送消息到队列尾部
xQueueSendToBack()      //
xQueueSendToFront()     //发送消息到队列头部
xQueueOverwrite()       //发送消息到队列，带覆盖功能，当队列满了以后，自动覆盖掉旧的消息

// 中断级入队函数
___________________________________________________________
xQueueSendFromISR()        //发送消息到队列尾部（用于中断服务函数）
xQueueSendToBackFromISR()  
xQueueSendToFrontFromISR() //发送消息到队列头部（用于中断服务函数）
xQueueOverwriteFromISR()   //发送消息到队列，带覆盖功能，当队列满了以后，自动覆盖掉旧的消息
