#include "lcd1602.h"


void lcd1602_write_command(uint8_t cmd)
{   
        RS_1602   = 0;
        RW_1602   = 0;
        EN_1602   = 0;
        PORT_1602 = cmd;
        delay_ms(2);
        EN_1602   = 1;
        delay_ms(2);
        EN_1602   = 0;
        delay_ms(2);
}


void lcd1602_write_data(uint8_t dat)
{   
        RS_1602   = 1;
        RW_1602   = 0;
        EN_1602   = 0;
        PORT_1602 = cmd;
        delay_ms(2);
        EN_1602   = 1;
        delay_ms(2);
        EN_1602   = 0;
        delay_ms(2);
}

/*******************************************************************************
  函数名称: lcd1602_busy_check()
  输入参数: 无
  输出参数: 返回忙状态（0不忙， 1忙）
  函数功能: lcd1602判断忙
*******************************************************************************/
uint8_t lcd1602_busy_check(void)
{
        uint8_t tmp = 0;
        uint8_t busy = 0;
        PORT_1602 = 0xFF;               // 设置PORT_1602全部为高电平
        RS_1602   = 0;                  // RS为“0”, 表示“命令”
        RW_1602   = 1;                  // RW为“1”, 表示“读” 
        delay_us(1);	                // 稍作延时
        do {
                EN_1602 = 1;            // 拉高“EN”
                delay_us(1);            // 稍作延时，等待lcd1602上的数据稳定
                busy = PORT_1602;       // 读取lcd1602上的数据
                delay_us(1);            // 稍作延时
                EN_1602 = 0;            // 拉低 EN
                delay_us(1);            // 稍作延时
                tmp++;
                if (tmp > 128) {
                        return(1);
                }  
        // 判断PORT_1602端口上的数据最高位，为“1”表示忙
        } while (busy & 0x80);
        return(0);
}

/*******************************************************************************
  函数名称: lcd1602_init()
  输入参数: 无
  输出参数: 无
  函数功能: lcd1602显示初始化
*******************************************************************************/
void lcd1602_init(void)
{
        lcd1602_write_command(0x38);    // 显示模式设置
        delay_ms(5);
        lcd1602_write_command(0x0f);    // 光标显示
        delay_ms(5);
        lcd1602_write_command(0x0c);    // 显示开及光标设置
        delay_ms(5);
        lcd1602_write_command(0x06);    // 显示光标移动设置
        delay_ms(5);
        lcd1602_write_command(0x01);    // 显示清屏
        delay_ms(5);
}


// lcd1602显示一个字符
// 在指定坐标设置字符 (行 x=0~1, 列 y=0~15)
//______________________________________________________________________________
void lcd1602_show_char(uint8_t pos_x, uint8_t pos_y, uint8_t t_char)
{
        uint8_t addr = 0x80;            // lcd1602基地址
        pos_x &= 0x01;                  // 行地址，共有2行; 取行地址
        pos_y &= 0x0f;                  // 列地址，共有16列; 取列地址
        addr  |= pos_y;                 // 获得lcd1602列地址值
        if (pos_x) {                    // 判断lcd1602是第几行(0或1)                    
                addr |= 0x40;           // 如果是第2行的话，加“0x40”
        }
        lcd1602_write_command(addr);    // lcd1602写入位置信息
        lcd1602_write_data(t_char);     // lcd1602写入数据信息
}

//lcd1602显示一串字符
//从指定位置开始设置字符串 (p_x=0~1，p_y=0~15，*pstr必须是以'\0'结尾的字符串)
//______________________________________________________________________________
void lcd1602_show_string(uint8_t pos_x, uint8_t pos_y, const uint8_t *pstr)
{
        uint8_t x = 0;
        uint8_t y = 0;
        pos_x &= 0x01;
        pos_y &= 0x0f;

        // 最外层循环， 行(0, 1)
        for (x = pos_x; x < 2; x++) {
                // 内层循环， 列(0 ~ 15)
                for (y = pos_y; (y < 16) && ((*pstr) != 0); y++) {
                        // 调用写一个字符串函数
                        lcd1602_show_char(x, y, *pstr++);
                }
        }
}

/*  
 *  整形数据转换为字符串
 *  (long dat):      要处理的数据
 *  (uint8_t *str):  处理数据存放的地方
 *  返回字符串的长度
 */
//______________________________________________________________________________
uint8_t int_convert_string(long dat, uint8_t *str)
{
        uint8_t i   = 0;        // 字符串索引
        uint8_t len = 0;        // 字符串长度
        uint8_t buf[6];         // 字符串临时缓冲区和要处理的字符串长度一致
        
        // 如果是负数，取绝对值
        //__________________
        if (dat < 0) {
                dat = -dat;	
                *str++ = '-';
                len++;
        }
        // 反着取字符串
        //__________________
        do {	
                buf[i++] = dat%10 + '0';  
                dat /= 10;
        } while (dat > 0);
        len += i;
        // 在把字符串反过来
        //__________________
        while (i-- > 0)       
                *str++ = buf[i];

        *str = '\0';    // 字符串结束加入一个“\0”                   
        return len;     // 返回字符串长度
}

// 80C51@12Mz  毫秒级延时子程序
//______________________________________________________________________________
void delay_ms(uint16_t z)
{
        uint16_t x,y;
        for(x = z; x > 0; x--)
                for(y = 110; y > 0; y--);
}
