// 使用定时2器，打开定时器中断（使用1ms定时中断）
// Ts 定时器周期（0.001S）
#define _constrain(amt, low, high)      ((amt) < (low) ? (low) : ((amt) > (high) ? (high): (amt)))



// 电机参数设置
//_____________________________________________________________
#define POLE_PAIR       7       //电机极对数
float angle = 0;                //电机的机械角度
float angle_el = 0;             //电机的电角度
float Ts = 0.001;               //1ms的控制周期
float angle_c;
float angle_curent = 0;         //
float angle_prev = 0;           //
float velocity = 0;            //速度



// 转速环PID参数
//_____________________________________________________________
float y_vel_prev = 0;           //电机之前的LPF实际转速
float vel_sp = 30;              //电机的设定转速
float vel_LPF = 0;              //电机的实际转速
float integral_vel_prev;        //积分项的前一个值 
float voltage_limit = 2;        //转速环输出（Uq限幅 = 3）
float KP_vel = 0.1;
float KI_vel = 1;
float KD_vel = 0;



// 角度环PID参数
//_____________________________________________________________
float angle_sp = 3.14159;       //参考角度
float angle_limit = 50;         //角度环输出（限速 = 50）
float KP_angle = 2;
float KI_angle = 0.2;
float KD_angle = 0;
float integral_angle_prev;



// 定时器2中断服务函数
//_____________________________________________________________
void TIM2_IRQhandler(void)
{
        // SVPWM函数输出
        //_____________________________________________________
        angle = as5600_get_angle();             // 机械角度
        angle = angle * POLE_PAIR;              // 电角度
        vel_sp = PID_angle(angle_sp - angle);   // 角度环PID
        Uq_set = PID_velocity(vel_sp - vel_LPF);// 速度环PID
        SetPhaseVolatage(Uq_set, 0, angle_el);  // SVPWM
        

        
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
        float y = 0.9 * y_vel_prev + 0.1 * x;
        y_vel_prev = y;
        return (y);
}


// 转速环PID函数 (velocity = 速度)
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
        
        // 转速环电压限幅
        output       = _constrain(output, -volatate_limit, voltage_limit);
        
        //存储上一次过程量
        integral_vel_prev = integral;
        output_vel_prev   = output;
        error_vel_prev    = error;
        return (output);
}


// 角度环PID函数
//_____________________________________________________________
float PID_angle(float error)
{
        float output, output_angle_prev;
        float proportional, integral, differential;
        float error_angle_prev;
        proportional = KP_angle * (error);
        integral     = integral_angle_prev + KI_angle * Ts * error;
        differential = KD_angle * (error - error_angle_prev) / Ts;
        output       = proportional + integral + differential;
        
        // 角度环速度限幅
        output       = _constrain(output, -speed_limit, speed_limit);
        
        //存储上一次过程量
        integral_angle_prev = integral;
        output_angle_prev   = output;
        error_angle_prev    = error;
        return (output);
}
