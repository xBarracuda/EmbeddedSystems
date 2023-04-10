/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "GPIO_Driver.h"
#include "STM.h"
#include "main.h"

int main(void)
{
	//Lauflicht
	/*GPIO_Handle_t LED_Lauflicht[4];
	lauflichtInit(LED_Lauflicht);
	for(int i=0; i<2; i++)
		lauflicht(LED_Lauflicht);*/


	GPIO_Handle_t LED_Rot, LED_Gelb, LED_Gruen;

	ampelInit(&LED_Rot, &LED_Gelb, &LED_Gruen);

	for(;;){
		GPIO_WriteToOutputPin(&LED_Rot, ENABLE);
		GPIO_WriteToOutputPin(&LED_Gelb, DISABLE);
		GPIO_WriteToOutputPin(&LED_Gruen, DISABLE);

		delay(5);

		GPIO_WriteToOutputPin(&LED_Rot, ENABLE);
		GPIO_WriteToOutputPin(&LED_Gelb, ENABLE);
		GPIO_WriteToOutputPin(&LED_Gruen, DISABLE);

		delay(5);

		GPIO_WriteToOutputPin(&LED_Rot, DISABLE);
		GPIO_WriteToOutputPin(&LED_Gelb, DISABLE);
		GPIO_WriteToOutputPin(&LED_Gruen, ENABLE);

		delay(5);

		GPIO_WriteToOutputPin(&LED_Rot, DISABLE);
		GPIO_WriteToOutputPin(&LED_Gelb, ENABLE);
		GPIO_WriteToOutputPin(&LED_Gruen, DISABLE);

		delay(5);
	}
}

void ampelInit(GPIO_Handle_t* LED_Rot,GPIO_Handle_t* LED_Gelb,GPIO_Handle_t* LED_Gruen){

	//Teil der Config, die immer gleich ist
	GPIO_PinConfig_t baseConfig;
	baseConfig.GPIO_PinMode = GPIO_MODE_OUT;
	baseConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	baseConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	baseConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//Config aller leds
	LED_Rot->pGPIOx = (GPIO_RegDef_t *)GPIOD_BASEADDR;
	LED_Rot->GPIO_PinConfig = baseConfig;
	LED_Rot->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;

	LED_Gelb->pGPIOx = (GPIO_RegDef_t *)GPIOD_BASEADDR;
	LED_Gelb->GPIO_PinConfig = baseConfig;
	LED_Gelb->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;

	LED_Gruen->pGPIOx = (GPIO_RegDef_t *)GPIOD_BASEADDR;
	LED_Gruen->GPIO_PinConfig = baseConfig;
	LED_Gruen->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;

	//Pin 0-2 als output initialisiert
	GPIO_Init(LED_Rot);
	GPIO_Init(LED_Gelb);
	GPIO_Init(LED_Gruen);
}

void lauflichtInit(GPIO_Handle_t * LED){
	for	(int i = 0; i < 4; i++){
		LED[i].pGPIOx = (GPIO_RegDef_t *)GPIOD_BASEADDR;
		LED[i].GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15 - i;
		LED[i].GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		LED[i].GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
		LED[i].GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		LED[i].GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
		GPIO_Init(&LED[i]);
	}

	for(int i = 0; i < 4; i++){
		GPIO_WriteToOutputPin(&LED[i], DISABLE);
	}
}

void lauflicht(GPIO_Handle_t * LED){
	// GPIO_WriteToOutputPort((GPIO_RegDef_t *)GPIOD_BASEADDR, 0xFF);
	for (int i = 0; i < 4; i++){
		GPIO_WriteToOutputPin(&LED[i], ENABLE);
		delay(3);
		GPIO_WriteToOutputPin(&LED[i], DISABLE);

	}
}

//Zeit in Sekunden
void delay(int time){
	for(volatile uint32_t i = 0; i<500000*time; i++);
}
