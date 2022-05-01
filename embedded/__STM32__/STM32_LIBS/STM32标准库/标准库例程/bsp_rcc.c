/* 使用外部高速晶体振荡器, 配置为72MHz */
void rcc_configure(void)
{
	/*  1 初始化为缺省值 */
	RCC_DeInit();
	/*  2 使能外部高速时钟 */	                       
	RCC_HSEConfig(RCC_HSE_ON);
	/*  3 等待外部高速时钟稳定 */ 
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
	/*  4 enable prefetch buffer */
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); 
	/*  5 flash 2 wait state  */
	FLASH_SetLatency(FLASH_Latency_2);
	/*  6 设置AHB时钟 HCLK = SYSCLK */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	/*  7 设置高速APB时钟 */                  
	RCC_PCLK2Config(RCC_HCLK_Div1);
	/*  8 设置低速APB时钟 */
	RCC_PCLK1Config(RCC_HCLK_Div2);
	/*  9 设置PLL */
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
	/* 10  打开PLL */ 
	RCC_PLLCmd(ENABLE);
	/* 11  等待PLL工作稳定 */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	/* 12 设置系统时钟 */  
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	/* 13 选择 PLL 作为系统时钟 */ 
	while (RCC_GetSYSCLKSource() != 0x08);

	/* 14 打开要使用的外设时钟 */ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd();
}

// STM32中断系统配置例程
{
	//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
	//使能GPIO的复用功能 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    

	// GPIO, 配置PB6为外部中断
	GPIO_DeInit(GPIOB);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//选择 GPIO 管脚用作外部中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6); 
	//EXTI, 外部中断配置
	EXIT_DeInit();
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//清除EXTI_Line6中断标志，为了安全
	EXTI_ClearITpendingBit(EXTI_Line6); 


	//NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 配置组为第1组，先占优先级 1 位， 从优先级 3 位 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* 外部中断线 9-5 中断 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure(&NVIC_InitStructure);      
}


//中断服务子程序
void EXTI9_5_IRQHandler(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Delay_MS(1000);
	EXTI_ClearITPendingBit(EXTI_Line6); //清除中断标志位
}
