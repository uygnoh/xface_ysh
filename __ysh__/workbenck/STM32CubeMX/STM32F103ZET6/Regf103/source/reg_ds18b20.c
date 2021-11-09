#include "common.h"
//DS18B20_IO__方向设置
#define DS18B20_IO_IN()  do{GPIOG->CRH &= 0XFFFF0FFF; GPIOG->CRH |= 8<<12;}while(0)
#define DS18B20_IO_OUT() do{GPIOG->CRH &= 0XFFFF0FFF; GPIOG->CRH |= 3<<12;}while(0)
//DS18B20_IO__操作函数
#define DS18B20_DQ_IN  PGin(11)  //数据端口 PG11
#define DS18B20_DQ_OUT PGout(11) //数据端口 PG11
/*******************************************************************************
  函数名称: void ds18b20_rst(void)
  输入参数: 无
  输出参数: 无
  函数功能: 复位DS18B20
*******************************************************************************/
void ds18b20_rst(void)
{
        DS18B20_IO_OUT();       //SET PG11 OUTPUT
        DS18B20_DQ_OUT=0;       //拉低DQ
        delay_us(750);          //拉低750us
        DS18B20_DQ_OUT=1;       //DQ=1
        delay_us(15);           //15US
}
/*******************************************************************************
  函数名称: uint8_t ds28b20_check(void)
  输入参数: 无
  输出参数:（返回1）:未检测到DS18B20的存在
  输出参数:（返回0）:存在
  函数功能: 等待DS18B20的回应
*******************************************************************************/
uint8_t ds28b20_check(void)
{
        uint8_t retry = 0;
        DS18B20_IO_IN();
        while (DS18B20_DQ_IN && retry < 200) {
                retry++;
                delay_us(1);
        };
        if(retry >= 200) {
                return (1);
        } else {
                retry = 0;
        }

        while (!DS18B20_DQ_IN && retry < 240) {
                retry++;
                delay_us(1);
        };
        if(retry >= 240) {
                return (1);
        }
        return 0;
}
/*******************************************************************************
  函数名称: uint8_t ds18b20_read_bit(void)
  输入参数: 无
  输出参数: 返回值：1/0
  函数功能: 从DS18B20读取一个位
*******************************************************************************/
uint8_t ds18b20_read_bit(void)
{
        uint8_t data;
        DS18B20_IO_OUT();       //SET PG11 OUTPUT
        DS18B20_DQ_OUT=0;
        delay_us(2);
        DS18B20_DQ_OUT=1;
        DS18B20_IO_IN();        //SET PG11 INPUT
        delay_us(12);
        if (DS18B20_DQ_IN) {
                data = 1;
        } else {
                data=0;
        }
        delay_us(50);
        return data;
}
/*******************************************************************************
  函数名称: uint8_t ds18b20_read_byte(void)
  输入参数: 无
  输出参数: 返回值：读到的数据
  函数功能: 从DS18B20读取一个字节
*******************************************************************************/
uint8_t ds18b20_read_byte(void)
{
        u8 i, j, dat;
        dat = 0;
        for (i = 1;i <= 8; i++) {
                j   = ds18b20_reae_bit();
                dat = (j<<7) | (dat>>1);
        }
        return dat;
}
/*******************************************************************************
  函数名称: void ds18b20_write_byte(uint8_t dat)
  输入参数: dat：要写入的字节
  输出参数: 无
  函数功能: 写一个字节到DS18B20
*******************************************************************************/
void ds18b20_write_byte(uint8_t dat)
{
        uint8_t i;
        uint8_t tmp;
        DS18B20_IO_OUT();                       //SET PG11 OUTPUT;
        for (i = 1; i <= 8; i++) {
                tmp = dat & 0x01;
                dat=dat>>1;
                if (tmp) {
                        DS18B20_DQ_OUT=0;       // Write 1
                        delay_us(2);
                        DS18B20_DQ_OUT=1;
                        delay_us(60);
                } else {
                        DS18B20_DQ_OUT=0;       // Write 0
                        delay_us(60);
                        DS18B20_DQ_OUT=1;
                        delay_us(2);
                }
        }
}
//开始温度转换
void ds18b20_start(void)
{
        ds18b20_rst();
        ds18b20_check();
        DS18B20_Write_Byte(0xcc);   // skip rom
        DS18B20_Write_Byte(0x44);   // convert
}
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在
uint8_t ds18b20_init(void)
{
        RCC->APB2ENR |= 1<<8;           //使能PORTG口时钟
        GPIOG->CRH   &= 0XFFFF0FFF;     //PORTG.11 推挽输出
        GPIOG->CRH   |= 0X00003000;
        GPIOG->ODR   |= 1<<11;          //输出1
        ds18b20_rst();
        return ds18b20_check();
}
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250）
short ds18b20_get_temperatur(void)
{
        uint8_t flag;
        uint8_t tl, th;
        short temperature;
        ds18b20_start ();               // ds1820 start convert
        ds18b20_rst();
        ds18b20_check();
        ds18b20_write_byte(0xcc);       // skip rom
        ds18b20_write_byte(0xbe);       // convert
        tl = ds18b20_Read_Byte();       // LSB
        th = ds18b20_Read_Byte();       // MSB

        if (th > 7) {
                th   =~ th;
                th   =~ tl;
                flag = 0;       //温度为负
        } else {
                flag = 1;       //温度为正
        }

        temperature   = th;
        temperature <<= 8;
        temperature  += tl;
        temperature   = (float)temperature * 0.0625;
        if (flag) {
                return temperature;
        } else {
                return -temperature;
        }
}















