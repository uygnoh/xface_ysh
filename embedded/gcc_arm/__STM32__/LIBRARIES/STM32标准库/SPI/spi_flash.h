#ifndef __SPI_H__
#define __SPI_H__
/*******************************************************************************
        => SPI__硬件引脚宏定义 
*******************************************************************************/
// SPI_NSS引脚配置
#define SPI_NSS_PORT            GPIOA
#define SPI_NSS_PIN             GPIO_Pin_4
#define SPI_NSS_HIGH()          GPIO_SetBits(SPI_NSS_PORT, SPI_NSS_PIN);
#define SPI_NSS_LOW()           GPIO_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN);
// SPI_SCLK引脚配置（串行时钟）
#define SPI_SCLK_PORT           GPIOA
#define SPI_SCLK_PIN            GPIO_Pin_5  
// SPI_MOSI引脚配置（主机发送，从机接收）
#define SPI_MOSI_PORT           GPIOA
#define SPI_MOSI_PIN            GPIO_Pin_7
// SPI_MISO引脚配置（主机接收，从机发送）
#define SPI_MISO_PORT           GPIOA
#define SPI_MISO_PIN            GPIO_Pin_6


#define SPI_TIMEOUT             1000


/*******************************************************************************
        => W25Q64__宏定义
*******************************************************************************/
#define DUMMY                   0x00
#define WRITE_ENABLE            0x06            // 写使能
#define WRITE_DISABLE           0x04            // 写禁止
#define READ_JEDEC_ID           0x9F            // 读取ID
#define ERASE_CHIP              0xC7            // 擦除芯片
#define ERASE_SECTOR            0x20            // 擦除扇区, 每次擦除(4KB)
#define READ_STATUS             0x05            // 读状态寄存器
#define READ_DATA               0x03            // 读取数据
#define PAGE_PROGRAM            0x02            // 写入数据（一次最多可以写256字节）
#define PAGE_SIZE               256             // 页大小
//______________________________________________________________________________
#define sFLASH_ID               0xEF3015        // W25X64
#define sFLASH_ID               0xEF4015        // W25Q16
#define sFLASH_ID               0xEF4017        // W25Q64
#define sFLASH_ID               0xEF4018        // W25Q128
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256
#endif
