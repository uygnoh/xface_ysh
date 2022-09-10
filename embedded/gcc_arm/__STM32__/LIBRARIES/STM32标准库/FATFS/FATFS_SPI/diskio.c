/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define SD_CARD			0
#define SPI_FLASH		1


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
        BYTE pdrv       //Physical drive nmuber to identify the drive
)
{
        DSTATUS stat;
        int result;

        switch (pdrv) {
        case SD_CARD :
	        return stat;

        case SPI_FLASH :
                if (spi_flash_read_id() == W25Q_FLASH_ID) {
                        stat = 0;               // W25Q_FLASH状态正常
                } else {                       // W25Q_FLASH状态（不）正常，初始化失败
                        stat = STA_NOINIT;
                }
                return stat;
        }
        return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
        BYTE pdrv       //Physical drive nmuber to identify the drive
)
{
        DSTATUS stat;
        int result;

        switch (pdrv) {
        case SD_CARD :
                return stat;

        case SPI_FLASH :
                spi_flash_init();               //STM32_SPI_FLASH初始化
                spi_flash_wakeup();             //唤醒SPI_FLASH
                stat = disk_status(SPI_FLASH);  //判断SPI_FLASH初始化是否成功
                return stat;
        }
        
        return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
        BYTE pdrv,              //Physical drive nmuber to identify the drive
        BYTE *buff,             //Data buffer to store read data
        LBA_t sector,           //Start sector in LBA
        UINT count              //Number of sectors to read
)
{
        DRESULT res;
        int result;

        switch (pdrv) {
        case SD_CARD :
                return res;

        case SPI_FLASH :
                // 计算偏移（2*1024*1024）/(4096)=512
                // 扇区偏移2MB，外部FLASH文件系统空间放在SPI_FLASH后面的（6MB）空间中
                sector += 512;
                
                spi_flash_buffer_read(buff, sector*4096, count*4096);
                res = RES_OK;
                return res;
        }

        return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
#if FF_FS_READONLY == 0
DRESULT disk_write (
        BYTE pdrv,              //Physical drive nmuber to identify the drive
        const BYTE *buff,       //Data to be written
        LBA_t sector,           //Start sector in LBA
        UINT count              //Number of sectors to write
)
{
        DRESULT res;
        int result;

        switch (pdrv) {
        case SD_CARD :
                return res;

        case SPI_FLASH :
                // 计算偏移（2*1024*1024）/(4096)=512
                // 扇区偏移2MB，外部FLASH文件系统空间放在SPI_FLASH后面的（6MB）空间中
                sector += 512;
                
                //先擦除，再写入
                spi_flash_sector_erase(sector*4096);
                spi_flash_buffer_write((uint8_t *)buff, sector*4096, count*4096);
                res = RES_OK;
                return res;
        }

        return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
DRESULT disk_ioctl (
        BYTE pdrv,              //Physical drive nmuber (0..)
        BYTE cmd,               //Control code
        void *buff              //Buffer to send/receive control data
)
{
        DRESULT res;
        int result;

        switch (pdrv) {
        case SD_CARD :
                return res;

        case SPI_FLASH :
                switch (cmd) {
                case GET_SECTOR_COUNT :         //返回扇区个数
                        *(DWORD *)buff = 1536;  //扇区数量：(1536*4096)/1024/1024=6MByte
                        break;
                case GET_SECTOR_SIZE  :         //返回每个扇区大小
                        *(DWORD *)buff = 4096;
                        break;
                case GET_BLOCK_SIZE   :         //返回擦除扇区的最小个数（单位：扇区）
                        *(DWORD *)buff = 1;
                        break;
                }
                
                res = RES_OK;
                return res;
        }

        return RES_PARERR;
}

//返回时间
__weak DWORD get_fattime(void)
{
        return ((DWORD)(2021 - 1980) << 25)     //year
                | ((DWORD)1 << 21)              //month
                | ((DWORD)1 << 16)              //day
                | ((DWORD)1 << 11)              //hour
                | ((DWORD)1 << 5 )              //minute
                | ((DWORD)1 << 1 );             //second
}
