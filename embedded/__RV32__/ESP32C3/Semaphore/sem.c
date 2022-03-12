/*******************************************************************************
        => 二进制信号量 Binary Semaphore
*******************************************************************************/

SemaphoreHandle_t semapore_handle;      //二进制信号量句柄
int count = 0;                          //全局变量

void task00(void *pvParam)
{
        for (;;) {
                //获取这个二进制信号量
                xSemaphoreTake(sempahore_handle, portMAX_DELAY);
                for (int i = 0; i < 10; i++) {
                        count++;
                        printf("TASK00 COUNT = %d\n", count);
                        vTaskDelay(pdMS_TO_TICKS(1000));
                }
                //释放二进制信号量
                xSemaphoreGive(semapore_handle);
                vTaskDelay(pdMS_TO_TICKS(1000));
        }
}

void task11(void *pvParam)
{
        for (;;) {
                //获取这个二进制信号量
                xSemaphoreTake(sempahore_handle, portMAX_DELAY);
                for (int i = 0; i < 10; i++) {
                        count++;
                        printf("TASK11 COUNT = %d\n", count);
                        vTaskDelay(pdMS_TO_TICKS(1000));
                }
                //释放二进制信号量
                xSemaphoreGive(semapore_handle);
                vTaskDelay(pdMS_TO_TICKS(1000));
        }
}
void app_main(void)
{
        //创建二进制信号量（创建完成后它是空的）
        semapore_handle = xSemaphoreCreateBinary();
        //所以要（释放二进制信号量）
        xSemaphoreGive(semapore_handle);
        
        xTaskCreate(task00, "TASK00", 1024*5, NULL, 1, NULL);
        xTaskCreate(task11, "TASK11", 1024*5, NULL, 1, NULL);
}


/*******************************************************************************
        => 计数信号量 Count Semaphore
*******************************************************************************/
SemaphoreHandle_t semphore_handle;

//模拟一个停车场（车进入停车场）
void CarInTask(void *pvParam)
{
        int emptySpace = 0;     //车位
        BaseType_t iResult;
        
        for (;;) {
                //获取计数信号量的可用的个数（也就是车位数量）
                emptySpace = uxSemaphoreGetCount(semphore_handle);
                printf("emptySpace = %d\n", emptySpace);
                
                //检查车库是否有空的车位（0表示不等待）
                iResult = xSemaphoreTake(semphore_handle, 0);
                if (iResult == pdPASS) {
                        //允许一两车进入停车场
                        printf("One car IN!\n");
                } else {
                        //表示没有空的车位
                        printf("No Space!\n");
                }
        }
}

//汽车出停车场
void carOutTask(void *pvParam)
{
        for (;;) {
                vTaskDelay(pdMS_TO_TICKS(6000));
                //释放这个计数信号量
                xSemaphoreGive(semaphore_handle);
                printf("One car OUT!\n");
        }
}

void app_main(void)
{
        //设置计数信号量为（5）
        //最大值为5， 有5个空的位置 
        semaphore_handle = xSemaphoreCreateCounting(5, 5);
        //释放计数信号量
        xSemaphoreGive(semaphore_handle);
        
        xTaskCreate(carInTask,  "carInTask",  1024*5, NULL, 1, NULL);
        xTaskCreate(carOutTask, "carOutTask", 1024*5, NULL, 1, NULL);
        
}



/*******************************************************************************
        => 互斥信号量 Mutex Semaphore
*******************************************************************************/
//互斥信号量和二进制信号量非常相似
//区别在于优先级继承

SemaphoreHandle_t mutex_handle;

void task11(void *pvParam)
{
        for (;;) {
                printf("TASK11 begin!\n");
                iRet = xSemaphoreTake(mutex_handle, 1000);
                if (iRet == pdPASS) {
                        for (int i = 0; i < 50; i++) {
                                printf("TASK11 i=%d\n", i);
                                vTaskDelay(pdMS_TO_TICKS(1000));
                        }
                        //释放这个互斥信号量
                        xSemaphoreGive(mutex_handle);
                        printf("TASK11 give!\n");
                        vTaskDelay(pdMS_TO_TICKS(5000));
                } else {
                        printf("TASK11 didn't take!\n");
                }
        }
}

void task22(void *pvParam)
{
        BaseType_t iRet;
        printf("TASK22 begin!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        for (;;) {
                ;
        }
}

void task33(void *pvParam)
{
        BaseType_t iRet;
        printf("TASK33 begin!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        for (;;) {
                //根据这个句柄获取互斥信号量，等待1000个Ticks
                iRet = xSemaphoreTake(mutex_handle, 1000);
                if (iRet == pdPASS) {
                        printf("TASK33 take!\n");
                        for (int i = 0; i < 10; i++) {
                                printf("TASK33 i = %d\n", i);
                                vTaskDelay(pdMS_TO_TICKS(1000));
                        }
                
                        //释放这个互斥信号量
                        xSemaphoreGive(mutex_handle);
                        printf("TASK33 give!\n");
                        vTaskDelay(pdMS_TO_TICKS(5000));
               //如果没有取到这个互斥信号量
                } else {
                        printf("TASK33 didn't take!\n");
                        vTaskDelay(pdMS_TO_TICKS(1000));
                }
        }
}
void app_main(void)
{
        //创建互斥信号量
        mutex_handle = xSemaphoreCreateMutex();
        vTaskSuspendAll();
        xTaskCreate(task11, "TASK11", 1024*5, NULL, 1, NULL); //优先级最低
        xTaskCreate(task22, "TASK22", 1024*5, NULL, 2, NULL); //优先级最中
        xTaskCreate(task33, "TASK33", 1024*5, NULL, 3, NULL); //优先级最高
        vTaskResumeAll();
}





/*******************************************************************************
        =>  
*******************************************************************************/












