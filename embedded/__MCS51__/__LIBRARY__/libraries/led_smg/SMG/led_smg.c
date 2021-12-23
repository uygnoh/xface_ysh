#include "led_smg.h"

/*******************************************************************************
  函数名称: smg_display()
  输入参数: 无
  输出参数: 无
  函数功能: 4位数码管动态刷新显示（延时1ms < 10ms）
*******************************************************************************/
void smg_display(void)
{
        //static用它来定义i为静态局部变量
        //它只初始化一次，下次再进入这个函数，就不在初始化了, 而是保存的是i上一次调用时的值
        static uint8_t i = 0;
        
        switch (i) {
        case 0:                                                 //第 1 位数码管
                SMG_SEG = smg_seg_code[led_buf[0]];             //__数码管__段码
                SMG_BIT = smg_bit_code[0];                      //__数码管__位选
                delay_ms(1);                                    //__数码管__延时
                SMG_SEG = 0x00;                                 //__数码管__消隐
                i++;
                break;
        case 1:                                                 //第 2 位数码管
                SMG_SEG = smg_seg_code[led_buf[1]];             //__数码管__段码
                SMG_BIT = smg_bit_code[1];                      //__数码管__位选
                delay_ms(1);                                    //__数码管__延时
                SMG_SEG = 0x00;                                 //__数码管__消隐
                i++;
                break;
        case 2:                                                 //第 3 位数码管
                SMG_SEG = smg_seg_code[led_buf[2]];             //__数码管__段码
                SMG_BIT = smg_bit_code[2];                      //__数码管__位选
                delay_ms(1);                                    //__数码管__延时
                SMG_SEG = 0x00;                                 //__数码管__消隐
                i++;
                break;
        case 3:                                                 //第 4 位数码管
                SMG_SEG = smg_seg_code[led_buf[3]];             //__数码管__段码
                SMG_BIT = smg_bit_code[3];                      //__数码管__位选
                delay_ms(1);                                    //__数码管__延时
                SMG_SEG = 0x00;                                 //__数码管__消隐
                i = 0;                                          //goto 第1位数码管
                break;
        default: 
                break;
        }
}

/*******************************************************************************
  函数名称: smg_more_window_display()
  输入参数: 无
  输出参数: 无
  函数功能: 分时显示多个窗口，数码管动态刷新
          定义4个窗口， 分时刷新显示
*******************************************************************************/
void smg_more_window_display(void)
{
        uint16_t i;
        switch (window) {
        case 0:                                 //__窗口__1
                led_buf[0] = 0;                 //第一个数码管显示“0”, 表示第1个窗口
                led_buf[1] = 22;                //第二个数码管显示“-”, 表示分隔符
                led_buf[2] = window_00 / 10;    //第三个数码管显示“十位”
                led_buf[3] = window_00 % 10;    //第四个数码管显示“个位”
                for (i = 0; i < 5000; i++) {    //显示这么长的时间
                        smg_display();          //数码管动态刷新
                }
                window++;
                break;
        case 1:                                 //__窗口__2
                led_buf[0] = 1;                 //第一个数码管显示“1”, 表示第2个窗口
                led_buf[1] = 22;                //第二个数码管显示“-”, 表示分隔符
                led_buf[2] = window_01 / 10;    //第三个数码管显示“十位”
                led_buf[3] = window_01 % 10;    //第四个数码管显示“个位”
                for (i = 0; i < 5000; i++) {
                        smg_display();
                }
                window++;
                break;
        case 2:                                 //__窗口__3
                led_buf[0] = 2;                 //第一个数码管显示“2”, 表示第3个窗口
                led_buf[1] = 22;                //第二个数码管显示“-”, 表示分隔符
                led_buf[2] = window_02 / 10;    //第三个数码管显示“十位”
                led_buf[3] = window_02 % 10;    //第四个数码管显示“个位”
                for (i = 0; i < 5000; i++) {
                        smg_display();
                }
                window++;
                break;
        case 3:                                 //__窗口__4
                led_buf[0] = 3;                 //第一个数码管显示“3”, 表示第4个窗口
                led_buf[1] = 22;                //第二个数码管显示“-”, 表示分隔符
                led_buf[2] = window_03 / 10;    //第三个数码管显示“十位”
                led_buf[3] = window_03 % 10;    //第四个数码管显示“个位”
                for (i = 0; i < 5000; i++) {    
                        smg_display();
                }
                window = 0;
                break;
        default: 
                break;
        }
}
