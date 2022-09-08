#include "ff.h"


FATFS           fs;                             // FatFs文件系统对象
FIL             fnew;                           // 文件对象
FRESULT         res_sdio;                       // 文件操作结果
UINT            fnum;                           // 文件成功读写数量
BYTE            ReadBuffer[1024]  = 0;          // 读缓冲区
BYTE            WriteBuffer[1024] = "STM22\r\n";// 写缓冲区

int main(void)
{
        // 挂载SD_CARD
        // ____________________________________________________
        res_sdio = f_mount(
                                &fs,    // FatFs文件系统对象
                                "0:",   // 路径（0）， 指向SDIO
                                1);     // 立即挂载
                                
                                
        // 文件格式化
        // 如果没文件系统就格式化，并创建文件系统
        // ____________________________________________________
        if (res_sdio == FR_NO_FILESYSTEM) {
                printf("SDIO没有文件系统， 即将格式化...\r\n");
                res_sdio = f_mkfs("0:', 0, 0);
                if (res_sdio == FR_OK) {
                        printf("SDIO文件系统已经格式化\r\n");
                        // 格式化后， 先取消挂载
                        res_sdio = f_mount(NULL, "0:", 1);
                        // 重新挂载
                        res_sdio = f_mount(&fs,  "0:", 1);
                } else {
                        printf("SDIO文件系统格式化 FAILD\r\n");
                        while(1);
                }

                
        } else if (res_sdio != FR_OK) {
                printf("SDIO文件系统挂载 FAILD\r\n");
                while (1);
        } else {
                printf("SDIO文件系统挂载 SUCCESS\r\n");
        }
        
        
        // 文件系统写测试
        // ____________________________________________________
        res_sdio = f_open(
                                &fnew, 
                                "0:write00.txt", 
                                FA_CREATE_ALWAYS | FA_WRITE);
        if (res_sdio == FR_OK) {
                printf("打开、创建（write00.txt）文件成功， 向文件写入数据\r\n");
                res_sdio = f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
                if (res_sdio == FR_OK) {
                        printf("文件写入成功， 写入字节数据： %d\r\n", fnum);
                } else {
                        printf("文件写入失败， %d\r\n", res_sdio);
                }
                // 关闭文件
                f_close(&fnew);
        } else {
                printf("打开文件失败");
        }
        
        // 不在使用文件系统，取消挂载文件系统
        f_mount(NULL, "0:", 1);
        
        
        
        // 文件系统读测试
        // ____________________________________________________
        res_sdio = f_open(
                                &fnew, 
                                "0:write00.txt",
                                FA_OPEN_EXISTING | FA_READ);
        if (res_sdio == FR_OK) {
                printf("打开文件成功");
                res_sdio = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
                if (res_sdio == FR_OK) {
                        printf("读取文件成功");
                } else {
                        printf("读取文件失败");
                }
        } else {
                printf("打开文件失败");
        }
}
