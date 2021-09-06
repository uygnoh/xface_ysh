#ifndef __W25Q64_H__
#define __W25Q64_H__

#include <stdio.h>
#include "stm32f1xx.h"

/* FLASH_W25Q器件地址宏定义 */
//#define sFLASH_ID	0xEF3015 //W25X16
//#define sFLASH_ID	0xEF4015 //W25Q16
//#define sFLASH_ID	0XEF4018 //W25Q128
#define   sFLASH_ID	0XEF4017 //W25Q64
/* FLASH_W25Q器件页宏定义 */
#define PER_PAGE_SIZE	256	//1页为256字节
#define PAGE_SIZE	256	//1页为256字节


/* FLASH_W25Q命令定义-开头*******************************/
#define W25X_WRITE_ENABLE		0x06 //写使能
#define W25X_WRITE_DIABLE		0x04 //禁止写入 
#define W25X_READ_STATUS_REG		0x05 //读状态寄存器 
#define W25X_WRITE_STATUS_REG		0x01 //写状态寄存器  
#define W25X_READ_DATA			0x03 //读数据 
#define W25X_FAST_READ_DATA		0x0B //快速读数据 
#define W25X_FAST_READ_DUAL		0x3B // 
#define W25X_PAGE_PROGRAM		0x02 //页编程 
#define W25X_BLOCK_ERASE		0xD8 //块擦除 
#define W25X_SECTOR_ERASE		0x20 //扇区擦除 
#define W25X_CHIP_ERASE			0xC7 //芯片擦除 
#define W25X_POWER_DOWN			0xB9 //掉电模式 
#define W25X_RELEASE_POWER_DOWN		0xAB // 
#define W25X_DEVICE_ID			0xAB // 
#define W25X_MANUFACT_DEVICE_ID		0x90 // 
#define W25X_JEDEC_DEVICE_ID		0x9F //
/* FLASH_W25Q命令定义-结尾*******************************/
#define BUSY_FLAG			0x01 //读忙标志  
#define DUMMY_BYTE			0xFF //伪字节


/*SPI接口定义-开始****************************/
#define SPIX				SPI1
#define SPIX_CLK_ENABLE()		__HAL_RCC_SPI1_CLK_ENABLE()
#define SPIX_SCK_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIX_MISO_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE() 
#define SPIX_MOSI_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE() 
#define SPIX_CS_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE() 
#define SPIX_FORCE_RESET()		__HAL_RCC_SPI1_FORCE_RESET()
#define SPIX_RELEASE_RESET()		__HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIX Pins */
#define FLASH_CS_PIN		GPIO_PIN_4               
#define FLASH_CS_GPIO_PORT	GPIOA   
#define SPIX_SCK_PIN		GPIO_PIN_5
#define SPIX_SCK_GPIO_PORT	GPIOA
#define SPIX_MISO_PIN		GPIO_PIN_6
#define SPIX_MISO_GPIO_PORT	GPIOA
#define SPIX_MOSI_PIN		GPIO_PIN_7
#define SPIX_MOSI_GPIO_PORT	GPIOA

#define	HIGH_LEVEL(p,i)		{p->BSRR = i;} //设置为高电平		
#define LOW_LEVEL(p,i)		{p->BSRR = (uint32_t)i << 16;}//输出低电平
#define SPI_FLASH_CS_LOW()	digitalLo(FLASH_CS_GPIO_PORT,FLASH_CS_PIN)
#define SPI_FLASH_CS_HIGH()	digitalHi(FLASH_CS_GPIO_PORT,FLASH_CS_PIN)
/*SPI接口定义-结尾****************************/


/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT	((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT	((uint32_t)(10 * SPIT_FLAG_TIMEOUT))


/*信息输出*/
#define FLASH_DEBUG_ON		1
#define FLASH_INFO(fmt,arg...)	printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)	printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)	do {			\
				if (FLASH_DEBUG_ON)	\
				printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
				} while (0)
#endif
