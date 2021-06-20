// Header: RND_GEN.h
// File Name: RND_GEN.c
// Author:
// Date: 2021.06.12
#include "main.h"
#include <rtc.h>
#include "RND_GEN.h"

uint8_t const entropy_data[32] = {
                             0x9d, 0x20, 0x1a, 0x18, 0x9b, 0x6d, 0x1a, 0xa7, 0x0e,
                             0x79, 0x57, 0x6f, 0x36, 0xb6, 0xaa, 0x88, 0x55, 0xfd,
                             0x4a, 0x7f, 0x97, 0xe9, 0x71, 0x69, 0xb6, 0x60, 0x88,
                             0x78, 0xe1, 0x9c, 0x8b, 0xa5
                           };
/* Nonce. Non repeating sequence, such as a timestamp */
uint8_t nonce[] = {0xFE, 0xA9, 0x96, 0xD4, 0x62, 0xC5, 0xd9, 0xaf};
/* Personalization String */
uint8_t personalization_String[] = {0x1E, 0x6C, 0x7B, 0x82, 0xE5, 0xA5, 0x71, 0x8D};
//uint8_t RandomString[32] = {0, };

RNGstate_stt RNGstate;

RNGinitInput_stt RNGinit_st;

int32_t status = RNG_SUCCESS;
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
//int32_t InitRND(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void GetTimeStamp(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/

int32_t InitRND()
{
	GetTimeStamp();
	RNGinit_st.pmEntropyData = (uint8_t*) entropy_data;
	RNGinit_st.mEntropyDataSize = sizeof(entropy_data);
	RNGinit_st.pmNonce =  0;
	RNGinit_st.mNonceSize = 0;
	RNGinit_st.pmPersData = 0;
	RNGinit_st.mPersDataSize = 0;
//	RNGinit_st.pmNonce =  (uint8_t*) nonce;
//	RNGinit_st.mNonceSize = 4;
//	RNGinit_st.pmPersData = personalization_String;
//	RNGinit_st.mPersDataSize = sizeof( personalization_String );

	status = RNGinit(&RNGinit_st, &RNGstate);
	return status;
}

void GetTimeStamp(void)
{
	volatile static uint32_t *pVar = 0;
	volatile static RTC_TimeTypeDef time_str;
	volatile static uint32_t tr = 0;
	tr = hrtc.Instance->TR;
	HAL_RTC_GetTime(&hrtc, (RTC_TimeTypeDef*)&time_str, FORMAT_BIN);
	pVar = (uint32_t*)nonce;
//	nonce[0] = time_str.Hours;
//	nonce[1] = time_str.Minutes;
//	nonce[2] = time_str.Seconds;
	*pVar = tr;
//	pVar = (uint32_t*)&nonce[3];
//	*pVar = tr = hrtc.Instance->SSR;
	nonce[3] = hrtc.Instance->SSR;
}

int32_t GenRNG(uint8_t* buf, uint16_t len)
{
//	status = InitRND();
	if(status != RNG_SUCCESS)
	{
		return status;
	}
    status = RNGgenBytes(&RNGstate, NULL, buf, len);
//    status = RNGgenBytes(&RNGstate, NULL, RandomString, sizeof(RandomString));
	if(status != RNG_SUCCESS)
	{
		return status;
	}
//	return RNGfree(&RNGstate);
	return status;
}
int32_t GenRNG32(uint32_t* buf, uint16_t len)
{
	status = InitRND();
	if(status != RNG_SUCCESS)
	{
		return status;
	}
    status = RNGgenWords(&RNGstate, NULL, buf, len);
	if(status != RNG_SUCCESS)
	{
		return status;
	}
	return RNGfree(&RNGstate);
}

uint32_t rand32(void)
{
	uint32_t r;
	GenRNG32(&r, 1);
	return r;
}
