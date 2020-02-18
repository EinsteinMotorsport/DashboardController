/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "display_driver.h"
#include "display_layout.h"
#include "can_data_provider.h"
#include "display_renderer.h"
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

display_page** generate_left_pages(void);
display_page** generate_right_pages(void);


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan2;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN2_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART3_UART_Init(void);
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
  MX_CAN2_Init();
  MX_I2C1_Init();
  MX_SPI3_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	

	display_init();
	can_data_init(&hcan2);
	
	display_page** left = generate_left_pages();
	display_page** right = generate_right_pages();
	
	
	
	display_layout_init(left,right,1,2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	
	
	
  while (1){
		
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
		//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
		
		
		HAL_Delay(1000);
		
		can_data_update();
		display_update_layout(DISPLAY_ID_ALL);
		
		
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief CAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 16;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_1TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SideLED2_Pin|SideLED3_Pin|SideLED4_Pin|SideLED5_Pin 
                          |SideLED6_Pin|SideLED7_Pin|DisplayC_D_Pin|DisplayRW_Pin 
                          |DisplayRD_Pin|DisplayRST_Pin|DisplayCS1_Pin|DisplayCS2_Pin 
                          |SideLED0_Pin|SideLED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, TopLED0_Pin|TopLED1_Pin|TopLED2_Pin|TopLED3_Pin 
                          |TopLED4_Pin|TopLED5_Pin|TopLED6_Pin|TopLED7_Pin 
                          |TopLED8_Pin|TopLED9_Pin|TopLEDA_Pin|TopLEDB_Pin 
                          |TopLEDC_Pin|TopLEDD_Pin|TopLEDE_Pin|TopLEDF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, DataBus8_Pin|DataBus9_Pin|DataBusA_Pin|DataBusB_Pin 
                          |DataBusC_Pin|DataBusD_Pin|DataBusE_Pin|DataBusF_Pin 
                          |DataBus0_Pin|DataBus1_Pin|DataBus2_Pin|DataBus3_Pin 
                          |DataBus4_Pin|DataBus5_Pin|DataBus6_Pin|DataBus7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SideLED2_Pin SideLED3_Pin SideLED4_Pin SideLED5_Pin 
                           SideLED6_Pin SideLED7_Pin DisplayC_D_Pin DisplayRW_Pin 
                           DisplayRD_Pin DisplayRST_Pin DisplayCS1_Pin DisplayCS2_Pin 
                           SideLED0_Pin SideLED1_Pin */
  GPIO_InitStruct.Pin = SideLED2_Pin|SideLED3_Pin|SideLED4_Pin|SideLED5_Pin 
                          |SideLED6_Pin|SideLED7_Pin|DisplayC_D_Pin|DisplayRW_Pin 
                          |DisplayRD_Pin|DisplayRST_Pin|DisplayCS1_Pin|DisplayCS2_Pin 
                          |SideLED0_Pin|SideLED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : TopLED0_Pin TopLED1_Pin TopLED2_Pin TopLED3_Pin 
                           TopLED4_Pin TopLED5_Pin TopLED6_Pin TopLED7_Pin 
                           TopLED8_Pin TopLED9_Pin TopLEDA_Pin TopLEDB_Pin 
                           TopLEDC_Pin TopLEDD_Pin TopLEDE_Pin TopLEDF_Pin */
  GPIO_InitStruct.Pin = TopLED0_Pin|TopLED1_Pin|TopLED2_Pin|TopLED3_Pin 
                          |TopLED4_Pin|TopLED5_Pin|TopLED6_Pin|TopLED7_Pin 
                          |TopLED8_Pin|TopLED9_Pin|TopLEDA_Pin|TopLEDB_Pin 
                          |TopLEDC_Pin|TopLEDD_Pin|TopLEDE_Pin|TopLEDF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DataBus8_Pin DataBus9_Pin DataBusA_Pin DataBusB_Pin 
                           DataBusC_Pin DataBusD_Pin DataBusE_Pin DataBusF_Pin 
                           DataBus0_Pin DataBus1_Pin DataBus2_Pin DataBus3_Pin 
                           DataBus4_Pin DataBus5_Pin DataBus6_Pin DataBus7_Pin */
  GPIO_InitStruct.Pin = DataBus8_Pin|DataBus9_Pin|DataBusA_Pin|DataBusB_Pin 
                          |DataBusC_Pin|DataBusD_Pin|DataBusE_Pin|DataBusF_Pin 
                          |DataBus0_Pin|DataBus1_Pin|DataBus2_Pin|DataBus3_Pin 
                          |DataBus4_Pin|DataBus5_Pin|DataBus6_Pin|DataBus7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */



can_value test_data = {89.350f,1};
text_renderer_data test_5 = {"Tmot%.1f",&test_data,3,WHITE,BLACK,GREEN};
color_fill_data test_0 = {PINK,   BLUE};
color_fill_data test_1 = {CYAN,   BLUE};
color_fill_data test_2 = {YELLOW, BLUE};
color_fill_data test_3 = {GREEN,  BLUE};
color_fill_data test_4 = {RED,    BLUE};

display_page** generate_left_pages(){

	const int number_pages = 1;
	
	display_region* page0 = malloc(sizeof(display_region) * 5);
	if(!page0) Error_Handler();
	page0[0] = (display_region){&test_5, 0, 0, 320, 80, text_renderer};
	page0[1] = (display_region){&test_1, 5, 240 - 3*3*16 - 10, 7*3*10, 3*16, color_fill_renderer};
	page0[2] = (display_region){&test_2, 5, 240 - 2*3*16 - 5, 7*3*10, 3*16, color_fill_renderer};
	page0[3] = (display_region){&test_3, 5, 240 - 1*3*16, 7*3*10, 3*16, color_fill_renderer};
	page0[4] = (display_region){&test_2, 220,80,100,160,color_fill_renderer};

	display_page* pages = malloc(sizeof(display_page) * number_pages);		
	if (!pages) Error_Handler();
	pages[0] = (display_page){5,page0};	
	
	display_page** ret = malloc(sizeof(void*) * number_pages);
	if (!ret) Error_Handler();
	ret[0] = pages;
	return ret;
}



display_page** generate_right_pages(){

	const int number_pages = 2;
	
	display_region* page0 = malloc(sizeof(display_region) * 5);
	if(!page0) Error_Handler();
	page0[0] = (display_region){&test_5, 0, 0, 320, 80, text_renderer};
	page0[1] = (display_region){&test_1, 5, 240 - 3*3*16 - 10, 7*3*10, 3*16, color_fill_renderer};
	page0[2] = (display_region){&test_2, 5, 240 - 2*3*16 - 5, 7*3*10, 3*16, color_fill_renderer};
	page0[3] = (display_region){&test_3, 5, 240 - 1*3*16, 7*3*10, 3*16, color_fill_renderer};
	page0[4] = (display_region){&test_2, 220,80,100,160,color_fill_renderer};

	display_region* page1 = malloc(sizeof(display_region) * 1);
	if(!page1) Error_Handler();
	page1[0] = (display_region){&test_4,0,0,320,240,color_fill_renderer};
	
	display_page* pages = malloc(sizeof(display_page) * number_pages);		
	if (!pages) Error_Handler();
	pages[0] = (display_page){5,page0};	
	pages[1] = (display_page){1,page1};
	
	display_page** ret = malloc(sizeof(void*) * number_pages);
	if (!ret) Error_Handler();
	ret[0] = pages;
	ret[1] = pages + 1;
	
	return ret;

}




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
