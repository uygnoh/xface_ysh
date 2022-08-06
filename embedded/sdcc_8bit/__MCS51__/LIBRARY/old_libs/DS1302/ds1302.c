#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
 
sbit SCLK=P3^6;
sbit CE=P3^5;
sbit DSIO=P3^4;
uchar ds1302_time_flag;
 
void ds1302_write(uchar address, uchar dat);
uchar ds1302_read(uchar address);
void ds1302_init();
void display_smg_4();
void delayus();
void delayms(uint z);
 
//---DS1302写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
uchar code read_rtc_address[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
uchar code write_rtc_address[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
uchar code smg_table[]={ //共阴数码管编码表
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c, 
0x39,0x5e,0x79,0x71};
 
int main(void)
{
    ds1302_init();
    while(1)
    {
        display_smg_4();
    }
}
 
void ds1302_write(uchar address, uchar dat)
{
    uchar number;
    CE = 0;
    delayus();
    SCLK = 0;
    delayus();
    CE = 1;
    delayus();
    for(number=0;number<8;number++)//开始传送八位地址命令
    {
        DSIO=address&0x01;//数据从低位开始传送
        address >>= 1;
        delayus();
        SCLK=1;//数据在上升沿时，DS1302读取数据
        delayus();
        SCLK=0;
        delayus();
    }
    for(number=0;number<8;number++)//写入8位数据
    {
        DSIO=dat&0x01;//数据从低位开始写入
        dat >>= 1;
        SCLK=1;//数据在上升沿时，DS1302读取数据
        delayus();
        SCLK=0;
        delayus();
    }
    CE=0;//传送数据结束
    delayus();
}


// 读取一个地址的数据
uchar ds1302_read(uchar address)
{
    uchar number,dat,dat1;
    CE=0;
    delayus();
    SCLK = 0;
    delayus();
    CE=1;
    delayus();
     
    for(number=0;number<8;number++)//开始传送八位地址命令
    {
        DSIO=address&0x01;//数据从低位开始传送
        address >>= 1;
        SCLK=1;//数据在上升沿时，DS1302读取数据
        delayus();
        SCLK=0; //DS1302下降沿时，放置数据
        delayus();
    }
    for(number=0;number<8;number++)
    {
        dat1=DSIO;
        dat = (dat>>1) | (dat1<<7);
        SCLK=1;
        delayus();
        SCLK=0;
        delayus();
    }
    CE=0;
    delayus();
    return dat;
}
 
/******************************************
* 函 数 名         : ds1302_init
* 函数功能         : 初始化ds1302.
* 输    入         : 无
* 输    出         : 无
*******************************************/
void ds1302_init()
{
    ds1302_write(0x8e,0x00);//禁止写保护，就是关闭写保护功能
    ds1302_write(write_rtc_address[0], ((19/10)<<4 | (19%10)));
    ds1302_write(write_rtc_address[1], ((19/10)<<4 | (19%10)));
    ds1302_write(write_rtc_address[2], ((23/10)<<4 | (23%10)));
    ds1302_write(write_rtc_address[3], ((31/10)<<4 | (31%10)));
    ds1302_write(write_rtc_address[4], ((12/10)<<4 | (12%10)));
    ds1302_write(write_rtc_address[5], ((7/10)<<4  | (7%10)));
    ds1302_write(write_rtc_address[6], ((17/10)<<4 | (17%10)));
    ds1302_write(0x8e,0x80); //打开写保护功能
}
 
//4位数码管动态显示扫描子程序
void display_smg_4()
{
    uchar dat,number;
    P1=0x02;//秒十位
    dat=ds1302_read(0x81);//dat值位BCD码
    number=(((dat&0xf0)>>4)*10+(dat&0x0f))/10;//BCD码转换成十进制，并求模
    P0=smg_table[number];
    delayms(6);//稍作延时，以提高亮度
    P0=0x00;//数码管断码清零
 
    P1=0x01;//秒个位
    dat=ds1302_read(0x81);
    number=(((dat&0xf0)>>4)*10+(dat&0x0f))%10;//BCD码转换成十进制，并求余
    P0=smg_table[number];
    delayms(6);
    P0=0x00;
 
    P1=0x08;//分十位
    dat=ds1302_read(0x83);
    number=(((dat&0xf0)>>4)*10+(dat&0x0f))/10;
    P0=smg_table[number];
    delayms(6);//稍作延时，以提高亮度
    P0=0x00;//数码管断码清零
 
    P1=0x04;//分个位
    dat=ds1302_read(0x83);
    number=(((dat&0xf0)>>4)*10+(dat&0x0f))%10;
    P0=smg_table[number];
    delayms(6);
    P0=0x00;
}
 
void delay_ms(uint z)//1毫秒延时
{
    uint x,y;
    for(x=z;x>0;x--)
        for(y=110;y>0;y--);
}
 
void delay_us()//1微秒延时
{
    _nop_();
    _nop_();
}
