typedef enum {
        CW  = 0,        //顺时针方向
        CCW = 1         //逆时针方向
} MOTOR_DIR;
typedef enum {
        STOP = 0,       //停机
        RUN  = 1        //运行
} MOTOR_STATE;

__IO int16_t    speed_duty = 15;        //速度占空比：0~100
__IO MOTOR_STATE motor_state = STOP;    //电机状态
__IO MOTOR_DIR   motor_direction = CW;  //电机方向
__IO uint8_t    time_over = 0;          //卡住超时溢出计数

void SystemClock_Config(void)
{
        1 使用外部调整晶体振荡器-8MHz
        2 9倍频，得到72MHz主频
        3 系统时钟72MHz， AHB时钟72MHz， APB1时钟36MHz，APB2时钟72MHz
}

int main(void)
{
        uint8_t key_count = 1;
        
        HAL_Init();             //复位所有外设，初始化Flash接口和系统滴答定时器
        SystemClock_Config();   //配置系统时钟
        KEY_GPIO_Init();        //按键初始化
        HALL_TIMx_Init();       //霍尔传感器接口初始化
        ADVANCED_TIMx_Init();   //高级定时器初始化并配置PWM输出功能
        
        
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
                                        motor_state = RUN;
                                        HAL_TIM_TriggerCallback(&TIMER_HALL);
                                        HAL_Delay(4);
                                        HAL_TIMEx_HallSensor_Start(&TIMER_HALL);
                                        __HAL_TIM_ENABLE_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                                        HAL_TIM_TriggerCallback(&TIMER_HALL);
                                }
                                break;
                        case 2:         //电机加速
                                speed_duty += 5;
                                if (speed_duty > 100)
                                        speed_duty = 100;
                                break;
                        case 3:         //电机减速
                                speed_duty -= 5;
                                if (speed_duty < 7)
                                        speed_duty = 7;
                                break;
                        case 4:         //电机方向反转
                                if (motor_direction == CW)
                                        motor_direction = CCW;
                                else
                                        motor_direction = CW;
                                break;
                        case 5:         //电机停机
                                motro_state = STOP;
                                HAL_TIMEx_HallSensor_Stop(&TIMER_HALL);
                                __HAL_TIM_DISABLE_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                                __HAL_TIM_CLEAR_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
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
void BLDC_PHASE_CHANGE(uint8_t step)
{
        switch (step) {
        case 4:         //****************** B+ C- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH2.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH3.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                break;
        case 5:         //****************** B+ A- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH2.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH1.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                break;
        case 1:         //****************** ******************//
                break;
        case 3:         //****************** ******************//
                break;
        case 2:         //****************** ******************//
                break;
        case 6:         //****************** ******************//
                break;
        default:
                break;
        }
}
