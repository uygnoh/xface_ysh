/**
  *****************************************************************************
  *
  =============================================================================
  1. IIC总线通过上拉电阻(多器件才用)接正电源。
  2. 当总线空闲时，2根线均为高电平。
  3. 连接到总线的任意器件输出低电平，都将使总线的信号变低，即各器件的 SDA及SCL都是线 "与" 关系。
  4. 每个接到IIC总线的器件都有唯一的地址。(内部地址，外部地址)
  5. 通过器件的地址进行总线仲裁。
  6. 
 
  =============================================================================
  IIC总线的数据传送
  
  1. 数据位的有效性
     IIC总线进行数据传送时，时钟信号为高电平期间，数据线上的数据必须保持稳定；
     只有在时钟信号为低电平期间，数据线上的高电平或低电平才永许变化。
  
  2. 起始和终止信号
     起始信号：	SCL线为高电平，SDA线由高电平向低电平的变化
     终止信号：	SCL线为高电平，SDA线由低电平向高电平的变化
     
     起始信号和终止信号都是由主机发出
     在起始信号发出后总线处于占用状态
     在终止信号发出后总线处于空闲状态
     
   3. 数据帧格式
      IIC总线上传送数据信号是广义的，即包括地址信号，又包括真正的数据信号
      在起始信号后必须传送一个从机地址，共7位，第8位是数据传送的方向(R/T)
      用 "0"表示主机发送数据(T)
      用 "1"表示主机接收数据(R)
      每次数据传送都是由主机发送起始信号和终止信号
      但是，若主机希望继续占用总线进行新的数据传送，则可以不产生终止信号，
      马上在发送起始信号对另一个从机进行寻址。
      
    =============================================================================  
    总线寻址
    
    IIC总线协议有明确规定：采用 7位寻址字节(寻址字节是起始信号的第一个字节)
    
    D7~D1位 组成从机的地址。D0位 是数据的传送方向，0表示写，1表示读
    
    高位在前，地位在后
    
    
    1. 发送器件地址 	device_address
    2. 发送器件内部地址	word_address
    
     
  IIC串行总线
  
  SDA	数据线
  SCL	时钟线
  WP	写包含，高电平有效
  
  * 2018/10/30
  * @freeysh
  */



#include <reg51.h>

#define US 6		//延时时间值
sbit SCL = 
sbit SDA =


void i2c_signal_start(void)
{
	SDA = 1;
	delay_us(US);
	SCL = 1;
	delay_us(US);
	SDA = 0;
	delay_us(US);
	SCL = 0;
	delay_us(US);
	
}


void i2c_signal_stop(void)
{
	SDA = 0;
	delay_us(US);
	SCL = 1;
	delay_us(US);
	SDA = 1;
	delay_us(US);
	
	SDA = 0;
	SCL = 0;	
}



void i2c_signal_ack(void)
{
	u8 i;
	SCL = 1;
	delay_us(US);
	while ((SDA == 1) && (i < 200))
		i++;
	SCL = 0;
	delay_us(US);
}


void i2c_signal_init(void)
{
	SCL = 1;
	delay_us(US);
	SDA = 1;
	delay_us(US);
}


void i2c_signal_write_byte(u8 data)
{
	u8 i;
	
	for (i = 0; i < 8; i++)
	{
		SCL = 0;
		delay_us(US);
		SDA = (bit)(data & 0x80);	//数据传送由高到低,(bi)强制类型转换，1 or 0
		delay_us(US);
		SCL = 1;
		delay_us(US);
		data <<= 1;
	}
		
	SCL = 0;
	delay_us(US);
	SDA = 1;
	delay_us(US);
}



u8 i2c_signal_read_byte()
{
	u8 i, data = 0;
	SCL = 0;
	delay_us(US);
	SDA = 1;
	delay_us(US);
	
	for (i = 0; i < 8; i++)
	{
		SCL = 1;
		delay_us(US);
		data = (data<<1) | SDA;	//高位在前
		SCL = 0;
		delay_us(US);
	}
	
	return(data);
}









/*
void write_byte(u8 data)
{
	u8 i;
	
	for (i = 0; i < 8; i++)
	{
		data <<= 1;
		SCL = 0;
		delay_us(US);
		SDA = CY;	//CY是PSW寄存器中的 CY位
		delay_us(US);
		SCL = 1;
		delay_us(US);
	}
	
	SCL = 0;
	delay_us(US);
	SDA = 1;	//释放总线
	delay_us(US);
}
*/



/* 
	写入地址和数据
*/
void i2c_24c08_write_address_data(u8 address, u8 data)
{
	i2c_signal_start();
	i2c_signal_write_byte(0xA0);	//写器件地址
	i2c_signal_ack();		//写了后马上要应答
	i2c_signal_write_byte(address); //写，要往那个地址写数据 00~1023
	i2c_signal_ack();		//写了后马上要应答
	i2c_signal_write_byte(data);	//把数据写入
	i2c_signal_ack();		//写了后马上要应答
	i2c_signal_stop();		//给一个停止位，结束数据写入
}


/* 
	写入要读出的地址和读出器件内部的数据
*/
u8 i2c_24c08_read_address_data(u8 address)
{
	u8 data;
	i2c_signal_start();
	i2c_signal_write_byte(0xA0);	//写器件地址，写数据
	i2c_signal_ack();		//写了后马上要应答
	i2c_signal_write_byte(address); //写入要往那个地址把数据读出来
	i2c_signal_ack();		//写了后马上要应答
	
	i2c_signal_start();	
	i2c_signal_write_byte(0xA1);	//写器件地址,读数据
	i2c_signal_ack();
	data = i2c_signal_read_byte();
	i2c_signal_stop();
	return data;
	
	
}
void display(u8 bai, u8 shi)
{
	wei2 = 0;
	P0 = table[bai];
	delay_ms(5);
	wei2 = 1;
	
	wei1 = 0;
	P0 = table[shi];
	delay_ms(5);
	wei1 = 1;
	
	
}


void timer0(void) interrupt 1
{
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	num++;	//每中断一次自加1，每次中断约50MS
}
int main(void)
{
	i2c_signal_init();
	sec = i2c_24c08_read_address_data(2);
	if (sec > 99)		//防止第一次读出数据错误
		sec = 0;
	
	TMOD = 0x01;		//定时器工作方式1
	ET0  = 1;		//开启定时器中断使能
	EA   = 1;		//开启总中断
	TH0  = (65536-50000)/256;
	TL0  = (65536-50000)%256;
	
	TR0  = 1;		//开启定时器
	
	while (1)
	{
		display(sec/10, sec%10);
		if (num == 20)
		{
			num = 0;
			sec++;
			if (sec == 100)
				sec = 0;
			i2c_24c08_write_address_data(2, sec);
		}
	}
	
	
	
}
  
