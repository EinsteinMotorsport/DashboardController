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
CAN_HandleTypeDef hcan1;
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
static void MX_CAN1_Init(void);
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
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
	

	display_init();
	can_data_init(&hcan1);
	
	display_page** left = generate_left_pages();
	display_page** right = generate_right_pages();
	
	
	
	display_layout_init(left,right,1,4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);
	unsigned int i = 0;
  while (1){
		if (i++>100000 && 0) {
			i=0;
			display_layout_next_page(DISPLAY_ID_RIGHT);
		}
		//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
		
				
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
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 4;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_3TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = ENABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
	//set interrupt mode for receiving new can data byte into rxfifo0
	//SET_BIT(hcan1.Instance->IER, CAN_IER_FMPIE0);
	
	CAN_FilterTypeDef sFilterConfig;
	
	//Configure CAN filter
	sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;
  
  if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
	
	//Start CAN peripheral
	
	if(HAL_CAN_Start(&hcan1) != HAL_OK)
	{
		Error_Handler();
	}

  /* USER CODE END CAN1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SideLED2_Pin|SideLED3_Pin|SideLED4_Pin|SideLED5_Pin 
                          |SideLED6_Pin|SideLED7_Pin|DisplayC_D_Pin|DisplayRW_Pin 
                          |DisplayRD_Pin|DisplayRST_Pin|DisplayCS1_Pin|DisplayCS2_Pin 
                          |SideLED0_Pin|SideLED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RGBLED0G_Pin|RGBLED1G_Pin|RGBLED2G_Pin|RGBLED3G_Pin 
                          |RGBLED0B_Pin|RGBLED1B_Pin|RGBLED2B_Pin|RGBLED3B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RGBLED0R_Pin|RGBLED1R_Pin|TopLED2_Pin|TopLED3_Pin 
                          |TopLED4_Pin|TopLED5_Pin|TopLED6_Pin|TopLED7_Pin 
                          |TopLED8_Pin|TopLED9_Pin|TopLEDA_Pin|TopLEDB_Pin 
                          |TopLEDC_Pin|TopLEDD_Pin|RGBLED2R_Pin|RGBLED3R_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pins : RGBLED0G_Pin RGBLED1G_Pin RGBLED2G_Pin RGBLED3G_Pin 
                           RGBLED0B_Pin RGBLED1B_Pin RGBLED2B_Pin RGBLED3B_Pin */
  GPIO_InitStruct.Pin = RGBLED0G_Pin|RGBLED1G_Pin|RGBLED2G_Pin|RGBLED3G_Pin 
                          |RGBLED0B_Pin|RGBLED1B_Pin|RGBLED2B_Pin|RGBLED3B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RGBLED0R_Pin RGBLED1R_Pin TopLED2_Pin TopLED3_Pin 
                           TopLED4_Pin TopLED5_Pin TopLED6_Pin TopLED7_Pin 
                           TopLED8_Pin TopLED9_Pin TopLEDA_Pin TopLEDB_Pin 
                           TopLEDC_Pin TopLEDD_Pin RGBLED2R_Pin RGBLED3R_Pin */
  GPIO_InitStruct.Pin = RGBLED0R_Pin|RGBLED1R_Pin|TopLED2_Pin|TopLED3_Pin 
                          |TopLED4_Pin|TopLED5_Pin|TopLED6_Pin|TopLED7_Pin 
                          |TopLED8_Pin|TopLED9_Pin|TopLEDA_Pin|TopLEDB_Pin 
                          |TopLEDC_Pin|TopLEDD_Pin|RGBLED2R_Pin|RGBLED3R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SteeringWheelButtonV_Pin */
  GPIO_InitStruct.Pin = SteeringWheelButtonV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SteeringWheelButtonV_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DataBus8_Pin DataBus9_Pin DataBusA_Pin DataBusB_Pin 
                           DataBusC_Pin DataBusD_Pin DataBusE_Pin DataBusF_Pin 
                           DataBus0_Pin DataBus1_Pin DataBus2_Pin DataBus3_Pin 
                           DataBus4_Pin DataBus5_Pin DataBus6_Pin DataBus7_Pin */
  GPIO_InitStruct.Pin = DataBus8_Pin|DataBus9_Pin|DataBusA_Pin|DataBusB_Pin 
                          |DataBusC_Pin|DataBusD_Pin|DataBusE_Pin|DataBusF_Pin 
                          |DataBus0_Pin|DataBus1_Pin|DataBus2_Pin|DataBus3_Pin 
                          |DataBus4_Pin|DataBus5_Pin|DataBus6_Pin|DataBus7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */




text_renderer_data test_5 = {"%04.0f",0,5,WHITE,BLACK,GREEN};
text_renderer_data test_6 = {"TMOT%3.0f",0,3,WHITE,BLACK,GREEN};
text_renderer_data test_7 = {"TOIL%3.0f",0,3,WHITE,BLACK,GREEN};
text_renderer_data test_8 = {"POIL%3.0f",0,3,WHITE,BLACK,GREEN};
text_renderer_data test_9 = {"%1.0f",0,10,WHITE,BLACK,GREEN};
color_fill_data test_0 = {PINK,   BLUE};
color_fill_data test_1 = {CYAN,   BLUE};
color_fill_data test_2 = {YELLOW, BLUE};
color_fill_data test_3 = {GREEN,  BLUE};
color_fill_data test_4 = {RED,    BLUE};

display_page** generate_left_pages(){
	
	test_5.can_value = can_data_get_value(NMOT);
	test_6.can_value = can_data_get_value(TMOT);
	test_7.can_value = can_data_get_value(TOIL);
	test_8.can_value = can_data_get_value(POIL);
	test_9.can_value = can_data_get_value(GEAR);
	
	const int number_pages = 1;
	
	display_region* page0 = malloc(sizeof(display_region) * 5);
	if(!page0) Error_Handler();
	page0[0] = (display_region){&test_5, 0, 0, 320, 80, text_renderer};
	page0[1] = (display_region){&test_6, 5, 240 - 3*3*16 - 10, 7*3*10, 3*16, text_renderer};
	page0[2] = (display_region){&test_7, 5, 240 - 2*3*16 - 5, 7*3*10, 3*16, text_renderer};
	page0[3] = (display_region){&test_8, 5, 240 - 1*3*16, 7*3*10, 3*16, text_renderer};
	page0[4] = (display_region){&test_9, 220,80,100,160,text_renderer};

	display_page* pages = malloc(sizeof(display_page) * number_pages);		
	if (!pages) Error_Handler();
	pages[0] = (display_page){5,page0};	
	
	display_page** ret = malloc(sizeof(void*) * number_pages);
	if (!ret) Error_Handler();
	ret[0] = pages;
	return ret;
}

text_renderer_data rp0l0 = {"speed %5.0f km/h",0,2,BLACK,YELLOW,GREEN};
text_renderer_data rp0l1 = {"Tmot2 %5.0f \u00f8C",0,2,WHITE,RED,GREEN};
text_renderer_data rp0l2 = {"Tfuel %5.0f \u00f8C",0,2,BLACK,YELLOW,GREEN};
text_renderer_data rp0l3 = {"Pfuel   %2.1f bar",0,2,WHITE,BLACK,GREEN};

text_renderer_data rp1l0 = {"fuel_con%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp1l1 = {"ub%5.0f V",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp1l2 = {"aps%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp1l3 = {"ath%5.0f",0,2,WHITE,BLACK,GREEN};

text_renderer_data rp2l0 = {"launchsw%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp2l1 = {"lambda%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp2l2 = {"%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp2l3 = {"flc%5.0f",0,2,WHITE,BLACK,GREEN};

text_renderer_data rp3l0 = {"TC-sw%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp3l1 = {"pclutch%5.0f bar",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp3l2 = {"steer%5.0f",0,2,WHITE,BLACK,GREEN};
text_renderer_data rp3l3 = {"fan_pwm%5.0f",0,2,WHITE,BLACK,GREEN};

display_page** generate_right_pages(){
	
	rp0l0.can_value = can_data_get_value(SPEED);
	rp0l1.can_value = can_data_get_value(TMOT2);
	rp0l2.can_value = can_data_get_value(TFUEL);
	rp0l3.can_value = can_data_get_value(PFUEL);
	rp1l0.can_value = can_data_get_value(FUELCONS);
	rp1l1.can_value = can_data_get_value(UB);
	rp1l2.can_value = can_data_get_value(APS);
	rp1l3.can_value = can_data_get_value(ATH);
	rp2l0.can_value = can_data_get_value(B_LAUNCHSW);
	rp2l1.can_value = can_data_get_value(LAMBDA);
	rp2l2.can_value = can_data_get_value(NMOT); //TODO Handschrift von Jonas entziffern.
	rp2l3.can_value = can_data_get_value(FLC);
	rp3l0.can_value = can_data_get_value(SPEED);//TODO Handschrift von Jonas entziffern.
	rp3l1.can_value = can_data_get_value(PCLUTCH);
	rp3l2.can_value = can_data_get_value(STEER);
	rp3l3.can_value = can_data_get_value(FAN_PWM_EMS);
	
	

	const int number_pages = 4;
	
	display_region* page0 = malloc(sizeof(display_region) * 4);
	if(!page0) Error_Handler();
	page0[0] = (display_region){&rp0l0, 0, 0, 320, 60, text_renderer};
	page0[1] = (display_region){&rp0l1, 0, 60, 320, 60, text_renderer};
	page0[2] = (display_region){&rp0l2, 0, 120, 320, 60, text_renderer};
	page0[3] = (display_region){&rp0l3, 0, 180, 320, 60, text_renderer};

	display_region* page1 = malloc(sizeof(display_region) * 4);
	if(!page0) Error_Handler();
	page1[0] = (display_region){&rp1l0, 0, 0, 320, 60, text_renderer};
	page1[1] = (display_region){&rp1l1, 0, 60, 320, 60, text_renderer};
	page1[2] = (display_region){&rp1l2, 0, 120, 320, 60, text_renderer};
	page1[3] = (display_region){&rp1l3, 0, 180, 320, 60, text_renderer};
	
	display_region* page2 = malloc(sizeof(display_region) * 4);
	if(!page0) Error_Handler();
	page2[0] = (display_region){&rp2l0, 0, 0, 320, 60, text_renderer};
	page2[1] = (display_region){&rp2l1, 0, 60, 320, 60, text_renderer};
	page2[2] = (display_region){&rp2l2, 0, 120, 320, 60, text_renderer};
	page2[3] = (display_region){&rp2l3, 0, 180, 320, 60, text_renderer};
	
	display_region* page3 = malloc(sizeof(display_region) * 4);
	if(!page0) Error_Handler();
	page3[0] = (display_region){&rp3l0, 0, 0, 320, 60, text_renderer};
	page3[1] = (display_region){&rp3l1, 0, 60, 320, 60, text_renderer};
	page3[2] = (display_region){&rp3l2, 0, 120, 320, 60, text_renderer};
	page3[3] = (display_region){&rp3l3, 0, 180, 320, 60, text_renderer};

	
	display_page* pages = malloc(sizeof(display_page) * number_pages);		
	if (!pages) Error_Handler();
	pages[0] = (display_page){4,page0};	
	pages[1] = (display_page){4,page1};
	pages[2] = (display_page){4,page2};
	pages[3] = (display_page){4,page3};
	
	
	display_page** ret = malloc(sizeof(void*) * number_pages);
	if (!ret) Error_Handler();
	ret[0] = pages;
	ret[1] = pages + 1;
	ret[2] = pages + 2;
	ret[3] = pages + 3;

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
