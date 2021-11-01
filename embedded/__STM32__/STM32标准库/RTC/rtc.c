/*******************************************************************************
  函数名称: rtc_setup()
  输入参数: 无
  输出参数: （0）返回成功， （非0）返回失败
  函数功能: RTC（实时时钟设置）
*******************************************************************************/
uint8_t rtc_setup(void)
{
        uint8_t tmp = 0;
        RCC_APB1PeriphClcokCmd(RCC_ARP1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        PWR_BackupAccessCmd(ENABLE); //使能后备区域访问
                                     //读取后备区域(BKP_DR1)的值，判断是否为（0x5A5A）
        if (BKP_ReadBackupRegister(BKP_DR1) != 0x5A5A) {
                BKP_DeInit();              //复位备份区域
                RCC_LSEConfig(RCC_LSE_ON); //设置外部低速晶振（LSE）
                while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET && (tmp < 250)) {
                        tmp++;
                        delay_ms(10);
                }
                if (tmp >= 250) return (1);     //初始化晶振失败******************
                RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //设置RTC时钟源
                RCC_RTCCLKCmd(ENABLE);           //使能RTC时钟
                RTC_WaitForLastTask();           //等待最近一次对RTC寄存器的写操作完成
                RTC_WaitForSynchro();            //等待RTC寄存器同步完成
                RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC秒中断
                RTC_WaitForLastTask();           //等待最近一次对RTC寄存器的写操作完成
                RTC_EnterConfigMode();           //进入RTC配置 ******************
                RTC_SetPrescaler(32767);         //设置RTC预分频值
                RTC_WaitForLastTask();           //等待最近一次对RTC寄存器的写操作完成
                rtc_time_setup(2015, 1, 14, 17, 42, 55); //RTC（实时时钟）设置时间
                RTC_ExitConfigMode();           //退出RTC配置 *******************
                BKP_WriteBackupRegister(BKP_DR1, 0x5A5A);
        } else {
                RTC_WaitForSynchro();            //等待RTC寄存器同步完成
                RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC秒中断
                RTC_WaitForLastTask();           //等待最近一次对RTC寄存器的写操作完成
        }
        rtc_nvic_setup();                        //RTC（实时时钟）中断配置
        RTC_Get();                               //RTC（实时时钟）更新时间
        return (0);
}
/*******************************************************************************
  函数名称: rtc_nvic_setup()
  输入参数: 无
  输出参数: 无
  函数功能: RTC（实时时钟）设置中断
*******************************************************************************/





/*******************************************************************************
  函数名称: is_leap_year()
  输入参数: 年份
  输出参数: （1）闰年， （0）非闰年
  函数功能: 判断是否是闰年函数
//______________________________________________________________//
//      _1  _2  _3  _4  _5  _6  _7  _8  _9  10  11  12          //月份
//      31  29  31  30  31  30  31  31  30  31  30  31          //闰年
//      31  28  31  30  31  30  31  31  30  31  30  31          //非闰年
//______________________________________________________________//
*******************************************************************************/
uint8_t is_leap_year(uint16_t year)
{
        if (year % 4 == 0) {
                if (year % 100 == 0) {
                        if (year % 400 == 0) {
                                return (1);
                        } else {
                                return (0);
                        }
                } else {
                        return (1);
                }
        } else {
                return (0);
        }
}
/*******************************************************************************
  函数名称: rtc_time_setup()
  输入参数: 年，月，日，时，分，秒
  输出参数: （0）返回成功， （非0）返回失败
  函数功能:  
*******************************************************************************/
//以（1970.01.01）为时间基准
//平年月份日期表
const uint8_t month_tab[2] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
uint8_t rtc_time_setup( 
                  uint16_t year,        //年
                  uint8_t  month,       //月
                  uint8_t  day,         //日
                  uint8_t  hour,        //时
                  uint8_t  minute,      //分
                  uint8_t  second)      //秒
{
        uint16_t tmp;
        uint32_t sec_cnt = 0;
        if (year < 1970 || year > 2099) {
                return (1);
        }
        for (tmp = 1970; tmp < year; tmp++) {
                if (is_leap_year(tmp)) {
                        sec_cnt += 31622400;           //闰年的秒数
                } else {
                        sec_cnt += 31536000;           //平年的秒数
                }
        }
        month -= 1;
        for (tmp = 0; tmp < month; tmp++) {
                secconut += (uint32_t)month_tab[tmp] * 86400;
                if (is_leap_year(year) && tmp == 1) {
                        sec_cnt += 86400;
                }
        }
        sec_cnt += (uint32_t)(day - 1) * 86400;
        sec_cnt += (uint32_t)hour      * 3600;
        sec_cnt += (uint32_t)minute    * 60;
        sec_cnt += second;
        RCC_APB1PeriphClcokCmd(RCC_ARP1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        PWR_BackupAccessCmd(ENABLE);    //使能后备区域访问
        RTC_SetCounter(sec_cnt);        //设置RTC（实时时钟）计数器的值
        RTC_WaitForLastTask();          //等待最近一次对RTC寄存器的写操作完成
        return (0);
}

/*******************************************************************************
  函数名称: rtc_alarm_setup()
  输入参数: 年，月，日，时，分，秒
  输出参数: （0）返回成功， （非0）返回失败
  函数功能: RTC（实时时钟）设置闹钟
*******************************************************************************/
uint8_t rtc_alarm_setup( 
                  uint16_t year,        //年
                  uint8_t  month,       //月
                  uint8_t  day,         //日
                  uint8_t  hour,        //时
                  uint8_t  minute,      //分
                  uint8_t  second)      //秒
{
        uint16_t tmp;
        uint32_t sec_cnt = 0;
        if (year < 1970 || year > 2099) {
                return (1);
        }
        for (tmp = 1970; tmp < year; tmp++) {
                if (is_leap_year(tmp)) {
                        sec_cnt += 31622400;
                } else {
                        sec_cnt += 31536000;
                }
        }
        month -= 1;
        for (tmp = 0; tmp < month; tmp++) {
                sec_cnt += (uint32_t)month_tab[tmp] * 86400;
                if (is_leap_year(year) && tmp == 1) {
                        sec_cnt += 86400;
                }
        }
        sec_cnt += (uint32_t)(day - 1) * 86400;
        sec_cnt += (uint32_t)hour      * 3600;
        sec_cnt += (uint32_t)minute    * 60;
        sec_cnt += second;
        RCC_APB1PeriphClcokCmd(RCC_ARP1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
        PWR_BackupAccessCmd(ENABLE);    //使能后备区域访问
        RTC_SetAlarm(sec_cnt);          //设置RTC（实时时钟）闹钟的值   
        RTC_WaitForLastTask();          //等待最近一次对RTC寄存器的写操作完成
        return (0);     
}




/*******************************************************************************
  函数名称: rtc_get_time()
  输入参数: 无
  输出参数: 无
  函数功能: RTC（实时时钟）获取时间
*******************************************************************************/
uint8_t rtc_get_time(void)
{
        static uint16_t daycnt = 0;
        uint32_t timecount = 0;
        uint32_t tmp = 0;
        uint32_t tmp1 = 0;
        timecount = RTC_GetCounter();
        tmp = timecount / 86400;        //天数
        if (daycnt != tmp) {            //超过一天了
                daycnt = tmp;
                tmp1 = 1970;
                while (tmp >= 365) {
                        if (is_leap_year(tmp1)) {
                                if (tmp >= 365) tmp -= 365;
                                else {tmp1++; break;}
                        } else {
                                tmp -= 365;
                                tmp1++;
                        }
                }
                calendar.w_year = tmp1; //得到年份
                tmp1 = 0;
                while (tmp >= 28) {     //超过一个月了
                        if (is_leap_year(calendar.w_year) && tmp1 == 1) {
                                if (tmp >= 29) tmp -= 29;
                                else break;
                        } else {
                                if (tmp >= mon_table[tmp1]) tmp -= mon_table[tmp1];
                                else break;
                        }
                        tmp1++;
                }
                calendar.w_month = tmp1 + 1;    //得到月份
                calendar.w_date  = tmp1 + 1;    //得到日期
        }
        tmp = timecount % 86400;                //得到秒钟数        
        calendar.hour = tmp / 3600;             //时
        calendar.min  = (tmp % 3600) / 60;      //分
        calendar.sec  = (tmp % 3600) % 60       //秒
        calendar.week = RTC_Get_Week(calendar, w_year, calendar.w_month, calendar.w_date);
}


/*******************************************************************************
  函数名称: RTC_IRQHandler()
  输入参数: 无
  输出参数: 无
  函数功能: RTC（实时时钟）中断处理函数
*******************************************************************************/
void RTC_IRQHandler(void)
{
        if (RTC_GetITStatus(RTC_IT_SEC != RESET) {
                RTC_Get();
        }
        if (RTC_GetITStatus(RTC_IT_ALR != RESET) {
                RTC_ClearITPendBit(RTC_IT_ALR);
                RTC_Get();
                printf();
        }
        RTC_ClearITPendBit(RTC_IT_SEC | RTC_IT_OW);
        RTC_WaitForLastTask();
}
