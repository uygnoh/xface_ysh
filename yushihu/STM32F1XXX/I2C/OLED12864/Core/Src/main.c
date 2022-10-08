//______________________________________________________________________________
//      => STM32 I2C 配置
//______________________________________________________________________________
//      EV5     SB=1            // 读SR1然后将地址写入DR寄存器将清除该事件
//      EV6     ADDR=1          // 读SR1然后读SR2将清除该事件
//      EV8_1   TxE=1           // 移位寄存器空,数据寄存器空,写DR寄存器
//      EV8     TxE=1           // 移位寄存器非空,数据寄存器空,写入DR寄存器将清除该事件
//      EV8_2   TxE=1,BTF=1     // 请求设置停止位。TxE和BTF位由硬件在产生停止条件时清除
//      EV9     ADDR10=1        // 读SR1然后写入DR寄存器将清除该事件



#include "main.h"
#include "ssd1306.h"
#include "characters.h"
#include "m32.h"


void SystemClock_Config(void);

int main(void)
{
        HAL_Init();
        SystemClock_Config();
        i2c_setup();
        ssd1306_setup();
        HAL_Delay(1000);
        ssd1306_clear();

        while (1) {
                oled_put_string_8x16(0, 0, "Temperature:1234");
                oled_put_string_8x16(0, 1, "Temperature:");
                oled_put_string_8x16(0, 2, "Humidity:XXX");
                oled_put_string_8x16(0, 3, "Temperature:YYY");
                HAL_Delay(1000);
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

/* USER CODE END 4 */

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
