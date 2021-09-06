/************************************************************************************************************
 * Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.
 * After program start green LED (STAT) will blink, when jumper LED_E is closed.
 *
 * Running Release code will set ReadOutProtection (see down) via function FLASH_ReadOutProtection_Enable().
 * Do not run Release code until you know how to set back ReadOutProtection!
 ************************************************************************************************************/

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_flash.h"

void FLASH_ReadOutProtection_Enable(void);
void DelayByDiv(void);

int main(int argc, char *argv[])
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// GPIOC Periph clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	// Configure PC12 to mode: slow rise-time, pushpull output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // GPIO No. 12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // slow rise time
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // push-pull output
	GPIO_Init(GPIOC, &GPIO_InitStructure); // GPIOC init

	FLASH_ReadOutProtection_Enable(); // enable ReadOutProtection when running Release code

	while(1)
	{
		GPIOC->BSRR = GPIO_BSRR_BS12; // GPIO PC12 set, pin=high, LED STAT off
		//GPIO_WriteBit(GPIOC,GPIO_Pin_12,Bit_SET); // GPIO PC12 set, pin=high, LED STAT off

		DelayByDiv(); // delay --> not much compiler optimizer settings dependent

		GPIOC->BSRR  = GPIO_BSRR_BR12; // GPIO PC12 reset, pin=low, LED STAT on
		//GPIO_WriteBit(GPIOC,GPIO_Pin_12,Bit_RESET); // GPIO PC12 reset, pin=low, LED STAT on

		DelayByDiv(); // delay --> not much compiler optimizer settings dependent
	}
}

void FLASH_ReadOutProtection_Enable(void)
// If FLASH readout protection not already set, enable protection and reset device
//
// NOTES: The user area of the Flash memory can be protected against read by untrusted code.
//        Protection is enabled only for firmware compiled with flag RELEASE_PUBLIC set (see makefile).
//        When readout protection is set debugging via JTAG is not possible any more.
//	  If the read protection is set while the debugger is still connected through JTAG/SWD, apply a
//        POR (power-on reset) instead of a system reset (without debugger connection).
{
	if (FLASH_GetReadOutProtectionStatus() != SET)
	{
		#ifdef RELEASE_PUBLIC // HINT: define is done via makefile
			FLASH_Unlock();
			if (FLASH_ReadOutProtection(ENABLE) != FLASH_COMPLETE) // set readout protection
			{
				// ERROR: could not program read protection
			}
			else
				NVIC_SystemReset(); // protection set --> reset device to enable protection
		#else
				// output warning message
		#endif
	}
}

void DelayByDiv(void)
// delay implemented by floating division
// not much compiler optimizer settings dependent
{
	float x=50.0f;

	while (x > 0.0001f)
		x = x/1.0001f; // delay loop
}
