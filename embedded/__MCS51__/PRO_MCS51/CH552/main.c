#include "8051.h"
#include "ch552.h"

int main(void)
{       
        P1_MOD_OC = 0b01111111;
        P1_DIR_PU = 0b01111111;
        while (1) {
        }
        return 0;
}
