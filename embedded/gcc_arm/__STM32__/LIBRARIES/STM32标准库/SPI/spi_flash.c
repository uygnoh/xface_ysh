/*******************************************************************************
  函数名称: spi_gpio_setup()
  输入参数: 无
  输出参数: 无
  函数功能: SPI_GPIO引脚初始化配置
*******************************************************************************/
void spi_gpio_setup(void)
{
        GPIO_InitTypeDef        Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        
        // MOSI(复用功能推挽输出)
        Y.GPIO_Pin   = SPI_MOSI_PIN;            // 选择GPIO引脚
        Y.GPIO_Speed = GPIO_Speed_50MHz;        // 设置GPIO引脚速度
        Y.GPIO_Mode  = GPIO_Mode_AF_PP;         // 设置GPIO引脚功能
        GPIO_Init(SPI_MOSI_PORT, &Y);           // 写入配置信息到寄存器中
                
        // MISO(浮空输入)
        Y.GPIO_Pin   = SPI_MISO_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_Init(SPI_MISO_PORT, &Y);
        
        // SCLK(复用功能推挽输出)
        Y.GPIO_Pin   = SPI_SCLK_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_Init(SPI_SCLK_PORT, &Y);
        
        // 初始化NSS引脚，使用软件控制，所以直接设置成推挽输出
        Y.GPIO_Pin   = SPI_NSS_PIN;
        Y.GPIO_Speed = GPIO_Speed_50MHz;
        Y.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_Init(SPI_NSS_PORT, &Y);
        // 设置NSS引脚空闲状态为高电平
        SPI_NSS_HIGH();
}



/*******************************************************************************
  函数名称: spi_flash_init()
  输入参数: 无
  输出参数: 无
  函数功能: SPI初始化配置
*******************************************************************************/
void spi_flash_init(void)
{
        // 72MHz / 2 = 36MHz
        SPI_InitTypeDef         Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);            // SPI时钟打开
        Y.SPI_BaudRatePrescaler = SPI_RaudRatePrescaler_2;              // 分频因子(2)
        Y.SPI_CPHA              = SPI_CPHA_2Edge;                       // 模式3
        Y.SPI_CPOL              = SPI_CPOL_HIGH;                        // 模式3
        Y.SPI_CRCPolynomial     = 0;                                    // 不使用CRC功能
        Y.SPI_DataSize          = SPI_DataSize_8b;                      // 8位数据位
        Y.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;      // 双线全双工
        Y.SPI_FirstBit          = SPI_First_MSB;                        // 高位在前
        Y.SPI_Mode              = SPI_Mode_Master;                      // 配置为主模式
        Y.SPI_NSS               = SPI_NSS_Soft;                         // 配置为软件控制
        SPI_Init(SPI1, &Y);                                             // 写入配置到寄存器
        SIP_Cmd(SPI1, ENABLE);                                          // 使能SPI1
}



/*******************************************************************************
  函数名称: spi_read_write()
  输入参数: data    要写入的数据
  输出参数: 返回接收到的数据
  函数功能: FLASH__W25Q64__读写一个字节
*******************************************************************************/
uint8_t spi_read_write(uint8_t data)
{
        uint16_t timeout;
        // 检测并等待发送（TX）缓冲区为空， TXE（事件）
        // ____________________________________________________
        timeout = SPI_TIMEOUT;
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
                if ((timeout--) == 0) {
                        return spi_timeout_callback(0);
                }
        }
        // 写入数据寄存器， 把写入的数据写入到发送缓冲区
        SPI_I2S_SendData(SPI1, data);
        
        
        // 检测并等待接收（RX）缓冲区为非空
        // ____________________________________________________
        timeout = SPI_TIMEOUT;
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {
                if ((timeout--) == 0) {
                        return spi_timeout_callback(1);
                }
        }
        // 读取数据寄存器， 获取接收缓冲区数据
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
        spi_read_write(READ_STATUS);                    // 发送读取命令
        do {                                            // 读取状态寄存器的值
                status_reg = spi_read_write(DUMMY);
        } while ((stauts_reg & 0x01) == 1);
        SPI_NSS_HIGH();
}



/*******************************************************************************
  函数名称: spi_flash_read_id()
  输入参数: 无
  输出参数: ID号码
  函数功能: 读取__W25Q64__ID号码
*******************************************************************************/
uint32_t spi_read_id(void)
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
uint32_t spi_read_id(void)
{
        uint32_t flash_id;
        uint32_t tmp0 = 0, tmp1 = 0, tmp2 = 0;
        SPI_NSS_LOW();                          // 开始通讯， CS低电平
        spi_read_write(READ_JEDEC_ID);          // 发送（JEDEC）指令， 读取ID
        tmp0 = spi_read_write(DUMMY);           // 读取一个字节
        tmp1 = spi_read_write(DUMMY);           // 读取一个字节
        tmp2 = spi_read_write(DUMMY);           // 读取一个字节
        SPI_NSS_HIGH();                         // 停止通讯， CS拉高
                                                // 组合数据， 并返回
        flash_id = (tmp0 << 16) | (tmp1 << 8) | tmp2;
        return flash_id;
}



/*******************************************************************************
  函数名称: spi_erase_sector()
  输入参数: addr， 24位FLASH地址
  输出参数: 无
  函数功能: __W25Q64__擦除FLASH指定扇区
  // Sector Erase (4KB) // 一次性擦除 4KByte
*******************************************************************************/
void spi_erase_sector(uint32_t addr)
{
        spi_flash_write_enable();               // 擦除扇区之前，先发送“写使能命令”
        spi_wait_write_complete();              // 等待写入完成
        SPI_NSS_LOW();
        spi_read_write(ERASE_SECTOR);
        spi_read_write((addr >> 16) & 0xFF);    // 先发高位字节
        spi_read_write((addr >>  8) & 0xFF);    // 再发中位字节
        spi_read_write(addr         & 0xFF);    // 再发低位字节
        SPI_NSS_HIGH();
        spi_wait_write_complete();              // 等待擦除扇区结束
}
void spi_erase_sector(uint32_t addr)
{
        spi_flash_write_enable();               // 擦除扇区之前，先发送“写使能命令”
        spi_wait_write_complete();              // 等待写入完成
        SPI_NSS_LOW();                          // 选择SPI-FLASH，开始通讯
        spi_read_write(ERASE_SECTOR);           // 发送擦除扇区指令
        spi_read_write((addr & 0xFF0000) >> 16);// 先送擦除扇区地址的高位字节
        spi_read_write((addr & 0xFF00)   >> 8); // 再送擦除扇区地址的中位字节
        spi_read_write(addr  & 0xFF);           // 再送擦除扇区地址的低位字节
        SPI_NSS_HIGH();                         // 结束SPI通讯
        spi_wait_write_complete();              // 等待擦除扇区擦除完成
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
void spi_write_page(uint32_t addr, uint8_t *buf, uint16_t len)
{
        if (len > PAGE_SIZE) {
                printf("SPI_FLASH_PAGE_WRITE too large!");
                return;
        }                                       // 写入数据之前， 要先擦除 //
        spi_flash_write_enable();               // 写入数据之前，先发送“写使能命令”
        spi_wait_write_complete();              // 等待写入完成
        SPI_NSS_LOW();                          // NSS片选线使能
        spi_read_write(PAGE_PROGRAM);           // 页编程
        spi_read_write((addr >> 16) & 0xFF);    // 发送写地址的高位
        spi_read_write((addr >>  8) & 0xFF);    // 发送写地址的中位
        spi_read_write(addr         & 0xFF);    // 发送写地址的低位
        while (len--) {
                spi_read_write(*buf);
                buf++;
        }
        SPI_NSS_HIGH();                         // NSS片选线禁止
        spi_wait_write_complete();              // 等待写入完成
}



/*******************************************************************************
  函数名称: spi_read_buffer()
  输入参数: addr， 24位FLASH地址， 从那个位置开始读取数据
  输入参数: buf，  数据存储缓冲区
  输入参数: len，  读取数据的长度
  输出参数: 无
  函数功能: 从__W25Q64__中读取多个字节
*******************************************************************************/
void spi_read_buffer(uint32_t addr, uint8_t *buf, uint32_t len)
{
        SPI_NSS_LOW();
        spi_read_write(READ_DATA);
        spi_read_write((addr >> 16) & 0xFF);    // spi_read_write((addr & 0xFF0000) >> 16);
        spi_read_write((addr >>  8) & 0xFF);    // spi_read_write((addr & 0xFF00)   >> 8);
        spi_read_write(addr         & 0xFF);    // spi_read_write((addr & 0xFF));
        
        while (len--) {
                *buf = spi_read_write(DUMMY);
                buf++
        }
        SPI_NSS_HIGH();
}
// _____________________________________________________________________________
// 对<SPI-FLASH>写入数据， 调用本函数写入数据前需要先擦除扇区
//      WriteAddr       // 要写入数据的地址
//      pBuffer         // 要写入数据的指针
//      NumByteToWrite  // 要写入数据的长度
//      #define SPI_FLASH_PageSize              256
// _____________________________________________________________________________
void spi_write_buffer(uint32_t WriteAddr, uint8_t *pBuffer, uint16_t NumByteToWrite)
{
        uint8_t NumOfPage   = 0;
        uint8_t NumOfSingle = 0;
        uint8_t Addr        = 0;
        uint8_t count       = 0;
        uint8_t temp        = 0;
        
        // mod运算求余， 若（WriteAddr）是SPI_FLASH_PageSize整数倍， 运算结果： Addr值为0
        Addr = WriteAddr % SPI_FLASH_PageSize;
        // 差 count个数据值， 刚好可以对齐到页地址
        count = SPI_FLASH_PageSize - Addr;
        // 计算出要写多少个整数页
        NumOfPage = NumByteToWrite / SPI_FLASH_PageSize;
        // mod运算求余， 计算出剩余不满一页的字节数
        NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
        
        
        // _____________________________________________________________________
        // SPI_FLASH_PageSize 页地址对齐
        // Addr = 0; 则WrtieAddr地址刚好页对齐
        // _____________________________________________________________________
        if (Addr == 0) {
                // 如果不满一页， 直接写入. （NumByteToWrite < SPI_FLASH_PageSize）
                if (NumOfPage == 0) {
                        spi_write_page(WriteAddr, pBuffer, NumByteToWrite);
                } else {
                        // 先把整页都写完
                        while (NumOfPage--) {
                                spi_write_page(WriteAddr, pBuffer, NumByteToWrite);
                                WriteAddr += SPI_FLASH_PageSize;
                                pBuffer   += SPI_FLASH_PageSize;
                        }
                        // 若有多余的不满一页的数据， 再把它写完
                        spi_write_page(WriteAddr, pBuffer, NumByteToWrite);
                }
                
                
        // _____________________________________________________________________
        // SPI_FLASH_PageSize 页地址不对齐
        // Addr != 0; 则WrtieAddr地址不对齐
        // _____________________________________________________________________
        } else {
                // NumByteToWrite < SPI_FLASH_PageSize
                // ____________________________________________________
                if (NumOfPage == 0) {
                        // 当前剩余的 count个位置比NumOfSingle小， 一页写不完
                        if (NumOfSingle > count) {
                                temp = NumOfSingle - count;
                                // 先写满当前页
                                spi_write_page(WriteAddr, pBuffer, count);
                                WriteAddr += count;
                                pBuffer   += count;
                                // 再写剩余的数据
                                spi_write_page(WriteAddr, pBuffer, temp);
                        // 当前剩余的 count个位置能写完NumOfSingle个数
                        } else {
                                spi_write_page(WriteAddr, pBuffer, NumByteToWrite);
                        }
                // NumByteToWrite > SPI_FLASH_PageSize
                // ____________________________________________________
                } else {
                        // 地址不对齐多出的count分开处理， 不加入这个运算
                        NumByteToWrite -= count;
                        NumOfPage = NumByteToWrite / SPI_FLASH_PageSize;
                        NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
                        // 先写完count个数据， 为的是让下一次要写的地址对齐
                        spi_write_page(WriteAddr, pBuffer, count);
                        
                        // 接下来重复地址对齐情况
                        WriteAddr += count;
                        pBuffer   += count;
                        // 把整页都写了
                        while (NumOfPage--) {
                                spi_write_page(WriteAddr, pBuffer, SPI_FLASH_PageSize);
                                WriteAddr += SPI_FLASH_PageSize;
                                pBuffer   += SPI_FLASH_PageSize;
                        }

                        // 若有多余的不满一页的数据， 把它写完
                        if (NumOfSingle != 0) {
                                spi_write_page(WriteAddr, pBuffer, NumOfSingle);
                        }
                        
                }

        }
        
}
/*******************************************************************************
  函数名称: main()
  输入参数: 无
  输出参数: 无
  函数功能: 
*******************************************************************************/
// SPI-FLASH 进入低功耗模式
void spi_flash_powerdown(void)
{
        SPI_NSS_LOW();
        spi_read_write(POWER_DOWN);             // POWER_DOWN = (0xB9)
        SPI_NSS_HIGH();
}
// SPI-FLASH 唤醒
void spi_flash_wakeup(void)
{
        SPI_NSS_LOW();
        spi_read_write(ReleasePowerDown);       // ReleasePowerDown = (0xAB)
        SPI_NSS_HIGH();
}


uint8_t         read_buf[4096];
uint8_t         write_buf[4096];
int main(void)
{
        gpio_setup();
        spi_setup();
        
        
        // 读取FLASH—ID
        // ____________________________________________________
        id = spi_read_id();
        printf("SPI-FLASH ID: %d\n", id);
        
        
        // 擦除扇区（从0扇区开始擦除， 擦除4096个字节）
        // 擦除扇区和向SPI-FLASH中写入数据（需在等待操作完成）
        // ____________________________________________________
        spi_erase_sector(0);
        
        
        // 从0地址开始取4096个字节数据（不需在等待）, 存储到read_buf
        // ____________________________________________________
        spi_read_buffer(0, read_buf, 4096);
        for (i = 0; i < 4096; i++) {
                printf("0x%x ", read_buff[i]);
                if (i % 10 == 0) {
                        printf("\r\n"); // 每10个数据加一个回车
                }
        }
        
        
        // 页编程， 一次性最多写入（256）字节
        // ____________________________________________________
        for (i = 0; i < 256; i++) {
                write_buf[i] = i;
        }
        spi_write_page(0, write_buf, 4096);
}



void spi_timeout_callback(uint8_t error_code)
{
        printf("TIMEOUT_CODE: %d\n", error_code);
}
