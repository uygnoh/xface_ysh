/******************************************************************************/
//存储器到存储器DMA传输（FLASH => SRAM）
//      => 定义(src_const_buff[]数组作DMA传输的数据源)
//      => const关键字，就是将src_const_buff[]数组变量类型 ->定义为常量类型
//      => const src_const_buff[]表示数据存储在FLASH中
/******************************************************************************/
#define BUFFER_SIZE             12

//下面的数据存储在内部FLASH中
//_________________________________________________________
const uint32_t src_const_buf[BUFFER_SIZE] = {
        0x01020304, 0x06060708, 0x090A0B0C, 0x0D0E0E10,
        0x11020304, 0x16060708, 0x190A0B0C, 0x1D0E0E10,
        0x21020304, 0x26060708, 0x290A0B0C, 0x2D0E0E10
};

//下面的数据存储在内部SRAM中
//_________________________________________________________
uint32_t destination_buf[BUFFER_SIZE];



/*******************************************************************************
  函数名称: dma_setup()
  输入参数: 无
  输出参数: 无
  函数功能: 存储器到存储器DMA数据传输（FLASH => SRAM）
*******************************************************************************/
void dma_setup(void)
{
        DMA_InitTypeDef Y;
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);      //打开DMA1时钟
        Y.DMA_PeripheralBaseAddr = src_const_buf;               //配置外设为数据来源
        Y.DMA_MemoryBaseAddr     = destination_buf;             //SRAM为目的地
        Y.DMA_DIR                = DMA_DIR_PeriphealSRC;        //FLASH => SRAM
        Y.DMA_BufferSize         = BUFFER_SIZE;                 //传输数据大小
        Y.DMA_PeriphealInc       = DMA_PeripheralInc_Enable;    //配置外设为地址增量模式
        Y.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //数据宽度为（32位)
        Y.DMA_MemoryInc          = DMA_MemoryInc_Enable;        //配置SRAM为地址增量模式
        Y.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;     //数据宽度为（32位)
        Y.DMA_Mode               = DMA_Mode_Normal;             //配置DMA模式
        Y.DMA_Priority           = DMA_Priority_High;           //配置DMA优先级
        Y.DMA_M2M                = DMA_M2M_Enable;              //配置DMA为内存到内存传输
        DMA_Init(DMA1_Channel6, &Y);                            //配置DMA1的通道6
        DMA_ClearFlag(DMA1_FLAG_TC6);                           //清除DMA1的通道6
        DMA_Cmd(DMA1_Channel6, ENABLE);                         //使能DMA1的通道6
}

/*******************************************************************************
  函数名称: buf2_cmp()
  输入参数: 无
  输出参数: 无
  函数功能: 判断指定的两个数据是否相等
          如果完全相等返回1， 只要其中一个不相等返回0
*******************************************************************************/
uint8_t buf2_cmp(const uint32_t *src_buf,
                  uint32_t       *dst_buf,
                  uint16_t        buf_len)
{
        while (buf_len--) {
                if (*src_buf != *dst_buf) {
                        return 0;
                }
                src_buf++;
                dst_buf++;
        }
        return 1;
}


int main(void)
{
        uint8_t status;
        dma_setup();
        //检测传输是否完成
        while (DMA_GetFlagStatus(DMA1_FLAG_TC6) == RESET);
        status = buf2_cmp(src_const_buf, destination_buf, BUFFER_SIZE);
        if (status == 0) {
                //关闭LED
        } else {
                //打开LED
        }
}
