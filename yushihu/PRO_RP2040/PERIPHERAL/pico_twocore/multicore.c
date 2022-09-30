#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "hardware/adc.h"


// Core 1 interrupt Handler
void core1_interrupt_handler(void)
{
        // Recive RAW value, Convert and Print Temperature over USB Serial
        while (multicore_fifo_rvalid()) {
                uint16_t raw = multicore_fifo_pop_blocking();
                const float conversion_factor = 3.3f / (1 << 12);
                float result = raw * conversion_factor;
                float temp = 27 - (result - 0.706) / 0.001721;
                printf("Temp = %f c\n", temp);
        }
        multicore_fifo_clear_irq();
}
// Core 1 Main Code
void core1_entry(void)
{
        // Configure Core interrupt
        multicore_fifo_clear_irq();
        irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
        irq_set_enabled(SIO_IRQ_PROC1, true);
        
        // Infinite loop which waits for interrupt
        while (1) {
                tight_loop_contents();
        }
}



int main(void)
{
        stdio_init_all();
        
        // Start core 1 - Must be called brefore configuring interrupts
        multicore_launch_core1(core1_entry);
        
        // Configure ADC
        adc_init();
        adc_set_temp_sensor_enabled(true);
        adc_select_input(4);
        
        while (1) {
                uint16_t raw = adc_read();
                multicore_fifo_push_blocking(raw);
                sleep_ms(1000);
        }
}
