/******************************************************************************/
//Start File 
// Header: 
// File Name: RF69_ACK.h
// Author: 
// Date: 2021.06.06
/******************************************************************************/
#ifndef ___RF69_ACK_INC
#define ___RF69_ACK_INC

//Start File

/******************************************************************************/
//include files
#include <stdbool.h>
#include "main.h"
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
volatile static uint32_t err_ACK_receiv;
volatile static uint32_t err_ACK_send;

volatile static uint32_t err_Packet_receiv;
volatile static uint32_t err_Packet_send;

volatile static uint32_t ok_Packet_send;
volatile static uint32_t ok_Packet_receiv;

volatile static uint32_t bad_Packet_send;
volatile static uint32_t bad_Packet_receiv;

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool SendFixACK(const uint8_t *buf, uint8_t len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool SendVarACK(const uint8_t *buf, uint8_t len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool SendUnlimACK(const uint8_t *buf, uint16_t len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool RecevFixACK(uint8_t *buf, uint8_t *len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool RecevVarACK(uint8_t *buf, uint8_t *len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool RecevUnlimACK(uint8_t *buf, uint16_t *len);


/******************************************************************************/
//Var

/******************************************************************************/

#ifdef __cplusplus
}
#endif
#endif //___RF69_ACK_INC

//End File
