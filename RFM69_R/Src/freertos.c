/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* File Name          : freertos.c
	* Description        : Code for freertos applications
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
//
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "MyAppConfig.h"
#include "RFM69_.h"
#include "RF69_ACK.h"
#include "RND_GEN.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
#if _APP_MODE == 1U //Fixed Packet
extern const uint8_t _LMessage[256];
uint8_t buf[RF69_MAX_FIFO_LENGHT];
uint8_t lenghtBuf;
#endif
#if _APP_MODE == 2U //Var Packet
extern const uint8_t _LMessage[256];
uint8_t buf[256];
#endif
#if _APP_MODE == 3U //Unlim Packet
extern const uint8_t  _UMessage[512];
uint8_t buf[512];
#endif
#if _APP_MODE == 4U //Fixed Packet with ACK
extern const uint8_t _LMessage[256];
uint8_t buf[RF69_MAX_FIFO_LENGHT];
uint8_t lenghtBuf;
#endif
#if _APP_MODE == 5U //Fixed Packet with ACK
extern const uint8_t _LMessage[256];
uint8_t buf[RF69_MAX_FIFO_LENGHT];
uint8_t lenghtBuf;
#endif
#if _APP_MODE == 6U //Unlim Packet
extern const uint8_t  _UMessage[512];
uint8_t buf[_MAX_UNLIM_BUF_LENGHT];
uint16_t lenghtBuf;
#endif


/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 256 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for InitTask */
osThreadId_t InitTaskHandle;
const osThreadAttr_t InitTask_attributes = {
  .name = "InitTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for RadioTask */
osThreadId_t RadioTaskHandle;
uint32_t RadioTaskBuffer[ 512 ];
osStaticThreadDef_t RadioTaskControlBlock;
const osThreadAttr_t RadioTask_attributes = {
  .name = "RadioTask",
  .cb_mem = &RadioTaskControlBlock,
  .cb_size = sizeof(RadioTaskControlBlock),
  .stack_mem = &RadioTaskBuffer[0],
  .stack_size = sizeof(RadioTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RequRadioTimer */
osTimerId_t RequRadioTimerHandle;
osStaticTimerDef_t RequRadioTimerControlBlock;
const osTimerAttr_t RequRadioTimer_attributes = {
  .name = "RequRadioTimer",
  .cb_mem = &RequRadioTimerControlBlock,
  .cb_size = sizeof(RequRadioTimerControlBlock),
};
/* Definitions for RF_Mutex */
osMutexId_t RF_MutexHandle;
osStaticMutexDef_t RF_MutexControlBlock;
const osMutexAttr_t RF_Mutex_attributes = {
  .name = "RF_Mutex",
  .cb_mem = &RF_MutexControlBlock,
  .cb_size = sizeof(RF_MutexControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartInitTask(void *argument);
void StartRadioTask(void *argument);
void RequRadioTimerCallback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN VPORT_SUPPORT_TICKS_AND_SLEEP */
__weak void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
{
  // Generated when configUSE_TICKLESS_IDLE == 2.
  // Function called in tasks.c (in portTASK_FUNCTION).
  // TO BE COMPLETED or TO BE REPLACED by a user one, overriding that weak one.
}
/* USER CODE END VPORT_SUPPORT_TICKS_AND_SLEEP */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of RF_Mutex */
  RF_MutexHandle = osMutexNew(&RF_Mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of RequRadioTimer */
  RequRadioTimerHandle = osTimerNew(RequRadioTimerCallback, osTimerOnce, NULL, &RequRadioTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of InitTask */
  InitTaskHandle = osThreadNew(StartInitTask, NULL, &InitTask_attributes);

  /* creation of RadioTask */
  RadioTaskHandle = osThreadNew(StartRadioTask, NULL, &RadioTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartInitTask */
/**
* @brief Function implementing the InitTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInitTask */
void StartInitTask(void *argument)
{
  /* USER CODE BEGIN StartInitTask */
  /* Infinite loop */
	osMutexWait(RF_MutexHandle, osWaitForever);
	RF69_Init();
	InitRND();
	
	
	
	osMutexRelease(RF_MutexHandle);
	 vTaskDelete(InitTaskHandle);
  /* USER CODE END StartInitTask */
}

/* USER CODE BEGIN Header_StartRadioTask */
/**
* @brief Function implementing the RadioTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRadioTask */
void StartRadioTask(void *argument)
{
  /* USER CODE BEGIN StartRadioTask */
	/* Infinite loop */
	volatile static uint32_t _good = 0;
	volatile static uint32_t _bad = 0;
	volatile static uint32_t _all = 0;
	volatile static float _percent = 0;

	volatile static bool _flag= 0;
	for(;;)
	{
#if _APP_MODE == 1U //Fixed Packet
	DBG_ON;
	DBG_OFF;
		RF69_PacketMode(_PACKET_FIXED);
		RF69_WaitAvailableTimeout(1000);
		lenghtBuf = RF69_MAX_FIFO_LENGHT;
		_flag = RF69_Recv((uint8_t*) buf, &lenghtBuf);
		_all++;
		if(_flag)
		{
			LED_YELL_ON;
			if(!memcmp(buf, _LMessage, lenghtBuf))
			{
				LED_GREEN_ON;
				_good++;
			}
			else
			{
//				LED_RED_ON;
				_bad++;
			}
			
		}
		else
		{
			LED_RED_ON;
			_bad++;
		}
		_percent = _bad/((float)_all/100);

#endif
#if _APP_MODE == 2U //Variable Packet
		_all++;
		volatile static uint8_t size = 254;
		volatile static uint8_t buf[255] ={0,};
		RF69_PacketMode(_PACKET_VARIABLE);
		size = 255;
		_flag = RF69_WaitAvailableTimeout(1000);
		if(_flag)
		{
			LED_YELL_ON;
			RF69_RecvVariablePacket ((uint8_t*)buf, (uint8_t*)&size);
			_flag = memcmp((uint8_t*)_LMessage, (uint8_t*)buf, size);
			if(!_flag)
			{
				LED_GREEN_ON;
				_good++;
			}
			else
			{
				_bad++;
			}
		}
		else
		{
			LED_RED_ON;
			_bad++;
		}
		_percent = _bad/((float)_all/100);
//extern bool SendACK(uint8_t *buf, uint16_t len);

//	SendACK((uint8_t*)_LMessage, size);
		
#endif
	
#if _APP_MODE == 3U //Unlimited Packet
		static uint8_t buf[2048];
		RF69_PacketMode(_PACKET_UNLIMIT);
		_flag = RF69_WaitAvailableTimeout(1000);
		static uint16_t size = 0;
		_all++;
		memset((uint8_t*)buf, 0, sizeof(buf));
		size = sizeof(buf);
		if(_flag)
		{
			LED_YELL_ON;
			RF69_RecvUnlimitPacket ((uint8_t*)buf, (uint16_t*)&size);

			_flag = memcmp((uint8_t*)_UMessage, (uint8_t*)buf, size);
			if(!_flag)
			{
				LED_GREEN_ON;
				_good++;
			}
			else
			{
				_bad++;
			}
			
		}
		else
		{
			LED_RED_ON;
			_bad++;
		}
		_percent = _bad/((float)_all/100);
        
#endif

#if _APP_MODE == 4U //Fix Packet with ACK
		lenghtBuf = RF69_MAX_FIX_BUF_LEN;
		_flag = RecevFixACK((uint8_t*)buf, &lenghtBuf);
		if(_flag)
		{
			LED_GREEN_ON;
		}
		else
		{
			LED_RED_ON;
		}

#endif
#if _APP_MODE == 5U //Var Packet with ACK
		lenghtBuf = 255;
		_flag = RecevVarACK((uint8_t*)buf, &lenghtBuf);
		if(_flag)
		{
			LED_YELL_ON;
			_flag = memcmp((uint8_t*)buf, _LMessage, lenghtBuf);
			if(_flag == 0)
			{
				LED_GREEN_ON;
			}
			
		}
		else
		{
			LED_RED_ON;
		}

#endif
#if _APP_MODE == 6U //Var Packet with ACK
		lenghtBuf = _MAX_UNLIM_BUF_LENGHT;
		_flag = RecevUnlimACK((uint8_t*)buf, &lenghtBuf);
		if(_flag)
		{
			LED_YELL_ON;
			_flag = memcmp((uint8_t*)buf, _UMessage, lenghtBuf);
			if(_flag == 0)
			{
				LED_GREEN_ON;
			}
			
		}
		else
		{
			LED_RED_ON;
		}

#endif
		osDelay(20);
		LED_BLUE_OFF;
		LED_GREEN_OFF;
		LED_RED_OFF;
		LED_YELL_OFF;
		osDelay(80);
  }
  /* USER CODE END StartRadioTask */
}

/* RequRadioTimerCallback function */
void RequRadioTimerCallback(void *argument)
{
  /* USER CODE BEGIN RequRadioTimerCallback */

  /* USER CODE END RequRadioTimerCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
	if(GPIO_Pin == DIO0_Pin)
	{
		if(HAL_GPIO_ReadPin(DIO0_GPIO_Port, DIO0_Pin) == SET)
		{
			RF69_Interrupt_DIO0();
		}
	}
	if(GPIO_Pin == DIO1_Pin)
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
	
  UNUSED(GPIO_Pin);
 
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
