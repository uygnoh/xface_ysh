IPM功率芯片的参数：（infineon）
1. IGCM15F60GA
2. 大疆（2312）
3. AN2016-12 Application Note




#define PWM_Period      100
#define _PI             3.14159265359
#define _PI_2           1.57079632679
#define _PI_3           1.0471975512
#define _2PI            6.28318530718
#define _3PI_2          4.71238898038
#define _PI_6           0.52359877559
#define _SQRT3          1.73205080757

float volatage_power_supply;    //直流母线电压值

//将角度值控制在（0 ~ 2pi）之间
//fmod（对浮点数取模）
float _normalizeAngle(float angle)
{
        float a = fmod(angle, _2PI); //将角度值对（_2PI）取模
        return a >= 0 ? a : (a+_2PI);
}

/*      
        SVPWM实现步骤：
        1. 计算参考电压矢量
        2. 判断参考电压矢量Vre所在扇区
        3. 计算相邻电压矢量和零矢量作用的时间
        4. 计算各相邻桥臂功率器件的开关时间
*/
//FOC核心函数， （输入Ud, Uq，电角度）
//Park（逆变换）， 将（Ud, Uq）变换成（U_alpha, U_beta）
void setPhaseVoltage(float Uq, float Ud, float angle_el)
{
        float Uref;             //参考电压
        uint32_t sector;        //
        float T0, T1, T2;
        float Ta, Tb, Tc;
        float U_alpha, U_beta;
        float V1, V2, V3;
        int A, B, C;
        int N;
        
        //标准化电角度值（0~2pi）， 加90度后是参考电压矢量的位置
        angle_el = _normalizeAngle(angle_el + _PI_2);
        
        U_alpha = Ud*cos(angle_el) - Uq*sin(angle_el);  //反Park变换
        U_beta  = Ud*sin(angle_el) + Uq*cos(angle_el);  //反Park变换
        
        U_ref   = _sqrt(U_alpha*U_alpha + U_beta*U_beta) / volatage_power_supply;
        
        //限幅（0.577 == ）
        //svpwm的最大不失真旋转电压矢量幅值（根号3 /3）
        if (Uref > 0.577) {
                Uref = 0.577;
        }
        if (Uref < -0.577) {
                Uref = -0.577;
        }
        
        
        //判断（参考电压矢量Vref所在扇区）
        sector = (angle_el / _PI_3) + 1;
        
        
        //计算各相邻桥臂功率器件的开关时间
        T1 = _SQRT3 * sin(sector*_PI_3 - anagle_el) * Uref;
        T2 = _SQRT3 * sin(angle_el -(sector - 1.0)*_PI_3) * Uref;
        T0 = 1 - T1 - T2;       //零矢量电压作用的时间
        
        //
        switch (sector) {
        case 1:
                Ta = T1 + T2 + T0/2;
                Tb = T2 + T0/2;
                Tc = T0/2;
                break;
        case 2:
                Ta = T1 + T0/2;
                Tb = T1 + T2 + T0/2;
                Tc = T0/2;
                break;
        case 3:
                Ta = T0/2;
                Tb = T1 + T2 + T0/2;
                Tc = T2 + T0/2;
                break;
        case 4:
                Ta = T0/2;
                Tb = T1 + T0/2;
                Tc = T1 + T2 + T0/2;
                break;
        case 5:
                Ta = T2 + T0;
                Tb = T0/2;
                Tc = T1 + T2 + T0/2;
        case 6:
                Ta = T1 + T2 + T0/2;
                Tb = T0/2;
                Tc = T1 + T0/2;
        default:
                Ta = 0;
                Tb = 0;
                Tc = 0;
        }
        //输出（SVPWM）
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Ta*PWM_Period);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Tb*PWM_Period);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, Tc*PWM_Period);
}



while (1) {
        setPhaseVolatate(1, 0, angle_el);
        angle_el += 0.1;
}





