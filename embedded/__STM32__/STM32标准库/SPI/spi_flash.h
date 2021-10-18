#ifndef __SPI_H__
#define __SPI_H__
//NSS引脚配置
#define SPI_NSS_PORT            GPIOA
#define SPI_NSS_PIN             GPIO_Pin_4
#define SPI_NSS_HIGH()          GPIO_SetBits(SPI_NSS_PORT, SPI_NSS_PIN);
#define SPI_NSS_LOW()           GPIO_ResetBits(SPI_NSS_PORT, SPI_NSS_PIN);

#define SPI_SCLK_PORT           GPIOA
#define SPI_SCLK_PIN            GPIO_Pin_5  
        
#define SPI_MOSI_PORT           GPIOA
#define SPI_MOSI_PIN            GPIO_Pin_7

#define SPI_MISO_PORT           GPIOA
#define SPI_MISO_PIN            GPIO_Pin_6
#endif
