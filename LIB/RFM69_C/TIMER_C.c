// Header: TIMER_C.h
// File Name: TIMER_C.c
// Author:
// Date:  2021.06.26

/******************************************************************************/
//Start File

//#define _TIM_CR1               (_timer_c_hTim->Instance->CR1)
//#define DisableTim(n)              (n.TIMx->CR1 &= (~((U16)TIM_CR1_CEN)))

/******************************************************************************/
//Include
#include  "TIMER_C.h"
/******************************************************************************/
//Var
static uint16_t _timer_c_Delay = 0;
static TIM_HandleTypeDef* _timer_c_hTim;

/******************************************************************************/
//Function

void _timer_c_Init(TIM_HandleTypeDef* tim_baseHandle)
{
	_timer_c_hTim = tim_baseHandle;
}

void _timer_c_StartTimer(uint16_t delay)
{
//	DBG_ON;
//	DBG_OFF;
	delay = delay*100;
	if(_timer_c_hTim->State == HAL_TIM_STATE_BUSY)
	{
		HAL_TIM_Base_Stop_IT(_timer_c_hTim);
			
	}
	
	__HAL_TIM_CLEAR_FLAG(_timer_c_hTim, TIM_SR_UIF); // очищаем флаг
	_timer_c_hTim->Instance->ARR = delay - 1;	//Записываем задержку
	_timer_c_hTim->Instance->EGR |= TIM_EGR_UG; //Обновляем регистр ARR
	HAL_TIM_Base_Start_IT(_timer_c_hTim);

}

void _timer_c_StopTimer()
{
//	DBG_ON;
//	DBG_OFF;
//	DBG_ON;
//	DBG_OFF;

	HAL_TIM_Base_Stop_IT(_timer_c_hTim);
	__HAL_TIM_CLEAR_FLAG(_timer_c_hTim, TIM_SR_UIF); // очищаем флаг
}




/******************************************************************************/
//End File

