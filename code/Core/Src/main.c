/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
void display7SEG(int num, int num2){
	uint32_t odr[10] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x04};
	uint32_t odr_2[10] = {0x80, 0x2780, 0x900, 0x300, 0x2600, 0x1200, 0x1000, 0x780, 0x00, 0x200};
	GPIOB->ODR = odr[num] | odr_2[num2];
}

void light(uint16_t red, uint16_t yellow, uint16_t green, int index) {
	HAL_GPIO_WritePin(GPIOA, red, index != 1);
	HAL_GPIO_WritePin(GPIOA, yellow, index != 2);
	HAL_GPIO_WritePin(GPIOA, green, index != 3);
}
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
  int cnt = 1, light1 = 0, light2 = 0;
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (cnt < 6) {
	      // Red on
		  light(R1_Pin, Y1_Pin, G1_Pin, 1);
		  light(R4_Pin, Y4_Pin, G4_Pin, 1);
		  light1 = 6 - cnt; // set time for light1
	  } else if (cnt < 9) {
	      // Green on
		  light(R1_Pin, Y1_Pin, G1_Pin, 3);
		  light(R4_Pin, Y4_Pin, G4_Pin, 3);
		  light1 = 9 - cnt; // set time for light1
	  } else {
	      // Yellow on
		  light(R1_Pin, Y1_Pin, G1_Pin, 2);
		  light(R4_Pin, Y4_Pin, G4_Pin, 2);
		  light1 = 11 - cnt; // set time for light1
	  }

	  if (cnt < 4) {
	      // Green on
		  light(R2_Pin, Y2_Pin, G2_Pin, 3);
		  light(R3_Pin, Y3_Pin, G3_Pin, 3);
		  light2 = 4 - cnt; // set time for light2
	  } else if (cnt < 6) {
	      // Yellow on
		  light(R2_Pin, Y2_Pin, G2_Pin, 2);
		  light(R3_Pin, Y3_Pin, G3_Pin, 2);
		  light2 = 6 - cnt; // set time for light2
	  } else {
	      // Red on
		  light(R2_Pin, Y2_Pin, G2_Pin, 1);
		  light(R3_Pin, Y3_Pin, G3_Pin, 1);
		  light2 = 11 - cnt; // set time for light2
	  }

	  display7SEG(light1, light2);
	  cnt = cnt == 10 ? cnt - 10 + 1 : cnt + 1;
	  HAL_Delay(1000); //
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
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, R1_Pin|Y1_Pin|G1_Pin|R2_Pin
                          |Y2_Pin|G2_Pin|R3_Pin|Y3_Pin
                          |G3_Pin|R4_Pin|Y4_Pin|G4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|d_Pin
                          |e_Pin|f_Pin|g_Pin|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : R1_Pin Y1_Pin G1_Pin R2_Pin
                           Y2_Pin G2_Pin R3_Pin Y3_Pin
                           G3_Pin R4_Pin Y4_Pin G4_Pin */
  GPIO_InitStruct.Pin = R1_Pin|Y1_Pin|G1_Pin|R2_Pin
                          |Y2_Pin|G2_Pin|R3_Pin|Y3_Pin
                          |G3_Pin|R4_Pin|Y4_Pin|G4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : a_Pin b_Pin c_Pin PB10
                           PB11 PB12 PB13 d_Pin
                           e_Pin f_Pin g_Pin PB7
                           PB8 PB9 */
  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|d_Pin
                          |e_Pin|f_Pin|g_Pin|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
