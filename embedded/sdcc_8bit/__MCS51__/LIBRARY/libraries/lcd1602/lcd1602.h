#ifndef __LCD1602_H__
#define __LCD1602_H__
#include<reg52.h>

/******************************************************************************/
/*      LCD1602_硬件连接                                                       */
/******************************************************************************/
/*
           .______RP______.
           |              |
        .__|__.       .___|___.
        | VL  |------>| 10K   |------>0V
        |_____|       |_______|
        ._____.
        | BLK |---------------------->0V
        |_____|
        ._____.       ._______.
        | BLA |------>| 0.01K |------>5V
        |_____|       |_______|
*/
#define PDC	P0      //PDAT(Parallel_Data_Communication)
#define PRS     P2^5    //lcd1602
#define PRW     P2^6    //lcd1602
#define PEN     P2^7    //lcd1602使能信号
/******************************************************************************/
/*      LCD1602_函数声明                                                       */
/******************************************************************************/
void lcd1602_write_cmd(uint8_t cmd);
void lcd1602_write_dat(uint8_t dat);
uint8_t lcd1602_busy_check(void);
void lcd1602_init(void);
void lcd1602_show_char(uint8_t pos_x, uint8_t pos_y, uint8_t t_char);
void lcd1602_show_string(uint8_t pos_x, uint8_t pos_y, const uint8_t *pstr);
uint8_t int_convert_string(long dat, uint8_t *str);
void delay_ms(uint16_t z);// 80C51单片机延时函数(stc80c51@12MHz)
#endif
