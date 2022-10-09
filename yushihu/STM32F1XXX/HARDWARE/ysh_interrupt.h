#ifndef __YSH_INTERRUPT_H__
#define __YSH_INTERRUPT_H__

#include "ysh_config.h"
void nvic_setup(void);


/*******************************************************************************
        => System Control Block (SCB)
*******************************************************************************/
//
//  中断优先级分组寄存器， STM32F1XX只用到了第7位到第4位
// ____________________________________________________________
//  组名   |    寄存器配置    | 分配结果
// ._______________________________________.
// | GRP  | SCB->AIRC[10:8] |   IPR[7:4]   |       分配结果
// |______|_________________|______________|____________________________.
// |  0   |       111       |     0:4      |  0位抢占优先级, 4位响应优先级  |  7
// |  1   |       110       |     1:3      |  1位抢占优先级, 3位响应优先级  |  6
// |  2   |       101       |     2:2      |  2位抢占优先级, 2位响应优先级  |  5
// |  3   |       100       |     3:1      |  3位抢占优先级, 1位响应优先级  |  4
// |  4   |       011       |     4:0      |  4位抢占优先级, 0位响应优先级  |  3
// |______|_________________|______________|_____________________________.
// (uint32_t)(0x05FA0000)               // 访问密钥
#define SCB_AIRCR_VECTKEY               (uint32_t)(0x05FA0000)
#define PRIORITY_GROUP_00               (uint32_t)(0x05FA0700)
#define PRIORITY_GROUP_01               (uint32_t)(0x05FA0600)
#define PRIORITY_GROUP_02               (uint32_t)(0x05FA0500)
#define PRIORITY_GROUP_03               (uint32_t)(0x05FA0400)
#define PRIORITY_GROUP_04               (uint32_t)(0x05FA0300)



// 系统异常优先级寄存器
// ____________________________________________________________
// SCB->SHP[11] = 0xF0;         // 设置SYSTICK的优先级为15，注意SYSTICK
                                // 属于系统异常，所以他的优先级在SCB里设置



// 0xE000_ED04 中断控制及状态寄存器
// ____________________________________________________________
//      PENDSVSET[28]           // 写 1 以悬起 PendSV
//      PENDSVCLR[27]           // 写 1 以清除 PendSV
//      PENDSTSET[26]           // 写 1 以悬起 SysTick
//      PENDSTCLR[25]           // 写 1 以清除 SysTick



/*******************************************************************************
        => Nested Vectored Interrupt Controller (NVIC)
*******************************************************************************/
//      __I     // defines 'read only' permissions      定义只读允许位
//      __O     // defines 'write only' permissions     定义只写允许位
//      __IO    // defines 'read / write' permissions   定义读/写允许位
//
//
// typedef struct {
//      __IOM uint32_t ISER[8U];  //  0x000 (R/W)  中断开启
//      uint32_t RESERVED0[24U];
//      __IOM uint32_t ICER[8U];  //  0x080 (R/W)  中断关闭
//      uint32_t RSERVED1[24U];
//      __IOM uint32_t ISPR[8U];  //  0x100 (R/W)  中断请求设置
//      uint32_t RESERVED2[24U];
//      __IOM uint32_t ICPR[8U];  //  0x180 (R/W)  中断请求清除
//      uint32_t RESERVED3[24U];
//      __IOM uint32_t IABR[8U];  //  0x200 (R/W)  中断活动位
//      uint32_t RESERVED4[56U];
//      __IOM uint8_t  IP[240U];  //  0x300 (R/W)  中断优先级 (8Bit wide)
//      uint32_t RESERVED5[644U];
//      __OM  uint32_t STIR;      //  0xE00 ( /W)  软件触发中断
// } NVIC_Type;



// 外部中断使能， 共有8个32位寄存器， 寄存器中的每个位代表一个中断号
//_____________________________________________________________
// NVIC->ISER[0] |= (1 << (28 - (32*0));        // TIM2 中断使能 : IRQn = 28
// NVIC->ISER[0] |= (1 << (31 - (32*0));        // IC1  事件中断 : IRQn = 31
// NVIC->ISER[1] |= (1 << (50 - (32*1));        // TIM5 中断使能 : IRQn = 50
//
//
// STM32F1XX只用到了第7位到第4位， 低4位没有用到
// 外部中断优先级配置寄存器（共有240个， 每个占用8位）
//_____________________________________________________________
// NVIC->IP[28] = uint8_t(0xF0);        // TIM2 中断优先级设置
// NVIC->IP[50] = uint8_t(0xF0);        // TIM5 中断优先级设置



/*******************************************************************************
        =>  EXTI
*******************************************************************************/
// AFIO_EXTI
// ____________________________________________________________
// 下面这4个寄存器都只用到了低（16位）， 第个端口用到了（4位）， 分别对应： A， B， ... G
// External interrupt configuration register 1 (AFIO_EXTICR1) // EXTI0  ~ EXTI3
// External interrupt configuration register 2 (AFIO_EXTICR2) // EXTI4  ~ EXTI7
// External interrupt configuration register 3 (AFIO_EXTICR3) // EXTI8  ~ EXTI11
// External interrupt configuration register 4 (AFIO_EXTICR4) // EXTI12 ~ EXTI15
// Example:
//      AFIO_EXTICR1 = (1 << 0);        // 对应 PB0
//      AFIO_EXTICR1 = (3 << 0);        // 对应 PD0
//
//      AFIO_EXTICR1 = (1 << 4);        // 对应 PB1
//      AFIO_EXTICR1 = (3 << 4);        // 对应 PD1



// External interrupt/event controller (EXTI)
// ____________________________________________________________
// Interrupt mask register (EXTI_IMR)                   // 中断屏蔽寄存器
//      0: Interrupt request from Line x is masked      //
//      1: Interrupt request from Line x is not masked  //
// Event mask register (EXTI_EMR)                       // 事件屏蔽寄存器
//      0: Event request from Line x is masked          //
//      1: Event request from Line x is not masked      //
// Rising trigger selection register (EXTI_RTSR)        // 上升沿触发选择寄存器
//      0: 禁止输入线x上的上升沿触发(中断和事件)            //
//      1: 允许输入线x上的上升沿触发(中断和事件)            //
// Falling trigger selection register (EXTI_FTSR)       // 下降沿触发选择寄存器
//      0: 禁止输入线x上的下降沿触发(中断和事件)            //
//      1: 允许输入线x上的下降沿触发(中断和事件)            //
// Software interrupt event register (EXTI_SWIER)       // 软件中断事件寄存器
//      当该位为 【0】 时， 写 【1】 将设置EXTI_PR中相应的挂起位//
//      如果在EXTI_IMR和EXTI_EMR中允许产生该中断或事件, 则此时将产生一个中断或事件
//      注: 通过清除EXTI_PR的对应位(写入【1】)， 可以清除该位为【0】
//                                                      //
// Pending register (EXTI_PR)                           // 挂起寄存器
//      0:没有发生触发请求
//      1:发生了选择的触发请求
//      当在外部中断线上发生了选择的边沿事件, 该位被置’1’。 在该位中写入’1’可以清除它
//
//
//
#endif
