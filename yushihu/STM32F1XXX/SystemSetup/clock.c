#include "clock.h"


/*******************************************************************************
        => 时钟系统
*******************************************************************************/

        // https://www.cnblogs.com/-colin/p/9880421.html
        
        
// 【1】  外部晶体/陶瓷谐振器(HSE晶体)模式
// ____________________________________________________
//      // 这种模式用得比较常见，HSE晶体可以为系统提供较为精确
        // 的时钟源。 在时钟控制寄存器RCC_CR中的HSERDY位用来指
        // 示高速外部振荡器是否稳定。 在启动时，直到这一位被硬件
        // 置’1’，时钟才被释放出来。 HSE晶体可以通过设置时钟控制
        // 寄存器里RCC_CR中的HSEON位被启动和关闭。
        //
        // 该时钟源是由外部无源晶体与MCU内部时钟驱动电路共同配合
        // 形成，有一定的启动时间，精度较高。 为了减少时钟输出的失
        // 真和缩短启动稳定时间，晶体/陶瓷谐振器和负载电容必须尽
        // 可能地靠近振荡器引脚。 负载电容值必须根据所选择的晶体来
        // 具体调整。 手册里明确地写明了这句，很多时候似乎被无视了。
        // 关于这点，ST官方有专门出了个应用笔记，编号为 AN2867
        //
        // 整体上讲， 陶瓷晶体和石英晶体的主要区别就在于精度和温
        // 度稳定性上。 石英晶体比陶瓷晶体精度要高，温度稳定性要好。
        
        
        
// 【2】  外部时钟源(HSE旁路)模式
// ____________________________________________________
        // 该模式下必须提供外部时钟。 用户通过设置时钟控制寄存
        // 器中的HSEBYP和HSEON位来选择这一模式。 外部时钟信号
        // (50%占空比的方波、正弦波或三角波)必须连到SOC_IN引脚，
        // 此时OSC_OUT引脚对外呈高阻态。
        //
        // 所谓HSE旁路模式，是指无需上面提到的使用外部晶体时
        // 所需的芯片内部时钟驱动组件，直接从外界导入时钟信号。
        // 犹如芯片内部的驱动组件被旁路了。
        //
        // 不过，在使用该模式时，经常有人出现配置错误，即使用
        // 跟HSE晶体模式一样的配置。这点在STM8/STM32应用中都
        // 有人发生。 所幸的是使用这个旁路模式的情形不像使用外
        // 部晶体模式那么多，不然可能更多人在这里遇到麻烦。
        //
        // 我们不妨以STM3F4系列芯片为例。
        // 关于寄存器位上面已经提到了，旁路模式除了配置HSEON还得配置HSEBYP位。
        

// 在ST MCU应用开发中，常有人会用到有源晶振作为时钟源。如果用它该选择哪种工作模式呢？
// 有源晶振一般是四脚封装，电源、地线、振荡输出和一个控制端【或者悬空端】。 相比无源晶体，
// 有源晶振本身就是个完整的振荡器件，只需要供给适当的电源就能输出时钟，无须额外的振荡
// 驱动匹配电路。其时钟输出不依赖于外部器件振荡电路，相对更不容易受外部线路不稳定性的影
// 响。自然其价格往往要高于无源晶体，不过其输出电平幅度往往不能像无源晶体那样随着应用电
// 路的变化而变化。
//
// 不难看出，如果使用有源晶振作为外部时钟源的话，我们应该配置为HSE旁路模式，而不是HSE
// 晶体模式。 将有源晶振的输出脚接到MCU的OSC_IN脚



/*******************************************************************************
        => APB | AHB 外设时钟复位
*******************************************************************************/
void apb_ahb_clock_reset(void)
{
        // 外设时钟复位
        // ____________________________________________________






        #if RCC_AHBRSTR_XXX
        // AHB外设时钟复位寄存器(RCC_AHBRSTR) // 复位值 :  0x0000 0000 //
        #endif
        

        #if RCC_APB2RSTR_XXX
        // APB2 外设复位寄存器(RCC_APB2RSTR) // 复位值 :  0x0000 0000 //
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_AFIORST);     // AFIO --->Reset
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_AFIORST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPARST);     // GPIOA
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPARST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPBRST);     // GPIOB
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPBRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPCRST);     // GPIOC
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPCRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPDRST);     // GPIOD
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPDRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPERST);     // GPIOE
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPERST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPFRST);     // GPIOF
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPFRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_IOPGRST);     // GPIOG
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_IOPGRST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_ADC1RST);     // ADC1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_ADC1RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_ADC2RST);     // ADC2
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_ADC2RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_TIM1RST);     // TIM1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_TIM1RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_SPI1RST);     // SPI1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_SPI1RST);     // ^0
        RCC->APB2RSTR   |=  (RCC_APB2RSTR_SPI1RST);     // USART1
        RCC->APB2RSTR   &= ~(RCC_APB2RSTR_USART1RST);   // ^0
        #endif
        
        
        #if RCC_APB1RSTR_XXX
        // APB1 外设复位寄存器(RCC_APB1RSTR) // 复位值 :   0x0000 0000 //
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART2RST);   // USART2 --->Reset
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART2RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART3RST);   // USART3
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART3RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART4RST);   // USART4
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART4RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_USART5RST);   // USART5
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_USART5RST);   // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_I2C1RST);     // I2C1
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_I2C1RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_I2C2RST);     // I2C2
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_I2C2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_SPI2RST);     // SPI2
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_SPI2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_SPI3RST);     // SPI3
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_SPI3RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM2RST);     // TIM2
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM3RST);     // TIM3
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM3RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM4RST);     // TIM4
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM4RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM5RST);     // TIM5
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM2RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM6RST);     // TIM6
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM6RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_TIM7RST);     // TIM7
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_TIM7RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_CAN1RST);     // CAN1
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_CAN1RST);     // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_DACRST);      // DAC
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_DACRST);      // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_BKPRST);      // BKP
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_BKPRST);      // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_PWRRST);      // PWR
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_PWRRST);      // ^0
        RCC->APB1RSTR   |=  (RCC_APB1RSTR_WWDGRST);     // WWDG
        RCC->APB1RSTR   &= ~(RCC_APB1RSTR_WWDGRST);     // ^0
        #endif   
}
/*******************************************************************************
        => APB | AHB 外设时钟使能
*******************************************************************************/
void apb_ahb_clock_enable(void)
{
        // 外设时钟使能
        // ____________________________________________________
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPAEN);       // GPIOA






        #if RCC_AHBENR_XXX
        // AHB外设时钟使能寄存器(RCC_AHBENR) // 复位值:0x0000 0014 //
        RCC->AHBENR     |=  (RCC_AHBENR_DMA1EN);        // DMA1
        RCC->AHBENR     |=  (RCC_AHBENR_DMA2EN);        // DMA2
        RCC->AHBENR     |=  (RCC_AHBENR_CRCEN);         // CRC
        #endif
        
        #if RCC_APB2ENR_XXX
        // APB2 外设时钟使能寄存器(RCC_APB2ENR) // 复位值: 0x0000 0000 //
        RCC->APB2ENR    |=  (RCC_APB2ENR_AFIOEN);       // AFIO
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPAEN);       // GPIOA
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPBEN);       // GPIOB
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPCEN);       // GPIOC
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPDEN);       // GPIOD
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPEEN);       // GPIOE
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPFEN);       // GPIOF
        RCC->APB2ENR    |=  (RCC_APB2ENR_IOPGEN);       // GPIOG
        RCC->APB2ENR    |=  (RCC_APB2ENR_ADC1EN);       // ADC1
        RCC->APB2ENR    |=  (RCC_APB2ENR_ADC2EN);       // ADC2
        RCC->APB2ENR    |=  (RCC_APB2ENR_TIM1EN);       // TIM1
        RCC->APB2ENR    |=  (RCC_APB2ENR_SPI1EN);       // SPI1
        RCC->APB2ENR    |=  (RCC_APB2ENR_USART1EN);     // USART1
        #endif
        
        #if RCC_APB1ENR_XXX
        // APB1 外设时钟使能寄存器(RCC_APB1ENR) // 复位值: 0x0000 0000 //
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART2EN);     // USART2
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART3EN);     // USART3
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART4EN);     // USART4
        RCC->APB1ENR    |=  (RCC_APB1ENR_USART5EN);     // USART5
        RCC->APB1ENR    |=  (RCC_APB1ENR_I2C1EN);       // I2C1
        RCC->APB1ENR    |=  (RCC_APB1ENR_I2C2EN);       // I2C2
        RCC->APB1ENR    |=  (RCC_APB1ENR_SPI2EN);       // SPI2
        RCC->APB1ENR    |=  (RCC_APB1ENR_SPI3EN);       // SPI3
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM2EN);       // TIM2
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM3EN);       // TIM3
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM4EN);       // TIM4
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM5EN);       // TIM5
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM6EN);       // TIM6
        RCC->APB1ENR    |=  (RCC_APB1ENR_TIM7EN);       // TIM7
        RCC->APB1ENR    |=  (RCC_APB1ENR_CAN1EN);       // CAN1
        RCC->APB1ENR    |=  (RCC_APB1ENR_CAN2EN);       // CAN2
        RCC->APB1ENR    |=  (RCC_APB1ENR_BKPEN);        // BKP
        RCC->APB1ENR    |=  (RCC_APB1ENR_PWREN);        // PWR
        RCC->APB1ENR    |=  (RCC_APB1ENR_DACEN);        // DAC
        RCC->APB1ENR    |=  (RCC_APB1ENR_WWDGEN);       // WWDG
        #endif
}
/*******************************************************************************
        => 内部高速时钟重新初始化
*******************************************************************************/
void rcc_hsi_setup(void)
{
        // HSION[0]     // 内部高速时钟使能
        RCC->CR         |= (0x00000001);

        // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
        // ^0   // MCO   [27:24]: 微控制器时钟输出
        // ^0   // OTGFSPRE [22]: 全速USB OTG预分频
        // ^0   // PLLMUX[21:18]: PLL倍频系数
        // ^0   // PLLXTPRE [17]: PREDIV1分频因子的低位
        // ^0   // PLLSRC   [16]: PLL输入时钟源
        // ^0   // ADCPR [15:14]: ADC预分频
        // ^0   // PPRE2 [13:11]: 高速APB预分频APB2
        // ^0   // PPRE1  [10:8]: 低速APB预分频APB1
        // ^0   // HPRE    [7:4]: AHB预分频
        // ^0   // SWS     [3:2]: 系统时钟切换状态 -> READONLY
        // ^0   // SW      [1:0]: 系统时钟切换
        RCC->CFGR       &= (0xF8FF0000);

        // Reset HSEON, CSSON and PLLON bits
        RCC->CR         &= (0xFEF6FFFF);

        // Reset HSEBYP bit (0: 外部 4-16MHz 晶体振荡器没有旁路)
        RCC->CR         &= (0xFFFBFFFF);

        // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
        RCC->CFGR       &= (0xFF80FFFF);

        // Disable all interrupts and clear pending bits
        RCC->CIR        =  (0x009F0000);
}
/*******************************************************************************
        => 设置系统时钟为72MHz
        => 在外部高速时钟晶体振荡器为[ 8MHz ]的情况下
*******************************************************************************/
int rcc_hse_setup(void)
{
        __IO uint32_t StartUpCounter = 0, HSEStatus = 0;


        // HSE_ON[16]   // 打开外部高速晶体振荡器
        RCC->CR         |= RCC_CR_HSEON;

        // 等待外部高速晶体振荡器稳定， 如果超时， 则退出
        do {
                HSEStatus = RCC->CR & RCC_CR_HSERDY;
                StartUpCounter++;  
        } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
        if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
                HSEStatus = (uint32_t)0x01;
        } else {
                HSEStatus = (uint32_t)0x00;
        }  


        if (HSEStatus == (uint32_t)0x01) {
                // Enable Prefetch Buffer
                FLASH->ACR |= FLASH_ACR_PRFTBE;
                // Flash 2 wait state
                FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
                FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    


                // HPRE[7:4]    // AHB预分频， HCLK 不分频
                RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

                // PPRE1[10:8]  // 低速APB预分频(APB1)， HCLK 2分频
                RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
                
                // PPRE2[13:11] // 高速APB预分频(APB2)， HCLK 不分频
                RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;


                // 配置PLL: PLLCLK = HSE * 9 = 72 MHz
                // ^0   RCC_CFGR_PLLSRC    [16]     
                // ^0   RCC_CFGR_PLLXTPRE  [17]
                // ^0   RCC_CFGR_PLLMULL   [21:18]
                RCC->CFGR &= (0xFFC0FFFF);
                RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);

                // 使能PLL
                RCC->CR |= RCC_CR_PLLON;

                // 等待PLL稳定
                while((RCC->CR & RCC_CR_PLLRDY) == 0) {
                }

                // 选择 PLL 作为系统时钟源
                // ^0           RCC_CFGR_SW[1:0]
                RCC->CFGR &= (0xFFFFFFFC);
                RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

                // Wait till PLL is used as system clock source
                // ^STATUS      SWS[3:2]: 系统时钟切换状态 : 10: PLL输出作为系统时钟
                while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) {
                }
                
                return (80);
        } else { 
                // If HSE fails to start-up, the application will have wrong clock
                // configuration. User can add here some code to deal with this error
                return (-1);
        }
}
