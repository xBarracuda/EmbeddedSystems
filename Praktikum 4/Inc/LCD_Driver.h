/**
 * Vorlage Praktikum 4: LCD_Driver.h
 **/

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "STM.h"
#include "GPIO_Driver.h"

// ToDo: Vervollständigen Sie die Bitfolgen für die einzelnen Kommandos
#define CMD_LCD_CLEAR					0b00000001
#define CMD_LCD_CONTROL_ON				0b00001111
#define CMD_LCD_SET_8BIT_2LINE			0b00111000
#define CMD_LCD_RETURN_HOME				0b00000010
#define CMD_LCD_SET_SECOND_LINE			0b11000000
#define CMD_LCD_ENTRY_MODE_INC			0b00000110
#define CMD_LCD_ENTRY_MODE_SHIFT		0b00000111
#define CMD_LCD_SHIFT_CURSOR_LEFT		0b00010000
#define CMD_LCD_SHIFT_CURSOR_RIGHT		0b00010100



/*
 * Handle struct für LCD
 */
typedef struct
{
	GPIO_Handle_t pGPIO_Data[8];
	GPIO_Handle_t RS;
	//GPIO_Handle_t RW;
	GPIO_Handle_t Enable;
}LCD_Handle_t;


// Hildfunktionen zum Setzen der Steuer-Bits
void setRS(LCD_Handle_t* lcd_config);
void resetRS(LCD_Handle_t* lcd_config);

/* Braucht für die aktuelle Version nicht implementiert zu werden
void setRW(LCD_Handle_t* lcd_config);
void resetRW(LCD_Handle_t* lcd_config);
*/

void setEnable(LCD_Handle_t* lcd_config);
void resetEnable(LCD_Handle_t* lcd_config);

void toggleEnable(LCD_Handle_t* lcd_config);

// Sendet das Kommando in cmd angegebene Kommando an das Display (instruction Mode)
// und führt es aus.
void lcd_command(LCD_Handle_t* lcd_config, uint8_t cmd);

// Setzt die 8 Datenbits auf die in Value angegebenen Werte
void setDataBits(uint8_t value, LCD_Handle_t* lcd_config);

// Inistialiserung des Displays
void lcd_init(LCD_Handle_t* lcd_config);

// Schreibt einen Buchstaben auf da Display
void printLetter(LCD_Handle_t* lcd_config, uint8_t letter);

// Gibt einen Text auf dem Display aus
void printText(LCD_Handle_t* lcd_config, char *Text, uint32_t delayvalue);

#endif /* LCD_DRIVER_H_ */
