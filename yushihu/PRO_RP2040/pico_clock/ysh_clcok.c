#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"


void measure_freqs(void)
{
        uint f_pll_sys  = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
        uint f_pll_usb  = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
        uint f_rosc     = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
        uint f_clk_sys  = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
        uint f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
        uint f_clk_usb  = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
        uint f_clk_adc  = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
        uint f_clk_rtc  = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);
        
        printf("pll_sys         = %dKHz\n", f_pll_sys);
        printf("pll_usb         = %dKHz\n", f_pll_usb);
        printf("rosc            = %dKHz\n", f_rosc);
        printf("clk_sys         = %dKHz\n", f_clk_sys);
        printf("clk_peri        = %dKHz\n", f_clk_peri);
        printf("clk_usb         = %dKHz\n", f_clk_usb);
        printf("clk_adc         = %dKHz\n", f_clk_adc);
        printf("clk_rtc         = %dKHz\n", f_clk_rtc);
}


int main(void)
{
        stdio_init_all();
        
        while (1) {
                measure_freqs();
                sleep_ms(1000);
        }
}
