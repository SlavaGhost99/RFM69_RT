/******************************************************************************/
//Start File
// Header: 
// File Name: RFM69_Config.h
// Author: 
// Date: 2021.06.06
/******************************************************************************/
#ifndef ___RFM69_CONFIG_INC
#define ___RFM69_CONFIG_INC

#ifdef __cplusplus
extern "C" {
#endif

//Start File

/******************************************************************************/
//include files
#include <spi.h>
//*** <<< Use Configuration Wizard in Context Menu >>> ***
// <h> Packet Mode Select
	// <e> Using VARIABLE PACKET
	#define _ENABLE_VAR_PACKET 0U
	// </e>
	
	// <e> Using UNLIMIT Packet
	#define _ENABLE_UNLIMIT_PACKET 1U
			// <o> Set UNLIMITED Buffer size
		//<0xF0-0x800>
		#define _MAX_UNLIM_BUF_LENGHT 0x800
		
	// </e>
	
	// <o> Set FIFO Treshold size
	// <1-66>
	#define RF_FIFOTHRESH_MAX 32
	
// </h>

// <h>	Select SPI
	//<o> Using SPI
	//<1=> SPI1
	//<2=> SPI2
	//<3=> SPI3
	//<4=> SPI4
	//<5=> SPI5
	#define _SPI_SELECT 2U
//</h>

// <h> Select Watch timer
	//<o> Using Timer
	//<1=> TIM1
	//<2=> TIM2
	//<3=> TIM3
	//<4=> TIM4
	//<5=> TIM5
	//<6=> TIM6
	//<7=> TIM7
	//<8=> TIM8
	//<9=> TIM9
	//<10=> TIM10
	//<11=> TIM11
	#define _TIM_SELECT 10U
	
	//<o> Set Timer delay (mS)
	//<20-1000>
	#define _TIMER_RF69_WD_DELAY	100U
//</h>
//<h> Select Adress
	//<o> This Adress
	//<1-254>
	#define _DEFAULT_THIS_ADR 6U
	//<o> To Adres 
	//<1-254>
	#define _DEFAULT_TO_ADR		5U
//</h>	
	
	
//*** <<< end of configuration section >>>    ***
	
/******************************************************************************/
//Var
#if  _SPI_SELECT == 1U
#define _SPI_HANDLE 	hspi1
#define _SPI_DMA_RX_HANDLE hdma_spi1_rx
#define _SPI_DMA_TX_HANDLE hdma_spi1_tx
#elif  _SPI_SELECT == 2U
#define _SPI_HANDLE 	hspi2
#define _SPI_DMA_RX_HANDLE hdma_spi2_rx
#define _SPI_DMA_TX_HANDLE hdma_spi2_tx
#elif  _SPI_SELECT == 3U
#define _SPI_HANDLE 	hspi3
#define _SPI_DMA_RX_HANDLE hdma_spi3_rx
#define _SPI_DMA_TX_HANDLE hdma_spi3_tx
#elif  _SPI_SELECT == 4U
#define _SPI_HANDLE 	hspi4
#define _SPI_DMA_RX_HANDLE hdma_spi4_rx
#define _SPI_DMA_TX_HANDLE hdma_spi4_tx
#elif  _SPI_SELECT == 5U
#define _SPI_HANDLE 	hspi5
#define _SPI_DMA_RX_HANDLE hdma_spi5_rx
#define _SPI_DMA_TX_HANDLE hdma_spi5_tx
#else 
#error "Select SPI Handle"
#endif

#if _TIM_SELECT == 1U
#define _TIMER_WATCH_HANDLE htim1
#elif _TIM_SELECT == 2U
#define _TIMER_WATCH_HANDLE htim2
#elif _TIM_SELECT == 3U
#define _TIMER_WATCH_HANDLE htim3
#elif _TIM_SELECT == 4U
#define _TIMER_WATCH_HANDLE htim4
#elif _TIM_SELECT == 5U
#define _TIMER_WATCH_HANDLE htim5
#elif _TIM_SELECT == 6U
#define _TIMER_WATCH_HANDLE htim6
#elif _TIM_SELECT == 7U
#define _TIMER_WATCH_HANDLE htim7
#elif _TIM_SELECT == 8U
#define _TIMER_WATCH_HANDLE htim8
#elif _TIM_SELECT == 9U
#define _TIMER_WATCH_HANDLE htim9
#elif _TIM_SELECT == 10U
#define _TIMER_WATCH_HANDLE htim10
#elif _TIM_SELECT == 11U
#define _TIMER_WATCH_HANDLE htim11
#else 
#error "Select TIM Handle"

#endif
/******************************************************************************/


#ifdef __cplusplus
}
#endif
#endif //___RFM69_CONFIG_INC

//End File
