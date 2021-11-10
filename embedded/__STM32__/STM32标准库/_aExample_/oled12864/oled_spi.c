4.设置起始列地址低位 （00H~0FH）
  这是一条单字节指令。
  高4位恒定为0H，低4位为要设置的起始列地址的低4位。这条指令仅用于页寻址模式。

5.设置起始列地址高位 （10H~1FH）
  这是一条单字节指令
  高4位恒定为1H，低4位为要设置的起始列地址的高4位。这条指令仅用于页寻址模式。

6.设置页地址 （B0H~B7H）
  这是一条单字节指令
  高4位恒定为BH，第5位规定为0，低3位用于设置页地址，从 B0H~B7H 分别设置起始页为 0~7。这条指令仅用于页寻址模式。



#define CLK             GPIO_Pin_0
#define MOSI            GPIO_Pin_1
#define RES             GPIO_Pin_2
#define DC              GPIO_Pin_3
#define CS              GPIO_Pin_4
#define CMD             0
#define DAT             1
#define OLED_PORT       GPIOF
#define CLK_LOW()       GPIO_ResetBits(OLED_PORT, CLK)  //OLED12864__时钟线
#define CLK_HIGH()      GPIO_SetBits(OLED_PORT, CLK)
#define MOSI_LOW()      GPIO_ResetBits(OLED_PORT, MOSI) //OLED12864__数据线
#define MOSI_HIGH()     GPIO_SetBits(OLED_PORT, MOSI)
#define RES_LOW()       GPIO_ResetBits(OLED_PORT, RES)  //OLED12864__复位线
#define RES_HIGH()      GPIO_SetBits(OLED_PORT, RES)
#define DC_LOW()        GPIO_ResetBits(OLED_PORT, DC)   //OLED12864__命令数据(0_CMD, 1_DATA)
#define DC_HIGH()       GPIO_SetBits(OLED_PORT, DC)
#define CS_LOW()        GPIO_ResetBits(OLED_PORT, CS)   //OLED12864__片选线
#define CS_HIGH()       GPIO_SetBits(OLED_PORT, CS)
void oled_pin_conf(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(OLED_PORT, ENABLE);
        GPIO_InitStructure.GPIO_Pin   = CLK | MOSI | RES | DC | CS;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_Init(OLED_PORT, &GPIO_InitStructure);
}
//OLED12864（模拟SPI通信）
//cmd，（0）写入的是命令，（1）写入的是数据
//dat，要写入的数据
void olde_write_byte(uint8_t cmd, uint8_t dat)
{
        uint8_t i;
        if (cmd == 0) {
                DC_LOW();       //DC == 0, 写入的是指令
        } else {                //DC == 1, 写入的是数据
                DC_HIGH();
        }
        
        CS_LOW();               //片选拉低，开始向OLE写入数据
        for (i = 0; i < 8; i++) {
                if ((dat << i) & 0x80) {
                        MOSI_HIGH();
                } else {
                        MOSI_LOW();
                }
                CLK_LOW();
                CLK_HIGH();
        }
        CS_HIGH();              //片选拉高，禁止向OLE写入数据
}
void oled_init(void)
{
        CLK_HIGH();
        delay_ms(100);
        RES_LOW();
        delay_ms(100);
        RES_HIGH();
        
        const uint8_t oled_cmd[] = {
                0xAE, 0x00, 0x10, 0x40, 0x81, 0xCF, 0xA1, 0xC8, 
                0xA6, 0x48, 0x3F, 0xD3, 0x00, 0xD5, 0x80, 0xD9,
                0xF1, 0xDA, 0x12, 0xDB, 0x40, 0x20, 0x02, 0x8D,
                0x14, 0xA4, 0xA6, 0xAF, 0xAF, 0xAF
        };
        
        uint8_t i;
        for (i = 0; i < sizeof(oled_cmd); i++) {
                oled_write_byte(CMD, oled_cmd[i]);
                delay_us(1);
        }
        oled_clear();
}
void oled_clear(void)
{
        uint8_t i;
        uint8_t n;
        for (i = 0; i < 8; i++) {
                oled_write_byte(CMD, 0xB0 | i); //设置页地址（对应页0~7）
                oled_write_byte(CMD, 0x00);     //设置列地址的低4位_Low
                oled_write_byte(CMD, 0x10);     //设置列地址的高4位_High
                for (n = 0; n < 128; n++) {     //清屏
                        oled_write_byte(DAT, 0x00);
                }
        }
}
//x，y   坐标__
//g，    高度__64
//k，    宽度__128
//dat，  数据__
void oled_display(uint8_t x, uint8_t y, uint8_t g, uint8_t k, uint8_t *dat)
{
        uint8_t i;
        for (i = 0; i < g; i++) {
                oled_write_byte(CMD, (0xB0 | i) + x);           //(0~7)64 行
                oled_write_byte(CMD, 0x10 + (y >> 4) & 0x0F);   //设置高4位地址
                oled_write_byte(CMD, y & 0x0f);                 //设置低4位地址
                for (j = 0; j < k; j++) {
                        oled_write_byte(DAT, *dat++);
                }
        }
}

