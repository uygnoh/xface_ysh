#include "ds1302.h"
/*******************************************************
 * DS1302 底层驱动
 * 1 主机向ds1302写入一个字节
 * 2 主机从ds1302中读取一个字节
 *
 *******************************************************/
/* 向DS1302写入一个字节 */ 
void ds1302_write_byte(uint8_t dat)
{
    uint8_t i;
    
    for (i = 0; i < 8; i++) 
    {   
        // % 数据从最低位开始传送
        // % 单片机在时钟的下降沿要把数据先准备好                   
        // % 把“dat”的最低位放入“DS1302_IO”端口上
        DS1302_IO = dat & 0x01; 
        dat >>= 1;          // % 将“dat”向右移“1”位
        SCLK = 1;           // % DS1302在时钟的上升沿采样，单片机把数据输出到总线上
        delay_us(1);        // % 稍作延时
        SCLK = 0;           // % 单片机在时钟的下降沿要把数据先准备好
        delay_us(1);        // % 稍作延时
    }
}

/* % 从DS1302中读取一个字节，使用移位的方法*/
uint8_t ds1302_read_byte(void)
{
    uint8_t tmp;
    uint8_t dat = 0;
    
    for (tmp = 0x01; tmp != 0; tmp<<=1)
    {                       // % 数据从最低位开始传送
        if (DS1302_IO != 0) // % 判断“DS1302_IO”端口上的数据是“0”还是“1”
            dat |= tmp;     // % 为“1”则把“tmp”中的数据存储到“dat”中
        SCLK = 1;           // % 单片机在时钟的上升沿采样，DS1302把数据输出到总线上
        delay_us(1);        // % 稍作延时
        SCLK = 0;           // % DS1302在时钟的下降沿要把数据准备好
        delay_us(1);        // % 稍作延时
    }   
    return dat;
}



/*******************************************************
 * DS1302 功能函数
 * 1 主机向ds1302寄存器中写入数据
 * 2 主机从ds1302寄存器中读出数据
 * 3 ds1302初始化
 * 4 主机从ds1302寄存器中读出时间
 * 
 *******************************************************/
/* 1 % 向ds1302寄存器中写入数据 */
void ds1302_write_register(uint8_t cmd, uint8_t dat)
{
    CE   = 0;           // % 初始化“CE”为低“0”
    delay_us(1);        // % 稍作延时
    SCLK = 0;           // % 初始化“SCLK”为低“0”
    delay_us(1);        // % 稍作延时
    CE   = 1;           // % 再把“CE”拉高，使能DS1302芯片
    delay_us(1);        // % 稍作延时
    ds1302_write_byte(cmd);
    ds1302_write_byte(dat);
    CE   = 0;           // % 先把“CE”拉低,完成一次操作
}

/* 2 % 从ds1302寄存器中读出数据 */
/* 读出的数据，读出的“dat”是BCD码格式 */
uint8_t ds1302_read_register(uint8_t cmd)
{
    uint8_t dat;
    
    CE   = 0;           // % 初始化“CE”为低“0”
    delay_us(1);        // % 稍作延时
    SCLK = 0;           // % 初始化“SCLK”为低“0”
    delay_us(1);        // % 稍作延时
    CE   = 1;           // % 再把“CE”拉高，使能DS1302芯片
    delay_us(1);        // % 稍作延时
    ds1302_write_byte(cmd);
    dat = ds1302_read_byte();
    CE   = 0;           // % 先把“CE”拉低,完成一次操作
    
    return dat;
}

/* 3 % ds1302初始化 */
void ds1302_init(void)
{
    uint8_t i;
    
    ds1302_write_register(0x8E, 0x00) // % 关闭写保护位
    for (i = 0; i < 7; i++)
    {
        ds1302_write_register(write_rtc_cmd[i], ds1302_time[i]);
    }
    ds1302_write_register(0x8E, 0x80) // % 打开写保护位
}

/* 4 % 从ds1302中读出时间 */
void ds1302_read_time(void)
{
    uint8_t i;
    
    for (i = 0; i < 7; i++)
    {
        ds1302_time[i] = ds1302_read_register(read_rtc_cmd[i]);
    }
}
 
 

/*******************************************************
 * DS1302 RAM(31Byte)
 * 1 主机向ds1302_ram中写入一个字节数据
 * 2 主机从ds1302_ram中读出一个字节数据
 * 
 *******************************************************/
// 向ds1302_ram中写入一个字节数据
// % RAM_ADDR: 0xC0 ~ FC
// % 最低位为“0”的时候为写， 最低位为“1”的时候为读
// % 0xC0为写
// % 0xC1为读
void ds1302_write_ram(uint8_t addr, uint8_t dat)
{
    ds1302_write_register(0x8E, 0x00) // % 关闭写保护位
    ds1302_write_register(addr, dat) // % 
    ds1302_write_register(0x8E, 0x80) // % 打开写保护位
}

// 从ds1302_ram中读出一个字节数据
// % RAM_ADDR: 0xC1 ~ FD
// % 最低位为“0”的时候为写， 最低位为“1”的时候为读
// % 0xC0为写
// % 0xC1为读
uint8_t ds1302_read_ram(uint8_t addr)
{
    uint8_t dat;
    dat = ds1302_read_register(addr); 
    return dat;
}

 
 
/*******************************************************
 * DS1302 Burst模式
 * 1 Burst模式_主机向ds1302寄存器中写入 8 个字节的数据
 * 2 Burst模式_主机从ds1302寄存器中连续读取8个字节
 * 3 Burst模式_ds1302初始化
 * 
 *******************************************************/
 // 1 % Burst模式，写入 8 个字节的数据
void ds1302_burst_write(void)
{
    uint8_t i;
    CE   = 0;           // % 初始化“CE”为低“0”
    delay_us(1);        // % 稍作延时
    SCLK = 0;           // % 初始化“SCLK”为低“0”
    delay_us(1);        // % 稍作延时
    CE   = 1;           // % 再把“CE”拉高，使能DS1302芯片
    delay_us(1);        // % 稍作延时
    
    ds1302_write_register(0x8E, 0x00) // % 关闭写保护位
    ds1302_write_byte(BURST_WRITE);   // % 0xBE命令，指的是Burst模式
    for (i = 0; i < 8; i++)
    {
        ds1302_write_byte(ds1302_time[i]);
    }
    ds1302_write_register(0x8E, 0x80) // % 打开写保护位
}

// 2 % Burst模式, 连续读取8个字节,存放到 *pbuf中
void ds1302_burst_read(uint8_t *pbuf)
{
    uint8_t i;
    CE   = 0;           // % 初始化“CE”为低“0”
    delay_us(1);        // % 稍作延时
    SCLK = 0;           // % 初始化“SCLK”为低“0”
    delay_us(1);        // % 稍作延时
    CE   = 1;           // % 再把“CE”拉高，使能DS1302芯片
    delay_us(1);        // % 稍作延时
    ds1302_write_byte(BURST_READ); // % 0xBE命令，指的是Burst模式
    for (i = 0; i < 8; i++)
    {
        pbuf[i] = ds1302_read_byte();
    }
    CE   = 0;           // % 初始化“CE”为低“0”
}

 // 3 % Burst模式，ds1302初始化
void ds1302_burst_init(void)
{
    uint8_t status;
    status = ds1302_read_register(0x81);    // % 读秒寄存器的值
    // % 判断秒寄存器的最高位是“0”还是“1”
    // % “0”表示时钟走时， “1”表示时钟停止
    // % 是“0”的话，不进行初始化操作
    if ((status & 0x80) != 0)
    {   
        ds1302_write_register(0x8E, 0x00) // % 关闭写保护位
        ds1302_burst_write();
        ds1302_write_register(0x8E, 0x80) // % 打开写保护位
    }
}


 
/*******************************************************
 * DS1302 Burst_RAM模式
 * 1 Burst_RAM模式_向起始地址开始写入数据到ds1302_RAM
 * 2 Burst_RAM模式_从ds1302_RAM起始地址开开始读取数据
 * 
 *******************************************************/
// 1 % Burst_RAM模式_向起始地址开始写入数据到ds1302_RAM
// Burst_RAM模式只能从“0xC0”地址处， 连续写入，最多写31字节
void ds1302_burst_write_ram(uint8_t *pbuf, uint8_t len)
{
    uint8_t i;
    if (len < 32)           // % RAM中只有31个字节
    {
        CE   = 0;           // % 初始化“CE”为低“0”
        delay_us(1);        // % 稍作延时
        SCLK = 0;           // % 初始化“SCLK”为低“0”
        delay_us(1);        // % 稍作延时
        CE   = 1;           // % 再把“CE”拉高，使能DS1302芯片
        delay_us(1);        // % 稍作延时
        
        ds1302_write_register(0x8E, 0x00) // % 关闭写保护位
        ds1302_write_byte(BURST_RAM_WRITE); // % 0xFE命令，指的是BurstRam模式
        for (i = 0; i < len; i++)
                ds1302_write_byte(pbuf[i]);
        ds1302_write_register(0x8E, 0x80) // % 打开写保护位
    }
}

// 2 % Burst_RAM模式_从ds1302_RAM起始地址开开始读取数据
// Burst_RAM模式只能从“0xC1”地址处， 连续读入，最多读31字节
void ds1302_burst_read_ram(uint8_t *pbuf, uint8_t len)
{
    uint8_t i;
    if (len < 32)           // % RAM中只有31个字节
    {
        CE   = 0;           // % 初始化“CE”为低“0”
        delay_us(1);        // % 稍作延时
        SCLK = 0;           // % 初始化“SCLK”为低“0”
        delay_us(1);        // % 稍作延时
        CE   = 1;           // % 再把“CE”拉高，使能DS1302芯片
        delay_us(1);        // % 稍作延时
        
        ds1302_write_register(0x8E, 0x00) // % 关闭写保护位
        ds1302_write_byte(BURST_RAM_READ); // % 0xFF命令，指的是BurstRam模式
        for (i = 0; i < len; i++)
                pbuf[i] = ds1302_read_byte();
        ds1302_write_register(0x8E, 0x80) // % 打开写保护位
    }
} 
  
 
 
