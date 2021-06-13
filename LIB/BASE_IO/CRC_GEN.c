// Header: CRC_GEN.h
// File Name: CRC_GEN.c
// Author:
// Date:
#include "main.h"
#include <stdbool.h>
#include <string.h>

#include "CRC_GEN.h"

uint32_t CalcCRC(uint8_t *buf, uint16_t len)
{
	volatile uint32_t crc = 0;
	volatile uint16_t len_ = 0;
	volatile uint8_t l8 = 0;
	volatile uint32_t *pVar = 0;
	volatile uint32_t Var = 0;
	volatile static uint8_t tmpBuf[4];
	
	len_ = len/sizeof(uint32_t);
	l8 = len%sizeof(uint32_t);
	
	__HAL_RCC_CRC_CLK_ENABLE();
	CRC->CR = 1; // сброс
	for(uint32_t count = 0; count < len_*4; count = count +4)
	{
		pVar = (uint32_t*)&buf[count];
		CRC->DR = (uint32_t)*pVar;
	}
	if(l8)
	{
		memset((uint8_t*)tmpBuf, 0, sizeof(tmpBuf));
		memcpy((uint8_t*)tmpBuf, (uint8_t*)&buf[len_+4], l8);
		pVar = (uint32_t*)tmpBuf;
		CRC->DR = (uint32_t)*pVar;
	}
	crc = CRC->DR;
	__HAL_RCC_CRC_CLK_DISABLE();
	return crc;
}
/*
uint32_t CalcCRC_ACK(uint8_t *buf, uint16_t len)
{
	__HAL_RCC_CRC_CLK_ENABLE();
	CRC->CR = 1; // сброс
	for(uint16_t count = 0; count < len; count++)
	{
		CRC->DR = (uint32_t)buf[count];
	}
	__HAL_RCC_CRC_CLK_DISABLE();
	return CRC->DR;
	
}
*/

/*
uint32_t CalcCRC_ACK(uint8_t *buf, uint16_t len)
{
	uint32_t crc = 0xffffffff;
	uint32_t i;

	for(i=0;i<len;i++) 
		{
			crc = crc32_update(crc, buf[i]);
		}
	return crc ^ 0xffffffff;
}
*/






//End File