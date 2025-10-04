/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
static void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  // Danh sách chân LED từ d0 -> d11
  uint16_t led_pins[12] = {
    d0_Pin, d1_Pin, d2_Pin, d3_Pin,
    d4_Pin, d5_Pin, d6_Pin, d7_Pin,
    d8_Pin, d9_Pin, d10_Pin, d11_Pin
  };

  // ================= Exercise 7 =================
  void clearAllClock() {
    for(int i = 0; i < 12; i++) {
      HAL_GPIO_WritePin(GPIOA, led_pins[i], GPIO_PIN_RESET);
    }
  }

  // ================= Exercise 8 =================
  void setNumberOnClock(int num) {
    if(num >= 0 && num < 12) {
      HAL_GPIO_WritePin(GPIOA, led_pins[num], GPIO_PIN_SET);
    }
  }

  // ================= Exercise 9 =================
  void clearNumberOnClock(int num) {
    if(num >= 0 && num < 12) {
      HAL_GPIO_WritePin(GPIOA, led_pins[num], GPIO_PIN_RESET);
    }
  }

  /* USER CODE BEGIN WHILE */
  while (1)
    {
      // ========== Exercise 6: Test từng LED ==========
      for(int i = 0; i < 12; i++) {
        clearAllClock();
        setNumberOnClock(i);
        HAL_Delay(500);
      }

      // ========== Exercise 10: Đồng hồ giả lập ==========
      // Ví dụ giả lập đồng hồ đếm thời gian đơn giản
      // hour: nhảy mỗi 5s, minute: nhảy mỗi 1s, second: nhảy nhanh hơn
      static int hour = 0;
      static int minute = 0;
      static int second = 0;

      // Tắt hết LED trước khi hiển thị
      clearAllClock();

      // Bật 3 LED tương ứng
      setNumberOnClock(hour);
      setNumberOnClock(minute);
      setNumberOnClock(second);

      // Delay 1s rồi cập nhật "thời gian"
      HAL_Delay(100);

      second = (second + 1) % 12;
      if(second == 0) {
        minute = (minute + 1) % 12;
        if(minute == 0) {
          hour = (hour + 1) % 12;
        }
      }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, d0_Pin|d1_Pin|d2_Pin|d3_Pin
                          |d4_Pin|d5_Pin|d6_Pin|d7_Pin
                          |d8_Pin|d9_Pin|d10_Pin|d11_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : d0_Pin d1_Pin d2_Pin d3_Pin
                           d4_Pin d5_Pin d6_Pin d7_Pin
                           d8_Pin d9_Pin d10_Pin d11_Pin */
  GPIO_InitStruct.Pin = d0_Pin|d1_Pin|d2_Pin|d3_Pin
                          |d4_Pin|d5_Pin|d6_Pin|d7_Pin
                          |d8_Pin|d9_Pin|d10_Pin|d11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

