// 使用定时2器，打开定时器中断（使用1ms定时中断）
// Ts 定时器周期（0.001S）
#define _constrain(amt, low, high)      ((amt) < (low) ? (low) : ((amt) > (high) ? (high): (amt)))

// 电机参数设置
//_____________________________________________________________
#define POLE_PAIR       7       //电机极对数
float angle = 0;                //电机的机械角度
float angle_el = 0;             //电机的电角度
float angle_curent = 0;         //
float angle_prev = 0;           //
float velocity = 0;             //角速度
float vel_prev = 0;             //电机之前的角速速
float vel_sp = 30;              //电机的设定转速
float vel_LPF = 0;              //经过低能滤波的（角速度）
float Ts = 0.001;               //1ms的控制周期
float integral_vel_prev;        //积分项的前一个值 



// PID控制器参数
//_____________________________________________________________
float KP_vel = 0.1;
float KI_vel = 1;
float KD_vel = 0;
float voltage_limit = 2;        //转速环输出（Uq限幅 = 3）


//_____________________________________________________________
void TIM2_IRQhandler(void)
{
        // SVPWM函数输出
        //_____________________________________________________
        angle    = as5600_get_angle();          //机械角度
        angle_el = angle * POLE_PAIR;           //电角度
        // vel_sp(用户设定的电机转速), vel_LPF(电机的实际转速)
        Uq_set = PID_velocity(vel_sp - vel_LPF);
        SetPhaseVolatage(Uq_set, 0, angle_el);
        
        // 角度差分计算转速
        //_____________________________________________________
        angle_current = angle;                  //当前机械角度
        //velocity(角速度) = (电机的当前机械角度 - 上一次电机的机械角度) / Ts(定时器2的周期)
        velocity = (angle_current - angle_prev) / Ts;
        //使用低通滤波，去除噪声（得到最终的电机——角速度）  
        vel_LPF = LPF_velocity(velocity);
        angle_prev = angle_current;
}

// 反馈转速低通滤波(LPF = low-pass filter)
//_____________________________________________________________
float LPF_velocity(float x)
{
        float y = 0.9 * vel_prev + 0.1 * x;
        vel_prev = y;
        return (y);
}

// 转速PID函数 (velocity = 速度)
//_____________________________________________________________
float PID_velocity(float error)
{
        float output, output_vel_prev;
        float proportional, integral, differential;
        float error_vel_prev;
        proportional = KP_vel * (error);
        integral     = integral_vel_prev + KI_vel * Ts * error;
        differential = KD_vel * (error - error_vel_prev) / Ts;
        output       = proportional + integral + differential;
        output       = _constrain(output, -volatate_limit, voltage_limit);
        
        //存储上一次过程量
        integral_vel_prev = integral;
        output_vel_prev   = output;
        error_vel_prev    = error;
        return (output);
}


// 角度控制PID函数
//_____________________________________________________________
