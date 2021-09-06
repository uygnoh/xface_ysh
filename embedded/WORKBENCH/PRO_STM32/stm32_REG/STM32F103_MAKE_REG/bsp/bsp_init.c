#include "bsp_init.h"

void rcc_init(void)
{
	/* 内部高速时钟初始化 */
	rcc_default();
	/* 设置系统时钟为: 外部高速时钟(72MHz) */
	set_clock_hse72();


	#ifdef TIM2_CONF
	/* 打开“AFIO”时钟(辅助功能IO时钟使能) */
	RCC->APB2ENR |= (uint32_t)RCC_APB2ENR_AFIOEN;
	/* 打开“GPIOC”时钟 */
	RCC->APB2ENR |= (uint32_t)RCC_APB2ENR_IOPCEN;
	/* 打开“通用定时器2”时钟 */
	RCC->APB1ENR |= (uint32_t)RCC_APB1ENR_TIM2EN;
	#endif
}

void nvic_init(void)
{
	/* % (设置优先级分组为第“3”组)3位抢占优先级, 1位响应优先级 */
	SCB->AIRCR      = (uint32_t)(0x05FA0000 | 0x00000400); 
	/* % 设置通用定时器“2”中断优先级(抢占优先级为7，响应优先级为1) */  
	NVIC->IP[28]    = (uint8_t)0xF0;
	/* % 打开通用定时器“2”中断 */  
	NVIC->ISER[0]   = (uint32_t)0x10000000;
}

void gpio_init(void)
{
	/* (stm32f103c8t6)_GPIO_PC13_测试程序 */
	#ifdef GPIO_LED_TEST
	/* PC_13端口配置 (通用推挽输出, 速度: 50MHz) */
	GPIOC->CRH = (uint32_t)0x00300000;

	/* 端口位设置/清除寄存器(GPIOx_BSRR) */
	GPIOC->BSRR = (uint32_t)GPIO_BSRR_BS13;
	delay_ms(500);
	GPIOC->BSRR = (uint32_t)GPIO_BSRR_BR13;
	delay_ms(500);
	#endif
}

void tim2_init(void)
{
	/* % 1:TIMx_ARR寄存器被装入缓冲器 */
	TIM2->CR1 |= (uint16_t)TIM_CR1_ARPE;
	/* % 1:计数器向下计数 */
	TIM2->CR1 |= (uint16_t)TIM_CR1_DIR;
	/* % 时钟源选择: 内部时钟源(CK_INT) */
	/* % SMS[2:0] 000:关闭从模式 – 如果CEN=1,则预分频器直接由内部时钟驱动 */
	TIM2->SMCR &= (uint16_t)(~TIM_SMCR_SMS);

	/* % 预分频器 */
	TIM2->PSC = (uint16_t)(7200-1);
	/* % 自动重装载寄存器 */
	TIM2->ARR = (uint16_t)(1000-1);
	/* % 计数器清零 */
	TIM2->CNT = (uint16_t)0x0000;
	/* 1:使能触发中断 */
	TIM2->DIER |= (uint16_t)TIM_DIER_TIE;
	TIM2->DIER |= (uint16_t)TIM_DIER_UIE;

	/* % 打开计数器"2" */
	TIM2->CR1 |= (uint16_t)TIM_CR1_CEN;

}
