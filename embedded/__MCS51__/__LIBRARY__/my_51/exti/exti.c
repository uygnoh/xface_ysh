#include <reg52.h>
#define uint16_t unsigned int
#define uint8_t  unsigned char 

sbit LED_00 = P0^0;
sbit LED_01 = P0^7;
sbit beep   = P1^7；
sbit tmp    = P3^2;     //增强现场保护

void delay_ms(uint16_t z)
{
        for (x = z; x > 0; x--) {
                for (y = 110; y > 0; y--);
        }
}

int main(void)
{
        EA  = 1;        //打开总中断
        EX0 = 1;        //打开外部中断0
        IT0 = 0;        //设定外部中断触发方式（IT0=0为低电平触发；IT0=1则为下降沿触发）
        while (!tmp) {  //一旦 P3^2 == 0, 进入死循环
                LED_00 = 0;
                delay_ms(500);
                LED_00 = 1;
                delay_ms(500);
        }
}

/*******************************************************************************
        => 外部中断_0中断服务程序
*******************************************************************************/
//一旦 P3^2 为低电平，则产生中断，进入中断子程序
void ext_00() interrupt 0       //中断子程序不用声明（ext_00外部中断名称）
{                               //interrupt_关键字_后面可以跟（0, 1, 2, 3, 4）
        LED_01 = 0;
        delay_ms(100);
        LED_01 = 1;
        delay_ms(100);
}
