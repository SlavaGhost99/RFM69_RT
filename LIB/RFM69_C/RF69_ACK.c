// Header: RF69_ACK.h
// File Name: RF69_ACK.c
// Author:
// Date: 2021.06.06

#include "RF69_ACK.h"
#include "RFM69_.h"
#include <string.h>
#include "RND_GEN.h"
#include "CRC_GEN.h"

/******************************************************************************/
#define _MAX_WAIT_SEND		100 //время ожидания окончания передачи
								//transmission end timeout
#define _MAX_WAIT_RECV		100 //время ожидания окончания приема
								//waiting time for the end of receive
/******************************************************************************/
typedef struct 
{
	volatile uint16_t lenght;
	volatile uint32_t dataRand;
	volatile uint8_t flags;
	volatile uint32_t crc;
	volatile uint32_t sessionRand;
}_ACK;

typedef struct
{
	uint16_t lenght;
	uint32_t dataRand;
	uint8_t flags;
	uint32_t crc;
}_HEADER_ACK_PACK;

/******************************************************************************/
#define MAX_FIX_DATA_LENGHT (RF69_MAX_FIFO_LENGHT - sizeof(RF69_HEADER_STRUCT)) - sizeof(_HEADER_ACK_PACK)
typedef struct
{
	_HEADER_ACK_PACK _header;
	uint8_t _packet[MAX_FIX_DATA_LENGHT];
}_PACKET_FIX_ACK;
static _PACKET_FIX_ACK _fix_pack;

static uint16_t _buf_len; //Длинна буфера
volatile static uint32_t _crcPaket;
/******************************************************************************/

#if _ENABLE_VAR_PACKET == 1U
	#define _VAR_PACKET_DATA_SIZE (255 - sizeof(_HEADER_ACK_PACK) - sizeof(RF69_HEADER_STRUCT))
	typedef struct
	{
		_HEADER_ACK_PACK _header;
		uint8_t _packet[_VAR_PACKET_DATA_SIZE];
	}_PACKET_VAR_ACK;

	volatile static _PACKET_VAR_ACK _var_pack;
#endif
	
/******************************************************************************/
#if _ENABLE_UNLIMIT_PACKET == 1U
	typedef struct
	{
		_HEADER_ACK_PACK _header;
		uint8_t _packet[_MAX_UNLIM_BUF_LENGHT];
	}_PACKET_UNLIMIT_ACK;

	volatile static _PACKET_UNLIMIT_ACK _unlim_pack;

#endif
/******************************************************************************/

	
#define _ACK_PACKET_SIZE	(sizeof(_ACK_PACKET))
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool SendACK(_HEADER_ACK_PACK *header, uint8_t *buf);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool ReceiveACK(_HEADER_ACK_PACK *header, uint8_t *buf);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool MakeACK(_HEADER_ACK_PACK *header, uint8_t *buf, _ACK* _ack);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool CompareACK(_ACK* _srcAck, _ACK* _desAck);


volatile static _ACK _ackRec;
volatile static _ACK _ackSnd;

volatile static uint8_t cnt = 0;

extern bool _flag_Tx_Busy;
extern bool _flag_Rx_Busy;

/******************************************************************************/
bool SendFixACK(const uint8_t *buf, uint8_t len)
{
//	DBG_ON;
//	DBG_OFF;
	RF69_PacketMode(_PACKET_FIXED);
	_fix_pack._header.lenght = len;
	GenRNG((uint8_t*) &_fix_pack._header.dataRand, sizeof(&_fix_pack._header.dataRand));
	_fix_pack._header.crc = CalcCRC((uint8_t*)buf, len);
	memset(_fix_pack._packet, 0, sizeof(_fix_pack._packet));
	memcpy(_fix_pack._packet, buf, len);
	if(!RF69_Send((uint8_t*)&_fix_pack, len + sizeof(_HEADER_ACK_PACK)))
	{
		bad_Packet_send++;
		return false;
	}
//	RF69_WaitPacketSent();
	RF69_TimerStart(100); // Запуск таймера
	uint8_t ret = ReceiveACK(&_fix_pack._header, (uint8_t*)buf);
	RF69_TimerStop(); // Останов таймера
	if (ret)
	{
		ok_Packet_send ++;
	}
	else
	{
		err_ACK_receiv ++;
	}
	return ret;
}

#if _ENABLE_VAR_PACKET == 1U
bool SendVarACK(const uint8_t *buf, uint8_t len)
{
	RF69_PacketMode(_PACKET_VARIABLE);
	if(len > _VAR_PACKET_DATA_SIZE)
	{
		return false;
	}
	_var_pack._header.lenght = len;
	_var_pack._header.crc = CalcCRC((uint8_t*)buf, len);
	memcpy((uint8_t*)_var_pack._packet, buf, len);
	GenRNG ((uint8_t*)&_var_pack._header.dataRand, sizeof(_var_pack._header.dataRand));
	RF69_SendVariablePacket((uint8_t*)&_var_pack, len + sizeof(_HEADER_ACK_PACK));
	cnt = 0;
	while(_flag_Tx_Busy)
	{
		if(cnt > _MAX_WAIT_SEND)
		{
			bad_Packet_send++;
			RF69_SetModeIdle();
			return false;
		}
		cnt++;
		vTaskDelay(1);
	}
	vTaskDelay(5);
//	return 0;
	RF69_TimerStart(100); // Запуск таймера
	uint8_t ret  = ReceiveACK ((_HEADER_ACK_PACK*)&_var_pack._header, (uint8_t*)buf);
	RF69_TimerStop(); // Останов таймера
	if (ret)
	{
		ok_Packet_send ++;
	}
	else
	{
		err_ACK_receiv ++;
	}	
	return ret;
	
}
#endif

#if _ENABLE_UNLIMIT_PACKET == 1U

bool SendUnlimACK(const uint8_t *buf, uint16_t len)
{
	RF69_PacketMode(_PACKET_UNLIMIT);
	if(len > _MAX_UNLIM_BUF_LENGHT)
	{
		return false;
	}
	_unlim_pack._header.lenght = len;
	_unlim_pack._header.crc = CalcCRC((uint8_t*)buf, len);
	memcpy((uint8_t*)_unlim_pack._packet, buf, len);
	GenRNG ((uint8_t*)&_unlim_pack._header.dataRand, sizeof(_unlim_pack._header.dataRand));
	RF69_SendUnlimitedLengthPacket((uint8_t*)&_unlim_pack, len + sizeof(_HEADER_ACK_PACK));
	cnt = 0;
	while(_flag_Tx_Busy)
	{
		if(cnt > _MAX_WAIT_SEND)
		{
			bad_Packet_send++;
			RF69_SetModeIdle();
			return false;
		}
		cnt++;
		vTaskDelay(1);
	}
//	vTaskDelay(5);
//	return 0;

	RF69_TimerStart(100); // Запуск таймера
	bool ret = ReceiveACK ((_HEADER_ACK_PACK*)&_unlim_pack._header, (uint8_t*)buf);
	RF69_TimerStop(); // Останов таймера
	if (ret)
	{
		ok_Packet_send ++;
	}
	else
	{
		err_ACK_receiv ++;
	}	
	return ret;
}
#endif
bool RecevFixACK(uint8_t *buf, uint8_t *len)
{
	//Ожидание приема
	RF69_PacketMode(_PACKET_FIXED);
	RF69_SetModeIdle();

	if(!RF69_WaitAvailableTimeout(500))
	{
		return false;
	}
	_buf_len = sizeof(_PACKET_FIX_ACK); //Максимальная длинна
	if(!RF69_Recv((uint8_t*)&_fix_pack, (uint8_t*)&_buf_len))
	{
		return false;
	}
	//Проверка CRC
	_crcPaket = CalcCRC(_fix_pack._packet, _fix_pack._header.lenght);
	if(_crcPaket != _fix_pack._header.crc)
	{
		return false;
	}
	//Проверка длинны
	if(_buf_len != _fix_pack._header.lenght + sizeof(_HEADER_ACK_PACK))
	{
		return false;
	}
	
	vTaskDelay(rand32()%20 + 5);
	memcpy(buf, _fix_pack._packet, _fix_pack._header.lenght);
	*len = _fix_pack._header.lenght;
	//Посылка подтверждения
	return SendACK(&_fix_pack._header, (uint8_t*)&_fix_pack._packet);
}
#if _ENABLE_VAR_PACKET == 1U

bool RecevVarACK(uint8_t *buf, uint8_t *len)
{
	RF69_PacketMode(_PACKET_VARIABLE);
	RF69_SetModeIdle();
	if(!RF69_WaitAvailableTimeout(500))
	{
		return false;
	}
	_buf_len = 255; //Максимальная длинна
	
	if (!RF69_RecvVariablePacket((uint8_t*)&_var_pack, (uint8_t*)&_buf_len))
	{
		return false;
	}
	cnt = 0;
	while(_flag_Rx_Busy)
	{
		if(cnt > _MAX_WAIT_RECV)
		{
			RF69_SetModeIdle();
			return false;
		}
		cnt++;
		vTaskDelay(1);
	}
//	return 0;
	_crcPaket = CalcCRC((uint8_t*)&_var_pack._packet, _var_pack._header.lenght);
	if(_crcPaket != _var_pack._header.crc)
	{
		return false;
	}
	//Проверка длинны
	if(_buf_len != _var_pack._header.lenght + sizeof(_HEADER_ACK_PACK))
	{
		return false;
	}
	memcpy(buf, (uint8_t*)_var_pack._packet, _var_pack._header.lenght);
	*len = _fix_pack._header.lenght;
	vTaskDelay(rand32()%20 + 5);
	//Посылка подтверждения
	return SendACK((_HEADER_ACK_PACK*)&_var_pack._header, (uint8_t*)&_var_pack._packet);

}
#endif

bool RecevUnlimACK(uint8_t *buf, uint16_t *len)
{
	RF69_PacketMode(_PACKET_UNLIMIT);
	RF69_SetModeIdle();
	if(!RF69_WaitAvailableTimeout(500))
	{
		return false;
	}
	_buf_len = _MAX_UNLIM_BUF_LENGHT; //Максимальная длинна
	
	if (!RF69_RecvUnlimitPacket((uint8_t*)&_unlim_pack, (uint16_t*)&_buf_len))
	{
		return false;
	}
	cnt = 0;
	while(_flag_Rx_Busy) //Ожидание окончания приема
	{
		if(cnt > _MAX_WAIT_RECV)
		{
			RF69_SetModeIdle();
			return false;
		}
		cnt++;
		vTaskDelay(1);
	}
//	return 0;
	_crcPaket = CalcCRC((uint8_t*)&_unlim_pack._packet, _unlim_pack._header.lenght);
	if(_crcPaket != _unlim_pack._header.crc)
	{
		return false;
	}
	//Проверка длинны
	if(_buf_len != _unlim_pack._header.lenght + sizeof(_HEADER_ACK_PACK))
	{
		return false;
	}
	memcpy(buf, (uint8_t*)_unlim_pack._packet, _unlim_pack._header.lenght);
	*len = _fix_pack._header.lenght;
	osDelay(rand32()%20 + 5);
	//Посылка подтверждения
	return SendACK((_HEADER_ACK_PACK*)&_unlim_pack._header, (uint8_t*)&_unlim_pack._packet);

}

/******************************************************************************/
bool SendACK(_HEADER_ACK_PACK *header, uint8_t *buf)
{
	RF69_PacketMode(_PACKET_FIXED);
	MakeACK(header, buf, (_ACK*)&_ackSnd);
	RF69_PacketMode(_PACKET_FIXED);
	return RF69_Send((uint8_t*)&_ackSnd, sizeof(_ACK));
}

bool ReceiveACK(_HEADER_ACK_PACK *header, uint8_t *buf)
{
	RF69_PacketMode(_PACKET_FIXED);
	MakeACK(header, buf, (_ACK*)&_ackSnd);
	if(!RF69_WaitAvailableTimeout(100))
	{
//		RF69_TimerStop();
		return false;
	}
	volatile static uint8_t ln;
	ln = sizeof(_ACK);
	if(!RF69_Recv((uint8_t*)&_ackRec, (uint8_t*)&ln))
	{
//		RF69_TimerStop();
		return false;
	}
	if(ln != sizeof(_ACK))
	{
//		RF69_TimerStop();
		return false;
	}
	
//	RF69_TimerStop();
	return CompareACK((_ACK*)&_ackSnd, (_ACK*)&_ackRec);
}

bool MakeACK(_HEADER_ACK_PACK *header, uint8_t *buf, _ACK* _ack)
{
	
	_ack->lenght = header->lenght;
	_ack->crc = CalcCRC(buf, header->lenght);
	_ack->dataRand = header->dataRand;
	GenRNG((uint8_t*)_ack->sessionRand, sizeof(_ack->sessionRand));
	return false;
}

bool CompareACK(_ACK* _srcAck, _ACK* _desAck)
{
	if(_srcAck->crc != _desAck->crc)
	{
		return false;
	}
	if(_srcAck->lenght != _desAck->lenght)
	{
		return false;
	}
	
	return true;
}






//End file

