/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SideLED2_Pin GPIO_PIN_2
#define SideLED2_GPIO_Port GPIOE
#define SideLED3_Pin GPIO_PIN_3
#define SideLED3_GPIO_Port GPIOE
#define SideLED4_Pin GPIO_PIN_4
#define SideLED4_GPIO_Port GPIOE
#define SideLED5_Pin GPIO_PIN_5
#define SideLED5_GPIO_Port GPIOE
#define SideLED6_Pin GPIO_PIN_6
#define SideLED6_GPIO_Port GPIOE
#define TopLED0_Pin GPIO_PIN_0
#define TopLED0_GPIO_Port GPIOA
#define TopLED1_Pin GPIO_PIN_1
#define TopLED1_GPIO_Port GPIOA
#define TopLED2_Pin GPIO_PIN_2
#define TopLED2_GPIO_Port GPIOA
#define TopLED3_Pin GPIO_PIN_3
#define TopLED3_GPIO_Port GPIOA
#define TopLED4_Pin GPIO_PIN_4
#define TopLED4_GPIO_Port GPIOA
#define TopLED5_Pin GPIO_PIN_5
#define TopLED5_GPIO_Port GPIOA
#define TopLED6_Pin GPIO_PIN_6
#define TopLED6_GPIO_Port GPIOA
#define TopLED7_Pin GPIO_PIN_7
#define TopLED7_GPIO_Port GPIOA
#define SideLED7_Pin GPIO_PIN_7
#define SideLED7_GPIO_Port GPIOE
#define DisplayC_D_Pin GPIO_PIN_8
#define DisplayC_D_GPIO_Port GPIOE
#define DisplayRW_Pin GPIO_PIN_9
#define DisplayRW_GPIO_Port GPIOE
#define DisplayRD_Pin GPIO_PIN_10
#define DisplayRD_GPIO_Port GPIOE
#define DisplayRST_Pin GPIO_PIN_11
#define DisplayRST_GPIO_Port GPIOE
#define DisplayCS1_Pin GPIO_PIN_12
#define DisplayCS1_GPIO_Port GPIOE
#define DisplayCS2_Pin GPIO_PIN_13
#define DisplayCS2_GPIO_Port GPIOE
#define DataBus8_Pin GPIO_PIN_8
#define DataBus8_GPIO_Port GPIOD
#define DataBus9_Pin GPIO_PIN_9
#define DataBus9_GPIO_Port GPIOD
#define DataBusA_Pin GPIO_PIN_10
#define DataBusA_GPIO_Port GPIOD
#define DataBusB_Pin GPIO_PIN_11
#define DataBusB_GPIO_Port GPIOD
#define DataBusC_Pin GPIO_PIN_12
#define DataBusC_GPIO_Port GPIOD
#define DataBusD_Pin GPIO_PIN_13
#define DataBusD_GPIO_Port GPIOD
#define DataBusE_Pin GPIO_PIN_14
#define DataBusE_GPIO_Port GPIOD
#define DataBusF_Pin GPIO_PIN_15
#define DataBusF_GPIO_Port GPIOD
#define TopLED8_Pin GPIO_PIN_8
#define TopLED8_GPIO_Port GPIOA
#define TopLED9_Pin GPIO_PIN_9
#define TopLED9_GPIO_Port GPIOA
#define TopLEDA_Pin GPIO_PIN_10
#define TopLEDA_GPIO_Port GPIOA
#define TopLEDB_Pin GPIO_PIN_11
#define TopLEDB_GPIO_Port GPIOA
#define TopLEDC_Pin GPIO_PIN_12
#define TopLEDC_GPIO_Port GPIOA
#define TopLEDD_Pin GPIO_PIN_13
#define TopLEDD_GPIO_Port GPIOA
#define TopLEDE_Pin GPIO_PIN_14
#define TopLEDE_GPIO_Port GPIOA
#define TopLEDF_Pin GPIO_PIN_15
#define TopLEDF_GPIO_Port GPIOA
#define DataBus0_Pin GPIO_PIN_0
#define DataBus0_GPIO_Port GPIOD
#define DataBus1_Pin GPIO_PIN_1
#define DataBus1_GPIO_Port GPIOD
#define DataBus2_Pin GPIO_PIN_2
#define DataBus2_GPIO_Port GPIOD
#define DataBus3_Pin GPIO_PIN_3
#define DataBus3_GPIO_Port GPIOD
#define DataBus4_Pin GPIO_PIN_4
#define DataBus4_GPIO_Port GPIOD
#define DataBus5_Pin GPIO_PIN_5
#define DataBus5_GPIO_Port GPIOD
#define DataBus6_Pin GPIO_PIN_6
#define DataBus6_GPIO_Port GPIOD
#define DataBus7_Pin GPIO_PIN_7
#define DataBus7_GPIO_Port GPIOD
#define SideLED0_Pin GPIO_PIN_0
#define SideLED0_GPIO_Port GPIOE
#define SideLED1_Pin GPIO_PIN_1
#define SideLED1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
