typedef struct {
        __IO float SetPoint;            // 目标值
        __IO float ActualValue;         // 期望值
        __IO float SumErroe;            // 累计偏差
        __IO float Proportion;          // 比例系数
        __IO float Integral;            // 积分系数
        __IO float Derivative;          // 微分系数
        __IO float Error;               // K
        __IO float LastError;           // K-1
        __IO float PrevError;           // K-2
        
} PID_TypeDef;


// 增量式PID参数
#define KP              8.50f
#define KI              5.00f
#define KD              0.10f


extern PID_TypeDef      g_speed_pid;    // 速度环PID参数结构体


void pid_init(void)
{
        g_speed_pid.Setpoint    = 0;
        g_speed_pid.ActualValue = 0;
        g_speed_pid.SumError    = 0;
        g_speed_pid.Error       = 0;
        g_speed_pid.LastError   = 0;
        g_speed_pid.PrevError   = 0;
        g_speed_pid.Proporition = KP;
        g_speed_pid.Integral    = KI;
        g_speed_pid.Derivative  = KD;
}



int32_t pid_control(PID_TypeDef *PID, float Feedback_value)
{
        PID->Error = (float)(PID->SetPoint - Feeback_value);    // 计算偏差
        
# if 如果定义的是增量式PID
        PID->ActualValue +=    (PID->Proportion * (PID->Error - PID->LastError)) 
                             + (PID->Integral   * PID->Error)
                             + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));
        PID->PrevError   = PID->LastError;      // 存储偏差值， 用于下一次计算
        PID->LastError   = PID->Error;          // 存储偏差值， 用于下一次计算
# else 位置式PID
        PID->SumError   += PID->Error;          // 偏差e累加求和
        PID->ActualValue =      (PID->Proportion * PID->Error)
                              + (PID->Integral   * PID->SumError)
                              + (PID->Derivative * (PID->Error - PID->LastError));
        PID->LastError  = PID->Error;
# endif
        return ((int32_t)(PID->ActualValue));
}
















