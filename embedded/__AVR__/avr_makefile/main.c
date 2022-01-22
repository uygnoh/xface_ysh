#undef  F_CPU
#define F_CPU                   (8000000UL)     //8MHz
#include <avr/io.h>
//#include <avr/iom328p>
#include <util/delay.h>
#include "bsp/bsp.h"

int main(void)
{
        DDRD = 0b11111111;
        while (1) {
                PORTD = 0b00000001;
                _delay_ms(500);
                PORTD = 0b00000000;
                _delay_ms(500);
        }
        //test();
        return 0;
}
