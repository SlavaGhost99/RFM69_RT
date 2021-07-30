/******************************************************************************/
//Start File
// Header: 
// File Name: AES_GEN.h
// Author: 
// Date:
/******************************************************************************/
#ifndef ___AES_GEN_INC__
#define ___AES_GEN_INC__

//Start File

/******************************************************************************/
//Include

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
//include files
#include "main.h"
#include "crypto.h"

//Define
/******************************************************************************/
//*** <<< Use Configuration Wizard in Context Menu >>> ***
//<h> Select AES mode
	//<e> AES CTR
		#define __AES_CTR	1u
	//</e> AES CTR
//</h>

//*** <<< end of configuration section >>>    ***

/******************************************************************************/
//Var
typedef enum
{
	__AES128 = 16u,
	__AES192 = 24u,
	__AES256 = 32u
}__AES_KEY_LENGHT;
/******************************************************************************/
//Function

#if __AES_CTR == 1u

/*******************************************************************************
* @brief  
* @param Input Message
* @param Input Message Lenght
* @param Output Message 
* @param Output Message Lenght
* @param Output Initialization Vector
* @retval state
*******************************************************************************/
int32_t AES_CTR_Encrypt(uint8_t*  InputMessage,
							uint32_t  InputMessageLength,
							uint8_t  *OutputMessage,
							uint32_t *OutputMessageLength);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
int32_t AES_CTR_Decrypt(uint8_t*  InputMessage,
							uint32_t  InputMessageLength,
							uint8_t  *OutputMessage,
							uint32_t *OutputMessageLength);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
int32_t AES_CTR_Set_Key (uint8_t* pKey, uint8_t keyLenght);

/*******************************************************************************
* @brief  
* @param  Returning a pointer to IV_buffer
* @retval None
*******************************************************************************/
void AES_CTR_GetIV		(uint8_t* IV);

/******************************************************************************/

/**
  * @brief  AES CTR Decryption example.
  * @param  InputMessage: pointer to input message to be decrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the decrypted message
  * @param  OutputMessageLength: pointer to decrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
  *         if error occured.
  */
int32_t _AES_CTR_Decrypt(uint8_t* InputMessage,
								uint32_t InputMessageLength,
								uint8_t  *AES_Key,
								__AES_KEY_LENGHT  AES_KeyLenght,
								uint8_t  *InitializationVector,
								uint32_t  IvLength,
								uint8_t  *OutputMessage,
								uint32_t *OutputMessageLength);


/******************************************************************************/

int32_t _AES_CTR_Encrypt(uint8_t* InputMessage,
										uint32_t InputMessageLength,
										uint8_t  *AES_Key,
										__AES_KEY_LENGHT  AES_KeyLenght,
										uint8_t  *InitializationVector,
										uint32_t  IvLength,
										uint8_t  *OutputMessage,
										uint32_t *OutputMessageLength);




#endif // __AES_CTR
#ifdef __cplusplus
}
#endif

/******************************************************************************/
#endif //___AES_GEN_INC__

//End File
