I2C_HandleTypeDef I2C_Handle;

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef PORT;
    
    // I2C引脚时钟打开 
    I2Cx_SCL_GPIO_CLK_ENABLE();
    I2Cx_SDA_GPIO_CLK_ENABLE();
    // I2C器件时钟打开
    I2Cx_CLK_ENABLE();
    
    
    PORT.Pin    = I2Cx_SCL_PIN;
    PORT.Mode   = GPIO_MODE_AF_OD;
    PORT.Pull   = GPIO_NOPULL;
    PORT.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &PORT);
    
    PORT.Pin    = I2Cx_SDA_PIN;
    HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &PORT);
    
    // Force the I2C peripheral clock reset
    I2Cx_FORCE_RESET();
    // Release the I2C peripheral clock reset
    I2Cx_RELEASE_RESET();
}


static void I2C_Mode_Config(void)
{
    I2C_Handle.Instance             = I2Cx;
    
    I2C_Handle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;  //7位地址模式
    I2C_Handle.Init.ClockSpeed      = 400000;                   //时钟速度
    I2C_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;  //I2C双地址模式
    I2C_Handle.Init.DutyCycle       = I2C_DUTYCYCLE_2;          //I2C时钟占空比
    I2C_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;  //广播模式
    I2C_Handle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;    //时钟延长模式
    I2C_Handle.Init.OwnAddress1     = I2C_OWN_ADDRESS7;         //主机地址
    I2C_Handle.Init.OwnAddress2     = 0;
    HAL_I2C_Init(&I2C_Handle);
}



void I2C_EE_Init(void)
{
    I2C_Mode_Config();
}

// 将缓冲区中的数据写到I2C—EEPROM中
// pBuffer缓冲区指针
// WriteAddr写入的地址
// NumByteToWrite写入的字节数
void I2C_EE_BufferWrite(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteWrite)
{
    uint8_t NumOfPage = 0;
    uint8_t NumOfSingle = 0;
    uint8_t Addr = 0;
    uint8_t count = 0;
    
    Addr = WriteAddr % EEPROM_PAGESIZE;
    count = EEPROM_PAGESIZE - Addr;
    NumOfPage = NumByteToWrite / EEPROM_PAGESIZE;
    NumOfSinge = NumByteToWrite % EEPROM_PAGESIZE;
    
    // 如果要写入的页起始地址为(0, 8, 16, 32)
    // if WirteAddr is I2C_pageSize aligned
    if (Addr == 0)
    {
        // 如果要写入的不足一页
        // if NumByteToWrite < I2C_PageSize
        if (NumOfPage == 0)
        {
            I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
        // 如果要写入的页大于一页
        // if NumByteToWrite > I2C_PageSize
        else
        {
            while (NumOfPage--)
            {
                I2C_EE_PageWrite(pBuffer, WriteAddr, EEPROM_PAGESIZE);
                WriteAddr += EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }
            if (NumOfSingle != 0)
            {
                I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
    
    // 如果要写入的页起始地址不是(0, 8, 16, 32)
    // If WriteAddr is not I2C_PageSize aligned
    else
    {
        // If NumByteToWrite < I2C_PageSize
        if (NumOfPage == 0 )
        {
            I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
        // If NumByteToWrite > I2C_PageSize
        else
        {
            NumByteToWrite -= count;
            NumOfPage = NumByteToWrite / EEPROM_PAGESIZE;
            NumOfSingle = NumByteToWrite % EEPROM_PAGESIZE;
        }
        
        if (count != 0)
        {
            I2C_EE_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;
        }
        
        while (NumOfPage--)
        {
            I2C_EE_PageWrite(pBuffer, WriteAddr, EEPROM_PAGESIZE);
            WriteAddr += EEPROM_PAGESIZE;
            pBuffer += EEPROM_PAGESIZE;
        }
        
        if (NumOfSingle != 0)
        {
            I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
        
    }
}


// 从EEPROM里面读取一块数据
// pBuffer存放从EEPROM读取的数据的缓冲区指针
// WriteAddr接收数据的EEPROM的地址
// NumByteToWrite要从EEPROM读取的字节数
uint32_t I2C_EE_BufferRead(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
    HAL_StatusTypeDef status = HAL_OK;
    
    // I2C句柄
    // EEPROM的从设备地址
    // 从EEPROM那里读数据
    // EEPROM内部地址大小
    // 数据存放缓冲区
    // 要读取多少个数据
    // 超时时间
    status = HAL_I2C_Mem_Read(&I2C_Handle, EEPROM_ADDRESS, ReadAddr, 
                              I2C_MEMADD_SIZE_8BIT, (uint8_t *)pBuffer,
                              NumByteToRead, 1000);
                              
    return status;                          
}




