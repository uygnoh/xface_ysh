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
#define ATA		        0       // SD卡使用
#define SPI_FLASH		1       // SPI-FLASH使用


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
        BYTE pdrv       //Physical drive nmuber to identify the drive
)
{
        DSTATUS status = STA_NOINIT;

        switch (pdrv) {
        case ATA :
                // 不管什么情况，设备ID读取正确
                status &= ~STA_NOINIT;
                break;
        default:
                status = STA_NOINIT;
        }
        return status;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
        BYTE pdrv       //Physical drive nmuber to identify the drive
)
{
        DSTATUS status = STA_NOINIT;

        switch (pdrv) {
        case ATA :
                if (SD_Init() != SD_OK) {
                        status = STA_NOINIT;
                }
                status &= ~STA_NOINIT;
                break;
        default:
                status = STA_NOINIT;
        }
        
        return status;
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
        DRESULT status = RES_PARERR;
        SD_Error sd_error;

        switch (pdrv) {
        case ATA :
                // buff 作4字节地址对齐
                // ____________________________________________
                if ((DWORD)buff & 3) {
                        DRESULT res = RES_OK;
                        DWORD scratch[SD_BLOCKSIZE / 4];
                        
                        while (count--) {
                                res = disk_read(ATA, (void *)scratch, sector++, 1);
                                if (res != RES_OK) {
                                        break;
                                }
                                memcpy(buff, scratch, SD_BLOCKSIZE);
                                buff += SD_BLOCKSIZE;
                        }
                        return res;
                }
                // ____________________________________________
                sd_error = SD_ReadMultiBlocks(
                        buff,                           //
                        sector * SDCarInfo.CarBlockSize,// 要读取的地址
                        SDCarInfo.CardBlockSize,        // 卡的单个块的大小
                        count);                         //  有多少个块
                        
                sd_error = SD_WaitReadOperation();
                while (SD_GetStatus() != SD_TRANSFER_OK);
                if (sd_error == SD_OK) {
                        status = RES_OK;
                } else {
                        status = RES_ERROR;
                }
                break;
        default:
                status = RES_PARERR;
        }

        return status;
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
        DRESULT status = RES_PARERR;
        
        SD_Error sd_error;
        if (!count) {
                return RES_PARERR;
        }
        
        switch (pdrv) {
        case ATA :
                // buff 作4字节地址对齐
                // ____________________________________________
                if ((DWORD)buff & 3) {
                        DRESULT res = RES_OK;
                        DWORD scratch[SD_BLOCKSIZE / 4];
                        
                        while (count--) {
                                memcpy(scratch, buff, SD_BLOCKSIZE);
                                res = disk_write(ATA, (void *)scratch, sector++, 1);
                                if (res != RES_OK) {
                                        break;
                                }
                                
                                buff += SD_BLOCKSIZE;
                        }
                        return res;
                }
                // ____________________________________________
                sd_error = SD_WriteMultiBlocks(
                                (uint8_t *)buff,                       // 文件系统要传入的数据
                                sector * SDCarInfo.CardBlocksSize,      // 写入的地址
                                SDCardInfo.CardBlockSize,               // 卡的单个块的大小
                                count);                                 // 有多少个块
                sd_error = SD_WaitWriteOperation();
                while (SD_GetStatus() != SD_TRANSFER_OK);
                if (sd_error == SD_OK)
                        status = RES_OK
                else
                        status = RES_ERROR;
                break;
        default:
                break;
        }
        return stauts;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
// 告诉Fatfs， SD卡的一些信息
DRESULT disk_ioctl (
        BYTE pdrv,              //Physical drive nmuber (0..)
        BYTE cmd,               //Control code
        void *buff              //Buffer to send/receive control data
)
{
        DRESULT res;

        switch (pdrv) {
        case ATA :
                switch (cmd) {
                case GET_SECTOR_COUNT :         //返回扇区个数
                        *(DWORD *)buff = SDCardInfo.CarCapacity / SDCardInfo.CardBlockSize;
                        break;
                case GET_SECTOR_SIZE  :         //返回扇区大小
                        *(DWORD *)buff = SDCardInfo.CardBlockSize;
                        break;
                case GET_BLOCK_SIZE   :         //返回擦除扇区的最小个数（单位：扇区）
                        *(DWORD *)buff = 1;
                        break;
                default;
                        return RES_PARERR;
                }
                res = RES_OK;
                return res;
        default:
                return RES_PARERR;
        }

        return RES_PARERR;
}

// 返回时间
__weak DWORD get_fattime(void)
{
        return ((DWORD)(2022 - 1980) << 25)     // Year 2022
                | ((DWORD)1 << 21)      // Month 1
                | ((DWORD)1 << 16)      // Mday  1
                | ((DWORD)0 << 11)      // Hour  0
                | ((DWORD)0 << 5)       // Min   0
                | ((DWORD)0 << 1)       // Sec   0
                
}
