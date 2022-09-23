#include "ysh_ds18b20.h"


// _____________________________________________________________________________
//      => DS18B20 初始化
// _____________________________________________________________________________
uint8_t ds18b20_init(void)
{
        uint8_t dat;
        DS18B20_IO_OUT();                       // DS18B20（输出操作）__Output
        DS18B20_DQ_LOW();                       // 先把DS18B20_DQ线拉低
        delay_us(480);                          // 延时（480us）
        DS18B20_DQ_HIGH();                      // 释放总线
        delay_us(60);                           // 延时（60us）
        DS18B20_IO_IN();                        // DS18B20（输入操作）__Input
        dat = DS18B20_DQ;                       // 读取DQ线上的数据
        delay_us(420);                          // 延时（420us)
        return (dat);
}



// _____________________________________________________________________________
//      => DS18B20 写1个字节数据
// _____________________________________________________________________________
void ds18b20_write_byte(uint8_t cmd)
{
        uint8_t i;
        for (i = 0; i < 8; i++) {
                DS18B20_IO_OUT();               // DS18B20（输出操作）__Output
                DS18B20_DQ_LOW();               // 先把DS18B20_DQ线拉低
                delay_us(2);                    // 延时（2us)
                if (cmd & 0x01) {               // 数据从最低位开始写入     
                        DS18B20_DQ_HIGH();      // 写入（1）
                } else {                        // 写入（0）
                        DS18B20_DQ_LOW();
                }
                delay_us(60);                   // 延时（60us)
                DS18B20_DQ_HIGH();              // 释放总线
                cmd >>= 1;                      // 右移一位
        }
}



// _____________________________________________________________________________
//      => DS18B20 读1个字节数据
// _____________________________________________________________________________
uint8_t ds18b20_read_byte(void)
{
        uint8_t i;
        uint8_t dat = 0;
        for (i = 0; i < 8; i++) {
                dat >>= 1;
                DS18B20_IO_OUT();               // DS18B20（输出操作）__Output
                DS18B20_DQ_LOW();               // 拉低总线
                delay_us(2);                    // 延时（2us）
                DS18B20_DQ_HIGH();              // 释放总线
                DS18B20_IO_IN();                // DS18B20（输入操作）__Input
                if (DS18B20_DQ == SET) {
                        dat |= 0x80;
                }
                delay_us(60);
        }
        return (dat);
}



// _____________________________________________________________________________
//      => DS18B20 读取温度数值
// _____________________________________________________________________________
float ds18b20_read_temperature(void)
{
        uint8_t  MSB = 0;
        uint8_t  LSB = 0;
        uint16_t tmp = 0;
        float    ftmp;
        if (ds18b20_init() == RESET) {
                ds18b20_init();
                ds18b20_write_byte(0xCC);
                ds18b20_write_byte(0x44);
                delay_ms(750);
                ds18b20_init();
                ds18b20_write_byte(0xCC);
                ds18b20_write_byte(0xBE);
                LSB = ds18b20_read_byte();
                MSB = ds18b20_read_byte();
                tmp = MSB;
                tmp = (tmp << 8 | LSB); /////////////////////////
                if (tmp & 0xF800) {     ///1111 1000 0000 0000（如果温度为负）
                        tmp = (~tmp + 0x01) * -0.0625;
                } else {
                        ftmp = (float)tmp * 0.0625;
                        //（*10）广大10位， （加0.5）去四舍五入
                        //tmp  = ftmp * 10 + 0.5;
                }
        } else {
                printf("DS18B20_NOT_EXIST\n");
                delay_ms(500);
        }
        return (ftmp);
}
