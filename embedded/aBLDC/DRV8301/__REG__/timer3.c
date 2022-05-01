void hall_init(void)
{
        //PC6   HALLA
        //PC7   HALLB
        //PC8   HALLC
        RCC->AHB1ENR    |=  (0x01 << 2); //使能GPIOC端口时钟
        GPIOC->MODER    &= ~(0x03 << 12 | 0x03 << 14 | 0x03 << 16);     //模式清零
        GPIOC->MODER    |=  (0x02 << 12 | 0x02 << 14 | 0x02 << 16);     //配置为复用功能
        GPIOC->AFR[0]   &=  (0x00FFFFFF);       //清零
        GPIOC->AFR[0]   |=  (0x22000000);       //配置PC7、PC6为TIM3CH1，TIM3CH2
        GPIOC->AFR[1]   &=  (0xFFFFFFF0);       //清零
        GPIOC->AFR[1]   |=  (0xFFFFFFF2);       //配置PC8为TIM3CH3
        GPIOC->OTYPER   &= ~(0x01 << 6  | 0x01 << 7  | 0x01 << 8);      //清零（推挽）
        GPIOC->OSPEEDR  &= ~(0x03 << 12 | 0x03 << 14 | 0x03 << 16);     //速度清零
        GPIOC->OSPEEDR  |=  (0x03 << 12 | 0x03 << 14 | 0x03 << 16);     //100MHz
        GPIOC->PUPDR    &= ~(0x03 << 12 | 0x03 << 14 | 0x03 << 16);     //无上下拉
        RCC->APB1ENR    |=  (0x01 << 1);        //使能TIM3时钟
        RCC->APB1RSTR   |=  (0x01 << 1);        //清零TIM3全部寄存器
        RCC->APB1RSTR   &= ~(0x01 << 1);        //结束清零
        TIM3->CR1       &= ~(0x03 << 8);        //采样滤波器使用CK_INT不分频
        TIM3->CR1       |=  (0x01 << 7);        //ARR使能预装载
        TIM3->CR1       &= ~(0x03 << 5);        //递增递或减模式
        TIM3->CR1       &= ~(0x01 << 4);        //计数器递增计数
        TIM3->CR1       &= ~(0x01 << 3);        //连续计数模式
        TIM3->CR1       &= ~(0x03 << 1);        //使能更新请求源和更新事件
        TIM3->CR2       |=  (0x01 << 7);        //CH1，CH2， CH3使用异或组合
        TIM3->SMCR      |=  (0x05 << 4);        //选择TI1FP1作为输入（CH1/CH2/CH3的异或信号）
        TIM3->SMCR      |=  (0x04);             //从模式选择RESET模式
                                                //当TRGI触发信号发生将发出更新事件并重置计数器
                                                //TRGI由TI1FP1生成
        TIM3->DIER      |=  (0x01 << 1);        //使能通道1的捕获中断
        TIM3->CCMR1     |=  (0x0F << 4);        //异或信号的采样率为FDTS/32, N=8
        TIM3->CCMR1     &= ~(0x03 << 2);        //1个事件算一个捕获（输入捕获 1 预分频器）
        TIM3->CCMR1     |=  (0x01);             //CH1设置为输入模式
        TIM3->CCER      |=  (0x01 << 1 | 0x01 << 3); //TIFP1检测双边沿有效
        TIM3->CCER      |=  (0x01);             //使能通道1的捕获并将捕获的值放到CCR1寄存器中
        TIM3->PSC        =  (0);                //实际上分频是1， 就是APB1*2=84MHz
        TIM3->ARR        =  (0xFFFFFFFF);       //配置为最大值，单次计时为12ns

        //设置TIM3的中断优先别
        TIM3->EGR       |=  (0x01);             //手动给一个更新事件
        
        //清零更新事件、通道1捕获事件、通道1重复捕获事件
        TIM3->SR        &= ~(0x01 | 0x01 << 1 | 0x01 << 9);
        NVIC_EnableIRQ(TIM3_IRQn);              //使能定时器3中断
        TIM3->CNT        =  0;                  //计数器清零
        TIM3->CR1       |=  0x01;               //使能定时器
}


//定时器3中断，这个中断检测霍尔信号
void TIM3_IRQHandler(void)
{
        if (TIM3->SR & 0x01 << 1) {     //如果是捕获中断
                TIM3->SR &= ~(0x01 | 0x01 << 1 | 0x01 << 9);
                printf("CCR1 = %u HALLA = %d HALLB = %d HALLC = %d\n",
                        TIM3->CCR1,
                        !!(GPIOC->IDR & 0x01 << 6),
                        !!(GPIOC->IDR & 0x01 << 7),
                        !!(GPIOC->IDR & 0x01 << 8));
        }
}
