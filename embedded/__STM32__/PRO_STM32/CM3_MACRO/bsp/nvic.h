#ifndef __NVIC_H__
#define __NVIC_H__
#include "stm32f10x.h"


void nvic_set_priority_group(void);
void nvic_set_irq_priority(uint8_t irq, uint8_t priority);

void nvic_enable_irq(uint8_t irqn);
void nvic_disable_irq(uint8_t irqn);
uint8_t nvic_get_pending_irq(uint8_t irqn);
void nvic_set_pending_irq(uint8_t irqn);
void nvic_clear_pending_irq(uint8_t irqn);
uint8_t nvic_get_irq_enabled(uint8_t irqn);
uint8_t nvic_get_active_irq(uint8_t irqn);
void nvic_generate_software_interrupt(uint16_t irqn);

void delay_us(uint32_t t);
void delay_ms(uint32_t t);
#endif
