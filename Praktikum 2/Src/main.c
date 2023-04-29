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
	GPIO_Handle_t LED_Lauflicht[4];
	lauflichtInit(LED_Lauflicht);
	for(int i=0; i<2; i++)
		lauflicht(LED_Lauflicht);

	//Ampelsteuerung
	GPIO_Handle_t ampelLED[3];

	ampelInit(&ampelLED);

	for(;;){
		setAmple(ENABLE,DISABLE,DISABLE,ampelLED);

		setAmple(ENABLE,ENABLE,DISABLE,ampelLED);

		setAmple(DISABLE,DISABLE,ENABLE,ampelLED);

		setAmple(DISABLE,ENABLE,DISABLE,ampelLED);
	}
}

void setAmple(int rot, int gelb, int gruen, GPIO_Handle_t* ampelLED){
	GPIO_WriteToOutputPin(&ampelLED[0], rot);
	GPIO_WriteToOutputPin(&ampelLED[1], gelb);
	GPIO_WriteToOutputPin(&ampelLED[2], gruen);
	delay(5);
}
void lauflicht(GPIO_Handle_t * LED){
	// GPIO_WriteToOutputPort((GPIO_RegDef_t *)GPIOD_BASEADDR, 0xFF);
	for (int i = 0; i < 4; i++){
		GPIO_WriteToOutputPin(&LED[i], ENABLE);
		delay(3);
		GPIO_WriteToOutputPin(&LED[i], DISABLE);

	}
}
void ampelInit(GPIO_Handle_t* ampelLED){
	for	(int i = 0; i < 3; i++){
		ampelLED[i].pGPIOx = GPIOD;
		ampelLED[i].GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		ampelLED[i].GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
		ampelLED[i].GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		ampelLED[i].GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
		ampelLED[i].GPIO_PinConfig.GPIO_PinNumber = i;
		GPIO_Init(&ampelLED[i]);
	}
}

void lauflichtInit(GPIO_Handle_t * LED){
	for	(int i = 0; i < 4; i++){
		LED[i].pGPIOx = GPIOD;
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

//Zeit in Sekunden
void delay(int time){
	for(volatile uint32_t i = 0; i<500000*time; i++);
}
