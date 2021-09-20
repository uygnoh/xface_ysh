#include <stdint.h>
#include <stdio.h>
#include "../stm8s.h"
#include "init.h"

#define __nop() __asm nop __endasm

void main() {
    port_init();
    clk_init();

    while (1) {
            PB_ODR ^= 0x20;
            __delay();
    }

}
