void dma_init(void)
{
        RCC->AHB1ENR     |=  (0x01 << 22);      //使能DMA2时钟
        RCC->AHB1RSTR    |=  (0x01 << 22);      //DMA2所有寄存器清零
        RCC->AHB1RSTR    &= ~(0x01 << 22);      //结束DMA2寄存器清零
        DMA2_Stream0->CR |=  (0x02 << 25);      //选择通道2
        DMA2_Stream0->CR &= ~(0x03 << 23);      //存储器突发增量传输为0
        DMA2_Stream0->CR &= ~(0x03 << 21);      //外设突发增量传输为0
        DMA2_Stream0->CR &= ~(0x01 << 19);      //选择存储器地址0
        DMA2_Stream0->CR &= ~(0x01 << 18);      //单缓存模式
        DMA2_Stream0->CR |=  (0x03 << 16);      //中优先级
        DMA2_Stream0->CR &= ~(0x01 << 15);      //传输偏移长度以PSIZE为准
        DMA2_Stream0->CR |=  (0x01 << 13);      //存储器一次偏移（传输）16个位
        DMA2_Stream0->CR |=  (0x01 << 11);      //外设一次偏移（传输）16个位
        DMA2_Stream0->CR |=  (0x01 << 10);      //存储器地址递增模式（递增长度MSIZE）
        DMA2_Stream0->CR &= ~(0x01 << 9 );      //外设地址固定（ADC_DR寄存器地址）
        DMA2_Stream0->CR |=  (0x01 << 8 );      //循环模式
        DMA2_Stream0->CR &= ~(0x03 << 6 );      //数据方向（外设到存储器）
        DMA2_Stream0->CR &= ~(0x01 << 5 );      //DMA是流控器
        DMA2_Stream0->CR |=  (0x01 << 4 );      //使能传输完成中断
        
        //每次传输5个单位，必须为5个，实际上是多出一个
        //可能是规则完成后还有一个EOC
        DMA2_Stream0->NDTR = 5; 
        DMA2_stream0->M0AR = (uint32_t)&AdcRegData; //设置存储器地址
        DMA2_Stream0->PAR  = (uint32_t)&ADC3->DR;   //外设地址设置为ADC3规则组DR
        //设置DMA2_Stream0中断优先级
        NVIC_EnableIRQ(DMA2_Strea0_IRQn);       //使能DMA2_Strea0中断
        DMA2->LIFCR      |=  (0x01 << 5);       //清DMA2_Strea0传输完成中断
        DMA2_Stream0->CR |=  (0x01);            //开启DMA传输传输
        
}


struct ADC_STRUCT_T {
        uint16_t vu;
        uint16_t vv;
        uint16_t vw;
        uint16_t temp;
        //占位EOC（规则组转换完成后还有一个EOC）
        uint16_t last_eoc;
};
struct ADC_STRUCT_T AdcRegData;


void DMA2_Stream0_IRQHandler(void)
{
        DMA2->LIFCR     |= (0x01 << 5); //清中断
        printf("%d, %d, %d, %d, \n", 
                AdcRegData.vu,
                AdcRegData.vv,
                AdcRegData.vw,
                AdcRegData.temp);
                
}
