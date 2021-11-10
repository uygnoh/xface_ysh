#include "ds18b20.h"

//DS18B20配置
void ds18b20_conf(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(DS18B20_PORT_CLK, ENABLE);
        GPIO_InitStructure.GPIO_Pin   = DS18B20_DQ;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
        DS18B20_HIGH();
}

//DS18B20__GPIO引脚输入输出设置
void ds18b20_pin_mode(uint8_t opt)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        
        if (opt) {      //(1)__Output, (0)__Input
                GPIO_InitStructure.GPIO_Pin   = DS18B20_DQ;
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;     //推挽输出
                GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
        } else {
                GPIO_InitStructure.GPIO_Pin   = DS18B20_DQ;
                GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;        //上拉输入
                GPIO_Init(DS18B20_PORT, &GPIO_InitStructure);
        }
}

//返回值为(0)说明与DS18B20已经建立连接
//返回值为(1)说明DS18B20无效或损坏
uint8_t ds18b20_reset(void)
{
        uint8_t dat;
        ds18b20_pin_mode(OUT)   //输出操作
        DS18B20_LOW();          //先把DS18B20拉低
        delay_us(480);          //延时（480us）
        DS18B20_HIGH();         //释放总线
        delay_us(60);           //延时（60us）
        ds18b20_pin_mode(IN)    //输入操作
        dat = GPIO_ReadInputDataBit(DS18B20_PORT, DS18B20_DQ);
        delay_us(420);          //延时（420us)
        return (dat);
}

void ds18b20_write_byte(uint8_t cmd)
{
        uint8_t i;
        for (i = 0; i < 8; i++) {
                ds18b20_pin_mode(OUT);
                DS18B20_LOW();          //先把DS18B20拉低
                delay_us(2);            //延时（2us)
                if (cmd & 0x01) {       //数据从最低位开始写入     
                        DS18B20_HIGH(); //写入（1）
                } else {                //写入（0）
                        DS18B20_LOW();
                }
                delay_us(60);           //延时（60us)
                DS18B20_HIGH();         //释放总线
                cmd >>= 1;              //右移一位
        }
}

uint8_t ds18b20_read_byte(void)
{
        uint8_t i;
        uint8_t dat = 0;
        for (i = 0; i < 8; i++) {
                dat >>= 1;
                ds18b20_pin_mode(OUT);  //引脚配置为输出模式
                DS18B20_LOW();          //拉低总线
                delay_us(2);            //延时（2us）
                DS18B20_HIGH();         //释放总线
                ds18b20_pin_mode(IN);   //引脚配置为输入模式
                if (GPIO_ReadInputDataBit(DS18B20_PORT, DS18B20_DQ) == SET) {
                        dat |= 0x80;
                }
                delay_us(60);
        }
        return (dat);
}

float ds18b20_read_temperature(void)
{
        uint8_t  MSB = 0;
        uint8_t  LSB = 0;
        uint16_t tmp = 0;
        float    ftmp;
        if (ds18b20_write_reset() == RESET) {
                ds18b20_write_reset();
                ds18b20_write_byte(0xCC);
                ds18b20_write_byte(0x44);
                delay_ms(750);
                ds18b20_write_reset();
                ds18b20_write_byte(0xCC);
                ds18b20_write_byte(0xBE);
                LSB = ds18b20_read_byte();
                MSB = ds18b20_read_byte();
                tmp = MSB;
                tmp = (tmp << 8 | LSB); /////////////////////////
                if (tmp & 0xF800) {     ///1111 1000 0000 0000///
                        tmp = (~tmp + 0x01) * -0.0625;
                } else {
                        ftmp = tmp * 0.0625;
                        //（*10）广大10位， （加0.5）去四舍五入
                        //tmp  = ftmp * 10 + 0.5;
                }
        } else {
                printf("DS18B20_NOT_EXIST\n");
                delay_ms(500);
        }
        return (ftmp);
}
int main(void)
{
        ds18b20_conf();
        printf("DS18B20复位状态: %.3f\n", ds18b20_read_temperature());
        delay_ms(500);
}
