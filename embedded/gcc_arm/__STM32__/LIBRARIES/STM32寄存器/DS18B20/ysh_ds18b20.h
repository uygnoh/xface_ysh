#ifndef __REG_DS18B20_H__
#define __REG_DS18B20_H__
#include "common.h"



// DS18B20__数据方向设置__(PIN_11)
#define DS18B20_IO_IN()         do {                                    \
                                        GPIOG->CRH &= 0xFFFF0FFF;       \
                                        GPIOG->CRH |= 0x00008000;       \
                                        GPIOG->ODR &= 0xFFFFF7FF;       \
                                        GPIOG->ODR |= 0x00000800;       \
                                } while (0)
#define DS18B20_IO_OUT()        do {                                    \
                                        GPIOG->CRH &= 0xFFFF0FFF;       \
                                        GPIOG->CRH |= 0x00003000;       \
                                } while (0)
// DS18B20__输出高低电平__(PIN_11)
#define DS18B20_DQ_HIGH()       do {                                    \
                                        GPIOG->BSRR &= 0xFFFFF7FF;      \
                                        GPIOG->BSRR |= 0x00000800;      \
                                } while (0)
#define DS18B20_DQ_LOW()       do {                                     \
                                        GPIOG->BSRR &= 0xF7FFFFFF;      \
                                        GPIOG->BSRR |= 0x08000000;      \
                                } while (0)
// 读取DQ线上的数据
#define DS18B20_DQ             (PG_IN(11))


uint8_t         ds18b20_init(void);                     // 初始化
void            ds18b20_write_byte(uint8_t cmd);        // 写一个字节命令
uint8_t         ds18b20_read_byte(void);                // 读一个字节数据
float           ds18b20_read_temperature(void);         // 读取温度值
/*
int main(void)
{
        RCC->APB2ENR |= BIT_08;   //打开GPIOG时钟
        while (1) {
                printf("DS18B20: %.3f\n", ds18b20_read_temperature());
                delay_ms(100);
        }
}
*/
#endif
