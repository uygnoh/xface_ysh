/******************************************************************************
  * 无字库的 lcd12864液晶程序
  * 1.Vdd		模块电源 +5v
  * 2.Vss		模块电源 地
  * 3.Vo  0~10V		外部液晶偏置(负压)输入端
  4~11			并行通信数据线
  * 12.CS1		左半屏使能(低电平有效)
  * 13.CS2		右半屏使能(低电平有效)
  * 14.RST		复位(低电平有效)
  * 15.R/W		H:读数据	L:写数据
  * 16.D/I		H:数据		L:指令
  * 17.EN		模块使能端
  * 18.Vss		模块电源地
  * 19.LED-A		LED背光源 +5V
  * 20.LED-K		LED背光源 +0V
  A.在背光电路中需要接串联 5欧姆的电阻，直接将背光源接入电源可能造成液晶损坏
  B.请在 DB0～DB7数据线中加入 10K上拉电阻，特别是使用单片机中的3态 IO时。
  C.Vo需要一个外部的 0v~10v 负压输入，使液晶显示，可以串联电位器以调节液晶灰度。
  
  设置列(Y地址)		列地址设置(0~63)
  设置页码(X地址)	页码设置(0~7)
  设置起始地址(Z地址)	显示起始地址设置(0~63)
 
  lcd12864是由左右两片 64*64 组成，使用 CS1/CS2使能(可同时使能)。
  每个半屏 8页，每个页中字节数据由低到高
***/

使用 Pctolcd取模软件，选择设置为； 阴码，逆向，列行式。


#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

#define display_on 0x38		//开显示
#define display_off 0x3E	//关显示
#define col_addr 0x40		//列地址
#define page_addr 0xB8		//页地址
#define start_line 0xC0		//起始地址


sbit DI  = P1^0
sbit RW  = P1^1;
sbit EN  = P1^2;
sbit CS1 = P1^3;
sbit CS2 = P1^4;
sbit RST = P1^5;


uchar code Chinese[][32] = {};


void delay_ms(uint z)
{
	uint x, y;
	for (x = z; x > 0; x--)
		for (y = 110; y > 0; y--);
}

void lcd12864_write_left_cmd(uchar cmd)
{
	CS1 = 1;
	CS2 = 0;
	DI  = 0;
	RW  = 0;
	P0  = cmd;
	delay_ms(1);
	EN  = 1;
	delay_ms(1);
	EN  = 0;
}


void lcd12864_write_right_cmd(uchar cmd)
{
	CS1 = 0;
	CS2 = 1;
	DI  = 0;
	RW  = 0;
	P0  = cmd;
	delay_ms(1);
	EN  = 1;
	delay_ms(1);
	EN  = 0;
}

void lcd12864_write_left_dat(uchar dat)
{
	CS1 = 1;
	CS2 = 0;
	DI  = 1;
	RW  = 0;
	P0  = dat;
	delay_ms(1);
	EN  = 1;
	delay_ms(1);
	EN  = 0;
}


void lcd12864_write_right_cmd(uchar dat)
{
	CS1 = 0;
	CS2 = 1;
	DI  = 1;
	RW  = 0;
	P0  = dat;
	delay_ms(1);
	EN  = 1;
	delay_ms(1);
	EN  = 0;
}

void lcd12864_clear_left()
{
	uchar j, k;
	CS1 = 1;
	CS2 = 0;
	lcd12864_write_left_cmd(page_addr+0);
	lcd12864_write_left_cmd(col_addr+0);
	for (k = 0; k < 8; k++)
	{
		lcd12864_write_left_cmd(page_addr+k);
		for (j = 0; j < 64; j++)
		{
			lcd12864_write_left_dat(0x00);
		}
	}
}




void lcd12864_clear_right()
{
	uchar j, k;
	CS1 = 1;
	CS2 = 0;
	lcd12864_write_right_cmd(page_addr+0);
	lcd12864_write_right_cmd(col_addr+0);
	for (k = 0; k < 8; k++)
	{
		lcd12864_write_right_cmd(page_addr+k);
		for (j = 0; j < 64; j++)
		{
			lcd12864_write_right_dat(0x00);
		}
	}
}
void lcd12864_init()
{
	RST = 0;
	delay_ms(50);
	RST = 1;
	delay_ms(50);
	lcd12864_write_left_cmd(display_off);
	lcd12864_write_right_cmd(display_off);
	lcd12864_write_left_cmd(page_addr+0);
	lcd12864_write_right_cmd(page_addr+0);
	lcd12864_write_left_cmd(start_line+0);
	lcd12864_write_right_cmd(start_line+0);
	
	lcd12864_write_left_cmd(col_addr+0);
	lcd12864_write_right_cmd(col_addr+0);
	
	lcd12864_write_left_cmd(display_on);
	lcd12864_write_right_cmd(display_on);
}


/******************************************************************************
	写入中文字符
	page 是页
	col 是列
	num 是字的顺序编号
*/
void Chinese_display_left(uchar page, uchar col, uchar num)
{
	uchar i, j;
	CS1 = 0;
	CS2 = 1;
	for (i = 0; i < 2; i++)		//应为是两个汉字,横向占2个字节
	{
		lcd12864_write_left_cmd(page_addr+page+i);
		lcd12864_write_left_cmd(col_addr+col);
		for (j = 0; j < 16; j++)
		{
			lcd12864_write_left_dat(Chindes[num][16*i+j]);
		}
	}
}

void Chinese_display_right(uchar page, uchar col, uchar num)
{
	uchar i, j;
	CS1 = 1;
	CS2 = 0;
	for (i = 0; i < 2; i++)		
	{
		lcd12864_write_right_cmd(page_addr+page+i);
		lcd12864_write_right_cmd(col_addr+col);
		for (j = 0; j < 16; j++)
		{
			lcd12864_write_right_dat(Chindes[][16*i+j]);
		}
	}
}


/******************************************************************************
	写入英文字符
	page 是页
	col 是列
	num 是字的顺序编号
*/
void English_display_left(uchar page, uchar col, uchar num)
{
	uchar i, j;
	CS1 = 0;
	CS2 = 1;
	for (i = 0; i < 2; i++)		//应为是两个汉字,横向占2个字节
	{
		lcd12864_write_left_cmd(page_addr+page+i);
		lcd12864_write_left_cmd(col_addr+col);
		for (j = 0; j < 8; j++)
		{
			lcd12864_write_left_dat(English[num][8*i+j]);
		}
	}
}

void English_display_right(uchar page, uchar col, uchar num)
{
	uchar i, j;
	CS1 = 1;
	CS2 = 0;
	for (i = 0; i < 2; i++)		
	{
		lcd12864_write_right_cmd(page_addr+page+i);
		lcd12864_write_right_cmd(col_addr+col);
		for (j = 0; j < 8; j++)
		{
			lcd12864_write_right_dat(Enlish[][8*i+j]);
		}
	}
}


int main(void)
{
	lcd12864_init();
	lcd12864_clear_left();
	lcd12864_clear_right();
	lcd1602_display_left(0, 0, 0);
	lcd1602_display_left(0, 16, 1);
	lcd1602_display_left(0, 32, 2);
	lcd1602_display_left(0, 48, 3);
	
	lcd1602_display_right(0, 0, 4);
	lcd1602_display_right(0, 16, 5);
	lcd1602_display_right(0, 32, 6);
	lcd1602_display_right(0, 48, 7);
	
}



