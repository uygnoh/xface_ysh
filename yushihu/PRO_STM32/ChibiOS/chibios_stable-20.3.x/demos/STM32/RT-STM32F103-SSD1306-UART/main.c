/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include <stdlib.h>
#include "chprintf.h"
#include "ssd1306.h"
#include "stdio.h"
#include <string.h>

char snum0[10];
char snum1[10];
char ionnum[10];
BaseSequentialStream *chp = (BaseSequentialStream *)&SD1;

/*
 * Blinker thread.
 */
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

static const I2CConfig i2ccfg = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

static const SSD1306Config ssd1306cfg = {
    &I2CD1,
    &i2ccfg,
    SSD1306_SAD_0X78,
};

static SSD1306Driver SSD1306D1;

static void __attribute__((unused)) delayUs(uint32_t val)
{
        (void)val;
}

static void __attribute__((unused)) delayMs(uint32_t val)
{
        chThdSleepMilliseconds(val);
}

static THD_WORKING_AREA(waOledDisplay, 512);
static __attribute__((noreturn)) THD_FUNCTION(OledDisplay, arg)
{
        (void)arg;

        chRegSetThreadName("OledDisplay");
        ssd1306ObjectInit(&SSD1306D1);
        ssd1306Start(&SSD1306D1, &ssd1306cfg);
        ssd1306FillScreen(&SSD1306D1, 0x00);

        while (TRUE)
        {
                // ssd1306FillScreen(&SSD1306D1, 0x00);
                ssd1306GotoXy(&SSD1306D1, 0, 1);
                ssd1306Puts(&SSD1306D1, snum0, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

                ssd1306GotoXy(&SSD1306D1, 0, 19);
                ssd1306Puts(&SSD1306D1, snum1, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

                ssd1306GotoXy(&SSD1306D1, 0, 39);
                ssd1306Puts(&SSD1306D1, ionnum, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
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

        //palSetPadMode(IOPORT2, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); // SCL
        //palSetPadMode(IOPORT2, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); // SDA
        palSetPadMode(IOPORT3, 13, PAL_MODE_OUTPUT_PUSHPULL);         // LED on PC13

        chThdSleepMilliseconds(10);
        sdStart(&SD1, NULL);

        // Blink Thread
        chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);
        chprintf(chp, "Hello world\n\r");
        // SSD1306 Thread
        chThdCreateStatic(waOledDisplay, sizeof(waOledDisplay), NORMALPRIO, OledDisplay, NULL);

        while (true)
        {
                chThdSleepMilliseconds(500);
        }
}
