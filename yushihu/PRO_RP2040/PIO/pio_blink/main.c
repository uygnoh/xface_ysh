#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "blink.pio.h"

int main(void) {
        static const uint led_pin = 25;
        static const float pio_freq = 2000;     // 2000Hz
        
        // 选择PIO硬件（PIO0 或 PIO1）
        PIO pio = pio0;
        
        // Get first free state machine in PIO 0
        uint sm = pio_claim_unused_sm(pio, true);
        
        // Add PIO program to PIO instructin memory.
        // return with the memory offset of the program
        uint offset = pio_add_program(pio, &blink_program);
        
        // Calculate the PIO clock divider
        float div = (float)clock_get_hz(clk_sys) / pio_freq;
        
        // PIO initialization
        blink_program_init(pio, sm, offset, led_pin, div);
        
        // Start running our PIO program int the state machine
        pio_sm_set_enabled(pio, sm, true);
        
        
        // Do nothing
        while (true) {
                sleep_ms(1000);
        }
}
