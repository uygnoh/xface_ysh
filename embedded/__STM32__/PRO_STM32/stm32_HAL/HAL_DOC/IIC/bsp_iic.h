#ifndef __BSP_IIC_H__
#define __BSP_IIC_H__

// AT24C01/02每页有8个字节
#define EEPROM_PAGESIZE     8

// 主机地址(这个地址只要与STM32外挂的I2C器件地址不一样即可)
#define I2C_OWN_ADDRESS7    0x0A

// 从机地址(AT2402)
#define EEPROM_ADDRESS      0xA0

#define I2Cx                            I2C1
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define I2Cx_SDA_FORCE_RESET()          __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()


#define I2Cx_SCL_PIN                    GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_7
#define I2Cx_SDA_GPIO_PORT              GPIOB
#endif

