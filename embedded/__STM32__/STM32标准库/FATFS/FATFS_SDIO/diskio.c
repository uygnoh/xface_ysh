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
#include "./sdio/bsp_sdio_sdcard.h"
#include <string.h>

/* Definitions of physical drive number for each drive */
#define ATA			0       //SD_CARD 接口
#define SPI_FLASH		1       //SPI     接口
extern SD_CardInfo SDCardInfo;         //用于存储卡的信息


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
//  pdrv = Physical drive nmuber to identify the drive
DSTATUS disk_status ( BYTE pdrv )
{
        DSTATUS retval = STA_NOINIT;

        switch (pdrv) {
        case ATA:
                // 为了简单，直接初始化为（~STA_NOINIT）值
                retval &= ~STA_NOINIT;
	        break;
        default:
                retval = STA_NOINIT;
        }
        return retval;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
//  pdrv = Physical drive nmuber to identify the drive
DSTATUS disk_initialize ( BYTE pdrv ) 
{
        DSTATUS retval = STA_NOINIT;

        switch (pdrv) {
        case ATA:
                //判断设备是否初始化（成功）
                if (SD_Init() != SD_OK) {
                        retval  = STA_NOINIT;
                } else {
                        retval &= ~STA_NOINIT;
                }
                return retval;
        }
        
        return retval;
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
        DRESULT retval = RES_PARERR;
        SD_Error sd_status;

        switch (pdrv) {
        case ATA:
                // 如果地址不是以（4）字节对齐的话，对（buff）进行地址对齐
                //_____________________________________________
                if ((DWORD)buff & 0x03) {
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
                
                // 地址已对齐，读取多个块
                //_____________________________________________
                sd_status = SD_ReadMultiBlocks( buff, 
                                                sector * SD_BLOCKSIZE, 
                                                SD_BLOCKSIZE,
                                                count   );
                if (sd_status == SD_OK) {
                        // Check if the Transfer is finished
                        sd_status = SD_WaitReadOperation();
                        while (SD_GetStatus() != SD_TRANSFER_OK);
                }

                if (sd_status != SD_OK) {
                        retval = RES_PARERR;
                } else {
                        retval = RES_OK;
                }
                break;
        }

        return retval;
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
        DRESULT retval = RES_PARERR;

        switch (pdrv) {
        case ATA:
                // 对（buff）进行地址对齐
                //_____________________________________________
                if ((DWORD)buff & 3) {
                        DRESULT res = RES_OK;
                        DWORD scratch[SD_BLOCK / 4];
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
                
                // 地址已经对齐
                //_____________________________________________
                sd_status = SD_WriteMultiBlocks( (uint8_t *)buff, 
                                                sector * SD_BLOCKSIZE, 
                                                SD_BLOCKSIZE, 
                                                count   );
                sd_status = SD_WaitWriteOperation();
                while (SD_GetStatus() != SD_TRANSFER_OK);
                if (sd_status == SD_OK) {
                        retval = RES_OK;
                } else {
                        retval = RES_PARERR;
                }
                return retval;
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
        DRESULT retval = RES_PARERR;

        switch (pdrv) {
        case ATA:
                switch (cmd) {
                case GET_SECTOR_COUNT:
                        //扇区数量（SDCARD卡容量 / 扇区大小）
                        *(DWORD *)buff = SDCardInfo.CardCapacity / SDCardInfo.CarBlockSize;
                        break;
                        //扇区大小
                case GET_SECTOR_SIZE:
                        *(WORD *)buff = SDCardInfo.CarBlockSize;
                        break;
                case GET_BLOCK_SIZE:
                        //同时擦除扇区的个数
                        *(DWORD *)buff = 1;
                        break;
                default:
                        break;
                }
                retval = RES_OK; 
        }

        return retval;
}

// 返回当前时间
DWORD get_fattime(void)
{
        return ( ((DWORD)(2022 - 1980) << 25)   //Year 2022
                        | ((DWORD)1 << 21)      //Month 1
                        | ((DWORD)1 << 16)      //Mday  1
                        | ((DWORD)0 << 11)      //Hour  0
                        | ((DWORD)0 << 5)       //Min   0
                        | ((DWORD)0 >> 1)       //Sec   0
                );
}
