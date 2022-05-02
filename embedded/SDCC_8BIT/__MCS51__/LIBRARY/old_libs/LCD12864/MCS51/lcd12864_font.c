
有字库 LCD12864液晶


1. VSS		模块电源地	4.5~5.5 V
2. VDD		模块的电源正端	0 V
3. V0		LCD驱动电压输入端(通常接个 10K 的电阻到地，调节它的对比度)
4. RS(CS)	并行的 指令/数据 选择信号；串行的片选信号	H/L
5. R/W(SID)	并行的读写信号，串行的数据口		H/L
6. EN(CLK)	并行的使能信号，串行的同步时钟		H/L
7 ~ 14		数据0端口到数据7端口(8bit)		H/L

15. PSB		并行/串行接口选择，		H并行， L串行	
16. NC		空脚
17. RET		复位，低电平有效				H/L
18. NC		空脚
19. LED_A	背光源正极
20. LED_B	背光源负极

###################################################################
/* 
1.本程序为最简单的显示汉子程序，带字库的LCD12864
2.汉字显示坐标首地址
	line1 80H
	line2 90H
	line3 88H
	line4 98H

*/

#include <reg51.h>
#define uchar unsigned char
#define int unsigned int

sbit RS = P1^0;
sbit RW = P1^1;
sbit EN = P1^2;

uchar code tab1[] = "好好学习天天向上";
uchar code tab2[] = "hongkong";


void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x > 0; x--)
		for (y = 110; y > 0; y--);
}

void lcd12864_write_cmd(uchar cmd)
{
	RS = 0;
	RW = 0;
	EN = 0;
	delay_ms(1);
	P0 = cmd;	//把命令通过P0端口写给lcd12864液晶
	delay_ms(1);
	EN = 1;
	delay_ms(5);
	EN = 0;
	delay_ms(5);
}

void lcd12864_write_dat(uchar dat)
{
	RS = 1;
	RW = 0;
	EN = 0;
	delay_ms(1);
	P0 = dat;	//把数据通过P0端口写给lcd12864液晶
	delay_ms(1);
	EN = 1;
	delay_ms(5);
	EN = 0;
	delay_ms(5);
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

void lcd12864_write_string(uchar *ch)
{
	while (*ch != 0)
		lcd12864_write_dat(*ch++);
}

void lcd12864_display()
{
	uchar i;
	lcd12864_write_cmd(0x80);
	for (i = 0; i < 16; i++)
	{
		lcd12864_write_dat(tab1[i]);
		delay_ms(5);
	}
	
}

/* 显示一首诗词 */
void display()
{
	lcd12864_write_cmd(0x80);
	lcd12864_write_string("白日依山尽");
	lcd12864_write_cmd(0x90);
	lcd12864_write_string("黄河入海流");
	lcd12864_write_cmd(0x88);
	lcd12864_write_string("欲穷千里目");
	lcd12864_write_cmd(0x98);
	lcd12864_write_string("更上一层楼");
}

void display1(void)
{
	uchar i;
	lcd12864_write_cmd(0x80);
	for (i = 0; i < 16; i++)
	{
		lcd12864_write_dat(tab1[i]);
		delay_ms(5);
	}
}
void display2(void)
{
	uchar i;
	lcd12864_write_cmd(0x90);
	for (i = 0; i < 16; i++)
	{
		lcd12864_write_dat(tab2[i]);
		delay_ms(5);
	}
}

int main(void)
{
	lcd12864_init();
	lcd12864_display();
	
	/* 写入一个特殊汉字 */
	lcd12864_write_cmd(0x88);
	lcd12864_write_dat(0xF7);
	lcd12864_write_dat(0xD0);



	
	/* 使用字符串函数写入字符 */
	lcd12864_write_cmd(0x98);	
	lcd12864_write_string("QQ:961832097");
	while (1);
}
