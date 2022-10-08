#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "m32.h"

void apb_ahb_clock_reset(void);
void apb_ahb_clock_enable(void);
void rcc_hsi_setup(void);
int rcc_hse_setup(void);
#endif
