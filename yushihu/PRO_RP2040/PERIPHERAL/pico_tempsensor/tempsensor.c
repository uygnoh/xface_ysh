#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main(void)
{
        stdio_init_all();
        
        // 配置ADC
        adc_init();
        adc_set_temp_sensor_enabled(true);
        adc_select_input(4);
        
        // Infinite Loop
        while (1) {
                uint16_t raw = adc_read();
                const float conversion = 3.3f / (1<<12);
                float voltage = raw * conversion;
                float temperature = 27 - (voltage - 0.706) / 0.001721;
                printf("Temperature: %f c\n", temperature);
                sleep_ms(1000);
        }
}
