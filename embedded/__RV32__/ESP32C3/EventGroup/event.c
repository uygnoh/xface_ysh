/*******************************************************************************
        =>  事件组等待
*******************************************************************************/
EventGroupHandle_t event_group_handle;

EventBits_t xEventGroupWaitBits(
        const EventGroupHandle_t xEventGroup,
        const EventBits_t uxBitsToWaitFor,      //设置等待的位
        const BaseType_t xClearOnExit,          //退出时是否清除等待设置的位
        const BaseType_t xWaitForAllBits,       //等待设置的所有的位，还是某一位就可以了
        TickType_t xTicksToWait);               //等待时间
#define BIT_0           (1 << 0)                //定义第0位
#define BIT_0           (1 << 4)                //定义第1位


//检查事件组等待位的设置
//_____________________________________________________________
void task11(void *pvParam)
{
        xEventGroupWaitBits(
                event_group_handle,
                BIT_0 | BIT_4,          //等待第0位和第4位
                pdTRUE,                 //BIT_0 and BIT_4 should be cleared befor returning  
                pdFALSE,                //如果BIT_0或BIT_4有一个设置为（1），才会解除事件组的阻塞状态
                                        //如果都是（0），那么让这个任务处于阻塞状态
                                        //pdTRUE if （BIT0 & BIT4 == 1）
                portMAX_DELAY);         //无限等待
                
                printf("_____________________________\n");
                printf("TASK11 的BIT0或BIT4被设置了\n");
                vTaskDelay(pdMS_TO_TICKS(1000));
}

//设置相关的位
//_____________________________________________________________
void task22(void *pvParam)
{
        vTaskDelay(pdMS_TO_TICKS(1000));
        for (;;) {
                printf("_____________________________\n");
                printf("TASK22 begin to set bits 0 \n");
                xEventGroupSetBits(event_group_handle, BIT_0);
                vTaskDelay(pdMS_TO_TICKS(5000));
                
                printf("_____________________________\n");
                printf("TASK22 begin to set bits 4 \n");
                xEventGroupSetBits(event_group_handle, BIT_4);
                vTaskDelay(pdMS_TO_TICKS(5000));
        }
}
void app_main(void)
{
        //创建事件组
        event_group_handle = xEventGroupCreate();
        if (event_group_handle == NULL) {
                printf("Event group Create fail!\n");
        } else {
        }
        
        vTaskSuspendAll();
        xTaskCreate(task11, "TASK11", 1024*5, NULL, 1, NULL);
        xTaskCreate(task22, "TASK22", 1024*5, NULL, 1, NULL);
        vTaskResumeAll();
}



/*******************************************************************************
        =>  事件组同步
*******************************************************************************/
