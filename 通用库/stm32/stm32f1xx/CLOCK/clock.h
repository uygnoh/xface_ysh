#ifndef __CLOCK_H__
#define __CLOCK_H__
#include "common.h"

// xtal 表示外部晶振（或外接晶振）（External Crystal Oscillator)。
// 而外部晶振常常连接至单片机的引脚，常常使用XTAL加上数字表示连接外部晶振。
// irc  表示内部RC振荡器，不容易损坏，但是精度不高

void clock_setup_irc_8mhz(void);
void clock_setup_xtal_8mhz_to_72mhz(void);
void peripheral_clock_setup(void);

#endif
