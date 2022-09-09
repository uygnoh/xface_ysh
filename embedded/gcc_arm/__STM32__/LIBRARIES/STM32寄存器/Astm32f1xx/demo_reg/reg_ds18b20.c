// DS18B20__数据方向设置__(PIN_11)
// _____________________________________________________________________________
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
//DS18B20__输出高低电平__(PIN_11)
#define DS18B20_DQ_HIGH()       do {                                    \
                                        GPIOG->BSRR &= 0xFFFFF7FF;      \
                                        GPIOG->BSRR |= 0x00000800;      \
                                } while (0)
#define DS18B20_DQ_LOW()       do {                                     \
                                        GPIOG->BSRR &= 0xF7FFFFFF;      \
                                        GPIOG->BSRR |= 0x08000000;      \
                                } while (0)
//读取DQ线上的数据
#define DS18B20_DQ             (PG_IN(11))

uint8_t ds18b20_init(void);             // 初始化
void ds18b20_write_byte(uint8_t cmd);   // 写一个字节命令
uint8_t ds18b20_read_byte(void);        // 读一个字节数据
float ds18b20_read_temperature(void);   // 读取温度值
/*
int main(void)
{
        GPIOG_CLOCK_ENABLE();   //打开GPIOG时钟
        while (1) {
                printf("DS18B20: %.3f\n", ds18b20_read_temperature());
                delay_ms(100);
        }
}
*/












/*******************************************************************************
  函数名称: void ds18b20_init(void)
  输入参数: 无
  输出参数: 返回值为(0)说明与DS18B20已经建立连接
  输出参数: 返回值为(1)说明DS18B20无效或损坏
  函数功能: 初始化__DS18B20__
*******************************************************************************/
uint8_t ds18b20_init(void)
{
        uint8_t dat;
        DS18B20_IO_OUT();                       //DS18B20（输出操作）__Output
        DS18B20_DQ_LOW();                       //先把DS18B20_DQ线拉低
        delay_us(480);                          //延时（480us）
        DS18B20_DQ_HIGH();                      //释放总线
        delay_us(60);                           //延时（60us）
        DS18B20_IO_IN();                        //DS18B20（输入操作）__Input
        dat = DS18B20_DQ;                       //读取DQ线上的数据
        delay_us(420);                          //延时（420us)
        return (dat);
}
void ds18b20_write_byte(uint8_t cmd)
{
        uint8_t i;
        for (i = 0; i < 8; i++) {
                DS18B20_IO_OUT();               //DS18B20（输出操作）__Output
                DS18B20_DQ_LOW();               //先把DS18B20_DQ线拉低
                delay_us(2);                    //延时（2us)
                if (cmd & 0x01) {               //数据从最低位开始写入     
                        DS18B20_DQ_HIGH();      //写入（1）
                } else {                        //写入（0）
                        DS18B20_DQ_LOW();
                }
                delay_us(60);                   //延时（60us)
                DS18B20_DQ_HIGH();              //释放总线
                cmd >>= 1;                      //右移一位
        }
}
uint8_t ds18b20_read_byte(void)
{
        uint8_t i;
        uint8_t dat = 0;
        for (i = 0; i < 8; i++) {
                dat >>= 1;
                DS18B20_IO_OUT();               //DS18B20（输出操作）__Output
                DS18B20_DQ_LOW();               //拉低总线
                delay_us(2);                    //延时（2us）
                DS18B20_DQ_HIGH();              //释放总线
                DS18B20_IO_IN();                //DS18B20（输入操作）__Input
                if (DS18B20_DQ == SET) {
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
