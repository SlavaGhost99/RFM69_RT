/******************************************************************************/
//Start File RFM69_Config.h
// Header: 
// File Name:
// Author: 
// Date:
/******************************************************************************/
#ifndef ___RFM69_CONFIG_INC
#define ___RFM69_CONFIG_INC

//Start File

/******************************************************************************/
//include files
#include <spi.h>
//*** <<< Use Configuration Wizard in Context Menu >>> ***
// <h> Packet Mode Select
	// <e> Using VARIABLE PACKET
	#define _ENABLE_VAR_PACKET 1U
	// </e>
	
	// <e> Using UNLIMIT Packet
	#define _ENABLE_UNLIMIT_PACKET 1U
			// <o> Set UNLIMITED Buffer size
		//<0xF0-0x800>
		#define _MAX_UNLIM_BUF_LENGHT 0x200
		
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
	
//<h> Listen setting
	//<e> Use Listing Mode
	#define _ENABLE_LISTEN_MODE	1U
		//<h> RegListen1
		//<o.6..7> Resolution of Listen mode Idle time
		//<1=>64 us
		//<2=>4.1 ms
		//<3=>262 ms
	
		//<o.4..5> Resolution of Listen mode Rx time
		//<1=>64 us
		//<2=>4.1 ms
		//<3=>262 ms
		
		//<o.3> Criteria for packet acceptance in Listen mode
		//<0=> 0
		//<1=> 1
		//<i>Criteria for packet acceptance in Listen mode:
		//<i>0 -> signal strength is above RssiThreshold
		//<i>1 -> signal strength is above RssiThreshold and
		//<i>SyncAddress matched
		
		//<o.1..2> Action taken after acceptance of a packet in Listen mode
		//<0=>00
		//<1=>01
		//<2=>10
		//<i>Action taken after acceptance of a packet in Listen mode:
		//<i>00 -> chip stays in Rx mode. Listen mode stops and must
		//<i>be disabled (see section 4.3).
		//<i>01 -> chip stays in Rx mode until PayloadReady or
		//<i>Timeout interrupt occurs. It then goes to the mode defined
		//<i>by Mode. Listen mode stops and must be disabled (see
		//<i>section 4.3).
		//<i>10 -> chip stays in Rx mode until PayloadReady or
		//<i>Timeout interrupt occurs. Listen mode then resumes in
		//<i>Idle state. FIFO content is lost at next Rx wakeup.
		//<i>11 -> Reserved
		//</h>
		#define _LISTEN_REG1_	144U
		
		//<o> RegListen2
		//<i>Duration of the Idle phase in Listen mode.
		//<0x0-0xFF>
		#define _LISTEN_IDLE_DURATION 0xF5U
		
		//<o> RegListen3
		//<i>Duration of the Rx phase in Listen mode
		//<0x0-0xFF>
		#define _LISTEN_RX_DURATION 0x20U
		
	//</e>
//</h>
//*** <<< end of configuration section >>>    ***
	
/******************************************************************************/
//Var
#if  _SPI_SELECT == 245U
#define _SPI_HANDLE 	hspi1
#define _SPI_DMA_RX_HANDLE hdma_spi1_rx
#define _SPI_DMA_TX_HANDLE hdma_spi1_tx
#elif  _SPI_SELECT == 2U
#define _SPI_HANDLE 	hspi2
#define _SPI_DMA_RX_HANDLE hdma_spi2_rx
#define _SPI_DMA_TX_HANDLE hdma_spi2_tx
#elif  _SPI_SELECT == 32U
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
#define _TIMER_WATCH_HANDLE (htim10)
#elif _TIM_SELECT == 11U
#define _TIMER_WATCH_HANDLE htim11
#else 
#error "Select TIM Handle"

#endif

//#define _LISTEN_REG1_ ((_LISTEN_IDLE_RESOL_ << 7U)  \
//						| (_LISTEN_RX_RESOL_ << 4U) \
//						| (_LISTEN_CRITERIA_ << 3)  \
//						| (_LISTEN_END << 2))
/******************************************************************************/
#endif //___RFM69_CONFIG_INC

//End File
