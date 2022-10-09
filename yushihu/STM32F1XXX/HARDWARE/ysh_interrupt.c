#include "ysh_interrupt.h"


void nvic_setup(void)
{
        SCB->AIRCR = PRIORITY_GROUP_04;
}
