#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  USART_SendData(USART1, (uint8_t *)&ch);
 
  return ch;
}


//系统时钟（72MHz）
void rcc_setup(void)
{
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        RCC_ADCCLKConfig(RCC_PCLK2_Div6);       //ADC时钟（12MHz）
}

void gpio_setup(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;       //TX
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;      //RX
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;      //ADC
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void nvic_setup(void)
{
        NVIC_InitTypeDef NVIC_InitStructure;
        
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
        NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
        
}

void _usart1_setup(void)
{
        USART_InitTypeDef USART_InitStructure;
        
        USART_InitStructure.USART_BaudRate   = 115200;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits   = USART_StopBits_1;
        USART_InitStructure.USART_Parity     = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(USART1, &USART_InitStructure);
        
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        USART_Cmd(USART1, ENABLE);
        USART_ClearFlag(USART1, USART_FLAG_TC);
}

void adc1_setup(void)
{
        ADC_InitTypeDef ADC_InitStructure;
        
        ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode       = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel       = 1;
        ADC_Init(ADC1, &ADC_InitStructure);
        
        ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
        ADC_TempSensorVrefintCmd(ENABLE);       //使能内部温度传感器
        ADC_Cmd(ADC1, ENABLE);                  //使能ADC1
        
        ADC_ResetCalibration(ADC1);
        while (ADC_GetResetCalibrationStatus(ADC1));
        
        ADC_StartCalibration(ADC1);
        while (ADC_GetCalibrationStatus(ADC1));
        
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

int main(void)
{
        float ad;
        uint8_t i;
        rcc_setup();
        nvic_setup();
        gpio_setup();
        _usart1_setup();
        adc1_setup();
        while (1) {
                ad = 0;
                i  = 0;
                for (i = 0; i < 50; i++) {
                        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
                        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
                        ad = ad + ADC_GetConversionValue(ADC1);
                }
                ad = ad / 50;
                printf("hello\n");
                printf("Temperature = %f\n", ((1.43 - 3.3 / 4095 * ad) / 0.0043 + 25));
                __delay_ms(1000);
        }
}