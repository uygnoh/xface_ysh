#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"

GPIO_InitTypeDef iIt;

int main(void)
{
	volatile int i;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	iIt.GPIO_Mode=GPIO_Mode_OUT;
	iIt.GPIO_OType=GPIO_OType_PP;
	iIt.GPIO_Speed=GPIO_Speed_50MHz;
	iIt.GPIO_PuPd=GPIO_PuPd_UP;
	iIt.GPIO_Pin=GPIO_Pin_5;
	
	GPIO_Init(GPIOA,&iIt);
	
	for(;;){
		GPIOA->BSRR=GPIO_Pin_5;
		for(i=0;i<720000;i++);
		GPIOA->BRR=GPIO_Pin_5;
		for(i=0;i<720000;i++);
	}
	return 0;
}

void _exit(int status)
{
}



