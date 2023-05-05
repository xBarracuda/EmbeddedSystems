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

uint8_t state = 0;
TIMER_Handle_t timer5sec;
TIMER_Handle_t timer7sec;

int main(void)
{
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
	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
	btn.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;

	GPIO_Init(&btn);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI3,ENABLE);

	//Lauflicht
	/*GPIO_Handle_t LED_Lauflicht[4];
	lauflichtInit(LED_Lauflicht);
	for(int i=0; i<2; i++)
		lauflicht(LED_Lauflicht);
*/
	//Ampelsteuerung
	GPIO_Handle_t ampelLED[3];

	ampelInit(ampelLED);

	for(;;){
		switch(state){
			case 0: setAmple(ENABLE,DISABLE,DISABLE,ampelLED); break;

			case 1: setAmple(ENABLE,DISABLE,DISABLE,ampelLED); break;

			case 2: setAmple(ENABLE,ENABLE,DISABLE,ampelLED); break;

			case 3: setAmple(DISABLE,DISABLE,ENABLE,ampelLED); break;

			case 4: setAmple(DISABLE,ENABLE,DISABLE,ampelLED); break;
		}
	}


}

void setAmple(int rot, int gelb, int gruen, GPIO_Handle_t* ampelLED){
	GPIO_WriteToOutputPin(&ampelLED[0], rot);
	GPIO_WriteToOutputPin(&ampelLED[1], gelb);
	GPIO_WriteToOutputPin(&ampelLED[2], gruen);
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

void TIM6_DAC_IRQHandler(void){
	state = ((state)%4+1);
	TIM_IRQHandling(timer5sec.pTIMx);
}

void TIM7_IRQHandler(void){
	TIM_StopTimer(&timer7sec);
	TIM_Reset(&timer5sec);
	TIM_StartTimer(&timer5sec);
	TIM_IRQHandling(timer7sec.pTIMx);
	state = 1;
}

void EXTI3_IRQHandler(void){
	state = 0;
	GPIO_IRQHandling(GPIO_PIN_NO_3);
	TIM_StopTimer(&timer5sec);
	TIM_Reset(&timer7sec);
	TIM_StartTimer(&timer7sec);
}
