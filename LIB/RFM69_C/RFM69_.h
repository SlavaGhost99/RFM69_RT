// Header: RFM69_.h
// File Name: 
// Author:
// Date: 2020.04.12
/******************************************************************************/
#ifndef ___RFM69_C_H___
#define ___RFM69_C_H___
//Start file

#define RF69_WRITE_MASK		0x80

//#include "stdint.h"
#include <stdbool.h>
#include "main.h"
#include "cmsis_os.h"
#include "BASE_DEF.h"
#include "RFM69registers.h"
#include "RFM69_Config.h"

typedef struct
{
	uint8_t		_HeaderLenght;		//Packet lenght
//	uint8_t		_HeaderTo;			//Receiver address. Адрес получателя. 
//	uint8_t		_HeaderFrom;		//The address of the transmitter. Адрес передатчика.
//	uint8_t		_HeaderVersion;		//Version
} RF69_HEADER_STRUCT;

#define RF69_MAX_FIX_BUF_LEN (RF69_MAX_FIFO_LENGHT - sizeof(RF69_HEADER_STRUCT))
typedef struct
{
	RF69_HEADER_STRUCT _header;
	uint8_t _data[RF69_MAX_FIX_BUF_LEN];
} RF69_FIX_PACKET;
/******************************************************************************/
#if _ENABLE_VAR_PACKET ==1U
	typedef struct
	{
		RF69_HEADER_STRUCT _header;
		uint8_t _data[255 - sizeof(RF69_HEADER_STRUCT)];
	} RF69_VAR_PACKET;
#endif

/******************************************************************************/
#if _ENABLE_UNLIMIT_PACKET ==1U
	typedef struct
	{
		uint8_t _adresTo;
		uint16_t _lenghtData;
	}_UNLIM_HEADER;
	typedef struct
	{
		_UNLIM_HEADER _header;
		uint8_t _data[_MAX_UNLIM_BUF_LENGHT];
	}RF69_UNLIM_PACKET;
#endif
/******************************************************************************/
#define _NSS_PIN			NSS_Pin
#define _NSS_PORT			NSS_GPIO_Port
#define _NSS_ON				HAL_GPIO_WritePin(_NSS_PORT, _NSS_PIN , GPIO_PIN_RESET)
#define _NSS_OFF			HAL_GPIO_WritePin(_NSS_PORT, _NSS_PIN , GPIO_PIN_SET)
#define _NSS_READ			HAL_GPIO_ReadPin(_NSS_PORT, _NSS_PIN)

#define _READ_MASK			0x80

#define _FLAG_ACKNOWLEDGE 			0x01
#define _FLAG_END_BLOCK				0x02
#define _FLAG_REQU_WANT_TO_SEND		0x04	//Request "I want to send file". Запрос "Хочу отправить файл"
#define _FLAG_READY_TO_ACCEPT		0x08	//The answer is "Ready to accept block.". Ответ "Готов принять блок".

#define _FLAG_FILE_HEADER			0x80
/******************************************************************************/

#define RF69_HEADER_LENGHT				sizeof(RF69_HEADER_STRUCT)
#define RF69_MAX_PAYLOAD_LENGHT			(RF69_MAX_FIFO_LENGHT - RF69_HEADER_LENGHT)
#define RF69_ACK_LENGHT					sizeof(RF69_ACK_STRUCT)
#define DATA_FILE_HEADER_LENGHT			sizeof(DATA_FILE_HEADER_STRUCT)
#define DATA_REQUEST_LENGHT				sizeof(DATA_REQUEST_STRUCT)

#define RF69_MAX_TIMEOUT_RECEIVE_ACK	200
#define RF69_MAX_TIMEOUT_RECEIVE_BLOCK	250

#define RF69_MAX_FILE_SIZE				255
/******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
//Interrupts
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
/*__weak*/ void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);

	/***************************************************************************
	 * @brief  
	 * @param  None
	 * @retval None
	 **************************************************************************/
/*__weak*/ void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);

#endif

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1U) //See to stm32f4xx_hal_conf.h

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
/******************************************************************************/
#define RF69_BROADCAST_ADDRESS	255
/******************************************************************************/
//Struct
typedef struct 
{
	uint8_t    reg_02;		///< Value for register REG_02_DATAMODUL
	uint8_t    reg_03;		///< Value for register REG_03_BITRATEMSB
	uint8_t    reg_04;		///< Value for register REG_04_BITRATELSB
	uint8_t    reg_05;		///< Value for register REG_05_FDEVMSB
	uint8_t    reg_06;		///< Value for register REG_06_FDEVLSB
	uint8_t    reg_19;		///< Value for register REG_19_RXBW
	uint8_t    reg_1a;		///< Value for register REG_1A_AFCBW
	uint8_t    reg_37;		///< Value for register REG_37_PACKETCONFIG1
} ModemConfig;

typedef enum
{
	FSK_Rb2Fd5 = 0,		///< FSK, Whitening, Rb = 2kbs,    Fd = 5kHz
	FSK_Rb2_4Fd4_8,  	///< FSK, Whitening, Rb = 2.4kbs,  Fd = 4.8kHz 
	FSK_Rb4_8Fd9_6,  	///< FSK, Whitening, Rb = 4.8kbs,  Fd = 9.6kHz 
	FSK_Rb9_6Fd19_2, 	///< FSK, Whitening, Rb = 9.6kbs,  Fd = 19.2kHz
	FSK_Rb19_2Fd38_4,	///< FSK, Whitening, Rb = 19.2kbs, Fd = 38.4kHz
	FSK_Rb38_4Fd76_8,	///< FSK, Whitening, Rb = 38.4kbs, Fd = 76.8kHz
	FSK_Rb57_6Fd120, 	///< FSK, Whitening, Rb = 57.6kbs, Fd = 120kHz
	FSK_Rb125Fd125,  	///< FSK, Whitening, Rb = 125kbs,  Fd = 125kHz
	FSK_Rb250Fd250,  	///< FSK, Whitening, Rb = 250kbs,  Fd = 250kHz
	FSK_Rb55555Fd50, 	///< FSK, Whitening, Rb = 55555kbs,Fd = 50kHz for RFM69 lib compatibility
	
	GFSK_Rb2Fd5,		///< GFSK, Whitening, Rb = 2kbs,    Fd = 5kHz
	GFSK_Rb2_4Fd4_8, 	///< GFSK, Whitening, Rb = 2.4kbs,  Fd = 4.8kHz
	GFSK_Rb4_8Fd9_6, 	///< GFSK, Whitening, Rb = 4.8kbs,  Fd = 9.6kHz
	GFSK_Rb9_6Fd19_2,   ///< GFSK, Whitening, Rb = 9.6kbs,  Fd = 19.2kHz
	GFSK_Rb19_2Fd38_4,  ///< GFSK, Whitening, Rb = 19.2kbs, Fd = 38.4kHz
	GFSK_Rb38_4Fd76_8,  ///< GFSK, Whitening, Rb = 38.4kbs, Fd = 76.8kHz
	GFSK_Rb57_6Fd120,   ///< GFSK, Whitening, Rb = 57.6kbs, Fd = 120kHz
	GFSK_Rb125Fd125,    ///< GFSK, Whitening, Rb = 125kbs,  Fd = 125kHz
	GFSK_Rb250Fd250,    ///< GFSK, Whitening, Rb = 250kbs,  Fd = 250kHz
	GFSK_Rb55555Fd50,   ///< GFSK, Whitening, Rb = 55555kbs,Fd = 50kHz

	OOK_Rb1Bw1,         ///< OOK, Whitening, Rb = 1kbs,    Rx Bandwidth = 1kHz. 
	OOK_Rb1_2Bw75,      ///< OOK, Whitening, Rb = 1.2kbs,  Rx Bandwidth = 75kHz. 
	OOK_Rb2_4Bw4_8,     ///< OOK, Whitening, Rb = 2.4kbs,  Rx Bandwidth = 4.8kHz. 
	OOK_Rb4_8Bw9_6,     ///< OOK, Whitening, Rb = 4.8kbs,  Rx Bandwidth = 9.6kHz. 
	OOK_Rb9_6Bw19_2,    ///< OOK, Whitening, Rb = 9.6kbs,  Rx Bandwidth = 19.2kHz. 
	OOK_Rb19_2Bw38_4,   ///< OOK, Whitening, Rb = 19.2kbs, Rx Bandwidth = 38.4kHz. 
	OOK_Rb32Bw64,       ///< OOK, Whitening, Rb = 32kbs,   Rx Bandwidth = 64kHz. 

//	Test,
} ModemConfigChoice;

typedef enum
{
	RF69_ModeInitialising = 0,	///< Transport is initialising. Initial default value until init() is called..
	RF69_ModeSleep,				///< Transport hardware is in low power sleep mode (if supported)
	RF69_ModeIdle,				///< Transport is idle.
	RF69_ModeTx,				///< Transport is in the process of transmitting a message.
	RF69_ModeRx,				///< Transport is in the process of receiving a message.
//	RF69_ModeCad,				///< Transport is in the process of detecting channel activity (if supported)
} RF69_Mode;


typedef enum
{
	_PACKET_FIXED = 0u,
	_PACKET_VARIABLE,
	_PACKET_UNLIMIT
}_PACKET_MODE;


/******************************************************************************/

volatile static uint8_t _thisAdress = 1;
volatile static uint8_t _toAdress = 2;

/******************************************************************************/
//SPI Functions

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_WriteReg(uint8_t reg, uint8_t data);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
uint8_t RF69_ReadReg(uint8_t reg);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_WriteMultipleReg(uint8_t reg, uint8_t *data, uint16_t len);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_ReadMultipleReg(uint8_t reg, uint8_t *data, uint16_t len);


/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_Reset(void);

/******************************************************************************/
//RFM69 Functions
/***************************************************************************
 * @brief  Initialize RFM69 band
 * @param  None
 * @retval None
 **************************************************************************/
uint8_t RF69_Init(void); 

/***************************************************************************
 * @brief  Set this address
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetAdressThis(uint8_t adr);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_SetAdressTo(uint8_t adr);

/*******************************************************************************
 * @brief  
 * @param  None
 * @retval None
 *******************************************************************************/
void RF69_SetModeIdle(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetModeRx(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetModeTx(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetOpMode(uint8_t mode);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetTxPower(int8_t power, uint8_t _IsHighPowerModule);

/***************************************************************************
 * @brief  Sets registers from a canned modem configuration structure
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetModemRegisters(const ModemConfig* config);

/***************************************************************************
 * @brief  Set one of the canned FSK Modem configs
 * @param  None
 * @retval Returns true if its a valid choice
 **************************************************************************/

uint8_t RF69_SetModemConfig(ModemConfigChoice index);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetPreambleLength(uint16_t bytes);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetSyncWords(const uint8_t* syncWords, uint8_t len);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_Set_AES_Key(uint8_t* key);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetFrequency(float freq);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_SetModeSleep(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
__inline int8_t RF69_RssiRead(void);

/******************************************************************************/
//Transmit & Receive fuinctions
/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_ReadFIFO(void);

#if _ENABLE_VAR_PACKET == 1U
	/*******************************************************************************
	* @brief  
	* @param  None
	* @retval None
	*******************************************************************************/
	bool RF69_RecvVariablePacket(uint8_t* buf, uint8_t* len);
#endif

#if _ENABLE_UNLIMIT_PACKET ==1U
	/*******************************************************************************
	* @brief  
	* @param  None
	* @retval None
	*******************************************************************************/
	bool RF69_RecvUnlimitPacket(uint8_t* buf, uint16_t* len);
#endif

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
bool RF69_Recv(uint8_t* buf, uint8_t* len);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
bool RF69_Send(const uint8_t* data, uint8_t len);

#if _ENABLE_VAR_PACKET == 1U
	/*******************************************************************************
	* @brief  
	* @param  None
	* @retval None
	*******************************************************************************/
void RF69_SendVariablePacket(const uint8_t* data, uint8_t len);
#endif

#if _ENABLE_UNLIMIT_PACKET ==1U
	/*******************************************************************************
	* @brief  
	* @param  None
	* @retval None
	*******************************************************************************/
void RF69_SendUnlimitedLengthPacket(const uint8_t* data, uint16_t len);
#endif

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_Interrupt_DIO0(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_Interrupt_DIO1(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_Interrupt_DIO1_Rising(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_Interrupt_DIO1_Falling(void);


/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
bool RF69_Available(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
bool RF69_WaitAvailable(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
bool RF69_WaitAvailableTimeout(uint16_t timeout);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_Exit_Wait(void);
/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_StopWaitAvailable(void);

/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
void RF69_InterruptHandler(void);


/***************************************************************************
 * @brief  
 * @param  None
 * @retval None
 **************************************************************************/
bool RF69_WaitPacketSent(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void RF69_PacketMode(_PACKET_MODE isLong);



#ifdef __cplusplus
}
#endif
//End file
#endif //___RFM69_C_H___
