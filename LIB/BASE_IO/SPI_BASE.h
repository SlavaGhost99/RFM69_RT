// Header:
// File Name: 
// Author:
// Date: 2020.04.12
/******************************************************************************/
#ifndef	__SPI_BASE_H__
#define __SPI_BASE_H__
//Start file __SPI_BASE_H__

#include "stdint.h"
#include "main.h"
#include <stdbool.h>

#include "spi.h"
#include "stm32f4xx_it.h"
#include "Base_DEF.h"

//Defined Select pin SPI
#define _NSS_PIN			NSS_Pin
#define _NSS_PORT			NSS_GPIO_Port
#define _NSS_ON				HAL_GPIO_WritePin(_NSS_PORT, _NSS_PIN , GPIO_PIN_RESET)
#define _NSS_OFF			HAL_GPIO_WritePin(_NSS_PORT, _NSS_PIN , GPIO_PIN_SET)
#define _NSS_READ			HAL_GPIO_ReadPin(_NSS_PORT, _NSS_PIN)

#define _READ_MASK			0x80

#if 0


/******************************************************************************/
//Interrupts
	/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);

	/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
#endif
/******************************************************************************/
// Special finctions
	/***************************************************************************
	 * @brief  Getting last error code
	 * @param  None
	 * @retval Дast error code
	 **************************************************************************/
uint8_t GetLastError(void);

	/***************************************************************************
	 * @brief  Unselected SPI 
	 * @param  None
	 * @retval Zero is OK
	 **************************************************************************/
void Select(void);

	/***************************************************************************
	 * @brief  Selected SPI
	 * @param  None
	 * @retval Zero is OK
	 **************************************************************************/
void Unselect(void);

	/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
void SetFlagUsingBus(void);

/******************************************************************************/
//RW functions

	/***************************************************************************
	 * @brief  Reading one byte from the register.
	 * @param  None
	 * @retval None
	 **************************************************************************/
uint8_t readRegister(uint8_t reg);

	/***************************************************************************
	 * @brief  Write one byte to the register.
	 * @param  None
	 * @retval None
	 **************************************************************************/
void writeRegister(uint8_t reg, uint8_t data);

	/***************************************************************************
	 * @brief  Write multiple bytes to the register.
	 * @param  None
	 * @retval None
	 **************************************************************************/
void WriteMultipleReg(uint8_t reg, uint8_t *data, uint16_t len);

	/***************************************************************************
	 * @brief  Reading multiple bytes from the register.
	 * @param  None
	 * @retval None
	 **************************************************************************/
void ReadMultipleReg(uint8_t reg, uint8_t *data, uint16_t len);

	/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
uint8_t transfer_wait(uint8_t byte_in);

	/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
uint8_t transfer(uint8_t byte_in, uint8_t *byte_out);




//End file __SPI_BASE_H__
#endif //__SPI_BASE_H__

