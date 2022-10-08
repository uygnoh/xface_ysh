#include "adc.h"


/*******************************************************************************
  函数名称: void adc_conf(void)
  输入参数: 无
  输出参数: 无
  函数功能: ADC配置（设置系统时钟为72MHz）， ADC1的时钟为（12MHz）
  +________________________________________________________________+
  |    SystemClock / PCLK_DIV_6 = 12MHz                            |
  |________________________________________________________________|
*******************************************************************************/
void adc_setup(void)
{
        RCC->APB2RSTR   |=  BIT_00;             // AFIO  时钟复位
        RCC->APB2RSTR   &= ~BIT_00;             //
        RCC->APB2RSTR   |=  BIT_02;             // GPIOA 时钟复位
        RCC->APB2RSTR   &= ~BIT_02;             //
        RCC->APB2RSTR   |=  BIT_09;             // ADC1  时钟复位
        RCC->APB2RSTR   &= ~BIT_09;             //
        RCC->APB2ENR    |=  BIT_00;             // AFIO  时钟开启
        RCC->APB2ENR    |=  BIT_02;             // GPIOA 时钟开启
        RCC->APB2ENR    |=  BIT_09;             // ADC1  时钟开启
        


        GPIOA->CRL      &=  (0xFFFFFF0F);       // PA1 - aIN-1 模拟输入通道1
        RCC->CFGR       &= ~(BIT_15 + BIT_14);  // 分频因子清零ADC_PRE[15:14]__PCLK2_DIV_2
        RCC->CFGR       |=  BIT_15;             // 分频因子设置ADC_PRE[15:14]__PCLK2_DIV_6
        
        
        ADC1->CR1       &=  (0xFFF0FFFF);       // DUALMOD[19:16] : 双模式选择
        ADC1->CR1       |=  (0xFFF0FFFF);       // 独立工作模式
        ADC1->CR1       &= ~(BIT_08);           // 非扫描模式
        ADC1->CR2       &= ~(BIT_01);           // 单次转换模式
        ADC1->CR2       &= ~(0xFFF1FFFF);       // CR2__EXTSEL[19:17] 111:SWSTART
        ADC1->CR2       |=  (0xFFFEFFFF);       // CR2__EXTSEL[19:17] 软件控制转换
        ADC1->CR2       |=  BIT_20;             // !!!必须使用一个事件来触发
        ADC1->CR2       &= ~(BIT_11);           // 数据右对齐

        ADC1->SQR1      &= ~(0xFF0FFFFF);       // SQR1__L[23:20]__规则组转换的总数
        ADC1->SQR1      |=  (0x00000000);       // Regular channel sequence length
        ADC1->SQR3      &= ~(0xFFFFFFE0);       // ADC1_SQR3__SQ1[4:0]
        ADC1->SQR3      |=  (0xFFFFFFE1);       // ADC1_通道1__选择第（1_序列）

        ADC1->SMPR2     &= ~(7 << 3);           // 设置通道1 的采样时间
        ADC1->SMPR2     |=  (7 << 3);           // 通道1（SMP0[2:0]__239.5 cycles）
}



void adc_start_convert(void)
{
        ADC1->CR2       |= BIT_00;      // 开启AD转换器
        ADC1->CR2       |= BIT_03;      // 初始化校准寄存器
        // ADC1->CR2_RSTCAL[3]该位由软件设置并由硬件清除。 
        // 在校准寄存器被初始化后该位将被清除
        while (ADC1->CR2 & BIT_03);     // 等待校准寄存器已初始化完成
        // ADC1->CR2_CAL[2]该位由软件设置以开始校准，并在校准结束时由硬件清除
        ADC1->CR2       |= BIT_02;      // 开启AD校准
        while (ADC1->CR2 & BIT_02);     // 等待校准结束
}


uint16_t adc_read(void)
{
        ADC1->CR2       |= BIT_22;      // 启动规则转换通道
        while (!(ADC1->SR & BIT_01));   // 等待转换结束
        return (ADC1->DR);              // 返回adc值
}
