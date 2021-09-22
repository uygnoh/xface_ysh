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
} xQUEUE;
