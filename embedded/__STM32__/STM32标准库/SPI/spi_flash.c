uint16 SPI_TIMEOUT;

void gpio_setup(void)
{
        GPIO_InitTypeDef Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        
        //MOSI(复用功能推挽输出)
        Y.GPIO_Pin   = SPI_MOSI_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_Init(SPI_MOSI_PORT, &Y);
        //MISO(浮空输入)
        Y.GPIO_Pin   = SPI_MISO_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPI_MISO_PORT, &Y);
        //SCLK(复用功能推挽输出)
        Y.GPIO_Pin   = SPI_SCLK_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_Init(SPI_SCLK_PORT, &Y);
        
        //初始化NSS引脚，使用软件控制，所以直接设置成推挽输出
        Y.GPIO_Pin   = SPI_NSS_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_Init(SPI_NSS_PORT, &Y);
        //设置NSS引脚空闲状态为高电平
        SPI_NSS_HIGH();
}

void spi_setup(void)
{
        SPI_InitTypeDef Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);    //SPI时钟打开
        Y.SPI_BaudRatePrescaler = SPI_RaudRatePrescaler_2;      //分频因子(2)
        Y.SPI_CPHA              = SPI_CPHA_2Edge;               //模式3
        Y.SPI_CPOL              = SPI_CPOL_HIGH;                //模式3
        Y.SPI_CRCPolynomial     = 0;                            //不使用CRC功能
        Y.SPI_DataSize          = SPI_DataSize_8b;              //8位数据位
        Y.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;//双线全双工
        Y.SPI_FirstBit          = SPI_First_MSB;                //高位在前
        Y.SPI_Mode              = SPI_Mode_Master;              //配置为主模式
        Y.SPI_NSS               = SPI_NSS_Soft;                 //配置为软件控制
        SPI_Init(SPI1, &Y);                                     //写入配置到寄存器
        SIP_Cmd(SPI1, ENABLE);                                  //使能SPI1
}

void spi_flash_init(void)
{
        gpio_setup();
        spi_setup();
}

uint8_t SPI_RW(uint8_t dat)
{
        SPI_TIMEOUT = 1000;
        //检测并等待TX缓冲区为空
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
                if (SPI_TIMEOUT-- == 0) {
                        return spi_timeout_usr_call_back(0);
                }
        }
        SPI_I2S_SendData(SPI1, dat);
        //检测并等待RX缓冲区为非空
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        //程序执行到此处，说明数据发送完毕，并接收到一个字节的数据
        return SPI_I2S_ReceiveData(SPI1);
}
