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
//step(4, 5, 1, 3, 2, 6) <===> pwm六步换相法
void bldc_phase_change(uint8_t step)
{
        switch (step) {
        case 4:                 //****************** B+ C- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH2.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH3.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                break;
        case 5:                 //****************** B+ A- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH2.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH1.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                break;
        case 1:                 //****************** C+ A- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH3.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH1.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                break;
        case 3:                 //****************** C+ B- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH3.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH3, TIM_CHANNEL_3);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH2.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                break;
        case 2:                 //****************** A+ B- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                
                PWM_CH1.Pulse = TIM1_PERIOD * speed_duty / 100;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH1, TIM_CHANNEL_1);
                HAL_TIM_PWM_Start(&TIMER_BLDC, TIM_CHANNEL_1);
                
                PWM_CH2.Pulse = TIM1_PERIOD;
                HAL_TIM_PWM_ConfigChannel(&TIMER_BLDC, &PWM_CH2, TIM_CHANNEL_2);
                HAL_TIMEx_PWMN_Start(&TIMER_BLDC, TIM_CHANNEL_2);
                break;
        case 6:                 //****************** A+ C- ******************//
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIM_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                
                PWM_CH1.Pulse = TIM1_PERIOD * speed_duty / 100;
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


//电机卡住超过一定时间的话， 让电机停止
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
        time_over++;
        //电机卡住超时
        if (time_over > 6) {
                motor_state = STOP;
                HAL_TIMEx_HallSensor_Stop(&TIMER_HALL);
                __HAL_TIM_DISABLE_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                __HAL_TIM_CLEAR_IT(&TIMER_HALL, TIM_IT_TRIGGER | TIM_IT_CC4);
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_1);
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_2);
                HAL_TIM_PWM_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
                HAL_TIMEx_PWMN_Stop(&TIMER_BLDC, TIM_CHANNEL_3);
        }
}


//定时器触发中断服务函数
//输入参数: GPIO_Pin，中断引脚
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
{
        uint8_t pinstate = 0;
        if (motor_state == STOP)
                return;
        
        //霍尔传感器状态获取
        if ((HALL_TIM_CH1_GPIO->IDR & HALL_TIM_CH1_PIN) != GPIO_PIN_RESET)
                pinstate |= 0x01;
        if ((HALL_TIM_CH2_GPIO->IDR & HALL_TIM_CH2_PIN) != GPIO_PIN_RESET)
                pinstate |= 0x02;
        if ((HALL_TIM_CH3_GPIO->IDR & HALL_TIM_CH3_PIN) != GPIO_PIN_RESET)
                pinstate |= 0x04;
        //方向判断
        if (motor_direction == CW)
                pinstate = 7 - pinstate;
        //驱动换相
        bldc_phase_change(pinstate);
        time_over = 0;
}

