
#include "main.h"
#include "stm32f4xx_it.h"


/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
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


void DebugMon_Handler(void)
{
        while (1) {
        }
}

#include "FreeRTOS.h"
#include "task.h"
extern void xPortSysTickHandler(void);
void SysTick_Handler(void)
{
        #if (INCLUDE_xTaskGetSchedulerState == 1)
        if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
        #endif
        	xPortSysTickHandler();
        #if (INCLUDE_xTaskGetSchedulerState == 1)
        }
        #endif
}

