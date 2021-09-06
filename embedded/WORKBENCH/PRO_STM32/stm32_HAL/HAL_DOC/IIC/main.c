#include <stdio.h>

#define DATA_Size       256
#define EEP_Firstpage   0x00
uint8_t I2c_Buf_Write[DATA_Size];
uint8_t I2c_Buf_Read[DATA_Size];

uint8_t I2C_Test(void)
{
    uint16_t i;
    
    EEPROM_INFO("写入的数据");
    
    for (i = 0; i < DATA_Size; i++)
    {
        I2c_Buf_Write[i] = i;
        printf("0x%02X ", I2c_Buf_Write[i]);
        if (i%16 == 15)
            printf("\n\r");
    }
    
    //将I2c_Buf_Writek 顺序递增的数据写入EEPROM中
    I2C_EE_BufferWrite(I2c_Buf_Write, EEP_Firstpage, DATA_Size);
    
    EEPROM_INFO("读出的数据");
    
    //将EEPROM读出数据顺序保存到I2c_Buf_Read中
    I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, DATA_Size);
    
    // 将I2c_Buf_Read中的数据通过串口打印
    for (i = 0; i < DATA_Size; i++)
    {
        if (I2c_Buf_Read[i] != I2c_Buf_Write[i])
        {
            printf("0x%02X ", I2c_Buf_Read[i];
            EEPROM_ERROR("错误：I2C EEPROM写入与读出的数据不一致");
            return 0;
        }
        printf("0x%02X ", I2c_Buf_Read[i];
        if (i % 16 == 15)
            printf("\n\r");
    }
}

int main(void)
{
    HAL_Init();
    LED_GPIO_Init();
    DEBUG_UART_Init();
    // IIC外设AT24C02初始化
    I2C_EE_Init();
    
    if (I2c_Test() = 1)
        LED_GREEN;
    else
        LED_RED;
    while (1)
    {
    }
}
