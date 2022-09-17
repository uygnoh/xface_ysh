/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/adc.h"

#define TIMES              256
#define GET_UNIT(x)        ((x>>3) & 0x1)


#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32H2
#define ADC_RESULT_BYTE     4
#define ADC_CONV_LIMIT_EN   0
#define ADC_CONV_MODE       ADC_CONV_ALTER_UNIT     //ESP32C3 only supports alter mode
#define ADC_OUTPUT_TYPE     ADC_DIGI_OUTPUT_FORMAT_TYPE2
#endif

#if CONFIG_IDF_TARGET_ESP32C3 || CONFIG_IDF_TARGET_ESP32S3 || CONFIG_IDF_TARGET_ESP32H2
static uint16_t adc1_chan_mask = BIT(2) | BIT(3) | BIT(4);
static uint16_t adc2_chan_mask = BIT(0);
// 配置ADC1通道（GPIO2 GPIO3 GPIO4 ）
static adc_channel_t channel[3] = {ADC1_CHANNEL_2, ADC1_CHANNEL_3, ADC1_CHANNEL_4, (ADC2_CHANNEL_0 | 1 << 3)};
#endif


static const char *TAG = "ADC DMA";

static void continuous_adc_init(uint16_t adc1_chan_mask, uint16_t adc2_chan_mask, adc_channel_t *channel, uint8_t channel_num)
{
    adc_digi_init_config_t adc_dma_config = {
        .max_store_buf_size = 1024,
        .conv_num_each_intr = TIMES,
        .adc1_chan_mask = adc1_chan_mask,
        .adc2_chan_mask = adc2_chan_mask,
    };
    ESP_ERROR_CHECK(adc_digi_initialize(&adc_dma_config));

    adc_digi_configuration_t dig_cfg = {
        .conv_limit_en = ADC_CONV_LIMIT_EN,
        .conv_limit_num = 250,
        .sample_freq_hz = 10 * 1000,
        .conv_mode = ADC_CONV_MODE,
        .format = ADC_OUTPUT_TYPE,
    };

    adc_digi_pattern_config_t adc_pattern[SOC_ADC_PATT_LEN_MAX] = {0};
    dig_cfg.pattern_num = channel_num;
    for (int i = 0; i < channel_num; i++) {
        uint8_t unit = GET_UNIT(channel[i]);
        uint8_t ch = channel[i] & 0x7;
        adc_pattern[i].atten = ADC_ATTEN_DB_0;  // ADC衰减等级
        adc_pattern[i].channel = ch;
        adc_pattern[i].unit = unit;
        adc_pattern[i].bit_width = SOC_ADC_DIGI_MAX_BITWIDTH;

        ESP_LOGI(TAG, "adc_pattern[%d].atten is :%x", i, adc_pattern[i].atten);
        ESP_LOGI(TAG, "adc_pattern[%d].channel is :%x", i, adc_pattern[i].channel);
        ESP_LOGI(TAG, "adc_pattern[%d].unit is :%x", i, adc_pattern[i].unit);
    }
    dig_cfg.adc_pattern = adc_pattern;
    ESP_ERROR_CHECK(adc_digi_controller_configure(&dig_cfg));
}

#if !CONFIG_IDF_TARGET_ESP32
static bool check_valid_data(const adc_digi_output_data_t *data)
{
    const unsigned int unit = data->type2.unit;
    if (unit > 2) return false;
    if (data->type2.channel >= SOC_ADC_CHANNEL_NUM(unit)) return false;

    return true;
}
#endif

void app_main(void)
{
        esp_err_t ret;
        uint32_t ret_num = 0;
        uint8_t result[TIMES] = {0};
        memset(result, 0xcc, TIMES);

        continuous_adc_init(adc1_chan_mask, adc2_chan_mask, channel, sizeof(channel) / sizeof(adc_channel_t));
        adc_digi_start();

        while(1) {
                adc_digi_read_bytes(result, TIMES, &ret_num, ADC_MAX_DELAY);
                for (int i = 0; i < ret_num; i+= ADC_RESULT_BYTE) {
                        adc_digi_output_data_t *p = (void *)&result[i];
                        if (check_valid_data(p)) {
                            if ((p->type2.uint == 0) || (p->type2.channel >= 2) || (p->type2.channel <=4))
                                switch (p->type2.channel) {
                                case 2:
                                        adc_value_channel_2 = (0.3 * adc_value_channel2) + (0.7 * p->type2.data);
                                        break;
                                case 3:
                                        adc_value_channel_3 = (0.3 * adc_value_channel3) + (0.7 * p->type2.data);
                                        break;
                                case 4:
                                        adc_value_channel_4 = (0.3 * adc_value_channel4) + (0.7 * p->type2.data);
                                        break;
                                }
                                ESP_LOGI(TAG, "UNIT: %d,  Channel: %d,  Value: %d,  p->type2.unit + 1, p->type2.channel, p->type2.data);
                        }
                }

                vTaskDelay(1);
        } 

    }

}
