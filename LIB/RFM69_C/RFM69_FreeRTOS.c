// Header: RFM69_FreeRTOS.h
// File Name: RFM69_FreeRTOS.c
// Author:
// Date: 2021.08.21

/******************************************************************************/
//Start File


/******************************************************************************/
//Include
#include "main.h"
#include "RFM69_FreeRTOS.h"
#include <queue.h>
#include <semphr.h>

/******************************************************************************/
//Var


extern osSemaphoreId_t SemDIO_RF69Handle;
volatile static uint16_t _DioPin = 0;
extern bool _rxBufValid;

/******************************************************************************/
//Function
void StartDIO_RF69(void *argument)
{
	for(;;)
	{
		xSemaphoreTake(SemDIO_RF69Handle, portMAX_DELAY );
		if(_DioPin == DIO0_Pin)
		{
			RF69_Interrupt_DIO0();
		}
		if(_DioPin == DIO1_Pin)
		{
			
			if(HAL_GPIO_ReadPin(DIO1_GPIO_Port, DIO1_Pin) == RESET)
			{
				RF69_Interrupt_DIO1_Falling();
			}
			else
			{
				RF69_Interrupt_DIO1_Rising();
			}
		}
		if(_rxBufValid)
		{
			_receivBuferLenght = (uint16_t)sizeof(_receivBufer);
			RF69_ReceivPacket((uint8_t*)_receivBufer, &_receivBuferLenght);
//			xHigherPriorityTaskWoken = pdFALSE;
//			xSemaphoreGiveFromISR(SemReceiv_RF69Handle, &xHigherPriorityTaskWoken );
//			portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
			
		}

	//    osDelay(1);
	}
}

void RF69_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
/* Prevent unused argument(s) compilation warning */
	if(GPIO_Pin == DIO0_Pin)
	{
		_DioPin = GPIO_Pin;
		xSemaphoreGiveFromISR(SemDIO_RF69Handle, &xHigherPriorityTaskWoken );
//		RF69_Interrupt_DIO0();
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}
	if(GPIO_Pin == DIO1_Pin)
	{
		_DioPin = GPIO_Pin;
		xSemaphoreGiveFromISR(SemDIO_RF69Handle, &xHigherPriorityTaskWoken );
//		RF69_Interrupt_DIO0();
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}
	
//	if(GPIO_Pin == KEY_Pin)
//	{ 
//		xSemaphoreGiveFromISR(SemaphoreKEYHandle, &xHigherPriorityTaskWoken );
//		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
//	}
	UNUSED(GPIO_Pin);

}



/******************************************************************************/
//End File

