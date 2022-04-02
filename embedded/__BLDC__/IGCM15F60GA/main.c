// STM32F103C8T6_STM32CubeIDE

// TIM1 高级定时器
// ____________________________________________________________
// 72*1000*1000 / 36  = 2*1000*1000             //系统时钟（72MHz）
//  2*1000*1000 / 100 = 20000                   //定时器PWM周期
// ____________________________________________________________
// 定时器1工作模式
Clock Sorcec            //Interanl Clock
Channel1                //PWM Generaltion CH1 CH1N
Channel2                //PWM Generaltion CH2 CH1N
Channel3                //PWM Generaltion CH3 CH1N
// 定时器1参数配置
Prescaler(PSC - 16 bits value)                          (36-1)  //定时器预分频
Cunter Period(AutoReload Register -16 bit value)        (100-1) //PWM周期
Pulse(16 - bits value)                                          //PWM占空比
Dead Time                                               (5)     //死区时间



#define duty    10
#define A0      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0); //A相占空比为（0）
#define B0      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0); //B相占空比为（0）
#define C0      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0); //C相占空比为（0）
#define A1      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);
#define B2      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty);
#define C3      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, duty);

int main(void)
{
        // 输出6路PWM
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
        HAL_TIM_PWMN_Start(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWMN_Start(&htim1, TIM_CHANNEL_2);
        HAL_TIM_PWMN_Start(&htim1, TIM_CHANNEL_3);
        
        while (1) {
                A1;     B0;     C0;
                HAL_Delay(10);
                A0;     B1;     C0;
                HAL_Delay(10);
                A0;     B0;     C1;
                HAL_Delay(10);
                
        }
}
