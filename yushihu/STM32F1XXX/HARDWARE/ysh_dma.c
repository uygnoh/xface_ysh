#include "ysh_dma.h"

adc_data_t      adc_data = {0};



void dma1_channel_1_setup(void)
{
        #define DMA1_ChannelXXX                         (DMA1_Channel1)
        DMA1_ChannelXXX->CCR &=  (0x00000000);          // ^0 [31:0]
                                                        // 
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_MEM2MEM);     // ^0 [14]
                                                        // 0: 非-存储器到存储器模式
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_PL_Msk);      // ^0 [13:12]
        DMA1_ChannelXXX->CCR |=  (DMA_CCR_PL_1);        // 1: 通道优先级 - 中级
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_MSIZE_Msk);   // ^0 [11:10]
        DMA1_ChannelXXX->CCR |=  (DMA_CCR_MSIZE_0);     // 1: 存储器数据宽度(16bit)
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_PSIZE_Msk);   // ^0 [9:8]
        DMA1_ChannelXXX->CCR |=  (DMA_CCR_PSIZE_0);     // 1: 外设数据宽度(16bit)
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_MINC);        // ^0 [7]
        DMA1_ChannelXXX->CCR |=  (DMA_CCR_MINC);        // 1: 存储器地址增量模式
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_PINC);        // ^0 [6]
                                                        // 0: 不执行外设地址增量操作
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_CIRC);        // ^0 [5]
        DMA1_ChannelXXX->CCR |=  (DMA_CCR_CIRC);        // 1: 执行循环操作
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_DIR);         // ^0 [4]
                                                        // 0: 从外设读
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_TEIE);        // ^0 [3]
                                                        // 0: 禁止TE中断 - 传输错误
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_HTIE);        // ^0 [2]
                                                        // 0: 禁止HT中断 - 传输半完成
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_TCIE);        // ^0 [1]
                                                        // 0: 禁止TC中断 - 传输完成
        DMA1_ChannelXXX->CCR &= ~(DMA_CCR_EN);          // ^0 [0]
                                                        // 0: 通道不工作
                                                        
                                                        
        DMA1_ChannelXXX->CNDTR  = 0x05;                 // 数据传输数量（5个）
        DMA1_ChannelXXX->CPAR   = (uint32_t)&ADC1->DR; // 外设地址
        DMA1_ChannelXXX->CMAR   = (uint32_t)&adc_data; // 存储器地址
        
        
        DMA1_ChannelXXX->CCR |=  (DMA_CCR_EN);          // 开启DMA
        
        
}
