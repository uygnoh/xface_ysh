

typedef struct {
        volatile uint8_t  hour;         //时
        volatile uint8_t  minute;       //分
        volatile uint8_t  second;       //秒
        volatile uint16_t year;         //年
        volatile uint8_t  month;        //月
        volatile uint8_t  day;          //日
        volatile uint8_t  week;         //周
        
} calendar_obj;
extern calendar_obj calendar;
			 


void rtc_nvic_setup(void);              //NVIC设置
uint8_t is_leap_year(uint16_t year);    //判断是否为闰年？
