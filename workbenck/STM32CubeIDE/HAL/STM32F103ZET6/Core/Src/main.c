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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "queue.h"
int __io_putchar(int ch)
{
    //注意下面第一个参数是&huart1，因为cubemx配置了串口1自动生成的
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

// 创建任务函数
//_____________________________________________________________
#define HOS_PRIO               1
#define HOS_STACK_SIZE         1024
TaskHandle_t hos_handle = NULL;
static void hos(void *pvParam);


#define TASK01_PRIO             1
#define TASK01_STACK_SIZE       1024
TaskHandle_t task01_handle = NULL;
void task01(void *pvParam);

#define TASK02_PRIO             1
#define TASK02_STACK_SIZE       1024
TaskHandle_t task02_handle = NULL;
void task02(void *pvParam);

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  BaseType_t xReturn = pdPASS;
  xReturn = xTaskCreate(
          (TaskFunction_t)hos,                 //任务函数
          (char *        )"HOS",               //任务名称
          (uint16_t      )HOS_STACK_SIZE,       //任务栈大小
          (void *        )NULL,                 //任务参数
          (UBaseType_t   )HOS_PRIO,             //任务优先级
          (TaskHandle_t *)&hos_handle);         //任务句柄
  if (pdPASS == xReturn) {
          printf("HOS create success!\n");
          vTaskStartScheduler();
          while (1);
  } else {

  }

  //vTaskStartScheduler();
  while (1) {









    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void hos(void *pvParam)
{
        BaseType_t xReturn;
        taskENTER_CRITICAL();
        xReturn = xTaskCreate(
                (TaskFunction_t)task01,               //任务函数
                (char *        )"TASK01",             //任务名称
                (uint16_t      )TASK01_STACK_SIZE,    //任务栈大小
                (void *        )NULL,                 //任务参数
                (UBaseType_t   )TASK01_PRIO,          //任务优先级
                (TaskHandle_t *)&task01_handle);      //任务句柄
        if (pdPASS == xReturn) {
                printf("Create Task01 success!\n");
        }
        xReturn = xTaskCreate(
                (TaskFunction_t)task02,               //任务函数
                (char *        )"TASK02",             //任务名称
                (uint16_t      )TASK02_STACK_SIZE,    //任务栈大小
                (void *        )NULL,                 //任务参数
                (UBaseType_t   )TASK02_PRIO,          //任务优先级
                (TaskHandle_t *)&task02_handle);      //任务句柄
        if (pdPASS == xReturn) {
                printf("Create Task02 success!\n");
        }
        vTaskDelete(hos_handle);
        printf("delete HOS success!\n");
        taskEXIT_CRITICAL();
}
void task01(void *pvParam)
{
        for (;;) {
                printf("task_01\n");
                vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
}
void task02(void *pvParam)
{
        for (;;) {
                printf("task_02\n");
                vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
}
/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
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
