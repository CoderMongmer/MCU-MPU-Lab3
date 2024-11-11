/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define LED_YELLOW_0_Pin GPIO_PIN_1
#define LED_YELLOW_0_GPIO_Port GPIOA
#define LED_GREEN_0_Pin GPIO_PIN_2
#define LED_GREEN_0_GPIO_Port GPIOA
#define LED_RED_1_Pin GPIO_PIN_3
#define LED_RED_1_GPIO_Port GPIOA
#define LED_YELLOW_1_Pin GPIO_PIN_4
#define LED_YELLOW_1_GPIO_Port GPIOA
#define LED_GREEN_1_Pin GPIO_PIN_5
#define LED_GREEN_1_GPIO_Port GPIOA
#define SEG_A2_Pin GPIO_PIN_6
#define SEG_A2_GPIO_Port GPIOA
#define SEG_B2_Pin GPIO_PIN_7
#define SEG_B2_GPIO_Port GPIOA
#define BTN_0_Pin GPIO_PIN_0
#define BTN_0_GPIO_Port GPIOB
#define BTN_1_Pin GPIO_PIN_1
#define BTN_1_GPIO_Port GPIOB
#define BTN_2_Pin GPIO_PIN_2
#define BTN_2_GPIO_Port GPIOB
#define EN_0_Pin GPIO_PIN_10
#define EN_0_GPIO_Port GPIOB
#define EN_1_Pin GPIO_PIN_11
#define EN_1_GPIO_Port GPIOB
#define EN_2_Pin GPIO_PIN_12
#define EN_2_GPIO_Port GPIOB
#define EN_3_Pin GPIO_PIN_13
#define EN_3_GPIO_Port GPIOB
#define SEG_C2_Pin GPIO_PIN_8
#define SEG_C2_GPIO_Port GPIOA
#define SEG_D2_Pin GPIO_PIN_9
#define SEG_D2_GPIO_Port GPIOA
#define SEG_E2_Pin GPIO_PIN_10
#define SEG_E2_GPIO_Port GPIOA
#define SEG_F2_Pin GPIO_PIN_11
#define SEG_F2_GPIO_Port GPIOA
#define LED_RED_0_Pin GPIO_PIN_12
#define LED_RED_0_GPIO_Port GPIOA
#define SEG_G2_Pin GPIO_PIN_13
#define SEG_G2_GPIO_Port GPIOA
#define SEG_A_Pin GPIO_PIN_3
#define SEG_A_GPIO_Port GPIOB
#define SEG_B_Pin GPIO_PIN_4
#define SEG_B_GPIO_Port GPIOB
#define SEG_C_Pin GPIO_PIN_5
#define SEG_C_GPIO_Port GPIOB
#define SEG_D_Pin GPIO_PIN_6
#define SEG_D_GPIO_Port GPIOB
#define SEG_E_Pin GPIO_PIN_7
#define SEG_E_GPIO_Port GPIOB
#define SEG_F_Pin GPIO_PIN_8
#define SEG_F_GPIO_Port GPIOB
#define SEG_G_Pin GPIO_PIN_9
#define SEG_G_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
