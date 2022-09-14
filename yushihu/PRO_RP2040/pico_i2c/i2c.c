#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT        i2c0

static int addr = 0x28;

void setup(void)
{
        // Check to see if connection is correct
        sleep_ms(1000);
        uint8_t reg = 0x00;
        uint8_t chip_id[1];
        i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
        i2c_read_blocking(I2C_PORT, addr, chip_id, 1, false);
        
        if (chip_id[0] != 0xA0) {
                printf("Chip ID Not Correct - Check Connection!");
                sleep_ms(5000);
        }
        
        // Use internal Oscillator
        uint8_t data[2];
        data[0] = 0x3F;
        data[1] = 0x40;
        i2c_write_blocking(I2C_PORT, addr, data, 2, true);
}

int main(void)
{
        stdio_init_all();

        i2c_init(I2C_PORT, 400000);             // 配置I2C， 通信速率为（400K）
        gpio_set_function(4, GPIO_FUN_I2C);     // 配置（GPIO4）为I2C功能
        gpio_set_function(5, GPIO_FUN_I2C);     // 配置（GPIO5）为I2C功能
        gpio_pull_up(4);
        gpio_pull_up(5);
        
        setup();
}
