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
        DSTATUS status = STA_NOINIT;

        switch (pdrv) {
        case SD_CARD :
                status &= ~STA_NOINIT;          //设备ID读取正确
	        break;
        case SPI_FLASH :
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
        int result;

        switch (pdrv) {
        case SD_CARD :
                if (SD_Init() != SD_OK) {
                        status  = STA_NOINIT;
                } else {
                        status &= ~STA_NOINIT;
                }
                return stat;

        case SPI_FLASH :
                break;
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

        switch (pdrv) {
        case SD_CARD :
                SD_ReadMultiBlocks(buff, sector * SDCardInfo.CarBlockSize, SDCardInfo.CarBlockSize, count);
                break;

        case SPI_FLASH :
                break;
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
                        *(DWORD *)buff = 2048;
                        break;
                case GET_SECTOR_SIZE  :         //返回扇区大小
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
DWORD get_fattime(void)
{
        return (0);
}
