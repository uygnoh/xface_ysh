#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "ssd1306.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>


// 向 SSD1306-OLED 中写入字符
// ____________________________________________________________
char line0[10] = {'A', ' ', '0', '1', '2', '3', '4', '5', '6', 'X'};
char line1[10] = {'C', ' ', '0', '1', '2', '3', '4', '5', '6', 'Y'};
char line2[10] = {'E', ' ', '0', '1', '2', '3', '4', '5', '6', 'Z'};


// ChibiOS提供了一个名为streams的可选模块，
// 它提供了一些功能，包括chprintf打印格式化的字符串
// ____________________________________________________________
BaseSequentialStream    *chp = (BaseSequentialStream *)&SD1;



static const I2CConfig i2ccfg = {
        OPMODE_I2C,                             // 选择I2C
        400000,                                 // 设置频率
        FAST_DUTY_CYCLE_2,                      // 
};                                              //
static const SSD1306Config ssd1306cfg = {      //
        &I2CD1,                                 //
        &i2ccfg,                                //
        SSD1306_SAD_0X78,                       // 配置I2C从机地址
};



// blinker 线程
// ____________________________________________________________
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{
        (void)arg;

        chRegSetThreadName("blinker");
        while (true)
        {
                palClearPad(GPIOA, 2);
                chThdSleepMilliseconds(500);
                palSetPad(GPIOA, 2);
                chThdSleepMilliseconds(500);
        }
}

// SSD1306-OLED 线程
// ____________________________________________________________
static SSD1306Driver    SSD1306D1;
static THD_WORKING_AREA(waOledDisplay, 512);
static __attribute__((noreturn)) THD_FUNCTION(OledDisplay, arg)
{
        (void)arg;

        chRegSetThreadName("OledDisplay");
        ssd1306ObjectInit(&SSD1306D1);          // SSD1306 对象初始化
        ssd1306Start(&SSD1306D1, &ssd1306cfg);  // SSD1306 配置初始化
        ssd1306FillScreen(&SSD1306D1, 0x00);    // SSD1306 清屏

        while (TRUE) {

                // 第一行位置
                // ____________________________________________
                ssd1306GotoXy(&SSD1306D1, 0, 1);
                ssd1306Puts(&SSD1306D1, line0, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

                // 第二行位置
                // ____________________________________________
                ssd1306GotoXy(&SSD1306D1, 0, 19);
                ssd1306Puts(&SSD1306D1, line1, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

                // 第三行位置
                // ____________________________________________
                ssd1306GotoXy(&SSD1306D1, 0, 39);
                ssd1306Puts(&SSD1306D1, line2, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

        }
        ssd1306Stop(&SSD1306D1);
}

/*
 * Application entry point.
 */
int main(void)
{
        halInit();
        chSysInit();

        // I2C 硬件连接已经在（os/hal/boards/MAPLEMINI_STM32_F103）中配置了
        //palSetPadMode(IOPORT2, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);        // SCL
        //palSetPadMode(IOPORT2, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);        // SDA
        palSetPadMode(IOPORT3, 13, PAL_MODE_OUTPUT_PUSHPULL);                   // LED on PC13
        chThdSleepMilliseconds(10);
        // 串口1，使用默认配置
        sdStart(&SD1, NULL);

        // Blink Thread
        chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);
        chprintf(chp, "Hello world\n\r");
        // SSD1306 Thread
        chThdCreateStatic(waOledDisplay, sizeof(waOledDisplay), NORMALPRIO, OledDisplay, NULL);

        while (true) {
                chThdSleepMilliseconds(500);
        }
}
