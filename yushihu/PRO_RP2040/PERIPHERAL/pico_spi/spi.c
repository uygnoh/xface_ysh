#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define MISO            16
#define CS              17
#define SCLK            18
#define MOSI            19
#define SPI_PORT        spi0

int main(void)
{
        stdio_init_all();
        gpio_init(CS);                          // Initialise CS pin
        gpio_set_dir(CS, GPIO_OUT);             // Set CS as output
        gpio_put(CS, 1);                        // Set CS high to indicate no currect SPI communication
        
        spi_init(SPI_PORT, 1 * 1000 * 1000);    // 1MHz
        spi_set_format( SPI_PORT,               // SPI instance
                        8,                      // Number of bits per transfer
                        1,                      // poalrity(CPOL)
                        1,                      // Phase(CPHA)
                        SPI_MSB_FIRST);
        gpio_set_function(MISO, GPIO_FUNC_SPI);
        gpio_set_function(SCLK, GPIO_FUNC_SPI);
        gpio_set_function(MOSI, GPIO_FUNC_SPI);
        


        

        
        // Write Operation Example!
        uint8_t data[2];
        data[0] = 0xF4 & 0x7F;
        data[1] = 0x27;
        gpio_put(CS, 0);        // Indicate beginning of communication
        spi_write_blocking(SPI_PORT, data, 2);
        gpio_put(CS, 1);        // Signal end ov communication
}
