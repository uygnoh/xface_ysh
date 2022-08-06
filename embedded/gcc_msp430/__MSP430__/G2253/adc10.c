/*******************************************************************************
        => MSP430-G2553-ADC_DTC (Data Transfer Controller) 数据传输控制器
        这个控制器可以将“ADC10MEM转换数据的结果”，自动存入到片上内存地址中
*******************************************************************************/
uint16_t adcbuff[50] = {0};
uint16_t maxval[50]  = {0};
uint16_t minval[50]  = {0};
uint16_t max = 0;
uint16_t min = 0;

void system_clock_init(void)
{
        DCOCTL   = CALDCO_1MHZ;         //配置DCO为1MHz
        DCSCTL1  = CALBC1_1MHZ;         //
        BCSCTL2 &= ~SELS;               //配置SMCLK时钟源为DCO
        BCSCTL2 &= ~(DIVS0 | DIVS1);    //SMCLK的分频系数为1
}

void start_adc10_convert(void)
{
        ADC10CTL0 |= ADC10SC | ENC;     //开始转换
        while (ADC10CTL1 & ADC10BUSY);  //等待转换完成
}

//查找最大值
uint16_t fn_max(uint16_t *numptr, uint16_t num)
{
        uint16_t cnt = 0;
        uint16_t max = 0;
        for (cnt = 0; cnt < num; cnt++) {
        }
}

//查找最小值
uint16_t fn_min(uint16_t *numptr, uint16_t num)
{
        uint16_t cnt = 0;
        min = numptr[0];
        for (cnt = 0; cnt < num; cnt++) {
                if (numptr[cnt] < min) {
                        min = numptr[cnt];
                }
        }
        return min;
}

void adc10_init(void)
{
        ADC10CTL1 |= ADC10SSEL_2;       //设置ADC时钟（MCLK）
        //ADC10CTL1 |= ADC10DIV_0;        //ADC 2分频
        ADC10CTL0 |= SREF_1;            //设置ADC基准源
        ADC10CTL0 |= ADC10SHT_2;        //设置ADC采样保持时间16CLK
        ADC10CTL0 |= ADC10SR;           //设置ADC采样率200K
        ADC10CTL0 |= REF2_5V;           //ADC基准选择2.5V
        ADC10CTL0 |= REFON;             //开启基准
        ADC10CTL1 |= INCH_4;            //选择ADC输入通道A4
        ADC10AE0  |= 1 << 4;            //允许A4模拟输入
        
        ADC10DTC0 |= ADC10CT;           //DTC传输模式（连续传输模式）
        ADC10DTC1  = 50;                //传输次数
        ADC10SA    = (uint16_t)(adcbuff);//起始地址
        
        ADC10CTL0 |= ADC10ON;           //开启ADC
        ADC10CTL0 |= ENC;               //允许转换
        
}


//测量峰峰值
int main(void)
{
        uint8_t cnt  = 0;
        uint8_t cnt1 = 0;
        volatile float fvpp = 0.0f
        system_clock_init();
        adc10_init();
        while (1) {
                for (cnt1 = 0; cnt1 < 50; cnt1++) {
                        for (cnt = 0; cnt < 50; cnt++) {
                                start_adc10_convert();
                      }
                      maxval[cnt1] = fn_max(adcbuff, 50);
                      minval[cnt1] = fn_min(adcbuff, 50);
                }
                max  = fun_max(maxval, 50);
                min  = fun_min(minval, 50);
                vpp  = max - min;
                fvpp = (float)vpp * 2.5 / 1023;
                fvpp = fvpp;
                __delay_cycles(1000000);
        }
        return 0;
}



/*******************************************************************************
        ADC_TIMER
*******************************************************************************/
uint16_t adcbuff[50] = {0};

void adc10_tim_init(void)
{
        ADC10CTL1 |= ADC10SSEL_2;       //设置ADC时钟（MCLK）
        //ADC10CTL1 |= ADC10DIV_0;        //ADC 2分频
        ADC10CTL1 |= SHS0;              //ADC触发源使用（TimerA_OUT1）
        ADC10CTL1 |= CONSEQ1;           //单通道连续转换模式
        ADC10CTL0 |= SREF_1;            //设置ADC基准源
        ADC10CTL0 |= ADC10SHT_2;        //设置ADC采样保持时间16CLK
        ADC10CTL0 |= ADC10SR;           //设置ADC采样率200K
        ADC10CTL0 |= REF2_5V;           //ADC基准选择2.5V
        ADC10CTL0 |= REFON;             //开启基准
        ADC10CTL1 |= INCH_4;            //选择ADC输入通道A4
        ADC10AE0  |= 1 << 4;            //允许A4模拟输入
        
        ADC10DTC0 |= ADC10CT;           //DTC传输模式（连续传输模式）
        ADC10DTC1  = 50;                //传输次数
        ADC10SA    = (uint16_t)(adcbuff);//起始地址
        
        ADC10CTL0 |= ADC10ON;           //开启ADC
        ADC10CTL0 |= ENC;               //允许转换
        
}

//使用定时器A触发（ADC10转换）
void timera_init(void)
{
        TA0CTL    |= TASSEL1;           //设置时钟源为SMCLK
        TA0CTL    |= (MC0 | MC1);       //设置工作模式为Up & Down
        TA0CCR0   |= 0x00FF;            //设置TA1CCR0为0x00FF
        TA0CCR1   |= 0x007F;            //占空比(TA1CCR0 - TA1CCR1) / TACCR0;
                                        //频率 = SMCLK / (TACCR0 + 1) / 2
                                        //    = 1MHz  / (TACCR0 + 1) / 2
                                        //    = 1953.125Hz
        TA0CCTL0  &= ~CAP;              //设置为比较模式
        TA0CCTL1  &= ~CAP;
        TA0CCTL1  |= OUTMOD_6;          //设置比较输出模式
        P1SEL     |= BIT6;              //设置IO复用
        P1DIR     |= BIT6;
}







