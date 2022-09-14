#include <stdio.h>
#include "pico/stdlib.h"


int main(void)
{
        stdio_init_all();
        
        // Initialise GPIO Pin 25 for LED
        gpio_init(25);
        gpio_set_dir(25, GPIO_OUT);
        
        char user_input;
        
        while (1) {
                printf("command (1 = ON  or  0 = OFF):\n");
                user_input = getchar();
                
                if (user_input == '1') {
                        gpio_put(25, 1);
                        printf("LED swicthed ON!\n");
                } else if (user_input == '0') {
                        gpio_put(25, 0);
                        printf("LED swicthed OFF!\n");
                } else {
                        printf("Invalid Input!\n");
                }
        }
}
