/*******************************************************************************
        => 位置式__PID__
*******************************************************************************/
typedef struct {
        float sv;       //用户设定值
        float pv;       //传感器传回数据
        float kp;       //比例系数
        float t;        //PID计算周期--采样周期
        float ti;       //积分时间（常数）
        float td;       //微分时间（常数）
        float ek;       //本次偏差
        float ek_1;     //上次偏差
        float sum_ek;   //历史偏差之和
        float pout;     //P算法计算结果
        float iout;     //I算法计算结果
        float dout;     //D算法计算结果
        float out;      //（PID）算法计算结果
        float out0;     //当（PID==0）时，加上一个常数，使控制不会失控
        uint16_t xms;   //由定时器产生（每1m增加一次）
        uint16_t pwmcycle;      //PWM周期
} pid;

//1MS中断一次
void TIM3_IRQHandler(void)
{
        uint8_t status;
        stauts = TIM_GetFlagStatus(TIM3, TIM_IT_Update);
        if (status != 0) {
                pid.xms++;
                TIM_ClearFlag(TIM3, TIM_IT_Update);
                pid_out();//输出PID运算结果
        }
}

void pid_init(void)
{
        pid.sv          = 120;  //用户设定值
        pid.kp          = 30;   //
        pid.t           = 500;  //PID计算周期（500ms）
        pid.ti          = 5000000;//积分时间
        pid.td          = 1000; //微分时间（1S中的变化率）
        pid.pwmcycle    = 200;  //PWM周期
        pid.out0        = 1;
}


void pid_calc(void)
{
        float del_ek;
        float ti;
        float ki;
        float td;
        float kd;
        float out;
        
        //计算周期未到
        if (pid.xms < pid.t) {
                return;
        }
        
        pid.ek   = pid.sv - pid.pv;     //得到当前的偏差值（用户设定值 - 传感器数值）
        pid.pout = pid.kp * pid.ek;             //比例输出
        pid.sum_ek += pid.ek;                   //历史偏差总和
        del_ek   = pid.ek - pid.ek_1;           //最近两次偏差之差
        
        ti = pid.t / pid.ti;
        ki = ti * pid.kp;
        pid.iout = ki * pid.sum_ek * pid.kp;    //积分输出
        
        td = pid.td / pid.t;                    //微分输出
        kd = pid.kp * td;
        pid.dout = kd * del_ek;
        
        out = pid.pout + pid.iout + pid.dout;
        
        if (out > pid.pwmcycle) {
                pid.out = pid.pwmcycle;
        } else if (out < 0) {
                pid.out = pid.out0;
        } else {
                pid.out = out;
        }
        
        pid.ek_1 = pid.ek;      //更新偏差数据
        pid.xms  = 0;
}
