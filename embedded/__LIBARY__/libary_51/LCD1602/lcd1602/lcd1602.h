#ifndef __LCD1602_H__
#define __LCD1602_H__

#include<reg52.h>

// LCD1602液晶显示器8位数据端口宏定义
#define PORT	P0
// LCD1602液晶显示器控制引脚位定义
sbit RS = P2^5;
sbit RW = P2^6;
sbit EN = P2^7;

// LCD1602底层读写函数
void lcd1602_write_cmd(uint8_t cmd);
void lcd1602_write_dat(uint8_t dat);
void lcd1602_busy_check(void);
// LCD1602初始化函数
void lcd1602_init(void);
// LCD1602显示函数
void lcd1602_show_char(uint8_t pos_x, uint8_t pos_y, uint8_t t_char);
void lcd1602_show_string(uint8_t pos_x, uint8_t pos_y, const uint8_t *pstr);
// 整形数据转换为字符串函数
uint8_t int_convert_string(long dat, uint8_t *str);
// 80C51单片机延时函数(stc80c51@12MHz)
void delay_ms(uint16_t z);
#endif
