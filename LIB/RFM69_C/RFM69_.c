// Header: RFM69_.h
// File Name: RFM69_.c
// Author:
// Date: 2020.04.12

/******************************************************************************/
#include "main.h"
#include "RFM69_Config.h"
#include "RFM69_.h"
#include <string.h>
#include "BASE_DEF.h"
//#include "SX1231driver.h"                 
/******************************************************************************/
//Defines
#define _MAX_INIT_DELAY			0xFF

// <<< Use Configuration Wizard in Context Menu >>>
//<h>	Version Packet
//		<o> Version
//			<0-255>
#define VERSION_PACKET			2
//</h>
//<h> Default Modem config
//		<o>	Modem mode
//		<0=> 			FSK_Rb2Fd5 0 - FSK, Whitening, Rb 2kbs, Fd 5kHz
//		<1=>            FSK_Rb2_4Fd4_8 - FSK, Whitening, Rb = 2.4kbs,  Fd = 4.8kHz 
//		<2=>            FSK_Rb4_8Fd9_6 - FSK, Whitening, Rb = 4.8kbs,  Fd = 9.6kHz 
//		<3=>            FSK_Rb9_6Fd19_2 - FSK, Whitening, Rb = 9.6kbs,  Fd = 19.2kHz
//		<4=>            FSK_Rb19_2Fd38_4 - FSK, Whitening, Rb = 19.2kbs, Fd = 38.4kHz
//		<5=>            FSK_Rb38_4Fd76_8 - FSK, Whitening, Rb = 38.4kbs, Fd = 76.8kHz
//		<6=>            FSK_Rb57_6Fd120 - FSK, Whitening, Rb = 57.6kbs, Fd = 120kHz
//		<7=>            FSK_Rb125Fd125 - FSK, Whitening, Rb = 125kbs,  Fd = 125kHz
//		<8=>            FSK_Rb250Fd250 - FSK, Whitening, Rb = 250kbs,  Fd = 250kHz
//		<9=>            FSK_Rb55555Fd50 - FSK, Whitening, Rb = 55555kbs,Fd = 50kHz for RFM69 lib compatibility
            
//		<10=>            GFSK_Rb2Fd5 - GFSK, Whitening, Rb = 2kbs,    Fd = 5kHz
//		<11=>            GFSK_Rb2_4Fd4_8 - GFSK, Whitening, Rb = 2.4kbs,  Fd = 4.8kHz
//		<12=>            GFSK_Rb4_8Fd9_6 - GFSK, Whitening, Rb = 4.8kbs,  Fd = 9.6kHz
//		<13=>            GFSK_Rb9_6Fd19_2 - GFSK, Whitening, Rb = 9.6kbs,  Fd = 19.2kHz
//		<14=>            GFSK_Rb19_2Fd38_4 - GFSK, Whitening, Rb = 19.2kbs, Fd = 38.4kHz
//		<15=>            GFSK_Rb38_4Fd76_8 - GFSK, Whitening, Rb = 38.4kbs, Fd = 76.8kHz
//		<16=>            GFSK_Rb57_6Fd120 - GFSK, Whitening, Rb = 57.6kbs, Fd = 120kHz
//		<17=>            GFSK_Rb125Fd125 - GFSK, Whitening, Rb = 125kbs,  Fd = 125kHz
//		<18=>            GFSK_Rb250Fd250 - GFSK, Whitening, Rb = 250kbs,  Fd = 250kHz
//		<19=>            GFSK_Rb55555Fd50 - GFSK, Whitening, Rb = 55555kbs,Fd = 50kHz
            
//		<20=>            OOK_Rb1Bw1 - OOK, Whitening, Rb = 1kbs,    Rx Bandwidth = 1kHz. 
//		<21=>            OOK_Rb1_2Bw75 - OOK, Whitening, Rb = 1.2kbs,  Rx Bandwidth = 75kHz. 
//		<22=>            OOK_Rb2_4Bw4_8 - OOK, Whitening, Rb = 2.4kbs,  Rx Bandwidth = 4.8kHz. 
//		<23=>            OOK_Rb4_8Bw9_6 - OOK, Whitening, Rb = 4.8kbs,  Rx Bandwidth = 9.6kHz. 
//		<24=>            OOK_Rb9_6Bw19_2 - OOK, Whitening, Rb = 9.6kbs,  Rx Bandwidth = 19.2kHz. 
//		<25=>            OOK_Rb19_2Bw38_4 - OOK, Whitening, Rb = 19.2kbs, Rx Bandwidth = 38.4kHz. 
//		<26=>            OOK_Rb32Bw64 - OOK, Whitening, Rb = 32kbs,   Rx Bandwidth = 64kHz. 

ModemConfigChoice _defaultModemConfig = (ModemConfigChoice) 17;
//</h>

//<h>Set Freq
//		
//		<o>	Frequency
//		<i> Min 315 - Max 928
//		<315-928>
float _defaultFreq = 867;

//</h>

//<h> Setting Preamble Length
//		<o>	Length
//		<i>	1..65535 def 0x40
//		<0x1-0xffff>
uint16_t _defaultPreambleLength = 0x0100;
//</h>

//<h> Set Sync Word
//		<o>	Sync Word Lenght
//		<1-8>
uint8_t _defaultSyncWordLenght = 4;
//		<o0> 1-th Word
//		<0x01-0xFF>
//		<o1> 2-th Word
//		<0x00-0xFF>
//		<o2> 3-th Word
//		<0x00-0xFF>
//		<o3> 4-th Word
//		<0x00-0xFF>
//		<o4> 5-th Word
//		<0x00-0xFF>
//		<o5> 6-th Word
//		<0x00-0xFF>
//		<o6> 7-th Word
//		<0x00-0xFF>
//		<o7> 8-th Word
//		<0x00-0xFF>
#define _SW_0	170
#define _SW_1	212
#define _SW_2	85
#define _SW_3	170
#define _SW_4	189
#define _SW_5	85
#define _SW_6	170
#define _SW_7	212
uint8_t _defaultSyncWord[] = {_SW_0, _SW_1, _SW_2, _SW_3, _SW_4, _SW_5, _SW_6, _SW_7} ;
//</h>
//*** <<< end of configuration section >>>    ***
#ifdef INC_FREERTOS_H
//extern osStatus osThreadYield (void);
#define YIELD		osThreadYield();

#else
#define YIELD HAL_Delay(1);
#endif //INC_FREERTOS_H
/******************************************************************************/

// These are indexed by the values of ModemConfigChoice
// Stored in flash (program) memory to save SRAM
// It is important to keep the modulation index for FSK between 0.5 and 10
// modulation index = 2 * Fdev / BR
// Note that I have not had much success with FSK with Fd > ~5
// You have to construct these by hand, using the data from the RF69 Datasheet :-(
// or use the SX1231 starter kit software (Ctl-Alt-N to use that without a connected radio)
#define CONFIG_FSK (RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_00)
#define CONFIG_GFSK (RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_FSK | RF_DATAMODUL_MODULATIONSHAPING_01)
#define CONFIG_OOK (RF_DATAMODUL_DATAMODE_PACKET | RF_DATAMODUL_MODULATIONTYPE_OOK | RF_DATAMODUL_MODULATIONSHAPING_00)

// Choices for REG_37_PACKETCONFIG1:
#define CONFIG_NOWHITE (RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_OFF | RF_PACKET1_CRC_ON | RF_PACKET1_ADRSFILTERING_OFF)
#define CONFIG_WHITE (RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_WHITENING | RF_PACKET1_CRC_ON | RF_PACKET1_ADRSFILTERING_OFF)
#define CONFIG_MANCHESTER (RF_PACKET1_FORMAT_VARIABLE | RF_PACKET1_DCFREE_MANCHESTER | RF_PACKET1_CRC_ON | RF_PACKET1_ADRSFILTERING_OFF)

/******************************************************************************/
/******************************************************************************/

//bool DATA_ReceiveFileHeader();
/******************************************************************************/

static const ModemConfig MODEM_CONFIG_TABLE[] =
{
    //  02,        03,   04,   05,   06,   19,   1a,  37
    // FSK, No Manchester, no shaping, whitening, CRC, no address filtering
    // AFC BW == RX BW == 2 x bit rate
    // Low modulation indexes of ~ 1 at slow speeds do not seem to work very well. Choose MI of 2.
    { CONFIG_FSK,  0x3e, 0x80, 0x00, 0x52, 0xf4, 0xf4, CONFIG_WHITE}, // FSK_Rb2Fd5      
    { CONFIG_FSK,  0x34, 0x15, 0x00, 0x4f, 0xf4, 0xf4, CONFIG_WHITE}, // FSK_Rb2_4Fd4_8
    { CONFIG_FSK,  0x1a, 0x0b, 0x00, 0x9d, 0xf4, 0xf4, CONFIG_WHITE}, // FSK_Rb4_8Fd9_6

    { CONFIG_FSK,  0x0d, 0x05, 0x01, 0x3b, 0xf4, 0xf4, CONFIG_WHITE}, // FSK_Rb9_6Fd19_2
    { CONFIG_FSK,  0x06, 0x83, 0x02, 0x75, 0xf3, 0xf3, CONFIG_WHITE}, // FSK_Rb19_2Fd38_4
    { CONFIG_FSK,  0x03, 0x41, 0x04, 0xea, 0xf2, 0xf2, CONFIG_WHITE}, // FSK_Rb38_4Fd76_8

    { CONFIG_FSK,  0x02, 0x2c, 0x07, 0xae, 0xe2, 0xe2, CONFIG_WHITE}, // FSK_Rb57_6Fd120
    { CONFIG_FSK,  0x01, 0x00, 0x08, 0x00, 0xe1, 0xe1, CONFIG_WHITE}, // FSK_Rb125Fd125
    { CONFIG_FSK,  0x00, 0x80, 0x10, 0x00, 0xe0, 0xe0, CONFIG_WHITE}, // FSK_Rb250Fd250
    { CONFIG_FSK,  0x02, 0x40, 0x03, 0x33, 0x42, 0x42, CONFIG_WHITE}, // FSK_Rb55555Fd50 

    //  02,        03,   04,   05,   06,   19,   1a,  37
    // GFSK (BT=1.0), No Manchester, whitening, CRC, no address filtering
    // AFC BW == RX BW == 2 x bit rate
    { CONFIG_GFSK,	0x3e,	0x80, 0x00, 0x52, 0xf4, 0xf5, CONFIG_WHITE}, // GFSK_Rb2Fd5
    { CONFIG_GFSK,	0x34,	0x15, 0x00, 0x4f, 0xf4, 0xf4, CONFIG_WHITE}, // GFSK_Rb2_4Fd4_8
    { CONFIG_GFSK,	0x1a,	0x0b, 0x00, 0x9d, 0xf4, 0xf4, CONFIG_WHITE}, // GFSK_Rb4_8Fd9_6
		
    { CONFIG_GFSK,	0x0d,	0x05, 0x01, 0x3b, 0xf4, 0xf4, CONFIG_WHITE}, // GFSK_Rb9_6Fd19_2
    { CONFIG_GFSK,	0x06,	0x83, 0x02, 0x75, 0xf3, 0xf3, CONFIG_WHITE}, // GFSK_Rb19_2Fd38_4
    { CONFIG_GFSK,	0x03,	0x41, 0x04, 0xea, 0xf2, 0xf2, CONFIG_WHITE}, // GFSK_Rb38_4Fd76_8
		
    { CONFIG_GFSK,	0x02,	0x2c, 0x07, 0xae, 0xe2, 0xe2, CONFIG_WHITE}, // GFSK_Rb57_6Fd120
    { CONFIG_GFSK,	0x01,	0x00, 0x08, 0x00, 0xe1, 0xe1, CONFIG_WHITE}, // GFSK_Rb125Fd125
    { CONFIG_GFSK,	0x00,	0x80, 0x10, 0x00, 0xe0, 0xe0, CONFIG_WHITE}, // GFSK_Rb250Fd250
    { CONFIG_GFSK,	0x02,	0x40, 0x03, 0x33, 0x42, 0x42, CONFIG_WHITE}, // GFSK_Rb55555Fd50 
		
    //  02,       	03,  	04,   05,   06,   19,   1a,  37
    // OOK, No Manchester, no shaping, whitening, CRC, no address filtering
    // with the help of the SX1231 configuration program
    // AFC BW == RX BW
    // All OOK configs have the default:
    // Threshold Type: Peak
    // Peak Threshold Step: 0.5dB
    // Peak threshiold dec: ONce per chip
    // Fixed threshold: 6dB
    { CONFIG_OOK,  0x7d, 0x00, 0x00, 0x10, 0x88, 0x88, CONFIG_WHITE}, // OOK_Rb1Bw1
    { CONFIG_OOK,  0x68, 0x2b, 0x00, 0x10, 0xf1, 0xf1, CONFIG_WHITE}, // OOK_Rb1_2Bw75
    { CONFIG_OOK,  0x34, 0x15, 0x00, 0x10, 0xf5, 0xf5, CONFIG_WHITE}, // OOK_Rb2_4Bw4_8
    { CONFIG_OOK,  0x1a, 0x0b, 0x00, 0x10, 0xf4, 0xf4, CONFIG_WHITE}, // OOK_Rb4_8Bw9_6
    { CONFIG_OOK,  0x0d, 0x05, 0x00, 0x10, 0xf3, 0xf3, CONFIG_WHITE}, // OOK_Rb9_6Bw19_2
    { CONFIG_OOK,  0x06, 0x83, 0x00, 0x10, 0xf2, 0xf2, CONFIG_WHITE}, // OOK_Rb19_2Bw38_4
    { CONFIG_OOK,  0x03, 0xe8, 0x00, 0x10, 0xe2, 0xe2, CONFIG_WHITE}, // OOK_Rb32Bw64

//    { CONFIG_FSK,  0x68, 0x2b, 0x00, 0x52, 0x55, 0x55, CONFIG_WHITE}, // works: Rb1200 Fd 5000 bw10000, DCC 400
//    { CONFIG_FSK,  0x0c, 0x80, 0x02, 0x8f, 0x52, 0x52, CONFIG_WHITE}, // works 10/40/80
//    { CONFIG_FSK,  0x0c, 0x80, 0x02, 0x8f, 0x53, 0x53, CONFIG_WHITE}, // works 10/40/40

};

/******************************************************************************/
#if _ENABLE_VAR_PACKET ==1U
	volatile static RF69_VAR_PACKET _packetVar;
#endif
/******************************************************************************/

/******************************************************************************/
#if _ENABLE_UNLIMIT_PACKET ==1U
	volatile static RF69_UNLIM_PACKET _unlimPacketSend;
	volatile static uint8_t _packetLenght;
	//Длинна заголовка Unlimit пакета
	#define _LENGHT_UNLIM_PACK_HEADER	(sizeof(_unlimPacketSend._header))
	uint16_t _maxPaketLen = _MAX_UNLIM_BUF_LENGHT;
#endif
/******************************************************************************/

static uint8_t bufRX[2];
static uint8_t bufTX[2];


/******************************************************************************/
extern SPI_HandleTypeDef _SPI_HANDLE;
extern DMA_HandleTypeDef _SPI_DMA_RX_HANDLE;
extern DMA_HandleTypeDef _SPI_DMA_TX_HANDLE;
extern TIM_HandleTypeDef _TIMER_WATCH_HANDLE;

static volatile uint32_t buf_crc[RF69_MAX_PAYLOAD_LENGHT/4 + 1];

/******************************************************************************/
static RF69_FIX_PACKET _packetFix;

volatile static uint8_t _rxBufLenght;

volatile bool _flagIRQ_DIO0					= false;
volatile bool _flagIRQ_DIO1					= false;

volatile _PACKET_MODE _PacketMode	= 255;
volatile bool _flagUseAES					= false;
volatile bool _flag_Rx_Busy					= false; //Флаг "Передатчик занят"
volatile bool _flag_Tx_Busy					= false; //Флаг "Приемник занят"
volatile bool _flag_FIFO_Start				= false;
volatile bool _flag_Tx_End					= false; //Флаг окончания передачи

volatile static uint16_t _count_FIFO;						//Счетчик FIFO
volatile static uint16_t _sizeFIFO_data;

volatile static uint32_t rxGood				= 0;
volatile static uint32_t rxBad				= 0;
volatile static uint32_t txGood				= 0;

volatile static bool _rxBufValid			= false;
volatile static bool _exitWaitAvailable		= false;

volatile RF69_Mode _mode;

volatile static int8_t _power;// The selected output power in dBm

volatile static int8_t _lastRssi;

//static RF69_FIX_PACKET buf;

volatile static uint16_t _seekPacket;
/******************************************************************************/


extern CRC_HandleTypeDef hcrc;

#define _TIM_WATCH_PERIOD	30


/******************************************************************************/
static uint8_t bFlagUseSPI;

/******************************************************************************/
//void RF69_StartTimer(uint16_t delay);
//void RF69_StopTimer(void);
/******************************************************************************/
//void RF69_StartTimer(uint16_t delay)
//{
//	_TIMER_WATCH_HANDLE.Instance->ARR = delay;
//	_TIMER_WATCH_HANDLE.Instance->EGR |= TIM_EGR_UG;
//	HAL_TIM_Base_Start_IT(&_TIMER_WATCH_HANDLE);
//}

//void RF69_StopTimer()
//{
//	HAL_TIM_Base_Stop_IT(&_TIMER_WATCH_HANDLE);
//}

//static uint8_t _LastErrorSPI;
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)

/*__weak*/ void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hspi);
	if (!bFlagUseSPI)
	{
		_NSS_OFF;
	}
}

/*__weak*/ void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(hspi);
	if (!bFlagUseSPI)
	{
		_NSS_OFF;
	}

}
#endif

void RF69_CallbackWatchTimer()
{
//	LED1_ON;
//	DBG_ON;
//	DBG_OFF;
//	DBG_ON;
//	DBG_OFF;
//	DBG_ON;
//	DBG_OFF;
//	DBG_ON;
//	DBG_OFF;
//	DBG_ON;
//	DBG_OFF;
	RF69_SetModeIdle();
}

void RF69_Select()
{
//	bFlagUseSPI = 1;
	_NSS_ON;
	Delay_uS(1);
}

void RF69_Unselect(void)
{
	bFlagUseSPI = 0;
	_NSS_OFF;
	Delay_uS(1);
}
/******************************************************************************/

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_ReadFIFO_DIO1(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_ReadFIFO_DIO0(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_Send_DIO1(void);
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/

/******************************************************************************/

void RF69_WriteReg(uint8_t reg, uint8_t data)
{
	
	if(bFlagUseSPI)
	{
		bFlagUseSPI = false;
		RF69_Unselect();
	}

	RF69_Unselect();
	bufTX[0] = reg | RF69_WRITE_MASK;
	bufTX[1] = data;
	
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	RF69_Select();
	__ASM volatile ("NOP");

	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, (uint8_t*)bufTX, 2);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0U)
	RF69_Unselect();
#endif

}

uint8_t RF69_ReadReg(uint8_t reg)
{
		if(bFlagUseSPI)
	{
		bFlagUseSPI = false;
		RF69_Unselect();
		HAL_Delay(1);
	}
	reg &= ~0x80;

	bufTX[0] = reg/* & 0x7F*/;
	bufTX[1] = 0;
	bufRX[0] = 0;
	bufRX[1] = 0;
	

	
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY && _SPI_DMA_RX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}

	RF69_Select();

	HAL_SPI_TransmitReceive_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, (uint8_t*)bufTX, (uint8_t*)bufRX, 2);

	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0U)
	RF69_Unselect();
#endif

//	_LastErrorSPI = HAL_OK;	
	return bufRX[1];


}

void RF69_WriteMultipleReg(uint8_t reg, uint8_t *data, uint16_t len)
{

	if(bFlagUseSPI)
	{
//		bIsUseSPI = false;
		RF69_Unselect();
	}
	bFlagUseSPI = true;
	RF69_Select();
	while(_NSS_READ != GPIO_PIN_RESET)
    {
		_NSS_ON;
    }
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
    
	reg = reg | RF69_WRITE_MASK;
	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, &reg, 1);
	while(_SPI_DMA_TX_HANDLE.State != HAL_DMA_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&_SPI_HANDLE, data, len);
	
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0U)
	while(_SPI_HANDLE.State != HAL_SPI_STATE_READY)
	{
		__ASM volatile ("NOP");
	}
#endif


	bFlagUseSPI = false;
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0U)
	RF69_Unselect();
#endif	
}

void RF69_ReadMultipleReg(uint8_t reg, uint8_t *data, uint16_t len)
{
#if 0
	ReadMultipleReg(reg & ~RF69_WRITE_MASK, data, len);
#endif
	static uint8_t tmpBuf[66];
	if(bFlagUseSPI)
	{
		bFlagUseSPI = false;
		RF69_Unselect();
	}
	reg &= ~0x80;
	bFlagUseSPI = true;
	RF69_Select();

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

	bFlagUseSPI = false;
	
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0U)
	RF69_Unselect();
#endif
}

void RF69_Reset()
{
	HAL_GPIO_WritePin(RF_RESET_GPIO_Port,RF_RESET_Pin , GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(RF_RESET_GPIO_Port,RF_RESET_Pin , GPIO_PIN_RESET);
	HAL_Delay(5);
}

void RF69_SetOpMode(uint8_t mode)
{
    static uint8_t opmode;
	opmode = RF69_ReadReg(REG_OPMODE_01); //Read OpMode
							// Read	RegOpMode ==		0x04
    opmode &= ~RF_OPMODE_MODE;
    opmode |= (mode & RF_OPMODE_MODE);
    RF69_WriteReg(REG_OPMODE_01, opmode);//Write OpMode 0x04
							// Write	RegOpMode	0x..

    // Wait for mode to change.
    while (!(RF69_ReadReg(REG_IRQFLAGS1_27) & RF_IRQFLAGS1_MODEREADY))//Read RegIrqFlags1
							// Read		RegIrqFlags1 ==		0x..
	{
		__ASM volatile ("NOP");
	}
	
}

void RF69_SetModeIdle(void)
{
    if (_mode != RF69_ModeIdle)
    {
		if (_power >= 18)
		{
			// If high power boost, return power amp to receive mode
			RF69_WriteReg(REG_TESTPA1_5A, RF_TESTPA1_NORMAL); //Write RegTestPa1 0x55
			RF69_WriteReg(REG_TESTPA2_5C, RF_TESTPA2_NORMAL); //Write RegTestPa2 0x70
		}
		RF69_SetOpMode(RF_OPMODE_STANDBY);
		_mode = RF69_ModeIdle;
    }
}

void RF69_SetModeRx(void)
{
	if (_mode != RF69_ModeRx)
	{
		if (_power >= 18)
		{
			// If high power boost, return power amp to receive mode
			RF69_WriteReg(REG_TESTPA1_5A, RF_TESTPA1_NORMAL);
			RF69_WriteReg(REG_TESTPA2_5C, RF_TESTPA2_NORMAL);
		}
		RF69_WriteReg(REG_DIOMAPPING1_25, RF_DIOMAPPING1_DIO0_01 | RF_DIOMAPPING1_DIO1_00); // Set interrupt line 0 PayloadReady
										//PayloadReady				FifoLevel
//		RF69_WriteReg(REG_DIOMAPPING1_25, RF_DIOMAPPING1_DIO0_00 | RF_DIOMAPPING1_DIO1_00); // Set interrupt line 0 PayloadReady
		RF69_SetOpMode(RF_OPMODE_RECEIVER); // Clears FIFO
		_mode = RF69_ModeRx;
	}
}

void RF69_SetModeTx(void)
{
	if (_mode != RF69_ModeTx)
	{
		if (_power >= 18)
		{
			// Set high power boost mode
			// Note that OCP defaults to ON so no need to change that.
			RF69_WriteReg(REG_TESTPA1_5A, RF_TESTPA1_BOOST);
			RF69_WriteReg(REG_TESTPA2_5C, RF_TESTPA2_BOOST);
		}
		
		_flag_Tx_End = false;
		RF69_WriteReg(REG_DIOMAPPING1_25, RF_DIOMAPPING1_DIO0_00 | RF_DIOMAPPING1_DIO1_10); // Set interrupt line 0 PacketSent
										//PacketSent				FifoNotEmpty
									// Write	RegDioMapping1		0x5D
		RF69_SetOpMode(RF_OPMODE_TRANSMITTER); // Clears FIFO
		_mode = RF69_ModeTx;
	}
}

void RF69_SetModeSleep()
{
	if (_mode != RF69_ModeSleep)
	{
		RF69_WriteReg(REG_OPMODE_01, RF_OPMODE_SLEEP);
		_mode = RF69_ModeSleep;
	}
}

void RF69_SetModeListenRX()
{
}

void RF69_SetTxPower(int8_t power, uint8_t _IsHighPowerModule)
{
	_power = power;
	static uint8_t palevel;

	if (_IsHighPowerModule)
	{
		if (_power < -2)
		{
			_power = -2; //RFM69HW only works down to -2. 
		}
		if (_power <= 13)
		{
			// -2dBm to +13dBm
			//Need PA1 exclusivelly on RFM69HW
			palevel = RF_PALEVEL_PA1_ON | ((_power + 18) & 
			RF_PALEVEL_OUTPUTPOWER_11111);
		}
		else
		{
			if (_power >= 18)
			{
				// +18dBm to +20dBm
				// Need PA1+PA2
				// Also need PA boost settings change when tx is turned on and off, see setModeTx()
				palevel = RF_PALEVEL_PA1_ON
					| RF_PALEVEL_PA2_ON
					| ((_power + 11) & RF_PALEVEL_OUTPUTPOWER_11111);
			}
			else
			{
				// +14dBm to +17dBm
				// Need PA1+PA2
				palevel = RF_PALEVEL_PA1_ON
					| RF_PALEVEL_PA2_ON
					| ((_power + 14) & RF_PALEVEL_OUTPUTPOWER_11111);
			}
		}
	}
	else
	{
		if (_power < -18)
		{
			_power = -18;
		}
		if (_power > 13)
		{
			_power = 13; //limit for RFM69W
		}
		palevel = RF_PALEVEL_PA0_ON
			| ((_power + 18) & RF_PALEVEL_OUTPUTPOWER_11111);
	}
	RF69_WriteReg(REG_PALEVEL_11, palevel);
}

// Sets registers from a canned modem configuration structure
void RF69_SetModemRegisters(const ModemConfig* config)
{
    RF69_WriteMultipleReg(REG_DATAMODUL_02, (uint8_t*)&config->reg_02, 5);
    RF69_WriteMultipleReg(REG_RXBW_19,          (uint8_t*)&config->reg_19, 2);
    RF69_WriteReg(REG_PACKETCONFIG1_37,       config->reg_37);
}

// Set one of the canned FSK Modem configs
// Returns true if its a valid choice
uint8_t RF69_SetModemConfig(ModemConfigChoice index)
{
    if (index > (signed int)(sizeof(MODEM_CONFIG_TABLE) / sizeof(ModemConfig)))
	{
        return 0;
	}
    ModemConfig cfg;
    memcpy(&cfg, &MODEM_CONFIG_TABLE[index], sizeof(ModemConfig));
    RF69_SetModemRegisters(&cfg);

    return 1;
}

void RF69_SetPreambleLength(uint16_t bytes)
{
    RF69_WriteReg(REG_PREAMBLEMSB_2C, bytes >> 8);
					// Write	RegPreambleMsb 0x00
    RF69_WriteReg(REG_PREAMBLELSB_2D, bytes & 0xff);
					// Write	RegPreambleLsb 0x40
}

void RF69_SetSyncWords(const uint8_t* syncWords, uint8_t len)
{
    uint8_t syncconfig = RF69_ReadReg(REG_SYNCCONFIG_2E);
							// Read 	RegSyncConfig
    if (syncWords && len && len <= 4)
    {
		RF69_WriteMultipleReg(REG_SYNCVALUE1_2F, (uint8_t*)syncWords, len);
							// Write	RegSyncValue1
		syncconfig |= RF_SYNC_ON;
    }
    else
		syncconfig &= ~RF_SYNC_ON;
    syncconfig &= ~RF_SYNC_SIZE_8;
    syncconfig |= (len-1) << 3;
    RF69_WriteReg(REG_SYNCCONFIG_2E, syncconfig);
							// Write	RegSyncConfig
}

void RF69_Set_AES_Key(uint8_t* key)
{
	if (key)
	{
		RF69_WriteMultipleReg(REG_AESKEY1_3E, key, 16);
		RF69_WriteReg(REG_PACKETCONFIG2_3D, RF69_ReadReg(REG_PACKETCONFIG2_3D) | RF_PACKET2_AES_ON);
	}
	else
	{
		RF69_WriteReg(REG_PACKETCONFIG2_3D, RF69_ReadReg(REG_PACKETCONFIG2_3D) & ~RF_PACKET2_AES_ON);
	}
}

void RF69_SetFrequency(float freq)
{
    // Frf = FRF / FSTEP
    uint32_t frf = (uint32_t)((freq * 1000000.0) / RF69_FREQ_STEP);
    RF69_WriteReg(REG_FRFMSB_07, (frf >> 16) & 0xff);
						//Write	RegFrfMsb 0xD8
    RF69_WriteReg(REG_FRFMID_08, (frf >> 8) & 0xff);
 						//Write	RegFrfMid 0xC0
   RF69_WriteReg(REG_FRFLSB_09, frf & 0xff);
						//Write	RegFrfLsb 0x00
}


uint8_t RF69_Init()
{
	 DWT_Init();
	_timer_c_Init(&_TIMER_WATCH_HANDLE);
	
	RF69_Reset();
	static uint8_t startTime = 0;
	static uint8_t _deviceType;
	startTime = HAL_GetTick();
	//readiness check
	do
	{
		RF69_WriteReg(REG_SYNCVALUE1_2F, 0xAA);
						//Write SyncValue1 0xAA
	}
	while (RF69_ReadReg(REG_SYNCVALUE1_2F) != 0xaa
							&& HAL_GetTick()-startTime < _MAX_INIT_DELAY);
						//Read SyncValue1 0xAA
	
	startTime = HAL_GetTick();
		do
	{
		RF69_WriteReg(REG_SYNCVALUE1_2F, 0x55);
						//Write SyncValue1 0x55
		__asm volatile ("nop");
	}
	  while (RF69_ReadReg(REG_SYNCVALUE1_2F) != 0x55 && HAL_GetTick()-startTime < _MAX_INIT_DELAY);
						//Read SyncValue1 0x55
	
	if((HAL_GetTick() - startTime) > _MAX_INIT_DELAY)
	{
		return false;
	}
	//
	_deviceType = RF69_ReadReg(REG_VERSION_10);
						//Read Version == 0x24
	
    if (_deviceType == 00 || _deviceType == 0xff)
	{
		return false;
	}	
	RF69_SetModeIdle(); // Read		RegOpMode == 0x04
						// Write	RegOpMode 0x04
						// Read		RegIrqFlags1 == 0x80
	
	RF69_WriteReg(REG_FIFOTHRESH_3C,
						RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY
						| RF_FIFOTHRESH_DEF); // thresh 15 is default
						// Write	RegFifoThresh 0x80 ? 0x8F
	
	RF69_WriteReg(REG_TESTDAGC_6F, RF_DAGC_IMPROVED_LOWBETA0);
						// Write	RegTestDagc 0x30
	
	// If high power boost set previously, disable it
	RF69_WriteReg(REG_TESTPA1_5A, RF_TESTPA1_NORMAL);
						// Write	RegTestPa1 0x55
	RF69_WriteReg(REG_TESTPA2_5C, RF_TESTPA1_BOOST);
						// Write	RegTestPa2 0x5D

    // The following can be changed later by the user if necessary.
    // Set up default configuration
//    uint8_t syncwords[] = { 0x2d, 0xd4 };
    RF69_SetSyncWords(_defaultSyncWord, _defaultSyncWordLenght); // 
						// Read		RegSyncConfig == 0x98
						// Write	RegSyncValue1 0xAA
						// Write	RegSyncValue2 0xD4
						// Write	RegSyncValue3 0x55
						// Write	RegSyncConfig 0x90
    // Reasonably fast and reliable default speed and modulation
    RF69_SetModemConfig(_defaultModemConfig);
						// Write	RegDataModul 0x01
						// Write	RegBitrateMsb 0x01
						// Write	RegBitrateLsb 0x00
						// Write	RegFdevMsb 0x08
						// Write	RegFdevMsb 0x00
						// Write	RegRxBw 0xE1 ?
						// Write	RegAfcBw 0xE1
						// Write	RegPacketConfig1 0xD0
	RF69_WriteReg(REG_PAYLOADLENGTH_38, RF69_MAX_FIFO_LENGHT);
						// Write	RegPayloadLength 0x42

	// 3 would be sufficient, but this is the same as RF22's
    RF69_SetPreambleLength(_defaultPreambleLength);
						// Write	RegPreambleMsb 0x00
						// Write	RegPreambleLsb 0x40

    // An innocuous ISM frequency, same as RF22's
    RF69_SetFrequency(_defaultFreq);
						// Write	RegFrfMsb 0xD8
						// Write	RegFrfMid 0xC0
						// Write	RegFrfLsb 0x00

    // No encryption
    RF69_Set_AES_Key(NULL);
						// Read 	RegPacketConfig2 == 0x02
						// Write	RegPacketConfig2 0x02

    // +13dBm, same as power-on default
    RF69_SetTxPower(20, 1); 
						// Write	RegPaLevel 0x7F
						
	RF69_SetAdressThis(_DEFAULT_THIS_ADR);
						// Write	RegNodeAdrs 0xxx
	RF69_SetAdressTo(_DEFAULT_TO_ADR);
	
	return 1;
}

int8_t RF69_RssiRead()
{
    return -((int8_t)(RF69_ReadReg(REG_RSSIVALUE_24) >> 1));
}

int8_t RF69_TemperatureRead(void)
{
    // Caution: must be ins standby.
//    setModeIdle();
    RF69_WriteReg(REG_TEMP1_4E, RF_TEMP1_MEAS_START); // Start the measurement
    while (RF69_ReadReg(REG_TEMP1_4E) & RF_TEMP1_MEAS_RUNNING)
	{
		__asm volatile ("nop");
	}
	; // Wait for the measurement to complete
    return 166 - RF69_ReadReg(REG_TEMP2_4F); // Very approximate, based on observation
}

void RF69_ReadFIFO(void)
{

	
	if(_PacketMode == _PACKET_FIXED)
	{
		memset(&_packetFix, 0, sizeof(RF69_FIX_PACKET));
		RF69_ReadMultipleReg(REG_FIFO_00, (uint8_t*)&_packetFix, RF69_MAX_FIFO_LENGHT);
		if(/*_packet._header._HeaderTo != _thisAdress */0
			|| _packetFix._header._HeaderLenght <= RF69_HEADER_LENGHT
			|| _packetFix._header._HeaderLenght > RF69_MAX_FIFO_LENGHT)
		{
			_rxBufValid = false; // RF69_ReadFIFO
			rxBad++;
			return;
		}
		rxGood++;
		_rxBufValid = true; // RF69_ReadFIFO
	}
//	else
//	{

//	}


}
/******************************************************************************/
#if _ENABLE_UNLIMIT_PACKET ==1U

void RF69_SendUnlimitedLengthPacket(const uint8_t* data, uint16_t len)
{
	if((len == 0)
//		|| _mode != RF69_ModeTx 
		|| _flag_Rx_Busy
		|| _flag_Tx_Busy
//		|| _PacketMode == _PACKET_FIXED
		)
	{
		return;
	}
	static uint8_t size;
	LED_BLUE_ON;
//	DBG_ON;
	
	RF69_PacketMode(_PACKET_UNLIMIT); //Switch the packet reception mode to Variable mode
												//Переключаем режим приема пакетов в Variable mode
	RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_MAX);
	
	RF69_WaitPacketSent();	// Make sure we dont interrupt an outgoing message
							//Проверяем, что мы не прерываем исходящее сообщение
	RF69_SetModeIdle(); // Prevent RX while filling the fifo

	_unlimPacketSend._header._adresTo = _toAdress; 
	_unlimPacketSend._header._lenghtData = len;
//	if(len < RF_FIFOTHRESH_MAX)
//	{
//		RF69_WriteReg(REG_FIFOTHRESH_3C, len);
//	}
	memcpy((uint8_t*)&_unlimPacketSend._data, (uint8_t*)data, len);
	
	size = (len < (RF69_MAX_FIFO_LENGHT - _LENGHT_UNLIM_PACK_HEADER))?
				(len + _LENGHT_UNLIM_PACK_HEADER):RF69_MAX_FIFO_LENGHT;
				//размер = 	если длинна > размера FIFO -> RF69_MAX_FIFO_LENGHT,
				//			если длинна < размера FIFO -> длинна + заголовок пакета
	_packetLenght = len;
	
	_seekPacket = RF69_MAX_FIFO_LENGHT - _LENGHT_UNLIM_PACK_HEADER; //Позиция данных в пакете
//	RF69_StartTimer(_TIM_WATCH_PERIOD);
	_timer_c_StartTimer(_TIMER_RF69_WD_DELAY);
	RF69_WriteMultipleReg(REG_FIFO_00,
				(uint8_t*)&_unlimPacketSend,
				size); //Запись в FIFO
	RF69_SetModeTx(); // Start the transmitter
	_count_FIFO = RF69_MAX_FIFO_LENGHT - _LENGHT_UNLIM_PACK_HEADER;
//	DBG_OFF;
	LED_BLUE_OFF;
	if (len <= RF69_MAX_FIFO_LENGHT -  _LENGHT_UNLIM_PACK_HEADER)
	{
//		_timer_c_StopTimer();
		_flag_Tx_Busy = false;
		return;
	}
	else
	{
		_flag_Tx_Busy = true;
	}
}

#endif

#if _ENABLE_VAR_PACKET == 1U

void RF69_SendVariablePacket(const uint8_t* data, uint8_t len)
{
	if((len == 0)
//		|| _mode != RF69_ModeTx 
		|| _flag_Rx_Busy
		|| _flag_Tx_Busy
//		|| _PacketMode == _PACKET_FIXED
		)
	{
		return;
	}
	static uint8_t size;
	
	RF69_PacketMode(_PACKET_VARIABLE); //Switch the packet reception mode to Variable mode
												//Переключаем режим приема пакетов в Variable mode
	RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_MAX);
									// Write	RegFifoThresh		0x20
	
	RF69_WaitPacketSent(); // Make sure we dont interrupt an outgoing message
	RF69_SetModeIdle(); // Prevent RX while filling the fifo

	memset((uint8_t*)&_packetVar,0,sizeof(RF69_VAR_PACKET));
	_packetVar._header._HeaderLenght = len; 
	if(len < RF_FIFOTHRESH_MAX)
	{
		RF69_WriteReg(REG_FIFOTHRESH_3C, len);
	}
	memcpy((uint8_t*)&_packetVar._data, (uint8_t*)data, len);
	
	size = (len < (RF69_MAX_FIFO_LENGHT - sizeof(_packetVar._header)))?(len + sizeof(_packetVar._header)):RF69_MAX_FIFO_LENGHT;


//	RF69_StartTimer(_TIM_WATCH_PERIOD);
	RF69_WriteMultipleReg(REG_FIFO_00,
				(uint8_t*)&_packetVar,
				size);
	RF69_SetModeTx(); // Start the transmitter
									// Write	RegTestPa1		0x5D
									// Write	RegTestPa2		0x7C
	_timer_c_StartTimer(_TIMER_RF69_WD_DELAY);
	_count_FIFO = RF69_MAX_FIFO_LENGHT - sizeof(_packetVar._header);
	DBG_OFF;
	LED_BLUE_OFF;
	if (len <= RF69_MAX_FIFO_LENGHT -  sizeof(_packetVar._header))
	{
//		_timer_c_StopTimer();
		_flag_Tx_Busy = false;
		return;
	}
	else
	{
		_flag_Tx_Busy = true;
	}

}
#endif

/******************************************************************************/

bool RF69_Send(const uint8_t* data, uint8_t len)
{
	if(len == 0)
	{
		return false;
	}
	if (len > RF69_MAX_FIFO_LENGHT)
	{
		return false;
	}
	memset((uint8_t*)&_packetFix, 0, sizeof(_packetFix));
	memcpy(_packetFix._data, data, len);
	_packetFix._header._HeaderLenght = len; //Длинна
	RF69_PacketMode(_PACKET_FIXED);
	RF69_WaitPacketSent(); // Make sure we dont interrupt an outgoing message
	RF69_SetModeIdle(); // Prevent RX while filling the fifo

	RF69_WriteMultipleReg(REG_FIFO_00, (uint8_t*)&_packetFix, sizeof(RF69_FIX_PACKET));

	RF69_SetModeTx(); // Start the transmitter
	return true;
}
/******************************************************************************/

void RF69_Send_DIO0(void)
{
	_flagIRQ_DIO0 = false;
	// Get the interrupt cause
	static uint8_t irqflags2 = 0;
	irqflags2 = RF69_ReadReg(REG_IRQFLAGS2_28);
	if (irqflags2 & RF_IRQFLAGS2_PACKETSENT)
	{
	// A transmitter message has been fully sent
		_timer_c_StopTimer();
		RF69_SetModeIdle();// Clears FIFO
		txGood++;
	}
}

void RF69_Send_DIO1(void)
{
	uint8_t size;
	if(_PacketMode == _PACKET_FIXED
			|| !(_mode == RF69_ModeTx)
			|| !_flag_Tx_Busy
			)
	{
		return;
	}
//	RF69_StartTimer(_TIM_WATCH_PERIOD);
#if _ENABLE_VAR_PACKET == 1U

	if(_PacketMode == _PACKET_VARIABLE)
	{
		if((_packetVar._header._HeaderLenght - _count_FIFO) >= RF_FIFOTHRESH_MAX)
		{
			size = RF_FIFOTHRESH_MAX;
		}
		else
		{
			size = _packetVar._header._HeaderLenght - _count_FIFO;
		}
		RF69_WriteMultipleReg(REG_FIFO_00,		//Write FIFO
			(uint8_t*)&_packetVar._data[_count_FIFO],
			size);
		_count_FIFO += size; 		//Add the size of the transmitted packet to the counter
		if(_count_FIFO == _packetVar._header._HeaderLenght) //If the counter is equal to the length of the message, then we end
		{
			_timer_c_StopTimer(); //Stop Timer
			_flag_Tx_Busy = false;
		}
	}
#endif
	
#if _ENABLE_UNLIMIT_PACKET ==1U
	if(_PacketMode == _PACKET_UNLIMIT) //Если пакет Unlimit
	{

		if((_unlimPacketSend._header._lenghtData - _count_FIFO) >= RF_FIFOTHRESH_MAX)
		{
			//Если оставшийся размер больше FIFOTHRESH_MAX
			size = RF_FIFOTHRESH_MAX; //посылаем в FIFO FIFOTHRESH_MAX байт
		}
		else
		{
			//Иначе Посылаем оставшиеся данные
			size = _unlimPacketSend._header._lenghtData - _count_FIFO;
		}
		RF69_WriteMultipleReg(REG_FIFO_00,
			(uint8_t*)&_unlimPacketSend._data[_count_FIFO],
			size);
		_count_FIFO += size;
		if(_count_FIFO == _unlimPacketSend._header._lenghtData)
		{

			_timer_c_StopTimer();
			_flag_Tx_Busy = false;
		}
		
	}
#endif
}

/******************************************************************************/

void RF69_Interrupt_DIO0(void)
{
	_flagIRQ_DIO0 = true;
	if(_PacketMode == _PACKET_FIXED)
	{
/*		if(_mode == RF69_ModeRx)
		{
			_lastRssi = -((int8_t)(RF69_ReadReg(REG_RSSIVALUE_24) >> 1));
			RF69_ReadMultipleReg(REG_FIFO_00, (uint8_t*)&_packetFix, RF69_MAX_FIFO_LENGHT);
			if(
//						_packet._header._HeaderTo != _thisAdress 
						0
						|| _packetFix._header._HeaderLenght <= RF69_HEADER_LENGHT
						|| _packetFix._header._HeaderLenght > RF69_MAX_FIFO_LENGHT)
			{
				_rxBufValid = false; // RF69_ReadFIFO
				rxBad++;
				return;
			}
			rxGood++;
			_rxBufValid = true; // RF69_ReadFIFO
			RF69_SetModeIdle();// Clears FIFO

		}
*/
		if(_mode == RF69_ModeTx)
		{
			static uint8_t irqflags2 = 0;
			irqflags2 = RF69_ReadReg(REG_IRQFLAGS2_28);
			if (_mode == RF69_ModeTx && (irqflags2 & RF_IRQFLAGS2_PACKETSENT))
			{
			// A transmitter message has been fully sent
				RF69_SetModeIdle();// Clears FIFO
				txGood++;
			}
		}
		
	}

//	if(_mode == RF69_ModeRx
//		&& (_PacketMode == _PACKET_VARIABLE || _PacketMode == _PACKET_UNLIMIT)
///*		  && _flag_Rx_Busy*/
//		)
//	{
//		RF69_ReadFIFO_DIO0();
//	}
//	if(_mode == RF69_ModeTx
//		&&  (_PacketMode == _PACKET_VARIABLE || _PacketMode == _PACKET_UNLIMIT)
//		)
//	{
//		RF69_Send_DIO0();
//	}
#if _ENABLE_VAR_PACKET == 1U
	if(_mode == RF69_ModeRx
		&& (_PacketMode == _PACKET_VARIABLE)
/*		&& _flag_Rx_Busy*/
		)
	{
		RF69_ReadFIFO_DIO0();
	}
	if(_mode == RF69_ModeTx
		&&  (_PacketMode == _PACKET_VARIABLE)
		)
	{
		RF69_Send_DIO0();
	}

#endif
#if _ENABLE_UNLIMIT_PACKET == 1U
	if(_mode == RF69_ModeRx
		&& (_PacketMode == _PACKET_UNLIMIT)
/*		  && _flag_Rx_Busy*/
		)
	{
		RF69_ReadFIFO_DIO0();
	}
	if(_mode == RF69_ModeTx
		&&  (_PacketMode == _PACKET_UNLIMIT)
		)
	{
		RF69_Send_DIO0();
	}

#endif
}

//void RF69_Interrupt_DIO1(void)
//{
//		_flagIRQ_DIO1 = true;
//}

void RF69_Interrupt_DIO1_Rising(void)
{
	_flagIRQ_DIO1 = true;
	
#if _ENABLE_VAR_PACKET == 1U
	if(_mode == RF69_ModeRx
		&&  (_PacketMode == _PACKET_VARIABLE)
		)
	{
		RF69_ReadFIFO_DIO1();
	}
#endif

#if _ENABLE_UNLIMIT_PACKET == 1U
	if(_mode == RF69_ModeRx
		&&  (_PacketMode == _PACKET_UNLIMIT)
		)
	{
		RF69_ReadFIFO_DIO1();
	}

#endif	
}

void RF69_Interrupt_DIO1_Falling(void)
{
	_flagIRQ_DIO1 = true;
	
//	_flagIRQ_DIO1_Fall = true;
	if(_mode == RF69_ModeTx
		&& _PacketMode
		&& _flag_Tx_Busy)
	{
		RF69_Send_DIO1();
	}
}
bool RF69_Available(void)
{
	if(_mode == RF69_ModeTx)
	{
		return false;
	}
	RF69_SetModeRx();
	return _rxBufValid;
}

void RF69_Exit_Wait()
{
	_exitWaitAvailable = true;
}

bool RF69_WaitAvailable(void)
{
	while(!RF69_Available())
    {
		if(_flagIRQ_DIO0)
		{
			RF69_InterruptHandler();
		}
		if(_exitWaitAvailable)
		{
			_exitWaitAvailable = false;
			return false;
		}
		osDelay(1);
//		YIELD;
    }
	return true;
}

void RF69_ReadFIFO_DIO1()
{
	if(!_PacketMode 
		|| (_mode != RF69_ModeRx)
		|| _rxBufValid
		|| _flag_Tx_Busy
		)
	{
		return;
	}

#if _ENABLE_VAR_PACKET == 1U
	if(_PacketMode == _PACKET_VARIABLE)
	{
		_timer_c_StartTimer(_TIMER_RF69_WD_DELAY);

		if(!_flag_Rx_Busy)
		{
			_flag_Rx_Busy = true;
			_count_FIFO = 0;
			RF69_ReadMultipleReg(REG_FIFO_00,
				(uint8_t*)&_packetVar,
				RF_FIFOTHRESH_MAX);
			_sizeFIFO_data = _packetVar._header._HeaderLenght;
			_count_FIFO = RF_FIFOTHRESH_MAX - sizeof(_packetVar._header);
		}
		else
		{
			RF69_ReadMultipleReg(REG_FIFO_00,
				(uint8_t*)&_packetVar._data[_count_FIFO],
				RF_FIFOTHRESH_MAX);	
			_count_FIFO += RF_FIFOTHRESH_MAX;
		}
	}
#endif

#if _ENABLE_UNLIMIT_PACKET ==1U
	volatile uint8_t size;
	if(_PacketMode == _PACKET_UNLIMIT)
	{
		if(!_flag_Rx_Busy) //Если начало приема
		{
			_timer_c_StartTimer(_TIMER_RF69_WD_DELAY);
			
			_flag_Rx_Busy = true;
			_count_FIFO = 0;
			RF69_ReadMultipleReg(REG_FIFO_00, //Чтение из FIFO Заголовок
				(uint8_t*)&_unlimPacketSend,
				RF69_ReadReg(REG_FIFOTHRESH_3C));
			//Если длинна данных меньше RF_FIFOTHRESH_MAX
			if(_unlimPacketSend._header._lenghtData == 0)
			{
				_timer_c_StopTimer();
				RF69_SetModeIdle();
				_rxBufValid = true; //RF69_ReadFIFO_DIO1
			}
			if(_unlimPacketSend._header._lenghtData < RF_FIFOTHRESH_MAX)
			{
				//Прописываем в REG_FIFOTHRESH_3C длинну данных
				RF69_WriteReg(REG_FIFOTHRESH_3C, _unlimPacketSend._header._lenghtData);
			}
			else
			{
				//Иначе RF_FIFOTHRESH_MAX
				RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_MAX);
			}
			//
			_sizeFIFO_data = _unlimPacketSend._header._lenghtData;
//			_count_FIFO = RF_FIFOTHRESH_MAX - sizeof(_unlimPacketSend._header);
			_count_FIFO = 0;
		}
		else //Иначе продолжаем прием
		{
			volatile static int16_t res = 0;
			res = ((_unlimPacketSend._header._lenghtData - _count_FIFO));
			if(res >= RF_FIFOTHRESH_MAX)
			{
				_timer_c_StartTimer(_TIMER_RF69_WD_DELAY);
				
				RF69_ReadMultipleReg(REG_FIFO_00,
					(uint8_t*)&_unlimPacketSend._data[_count_FIFO],
					RF_FIFOTHRESH_MAX);	
				_count_FIFO += RF_FIFOTHRESH_MAX;
			}
			else
			{
				size = _unlimPacketSend._header._lenghtData - _count_FIFO;
				if(size)
				{
					RF69_ReadMultipleReg(REG_FIFO_00,
						(uint8_t*)&_unlimPacketSend._data[_count_FIFO],
						size);
				}
				_timer_c_StopTimer();
				RF69_SetModeIdle();
				RF69_WriteReg(REG_FIFOTHRESH_3C, sizeof(_UNLIM_HEADER)); //Прерывание после приема заголовка

				_flag_Rx_Busy = false;
				_rxBufValid = true; //RF69_ReadFIFO_DIO1
			}
		}
	}
#endif
}

void RF69_ReadFIFO_DIO0()
{
	volatile static uint8_t size = 0;
	if(!_PacketMode 
		//|| (_mode != RF69_ModeRx)
		|| _rxBufValid
		|| _flag_Tx_Busy
		)
	{
		return;
	}
#if _ENABLE_VAR_PACKET == 1U
	if(_PacketMode == _PACKET_VARIABLE)
	{
		if(!_flag_Rx_Busy && _mode == RF69_ModeRx)
		{
			RF69_ReadMultipleReg(REG_FIFO_00, (uint8_t*)&_packetVar, RF69_ReadReg(REG_FIFOTHRESH_3C));
			
		}
		if(_sizeFIFO_data > _count_FIFO)
		{
			
			size = _sizeFIFO_data - _count_FIFO;
			RF69_ReadMultipleReg(REG_FIFO_00,
				(uint8_t*)&_packetVar._data[_count_FIFO],
				size);	
		}
		_timer_c_StopTimer();
	}
#endif
	
#if _ENABLE_UNLIMIT_PACKET ==1U
/*
	if(_PacketMode == _PACKET_UNLIMIT)
	{
		if(!_flag_Rx_Busy && _mode == RF69_ModeRx)
		{
			//Прием заголовка
			RF69_ReadMultipleReg(REG_FIFO_00, 
					(uint8_t*)&_unlimPacketSend, RF69_ReadReg(REG_FIFOTHRESH_3C));
			//Если длинна данных меньше RF_FIFOTHRESH_MA
			if(_unlimPacketSend._header._lenghtData < RF_FIFOTHRESH_MAX)
			{
				//Записываем REG_FIFOTHRESH_3C длинну данных
				RF69_WriteReg(REG_FIFOTHRESH_3C, _unlimPacketSend._header._lenghtData);
			}
			else
			{
				//Иначе RF_FIFOTHRESH_MAX
				RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_MAX);
			}
			
		}
		if(_sizeFIFO_data > _count_FIFO)
		{
//			volatile static uint8_t cn = 0;
			size = _sizeFIFO_data - _count_FIFO;
			RF69_ReadMultipleReg(REG_FIFO_00,
				(uint8_t*)&_unlimPacketSend._data[_count_FIFO], 
				size);	
		}
//		else
//		{
//		}
	}
*/
#endif
//	HAL_TIM_Base_Stop_IT(&_TIMER_WATCH_HANDLE);

	_flag_Rx_Busy = false;
	_rxBufValid = true; //RF69_ReadFIFO_DIO0
	RF69_SetModeIdle();

}
#if _ENABLE_VAR_PACKET ==1U

bool RF69_RecvVariablePacket(uint8_t* buf, uint8_t* len)
{
	if (!RF69_Available())
	{
		return false;
	}
	if(*len < _packetVar._header._HeaderLenght)
	{
		return false;
	}
	memcpy(buf, &_packetVar._data, _packetVar._header._HeaderLenght);
	*len = _packetVar._header._HeaderLenght;
	_rxBufValid = false; //RF69_RecvVariablePacket
	return true;
}

#endif

#if _ENABLE_UNLIMIT_PACKET ==1U

bool RF69_RecvUnlimitPacket(uint8_t* buf, uint16_t* len)
{
	RF69_PacketMode(_PACKET_UNLIMIT);
	if (!RF69_Available())
	{
		return false;
	}
	if(*len <= _unlimPacketSend._header._lenghtData)
	{
		return false;
	}
	memcpy(buf, &_unlimPacketSend._data, _unlimPacketSend._header._lenghtData);
	*len = _unlimPacketSend._header._lenghtData;
	_rxBufValid = false; // RF69_RecvUnlimitPacket
	
	return true;
}
#endif

/******************************************************************************/

bool RF69_WaitAvailableTimeout(uint16_t timeout)
{
	unsigned long starttime = HAL_GetTick();
	while ((HAL_GetTick() - starttime) < timeout)
	{
		if(_flagIRQ_DIO0)
		{
			RF69_InterruptHandler();
		}
		if (RF69_Available())
		{
		   return true;
		}
		if(_exitWaitAvailable)
		{
			_exitWaitAvailable = false;
			return false;
		}
		YIELD;
		
//		osDelay(1);
	}
	return false;
}

void RF69_StopWaitAvailable(void)
{
	_exitWaitAvailable = true;
}

void RF69_InterruptHandler(void)
{
//	return;
	if(!_flagIRQ_DIO0 && !_flagIRQ_DIO1)
	{
		return;
	}

	if(_flagIRQ_DIO0 && _PacketMode == _PACKET_FIXED)
	{
		_flagIRQ_DIO0 = false;
		// Get the interrupt cause
		static uint8_t irqflags2 = 0;
		irqflags2 = RF69_ReadReg(REG_IRQFLAGS2_28);
		if (_mode == RF69_ModeTx && (irqflags2 & RF_IRQFLAGS2_PACKETSENT))
		{
		// A transmitter message has been fully sent
			RF69_SetModeIdle();// Clears FIFO
			txGood++;
		}
		// Must look for PAYLOADREADY, not CRCOK, since only PAYLOADREADY occurs _after_ AES decryption
		// has been done
		if (_mode == RF69_ModeRx && (irqflags2 & RF_IRQFLAGS2_PAYLOADREADY))
		{
			// A complete message has been received with good CRC
			_lastRssi = -((int8_t)(RF69_ReadReg(REG_RSSIVALUE_24) >> 1));
//			RF69_SetModeIdle();
			// Save it in our buffer
			if(_PacketMode) return;
			RF69_ReadFIFO();
		}
	}
	

}

bool RF69_Recv(uint8_t* buf, uint8_t* len)
{
	if (!RF69_Available())
	{
		return false;
	}
	if(*len < _packetFix._header._HeaderLenght)
	{
		*len = 0;
		_rxBufValid = false; //RF69_Recv Got the most recent message
		return false;
	}
	*len = _packetFix._header._HeaderLenght;
    if (buf && len)
    {
//		__ATOMIC_ACQUIRE;
//		if (*len >= _rxBufLenght)
//			*len = _rxBufLenght;
		memcpy(buf, (uint8_t*)&_packetFix._data, *len);
//		__ATOMIC_RELAXED;
    }
    _rxBufValid = false; //RF69_Recv Got the most recent message
    return true;
}



bool RF69_WaitPacketSent(void)
{
	uint32_t startTm = HAL_GetTick();

	while (_mode == RF69_ModeTx && (HAL_GetTick() - startTm) < 200)
	{
//		DBG_ON;
//		DBG_OFF;
		
		if(_flagIRQ_DIO0)
		{
//			DBG_ON;
//			DBG_OFF;
//			DBG_ON;
//			DBG_OFF;

			RF69_InterruptHandler();
		}
		YIELD; // Wait for any previous transmit to finish		
//		osDelay(1);
	}
	if((HAL_GetTick() - startTm) >= 200) 
	{
		return false;
	}

	return true;
}

//bool RF69_WaitPacketSentTimeout(uint16_t timeout)
//{
//	uint32_t startTm = HAL_GetTick();

//	while (_mode == RF69_ModeTx && (HAL_GetTick() - startTm) < 200)
//	{
//		if(_flagIRQ_DIO0)
//		{
//			RF69_InterruptHandler();
//		}
//		YIELD; // Wait for any previous transmit to finish		
////		osDelay(1);
//	}
//	if((HAL_GetTick() - startTm) >= 200) 
//	{
//		return false;
//	}

//	return true;
//}

void RF69_SetAdressThis(uint8_t adr)
{
	RF69_WriteReg(REG_NODEADRS_39, adr);
					// Write	RegNodeAdrs
_thisAdress = adr;
}

void RF69_SetAdressTo(uint8_t adr)
{
	_toAdress = adr;
}

void RF69_PacketMode(_PACKET_MODE isLong)
{
	if(_PacketMode == isLong)
	{
		return;
	}
	_PacketMode = isLong;
	uint8_t packet_conf = RF69_ReadReg(REG_PACKETCONFIG1_37) & ~RF_PACKET1_CRC_ON;
								// Read	RegPacketConfig1	0xD0

//	uint8_t packet_conf = RF69_ReadReg(REG_PACKETCONFIG1_37) |  RF_PACKET1_CRC_ON;
	switch(isLong)
	{
#if _ENABLE_VAR_PACKET == 1U
		case _PACKET_VARIABLE: 			//Пакет переменной длинны 
			RF69_WriteReg(REG_PAYLOADLENGTH_38, 255); //Длинна пакета = 255
								// Write	RegPayloadLength	0xFF
			RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_MAX); //
								// Write	RegFifoThresh		0x20
			packet_conf |= RF_PACKET1_FORMAT_VARIABLE;
			packet_conf &= ~RF_PACKET1_ADRSFILTERING_NODE;		//Отключение фильтрации адреса
			packet_conf &= ~RF_PACKET1_CRC_ON; //
			RF69_WriteReg(REG_PACKETCONFIG1_37, packet_conf); //0xC0
								// Write	RegPacketConfig1	0xC0
//			packet_conf = RF69_ReadReg(REG_PACKETCONFIG1_37);
			if(_flagUseAES)
			{
				RF69_Set_AES_Key(NULL);
			}
			break;
#endif			
#if _ENABLE_UNLIMIT_PACKET ==1U
		case _PACKET_UNLIMIT:			//Пакет неограниченной длинны 
			RF69_WriteReg(REG_PAYLOADLENGTH_38, 0); //Длинна пакета = 0
			RF69_WriteReg(REG_FIFOTHRESH_3C, sizeof(_UNLIM_HEADER)); //Прерывание после приема заголовка
//			RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_MAX);
			packet_conf &= ~RF_PACKET1_FORMAT_VARIABLE; //
			packet_conf |= RF_PACKET1_ADRSFILTERING_NODE;
			packet_conf &= ~RF_PACKET1_CRC_ON; //
			
			RF69_WriteReg(REG_PACKETCONFIG1_37, packet_conf);
			
			if(_flagUseAES)
			{
				RF69_Set_AES_Key(NULL);
			}
			break;
#endif
		default:					//Пакет фиксированной длинны 
			RF69_WriteReg(REG_PAYLOADLENGTH_38, RF69_MAX_FIFO_LENGHT); //Длинна пакета = размер буфера (66)
			RF69_WriteReg(REG_FIFOTHRESH_3C, RF_FIFOTHRESH_DEF); //Прерывание 
			packet_conf &= ~RF_PACKET1_FORMAT_VARIABLE;
//			packet_conf |= RF_PACKET1_ADRSFILTERING_NODE;		//Отключение фильтрации адреса
			packet_conf &= ~RF_PACKET1_ADRSFILTERING_NODE;		//Отключение фильтрации адреса
			packet_conf &= ~RF_PACKET1_CRC_ON; //
			RF69_WriteReg(REG_PACKETCONFIG1_37, packet_conf); //0x40
			
	}

}













//End File
