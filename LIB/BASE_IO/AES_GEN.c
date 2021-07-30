// Header: AES_GEN.h
// File Name: AES_GEN.c
// Author:
// Date: 2021.07.24

/******************************************************************************/
//Start File


/******************************************************************************/
//Include
#include <string.h>
#include "AES_GEN.h"
#include "AES_KEY.h"
#include "RND_GEN.h"
/******************************************************************************/
//Var

/******************************************************************************/
//Def

/******************************************************************************/
//Function
void __AES_Init(void);
/******************************************************************************/
void __AES_Init(void)
{
	static bool flag_AES_Init = 0;
	
}
#if __AES_CTR == 1u



volatile static uint8_t __AES_CTR_Key[CRL_AES256_KEY]; //Key 
volatile static uint8_t __AES_CTR_Key_Lenght = CRL_AES256_KEY; //Lenght

volatile static uint8_t __AES_CTR_IV[CRL_AES_BLOCK];
/******************************************************************************/

int32_t __AES_CTR_GEN_IV(void);


/******************************************************************************/

int32_t __AES_CTR_GEN_IV(void)
{
	return GenRNG((uint8_t*)__AES_CTR_IV, CRL_AES_BLOCK);
}
int32_t AES_CTR_Encrypt(uint8_t* InputMessage,
							uint32_t InputMessageLength,
							uint8_t  *OutputMessage,
							uint32_t *OutputMessageLength)
{
  AESCTRctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = 16;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = 16;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because CTR doesn't use any IV */
  error_status = AES_CTR_Encrypt_Init(&AESctx, (uint8_t*)__AES_CTR_Key, (uint8_t*)AK_IV );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data */
    error_status = AES_CTR_Encrypt_Append(&AESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);

    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AES_CTR_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}

//int32_t AES_CTR_Encrypt(uint8_t* InputMessage,
//							uint32_t InputMessageLength,
//							uint8_t  *OutputMessage,
//							uint32_t *OutputMessageLength)
//{

//	AESCTRctx_stt AESctx;

//	static uint32_t error_status = 0;
//	 error_status = AES_SUCCESS;

//	error_status = __AES_CTR_GEN_IV();
//	if(error_status)
//	{
//		return error_status;
//	}
//	int32_t outputLength = 0;

//	/* Set flag field to default value */
//	AESctx.mFlags = E_SK_DEFAULT;

//	/* Set key size to 16 (corresponding to AES-128) */
//	AESctx.mKeySize = __AES_CTR_Key_Lenght;

//	/* Set iv size field to IvLength*/
//	AESctx.mIvSize = CRL_AES_BLOCK;

//	/* Initialize the operation, by passing the key.
//	* Third parameter is NULL because CTR doesn't use any IV */
//	error_status = AES_CTR_Encrypt_Init(&AESctx,
//										(uint8_t*)__AES_CTR_Key,
//										(uint8_t*)__AES_CTR_IV );

//	/* check for initialization errors */
//	if (error_status == AES_SUCCESS)
//	{
//	/* Encrypt Data */
//		error_status = AES_CTR_Encrypt_Append(&AESctx,
//												InputMessage,
//												InputMessageLength,
//												OutputMessage,
//												&outputLength);

//		if (error_status == AES_SUCCESS)
//		{
//			/* Write the number of data written*/
//			*OutputMessageLength = outputLength;
//			/* Do the Finalization */
//			error_status = AES_CTR_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
//			/* Add data written to the information to be returned */
//			*OutputMessageLength += outputLength;
//		}
//	}

//	return error_status;
//}


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
int32_t AES_CTR_Decrypt(uint8_t* InputMessage,
							uint32_t InputMessageLength,
							uint8_t  *OutputMessage,
							uint32_t *OutputMessageLength)
{
	AESCTRctx_stt AESctx;

	uint32_t error_status = AES_SUCCESS;

	int32_t outputLength = 0;

	/* Set flag field to default value */
	AESctx.mFlags = E_SK_DEFAULT;

	/* Set key size to 16 (corresponding to AES-128) */
	AESctx.mKeySize = __AES_CTR_Key_Lenght;

	/* Set iv size field to IvLength*/
	AESctx.mIvSize = CRL_AES_BLOCK;

	/* Initialize the operation, by passing the key.
	* Third parameter is NULL because CTR doesn't use any IV */
	error_status = AES_CTR_Decrypt_Init(&AESctx,
										(uint8_t*)__AES_CTR_Key,
										(uint8_t*)__AES_CTR_IV );

	/* check for initialization errors */
	if (error_status == AES_SUCCESS)
	{
		/* Decrypt Data */
		error_status = AES_CTR_Decrypt_Append(&AESctx,
											  InputMessage,
											  InputMessageLength,
											  OutputMessage,
											  &outputLength);
		if (error_status == AES_SUCCESS)
		{
			/* Write the number of data written*/
			*OutputMessageLength = outputLength;
			/* Do the Finalization */
			error_status = AES_CTR_Decrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
			/* Add data written to the information to be returned */
			*OutputMessageLength += outputLength;
		}
	}

	return error_status;
}

/******************************************************************************/
void AES_CTR_GetIV		(uint8_t* IV)
{
	IV = (uint8_t*) __AES_CTR_IV;
}

int32_t AES_CTR_Set_Key (uint8_t* pKey, uint8_t keyLenght)
{
	if(keyLenght <= CRL_AES128_KEY)
	{
		__AES_CTR_Key_Lenght = CRL_AES128_KEY;
	}
	else if(keyLenght > CRL_AES128_KEY && keyLenght <= CRL_AES192_KEY)
	{
		__AES_CTR_Key_Lenght = CRL_AES192_KEY;
	}
	else
	{
		__AES_CTR_Key_Lenght = CRL_AES256_KEY;
	}
	if(keyLenght > CRL_AES256_KEY)
	{
		keyLenght = CRL_AES256_KEY;
	}
	memcpy((uint8_t*) __AES_CTR_Key, pKey, keyLenght);
}



	/**
  * @brief  AES CTR Encryption example.
  * @param  InputMessage: pointer to input message to be encrypted.
  * @param  InputMessageLength: input data message length in byte.
  * @param  AES128_Key: pointer to the AES key to be used in the operation
  * @param  InitializationVector: pointer to the Initialization Vector (IV)
  * @param  IvLength: IV length in bytes.
  * @param  OutputMessage: pointer to output parameter that will handle the encrypted message
  * @param  OutputMessageLength: pointer to encrypted message length.
  * @retval error status: can be AES_SUCCESS if success or one of
  *         AES_ERR_BAD_CONTEXT, AES_ERR_BAD_PARAMETER, AES_ERR_BAD_OPERATION
  *         if error occured.
  */
int32_t _AES_CTR_Encrypt(uint8_t* InputMessage,
										uint32_t InputMessageLength,
										uint8_t  *AES_Key,
										__AES_KEY_LENGHT  AES_KeyLenght,
										uint8_t  *InitializationVector,
										uint32_t  IvLength,
										uint8_t  *OutputMessage,
										uint32_t *OutputMessageLength)
{
  AESCTRctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = AES_KeyLenght;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because CTR doesn't use any IV */
  error_status = AES_CTR_Encrypt_Init(&AESctx, AES_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Encrypt Data */
    error_status = AES_CTR_Encrypt_Append(&AESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);

    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AES_CTR_Encrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


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
								uint32_t *OutputMessageLength)
{
  AESCTRctx_stt AESctx;

  uint32_t error_status = AES_SUCCESS;

  int32_t outputLength = 0;

  /* Set flag field to default value */
  AESctx.mFlags = E_SK_DEFAULT;

  /* Set key size to 16 (corresponding to AES-128) */
  AESctx.mKeySize = AES_KeyLenght;

  /* Set iv size field to IvLength*/
  AESctx.mIvSize = IvLength;

  /* Initialize the operation, by passing the key.
   * Third parameter is NULL because CTR doesn't use any IV */
  error_status = AES_CTR_Decrypt_Init(&AESctx, AES_Key, InitializationVector );

  /* check for initialization errors */
  if (error_status == AES_SUCCESS)
  {
    /* Decrypt Data */
    error_status = AES_CTR_Decrypt_Append(&AESctx,
                                          InputMessage,
                                          InputMessageLength,
                                          OutputMessage,
                                          &outputLength);
    if (error_status == AES_SUCCESS)
    {
      /* Write the number of data written*/
      *OutputMessageLength = outputLength;
      /* Do the Finalization */
      error_status = AES_CTR_Decrypt_Finish(&AESctx, OutputMessage + *OutputMessageLength, &outputLength);
      /* Add data written to the information to be returned */
      *OutputMessageLength += outputLength;
    }
  }

  return error_status;
}


#endif // __AES_CTR



/******************************************************************************/
//End File

