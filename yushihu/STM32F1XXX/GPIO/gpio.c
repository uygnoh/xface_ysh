#include "gpio.h"

#define GPIOX           (GPIOA)


void gpio_setup(void)
{
        #if USE_GPIOX_CRL
        // 通用输入输出端口模式配置（PIN0 ~ PIN7）
        // GPIO_CRL[ 复位值 : 0x4444 4444 ] // 端口配置低寄存器 //
        // _____________________________________________________________________
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 0 );    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 0 );    // PA_0
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 4 );    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 4 );    // PA_1
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // PA_2
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 12);    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 12);    // PA_3
        
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 16);    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 16);    // PA_4
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 20);    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 20);    // PA_5
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 24);    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 24);    // PA_6
        GPIOX->CRL      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 28);    // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 28);    // PA_7
        #endif
        
        
        #if USE_GPIOX_CRH
        // 通用输入输出端口模式配置（PIN8 ~ PIN15）
        // GPIO_CRH[ 复位值 : 0x4444 4444 ] // 端口配置高寄存器 //
        // _____________________________________________________________________
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 0 );    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 0 );    // PA_8
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 4 );    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 4 );    // PA_9
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // PA_10
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 12);    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 12);    // PA_11
        
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 16);    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 16);    // PA_12
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 20);    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 20);    // PA_13
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 24);    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 24);    // PA_14
        GPIOX->CRH      &= ~(GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 28);    // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 28);    // PA_15
        #endif
        
        
        #if AFIO_MAPR
        // STM32F1XXX 端口重映射配置
        // AFIO_MAPR [ 复位值 : 0x0000 0000 ] // 复用重映射和调试I/O配置寄存器 //
        // _____________________________________________________________________
        AFIO->MAPR      = (0x00000000)       // SWJ_CFG[26:24] = 000 
                                             // 完全SWJ(JTAG-DP + SW-DP): 复位状态
        #endif
}
