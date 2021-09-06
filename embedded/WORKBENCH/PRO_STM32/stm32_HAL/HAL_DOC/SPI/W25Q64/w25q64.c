/******************************************************************************/
// STM32F103_HAL库句柄结构体定义
hspiTypeDef hspi;

static __IO uint32_t  spi_timeout = SPIT_LONG_TIMEOUT;   

static uint16_t spi_timeout_info(uint8_t err_code);

/**
  * @brief SPI MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(hspiTypeDef *hspi)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-1- 打开外设和GPIO时钟 */
	/* Enable GPIO TX/RX clock */
	SPIX_SCK_GPIO_CLK_ENABLE();
	SPIX_MISO_GPIO_CLK_ENABLE();
	SPIX_MOSI_GPIO_CLK_ENABLE();
	SPIX_CS_GPIO_CLK_ENABLE();
	/* Enable SPI clock */
	SPIX_CLK_ENABLE(); 


	/*##-2- 配置外设引脚 */  
	/* SPI SCK GPIO pin configuration  */
	GPIO_InitStruct.Pin	= SPIX_SCK_PIN;
	GPIO_InitStruct.Mode	= GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull	= GPIO_PULLUP;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(SPIX_SCK_GPIO_PORT, &GPIO_InitStruct);

	/* SPI MISO GPIO pin configuration  */
	GPIO_InitStruct.Pin = SPIX_MISO_PIN;  
	HAL_GPIO_Init(SPIX_MISO_GPIO_PORT, &GPIO_InitStruct);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_InitStruct.Pin = SPIX_MOSI_PIN; 
	HAL_GPIO_Init(SPIX_MOSI_GPIO_PORT, &GPIO_InitStruct);   

	GPIO_InitStruct.Pin = FLASH_CS_PIN ;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStruct); 
}

void spi_flash_init(void)
{
	hspi.Instance               = SPIX;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi.Init.Direction         = SPI_DIRECTION_2LINES;
	hspi.Init.CLKPhase          = SPI_PHASE_2EDGE;
	hspi.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	hspi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial     = 7;
	hspi.Init.DataSize          = SPI_DATASIZE_8BIT;
	hspi.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	hspi.Init.NSS               = SPI_NSS_SOFT;
	hspi.Init.TIMode            = SPI_TIMODE_DISABLE;

	hspi.Init.Mode = SPI_MODE_MASTER;

	HAL_SPI_Init(&hspi); 

	__HAL_SPI_ENABLE(&hspi);     
}
/******************************************************************************/



/*
 * @brief  使用SPI读取一个字节的数据
 * @param  无
 * @retval 返回接收到的数据
 */
uint8_t spi_flash_read_byte(void)
{
	return (spi_flash_send_byte(DUMMY_BYTE));
}

/*
 * @brief  使用SPI发送一个字节的数据
 * @param  byte：要发送的数据
 * @retval 返回接收到的数据
 */
uint8_t spi_flash_send_byte(uint8_t byte)
{
	spi_timeout = SPIT_FLAG_TIMEOUT;
	/* 等待发送缓冲区为空，TXE事件 */
	while (__HAL_SPI_GET_FLAG( &hspi, SPI_FLAG_TXE ) == RESET) {
		if((spi_timeout--) == 0)
			return spi_timeout_info(0);
	}		 
	/* 写入数据寄存器，把要写入的数据写入发送缓冲区 */
	WRITE_REG(hspi.Instance->DR, byte);

	spi_timeout = SPIT_FLAG_TIMEOUT;
	/* 等待接收缓冲区非空，RXNE事件 */
	while (__HAL_SPI_GET_FLAG( &hspi, SPI_FLAG_RXNE ) == RESET) {
		if((spi_timeout--) == 0) 
			return spi_timeout_info(1);
	}
	/* 读取数据寄存器，获取接收缓冲区数据 */
	return READ_REG(hspi.Instance->DR);
/* 	使用HAL_Library
	static uint8_t Rx_Data[1];
	static uint8_t Tx_Data[1];
	if ((HAL_SPI_TransmitReceive(&hspi, TxData, Rx_Data, 1, 100) != HAL_OK)
		return 0;
	else
		return Rx_Data[0];
*/
}

/*
 * @brief  使用SPI发送半字的数据
 * @param  Half Word：要发送的数据
 * @retval 返回接收到的数据
 */
uint16_t spi_flash_send_halfword(uint16_t halfword)
{
	spi_timeout = SPIT_FLAG_TIMEOUT;
	/* Loop while DR register in not emplty */
	while (__HAL_SPI_GET_FLAG( &hspi,  SPI_FLAG_TXE ) == RESET) {
		if((spi_timeout--) == 0) 
			return spi_timeout_info(2);
	}
	/* Send Half Word through the SPIX peripheral */
	WRITE_REG(hspi.Instance->DR, halfword);

	spi_timeout = SPIT_FLAG_TIMEOUT;
	/* Wait to receive a Half Word */
	while (__HAL_SPI_GET_FLAG( &hspi, SPI_FLAG_RXNE ) == RESET) {
		if((spi_timeout--) == 0) 
			return spi_timeout_info(3);
	}
	/* Return the Half Word read from the SPI bus */
	return READ_REG(hspi.Instance->DR);
}

/*
 * @brief  等待WIP(BUSY)标志被置0，即等待到FLASH内部数据写入完毕
 * @param  none
 * @retval none
 */
void spi_flash_wait_write_end(void)
{
	uint8_t flash_status = 0;

	/* 选择 FLASH: CS 低 */
	SPI_FLASH_CS_LOW();

	/* 发送 读状态寄存器 命令 */
	spi_flash_send_byte(W25X_ReadStatusReg);

	spi_timeout = SPIT_FLAG_TIMEOUT;
	/* 若FLASH忙碌，则等待 */
	do {
		/* 读取FLASH芯片的状态寄存器 */
		flash_status = spi_flash_send_byte(DUMMY_BYTE);
		if((spi_timeout--) == 0) {
			spi_timeout_info(4);
			return;
		}
	} while ((flash_status & WIP_FLAG) == SET); /* 正在写入标志 */

	/* 停止信号  FLASH: CS 高 */
	SPI_FLASH_CS_HIGH();
}

 /**
  * @brief  向FLASH发送写使能命令
  * @param  none
  * @retval none
  */
void spi_flash_write_enable(void)
{
	/* 通讯开始：CS低 */
	SPI_FLASH_CS_LOW();

	/* 发送写使能命令*/
	spi_flash_send_byte(W25X_WRITE_ENABLE);

	/*通讯结束：CS高 */
	SPI_FLASH_CS_HIGH();
}

/*******************************************************************************
* Function Name  : spi_flash_start_read_sequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - read_addr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void spi_flash_start_read_sequence(uint32_t read_addr)
{
	/* Select the FLASH: Chip Select low */
	SPI_FLASH_CS_LOW();

	/* Send "Read from Memory " instruction */
	spi_flash_send_byte(W25X_READ_DATA);

	/* Send the 24-bit address of the address to read from */
	/* Send read_addr high nibble address byte */
	spi_flash_send_byte((read_addr & 0xFF0000) >> 16);
	/* Send read_addr medium nibble address byte */
	spi_flash_send_byte((read_addr & 0xFF00) >> 8);
	/* Send read_addr low nibble address byte */
	spi_flash_send_byte(read_addr & 0xFF);
}


 /**
  * @brief  FLASH扇区擦除
  * @param  sector_addr：要擦除的扇区地址
  * @retval 无
  */
void spi_flash_sector_erase(uint32_t sector_addr)
{
	/* 发送FLASH写使能命令 */
	spi_flash_write_enable();
	spi_flash_wait_write_end();
	/* 擦除扇区 */
	/* 选择FLASH: CS低电平 */
	SPI_FLASH_CS_LOW();
	/* 发送扇区擦除指令*/
	spi_flash_send_byte(W25X_SECTOR_ERASE);
	/*发送擦除扇区地址的高位*/
	spi_flash_send_byte((sector_addr & 0xFF0000) >> 16);
	/* 发送擦除扇区地址的中位 */
	spi_flash_send_byte((sector_addr & 0xFF00) >> 8);
	/* 发送擦除扇区地址的低位 */
	spi_flash_send_byte(sector_addr & 0xFF);
	/* 停止信号 FLASH: CS 高电平 */
	SPI_FLASH_CS_HIGH();
	/* 等待擦除完毕*/
	spi_flash_wait_write_end();
}

 /**
  * @brief  FLASH整片擦除
  * @param  无
  * @retval 无
  */
void spi_flash_chip_erase(void)
{
	/* 发送FLASH写使能命令 */
	spi_flash_write_enable();

	/* 整块 Erase */
	/* 选择FLASH: CS低电平 */
	SPI_FLASH_CS_LOW();
	/* 发送整块擦除指令*/
	spi_flash_send_byte(W25X_CHIP_ERASE);
	/* 停止信号 FLASH: CS 高电平 */
	SPI_FLASH_CS_HIGH();

	/* 等待擦除完毕*/
	spi_flash_wait_write_end();
}

 /**
  * @brief  对FLASH按页写入数据，调用本函数写入数据前需要先擦除扇区
  * @param  pbuf，要写入数据的指针
  * @param  write_addr，写入页地址
  * @param  write_dat_len，写入数据长度，必须小于等于PER_PAGE_SIZE
  * @retval None
  */
void spi_flash_page_write(uint8_t *pbuf, 
                          uint32_t write_addr,
                          uint16_t write_dat_len)
{
	/* 发送FLASH写使能命令 */
	spi_flash_write_enable();

	/* 选择FLASH: CS低电平 */
	SPI_FLASH_CS_LOW();
	/* 写页写指令*/
	spi_flash_send_byte(W25X_PAGE_PROGRAM);
	/*发送写地址的高位*/
	spi_flash_send_byte((write_addr & 0xFF0000) >> 16);
	/*发送写地址的中位*/
	spi_flash_send_byte((write_addr & 0xFF00) >> 8);
	/*发送写地址的低位*/
	spi_flash_send_byte(write_addr & 0xFF);

	if(write_dat_len > PER_PAGE_SIZE) {
		write_dat_len = PER_PAGE_SIZE;
		FLASH_ERROR("spi_flash_page_write too large!");
	}

	/* 写入数据*/
	while (write_dat_len--) {
		/* 发送当前要写入的字节数据 */
		spi_flash_send_byte(*pbuf);
		/* 指向下一字节数据 */
		pbuf++;
	}

	/* 停止信号 FLASH: CS 高电平 */
	SPI_FLASH_CS_HIGH();

	/* 等待写入完毕*/
	spi_flash_wait_write_end();
}


 /**
  * @brief	对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
  * @param	pbuf，要写入数据的指针
  * @param	write_addr，写入地址
  * @param	write_dat_len，写入数据长度
  * @retval	0,页地址对齐 1,页地址不对齐
  */
uint8_t spi_flash_buf_write(uint8_t* pbuf, 
                         uint32_t write_addr, 
                         uint16_t write_dat_len)
{
	uint8_t page_num = 0, 
	uint8_t single_num = 0, 
	uint8_t addr = 0, 
	uint8_t count = 0, 
	uint8_t tmp = 0;

	/*mod运算求余，若write_addr是PAGE_SIZE整数倍，运算结果addr值为0*/
	addr = write_addr % PAGE_SIZE;

	/*差count个数据值，刚好可以对齐到页地址*/
	count = PAGE_SIZE - addr;	
	/*计算出要写多少整数页*/
	page_num =  write_dat_len / PAGE_SIZE;
	/*mod运算求余，计算出剩余不满一页的字节数*/
	single_num = write_dat_len % PAGE_SIZE;
	
/*************************** 若地址与 PAGE_SIZE 对齐  *************************/
	/* addr=0,则write_addr 刚好按页对齐 aligned  */
	if (addr == 0) {
		/* write_dat_len < PAGE_SIZE */
		if (page_num == 0) {
			spi_flash_page_write(pbuf, write_addr, write_dat_len);
		} else { 
		/* write_dat_len > PAGE_SIZE */
		/*先把整数页都写了*/
			while (page_num--) {
				spi_flash_page_write(pbuf, write_addr, PAGE_SIZE);
				write_addr +=  PAGE_SIZE;
				pbuf += PAGE_SIZE;
			}
			/*若有多余的不满一页的数据，把它写完*/
			spi_flash_page_write(pbuf, write_addr, single_num);
		}
		return 0;
	}	
/*************************** 若地址与 PAGE_SIZE 不对齐  ************************/	
	/* write_dat_len < PAGE_SIZE */
	if (page_num == 0) 
	{
		/* 当前页剩余的count个位置比single_num小，写不完 */
		if (single_num > count) {
			tmp = single_num - count;
						
			/* 先写满当前页 */
			spi_flash_page_write(pbuf, write_addr, count);
			write_addr +=  count;
			pbuf += count;
						
			/*再写剩余的数据*/
			spi_flash_page_write(pbuf, write_addr, tmp);
		} else { /*当前页剩余的count个位置能写完single_num个数据*/		
			spi_flash_page_write(pbuf, write_addr, write_dat_len);
		}
		
	/* write_dat_len > PAGE_SIZE */
	} else { 
		/*地址不对齐多出的count分开处理，不加入这个运算*/
		write_dat_len -= count;
		page_num =  write_dat_len / PAGE_SIZE;
		single_num = write_dat_len % PAGE_SIZE;
		spi_flash_page_write(pbuf, write_addr, count);
		write_addr +=  count;
		pbuf += count;
				
		/*把整数页都写了*/
		while (page_num--) {
			spi_flash_page_write(pbuf, write_addr, PAGE_SIZE);
			write_addr +=  PAGE_SIZE;
			pbuf += PAGE_SIZE;
		}
		/*若有多余的不满一页的数据，把它写完*/
		if (single_num != 0)
			spi_flash_page_write(pbuf, write_addr, single_num);
	}
	return 1;
}


 /**
  * @brief   读取FLASH数据
  * @param   pbuf，存储读出数据的指针
  * @param   read_addr，读取地址
  * @param   read_dat_len，读取数据长度
  * @retval 无
  */
void spi_flash_buf_read(uint8_t* pbuf, 
                        uint32_t read_addr, 
                        uint16_t read_dat_len)
{
	/* 选择FLASH: CS低电平 */
	SPI_FLASH_CS_LOW();

	/* 发送 读 指令 */
	spi_flash_send_byte(W25X_READ_DATA);

	/* 发送 读 地址高位 */
	spi_flash_send_byte((read_addr & 0xFF0000) >> 16);
	/* 发送 读 地址中位 */
	spi_flash_send_byte((read_addr& 0xFF00) >> 8);
	/* 发送 读 地址低位 */
	spi_flash_send_byte(read_addr & 0xFF);

	/* 读取数据 */
	while (read_dat_len--) {
		/* 读取一个字节*/
		*pbuf = spi_flash_send_byte(DUMMY_BYTE);
		/* 指向下一个字节缓冲区 */
		pbuf++;
	}

	/* 停止信号 FLASH: CS 高电平 */
	SPI_FLASH_CS_HIGH();
}


 /**
  * @brief  读取FLASH ID
  * @param 	无
  * @retval FLASH ID
  */
uint32_t spi_flash_read_id(void)
{
	uint32_t tmp  = 0, 
	uint32_t tmp0 = 0, 
	uint32_t tmp1 = 0, 
	uint32_t tmp2 = 0;

	/* 开始通讯：CS低电平 */
	SPI_FLASH_CS_LOW();

	/* 发送JEDEC指令，读取ID */
	spi_flash_send_byte(W25X_JEDEC_DEVICE_ID);

	/* 读取一个字节数据 */
	tmp0 = spi_flash_send_byte(DUMMY_BYTE);

	/* 读取一个字节数据 */
	tmp1 = spi_flash_send_byte(DUMMY_BYTE);

	/* 读取一个字节数据 */
	tmp2 = spi_flash_send_byte(DUMMY_BYTE);

	/* 停止通讯：CS高电平 */
	SPI_FLASH_CS_HIGH();

	/*把数据组合起来，作为函数的返回值*/
	tmp = (tmp0 << 16) | (tmp1 << 8) | tmp2;

	return tmp;
}

 /**
  * @brief  读取FLASH Device ID
  * @param 	无
  * @retval FLASH Device ID
  */
uint32_t spi_flash_read_device_id(void)
{
	uint32_t tmp = 0;

	/* Select the FLASH: Chip Select low */
	SPI_FLASH_CS_LOW();

	/* Send "RDID " instruction */
	spi_flash_send_byte(W25X_DEVICE_ID);
	spi_flash_send_byte(DUMMY_BYTE);
	spi_flash_send_byte(DUMMY_BYTE);
	spi_flash_send_byte(DUMMY_BYTE);

	/* Read a byte from the FLASH */
	tmp = spi_flash_send_byte(DUMMY_BYTE);

	/* Deselect the FLASH: Chip Select high */
	SPI_FLASH_CS_HIGH();

	return tmp;
}





//进入掉电模式
void spi_flash_power_down(void)   
{ 
	/* 选择 FLASH: CS 低 */
	SPI_FLASH_CS_LOW();

	/* 发送 掉电 命令 */
	spi_flash_send_byte(W25X_POWER_DOWN);

	/* 停止信号  FLASH: CS 高 */
	SPI_FLASH_CS_HIGH();
}   

//唤醒
void spi_flash_wakeup(void)   
{
	/*选择 FLASH: CS 低 */
	SPI_FLASH_CS_LOW();

	/* 发上 上电 命令 */
	spi_flash_send_byte(W25X_RELEASE_POWER_DOWN);

	/* 停止信号 FLASH: CS 高 */
	SPI_FLASH_CS_HIGH();
}   


/**
  * @brief  等待超时函数
  * @param  None.
  * @retval None.
  */
static  uint16_t spi_timeout_info(uint8_t err_code)
{
  /* 等待超时后的处理,输出错误信息 */
  FLASH_ERROR("SPI 等待超时!err_code = %d",err_code);
  return 0;
}
