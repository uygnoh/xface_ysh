#include "nvic.h"


void scb_set_priority_grouping(void)
{
        SCB->AIRCR = PRIORITY_GROUP_04;
}
