/******************************************************************************/
//Start File "ssd1306.h"
// Header: 
// File Name: 
// Author: 
// Date: 
/******************************************************************************/


//End File

//	Deze library is door Olivier Van den Eede 2016 geschreven en aangepast voor gebruik met
//	Stm32 microcontrollers en maakt gebruik van de HAL-i2c library's.
//
//	Deze library is gemaakt om gebruik te kunnen maken van een ssd1306 gestuurd oled display.
//	Voor het gebruik moeten zeker de onderstaande defines juist ingesteld worden.
//	Zoals de gebruikte i2c poort en de groote van het scherm.
//
//	De library maakt gebruik van 2 files (fonts.c/h) Hierin staan 3 fonts beschreven.
//	Deze fonts kunnen zo gebruikt worden: 	- Font_7x10
//											- Font_11x18
//											- Font_16x26

//*** <<< Use Configuration Wizard in Context Menu >>> ***

//<o> Select I2C Interface
//<1=>I2C1
//<2=>I2C2
//<3=>I2C3
#define _I2C_INTERFACE 1U

#include "stm32f4xx_hal.h"
#include "fonts.h"

//*** <<< end of configuration section >>>    ***

#ifndef __SSD13006_FILE__
#define __SSD13006_FILE__

// i2c port naam in main programma gegenereerd door cube
// I2C address 
#if _I2C_INTERFACE == 1
#define SSD1306_I2C_PORT		hi2c1
#elif _I2C_INTERFACE == 2		
#define SSD1306_I2C_PORT		hi2c2
#elif _I2C_INTERFACE == 2		
#define SSD1306_I2C_PORT		hi2c3
#else
#error "Select I2C Interfase"
#endif

#define SSD1306_I2C_ADDR        0x78
// SSD1306 width in pixels
#define SSD1306_WIDTH           128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT          64


//
//	Enum voor de kleuren van het scherm Black en White
//
typedef enum {
	Black = 0x00, /*!< Black color, no pixel */
	White = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR;

//
//	Struct om wijzigingen bij te houden
//
typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;

//	De i2c poort staat in de main
extern I2C_HandleTypeDef SSD1306_I2C_PORT;

//
//	De functies definities van de functies die gebruikt kunnen worden
//
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
uint8_t ssd1306_Init(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void ssd1306_Fill(SSD1306_COLOR color);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void ssd1306_UpdateScreen(void);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
void ssd1306_SetCursor(uint8_t x, uint8_t y);

/*******************************************************************************
* @brief  
* @param  None
* @retval None
*******************************************************************************/
static void ssd1306_WriteCommand(uint8_t command);

#endif //__SSD13006_FILE__
