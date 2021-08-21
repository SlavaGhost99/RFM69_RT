/******************************************************************************/
//Start File
// Header: 
// File Name: RFM69_FreeRTOS.h
// Author: 
// Date: 2021.08.21
/******************************************************************************/
#ifndef ___RFM69_FREERTOS_INC__
#define ___RFM69_FREERTOS_INC__

//Start File

/******************************************************************************/
//Include

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
//Define

/******************************************************************************/
//include files
#include "main.h"
#include "MyAppConfig.h"
#include "RFM69_Config.h"
#include <stm32f4xx_hal_dma.h>
#include "RFM69_.h"
#include "RF69_ACK.h"
#include "RND_GEN.h"
#include "AES_GEN.h"
#include "AES_KEY.h"
#include "TIMER_C.h"

#define _MAX_RECEIVE_BUFFER_LENGHT		512
/******************************************************************************/
//Var
static uint8_t _receivBufer[_MAX_RECEIVE_BUFFER_LENGHT];
static uint16_t _receivBuferLenght;
/******************************************************************************/
//Function
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void StartDIO_RF69(void *argument);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



/******************************************************************************/

#ifdef __cplusplus
}
#endif

/******************************************************************************/
#endif //___RFM69_FREERTOS_INC__

//End File
