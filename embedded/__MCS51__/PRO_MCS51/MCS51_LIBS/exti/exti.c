#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char 

sbit D0=P0^0;
sbit D1=P0^7;
sbit beep=P1^7；

sbit temp=P3^2;	//增强现场保护

void delay_ms(uint z)
{
    for (x = z; x > 0; x--) 
    {
        for (y = 110; y > 0; y--);
    }
}

int main(void)
{
    EA = 1;     //打开总中断
    EX0 = 1;    //打开外部中断0
    IT0 = 0;    //设定外部中断0为 低电平触发方式，如果 IT0=1,则为下降沿触发方式
    while (!temp)//一旦 P3^2==0,进入死循环
    {
        D0 = 0;
        delay_ms(500);
        D1 = 1;
        delay_ms(500);
    }
}

/* 外部中断 0 */
void exter0() interrupt 0	//中断子程序不用声明
{                           //后面可以跟 0,1,2,3,4
    D0 = 0;
    delay_ms(100);
    D1 = 1;
    delay_ms(100);
}


/* 一旦 P3^2 为低电平，则产生中断，进入中断子程序 */


