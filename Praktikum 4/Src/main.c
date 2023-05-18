/**
 * Vorlage Praktikum 4: main.c
 **/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stddef.h>
#include <stdint.h>

#include <STM.h>
#include <GPIO_Driver.h>
#include <LCD_Driver.h>

void delay(uint32_t a) {
	for (volatile uint32_t i = 0; i < a; i++);
}

uint8_t state = 0;
TIMER_Handle_t timer5sec;
TIMER_Handle_t timer7sec;
LCD_Handle_t lcd_config;
uint32_t delayValue = 10000;

int main(void)
{
	//Prescaler = Zeit * Taktfrequenz/Period
		//Period = Zeit * Taktfrequenz/Prescaler
		//Taktfrequenz = (Period*Prescaler)/Zeit
		//Zeit = (Period*Prescaler)/Taktfrequenz
		timer5sec.pTIMx = TIM6;
		timer5sec.TIM_Config.Mode = TIM_MODE_IRQ;
		timer5sec.TIM_Config.Period = 65003;
		timer5sec.TIM_Config.Prescaler = 1226;

		TIM_Init(&timer5sec);
		TIM_StartTimer(&timer5sec);

		timer7sec.pTIMx = TIM7;
		timer7sec.TIM_Config.Mode = TIM_MODE_IRQ;
		timer7sec.TIM_Config.Period = 64980;
		timer7sec.TIM_Config.Prescaler = 1717;

		TIM_Init(&timer7sec);

		GPIO_Handle_t btn;
		//Button-Konfiguration
		btn.pGPIOx = GPIOD;
		btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
		btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
		btn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;
		btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

		GPIO_Init(&btn);
		GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10,ENABLE);

	// LCD Handle

	// Einrichten der Felder des LCD Handles
	for (int i = 0; i<8; i++){
		memset(&(lcd_config.pGPIO_Data[i]), 0, sizeof(lcd_config.pGPIO_Data[i]));
		lcd_config.pGPIO_Data[i].pGPIOx = GPIOD;
		lcd_config.pGPIO_Data[i].GPIO_PinConfig.GPIO_PinNumber = i;
	}
	memset(&(lcd_config.RS), 0, sizeof(lcd_config.RS));
	lcd_config.RS.pGPIOx = GPIOD;
	lcd_config.RS.GPIO_PinConfig.GPIO_PinNumber = 12;

	memset(&(lcd_config.Enable), 0, sizeof(lcd_config.Enable));
	lcd_config.Enable.pGPIOx = GPIOD;
	lcd_config.Enable.GPIO_PinConfig.GPIO_PinNumber = 14;

	// InitialisiereDisplay
	lcd_init(&lcd_config);
	delay(2000);
	// Setze Display zurück
	lcd_command(&lcd_config, CMD_LCD_CLEAR);
	delay(2000);
	// Setze Modus 2 Linien mit 8 Bit-Übertragung
	lcd_command(&lcd_config, CMD_LCD_SET_8BIT_2LINE);
	delay(2000);
	// Schaltet das ganze Display und blinkenden Cursor an
	lcd_command(&lcd_config, CMD_LCD_CONTROL_ON);
	delay(2000);
}

void printCorrectText(){
	switch(state){
		case 0: printText(&lcd_config, "Rot:1 Gelb:0 Gruen:0", delayValue); break;
		case 1: printText(&lcd_config, "Rot:1 Gelb:0 Gruen:0", delayValue); break;
		case 2: printText(&lcd_config, "Rot:1 Gelb:1 Gruen:0", delayValue); break;
		case 3: printText(&lcd_config, "Rot:0 Gelb:0 Gruen:1", delayValue); break;
		case 4: printText(&lcd_config, "Rot:0 Gelb:1 Gruen:0", delayValue); break;
	}
}

void TIM6_DAC_IRQHandler(void){
	state = ((state)%4+1);
	TIM_IRQHandling(timer5sec.pTIMx);
	printCorrectText();
}

void TIM7_IRQHandler(void){
	TIM_StopTimer(&timer7sec);
	TIM_Reset(&timer5sec);
	TIM_StartTimer(&timer5sec);
	TIM_IRQHandling(timer7sec.pTIMx);
	state = 1;
	printCorrectText();
}

void EXTI15_10_IRQHandler(void){
	state = 0;
	GPIO_IRQHandling(GPIO_PIN_NO_3);
	TIM_StopTimer(&timer5sec);
	TIM_Reset(&timer7sec);
	TIM_StartTimer(&timer7sec);
	printCorrectText();
}
