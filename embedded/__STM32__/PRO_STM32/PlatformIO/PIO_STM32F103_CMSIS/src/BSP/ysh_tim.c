#include "ysh_tim.h"

void tim2_init(void)
{
    /* % 1:TIMx_ARR寄存器被装入缓冲器 */
    TIM2->CR1 |= (uint16_t)TIM_CR1_ARPE;
    /* % 1:计数器向下计数 */
    TIM2->CR1 |= (uint16_t)TIM_CR1_DIR;
    /* % 时钟源选择: 内部时钟源(CK_INT) */
    /* % SMS[2:0] 000:关闭从模式 – 如果CEN=1,则预分频器直接由内部时钟驱动 */
    TIM2->SMCR &= (uint16_t)(~TIM_SMCR_SMS);

    /* % 预分频器 */
    TIM2->PSC = (uint16_t)(7200-1);
    /* % 自动重装载寄存器 */
    TIM2->ARR = (uint16_t)(1000-1);
    /* % 计数器清零 */
    TIM2->CNT = (uint16_t)0x0000;
    /* 1:使能触发中断 */
    TIM2->DIER |= (uint16_t)TIM_DIER_TIE;
    TIM2->DIER |= (uint16_t)TIM_DIER_UIE;


    /* % 打开计数器"2" */
    TIM2->CR1 |= (uint16_t)TIM_CR1_CEN;

}