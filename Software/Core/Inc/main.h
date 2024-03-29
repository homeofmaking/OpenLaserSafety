/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f0xx_hal.h"

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
#define WATERTEMP2_Pin GPIO_PIN_0
#define WATERTEMP2_GPIO_Port GPIOA
#define PRESSURE_Pin GPIO_PIN_1
#define PRESSURE_GPIO_Port GPIOA
#define ADC_SPARE1_Pin GPIO_PIN_2
#define ADC_SPARE1_GPIO_Port GPIOA
#define ADC_SPARE2_Pin GPIO_PIN_3
#define ADC_SPARE2_GPIO_Port GPIOA
#define DOOR2_Pin GPIO_PIN_4
#define DOOR2_GPIO_Port GPIOA
#define FIREALARM_Pin GPIO_PIN_5
#define FIREALARM_GPIO_Port GPIOA
#define SPARE_IO1_Pin GPIO_PIN_7
#define SPARE_IO1_GPIO_Port GPIOA
#define SPARE_IO2_Pin GPIO_PIN_0
#define SPARE_IO2_GPIO_Port GPIOB
#define EXT_UNLOCK_Pin GPIO_PIN_1
#define EXT_UNLOCK_GPIO_Port GPIOB
#define MASTER_DO_Pin GPIO_PIN_12
#define MASTER_DO_GPIO_Port GPIOB
#define SPARE_IO3_Pin GPIO_PIN_13
#define SPARE_IO3_GPIO_Port GPIOB
#define SPARE_IO4_Pin GPIO_PIN_14
#define SPARE_IO4_GPIO_Port GPIOB
#define WATERFLOW_Pin GPIO_PIN_8
#define WATERFLOW_GPIO_Port GPIOA
#define EXHAUST_Pin GPIO_PIN_11
#define EXHAUST_GPIO_Port GPIOA
#define DOOR1_Pin GPIO_PIN_12
#define DOOR1_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
