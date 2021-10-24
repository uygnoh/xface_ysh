#include "stm32f10x.h"

/*******************************************************************************
  函数名称: void PC13_TEST(void)
  输入参数: 无
  输出参数: 无
  函数功能: GPIO—pc13_led_test测试
*******************************************************************************/
void pc13_led_test(void)
{
	uint8_t i;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef PORT;
	PORT.GPIO_Pin      = GPIO_Pin_13;      //端口选择
	PORT.GPIO_Speed    = GPIO_Speed_50MHz; //速度设置
	PORT.GPIO_Mode     = GPIO_Mode_Out_PP; //推挽输出
	GPIO_Init(GPIOC, &PORT);

	for (i = 0; i < 9; i++) {
		PC_OUT(13) = 0;
		delay_ms(1000);
		PC_OUT(13) = 1;
		delay_ms(1000);
	}
}


int main(void)
{
	pc13_led_test();
	while (1) {
	}
	return 0;
}

