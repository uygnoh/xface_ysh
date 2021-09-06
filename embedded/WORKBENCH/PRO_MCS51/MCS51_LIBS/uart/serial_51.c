#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
 
uchar serial_temp,serial_flag;
void serial8051_init();
int main(void)
{
    serial8051_init();
    while(1)
    {
        if(serial_flag==1)
        {
            serial_flag=0;
            SBUF=serial_temp;
        }
    }
    return 0;
}
//串行波特率600
void serial8051_init()
{
    //串行控制寄存器SCON:设置串口的工作方式1;串行接受允许控制位(REN)启动。
    SCON=0x50;
    //串行波特率设置
    TMOD=0x20;  //设置定时器1的工作方式为2
    TH1=0xcc; //装初值
    TL1=0xcc;
    TR1=1;//启动定时器1
    EA=1;//开总中断
    ES=1;//开串行口中断
}
void serial8051() interrupt 4
{
//  if(RI==1)
//  {
        RI=0;
        P2=SBUF;
        serial_flag=1;
        serial_temp=SBUF;
//  }
}
