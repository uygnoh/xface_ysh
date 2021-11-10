/******************************************************************************
  * lcd12864串口行接口程序
  * PSB = 0;	串行通信
  * RS[CS]	串行通信片选端口
  * RW[SID]	串行通信数据线
  * EN[CLk)	串行通信的同步时钟
  * 数据是高位在前
  串行通信数据传输分 3个字节 完成
  1. 第一个字节：串口控制格式 11111ABC
  	A 为数据传送方向控制，H表示数据从 LCD到MCU，L表示数据从MCU到LCD。
  	B 为数据类型，H表示数据是显示数据，L表示数据是控制指令
  	C 固定为0
  2. 第二个字节：(并行)8位数据的高4位 格式 DDDD0000	[第一次传送的是字节的高4位，低4位舍去]
  
  2. 第三个字节：(并行)8位数据的低4位 格式 0000DDDD  [第二次传送的是字节的低4位，高4位舍去]	
  
  */
  
  
#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

/* 片选信号(为高电平有效，51单片机开机默认为高电平)，所以此引脚可以不接 */	        
sbit CS  = P1^0;	


sbit SID = P1^1;	//数据信号
sbit CLK = P1^2;	//时钟信号
sbit PSB = P1^3;	//通信选择信号,低电平位串行通信方式

void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x > 0; x--)
		for (y = 110; y > 0; y--);
}


void lcd12864_send_byte(uchar dat)
{
	uchar i;
	for (i = 0; i < 8; i++)
	{
		CLK = 0;
		dat = dat<<1;	//把数据的高位移到进位标志位 CY位中
		SDI = CY;	//把数据从 CY位中放到串行数据线上
		CLK = 1;
		CLK = 0;
	}
}

/* 写命令函数 */
void lcd12864_write_cmd(uchar cmd)
{
	lcd12864_send_byte(0xf8);		//等同于写命令
	lcd12864_send_byte(0xf0 & cmd);		//命令的高4位
	lcd12864_send_byte(0xf0 & cmd<<4);	//命令的低4位
}

/* 写数据函数 */
void lcd12864_write_dat(uchar dat)
{
	lcd12864_send_byte(0xfA);		//等同于写数据
	lcd12864_send_byte(0xf0 & dat);		//命令的高4位
	lcd12864_send_byte(0xf0 & dat<<4);	//命令的低4位
}


void lcd12864_write_string(uchar *ch)
{
	while (*ch != 0)
		lcd12864_write_dat(*ch++);
}



void lcd12864_init()
{
	delay_ms(100);
	lcd12864_write_cmd(0x30);	//启动标准的显示形式
	delay_ms(1);
	lcd12864_write_cmd(0x30);
	delay_ms(1);
	lcd12864_write_cmd(0x0E);	//打开所有显示
	delay_ms(1);
	lcd12864_write_cmd(0x0C);	//不显示光标
	delay_ms(1);
	lcd12864_write_cmd(0x06);	//地址指针自动加 1
	delay_ms(1);
	lcd12864_write_cmd(0x01);	//清屏
	delay_ms(1);
}



int main(void)
{
	PSB = 0;
	lcd12864_init();
	lcd1602_display();
}
