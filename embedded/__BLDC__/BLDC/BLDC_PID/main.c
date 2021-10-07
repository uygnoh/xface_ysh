typedef enum {
        CW  = 0,        //顺时针方向
        CCW = 1         //逆时针方向
} MOTOR_DIR;

typedef enum {
        STOP = 0,       //停机
        RUN  = 1        //运行
} MOTOR_STATE;

typedef struct {
        __IO int                motor_speed;    //电机转速(RPM): 0..2500
        __IO MOTOR_STATE        motor_state;    //电机旋转状态
        __IO MOTOR_DIR          motor_direction;//电机转动方向
        __IO uint32_t          step_counter;   //霍尔传感器步数，用于测量电机转速
        __IO uint16_t          stalling_count; //停机标志，如果该值超过2000，认为电机停止旋转
} MOTOR_DEVICE;

typedef struct {
        __IO int                SetPoint;       //设定目标
        __IO double             Proportion;     //比例常数
        __IO double             Intergral;      //积分常数
        __IO double             Derivative;     //微分常数
        __IO int                LastError;      //Error[-1]
        __IO int                PrevError;      //Error[-2]
} PID;


//定义PID参数，这3个参数设定对电机运行影响非常大
#define P_DATA                  0.5
#define I_DATA                  0.06
#define D_DATA                  0

#define MOTOR_RATED_SPEED       2500            //额定转速
#define MOTOR_MAX_SPEED         3500            //空载转速
#define MOTOR_MIN_SPEED         100
#define MOTOR_POLE_PAIR_NUM     4               //极对数(8磁极数)
/*
        机械角度，  是指电机转子的旋转角度
        电角度，   是指磁场的旋转角度
        当电机为“4极对数”时， 电机的电角度  ==  4 * （机械角度360）  ==  1440度
        _______________________________________________________________
        当电机旋转一圈时， 3个霍尔传感器总共产生“4 * 6 == 24”个霍尔信号
*/



MOTOR_DEVICE bldc_dev = {500, STOP, CCW, 0, 0};
static PID bldc_pid;
__IO int16_t speed_duty = 100;                  //速度占空比: 0~1000
                                                //为“1000”时，占空比为100%
                                                //初始化值必须不小于“70”，否则电机不转
__IO uint8_t time_over  = 0;                    //“定时器3”->通道 4 溢出计数，


void system_clock_setup(void)
{
        1 使用外部调整晶体振荡器-8MHz
        2 9倍频，得到72MHz主频
        3 系统时钟72MHz， AHB时钟72MHz， APB1时钟36MHz，APB2时钟72MHz
}

int main(void)
{
        uint8_t key_count = 1;
        
        HAL_Init();             //复位所有外设，初始化Flash接口和系统滴答定时器
        system_clock_setup();   //配置系统时钟
        key_init();             //按键初始化
        hall_sensor_init();     //霍尔传感器接口初始化
        timer1_init();          //高级定时器“1”初始化并配置PWM输出功能
        
        
        while (1) {
                //****************** 功能选择 ******************//
                if (KEY1_StateRead() == KEY_DOWN) {
                        key_count++;
                        if (key_count > 5)
                                key_count = 1;
                }
                //****************** 功能执行 ******************//
                if (KEY2_StateRead() == KEY_DOWN) {
                        switch (key_count) {
                        case 1:         //电机启动
                                if (motor_state == STOP) {
                                        bldc_dev.motor_state    = RUN;
                                        bldc_dev.step_counter   = 0;
                                        bldc_dev.stalling_count = 0;
                                        IncPIDInit();

                                        if ((bldc_dev.motor_speed * 10 / 25) > 70)
                                        //*10/25为转速和占空比一个转换，转速（0~2500），占空比（0~1000）
                                                speed_duty = bldc_dev.motor_speed * 10 / 25;
                                        else
                                                speed_duty = 70;

                                        HAL_TIMEx_HallSensor_Start(&TIMER_HALL);
                                        __HAL_TIM_ENABLE_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                                        HAL_TIM_TriggerCallback(&TIMER_HALL);
                                }
                                break;
                        case 2:         //电机加速
                                bldc_dev.motor_speed += 20;
                                if (bldc_dev.motor_speed > MOTOR_MAX_SPEED)
                                        bldc_dev.motor_speed = MOTOR_MAX_SPEED;
                                bldc_pid.SetPoint = bldc_dev.motor_speed;
                                break;
                        case 3:         //电机减速
                                bldc_dev.motor_speed -= 50;
                                if (bldc_dev.motor_speed < MOTOR_MINI_SPEED)
                                        bldc_dev.motor_speed = MOTOR_MINI_SPEED;
                                bldc_pid.SetPoint = bldc_dev.motor_speed;
                                break;
                        case 4:         //电机方向反转
                                if (motor_direction == CW)
                                        bldc_dev.motor_direction = CCW;
                                else
                                        bldc_dev.motor_direction = CW;
                                break;
                        case 5:         //电机停机
                                HAL_TIMEx_HallSensor_Stop(&TIMER_HALL);
                                __HAL_TIM_DISABLE_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                                __HAL_TIM_CLEAR_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                                //这里作了一个简单的刹车效果
                                HAL_Delay(5);
                                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                                while (bldc_dev.stalling_count < 1);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                                bldc_dev.motor_state = STOP;
                                break;
                        }
                }
        }
}

/*________________________________________________________|
|               A <===> PWM_CH1 <===> U                   |
|               B <===> PWM_CH2 <===> V                   |
|               C <===> PWM_CH3 <===> W                   |
|________________________________________________________*/
//无刷驱动换相, 上桥臂PWM, 下桥臂ON
//step(4, 5, 1, 3, 2, 6) <===> pwm六步换相法
void bldc_phase_change(uint8_t step)
{
        switch (step) {
        case 4:                 //****************** B+ C- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH2.Pulse = TIM1_PERIOD * speed_duty / 1000;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH3.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                break;
        case 5:                 //****************** B+ A- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH2.Pulse = TIM1_PERIOD * speed_duty / 1000;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH1.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                break;
        case 1:                 //****************** C+ A- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH3.Pulse = TIM1_PERIOD * speed_duty / 1000;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH1.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                break;
        case 3:                 //****************** C+ B- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH3.Pulse = TIM1_PERIOD * speed_duty / 1000;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH2.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                break;
        case 2:                 //****************** A+ B- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH1.Pulse = TIM1_PERIOD * speed_duty / 1000;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH2.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                break;
        case 6:                 //****************** A+ C- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH1.Pulse = TIM1_PERIOD * speed_duty / 1000;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH3.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                break;
        default:                  //****************** OFF ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3); 
                break;
        }
}


//定时器3输出比较中断服务函数
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
        time_over++;
        //电机卡住超时
        if (time_over > 6) {
                bldc_dev.stalling_count++; //电机停止转动标志
                time_over = 0;
        }
}


//定时器触发中断服务函数
//输入参数: GPIO_Pin，中断引脚
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
{
        uint8_t pinstate  = 0;
        uint8_t pinstate0 = 0;
        if (bldc_dev.motor_state == STOP)
                return;
        
        //霍尔传感器状态获取
        if ((HALL_TIM_CH1_GPIO->IDR & HALL_TIM_CH1_PIN) != GPIO_PIN_RESET)
                pinstate |= 0x01;
        if ((HALL_TIM_CH2_GPIO->IDR & HALL_TIM_CH2_PIN) != GPIO_PIN_RESET)
                pinstate |= 0x02;
        if ((HALL_TIM_CH3_GPIO->IDR & HALL_TIM_CH3_PIN) != GPIO_PIN_RESET)
                pinstate |= 0x04;
        
        if (bldc_dev.motor_direction == CW)
                pinstate = 7 - pinstate;
        bldc_phase_change(pinstate);
        //测试发现有时会连续出现2个相同的数据，这里过滤重复的
        if (pinstate0 != pinstate) {
                bldc_dev.step_counter++;
                bldc_dev.stalling_count = 0;
        }
        pinstate0 = pinstate;
        time_over = 0;
}



//PID参数初始化
void IncPIDInit(void)
{
        bldc_pid.LastError  = 0;                        //Error[-1]
        bldc_pid.PrevError  = 0;                        //Error[-2]
        bldc_pid.Proportion = P_DATA;                   //比例常数
        bldc_pid.Integral   = I_DATA;;                  //积分常数
        bldc_pid.Derivative = D_DATA;                   //微分常数
        bldc_pid.SetPoint   = bldc_dev.motor_speed;     //设定目标速度
}
//增量式PID控制设计
int IncPIDCalc(int NextPoint)
{
        int iError, iIncpid;                                  //当前误差
        iError  = bldc_pid.SetPoint - NextPoint;              //增量计算
        iIncpid =  (bldc_pid.Proportion * iError)             //E[k]  项
                  -(bldc_pid.Integral   * bldc_pid.LastEror)  //E[k-1]项
                  +(bldc_pid.Derivative * bldc_pid.PrevError);//E[K-2]项
        bldc_pid.PrevError = bldc_pid.LastError;  //存储误差，用于下次计算
        bldc_pid.LastError = iError;
        return(iIncpid);                        //返回增量值
}

//系统滴答定时器回调函数, 1ms运行一次
void HAL_SYSTICK_Callback(void)
{
        static uint16_t time_count = 0;
        if (bldc_dev.motor_state == RUN) {
                time_count++;
                if (time_count > 50) {
                        int tmp, pid_result;
                //bldc_dev.step_counter-记录霍尔传感器在“50ms”时间内产生的脉冲个数
                //而电机旋转一圈总共（MOTOR_POLE_PAIR_NUM*6）个脉冲数， 使用
                //n == bldc_dev.step_counter / (MOTOR_POLE_PAIR_NUM * 6) 为
                //       “50ms”内电机转动圈数， 为换算为【转/分钟(RPM)】
                // n / 50 = x / (60*1000)   ===>  x = bldc_dev.step_counter*50
                        tmp = bldc_dev.step_counter * 50;
                        pid_result = IncPIDCalc(tmp);      //增量式PID计算
                        pid_result = pid_result * 10 / 25; //*10/25转速和占空比转换
                        if ((pid_result + speed_duty) < 70)
                                speed_duty = 70;
                        else if ((pid_result + speed_duty) > 1000)
                                speed_duty = 1000;
                        else
                                speed_duty += pid_result;
                        time_count = 0;
                        bldc_dev.step_counter = 0;
                } 
        } else {
                time_count = 0;
        }
}
