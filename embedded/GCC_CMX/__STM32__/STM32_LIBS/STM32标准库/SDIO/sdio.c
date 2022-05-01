void microsd_test(void)
{
        LED_BLUE();
        
        //SD卡使用中断及DMA接收数据
        if ((Status = SD_Init()) != SD_OK) {
                LED_RED();
                printf("SD卡初始化失败，请确保SD卡已正确接入开发板，或换一张SD卡测试！\n");
        } else {
                printf("SD卡初始化成功!\n");
        }
        if (Status == SD_OK) {
                LED_BLUE();
                SD_EraseTest();
                
                LED_BLUE();
                SD_SingleBlockTest();   //单块读写测试
                
                LED_BLUE();
                SD_MultiBlockTest();    //多块读写测试（暂不支持多块读写）
        }
}



void SD_EraseTest(void)
{
        if (Status == SD_OK) {
                Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
        }
        if (Status == SD_OK) {
        }
}
