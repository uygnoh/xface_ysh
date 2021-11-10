void rcc_configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                               , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1);
}

void nvic_configuration(void)
{	
}

void iic_gpio_configruation(void)
{
	GPIO_InitTypeDef PORT;
	PORT.GPIO_Pin	= GPIO_Pin_6 | GPIO_Pin_7;	
	PORT.GPIO_Speed	= GPIO_Speed_50MHz;
	PORT.GPIO_Mode	= GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &PORT);	
}


void iic_configuration(void)
{
	I2C_InitypeDef I2C_INI;
	I2C_INI.I2C_Mode 		= // iic模式
	I2C_INI.I2C_DutyCycle 		= // iic占空比
	I2C_INI.I2C_Own_Address1 	= // iic设备地址
	I2C_INI.I2C_Ack 		= // iic应答
	I2C_INI.I2C_Acknowledge_Address	= // iic为几位地址
	I2C_INI.I2C_ClockSpeed		= // iic速度	  
	I2C_INI(I2C1, &I2C_INI);
	
	I2C_Cmd(I2C1, ENABLE);
}

#define EEPROM_DEV_ADDR	//器件地址 
#define EEPROM_DAT_ADDR//数据地址
#define EEPROM_DAT_ADDR_SIZE		8 //数据地址大小
void eeprom_write_byte(uint16_t eeprom_data_addr, uint8_t data)
{	/* 在操作硬件I2之前需要检测I2C是否处于“忙”状态 */
	while (I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY));
	
	/* 1. 主设备发送起始信号 */
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	/* 2. 主设备发送从机设备地址，最后一位为“写操作” */
	I2C_Send7bitAddress(I2C1, EEPROM_DEV_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	/* 3. 主设备发送从机数据地址 */
	#if (8 == EEPROM_DAT_ADDR_SIZE)
	I2C_SendData(I2C1, (eeprom_data_addr & 0x00FF));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	#else
	I2C_SendData(I2C1, (uint8_t)(eeprom_data_addr >> 8));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, (uint8_t)(eeprom_data_addr & 0x00FF));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	#endif
		
	/* 4. 主设备发送一字节数据 */
	I2C_SendData(I2C1, data);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	/* 5. 主设备发送停止信号 */
	I2C_GenerateSTOP(I2C1, ENABLE);
}

uint8_t eeprom_read_byte(uint16_t eeprom_data_addr)
{	
	uint8_t read_data;
	/* 在操作硬件I2之前需要检测I2C是否处于“忙”状态 */
	while (I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY));
	
	/* 1. 主设备发送起始信号 */
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	
	/* 2. 主设备发送从机设备地址，最后一位为“写操作” */
	I2C_Send7bitAddress(I2C1, EEPROM_DEV_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	/* 3. 主设备发送从机数据地址 */
	#if (8 == EEPROM_DAT_ADDR_SIZE)
	I2C_SendData(I2C1, (eeprom_data_addr & 0x00FF));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	#else
	I2C_SendData(I2C1, (uint8_t)(eeprom_data_addr >> 8));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C1, (uint8_t)(eeprom_data_addr & 0x00FF));
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	#endif
		
	/* 4. 主设备“从新发送”起始信号 */
	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
		
	/* 5. 主设备发送从机设备地址，最后一位为“读操作” */
	I2C_Send7bitAddress(I2C1, EEPROM_DEV_ADDR, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	/* 6. 读取从设备数据 */
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET);
	read_data = I2C_ReceiveData(I2C1);
	
	/* 7. 主设备发送停止信号 */
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return read_data;
}



