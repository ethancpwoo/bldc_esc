/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
  /* USER CODE BEGIN 2 */

  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  TIM1->CR1 = 0;
  TIM1->PSC = 7;
  TIM1->ARR = 45;
  TIM1->DIER |= TIM_DIER_UIE;
  TIM1->CR1 |= TIM_CR1_CEN;

  TIM2->CR1 = 0;
  TIM2->PSC = 1599;
  TIM2->ARR = 6249;
  TIM2->DIER |= TIM_DIER_UIE;
  TIM2->CR1 |= TIM_CR1_CEN;

  GPIOA->MODER |= (0x5555 << 0);
  GPIOA->OTYPER &= ~(0xFF << 0);
  GPIOA->OSPEEDR |= (0xFFFF << 0);

  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
  NVIC_EnableIRQ(TIM2_IRQn);

  void TIM1_UP_TIM10_IRQHandler(void) {
      if (TIM1->SR & TIM_SR_UIF) {
          TIM1->SR &= ~TIM_SR_UIF;
          if (current_on) current_on = false;
      }
  }

  void TIM1_CC_IRQHandler(void) {
      if (TIM1->SR & TIM_SR_CC1IF) {
          TIM1->SR &= ~TIM_SR_CC1IF;
          if (!current_on) current_on = true;
      }
  }

  void TIM2_IRQHandler(void) {
      if (TIM2->SR & TIM_SR_UIF) {
          TIM2->SR &= ~TIM_SR_UIF;
          step++;
          if (step == 6) step = 0;
      }
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  switch (step) {
		  case 0:
			  GPIOA->ODR = current_on ? 0x0C : 0x80;
			  break;
		  case 1:
			  GPIOA->ODR = current_on ? 0xC8 : 0x08;
			  break;
		  case 2:
			  GPIOA->ODR = current_on ? 0xE0 : 0x20;
			  break;
		  case 3:
			  GPIOA->ODR = current_on ? 0xB0 : 0x80;
			  break;
		  case 4:
			  GPIOA->ODR = current_on ? 0x38 : 0x08;
			  break;
		  case 5:
			  GPIOA->ODR = current_on ? 0x2C : 0x20;
			  break;
	  }
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
