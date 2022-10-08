//______________________________________________________________________________
//      => STM32 I2C 配置
//______________________________________________________________________________
//      EV5     SB=1            // 读SR1然后将地址写入DR寄存器将清除该事件
//      EV6     ADDR=1          // 读SR1然后读SR2将清除该事件
//      EV8_1   TxE=1           // 移位寄存器空,数据寄存器空,写DR寄存器
//      EV8     TxE=1           // 移位寄存器非空,数据寄存器空,写入DR寄存器将清除该事件
//      EV8_2   TxE=1,BTF=1     // 请求设置停止位。TxE和BTF位由硬件在产生停止条件时清除
//      EV9     ADDR10=1        // 读SR1然后写入DR寄存器将清除该事件
        
        
        
#include "main.h"
#include "ssd1306.h"
#include "characters.h"
#include "m32.h"


void SystemClock_Config(void);

void timeout_user_callback(void)
{

        while (1) {
        }
}

void i2c_setup(void)
{
        RCC->APB2RSTR   |=  BIT_00;     // AFIO
        RCC->APB2RSTR   &= ~BIT_00;
        RCC->APB2RSTR   |=  BIT_02;     // GPIOA
        RCC->APB2RSTR   &= ~BIT_02;
        RCC->APB2RSTR   |=  BIT_03;     // GPIOB
        RCC->APB2RSTR   &= ~BIT_03;
        RCC->APB2ENR    |=  BIT_00;     // 打开 AFIO 时钟
        RCC->APB2ENR    |=  BIT_02;     // 打开 GPIOA时钟
        RCC->APB2ENR    |=  BIT_03;     // 打开 GPIOB时钟
        GPIOB->CRL      &=  0x00FFFFFF; // 清除相关位
                                        // 复用开漏输出@50MHz
                                        // PB6  --> I2C1_SCL
        GPIOB->CRL      |=  0xFF000000; // PB7  --> I2C1_SDA



        RCC->APB1RSTR   |=  BIT_21;     // I2C外设复位
        RCC->APB1RSTR   &= ~BIT_21;     // I2C外设停止复位
        RCC->APB1ENR    |=  BIT_21;     // 打开 I2C 时钟

        I2C1->CR1       |=  BIT_15;     // I2C模块软件复位
        I2C1->CR1       &= ~BIT_15;     // I2C模块软件停止复位
        I2C1->CR1       &= ~BIT_01;     // I2C模式
        I2C1->CR1       |=  BIT_10;     // 接受到一个字节后返回一个应答
        I2C1->CR2       |=  0x24;       // I2C模块输入时钟频率 = 36MHz
        I2C1->OAR1       =  0x4000;     // 自身地址寄存器 1
                                        // 普通模式 100KHz
        I2C1->CCR        =  0xB4;       // 快速/标准模式下的时钟控制分频系数
        I2C1->TRISE      =  0x25;       // 快速/标准模式下的最大上升时间
        I2C1->CR1       |=  BIT_00;     // I2C模块使能
}

void ssd1306_write_command(uint8_t command)
{
        uint32_t timeout, tmpreg;

        // 等待I2C总线不忙
        // ____________________________________________________
        timeout = LONG_TIMEOUT;
        while (I2C1->SR2 &= BIT_01) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }


        // 产生起始信号
        // ____________________________________________________
        I2C1->CR1 |= BIT_08;
        timeout = LONG_TIMEOUT;
        while (!(I2C1->SR1 &= BIT_00)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }
        // SR1.AF 清零
        I2C1->SR1 &= ~BIT_10;


        // 发送从机设备地址( 0x78 )
        // ____________________________________________________
        I2C1->DR = 0x78;
        timeout = LONG_TIMEOUT;
        // 等待SR1.ADDR=1，从设备应答
        while (!(I2C1->SR1 &= BIT_01)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }
        // SR1.ADDR 清零
        tmpreg = I2C1->SR1;
        tmpreg = I2C1->SR2;


        // “主机”发送控制字，写命令(0x00)
        // ____________________________________________________
        I2C1->DR = 0x00;
        timeout = LONG_TIMEOUT;
        // 等待SR1.BIF=1，
        while (!(I2C1->SR1 & BIT_02)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }


        // “主机”发送控命令(command)
        // ____________________________________________________
        I2C1->DR = command;
        timeout = LONG_TIMEOUT;
        while (!(I2C1->SR1 &= BIT_02)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }


        // 产生I2C停止信号
        // ____________________________________________________
        I2C1->CR1 |= BIT_09;
}

void ssd1306_write_data(uint8_t data)
{
        uint32_t timeout, tmpreg;

        // 等待I2C总线不忙
        // ____________________________________________________
        timeout = LONG_TIMEOUT;
        while (I2C1->SR2 &= BIT_01) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }


        // 产生起始信号
        // ____________________________________________________
        I2C1->CR1 |= BIT_08;
        timeout = LONG_TIMEOUT;
        while (!(I2C1->SR1 &= BIT_00)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }
        // SR1.AF 清零
        I2C1->SR1 &= ~BIT_10;


        // 发送从机设备地址
        // ____________________________________________________
        I2C1->DR = 0x78;
        timeout = LONG_TIMEOUT;
        // 等待SR1.ADDR=1，从设备应答
        while (!(I2C1->SR1 &= BIT_01)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }
        // SR1.ADDR 清零
        tmpreg = I2C1->SR1;
        tmpreg = I2C1->SR2;


        // “主机”发送控制字，写数据(0x40)
        // ____________________________________________________
        I2C1->DR = 0x40;
        timeout = LONG_TIMEOUT;
        // 等待SR1.BIF=1，
        while (!(I2C1->SR1 & BIT_02)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }


        // “主机”发送数据
        // ____________________________________________________
        I2C1->DR = data;
        timeout = LONG_TIMEOUT;
        while (!(I2C1->SR1 &= BIT_02)) {
                if ((timeout--) == 0) {
                        return timeout_user_callback();
                }
        }


        // 产生I2C停止信号
        // ____________________________________________________
        I2C1->CR1 |= BIT_09;
}


void ssd1306_setup(void)
{
        HAL_Delay(100);

        ssd1306_write_command(0xAE); // 关闭显示
        ssd1306_write_command(0x00); // set low column address
        ssd1306_write_command(0x10); // set high column address
        ssd1306_write_command(0x40); // set display start line
        // ssd1306_write_command(0x81); // 设置对比度命令
        // ssd1306_write_command(0x00);
        ssd1306_write_command(0xA1); // 设置细分重映射 (0xA1正常,0xA0左右反置)
        ssd1306_write_command(0xC8); // 设置列输出扫描方向 (0xC8正常,0xC0上下反置)
        ssd1306_write_command(0xA6); // 设置正常/反向 (0xA6正常显示, 0xA7反向显示)
        ssd1306_write_command(0xA8); // 设置多路复用比率
        ssd1306_write_command(0x3F);
        ssd1306_write_command(0xD3); // 设置显示偏移(垂直偏移)
        ssd1306_write_command(0x00);
        ssd1306_write_command(0xD5); // 设置显示时钟分频
        ssd1306_write_command(0x80);
        ssd1306_write_command(0xD9); // 设置预充电期
        ssd1306_write_command(0xF1); // 将预充电设置为15个时钟并将其放电设置为1个时钟
        ssd1306_write_command(0xDA); // 设置COM引脚硬件配置
        ssd1306_write_command(0x12); // 启用备用COM引脚配置
        ssd1306_write_command(0xDB); // 设置Vcomh取消选择级别
        ssd1306_write_command(0x00); // ~ 0.65 x VCC
        ssd1306_write_command(0x20); // 设置内存寻址模式
        ssd1306_write_command(0x02); // 页面寻址模式
        ssd1306_write_command(0x8d); // 充电凹凸设置
        ssd1306_write_command(0x14); // 在显示期间启用电荷泵
        ssd1306_write_command(0xA4); // entire display on
        ssd1306_write_command(0xA6); // set Normal display
        ssd1306_write_command(0xaf); // 开启显示
}
void ssd1306_clear(void)
{
        ssd1306_write_command(0x20); // 设置寻址模式
        ssd1306_write_command(0x00); // 水平模式
        ssd1306_write_command(0xB0); // 设置起始地址
        ssd1306_write_command(0x00); // 设置显示位置-列低地址
        ssd1306_write_command(0x10); // 设置显示位置-列高地址
        for (int x = 0; x < 1024; x++) {
                ssd1306_write_data(0x00);
        }
}
void oled_put_char_8x16(uint8_t x, uint8_t y, char character)
{
        uint8_t i;

        // set page
        ssd1306_write_command(0x22);
        ssd1306_write_command(y * 2);
        ssd1306_write_command(0x01 + y * 2);
        // set column
        ssd1306_write_command(0x21);
        ssd1306_write_command(0x08 * x);
        ssd1306_write_command(0x08 * x + 0x07);

        for (i = 0; i < 16; i++) {
                ssd1306_write_data(CHARACTERS_8X16[character - 32][i]);
        }
}

void oled_put_string_8x16(uint8_t x, uint8_t y, const char *characters)
{
        uint8_t i;
        for(i = 0; *(characters+i) != '\0'; i++) {
                // 自动换行
                if(x + 1 > 16) {
                        y++;
                        x = 0;
                }
                oled_put_char_8x16(x++, y, *(characters + i));
        }
}

