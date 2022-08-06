
#include "os.h"
void SysTick_Handler(void)
{
        #if OS_CRITICAL_METHOD == 3u
        OS_CPU_SR  cpu_sr;
        #endif
        
        OS_ENTER_CRITICAL();
        OSIntEnter();
        OS_EXIT_CRITICAL();

        OSTimeTick();

        OSIntExit();
}

