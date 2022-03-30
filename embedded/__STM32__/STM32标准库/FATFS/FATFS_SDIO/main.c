// FATFS/ffconf.h
// ____________________________________________________________
// 如果要支持长文件名
//      0 #define _CODE_PAGE      936     // 支持中文文件名
//      1 #define _USE_LFN        1       // 使用长文件名
//      2 #define _MAX_LFN        255     // 
// ____________________________________________________________
#define _CODE_PAGE      437     // U.S 编码
#define _USE_LFN        0       // 不使用长文件名
#define _MAX_LFN        255     // 
#define _VOLUMES        2       // 磁盘个数
#define _MIN_SS         512     // 最小扇区大小 
#define _MAX_SS         4096    // 最大扇区大小
#define _USE_MKFS       1       // 文件系统格式化
#define _FS_READONLY    0       // 默认配置
#define _USE_STRFUNC    1       // 
// ____________________________________________________________


FATFS           fs;             // FATFS文件系统对象
FIL             fnew;           // 文件对象
FRESULT         res_file;       // 文件操作结果
UINT            fnum;           // 文件成功读取数量
BYTE            ReadBuffer[1024] = {0};
BYTE            WriteBuffer[] = " SDIO TEST\n ";


int main(void)
{
        // 文件系统挂载
        //_____________________________________________________
        // &fs
        // "0:" 表示（ATA），也就是SD_CARD
        //  1   表示立即挂载文件系统
        res_file = f_mount(&fs, "0:", 1);
        
        
        // 文件系统格式化测试
        //_____________________________________________________
        if (res_file == FR_NO_FILESYSTEM) {
                printf("SDCARD 还没有文件系统，即将进行格式化... \n");
                res_file = f_mkfs("0:", 0, 0);
                if (res_file == FR_OK) {
                        printf("SDCARD 已经成功格式化文件系统... \n");
                        res_file = f_mount(NULL, "0:", 1);     // 格式化后，先取消挂载
                        res_file = f_mount(&fs,  "0:", 1);     // 然后再重新挂载
                } else {
                        printf("FLASH 格式化失败... res = %d\n", res_file);
                }
        }
        
        
        // 文件系统操作测试     => 写
        //_____________________________________________________
        printf("SDCARD 文件系统即将进入写操作测试... \n");
        res_file= f_open(      &fnew, 
                                "0: Fatfs.txt",         //文件路径
                                FA_CREATE_ALWAYS |      //如果文件不存在，则创建它
                                FA_WRITE);              //写操作
        
        if (res_file == FR_OK) {
                printf("创建Fatfs读写测试文件（Fatfs.txt）成功，向文件写入数据... \n");
                res_file = f_write(&fnew, WriteBuffer, sizeof(WriteBuffer), &fnum);
                if (res_file == FR_OK) {
                        printf("文件写入成功，写入字节数据: %d\n", fnum);
                        printf("向文件写入的数据为: %s \n", WriteBuffer);
                } else {
                        printf("写入文件失败！ res = %d\n", res_file);
                }
                f_close(&fnew);      
        }
        
        
        // 文件系统操作测试     => 读
        //_____________________________________________________
        printf("SDCARD 文件系统即将进入读操作测试... \n");
        res_file = f_open(&fnew, "0:Fatfs.txt", FA_OPEN_EXISTING | FA_READ);
        if (res_file == FR_OK) {
                printf("SDCARD 打开文件成功... \n");
                res_file = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
                if (res_file == FR_OK) {
                        printf("SDCARD 读取文件成功... \n");
                        printf("SDCARD 读取文件数据: %s\n", ReadBuffer);
                } else {
                        printf("读取文件失败！ res = %d\n", res_file);
                }
        }     
}
