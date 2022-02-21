#include <stdint.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void my_task(void *pvParam);
int main(void)
{
        bsp_init();
        TaskHandle_t my_handle = NULL;
        xTaskCreate(my_task, "myTask1", 1024, NULL, 1, &my_handle);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
}
void my_task(void *pvParam)
{
        while (1) {
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                printf("...Run-time checking enabled  \n\r");
        }
}


