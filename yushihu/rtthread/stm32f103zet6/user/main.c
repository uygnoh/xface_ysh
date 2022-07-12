#include "stm32f1xx_hal.h"
#include <rtthread.h>

#define LED_GPIO_PORT   GPIOA
#define LED_PIN         GPIO_PIN_2

void hardware_initialization(void);
static void MX_GPIO_Init(void);

int main(void)
{
        while (1) {
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
                rt_thread_mdelay(500);
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
                rt_thread_mdelay(500);
        }
}


void hardware_initialization(void)
{
        //HAL_Init();
        //SystemClock_Config();
        MX_GPIO_Init();
}

static void MX_GPIO_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        __HAL_RCC_GPIOA_CLK_ENABLE();
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);

        GPIO_InitStruct.Pin   = LED_PIN;
        GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull  = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}
