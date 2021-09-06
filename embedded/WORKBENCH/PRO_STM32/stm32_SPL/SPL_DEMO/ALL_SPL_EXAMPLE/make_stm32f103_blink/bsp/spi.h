#ifndef __SPI_H__
#define __SPI_H__

#include "stm32f10x_conf.h"

// SPI pins
#define SPI_CS     pbout(3) 
#define SPI_SCK    pbout(4)
#define SPI_MOSI   pbout(5)
#define SPI_MISO   pbout(6)

// OLED pins
#define OLED_DC    pbout(7)
#define OLED_RESET pbout(8)


void spi_read_write(unsigned char data);

#endif
