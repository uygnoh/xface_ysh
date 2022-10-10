#include "ysh_gpio.h"


void gpio_setup(void)
{
        // GPIO 模式配置
        // ____________________________________________________
        //GPIOA->CRL      &=  (GPIO_CONF_CLR_02);                         // ^0
        //GPIOA->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // PA_2
        GPIOA->CRL      &=  (0xFFFF0000);       // PA0 - aIN-0 模拟输入通道0
                                                // PA1 - aIN-1 模拟输入通道0
                                                // PA2 - aIN-2 模拟输入通道0
                                                // PA3 - aIN-3 模拟输入通道0


        #if GPIO_CRL_XXX
        // 通用输入输出端口模式配置（PIN0 ~ PIN7）
        // GPIO_CRL[ 复位值 : 0x4444 4444 ] // 端口配置低寄存器 //
        GPIOX->CRL      &= ~(uint32_t)(0xF << 0 );      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 0 );    // PA_0
        GPIOX->CRL      &= ~(uint32_t)(0xF << 4 );      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 4 );    // PA_1
        GPIOX->CRL      &= ~(uint32_t)(0xF << 8 );      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // PA_2
        GPIOX->CRL      &= ~(uint32_t)(0xF << 12);      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 12);    // PA_3
        GPIOX->CRL      &= ~(uint32_t)(0xF << 16);      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 16);    // PA_4
        GPIOX->CRL      &= ~(uint32_t)(0xF << 20);      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 20);    // PA_5
        GPIOX->CRL      &= ~(uint32_t)(0xF << 24);      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 24);    // PA_6
        GPIOX->CRL      &= ~(uint32_t)(0xF << 28);      // ^0
        GPIOX->CRL      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 28);    // PA_7
        #endif
        
        #if GPIO_CRH_XXX
        // 通用输入输出端口模式配置（PIN8 ~ PIN15）
        // GPIO_CRH[ 复位值 : 0x4444 4444 ] // 端口配置高寄存器 //
        GPIOX->CRH      &= ~(uint32_t)(0xF << 0 );      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 0 );    // PA_8
        GPIOX->CRH      &= ~(uint32_t)(0xF << 4 );      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 4 );    // PA_9
        GPIOX->CRH      &= ~(uint32_t)(0xF << 8 );      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 8 );    // PA_10
        GPIOX->CRH      &= ~(uint32_t)(0xF << 12);      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 12);    // PA_11
        GPIOX->CRH      &= ~(uint32_t)(0xF << 16);      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 16);    // PA_12
        GPIOX->CRH      &= ~(uint32_t)(0xF << 20);      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 20);    // PA_13
        GPIOX->CRH      &= ~(uint32_t)(0xF << 24);      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 24);    // PA_14
        GPIOX->CRH      &= ~(uint32_t)(0xF << 28);      // ^0
        GPIOX->CRH      |=  (GPIO_MODE_OUTPUT_PUSHPULL_50MHZ << 28);    // PA_15
        #endif
        
        #if AFIO_MAPR_XXX
        // STM32F1XXX 端口重映射配置
        // AFIO_MAPR [ 复位值 : 0x0000 0000 ] // 复用重映射和调试I/O配置寄存器 //
        AFIO->MAPR      = (0x00000000)       // SWJ_CFG[26:24] = 000 
                                             // 完全SWJ(JTAG-DP + SW-DP): 复位状态
                              
        // JTAG/SWD复用功能重映射
        // _____________________________________________________________________
        // 为了在调试期间可以使用更多GPIOs,通过设置复用重映射和调试I/O配置寄存器(AFIO_MAPR)
        // 的SWJ_CFG[2:0]位, 可以改变下述重映像配置， 调试接口信号
                JTMS/SWDIO              PA13
                JTCK/SWCLK              PA14
                JTDI                    PA15
                JTDO/TRACESWO           PB3
                JNTRST                  PB4
                TRACECK                 PE2
                TRACED0                 PE3
                TRACED1                 PE4
                TRACED2                 PE5
                TRACED3                 PE6
        #endif
}
