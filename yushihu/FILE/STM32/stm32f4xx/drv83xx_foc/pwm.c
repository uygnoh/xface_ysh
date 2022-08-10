void pwm_setup(void)
{
        //PA8-CH  PA9-BH  PA10-AH
        RCC->AHB1ENR    |=  (0x01);                                     //使能GPIOA时钟
        GPIOA->MODER    &= ~(0x03 << 16 | 0x03 << 18 | 0x03 << 20);     //清零
        GPIOA->MODER    |=  (0x02 << 16 | 0x02 << 18 | 0x02 << 20);     //配置为复用功能
        GPIOA->AFR[1]   &=  (0xFFFFF000);                               //清零
        GPIOA->AFR[1]   |=  (0x00000111);                               //配置为TIM1（CH1，CH2，CH3）
        GPIOA->OTYPER   &= ~(0x01 << 8  | 0x01 << 9  | 0x01 << 10);     //清零（推挽模式）
        GPIOA->OSPEEDR  &= ~(0x03 << 16 | 0x03 << 18 | 0x03 << 20);     //清零
        GPIOA->OSPEEDR  |=  (0x03 << 16 | 0x03 << 18 | 0x03 << 20);     //速度（100MHz）
        GPIOA->PUPDR    &= ~(0x03 << 16 | 0x03 << 18 | 0x03 << 20);     //清零
        GPIOA->PUPDR    |=  (0x02 << 16 | 0x02 << 18 | 0x02 << 20);     //配置为下拉模式
        //PB13-CL  PB14-BL  PB15-AL
        RCC->AHB1ENR    |=  (0x01 << 1);                                //使能GPIOB时钟
        GPIOB->MODER    &= ~(0x03 << 26 | 0x03 << 28 | 0x03 << 30);     //清零
        GPIOB->MODER    |=  (0x02 << 26 | 0x02 << 28 | 0x02 << 30);     //配置为复用功能
        GPIOB->AFR[1]   &=  (0x000FFFFF);                               //清零
        GPIOB->AFR[1]   |=  (0x11100000);                               //配置为TIM1（CH1N，CH2N，CH3N）
        GPIOA->OTYPER   &= ~(0x01 << 13 | 0x01 << 14 | 0x01 << 15);     //清零（推挽模式）
        GPIOA->OSPEEDR  &= ~(0x03 << 26 | 0x03 << 28 | 0x03 << 30);     //清零
        GPIOA->OSPEEDR  |=  (0x03 << 26 | 0x03 << 28 | 0x03 << 30);     //速度（100MHz）
        GPIOA->PUPDR    &= ~(0x03 << 26 | 0x03 << 28 | 0x03 << 30);     //清零
        GPIOA->PUPDR    |=  (0x02 << 26 | 0x02 << 28 | 0x02 << 30);     //配置为下拉模式
        
        
        #if 1   //TIM4_CH4 调试使用，正常使用的时候置（0）
        RCC->AHB1ENR    |=  (0x01);
        GPIOA->MODER    &= ~(0x03 << 22);
        GPIOA->MODER    |=  (0x02 << 22);
        GPIOA->AFR[1]   &= ~(0xFFFF0FFF);
        GPIOA->AFR[1]   |=  (0x00001000);
        GPIOA->OTYPER   &= ~(0x01 << 11);
        GPIOA->OSPEEDR  |=  (0x03 << 22);
        GPIOA->PUPDR    &= ~(0x03 << 22);
        #endif
        
        
        RCC->APB2ENR    |=  (0x01);             //使能定时器1时钟（168MHz）
        RCC->APB2RSTR   |=  (0x01);             //复位TIM1全部寄存器
        RCC->APB2RSTR   &= ~(0x01);             //结束复位TIM1寄存器
        
        
        //PWM三相设置
        TIM1->CR1       &= ~(0x03 << 8);        //死区滤波器与数字滤波器为CK_INT的频率（不分频）
                                                //dead-time generators and digitla filters
        TIM1->CR1       &= ~(0x01 << 7);        //不使用ARR预装载，修改的值立即生效
        TIM1_>CR1       |=  (0x01 << 5);        //采用中断对齐模式1，其实采用1，2，3模式都可以
                                                //代表向上或向下计数时候CNT与CCR寄存器产生中断的时机
        TIM1->CR1       &= ~(0x01 << 3);        //不采用单脉冲模式
        TIM1->CR1       &= ~(0x03 << 1);        //更新事件请求源选择
        TIM1->CR2       &= ~(0x01 << 8);        //当MOE清零并经过死区时间之后，OC1 输出低电平
        TIM1->CR2       &= ~(0x01 << 9);        //当MOE清零并经过死区时间之后，OC1N输出低电平
        TIM1->CR2       &= ~(0x01 << 10;        //当MOE清零并经过死区时间之后，OC2 输出低电平
        TIM1->CR2       &= ~(0x01 << 11);       //当MOE清零并经过死区时间之后，OC2N输出低电平
        TIM1->CR2       &= ~(0x01 << 12);       //当MOE清零并经过死区时间之后，OC3 输出低电平
        TIM1->CR2       &= ~(0x01 << 13);       //当MOE清零并经过死区时间之后，OC3N输出低电平
        
        
        //OC2REF_______________________________________________
        TIM1->CCMR1     &= ~(0x01 << 15);       //OC2REF不受ETRF信号影响
        TIM1->CCMR1     |=  (0x07 << 12);       //OC2使用PWM2模式，OC2REF的状态是
                                                // CNT > CCR有效, CNT < CCR无效
        TIM1->CCMR1     &= ~(0x01 << 11);       //不使用CCR预装载寄存器，CCR寄存器的值立即修改生效，立即生效
        TIM1->CCMR1     &= ~(0x01 << 10);       //触发信号不会影响CCR与CNT的比较输出
        TIM1->CCMR1     &= ~(0x03 << 8 );       //CC2配置为输出
        //OC1REF_______________________________________________
        TIM1->CCMR1     &= ~(0x01 << 7 );       //OC1REF不受ETRF信号影响
        TIM1->CCMR1     |=  (0x07 << 4 );       //OC1使用PWM2模式，OC2REF的状态是
                                                // CNT > CCR有效, CNT < CCR无效
        TIM1->CCMR1     &= ~(0x01 << 3 );       //不使用CCR预装载寄存器，CCR寄存器的值立即修改生效，立即生效
        TIM1->CCMR1     &= ~(0x01 << 2 );       //触发信号不会影响CCR与CNT的比较输出
        TIM1->CCMR1     &= ~(0x03);             //CC1配置为输出
        //OC3REF_______________________________________________
        TIM1->CCMR2     &= ~(0x01 << 7 );       //OC3REF不受ETRF信号影响
        TIM1->CCMR2     |=  (0x07 << 4 );       //OC3使用PWM2模式，OC2REF的状态是
                                                // CNT > CCR有效, CNT < CCR无效
        TIM1->CCMR2     &= ~(0x01 << 3 );       //不使用CCR预装载寄存器，CCR寄存器的值立即修改生效，立即生效
        TIM1->CCMR2     &= ~(0x01 << 2 );       //触发信号不会影响CCR与CNT的比较输出
        TIM1->CCMR2     &= ~(0x03);             //CC3配置为输出
        
        
        TIM1->CCER      &= ~(0x01 << 11);       //OC3N高电平有效
        TIM1->CCER      |=  (0x01 << 10);       //OC3N使能输出
        TIM1->CCER      &= ~(0x01 << 9 );       //OC3高电平有效
        TIM1->CCER      |=  (0x01 << 8 );       //OC3使能输出
        TIM1->CCER      &= ~(0x01 << 7 );       //OC2N高电平有效
        TIM1->CCER      |=  (0x01 << 6 );       //OC2N使能输出
        TIM1->CCER      &= ~(0x01 << 5 );       //OC2高电平有效
        TIM1->CCER      |=  (0x01 << 4 );       //OC2使能输出
        TIM1->CCER      &= ~(0x01 << 3 );       //OC1N高电平有效
        TIM1->CCER      |=  (0x01 << 2 );       //OC1N使能输出
        TIM1->CCER      &= ~(0x01 << 1 );       //OC1高电平有效
        TIM1->CCER      |=  (0x01 << 0 );       //OC1使能输出
        
        
        TIM1->PSC        = 0;           //频率为168MHz
        //PWM周期为 168/(PSC+1)*ARR= 40KHz, 因为是中心对齐模式，
        //所以一个PWM周期除以2, 所以PWM的周期为（20KHz）
        TIM1->ARR        = 4200;        //PWM占空比刚好是一半  
        TIM1->CCR1       = 2100;        //PWM占空比刚好是一半  
        TIM1->CCR2       = 2100;        //PWM占空比刚好是一半  
        TIM1->CCR3       = 2100;        //PWM占空比刚好是一半 
        
        
        //TIM1-CH4（第四通道ADC触发信号设置）
        TIM1->CR2       &= ~(0x01 << 14);       //当MOE清零并经过死区时间之后，OC4输出低电平
        TIM1->CCMR2     &= ~(0x01 << 15);       //OC4REF不受ETRF信号影响
        TIM1->CCMR2     |=  (0x06 << 12);       //OC4使用PWM1模式，OC4REF的状态是
                                                // CNT < CCR有效, CNT > CCR无效
        TIM1->CCMR2     &= ~(0x01 << 11);       //不使用预装载寄存器
        TIM1->CCMR2     &= ~(0x01 << 10);       //触发信号不会影响CCR与CNT的比较结果
        TIM1->CCMR2     &= ~(0x03 << 8 );       //CC4配置为输出
        //TIM1_CH4是ADC的触发信号
        //一整个PWM周期结束后采集以此，所以CCR4是50
        TIM1->CCR4       =  (50);             
        TIM1->CCER      &= ~(0x01 << 13);       //OC4高电平有效
        TIM1->CCER      |=  (0x01 << 12);       //OC4便能输出
        
        
        //死区设置
        TIM1->BDTR      &= ~(0x01 << 14);       //主输出MOE只能软件清零
        TIM1->BDTR      &= ~(0x01 << 12);       //关闭刹车功能
        TIM1->BDTR      |=  (0x01 << 11);       //使能OSSR
        TIM1->BDTR      |=  (0x01 << 10);       //使能OSSI
        //死区时间设置为（DTG[7:5]=0xx => DT=DTG[7:0]x t_dtg ,其中 t_dtg =t_DTS）
        //t_dtg = 1/168MHz = 5.95ns
        //(100001)BIN = 33 * 5.95 = 196.35ns
        TIM1->BDTR      |=  (0x01 << 5 | 0x01);
        TIM1->BDTR      |=  (0x01 << 8);        //锁定模式1
        TIM1->CR1       |=  (0x01);             //使能定时器1
        TIM1->BDTR      |=  (0x01 << 15);       //使能主输出MOE
}
