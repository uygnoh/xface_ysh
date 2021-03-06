#include "temperature.h"

/*******************************************************************************
  函数名称: void adc1_16_conf(void)
  输入参数: 无
  输出参数: 无
  函数功能: ADC配置（设置系统时钟为72MHz）， ADC1的时钟为（12MHz）
  +________________________________________________________________+
  |    SystemClock / PCLK_DIV_6 = 12MHz                            |
  |________________________________________________________________|
*******************************************************************************/
void adc1_16_conf(void)
{
        //GPIOA_CLOCK_ENABLE();                 //使能PORTA口时钟
        //GPIOA->CRL    &= 0XFFFFFF0F;          //PA1__模拟输入
        ADC1_CLOCK_ENABLE();                    //ADC1时钟使能
        RCC->APB2RSTR |= BIT_09;                //ADC1复位
        RCC->APB2RSTR &= ~(BIT_09);             //ADC1复位结束
        RCC->CFGR     &= ~(BIT_15 + BIT_14);    //分频因子清零ADC_PRE[15:14]__PCLK2_DIV_2
        RCC->CFGR     |= BIT_15;                //分频因子设置ADC_PRE[15:14]__PCLK2_DIV_6
        ADC1->CR1     &= 0XF0FFFF;              //ADC1_CR1__工作模式清零__
        ADC1->CR1     |= 0XF0FFFF;              //ADC1_CR1__独立工作模式__
        ADC1->CR1     &= ~(BIT_08);             //ADC1_CR1__非扫描模式
        ADC1->CR2     &= ~(BIT_01);             //ADC1_CR2__单次转换模式
        ADC1->CR2     &= (uint32_t)0xFFF1FFFF;  //ADC1_CR2__EXTSEL[19:17]
        ADC1->CR2     |= (uint32_t)0xFFFEFFFF;  //ADC1_CR2__EXTSEL[19:17]软件控制转换
        ADC1->CR2     |= BIT_20;                //使用外部事件启动转换(SWSTART) !!!必须使用一个事件来触发
        ADC1->CR2     &= ~(BIT_11);             //ALIGN:数据对齐（0，右对齐）
        ADC1->CR2     |= BIT_23;                //启用温度传感器和V_REFINT

        ADC1->SQR1    &= (uint32_t)0xFF0FFFFF;  //ADC_SQR1__L[23:20]__规则组转换的总数
        ADC1->SQR1    |= (uint32_t)0x00000000;  //Regular channel sequence length

        //ADC1->SMPR2   &= (uint32_t)0xFFFFFFF0;//设置通道__1__的采样时间
        //ADC1->SMPR2   |= (uint32_t)0xFFFFFFF7;//通道1（SMP0[2:0]__239.5 cycles）
        ADC1->SMPR1   &= (uint32_t)0xFFE3FFFF;  //设置通道__16__的采样时间
        ADC1->SMPR1   |= (uint32_t)0x001C0000;  //通道1（SMP16[20:18]__239.5 cycles）

        ADC1->CR2     |= BIT_00;                //开启AD转换器
        ADC1->CR2     |= BIT_03;                //初始化校准寄存器
        //ADC1->CR2_RSTCAL[3]该位由软件设置并由硬件清除。 在校准寄存器被初始化后该位将被清除
        while (ADC1->CR2 & BIT_03);             //等待校准寄存器已初始化完成
        //ADC1->CR2_CAL[2]该位由软件设置以开始校准，并在校准结束时由硬件清除
        ADC1->CR2     |= BIT_02;                //开启AD校准
        while (ADC1->CR2 & BIT_02);            //等待校准结束
}
/*******************************************************************************
  函数名称: uint16_t get_adc1_16_value(uint8_t channel)
  输入参数: channel:通道值（0~16）
  输出参数: 返回值:转换结果
  函数功能: 获得ADC1__通道16__的值
*******************************************************************************/
uint16_t get_adc1_16_value(uint8_t channel)
{
        ADC1->CR2  |= BIT_00;           //再次开启AD转换器
        ADC1->SQR3 &= 0XFFFFFFE0;       //ADC1_SQR3__SQ1[4:0]
        ADC1->SQR3 |= channel;          //ADC1_通道__16__选择第（1_序列）
        ADC1->CR2  |= BIT_22;           //启动规则转换通道
        while (!(ADC1->SR & BIT_01));   //等待转换结束
        return (ADC1->DR);              //返回adc1的值
}
/*******************************************************************************
  函数名称: uint16_t get_adc1_16_average(uint8_t channel, uint8_t number)
  输入参数: channel: 通道编号（0~16）
  输入参数: number:  读取温度的次数
  输出参数: 返回（number）次温度的平均值
  函数功能: 获取通道__16__的温度转换值， 取number次, 然后平均
*******************************************************************************/
uint16_t get_adc1_16_average(uint8_t channel, uint8_t number)
{
        uint8_t  i;
        uint16_t tmp = 0;
        for (i = 0; i < number; i++) {
                tmp += get_adc1_16_value(channel);
                HAL_Delay(5);
        }
        return (tmp / number);
}
/*******************************************************************************
  函数名称: void get_temperature(void)
  输入参数: 无
  输入参数: 无
  输出参数: 返回值:温度值(单位:℃.)
  函数功能: 得到STM32F103内部温度数据
  读取ADC1通道__16__, 取10次平均温度值（ADC通道16是内部温度传感器专用通道）
*******************************************************************************/
void get_temperature(void)
{
        uint16_t  adcx;
        adcx = get_adc1_16_average(16, 10);
        printf("Temperature: %f\n", (1.43 - adcx * 3.3 / 4096) / 0.0043 + 25);
}
/* example
adc1_16_conf();
uint16_t adcx;
adcx = get_adc1_16_value(16);
delay_ms(500);
printf("adcx: %d\n", adcx);
printf("Temperature: %f\n", (((1.43 - (adcx * 3.3 / 4096)) / 0.0043) + 25));
*/
