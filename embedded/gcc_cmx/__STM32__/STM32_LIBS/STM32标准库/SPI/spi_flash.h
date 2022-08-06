#ifndef __SPI_H__
#define __SPI_H__
/******************************************************************************/
/*      SPI__硬件引脚宏定义                                                      */
/******************************************************************************/
//SPI_NSS引脚配置
#define SPI_NSS_PORT            GPIOA
#define SPI_NSS_PIN             GPIO_Pin_4
#define SPI_NSS_HIGH()          GPIO_SetBits(SPI_NSS_PORT, SPI_NSS_PIN);
#define SPI_NSS_LOW()           GPIO_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN);
//SPI_SCLK引脚配置（串行时钟）
#define SPI_SCLK_PORT           GPIOA
#define SPI_SCLK_PIN            GPIO_Pin_5  
//SPI_MOSI引脚配置（主机发送，从机接收）
#define SPI_MOSI_PORT           GPIOA
#define SPI_MOSI_PIN            GPIO_Pin_7
//SPI_MISO引脚配置（主机接收，从机发送）
#define SPI_MISO_PORT           GPIOA
#define SPI_MISO_PIN            GPIO_Pin_6

/******************************************************************************/
/*      W25Q64__宏定义                                                         */
/******************************************************************************/
#define DUMMY                   0x00
#define WRITE_ENABLE            0x06
#define READ_JEDEC_ID           0x9F    //读取ID
#define ERASE_SECTOR            0x20    //擦除扇区
#define READ_STATUS             0x05    //读状态寄存器
#define READ_DATA               0x03    //读取数据
#define PAGE_PROGRAM            0x02    //写入数据（一次最多可以写256字节）
#define PAGE_SIZE               256
#endif
