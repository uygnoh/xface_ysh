#include "spi.h"

/*******************************************************************************
  函数名称: spi_write()
  输入参数: (uint8_t dat)，要写入的数据
  输出参数: 无
  函数功能: 写入一个字节数据(高位在前， 低位在后) //从最高位开始, 先把数据准备好
          从机在上升沿采样， 在上升沿之前“主机”要把数据准备好
*******************************************************************************/
void spi_write(uint8_t dat)
{
        uint8_t i;
        for (i = 0; i < 8; i++) {               //高位在前，低位在后
                SCLK = 0;                       //时钟线拉低, 先把数据准备好
                if ((dat & 0x80) == 0x80) {     //判断当前传输位是“1”还是“0”
                        MOSI = 1;               //从机接收数据，主机发送数据
                } else {
                        MOSI = 0;
                }
                dat <<= 1;                      //准备下一个数据位
                SCLK = 1;                       //上升沿，“从机”数据采样
        }
}

/*******************************************************************************
  函数名称: spi_read()
  输入参数: 无
  输出参数: 返回从SPI总线上读取到一个字节的数据(高位在前， 低位在后)
  函数功能: 读入一个字节数据， 主机在上升沿采样， 在上升沿之前“从机”要把数据准备好
*******************************************************************************/
uint8_t spi_read(void)
{
        uint8_t i;
        uint8_t dat;
        for (i = 0; i < 8; i++) {
                SCLK  = 0;              //时钟下降沿期间，从机准备好数据
                SCLK  = 1;              //来一个上升沿，主机采样总线上的数据
                dat <<= 1;              //dat右移1位
                if (MISO == 1) {        //从机发送数据，主机接收数据
                        dat |= 0x01;
                } else {
                        dat &= 0xFE;
                }
        }
        return(dat);
}

/*******************************************************************************
  函数名称: eeprom_wrirte_enable()
  输入参数: 无
  输出参数: 无
  函数功能: 写使能（使用WREN指令）
*******************************************************************************/
void eeprom_wrirte_enable(void)
{
        CS = 0;
        spi_write(WREN);
        CS = 1;
}

/*******************************************************************************
  函数名称: eeprom_read_byte()
  输入参数: 无
  输出参数: addr，从那个地址中读出数据
  函数功能: 向eeprom中读出一个字节数据
*******************************************************************************/
uint8_t eeprom_read_byte(uint8_t addr)
{
        uint8_t dat;
        CS = 0;                 //片选信号
        spi_write(READ);        //写入“读”命令
        spi_write(addr);        //写入要读的地址
        dat = spi_read();       //返回读出的字节
        CS = 1;                 //片选信号
}

/*******************************************************************************
  函数名称: eeprom_read_byte()
  输入参数: 无
  输出参数: addr，从那个地址中写入数据
  输出参数: dat， 写入的数据
  函数功能: 向eeprom中写入一个字节数据
*******************************************************************************/
void eeprom_write_byte(uint8_t addr, uint8_t dat)
{
        uint8_t state;
        eeprom_wrirte_enable(); //在准备写入数据之前，要(使能写操作)
        CS = 0;
        spi_write(WRITE);  //写入“写”命令
        spi_write(addr);   //写入器件内部地址
        spi_write(dat);    //写入数据
        //_________________________________________________ 
        //在写周期中，也可以读STATUS寄存器的状态（可以多字节写入）
        //_________________________________________________ 
        while (1) {
                CS = 0;
                spi_write(RDSR);   //写入的指令，是读状态寄存器的指令
                state = spi_read();//读出状态寄存器中的内容
                if ((state & 0x01) == 0)//为“1”时，表明写操作正在进行
                        break;
                CS = 1;
        }   
        CS = 1;
}
