/*******************************************************************************
        => CAN__回环测试程序__
*******************************************************************************/
CanRxMsg can_rx_data;         //定义为全局变量（CAN接收数据存储的地方）
CanTxMsg can_tx_data;
int main(void)
{
        uint8_t box;
        
        can_gpio_setup();
        can_nvic_setup();
        can_mode_setup();
        can_filter_setup();
        
        //CAN发送数据
        can_tx_data.StdId   = 0;
        can_tx_data.ExtId   = 0x1314;       //扩展ID
        can_tx_data.RTR     = CAN_RTR_Data; //发送的是数据帧
        can_tx_data.IDE     = CAN_Id_Extended;
        can_tx_data.DLC     = 1;            //发送一个字节
        can_tx_data.Data[0] = 10;    
        //把数据发送出去( 它返回发送邮箱号码 )
        box = CAN_Transmit(CAN1, &can_tx_data);
        while (CAN_TransmitStatus(CAN1, box) == CAN_TxStatus_Failed);
        
        while (1) {
                if (flag == 1) {
                        printf("接收到的数据0： %d", can_rx_data.Data[0]);
                        flag = 0;
                } else {
                }
        }
        return 0;
}



/*******************************************************************************
        => CAN__中断处理函数__
*******************************************************************************/
extern __IO uint32_t flag;
extern CanRxMsg can_rx_data;

void USB_LP_CAN1_RX0_IRQHandler(void)
{       //使用这个函数不用清除标志位（它自动清除）
        //从邮箱接收报文
        CAN_Receive(CAN1, CAN_FIFO0, &can_rx_data);
        //比较ID是否为0x1314
        if ((can_rx_data.ExtId == 0x1314)     && 
            (can_rx_data.IDE   == CAN_ID_EXT) && 
            (can_rx_data.DLC   == 8)) {
                flag = 1;
        } else {
                flag = 0;
        }
}



/*******************************************************************************
        => STM32F10x_CAN__主程序__
*******************************************************************************/
//CAN被重映射到（PB9， PB8）
//_________________________________________________________
static void can_gpio_setup(void)
{
        GPIO_InitTypeDef Y;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);

        Y.GPIO_Pin  = GPIO_Pin_9;               //CAN_TX_GPIOB_PIN_9
        Y.GPIO_Mode = GPIO_Mode_AF_PP;	        //复用推挽输出
        GPIO_Init(GPIOB, &Y);                   //
        Y.GPIO_Pin  = GPIO_Pin_8;               //CAN_RX_GPIOB_PIN_8
        Y.GPIO_Mode = GPIO_Mode_IPU;            //上拉输入
        GPIO_Init(GPIOB, &Y);                   //
}

//NVIC配置， 使能CAN1通道中断信号源
//_________________________________________________________
static void can_nvic_setup(void)
{
        NVIC_InitTypeDef Y;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
        Y.NVIC_IRQChannel                   = USB_LP_CAN1_RX0_IRQn;
        Y.NVIC_IRQChannelPreemptionPriority = 0;
        Y.NVIC_IRQChannelSubPriority        = 0;
        Y.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_Init(&Y);
}

//CAN模式设置
//_________________________________________________________
static void can_mode_setup(void)
{
        CAN_InitTypeDef Y;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
        CAN_DeInit(CAN1);                       //将外设CAN寄存器重设为缺省值
        Y.CAN_TTCM      = DISABLE;              //关闭时间触发通信模式使能
        Y.CAN_ABOM      = ENABLE;               //使能自动离线管理
        Y.CAN_AWUM      = ENABLE;               //使用自动唤醒模式
        Y.CAN_NART      = DISABLE;              //禁止报文自动重传
        Y.CAN_RFLM      = DISABLE;              //接收 FIFO 不锁定(溢出时新报文会覆盖原有报文)
        Y.CAN_TXFP      = DISABLE;              //发送 FIFO 优先级 取决于报文标示符
        Y.CAN_Mode      = CAN_Mode_LoopBack;    //调式使用（回环模式）*************
        Y.CAN_SJW       = CAN_SJW_2tq;          //重新同步跳跃宽度 2 个时间单元
        Y.CAN_BS1       = CAN_BS1_5tq;          //时间段 1 占用了 5 个时间单
        Y.CAN_BS2       = CAN_BS2_3tq;          //时间段 2 占用了 3 个时间单
        Y.CAN_Prescaler = 4;//波特率分频器, 定义了时间单元的时间长度 36/(1+5+3)/4=1Mbps
        CAN_Init(CANx, &Y);
}

//CAN过滤器设置（使用扩展帧， 工作在掩码模式）
#define PASS_ID        ((uint32_t)0x1314)
//_________________________________________________________
#define CAN_ID_STD     ((uint32_t)0x00000000)   //标准 ID
#define CAN_ID_EXT     ((uint32_t)0x00000004)   //扩展 ID
#define CAN_RTR_Data   ((uint32_t)0x00000000)   //数据帧
#define CAN_RTR_Remote ((uint32_t)0x00000002)   //远程帧
static void can_filter_setup(void)
{
        CAN_FilterInitTypeDef  Y;

        Y.CAN_FilterNumber         = 0;                    // 配置筛选器组为“0”
        Y.CAN_FilterMode           = CAN_FilterMode_IdMask;// 工作在掩码模式
        Y.CAN_FilterScale          = CAN_FilterScale_32bit;// 筛选器位宽为单个32位
        
        
        /* 使能筛选器, 按照标志符的内容进行比对筛选,
           扩展 ID 不是如下的就抛弃掉,是的话,会存入 FIFO0  */
        Y.CAN_FilterIdHigh         = ((
                                        ((uint32_t)0x1314 << 3) //
                                        | CAN_ID_EXT            //
                                        | CAN_RTR_DATA          //
                                      ) & 0xFFFF0000            //
                                     )  >> 16;                  //
        Y.CAN_FilterIdLow          = (
                                        ((uint32_t)0x1314 << 3) //
                                        | CAN_ID_EXT            //
                                        | CAN_RTR_DATA          //
                                     )  & 0xFFFF;               //

                          
        Y.CAN_FilterMaskIdHigh     = 0xFFFF;            //筛选器高 16 位每位必须匹配
        Y.CAN_FilterMaskIdLow      = 0xFFFF;            //筛选器低 16 位每位必须匹配
        Y.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ; //筛选器被关联到 FIFO_0
        Y.CAN_FilterActivation     = ENABLE;            //使能筛选器
        CAN_FilterInit(&Y);
        CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);        //CAN通信中断使能(接收邮箱0)
}



/*******************************************************************************
        => 
*******************************************************************************/
//CAN接收初始化
void Init_RxMes(CanRxMsg *RxMessage)
{
        uint8_t ubCounter = 0;

        RxMessage->StdId = 0x00;
        RxMessage->ExtId = 0x00;
        RxMessage->IDE   = CAN_ID_STD;
        RxMessage->DLC   = 0;
        RxMessage->FMI   = 0;
        for (ubCounter = 0; ubCounter < 8; ubCounter++) {
                RxMessage->Data[ubCounter] = 0x00;
        }
}
//CAN数据发送
void CAN_SetMsg(CanTxMsg *TxMessage)
{	  
        uint8_t ubCounter  = 0;
        TxMessage->ExtId   = 0x1314;
        TxMessage->IDE     = CAN_ID_EXT;
        TxMessage->RTR     = CAN_RTR_DATA;
        TxMessage->DLC     = 8;
        for (ubCounter = 0; ubCounter < 8; ubCounter++) {
                TxMessage->Data[ubCounter] = ubCounter;
        }
}
