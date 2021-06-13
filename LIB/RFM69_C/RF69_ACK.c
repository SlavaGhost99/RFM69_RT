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
typedef struct 
{
	volatile uint16_t lenght;
	volatile uint32_t u32Rand;
	volatile uint8_t flags;
	volatile uint32_t crc;
	volatile uint8_t reserved8_0;
	volatile uint8_t reserved8_1;
	volatile uint16_t reserved16_0;
	volatile uint16_t reserved16_1;
	volatile uint32_t reserved32_0;
	volatile uint32_t reserved32_1;
}_ACK;

typedef struct
{
	uint16_t lenght;
	uint32_t u32Rand;
	uint8_t flags;
	uint32_t crc;
}_HEADER_ACK_PACK;

#if _ENABLE_VAR_PACKET == 1U
#define _VAR_PACKET_DATA_SIZE (255 - sizeof(_HEADER_ACK_PACK) - sizeof(RF69_HEADER_STRUCT))
typedef struct
{
	_HEADER_ACK_PACK _header;
	uint8_t _packet[_VAR_PACKET_DATA_SIZE];
}_PACKET_VAR_ACK;

volatile static _PACKET_VAR_ACK _var_pack;
#endif

#define _ACK_PACKET_SIZE	(sizeof(_ACK_PACKET))
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool SendACK(uint8_t *buf, uint16_t len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool ReceiveACK(uint8_t *buf, uint16_t len);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool MakeACK(uint8_t *buf, uint16_t len, _ACK* _ack);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
bool CompareACK(_ACK* _srcAck, _ACK* _desAck);


volatile static _ACK _ackRec;
volatile static _ACK _ackSnd;

extern bool _flag_Tx_Busy;

/******************************************************************************/
bool SendFixACK(const uint8_t *buf, uint8_t len)
{
	DBG_ON;
	DBG_OFF;
	RF69_PacketMode(_PACKET_FIXED);
	if(!RF69_Send(buf, len))
	{
		return false;
	}
	return ReceiveACK((uint8_t*)buf, len);
}

#if _ENABLE_VAR_PACKET == 1U
bool SendVarACK(const uint8_t *buf, uint8_t len)
{
	RF69_PacketMode(_PACKET_VARIABLE);
	_var_pack._header.lenght = len;
	_var_pack._header.crc = CalcCRC((uint8_t*)buf, len);
	GenRNG ((uint8_t*)&_var_pack._header.u32Rand, sizeof(_var_pack._header.u32Rand));
	RF69_SendVariablePacket((uint8_t*)buf, len);
	static uint8_t cnt = 0;
	cnt = 0;
	while(_flag_Tx_Busy)
	{
		if(cnt >100)
		{
			RF69_SetModeIdle();
			return false;
		}
		cnt++;
		osDelay(1);
	}
	return ReceiveACK ((uint8_t*)buf, len);
	
}
#endif

#if _ENABLE_UNLIMIT_PACKET == 1U

bool SendUnlimACK(const uint8_t *buf, uint16_t len)
{
	return false;
}
#endif
bool RecevFixACK(uint8_t *buf, uint8_t *len)
{
	return false;
}

bool RecevVarACK(uint8_t *buf, uint8_t *len)
{
	return false;
}

bool RecevUnlimACK(uint8_t *buf, uint16_t *len)
{
	return false;
}

/******************************************************************************/
bool SendACK(uint8_t *buf, uint16_t len)
{
	MakeACK(buf, len, (_ACK*)&_ackSnd);
	RF69_PacketMode(_PACKET_FIXED);
	return RF69_Send((uint8_t*)&_ackSnd, sizeof(_ACK));
}

bool ReceiveACK(uint8_t *buf, uint16_t len)
{
	MakeACK(buf, len, (_ACK*)&_ackSnd);
	if(!RF69_WaitAvailableTimeout(100))
	{
		return false;
	}
	volatile static uint8_t ln;
	ln = sizeof(_ACK);
	if(!RF69_Recv((uint8_t*)&_ackRec, (uint8_t*)&ln))
	{
		return false;
	}
	if(ln != sizeof(_ACK))
	{
		return false;
	}
	
	return CompareACK((_ACK*)&_ackSnd, (_ACK*)&_ackRec);
}

bool MakeACK(uint8_t *buf, uint16_t len, _ACK* _ack)
{
	_ack->lenght = len;
	_ack->crc = CalcCRC(buf, len);
	GenRNG((uint8_t*) &_ack->u32Rand, 4);
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

