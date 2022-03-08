void adc_init(void)
{
        //规则组： PC0__ADC3IN10__U  PC2__ADC3IN12__V  PC3__ADCIN13__W  PA0__ADC3IN0_TEMP
        //注入组： PF8__ADC3IN6__ia  PF7__ADC3IN5__ib  PF9__ADCIN7__VBUS PF6__ADC3IN4__iTotal
        RCC->AHB1ENR    |=  (0x01);             //使能GPIOA时钟
        RCC->AHB1ENR    |=  (0x01 << 2);        //使能GPIOC时钟
        RCC->AHB1ENR    |=  (0x01 << 5);        //使能GPIOF时钟
        //GPIOA
        GPIOA->MODER    |=  (0x03);             //PA0配置为模拟功能
        GPIOA->OTYPER   &= ~(0x01);             //清零（推挽）
        GPIOA->OSPEEDR  |=  (0x03);             //100MHz
        GPIOA->PUPDR    &= ~(0x03);             //无上下拉
        //GPIOC(  0   2   0  )
        GPIOC->MODER    |=  (0x03       | 0x03 << 4  | 0x03 << 6);
        GPIOC->OTYPER   &= ~(0x01       | 0x01 << 2  | 0x01 << 3);
        GPIOC->OSPEEDR  |=  (0x03       | 0x03 << 4  | 0x03 << 6);
        GPIOC->PUPDR    &= ~(0x03       | 0x03 << 4  | 0x03 << 6);
        //GPIOF(  6   7   8  9  )
        GPIOF->MODER    |=  (0x03 << 12 | 0x03 << 14 | 0x03 << 16 | 0x03 << 18);
        GPIOF->OTYPER   &= ~(0x01 << 6  | 0x01 << 7  | 0x01 << 8  | 0x01 << 9 );
        GPIOF->OSPEEDR  |=  (0x03 << 12 | 0x03 << 14 | 0x03 << 16 | 0x03 << 18);
        GPIOF->PUPDR    &= ~(0x03 << 12 | 0x03 << 14 | 0x03 << 16 | 0x03 << 18);
        RCC->APB2ENR    |=  (0x01 << 10);       //使能ADC3时钟
        RCC->APB2RSTR   |=  (0x01 << 10);       //复位ADC3寄存器
        RCC->APB2RSTR   &= ~(0x01 << 10);       //结束复位ADC3寄存器
        ADC3->CR1       &= ~(0x01 << 26);       //ADC3溢出中断关闭（VIN > VREF检测电压过高）
        ADC3->CR1       &= ~(0x03 << 24);       //ADC3分辨率为（12bit）
        ADC3->CR1       &= ~(0x03 << 22);       //规则组和注入组不需要模拟看门狗
        ADC3->CR1       &= ~(0x01 << 12);       //不使用注入组不连续采样模式
        ADC3->CR1       &= ~(0x01 << 11);       //不使用规则组不连续采样模式
        ADC3->CR1       &= ~(0x01 << 10);       //规则组结束后，注入组不启动，而是靠外部触发启动
        ADC3->CR1       |=  (0x01 << 8);        //使能扫描模式
        ADC3->CR1       |=  (0x01 << 7);        //注入组转换完成中断使能
        ADC3->CR1       |=  (0x01 << 5);        //规则组转换完成中断使能
        ADC3->CR2       &= ~(0x03 << 28);       //规则组不使用外部触发
        ADC3->CR2       |=  (0x01 << 20);       //注入组上升沿触发
        ADC3->CR2       &= ~(0x0F << 16);       //触发信号采用TIM1CH4
        ADC3->CR2       &= ~(0x01 << 11);       //数据右对齐（采集更高效）
        ADC3->CR2       &= ~(0x01 << 10);       //每一个通道转换完成后都进入中断
        ADC3->CR2       |=  (0x01 << 9);        //DMA连续传输模式
        ADC3->CR2       |=  (0x01 << 8);        //DMA使能
        ADC3->CR2       |=  (0x01 << 1);        //ADC3连续转换模式
        //0,4,5,6,7,10,12,13采样事件设置15Cycle，以此转换为（15+12=27）个ADCCLK周期
        ADC3->SMPR1     |=  (0x01);             //CH10-U
        ADC3->SMPR1     |=  (0x01 << 6);        //CH12-V
        ADC3->SMPR1     |=  (0x01 << 9);        //CH13-W
        ADC3->SMPR2     |=  (0x01);             //CH0-TEMP
        ADC3->SMPR2     |=  (0x01 << 12);       //CH4-iTotal
        ADC3->SMPR2     |=  (0x01 << 15);       //CH5-ib
        ADC3->SMPR2     |=  (0x01 << 18);       //CH6-ia
        ADC3->SMPR2     |=  (0x01 << 21);       //CH7-VBUS
        ADC3->SQR1      |=  (0x04 << 20);       //规则通道一次转换扫描4个通道
        ADC3->SQR3      |=  (  10      );       //CH10-U
        ADC3->SQR3      |=  (  12 << 5 );       //CH12-V
        ADC3->SQR3      |=  (  13 << 10);       //CH13-W
        ADC3->SQR3      &= ~(0x1F << 15);       //CH10-TEMP
        ADC3->JSQR      |=  (0x03 << 20);       //注入通道一次转换扫描4个通道
        ADC3->JSQR      |=  (   6      );       //CH6-ia
        ADC3->JSQR      |=  (   5 << 5 );       //CH5-ib
        ADC3->JSQR      |=  (   7 << 10);       //CH7-VBUS
        ADC3->JSQR      |=  (   4 << 15);       //CH4-iTotal
        ADC->CCR        &= ~(0x01 << 23);       //内部温度传感器关闭
        ADC->CCR        &= ~(0x01 << 22);       //VBAT传感器关闭
        ADC->CCR        |=  (0x01 << 16);       //时钟4分频，84/4=21Mhz
                                                //1/21M*27=1.2852us一次采样
        
        NVIC_SetPriortity(ADC_IRQn, prio);      //设置ADC3的中断优先级    
        NVIC_EnableIRQ(ADC_IRQn);               //使能ADC中断
        
        ADC3->SR        &= ~(0x01 << 2);        //清注入组中断
        ADC3->SR        &= ~(0x01 << 1);        //清规则组中断
        ADC3->CR2       |=  (0x01);             //开启ADC3
        ADC3->CR2       |=  (0x01 << 30);       //开启规则通道转换
        ADC3->CR2       |=  (0x01 << 22);       //开启注入通道转换 
}

void ADC_IRQHandler(void)
{
        if (ADC3->SR & 0x01 << 2) {             //注入组完成
                ADC3->SR &= ~(0x01 << 2);       //清中断
                printf("J= %d  %d  %d  %d\n", 
                        ADC3->JDR1, 
                        ADC3->JDR2, 
                        ADC3->JDR3, 
                        ADC3->JDR4  );
        }
}
