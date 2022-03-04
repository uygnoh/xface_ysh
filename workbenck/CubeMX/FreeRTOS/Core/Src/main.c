/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

//FreeRTOS
//_____________________________________________________________
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


// SWV调试系统
//_____________________________________________________________
#include "stdio.h"
int _write(int file, char *ptr, int len)
{
        int i = 0;
        for (i = 0; i < len; i++) {
            ITM_SendChar((*ptr++));
        }
        return len;
}


//空闲任务内存分配
//_____________________________________________________________
static StackType_t      IdleTaskStack[configMINIMAL_STACK_SIZE];
static StaticTask_t     IdleTaskTCB;
//定时器任务内存分配
//_____________________________________________________________
static StackType_t      TimerTaskStack[configTIMER_TASK_STACK_DEPTH];
static StaticTask_t     TimerTaskTCB;

//_____________________________________________________________
//  任务__00__数据
//_____________________________________________________________
#define TASK00_STACK_SIZE                       1024
#define TASK00_PRIO                             3
TaskHandle_t task00_handle = NULL;
StackType_t task00_stack[TASK00_STACK_SIZE];
StaticTask_t task00_tcb;
//_____________________________________________________________
//  任务__11__数据
//_____________________________________________________________
#define TASK11_STACK_SIZE                       1024
#define TASK11_PRIO                             3
TaskHandle_t task11_handle = NULL;
StackType_t task11_stack[TASK11_STACK_SIZE];
StaticTask_t task11_tcb;
//_____________________________________________________________
//  任务__22__数据
//_____________________________________________________________
#define TASK22_STACK_SIZE                       512
#define TASK22_PRIO                             3
TaskHandle_t task22_handle = NULL;
StackType_t task22_stack[TASK22_STACK_SIZE];
StaticTask_t task22_tcb;


void task00(void *parameters);
void task11(void *parameters);
void task22(void *parameters);
void SystemClock_Config(void);


//      => 空闲任务
//_____________________________________________________________
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t  **ppxIdleTaskStackBuffer,
                                    uint32_t      *pulIdleTaskStackSize)
{
        *ppxIdleTaskTCBBuffer   = &IdleTaskTCB;
        *ppxIdleTaskStackBuffer = IdleTaskStack;
        *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
}

//      => 定时器任务
//_____________________________________________________________
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t  **ppxTimerTaskStackBuffer,
                                     uint32_t      *pulTimerTaskStackSize)
{
        *ppxTimerTaskTCBBuffer   = &TimerTaskTCB;
        *ppxTimerTaskStackBuffer = TimerTaskStack;
        *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}

//      => 任务 00
//_____________________________________________________________
void task00(void *parameters)
{
        for (;;) {
                taskENTER_CRITICAL();
                task11_handle = xTaskCreateStatic(
                                (TaskFunction_t)task11,
                                (char *)"TASK11",
                                (uint32_t)TASK11_STACK_SIZE,
                                (void *)NULL,
                                (UBaseType_t)TASK11_PRIO,
                                (StackType_t *)task11_stack,
                                (StaticTask_t *)&task11_tcb
                                );
                if (task11_handle == NULL) {
                        Error_Handler();
                }
                task22_handle = xTaskCreateStatic(
                                (TaskFunction_t)task22,
                                (char *)"TASK22",
                                (uint32_t)TASK22_STACK_SIZE,
                                (void *)NULL,
                                (UBaseType_t)TASK22_PRIO,
                                (StackType_t *)task22_stack,
                                (StaticTask_t *)&task22_tcb
                                );
                if (task22_handle == NULL) {
                        Error_Handler();
                }
                vTaskDelete(task00_handle);
                printf("TASK00 Delete ...\n");
                taskEXIT_CRITICAL();
        }
}


//      => 任务 11
//_____________________________________________________________
void task11(void *parameters)
{
        const portTickType xDelay = 500 / portTICK_RATE_MS;
        for (;;) {
                printf("TASK_11\n");
                vTaskDelay(xDelay);
        }
}
void task22(void *parameters)
{
        const portTickType xDelay = 500 / portTICK_RATE_MS;
        for (;;) {
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
                vTaskDelay(xDelay);
                HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                vTaskDelay(xDelay);
                printf("TASK_22\n");
        }
}

int main(void)
{
        HAL_Init();
        SystemClock_Config();
        MX_GPIO_Init();
        MX_USART2_UART_Init();

        task00_handle = xTaskCreateStatic(
                        (TaskFunction_t)task00,
                        (char *)"TASK00",
                        (uint32_t)TASK00_STACK_SIZE,
                        (void *)NULL,
                        (UBaseType_t)TASK00_PRIO,
                        (StackType_t *)task00_stack,
                        (StaticTask_t *)&task00_tcb
                        );
        if (task00_handle == NULL) {
                Error_Handler();
        }

        vTaskStartScheduler();

        while (1) {

        }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM5 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
