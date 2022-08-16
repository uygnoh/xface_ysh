//      测试目标： 以10步、1度的分辨率， 以120转/每分钟 的转速运行
//
//
//      求theta(角):
//                              2PI         1       2PI
//      1庋 = 10步 => theta =  ------  X  -----  = ------- =  0.0008726646 弧度
//                              360        10       3600
//
//
//      求定时器PSC的值： 
//      设置： 电机极对数为（2）     
//      机械（1分钟120转） => 机械1转（500毫秒） => 电角度2PI => 电角度（250毫秒）
//      定时器中断间隔为：
//              10步为1庋
//              2500ms/3600 = 0.069444ms = 69.444us
//
//


// 定时器6微秒延时函数
void timer6delayus(uint16_t us)
{
        RCC->APB1ENR    |=   0x01 << 4;         // TIM6时钟打开
        TIM6->CR1       &= ~(0x01 << 7);        // 不进行重载缓冲
        TIM6->CR1       &= ~(0x01 << 3);        // 连续工作模式
        TIM6->PSR        =  (84 - 1);           // 设置为（1000000Hz）
        TIM6->ARR        =  (us);               // 1微秒 * us
        TIM6->CNT        =  (0);                // 清零计数器
        TIM6->EGR       |=  (0x01);             // 给UG更新事件，让定时器回到准备状态
        TIM6->SR        &= ~(0x01);             ///
        TIM6->CR1       |=  (0x01);             // 使能计数器
        while (!(TIM6->SR & 0x01);
        TIM6->SR        &= ~(0x01);
        TIM6->CR1       &= ~(0x01);
}










#include "stm32f4xx.h"
#include "arm_math.h"
#define sqrt3   1.7320508f
//
//
//
// 反Park变换
// 将静止两相坐标系 D/Q  转换为旋转两相坐标系 Valpha/Vbeta
void RevParkOperate(float vd, float vq, float theta, float *valpha, float *vbeta)
{
        *valpha = vd * arm_cos_f32(theta) - vq * arm_sim_f32(theta);
        *vbeta  = vd * arm_sim_f32(theta) + vq * arm_cos_f32(theta);
}


// 扇区判断函数，通过valpha和vbeta判断扇区
// 返回值： 315462 对应的扇区 123456
uint8_t SectorJudge(float valpha, float vbeta)
{
        float A = vbeta;
        float B =  valpha  * sqrt3 / 2.0f - vbeta / 2.0f;
        float C = -valpha  * sqrt3 / 2.0f - vbeta / 2.0f;
        
        uint8_t N = 0;
        if (A > 0) {
                N = N + 1；
        }
        if (B > 0) {
                N = N + 2;
        }
        if (C > 0) {
                N = N + 4;
        }
        return N;
}


// 矢量作用时间计算
void VectorActionTime(uint8_t n, float valpha, float vbeta, uint32_t udc, uint32_t tpwm
                        float *ta, float *tb) {
        float X = (sqrt3 * tpwm) / udc * vbeta;
        float Y = (sqrt3 * tpwm) / udc * ( (sqrt3 / 2.0f) * valpha - 0.5 * vbeta);
        float Z = (sqrt3 * tpwm) / udc * (-(sqrt3 / 2.0f) * vlapha - 0.5 * vbeta);
        
        if (n == 3) {           // 第 1 扇区
                *ta = Y;
                *tb = X;
        }
        if (n == 1) {           // 第 2 扇区
                *ta = -Y;
                *tb = -Z;
        }
        if (n == 5) {           // 第 3 扇区
                *ta = X;
                *tb = Z;
        } 
        if (n == 4) {           // 第 4 扇区
                *ta = -X;
                *tb = Y;
        }   
        if (n == 6) {           // 第 5 扇区
                *ta = Z;
                *tb = Y;
        } 
        if (n == 2) {           // 第 6 扇区
                *ta = -Z;
                *tb = -X;
        } 
}

// CCR时间计算
void CCRCalulate(uint8_t n, float ta, float tb, uint32_t tpwm, 
                        uint32_t *ccr1, uint32_t *ccr2, uint32_t ccr3) {
        float temp = ta + tb;
        if (temp > tpwm) {
                ta = ta / temp * tpwm;
                tb = tb / temp * tpwm;
        }
        
        float value1 = (tpwm - ta - tb) / 4.0f;
        float value2 = value1 + ta / 2.0f;
        float value3 = value2 + tb / 2.0f;
        
        switch (n) {
        case 3:
                *ccr1 = value1;
                *ccr2 = value2;
                *ccr3 = value3;
                break;
        case 1:
                *ccr1 = value2;
                *ccr2 = value1;
                *ccr3 = value3;
                break;
        case 5:
                *ccr1 = value3;
                *ccr2 = value1;
                *ccr3 = value2;
                break;
        case 4:
                *ccr1 = value3;
                *ccr2 = value2;
                *ccr3 = value1;
                break;
        case 6:
                *ccr1 = value2;
                *ccr2 = value3;
                *ccr3 = value1;
                break;
        case 2:
                *ccr1 = value1;
                *ccr2 = value3;
                *ccr3 = value2;
                break;
        }
}



// 通过 Vd, Vq, Theta, Udc, Tpwm 计算每一步的CCR值
// udc  = 24V
// tpwm = 8400
void SvpwmAlgorithm(float vd, float vq, float theta, uint32_t udc, uint32_t tpwm) {
        float valpha = 0;
        float vbeta  = 0;
        RevParkOperate(vd, vq, theta, &valpha, &vbeta); // 计算当前Valpha和Vbeta
        uint8_t n = SectorJude(valpha, vbeta);          // 计算当前的扇区
        float ta = 0;
        float tb = 0;   // 定义矢量作用时间
        VectorActionTime(n, valpha, vbeta, udc, tpwm, &ta, &tb);
        uint32_t ccr1 = 0;
        uint32_t ccr2 = 0;
        uint32_t ccr3 = 0;
        CCRCalulate(n, ta, ta, tpwm, &ccr1, &ccr2, &ccr3);
        TIM1->CCR1 = ccr1;
        TIM1->CCR2 = ccr2;
        TIM1->CCR3 = ccr3;
}
