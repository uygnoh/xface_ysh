#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "ssd1306.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
// http://cholla.mmto.org/electronics/displays/oled/



// ChibiOS提供了一个名为streams的可选模块，
// 它提供了一些功能，包括chprintf打印格式化的字符串
// ____________________________________________________________
BaseSequentialStream    *chp = (BaseSequentialStream *)&SD1;



#define ADC_GRP1_NUM_CHANNELS   1       // 
#define ADC_GRP1_BUF_DEPTH      8

#define ADC_GRP2_NUM_CHANNELS   8       // 
#define ADC_GRP2_BUF_DEPTH      16



// typedef uint16_t adcsample_t;
// &samples1[0] 是ADC使用DMA传输内存的首地址
static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];


// 向 SSD1306-OLED 中写入字符
// ____________________________________________________________
char line0[10] = {'A', ' ', '0', '1', '2', '3', '4', '5', '6', 'X'};
char line1[10] = {'C', ' ', '0', '1', '2', '3', '4', '5', '6', 'Y'};
char line2[10] = {'E', ' ', '0', '1', '2', '3', '4', '5', '6', 'Z'};



/*
 * ADC streaming callback.
 */
uint16_t        ion = 0;


static void adccallback(ADCDriver *adcp) 
{

        (void)adcp;
        //ion++;
       
}

static void adccallback11(ADCDriver *adcp) 
{

        (void)adcp;
        ion = samples1[0];
       
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) 
{

        (void)adcp;
        (void)err;
}


/*
 * ADC conversion group.
 * Mode:        Linear buffer, 8 samples of 1 channel, SW triggered.
 * Channels:    IN10.
 */
static const ADCConversionGroup adcgrpcfg1 = {
        FALSE,
        ADC_GRP1_NUM_CHANNELS,
        adccallback11,
        adcerrorcallback,
        0, 0,                         /* CR1, CR2 */
        ADC_SMPR1_SMP_AN10(ADC_SAMPLE_1P5),
        0,                            /* SMPR2 */
        ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
        0,                            /* SQR2 */
        ADC_SQR2_SQ9_N(ADC_CHANNEL_IN10)
};


/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN10, IN11, IN12, IN13, IN10, IN10, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg2 = {
        TRUE,
        ADC_GRP2_NUM_CHANNELS,
        adccallback,
        adcerrorcallback,
        0, ADC_CR2_TSVREFE,           /* CR1, CR2 */
        ADC_SMPR1_SMP_AN11(ADC_SAMPLE_41P5) | ADC_SMPR1_SMP_AN10(ADC_SAMPLE_41P5) |
        ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_239P5) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_239P5),
        0,                            /* SMPR2 */
        ADC_SQR1_NUM_CH(ADC_GRP2_NUM_CHANNELS),
        ADC_SQR2_SQ8_N(ADC_CHANNEL_SENSOR) | ADC_SQR2_SQ7_N(ADC_CHANNEL_VREFINT),
        ADC_SQR3_SQ6_N(ADC_CHANNEL_IN10)   | ADC_SQR3_SQ5_N(ADC_CHANNEL_IN10) |
        ADC_SQR3_SQ4_N(ADC_CHANNEL_IN13)   | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN12) |
        ADC_SQR3_SQ2_N(ADC_CHANNEL_IN11)   | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
};



// I2C和SSD1306 参数设置
// ____________________________________________________________
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
                chThdSleepMilliseconds(1000);
                palSetPad(GPIOA, 2);
                chThdSleepMilliseconds(1000);

                chprintf(chp, "samples2 PC0= %d\n\r", samples2[0]);
                chprintf(chp, "samples2 PC1= %d\n\r", samples2[1]);
                chprintf(chp, "samples2 PC2= %d\n\r", samples2[2]);
                chprintf(chp, "samples2 PC3= %d\n\r", samples2[3]);
                chprintf(chp, "samples2 PC0= %d\n\r", samples2[4]);
                chprintf(chp, "samples2 PC0= %d\n\r", samples2[5]);
                chprintf(chp, "---------------------------------\n\r");
                chprintf(chp, "samples2 = %d\n\r", samples2[6]);
                chprintf(chp, "samples2 = %d\n\r", samples2[7]);
                chprintf(chp, "------------------------------------------\n\r");
                chprintf(chp, "ino = %d\n\r", ion);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[8]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[16]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[24]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[32]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[40]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[48]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[56]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[64]);
                chprintf(chp, "samples2 PC0======= %d\n\r", samples2[120]);
                chprintf(chp, "------------------------------------------\n\r");
                chprintf(chp, "samples1 PC0======= %d\n\r", samples1[0]);
                chprintf(chp, "samples1 PC0======= %d\n\r", samples1[1]);
                chprintf(chp, "samples1 PC0======= %d\n\r", ion);
                
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
                ssd1306GotoXy(&SSD1306D1, 8, 0);
                ssd1306Puts(&SSD1306D1, line0, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

                // 第二行位置
                // ____________________________________________
                ssd1306GotoXy(&SSD1306D1, 0, 21);
                ssd1306Puts(&SSD1306D1, line1, &ssd1306_font_11x18, SSD1306_COLOR_WHITE);
                ssd1306UpdateScreen(&SSD1306D1);
                chThdSleepMilliseconds(100);

                // 第三行位置
                // ____________________________________________
                ssd1306GotoXy(&SSD1306D1, 0, 42);
                ssd1306Puts(&SSD1306D1, line2, &ssd1306_font_11x18, SSD1306_COLOR_BLACK);
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


        palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_ANALOG);         // PC0 - ADC123-IN(10)
        palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG);         // PC0 - ADC123-IN(11)
        palSetPadMode(GPIOC, 2, PAL_MODE_INPUT_ANALOG);         // PC0 - ADC123-IN(12)
        palSetPadMode(GPIOC, 3, PAL_MODE_INPUT_ANALOG);         // PC0 - ADC123-IN(13)


        // I2C 硬件连接已经在（os/hal/boards/MAPLEMINI_STM32_F103）中配置了
        palSetPadMode(IOPORT2, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); // SCL
        palSetPadMode(IOPORT2, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); // SDA
        chThdSleepMilliseconds(10);
        
        adcStart(&ADCD1, NULL);
        /*
        * Linear conversion.
        */
        adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
        chThdSleepMilliseconds(100);
        /*
        * Starts an ADC continuous conversion.
        */
        adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);
        
        
        // 启用串口 1， (NULL)使用默认配置
        // PA9  ---> TX
        // PA10 ---> RX
        sdStart(&SD1, NULL);

        // 使用静态方法（创建Blink线程）
        chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);
        chprintf(chp, "Hello world\n\r");
        // 使用静态方法（创建OLED线程）
        chThdCreateStatic(waOledDisplay, sizeof(waOledDisplay), NORMALPRIO, OledDisplay, NULL);

        while (true) {
                chThdSleepMilliseconds(500);
        }
}
