#include "adc.h"

/*
  ADC配置（APB2 = 72MHz）， ADC1的时钟为（12MHz）
  +________________________________________________________________+
  |    SystemClock / PCLK_DIV_6 = 12MHz                            |
  |________________________________________________________________|
*/
void adc_setup(void)
{
        // ADC1 CLOCK
        //_____________________________________________________________
        RCC->CFGR     &= ~(BIT_15 + BIT_14);    //分频因子清零ADC_PRE[15:14]__PCLK2_DIV_2
        RCC->CFGR     |= BIT_15;                //分频因子设置ADC_PRE[15:14]__PCLK2_DIV_6
        
        
        // GPIOA INITIALIZE
        //_____________________________________________________________
        GPIOA->CRL    &= 0XFFFFFF0FU;    //PA1__模拟输入
        
        
        // ADC1 CONFIGURATION
        //_____________________________________________________________
        ADC1->CR1     &= 0XFFF0FFFFU;   // 工作模式清零[19:16]
        ADC1->CR1     |= 0X00000000U;   // 0000：独立模式
        ADC1->CR1     &= ~(BIT_08);     // 非扫描模式
        
        ADC1->CR2     &= ~(BIT_01);     // 单次转换模式
        ADC1->CR2     &= 0xFFF1FFFFU;   // 软件控制转换EXTSEL[19:17]
        ADC1->CR2     |= 0xFFFEFFFFU;   // 111：SWSTART
        ADC1->CR2     |= BIT_20;        // 使用外部事件启动转换
        ADC1->CR2     &= ~(BIT_11);     // 数据对齐方式（右对齐）

        ADC1->SQR1    &= 0xFF0FFFFFU;   // 规则组转换的总数[23:20]
        ADC1->SQR1    |= 0x00000000U;   // 0000：1个转换

        ADC1->SMPR2   &= 0xFFFFFFF0U;   // 设置通道__1__的采样时间SMP0[2:0]
        ADC1->SMPR2   |= 0xFFFFFFF7U;   //  111：239.5周期 

        ADC1->CR2     |= BIT_00;        // 开启AD转换器
        ADC1->CR2     |= BIT_03;        // 初始化校准寄存器
        //ADC1->CR2_RSTCAL[3]该位由软件设置并由硬件清除。 在校准寄存器被初始化后该位将被清除
        while (ADC1->CR2 & BIT_03);     //等待校准寄存器已初始化完成
        //ADC1->CR2_CAL[2]该位由软件设置以开始校准，并在校准结束时由硬件清除
        ADC1->CR2     |= BIT_02;        //开启AD校准
        while (ADC1->CR2 & BIT_02);     //等待校准结束
}



/*
  输入参数: channel:通道值（0~16）
  返回数值: 转换结果
  函数功能: 获得ADC1某个通道的值
*/
uint16_t get_adc_value(uint8_t channel)
{
        ADC1->SQR3 &= 0XFFFFFFE0U;      // ADC1_SQR3__SQ1[4:0]
        ADC1->SQR3 |= channel;          // ADC1_通道__16__选择第（1_序列）
        ADC1->CR2  |= BIT_22;           // 启动规则转换通道
        while (!(ADC1->SR & BIT_01));   // 等待转换结束
        return (ADC1->DR);              // 返回adc值
}
