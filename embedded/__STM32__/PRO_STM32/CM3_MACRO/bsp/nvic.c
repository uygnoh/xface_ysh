#include "nvic.h"


/*---------------------------------------------------------------------------*/
/** @brief 设置中断优先级组
 * 31:16 (访问钥匙密)任何对该寄存器的写操作,都必须同时写入“0x05FA”
 * 10:8  (优先级分组)指定先占优先级和从优先级位数
Cortex-M3共有8位可配置的优先级，但STM32F10x只用到“高”4位
 * 111   (0位抢占优先级, 4位响应优先级)	7
 * 110   (1位抢占优先级, 3位响应优先级)	6
 * 101   (2位抢占优先级, 2位响应优先级)	5
 * 100   (3位抢占优先级, 1位响应优先级)	4
 * 011   (4位抢占优先级, 0位响应优先级)	3
 */
void nvic_set_priority_group(void)
{
	/* 清除高16位和低(10,9,8)位 */ 
	SCB->AIRCR &= (uint32_t)(0x0000F8FF);
	/* 2位抢占优先级, 2位响应优先级 */
	SCB->AIRCR |= (uint32_t)(0x05FA0000 | 0x00000500);
}

/** @brief 设置外部中断的先占优先级和从优先级
 * @param[in] uint8_t irq, 选择外部中断编号
 * @param[in] uint8_t priority, 设置它对应的先占优先级和从优先级
 */
void nvic_set_irq_priority(uint8_t irq, uint8_t priority)
{
	NVIC->IP[irq] = priority;
}



/*---------------------------------------------------------------------------*/
/** @brief NVIC Enable Interrupt
 *
 * Enables a user interrupt.
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 */
void nvic_enable_irq(uint8_t irqn)
{
	NVIC->ISER[irqn / 32] = (1 << (irqn % 32));
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Disable Interrupt
 *
 * Disables a user interrupt.
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 */
void nvic_disable_irq(uint8_t irqn)
{
	NVIC->ICER[irqn / 32] = (1 << (irqn % 32));
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Return Pending Interrupt
 *
 * True if the interrupt has occurred and is waiting for service.
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 * @return Boolean. Interrupt pending.
 */
uint8_t nvic_get_pending_irq(uint8_t irqn)
{
	return NVIC->ISPR[irqn / 32] & (1 << (irqn % 32)) ? 1 : 0;
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Set Pending Interrupt
 *
 * Force a user interrupt to a pending state. This has no effect if the
 * interrupt is already pending.
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 */
void nvic_set_pending_irq(uint8_t irqn)
{
	NVIC->ISPR[irqn / 32] = (1 << (irqn % 32));
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Clear Pending Interrupt
 *
 * Force remove a user interrupt from a pending state. This has no effect if
 * the interrupt is actively being serviced.
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 */
void nvic_clear_pending_irq(uint8_t irqn)
{
	NVIC->ICPR[irqn / 32] = (1 << (irqn % 32));
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Return Enabled Interrupt
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 * @return Boolean. Interrupt enabled.
 */
uint8_t nvic_get_irq_enabled(uint8_t irqn)
{
	return NVIC->ISER[irqn / 32] & (1 << (irqn % 32)) ? 1 : 0;
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Return Active Interrupt
 *
 * Interrupt has occurred and is currently being serviced.
 *
 * @param[in] irqn Unsigned int8. Interrupt number
 * @return Boolean. Interrupt active.
 */
uint8_t nvic_get_active_irq(uint8_t irqn)
{
	return NVIC->IABR[irqn / 32] & (1 << (irqn % 32)) ? 1 : 0;
}

/*---------------------------------------------------------------------------*/
/** @brief NVIC Software Trigger Interrupt
 *
 * Generate an interrupt from software. This has no effect for unprivileged
 * access unless the privilege level has been elevated through the System
 * Control Registers.
 *
 * @param[in] irqn Unsigned int16. Interrupt number (0 ... 239)
 */
void nvic_generate_software_interrupt(uint16_t irqn)
{
	if (irqn <= 239) {
		NVIC->STIR |= irqn;
	}
}



/*---------------------------------------------------------------------------*/
/* SysTick有两种获得系统时钟的方式
(一种是直接取自系统时钟，另一种是将系统时钟8分频)
 * SysTick->CTRL    
 16 COUNTFLAG
 2  CLKSOURCE   0=系统时钟8分频 1=系统时钟(FCLK)
 1  TICKINT     1=SysTick 倒数到 0 时产生 SysTick 异常请求
 0  ENABLE      SysTick 定时器的使能位
 * SysTick->LOAD
   当倒计数到“0”时，将被重装载的值
 * SysTick->VAL     
   当前数值寄存器( 读取时返回当前倒计数的值，写它则使之清零， 
   同时还会清除在 SysTick 控制及状态寄存器COUNTFLAG标志 )
 * SysTick->CALIB   校准数值寄存器
 */
// 1微秒延时 SysTick = @系统时钟为72MHz / 8
void delay_us(uint32_t t)
{
	uint32_t tmp;

	SysTick->LOAD = 9 * t;
	SysTick->VAL  = 0x00;
	/* 启动SysTick计数器 */
	SysTick->CTRL = 0x01;
	/* 判断(COUNTFLAG)这个标志位的值 */
	do {
		tmp = SysTick->CTRL;
	} while ((tmp & 0x01) && (!(tmp & (1 << 16))));

	SysTick->CTRL = 0x00;
	SysTick->VAL  = 0x00;
}

void delay_ms(uint32_t t)
{
	uint32_t tmp;

	SysTick->LOAD = 9000 * t;
	SysTick->VAL  = 0x00;
	/* 启动SysTick计数器 */
	SysTick->CTRL = 0x01;
	/* 判断(COUNTFLAG)这个标志位的值 */
	do {
		tmp = SysTick->CTRL;
	} while ((tmp & 0x01) && (!(tmp & (1 << 16))));

	SysTick->CTRL = 0x00;
	SysTick->VAL  = 0x00;
}
