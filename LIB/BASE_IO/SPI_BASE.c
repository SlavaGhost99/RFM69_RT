// Header:
// File Name: SPI_BASE.c
// Author:
// Date: 2020.04.12

/******************************************************************************/
#include "SPI_BASE.h"

/******************************************************************************/
//private var
static uint8_t bFlagUseSPI;

static uint8_t _LastErrorSPI;

uint8_t GetLastError()
{
	return _LastErrorSPI;
}

static uint8_t bufRX[2];
static uint8_t bufTX[2];
//static SPI_HandleTypeDef
	
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;
#define _SPI_HANDLE			hspi2
#define _SPI_DMA_RX_HANDLE	hdma_spi2_rx
#define _SPI_DMA_TX_HANDLE	hdma_spi2_tx
#define _PSPI_HANDLE		&hspi2
#define _PSPI_DMA_RX_HANDLE	&hdma_spi2_rx
#define _PSPI_DMA_TX_HANDLE	&hdma_spi2_tx

/******************************************************************************/

#if 0
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hspi);
	if (!bFlagUseSPI)
	{
		_NSS_OFF;
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hspi);
	if (!bFlagUseSPI)
	{
		_NSS_OFF;
	}

}
#endif

void Select()
{
//	bFlagUseSPI = 1;
	_NSS_ON;
	Delay_uS(1);
}

void Unselect(void)
{
	bFlagUseSPI = 0;
	_NSS_OFF;
	Delay_uS(1);
}

uint8_t readRegister(uint8_t reg)
{
	if(bFlagUseSPI)
	{
		bFlagUseSPI = false;
		Unselect();
		HAL_Delay(1);
	}
	
	bufTX[0] = reg/* & 0x7F*/;
	bufTX[1] = 0;
	bufRX[0] = 0;
	bufRX[1] = 0;
	

	
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY && _SPI_DMA_RX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
//	Unselect();
//	Delay_uS(50);
//	Select();
//	Delay_uS(50);
	Select();
//	Delay_uS(50);

	HAL_SPI_TransmitReceive_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, (uint8_t*)bufTX, (uint8_t*)bufRX, 2);
	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	_LastErrorSPI = HAL_OK;	
	return bufRX[1];

}

void writeRegister(uint8_t reg, uint8_t data)
{
	if(bFlagUseSPI)
	{
		bFlagUseSPI = false;
		Unselect();
	}

	Unselect();
	bufTX[0] = reg;
	bufTX[1] = data;
	
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	Select();
	__ASM volatile ("NOP");

	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, (uint8_t*)bufTX, 2);
	Unselect();

}

void WriteMultipleReg(uint8_t reg, uint8_t *data, uint16_t len)
{
	if(bFlagUseSPI)
	{
//		bIsUseSPI = false;
		Unselect();
	}	bFlagUseSPI = true;
	Select();

	while(_NSS_READ != GPIO_PIN_RESET)
    {
		_NSS_ON;
    }
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
    
	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, &reg, 1);
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, data, len);
	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
	{
		__ASM volatile ("NOP");
	}


	bFlagUseSPI = false;
	Unselect();
	
#if 0
	Unselect();
	//TODO: add wait?
	bFlagUseSPI = 1;
	_NSS_ON;
	transfer_wait(reg);
	do
    {
		_LastErrorSPI = HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, data, len);
		if(_LastErrorSPI == HAL_SPI_STATE_ERROR || _LastErrorSPI == HAL_SPI_STATE_ABORT)
		{
			bFlagUseSPI = 0;
			_NSS_OFF;
			return;
		}
		if(_LastErrorSPI != HAL_OK)
		{
			Delay_uS(50);
//			HAL_Delay(1);
		}
    }
    while(_LastErrorSPI != HAL_OK);
	bFlagUseSPI = 0;
#endif
}

void ReadMultipleReg(uint8_t reg, uint8_t *data, uint16_t len)
{
	static uint8_t tmpBuf[66];
	if(bFlagUseSPI)
	{
		bFlagUseSPI = false;
		Unselect();
	}
	/*adr |= 0x80;*/
	bFlagUseSPI = true;
	Select();
//	while(HAL_GPIO_ReadPin((GPIO_TypeDef*)SPI_NSS_Port, SPI_NSS_Pin) != GPIO_PIN_RESET)
//    {
//		HAL_GPIO_WritePin((GPIO_TypeDef*)SPI_NSS_Port, SPI_NSS_Pin, GPIO_PIN_RESET);
//    }

	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
    
	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, &reg, 1);
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	HAL_SPI_TransmitReceive_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE,tmpBuf, data, len);
	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
	{
		__ASM volatile ("NOP");
	}

	Unselect();
	bFlagUseSPI = false;
	
#if 0
	Unselect();
	//TODO: add wait?
	bFlagUseSPI = 1;
	_NSS_ON;
	transfer_wait(reg);
	do
    {
		_LastErrorSPI = HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, (uint8_t*)data, len);
		if(_LastErrorSPI == HAL_SPI_STATE_ERROR || _LastErrorSPI == HAL_SPI_STATE_ABORT)
		{
			_NSS_OFF;
			return ;
		}
		if(_LastErrorSPI != HAL_OK)
		{
			Delay_uS(50);
//			HAL_Delay(1);
		}
    }
    while(_LastErrorSPI != HAL_OK);
	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
	{
		_LastErrorSPI = _SPI_HANDLE.State;
		if(_LastErrorSPI == HAL_SPI_STATE_ERROR || _LastErrorSPI == HAL_SPI_STATE_ABORT)
		{
			_NSS_OFF;
			return ;
		}
		Delay_uS(50);
//		HAL_Delay(1);
	}
//	_NSS_OFF;
#endif
	_LastErrorSPI = HAL_OK;

}

uint8_t transfer_wait(uint8_t byte_in)
{
    static uint8_t rx = 0;
#if 0
    
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY && _SPI_DMA_RX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	HAL_SPI_TransmitReceive_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, &byte_in, &rx, 1);
	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
//	while(p_hDmaTx->State != HAL_DMA_STATE_READY && p_hDmaRx->State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
#elseif
//	static uint8_t errcode = 0xFF;
//	while( !=HAL_OK)
//	{
//		HAL_Delay(1);
//	}
	do
    {	
		_LastErrorSPI = HAL_SPI_TransmitReceive_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, &byte_in, &rx, 1));
		if(_LastErrorSPI == HAL_SPI_STATE_ERROR || _LastErrorSPI == HAL_SPI_STATE_ABORT)
		{ 
			return 0;
		}
		if(_LastErrorSPI != HAL_OK)
		{
			Delay_uS(50);
//			HAL_Delay(1);
		}
    }
    while(_LastErrorSPI != HAL_OK);
#endif
	return rx;
}

uint8_t transfer(uint8_t byte_in, uint8_t *byte_out)
{
	return HAL_SPI_TransmitReceive_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, &byte_in, byte_out, 1);
}











//End file
