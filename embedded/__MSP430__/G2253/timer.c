#include <msp430g2253.h>

int main(void)
{
        WDTCTL = WDTPW + WDTHOLD;
        P1DIR |= 0x01;
        TACTL  = TASSEL_1 + MC_2 + TAIE;        // 时钟源ACLK，连续计数模式，开中断
        _BIS_SR(LPM3_bits + GIE);               // 进入低功耗模式3，开总中断
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
        switch (TA0IV) {
        case 2: break;          // CCR1 not used
        case 4: break;          // CCR2 not used
        case 10:                // 计数到（65535），产生溢出中断
                P1OUT ^= 0x01;  // 翻转电平
                break;
        }
}
