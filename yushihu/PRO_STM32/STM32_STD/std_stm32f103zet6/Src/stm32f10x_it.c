
#include "stm32f10x_it.h"



/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/
void NMI_Handler(void)
{
        while (1) {
        }
}



void HardFault_Handler(void)
{
        while (1) {
        }
}



void MemManage_Handler(void)
{
        while (1) {
        }
}



void BusFault_Handler(void)
{
        while (1) {
        }
}



void UsageFault_Handler(void)
{
        while (1) {
        }
}



void SVC_Handler(void)
{
        while (1) {
        }
}



void DebugMon_Handler(void)
{
        while (1) {
        }
}



void PendSV_Handler(void)
{
        while (1) {
        }
}



void SysTick_Handler(void)
{
        while (1) {
        }
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
        if(EXTI_GetITStatus(EXTI_Line10) != RESET) {
                for (;;) {
                        GPIOA->BSRR = 0x00000005;
                }
                // Clear the  EXTI line 10 pending bit
                EXTI_ClearITPendingBit(EXTI_Line10);
        }
}

