#ifndef __SPI_H__
#define __SPI_H__


/******************************************************************************/
/*      SPI_25AA020A_2Kbit(Microchip)_硬件连接                                  */
/******************************************************************************/
        SCK     //SCLK_串行时钟线
        SI      //MOSI_串行数据输出
        SO      //MISO_串行数据输入
        CS      //NSS__片选信号线
        HOLD    //保持输入
        WP      //写保护

/******************************************************************************/
/*      SPI_25AA020A指令集 宏定义                                               */
/******************************************************************************/
#define READ    0x03    //从所选地址开始 从存储器陈列读数据
#define WRITE   0x02    //从所选地址开始 向存储器陈列写数据
#define WREN    0x06    //置 1 写使能锁存器    (使能写操作)
#define WRDI    0x04    //复位写使能使能锁存器 (禁止写操作)
#define RDSR    0x05    //读STATUS寄存器
#define WRSR    0x01    //写STATUS寄存器


#endif
