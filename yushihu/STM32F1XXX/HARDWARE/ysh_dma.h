#ifndef __YSH_DMA_H__
#define __YSH_DMA_H__

#include "ysh_config.h"
void dma_printf(void);
void dma1_channel_1_setup(void);

typedef struct {
        uint16_t in0;
        uint16_t in1;
        uint16_t in2;
        uint16_t in3;
        // 占位EOC（规则组转换完成后还有一个EOC）
        uint16_t last_eoc;
} adc_data_t;


#endif
