/******************************************************************************/
//Start File	AES_KEY.h
// Header: 
// File Name: AES_KEY.h
// Author: 
// Date: 2021.07.25
/******************************************************************************/
#ifndef ___AES_KEY_INC__
#define ___AES_KEY_INC__

//Start File


#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
//Include
#include "main.h"
#include "crypto.h"

/******************************************************************************/
//Define
#define PLAINTEXT_LENGTH 64

/******************************************************************************/
//include files


/******************************************************************************/
//Var
extern uint8_t AK_Key128[CRL_AES128_KEY];
extern uint8_t AK_Key192[CRL_AES192_KEY];
extern uint8_t AK_Key256[CRL_AES256_KEY];
extern uint8_t AK_IV[CRL_AES_BLOCK];
extern uint8_t AK_Plaintext[PLAINTEXT_LENGTH];
//extern uint32_t AK_OutputMessageLength;
//extern uint8_t AK_OutputMessage[PLAINTEXT_LENGTH];
//extern uint8_t AK_EncryptMessage[PLAINTEXT_LENGTH];
//volatile static uint8_t AK_EncryptMessage[PLAINTEXT_LENGTH];
//volatile static uint8_t AK_OutputMessage[PLAINTEXT_LENGTH];

/******************************************************************************/
//Function

/******************************************************************************/

#ifdef __cplusplus
}
#endif

/******************************************************************************/
#endif //___AES_KEY_INC__

//End File
