/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
//#include "stdio.h"
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
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define LED_BLUE_Pin GPIO_PIN_4
#define LED_BLUE_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOA
#define LED_YELL_Pin GPIO_PIN_6
#define LED_YELL_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOA
#define NSS_Pin GPIO_PIN_12
#define NSS_GPIO_Port GPIOB
#define RF_RESET_Pin GPIO_PIN_8
#define RF_RESET_GPIO_Port GPIOA
#define DBG_Pin GPIO_PIN_9
#define DBG_GPIO_Port GPIOA
#define DIO0_Pin GPIO_PIN_10
#define DIO0_GPIO_Port GPIOA
#define DIO0_EXTI_IRQn EXTI15_10_IRQn
#define DIO1_Pin GPIO_PIN_3
#define DIO1_GPIO_Port GPIOB
#define DIO1_EXTI_IRQn EXTI3_IRQn
/* USER CODE BEGIN Private defines */
#ifdef LED1_Pin
#define LED1_ON			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin , GPIO_PIN_RESET)
#define LED1_OFF		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin , GPIO_PIN_SET)
#define LED1_TGL		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
#endif //LED1_Pin

#ifdef LED_BLUE_Pin
#define LED_BLUE_ON		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin , GPIO_PIN_RESET)
#define LED_BLUE_OFF	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin , GPIO_PIN_SET)
#define LED_BLUE_TGL	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin)
#endif //LED_BLUE_Pin

#ifdef LED_RED_Pin
#define LED_RED_ON		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin , GPIO_PIN_RESET)
#define LED_RED_OFF		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin , GPIO_PIN_SET)
#define LED_RED_TGL		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin)
#endif //LED_RED_Pin

#ifdef LED_YELL_Pin
#define LED_YELL_ON		HAL_GPIO_WritePin(LED_YELL_GPIO_Port,LED_YELL_Pin , GPIO_PIN_RESET)
#define LED_YELL_OFF	HAL_GPIO_WritePin(LED_YELL_GPIO_Port,LED_YELL_Pin , GPIO_PIN_SET)
#define LED_YELL_TGL	HAL_GPIO_TogglePin(LED_YELL_GPIO_Port, LED_YELL_Pin);
#endif //LED_YELL_Pin

#ifdef LED_GREEN_Pin
#endif //LED_GREEN_Pin
#define LED_GREEN_ON	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin , GPIO_PIN_RESET)
#define LED_GREEN_OFF	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin , GPIO_PIN_SET)
#define LED_GREEN_TGL	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin)

#ifdef NSS_Pin
#define NSS_ON			HAL_GPIO_WritePin(NSS_GPIO_Port,NSS_Pin , GPIO_PIN_RESET)
#define NSS_OFF			HAL_GPIO_WritePin(NSS_GPIO_Port,NSS_Pin , GPIO_PIN_SET)
#endif //NSS_Pin

#ifdef RF_RESET_Pin
#define RF_RESET_SET		HAL_GPIO_WritePin(RF_RESET_GPIO_Port,RF_RESET_Pin , GPIO_PIN_SET)
#define RF_RESET_RESET		HAL_GPIO_WritePin(RF_RESET_GPIO_Port,RF_RESET_Pin , GPIO_PIN_RESET)
#endif //RF_RESET_Pin

#ifdef DBG_Pin
#define DBG_OFF			HAL_GPIO_WritePin(DBG_GPIO_Port,DBG_Pin , GPIO_PIN_RESET)
#define DBG_ON			HAL_GPIO_WritePin(DBG_GPIO_Port,DBG_Pin , GPIO_PIN_SET)
#endif
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
