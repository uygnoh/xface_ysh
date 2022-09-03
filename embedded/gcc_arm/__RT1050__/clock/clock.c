// 正点原子RT1050（125页）
// 设置RT1052系统时钟
// PLL-ARM 的倍频系数： 范围（54 ~ 108）
// 内核主频 = (24 * pllarm/2) / (ARM_PODF + 1) / (AHB_PODF + 1)
// 当ARM_PODF = 1， AHB_PODF = 0， pllarm = 100
// ARM_CORE_FREQ = 600MHz
        ARM_PODF 为内核分频器,   一般设置为 1,   即 2 分频。
        AHB_PODF 为 AHB 分频器, 一般设置为 0,   即不分频
void rt1052_clock_setup(uint8_t pllarm)
{
        uint32_t tmpreg = 0;
        
        // 1
        // 段1,用于禁止看门狗(WDOG1 和 WDOG2),因为 boot rom 有可能开启了看门狗,如果
        // 我们不禁止,将会导致我们自己的程序也受看门狗影响,从而不能正常工作。所以必须关闭这
        // 两个看门狗。Boot rom 是指固化在 RT1052 内部的 96K Rom,用于控制 RT1052 的启动过程,
        // 用户无法修改和使用。
        // ____________________________________________________
        WDOG1->WCR      &= ~(1<<2);     // 关闭看门狗 1
        WDOG2->WCR      &= ~(1<<2);     // 关闭看门狗 2
        RTWDOG->CNT     = 0xD928C520;   // 写入键值 0XD928C520,解锁一次写入限制
        RTWDOG->TOVAL   = 0xFFFF;
                                        // 禁止 RT 看门狗,允许更新
        RTWDOG->CS      = ((RTWDOG->CS) & ~(1<<7)) | (1<<5);
        
        
        // 2
        // ____________________________________________________
        // 初始化时钟阶段先设置内核时钟源为低速的 24M 时钟,
        // 后面会重新将 PLL1 设置为 1200MHz, 主频设置为 600MHz
        CCM->CBCMR      &= ~(3 << 12);          // 清除 PERIPH_CLK2 原来的设置
        CCM->CBCMR      |=  (1 << 12);          // 设置 PERIPH_CLK2 时钟来自 24M 晶振
                                                // (此时 PLL1 还没配置起来)
        CCM->CBCDR      |=  (1 << 25);          // 设置 PERIPH_CLK 时钟来自 PERIPH_CLK2,即 24M 
        
        
        // 3
        // ____________________________________________________
        // 设置 VDD_SOC 电压为 1.25V,AHB 时钟才可以到 600MHz
        DCDC->REG3      &= ~(0x1F << 0);                // 清除 TRG 原来的设置
        DCDC->REG3      |=  (0x12 << 0);                // 设置 TRG = 18,VDD_SOC=0.8+18*TRG=1.25V
        while ((DCDC->REG0 & ((u32)1 << 31)) == 0 );    //等待 DCDC 设置完成
        
        
        // 4
        // ____________________________________________________
        // 设置 PLL1(PLL_ARM)   PLL2(PLL_SYS)   PLL3(PLL_USB1)
        // 使能 PLL1(PLL_ARM),设置倍频数,范围 54~108,Fpll1=24*pllarm/2 Mhz
        CCM_ANALOG->PLL_ARM     = (1 << 13) | (pllarm & 0x7F);
        // 等待频率锁定
        while ((CCM_ANALOG->PLL_ARM & ((u32)1 << 31)) == 0); 
        
        // 使能 PLL2(PLL_SYS),选择倍频系数 22,Fpll2=24*22=528Mhz
        // 等待频率锁定
        CCM_ANALOG->PLL_SYS     = (1 << 13) | (1 << 0);
        while ((CCM_ANALOG->PLL_SYS & ((u32)1 << 31)) == 0);
        
        // 使能 PLL3(PLL_USB1),PLL3 上电,使能 USB 时钟,倍频系数 20,Fpll3=24*20=480Mhz
        CCM_ANALOG->PLL_USB1    = (3 << 12) | (1 << 6) | (0 << 0);
        // 等待频率锁定
        while ((CCM_ANALOG->PLL_USB1 & ((u32)1 << 31)) == 0);


        // 5
        // ____________________________________________________
        // 设置 AHB_CLK_ROOT(内核时钟)/IPG_CLK_ROOT/PERCLK_CLK_ROOT 时钟分频
        CCM->CACRR      = 1<<0;
        // 设置 ARM_PDOF:2 分频 PLL1_OUT=1200M/2=600Mhz
        CCM->CBCDR&     =~ (7<<10); //清除 AHB_PDOF 原来的设置
        CCM->CBCDR      |= 0<<10;
        // 设置 AHB_PDOF:1 分频,AHB_CLK_ROOT=600Mhz
        CCM->CBCDR      &= ~(3<<8); //清除 IPG_PDOF 原来的设置
        CCM->CBCDR      |= 3<<8;
        // 设置 IPG_PDOF:4 分频, AHB_CLK:IPG_CLK=4:1
        // 设置 PERCLK_CLK_SEL 为 0,IPG_CLK_ROOT 为 PERCLK_CLK_ROOT 的时钟源
        CCM->CSCMR1     &= ~(1<<6);
        CCM->CSCMR1     &= ~(0X3F<<0);
        // 清除 PERCLK_PODF 原来的设置.
        // 设置 PERCLK_CLK 2 分频,PERCLK_CLK_ROOT=IPG_CLK_ROOT/2=150/2=75Mhz
        CCM->CSCMR1     |= 1<<0;
        
        
        // 6
        // ____________________________________________________
        // 重新设置内核时钟源为 PLL1 经过 ARM_PODF 和 AHB_PODF 分频后的时钟
        CCM->CBCMR      &= ~(3<<18);
        // 清除 PRE_PERIPH_CLK_SEL 原来的设置
        CCM->CBCMR      |= 3<<18;
        // 设置 PRE_PERIPH_CLK_SEL=PLL1_OUT=600Mhz
        CCM->CBCDR      &= ~(1<<25);
        // 设置 PERIPH_CLK=PRE_PERIPH_CLK_SEL=600M
        
        
        
        // 7
        // ____________________________________________________
        // 设置 PLL2 的 PFD0/PFD1/PFD2/PFD3
        tempreg         = CCM_ANALOG->PFD_528;
        tempreg         &= ~(0x3F3F3F3F);       //清除原来的设置
        
        tempreg         |= 32<<24;              // PLL2_PFD3=528*18 / 32 =297Mhz
        tempreg         |= 24<<16;              // PLL2_PFD2=528*18 / 24 =396Mhz
        tempreg         |= 16<<8;               // PLL2_PFD1=528*18 / 16 =594Mhz
        tempreg         |= 27<<0;               // PLL2_PFD0=528*18 / 27 =352Mhz
        CCM_ANALOG->PFD_528 = tempreg;          // 设置 PLL2_PFD0~3
        
        
        
        // 8
        // ____________________________________________________
        // 设置 PLL3 的 PFD0/PFD1/PFD2/PFD3
        tempreg         = CCM_ANALOG->PFD_480;
        tempreg         &= ~(0x3F3F3F3F);       // 清除原来的设置
        tempreg         |= 19<<24;              // PLL3_PFD3=480*18 / 19 =454.74Mhz
        tempreg         |= 17<<16;              // PLL3_PFD2=480*18 / 17 =508.24Mhz
        tempreg         |= 13<<8;               // PLL3_PFD1=480*18 / 13 =664.62Mhz
        tempreg         |= 12<<0;               // PLL3_PFD0=480*18 / 12 =720Mhz
        CCM_ANALOG->PFD_480 = tempreg;          // 设置 PLL3_PFD0~3
        
        
        // 9
        // ____________________________________________________
        //关闭暂时没用到的 PLL,后续如需要用,请添加相应的初始化代码
        CCM_ANALOG->PLL_AUDIO = 1<<12;          //PLL4(AUDIO_PLL) POWER DOWN
        CCM_ANALOG->PLL_VIDEO = 1<<12;          //PLL5(VIDEO_PLL) POWER DOWN
        CCM_ANALOG->PLL_ENET  = 1<<12;          //PLL6(ENET_PLL)  POWER DOWN
        CCM_ANALOG->PLL_USB2  = 0<<12;          //PLL7(USB2_PLL)  POWER DOWN



        // 开启 IOMUXC 时钟,因为基本上只要用到 IO 的地方就得设置该时钟,
        // 所以放时钟初始化函数里面,默认开启,避免重复设置
        CCM->CCGR4|=3<<2;
        // 开启 IOMUXC 时钟,配置 IOMUXC 相关寄存器时,需开启
        SCB_EnableDCache();
        // 使能 D Cache
        SCB_EnableICache();
        // 使能 I Cache
}
