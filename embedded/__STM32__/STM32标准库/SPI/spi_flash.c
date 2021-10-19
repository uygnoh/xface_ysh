/*******************************************************************************
  函数名称: gpio_setup()
  输入参数: 无
  输出参数: 无
  函数功能: SPI_GPIO引脚初始化配置
*******************************************************************************/
void gpio_setup(void)
{
        GPIO_InitTypeDef Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        
        //MOSI(复用功能推挽输出)
        Y.GPIO_Pin   = SPI_MOSI_PIN;    //选择GPIO引脚
        Y.GPIO_Speed = GPIO_Speed_50MHz;//设置GPIO引脚速度
        Y.GPIO_Mode  = GPIO_Mode_AF_PP; //设置GPIO引脚功能
        GPIO_Init(SPI_MOSI_PORT, &Y);   //写入配置信息到寄存器中
        
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

/*******************************************************************************
  函数名称: spi_setup()
  输入参数: 无
  输出参数: 无
  函数功能: SPI初始化配置
*******************************************************************************/
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

/*******************************************************************************
  函数名称: spi_read_write()
  输入参数: dat，写入的数据
  输出参数: 返回读取的数据
  函数功能: FLASH__W25Q64__读写一个字节
*******************************************************************************/
uint8_t spi_read_write(uint8_t dat)
{
        uint16_t timeout = 1000;
        //检测并等待发送（TX）缓冲区为空
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
                if (timeout == 0) {
                        timeout--;
                        return (0x00);
                }
        }
        SPI_I2S_SendData(SPI1, dat);
        
        //检测并等待接收（RX）缓冲区为非空
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {
                if (timeout == 0) {
                        timeout--;
                        return (0x00);
                }
        }
        //程序执行到此处，说明数据发送完毕，并接收到一个字节的数据
        return SPI_I2S_ReceiveData(SPI1);
}

/*******************************************************************************
  函数名称: spi_flash_write_enable()
  输入参数: 无
  输出参数: 无
  函数功能: FLASH__W25Q64__芯片写使能
*******************************************************************************/
void spi_flash_write_enable(void)
{
        SPI_NSS_LOW();
        spi_read_write(WRITE_ENABLE);
        SPI_NSS_HIGH();
}

/*******************************************************************************
  函数名称: spi_wait_write_complete()
  输入参数: 无
  输出参数: 无
  函数功能: FLASH__W25Q64__等待FLASH内部时序操作完成
*******************************************************************************/
void spi_wait_write_complete(void)
{
        uint8_t status_reg = 0;
        SPI_NSS_LOW();
        spi_read_write(READ_STATUS);
        do {
                status_reg = spi_read_write(DUMMY);
        } while ((stauts_reg & 0x01) == 1);
        SPI_NSS_HIGH();
}

/*******************************************************************************
  函数名称: spi_read_id()
  输入参数: 无
  输出参数: 无
  函数功能: 读取__W25Q64__ID号码
*******************************************************************************/
void spi_read_id(void)
{
        uint32_t flash_id;
        SPI_NSS_LOW();
        spi_read_write(READ_JEDEC_ID);
        flash_id  = spi_read_write(DUMMY);
        flash_id  = flash_id << 8;
        flash_id |= spi_read_write(DUMMY);
        flash_id  = flash_id << 8;
        flash_id |= spi_read_write(DUMMY);
        SPI_NSS_HIGH();
        return flash_id;
}

/*******************************************************************************
  函数名称: spi_read_id()
  输入参数: addr， 24位FLASH地址
  输出参数: 无
  函数功能: __W25Q64__擦除FLASH指定扇区
*******************************************************************************/
void spi_erase_sector(uint32_t addr)
{
        spi_flash_write_enable();  //擦除扇区之前，先发送“写使能命令”
        spi_wait_write_complete(); //等待写入完成
        SPI_NSS_LOW();
        spi_read_write(ERASE_SECTOR);
        spi_read_write((addr >> 16) & 0xFF);
        spi_read_write((addr >>  8) & 0xFF);
        spi_read_write(addr         & 0xFF);
        SPI_NSS_HIGH();
        spi_wait_write_complete(); //等待擦除扇区结束
}

/*******************************************************************************
  函数名称: spi_read_id()
  输入参数: addr， 24位FLASH地址
  输入参数: buf，  从那个位置开始读取数据
  输入参数: len，  读取数据的长度
  输出参数: 无
  函数功能: 从__W25Q64__中读取多个字节
*******************************************************************************/
void spi_read_data(uint32_t addr, uint8_t *buf, uint32_t len)
{
        SPI_NSS_LOW();
        spi_read_write(READ_DATA);
        spi_read_write((addr >> 16) & 0xFF);
        spi_read_write((addr >>  8) & 0xFF);
        spi_read_write(addr         & 0xFF);
        
        while (len--) {
                *buf++ = spi_read_write(DUMMY);
        }
        SPI_NSS_HIGH();
}

/*******************************************************************************
  函数名称: spi_write_page()
  输入参数: addr， 24位FLASH地址
  输入参数: buf，  从那个位置开始写入数据
  输入参数: len，  写入数据的长度
  输出参数: 无
  函数功能: 从__W25Q64__中写入多个字节
          页编程，一次最多写入（256字节）数据
*******************************************************************************/
void spi_write_page(uint32_t addr, uint8_t *buf, uint16_t page)
{
        if (page > PAGE_SIZE) {
                return;
        }
        spi_flash_write_enable();  //写入数据之前，先发送“写使能命令”
        spi_wait_write_complete(); //等待写入完成
        SPI_NSS_LOW();             //NSS片选线使能
        spi_read_write(PAGE_PROGRAM);
        spi_read_write((addr >> 16) & 0xFF);
        spi_read_write((addr >>  8) & 0xFF);
        spi_read_write(addr         & 0xFF);
        while (page--) {
                spi_read_write(*buf);
                buf++;
        }
        SPI_NSS_HIGH();            //NSS片选线禁止
        spi_wait_write_complete(); //等待写入完成
}

/*******************************************************************************
  函数名称: main()
  输入参数: 无
  输出参数: 无
  函数功能: 
*******************************************************************************/
uint8_t buf[4096];
int main(void)
{
        gpio_setup();
        spi_setup();
        id = spi_read_id();     //读取FLASH—ID
        spi_erase_sector(0);    //擦除扇区（地址为0x00）
        spi_read_data(0, buf, 4096);
}
