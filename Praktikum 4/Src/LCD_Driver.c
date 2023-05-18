/**
 * Vorlage Praktikum 4: LCD_Driver.c
 **/

#include "LCD_Driver.h"

void delay_LCD(uint32_t a) {
	for (volatile uint32_t i = 0; i < a; i++);
}

//Todo: Implementieren Sie die leeren Funktionen!
// Nutzen Die dazu Ihren GPIO-Treiber

void setRS(LCD_Handle_t* lcd_config){
	GPIO_WriteToOutputPin(&lcd_config->RS,1);
}

void resetRS(LCD_Handle_t* lcd_config){
	GPIO_WriteToOutputPin(&lcd_config->RS,0);
}


void setEnable(LCD_Handle_t* lcd_config){
	GPIO_WriteToOutputPin(&lcd_config->Enable,1);
}

void resetEnable(LCD_Handle_t* lcd_config){
	GPIO_WriteToOutputPin(&lcd_config->Enable,0);
}

void toggleEnable(LCD_Handle_t* lcd_config)
{
	GPIO_ToggleOutputPin(&lcd_config->Enable);
}

// Sendet das Kommando in cmd angegebene Kommando an das Display (instruction Mode)
// und führt es aus.
void lcd_command(LCD_Handle_t* lcd_config, uint8_t cmd)
{
	setEnable(lcd_config);
	resetRS(lcd_config);
	setDataBits(cmd,lcd_config);
	delay_LCD(2000);
	resetEnable(lcd_config);
}

// Setzt die 8 Datenbits auf die in Value angegebenen Werte
void setDataBits(uint8_t value, LCD_Handle_t* lcd_config){
	//for(int i=0; i<sizeof(lcd_config->pGPIO_Data); i++){
	for(int i=0; i<8; i++){
		GPIO_WriteToOutputPin(&lcd_config->pGPIO_Data[i],((value>>i)&(0x01)));
	}
}

// Inistialiserung des Displays
void lcd_init(LCD_Handle_t* lcd_config){
	GPIO_Handle_t RS_Handle;
	GPIO_PinConfig_t RS_Config;
	RS_Config.GPIO_PinMode = GPIO_MODE_OUT;
	RS_Config.GPIO_PinNumber = 12;
	RS_Config.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	RS_Config.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	RS_Config.GPIO_PinSpeed = GPIO_SPEED_LOW;
	RS_Handle.GPIO_PinConfig = RS_Config;
	RS_Handle.pGPIOx = GPIOD;
	GPIO_Init(&RS_Handle);
	lcd_config->RS = RS_Handle;

	GPIO_Handle_t EN_Handle;
	GPIO_PinConfig_t EN_Config;
	EN_Config.GPIO_PinMode = GPIO_MODE_OUT;
	EN_Config.GPIO_PinNumber = 14;
	EN_Config.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	EN_Config.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	EN_Config.GPIO_PinSpeed = GPIO_SPEED_LOW;
	EN_Handle.GPIO_PinConfig = EN_Config;
	EN_Handle.pGPIOx = GPIOD;
	GPIO_Init(&EN_Handle);
	lcd_config->Enable = EN_Handle;

	GPIO_Handle_t D_Handle[8];
	GPIO_PinConfig_t D_Config[8];

	for(int i=0; i<8; i++){
		D_Config[i].GPIO_PinMode = GPIO_MODE_OUT;
		D_Config[i].GPIO_PinNumber = i;
		D_Config[i].GPIO_PinOPType = GPIO_OP_TYPE_PP;
		D_Config[i].GPIO_PinPuPdControl = GPIO_NO_PUPD;
		D_Config[i].GPIO_PinSpeed = GPIO_SPEED_LOW;
		D_Handle[i].GPIO_PinConfig = D_Config[i];
		D_Handle[i].pGPIOx = GPIOD;
		GPIO_Init(&D_Handle[i]);
		lcd_config->pGPIO_Data[i] = D_Handle[i];
	}
}


void printLetter(LCD_Handle_t* lcd_config, uint8_t letter)
{
	setEnable(lcd_config);
	setRS(lcd_config);
	setDataBits(letter,lcd_config);
	delay_LCD(2000);
	resetEnable(lcd_config);
}

// Diese Funktion brauchen Sie nicht zu modifizieren. Die dient dem Test in der main.c
void printText(LCD_Handle_t* lcd_config, char *Text, uint32_t delayvalue)
{
	lcd_command(lcd_config, CMD_LCD_CLEAR);
	delay_LCD(delayvalue);
	// Print a text to the display
	char *tmp = Text;
	uint8_t counter = 0;

	while(*tmp != '\0')
	{
		printLetter(lcd_config, *tmp);
		tmp++;
		counter++;
		delay_LCD(delayvalue);
		if(counter > 16)
		{
			lcd_command(lcd_config, CMD_LCD_SET_SECOND_LINE);
			delay_LCD(delayvalue);
			counter = 0;
		}
	}
}
