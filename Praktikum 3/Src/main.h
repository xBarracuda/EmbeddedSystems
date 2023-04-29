/*
 * main.h
 *
 *  Created on: 10.04.2023
 *      Author: Julius
 */

#ifndef MAIN_H_
#define MAIN_H_
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "GPIO_Driver.h"
void delay(int time);
void lauflichtInit(GPIO_Handle_t * LED);
void lauflicht(GPIO_Handle_t * LED);
void ampelInit(GPIO_Handle_t* ampelLED);
void setAmple(int rot, int gelb, int gruen, GPIO_Handle_t* ampelLED);

#endif /* MAIN_H_ */
