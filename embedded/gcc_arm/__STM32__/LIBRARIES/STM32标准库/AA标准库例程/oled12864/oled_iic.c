/*******************************************************************************
        => I2C__底层时序__
*******************************************************************************/
#define IN              0
#define OUT             1
#define SDA             GPIO_Pin_0
#define SCL             GPIO_Pin_1
#define I2C_PORT        GPIOF
#define SDA_LOW()       GPIO_ResetBits(I2C_PORT, SDA)
#define SDA_HIHG()      GPIO_SetBits(I2C_PORT, SDA)
#define SCL_LOW()       GPIO_ResetBits(I2C_PORT, SDA)
#define SCL_HIHG()      GPIO_SetBits(I2C_PORT, SDA)
#define READ_SDA()      GPIO_ReadInputDataBit(I2C_PORT, SDA)
//OLED_0.91
#define OLED_ADDR       0x78
void i2c_pin_conf(void)
{
        GPIO_InitTypeDef GPIO_Structure;
        RCC_APB2PeriphClockCmd(I2C_PORT, ENABLE);
        GPIO_Structure.GPIO_Pin   = SDA | SCL;
        GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Structure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_Init(I2C_PORT, &GPIO_Structure);
}
//输入输出数据配置__IO__
void i2c_sda_mode(uint8_t opt)
{
        GPIO_InitTypeDef GPIO_Structure;
        if (opt) {
                GPIO_Structure.GPIO_Pin   = SDA;                //Output
                GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
                GPIO_Structure.GPIO_Mode  = GPIO_Mode_Out_PP;
                GPIO_Init(I2C_PORT, &GPIO_Structure);
        } else {
                GPIO_Structure.GPIO_Pin   = SDA;                //Input
                GPIO_Structure.GPIO_Mode  = GPIO_Mode_IPU;
                GPIO_Init(I2C_PORT, &GPIO_Structure);
        }
}
void i2c_start_signal(void)
{
        i2c_sda_mode(OUT);      //配置为输出模式__Output
        SCL_HIGH();
        SDA_HIGH();
        delay_us(5);
        SDA_LOW();
        delay_us(5);
        SCL_LOW();
}
void i2c_stop_signal(void)
{
        i2c_sda_mode(OUT);      //配置为输出模式__Output
        SCL_LOW();
        SDA_LOW();
        delay_us(5);
        SCL_HIGH();
        delay_us(5);
        SDA_HIGH();
}
uint8_t ic2_write_ack(void)
{
        uint8_t timeout;
        i2c_sda_mode(IN);      //配置为输入模式__Input
        SCL_HIGH();
        delay_us(4);
        while (READ_SDA()) {
                if (++timeout > 250) {
                        i2c_stop_signal();
                        return (1);
                }
        }
        SCL_LOW();
        delay_us(4);
        return (0);
}
void i2c_write_byte(uint8_t dat)
{
        SCL_LOW();
        delay_us(4);
        for (i = 0; i < 8; i++) {
                i2c_sda_mode(OUT);      //配置为输出模式__Output
                if ((dat << i) & 0x80) {
                        SDA_HIGH();
                } else {
                        SDA_LOW();
                }
                SCL_HIGH();
                delay_us(4);
                SCL_LOW();
                delay_us(4);
        }
}
uint8_t i2c_read_byte(void)
{
        uint8_t dat;
        for (i = 0; i < 8; i++) {
                i2c_sda_mode(IN);      //配置为输入模式__Input
                SCL_HIGH();
                delay_us(4);
                dat <<= 1;
                if (READ_SDA()) == 1) {
                        dat |= 0x01;
                }
                SCL_LOW();
                delay_us(4);
        }
        return (dat);
}


/*******************************************************************************
//DC是数据和命令的选择位（0_COMMAND, 1_DATA）
|_________________________________________________________|
|        OLED_0.91(128 * 32)                              |
|        OLED_ADDRESS:  0x78                              |
|_________________________________________________________|
|        OLED_CMD:      0x00                              |
|        OLED_DAT:      0x40                              |
|_________________________________________________________|
*******************************************************************************/
void oled_write_cmd(uint8_t cmd)
{
        i2c_start_signal();                     //发送起始信号
        i2c_start_write_byte(OLED_ADDR);        //发送器件地址
        i2c_write_ack();                        //应答号
        i2c_start_write_byte(0x00);             //WRITE_CMD_COMMAND
        i2c_write_ack();                        //应答号
        i2c_start_write_byte(cmd);              //写指令
        i2c_write_ack();                        //应答号
        i2c_stop_signal();                      //停止信号
}
void oled_write_dat(uint8_t dat)
{
        i2c_start_signal();                     //发送起始信号
        i2c_start_write_byte(OLED_ADDR);        //发送器件地址
        i2c_write_ack();                        //应答号
        i2c_start_write_byte(0x40);             //WRITE_DATA_COMMAND
        i2c_write_ack();                        //应答号
        i2c_start_write_byte(dat);              //写数据
        i2c_write_ack();                        //应答号
        i2c_stop_signal();                      //停止信号
}
void oled_init(void)
{
        delay_ms(200);
        oled_write_cmd(0xA8);   //设置分辨率
        oled_write_cmd(0x1F);   //(0x3F: 128*64) (0x1F: 128*32)
        oled_write_cmd(0xDA);   //设置COM硬件引脚配置，适应分辨率
        oled_write_cmd(0x02);   //(0x12: 128*64) (0x02: 128*32)
        oled_write_cmd(0xD3);   //设置显示偏移
        oled_write_cmd(0x00);   //默认设置（0x00）没有偏移
        oled_write_cmd(0x40);   //设置显示开始（0~63）
        oled_write_cmd(0xA1);   //段SEGMENT重映射对于IIC通讯四引脚OLED要设置（0xA1）
        oled_write_cmd(0x81);   //设置对比度指令
        oled_write_cmd(0xFF);   //亮度调节（0x00~0xFF）数值越大，亮度越大
        oled_write_cmd(0xA4);   //输出遵循RAM内容，（0x05）输出忽略RAM内容
        oled_write_cmd(0xA6);   //设置显示方式（0xA6正常显示， 0xA7反向显示）
        oled_write_cmd(0xD5);   //设置显示时钟分频
        oled_write_cmd(0xF0);   //设置分辨率值
        oled_write_cmd(0x8D);   //充电泵设置
        oled_write_cmd(0x14);   //0x14:允许在显示开启时使用， 0x10:不允许在开启前使用
        oled_write_cmd(0xAE);   //0xAE:显示关闭， 0xAF:显示开启
        oled_write_cmd(0x20);   //设置内存地址寻址模式
        oled_write_cmd(0x02);   //0x00:水平， 0x01:垂直， 0x02页寻址
        oled_write_cmd(0xB0);   //为页寻址模式设置页面开启地址（0~7）
        oled_write_cmd(0xC8);   //设置COM扫描方式
        oled_write_cmd(0x00);   //设置低列地址
        oled_write_cmd(0x10);   //设置高列地址
        oled_write_cmd(0x40);   //设置显示开始行（0~63）
        oled_write_cmd(0xD9);   //设置预充电时期
        oled_write_cmd(0x22);   //设置充电时间
        oled_write_cmd(0xDB);   //设置取消选择级别
        oled_write_cmd(0x20);   //默认
        oled_write_cmd(0xAF);   //设置显示开启
        oled_clear();           //清屏
}
void oled_clear(void)
{
        uint8_t i;
        for (i = 0; i < 4; i++) {
                oled_write_cmd(0xB0 | i);
                oled_write_cmd(0x00);
                oled_write_cmd(0x10);
                for (n = 0; n < 128; n++) {
                        oled_write_dat(0x00);
                }
        }
}
