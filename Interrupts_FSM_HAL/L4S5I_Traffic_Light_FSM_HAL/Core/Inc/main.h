/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

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
#define PedButton_Pin GPIO_PIN_13
#define PedButton_GPIO_Port GPIOC
#define NS_G_Pin GPIO_PIN_0
#define NS_G_GPIO_Port GPIOC
#define NS_Y_Pin GPIO_PIN_1
#define NS_Y_GPIO_Port GPIOC
#define NS_R_Pin GPIO_PIN_2
#define NS_R_GPIO_Port GPIOC
#define EW_G_Pin GPIO_PIN_3
#define EW_G_GPIO_Port GPIOC
#define PedRed_Pin GPIO_PIN_5
#define PedRed_GPIO_Port GPIOA
#define EW_Y_Pin GPIO_PIN_4
#define EW_Y_GPIO_Port GPIOC
#define EW_R_Pin GPIO_PIN_5
#define EW_R_GPIO_Port GPIOC
#define PedGreen_Pin GPIO_PIN_14
#define PedGreen_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
