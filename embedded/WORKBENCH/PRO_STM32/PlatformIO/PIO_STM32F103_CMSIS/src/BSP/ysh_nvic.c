    #include "ysh_nvic.h"
    
    void nvic_init(void)
    {
        /* % (设置优先级分组为第“3”组)3位抢占优先级, 1位响应优先级 */
        SCB->AIRCR      = (uint32_t)(0x05FA0000 | 0x00000400); 
        /* % 设置通用定时器“2”中断优先级(抢占优先级为7，响应优先级为1) */  
        NVIC->IP[28]    = (uint8_t)0xF0;
        /* % 打开通用定时器“2”中断 */  
        NVIC->ISER[0]   = (uint32_t)0x10000000;
    }

