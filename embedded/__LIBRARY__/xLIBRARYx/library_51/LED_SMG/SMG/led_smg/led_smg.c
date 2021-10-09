#include "led_smg.h"

/* % 4位数码管动态刷新显示 */
void smg_display(void)
{
	/* % static用它来定义i为静态局部变量 */
	/* % 它只初始化一次，下次再进入这个函数，就不在初始化了 */
	/* % 而是保存的是i上一次调用时的值 */
	static uint8_t i = 0;
	switch (i)
	{
	case 0:             /* % 第 1 位数码管 */
		/* % 段码 */
		SMG_SEG = smg_seg_code[led_buf[0]];
		/* % 位选 */
		SMG_BIT = smg_bit_code[0];
		/* % 延时 */
		delay_ms(1);
		/* % 消隐 */
		SMG_SEG = 0x00;
		i++;
		break;
	case 1:             /* % 第 2 位数码管 */
		SMG_SEG = smg_seg_code[led_buf[1]];
		SMG_BIT = smg_bit_code[1];
		delay_ms(1);
		SMG_SEG = 0x00;
		i++;
		break;
	case 2:             /* % 第 3 位数码管 */
		SMG_SEG = smg_seg_code[led_buf[2]];
		SMG_BIT = smg_bit_code[2];
		delay_ms(1);
		SMG_SEG = 0x00;
		i++;
		break;
	case 3:             /* % 第 4 位数码管 */
		SMG_SEG = smg_seg_code[led_buf[3]];
		SMG_BIT = smg_bit_code[3];
		delay_ms(1);
		SMG_SEG = 0x00;
		i = 0;
		break;
	default: 
		break;
	}
}


/* % 分时显示多个窗口，数码管动态刷新 */
/* % 定义4个窗口， 分时刷新显示 */
void smg_more_window_display(void)
{
	uint16_t i;
	switch (window)
	{
	case 0:                        /* % 窗口 1 */
		led_buf[0] = 0;         /* % 第一个数码管显示“0”, 表示第1个窗口 */
		led_buf[1] = 22;        /* % 第二个数码管显示“-” */
		led_buf[2] = parm1/10;  /* % 第三个数码管显示“” */
		led_buf[3] = parm1%10;  /* % 第四个数码管显示“” */
		for (i = 0; i < 5000; i++)
			smg_display();  /* % 动态刷新四个数码管显示“” */
		window++;               /* % 跳转到下一个窗口 */
		break;
	case 1:                         /* % 窗口 2 */
		led_buf[0] = 1;         /* % 第一个数码管显示“1”, 表示第2个窗口 */
		led_buf[1] = 22;        /* % 第二个数码管显示“-” */
		led_buf[2] = parm2/10;  /* % 第三个数码管显示“” */
		led_buf[3] = parm2%10;  /* % 第四个数码管显示“” */
		for (i = 0; i < 5000; i++)
			smg_display();  /* % 动态刷新四个数码管显示“” */
		window++;               /* % 跳转到下一个窗口 */
		break;
	case 2:                         /* % 窗口 3 */
		led_buf[0] = 2;         /* % 第一个数码管显示“2”, 表示第3个窗口 */
		led_buf[1] = 22;        /* % 第二个数码管显示“-” */
		led_buf[2] = parm3/10;  /* % 第三个数码管显示“” */
		led_buf[3] = parm3%10;  /* % 第四个数码管显示“” */
		for (i = 0; i < 5000; i++)
			smg_display();  /* % 动态刷新四个数码管显示“” */
		window++;               /* % 跳转到下一个窗口 */
		break;
	case 3:                         /* % 窗口 4 */
		led_buf[0] = 3;         /* % 第一个数码管显示“3”, 表示第4个窗口 */
		led_buf[1] = 22;        /* % 第二个数码管显示“-” */
		led_buf[2] = parm4/10;  /* % 第三个数码管显示“” */
		led_buf[3] = parm4%10;  /* % 第四个数码管显示“” */
		for (i = 0; i < 5000; i++)
			smg_display();  /* % 动态刷新四个数码管显示“” */
		window = 0;             /* % 跳转到第一个窗口 */
		break;
	default: 
		break;
	}
}
