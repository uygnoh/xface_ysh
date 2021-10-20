/******************************************************************************/
//SRAM到外设数据传输（SRAM => Peripheral）
//      => 
//      => 
//      => 
/******************************************************************************/
#define TXBUF_SIZE              500
uint8_t tx_buf[TXBUF_SIZE];

//GPIO设置
//_________________________________________________________
void gpio_setup(void)
{
        GPIO_InitTypeDef Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //打开GPIOA时钟
        Y.GPIO_Pin   = GPIO_Pin_9;                              //串口发送引脚
        Y.GPIO_Mode  = GPIO_Mode_AF_PP;                         //复用推挽输出
        Y.GPIO_Speed = GPIO_Speed_50MHz;                        //
        GPIO_Init(GPIOA, &Y);                                   //
        Y.GPIO_Pin   = GPIO_Pin_10;                             //串口接收引脚
        Y.GPIO_Mode  = GPIO_Mode_IN_FLOATING;                   //浮空输入
        GPIO_Init(GPIOA, &Y);                                   //
}

//USART设置
//_________________________________________________________
void uart_setup(void)
{
        USART_InitTypeDef Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  //打开USART1时钟
        Y.USART_BaudRate            = 115200;                   //配置波特率
        Y.USART_WordLength          = USART_WordLength_8b;      //8位字长
        Y.USART_StopBits            = USART_StopBits_1;         //1位停止位
        Y.USART_Parity              = USART_Parity_No;          //无奇偶校验
        Y.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        Y.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &Y);
        USART_Cmd(USART1, ENABLE);
}


#define  USART_TX_DMA_CHANNEL           DMA1_Channel4
#define  USART_TX_DMA_FLAG_TC           DMA1_FLAG_TC4
#define  USART_DR_ADDRESS               (USART1_BASE+0x04)
// SRAM到外设的数据传输
//_________________________________________________________
void dma_setup(void)
{
        DMA_InitTypeDef Y;
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);      //打开DMA1时钟
        Y.DMA_PeripheralBaseAddr = (uint32_t)(USART1_BASE+0x04);//配置USART1_DR寄存器地址
        Y.DMA_MemoryBaseAddr     = (uint32_t)tx_buf;            //配置数据来源地址
        Y.DMA_DIR                = DMA_DIR_PeripheralDST;       //配置数据目的地址
        Y.DMA_BufferSize         = TXBUF_SIZE;                  //传输数据长度
        Y.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;   //配置外设为地址增量禁止
        Y.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //配置外设数据传输宽度为（8）	
        Y.DMA_MemoryInc          = DMA_MemoryInc_Enable;        //配置SRAM为地址增量模式
        Y.DMA_MemoryDataSize     = DMA_PeripheralDataSize_Byte; //配置SRAM数据传输宽度为（8）
        Y.DMA_Mode               = DMA_Mode_Normal;             //配置DMA模式
        Y.DMA_Priority           = DMA_Priority_High;           //配置DMA优先级
        Y.DMA_M2M                = DMA_M2M_Disable;             //内存到内存传输禁止
        DMA_Init(DMA1_Channel4, &Y);                            //配置DMA1的通道4
        DMA_ClearFlag(DMA1_FLAG_TC4);                           //清除DMA1的通道4
        DMA_Cmd(DMA1_Channel4, ENABLE);                         //使能DMA1的通道4
}
