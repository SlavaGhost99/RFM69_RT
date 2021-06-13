// Header:Base definition header (adding to main.h)
// File Name: BASE_DEF.h
// Author:
// Date: 2020.04.12
/******************************************************************************/
#ifndef  __BASE_DEF__
#define __BASE_DEF__
//Start file

#include "main.h"
#ifdef __cplusplus
extern "C" {
#endif

//#ifdef LED1_Pin
//#define LED1_ON			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin , GPIO_PIN_RESET)
//#define LED1_OFF		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin , GPIO_PIN_SET)
//#define LED1_TGL		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//#endif //LED1_Pin

//#ifdef LED_BLUE_Pin
//#define LED_BLUE_ON		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin , GPIO_PIN_RESET)
//#define LED_BLUE_OFF	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port,LED_BLUE_Pin , GPIO_PIN_SET)
//#define LED_BLUE_TGL	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin)
//#endif //LED_BLUE_Pin

//#ifdef LED_RED_Pin
//#define LED_RED_ON		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin , GPIO_PIN_RESET)
//#define LED_RED_OFF		HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin , GPIO_PIN_SET)
//#define LED_RED_TGL		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin)
//#endif //LED_RED_Pin

//#ifdef LED_YELL_Pin
//#define LED_YELL_ON		HAL_GPIO_WritePin(LED_YELL_GPIO_Port,LED_YELL_Pin , GPIO_PIN_RESET)
//#define LED_YELL_OFF	HAL_GPIO_WritePin(LED_YELL_GPIO_Port,LED_YELL_Pin , GPIO_PIN_SET)
//#define LED_YELL_TGL	HAL_GPIO_TogglePin(LED_YELL_GPIO_Port, LED_YELL_Pin);
//#endif //LED_YELL_Pin

//#ifdef LED_GREEN_Pin
//#endif //LED_GREEN_Pin
//#define LED_GREEN_ON	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin , GPIO_PIN_RESET)
//#define LED_GREEN_OFF	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin , GPIO_PIN_SET)
//#define LED_GREEN_TGL	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin)

//#ifdef NSS_Pin
//#define NSS_ON			HAL_GPIO_WritePin(NSS_GPIO_Port,NSS_Pin , GPIO_PIN_RESET)
//#define NSS_OFF			HAL_GPIO_WritePin(NSS_GPIO_Port,NSS_Pin , GPIO_PIN_SET)
//#endif //NSS_Pin

//#ifdef RF_RESET_Pin
//#define RF_RESET_SET		HAL_GPIO_WritePin(RF_RESET_GPIO_Port,RF_RESET_Pin , GPIO_PIN_SET)
//#define RF_RESET_RESET		HAL_GPIO_WritePin(RF_RESET_GPIO_Port,RF_RESET_Pin , GPIO_PIN_RESET)
//#endif //RF_RESET_Pin

//#ifdef DBG_Pin
//#define DBG_OFF			HAL_GPIO_WritePin(DBG_GPIO_Port,DBG_Pin , GPIO_PIN_RESET)
//#define DBG_ON			HAL_GPIO_WritePin(DBG_GPIO_Port,DBG_Pin , GPIO_PIN_SET)
//#endif

//Functions

void DWT_Init(void);
void Delay_uS(uint32_t uS); // DelayMicro

#ifdef __cplusplus
}
#endif

//End file
#endif
//__BASE_DEF__
