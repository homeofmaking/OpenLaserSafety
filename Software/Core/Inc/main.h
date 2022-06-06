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
#include "stm32f1xx_hal.h"

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
#define DOOR2_Pin GPIO_PIN_4
#define DOOR2_GPIO_Port GPIOA
#define WATERTEMP_Pin GPIO_PIN_6
#define WATERTEMP_GPIO_Port GPIOA
#define DOOR1_Pin GPIO_PIN_10
#define DOOR1_GPIO_Port GPIOA
#define DOOR1XXXX_Pin GPIO_PIN_12
#define DOOR1XXXX_GPIO_Port GPIOA
#define Exhaust_digital_Pin GPIO_PIN_4
#define Exhaust_digital_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
