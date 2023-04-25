/*
 * GPIO_Driver.c
 * Vorlage fürs Praktikum 
 */

#include "GPIO_Driver.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}else if (pGPIOx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}else if (pGPIOx == GPIOC)
				{
					GPIOC_PCLK_DI();
				}else if (pGPIOx == GPIOD)
				{
					GPIOD_PCLK_DI();
				}else if (pGPIOx == GPIOE)
				{
					GPIOE_PCLK_DI();
				}else if (pGPIOx == GPIOF)
				{
					GPIOF_PCLK_DI();
				}else if (pGPIOx == GPIOG)
				{
					GPIOG_PCLK_DI();
				}else if (pGPIOx == GPIOH)
				{
					GPIOH_PCLK_DI();
				}else if (pGPIOx == GPIOI)
				{
					GPIOI_PCLK_DI();
				}
	}
}

// Implementieren Sie die weiteren Schritte. Denken Sie daran die Einträge eines Registers zurückzusetzen, bevor Sie einzelne Bits setzen!
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	 //Anschalten der Clock
	 GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	 //Konfigurieren des PIN in INPUT oder OUTPUT-Modus
	 if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	 {
		pGPIOHandle->pGPIOx->MODE_REG &= ~(0b11 <<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber*2); // löschen der Bits im Mode-Register
		pGPIOHandle->pGPIOx->MODE_REG |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber*2); // setzen der Bits im ode Register an der jeweiligen Stelle
	 }
	 
	 // ####################################### Praktikum 3: IRQ ############################################################
	 
	 else
	 { 
		 // IRQ-Modus (Muss erst im dritten Praktikum bearbeitet werden)
		 // 1. Konfiguration für Trigger auf fallenende, steigende oder beide Flanken
		 // 2. Konfiguration des entsprechenden GPIO-Ports in SYSCFG_EXTICR
		 // 3.  Aktivieren des EXTI Interrupts handling in IMR-Register

		 EXTI_RegDef_t* exti = EXTI;
		 exti->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		 exti->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		 switch (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode){
		 case (GPIO_MODE_IT_FT):
				 exti->RTSR |= (0 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		 	 	 exti->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
				 break;
		 case (GPIO_MODE_IT_RT):
		 	 	 exti->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		 		 exti->FTSR |= (0 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		 		 break;
		 case (GPIO_MODE_IT_RFT):
				 exti->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		 		 exti->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		 		 break;
		 }

		 SYSCFG_RegDef_t* syscfg = SYSCFG;
		 uint8_t bitPosition = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4*4; //Errechnet die Startposition des Blocks im Register. Bei Pin 5 ergibt sich Bit 4, da wir den zweiten Block im Register[4-7] setzen müssen
		 syscfg->EXTICR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4] &= ~(0b1111 << bitPosition); //Resetet den Block
		 syscfg->EXTICR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4] |= (GPIO_BASEADDR_TO_CODE(pGPIOHandle)<< bitPosition); //Setzt den Block

		 exti->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	 }
	 
	// ####################################### ENDE IRQ #####################################################################
	
	 //Konfigurieren des Output-Speeds
	 pGPIOHandle->pGPIOx->OUTPUT_SPEED &= ~(0b11 <<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber*2); // löschen der Bits im Speed-Register
	 pGPIOHandle->pGPIOx->OUTPUT_SPEED |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber*2); // setzen der Bits im ode Register an der jeweiligen Stelle

	 //Konfigurieren des Pull-up/down Settings
	 pGPIOHandle->pGPIOx->PULL_UP_DOWN &= ~(0b11 <<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber*2); // löschen der Bits im PullUp/Down-Register
	 pGPIOHandle->pGPIOx->PULL_UP_DOWN |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber*2); // setzen der Bits im ode Register an der jeweiligen Stelle

	 //Konfigurieren des Output modus
	 pGPIOHandle->pGPIOx->OUTPUT_TYPE &= ~(1 <<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // löschen der Bits im Output Type-Register
	 pGPIOHandle->pGPIOx->OUTPUT_TYPE |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // setzen der Bits im ode Register an der jeweiligen Stelle

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

uint8_t GPIO_ReadFromInputPin(GPIO_Handle_t *pGPIO_Handle)
{
	uint16_t Input_reg = GPIO_ReadFromInputPort(pGPIO_Handle->pGPIOx); // Input_Register einlesen, pGPIOx -> Basisadresse des einzulesenden Registers
	uint8_t pin_shift = (Input_reg >> pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber); // shiften des Input_reg der jeweiligen Pin_number
	return pin_shift & 1; // mit 00000001 verunden, um im ersten Bit den Input 1 oder 0 auszulesen
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	return pGPIOx->INPUT_DATA_REG; // Registerinhalt von der zugehörigen GPIO auslesen
}

void GPIO_WriteToOutputPin(GPIO_Handle_t *pGPIO_Handle, uint8_t Value)
{
	uint16_t new_val = Value; //0000 0000 0000 0001 | 0
	new_val = (new_val << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber); // shifte 1 oder 0 an die PinNumber, an der wir ausgeben wollen

	if(Value == 1){
		pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG |= new_val; // 16 Bit Register mit new_val verodern, um an der jeweiligen Pin-Stelle 1 oder 0 zu schreiben
	}else{
		pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber); // lösche die Stelle im Output Register der Pinnumber
	}
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->OUTPUT_DATA_REG = Value; // setzt Registerinhalt des zugehörigen GPIO-Registers
}


void GPIO_ToggleOutputPin(GPIO_Handle_t *pGPIO_Handle)
{
	pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG ^= (1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
}

// ####################################### Praktikum 3: IRQ ############################################################

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	// Hinweis: Bedenken Sie welche ISER und ICER Register des Prozessors in dem verwendeten Mikrocontroller benutzt werden können.
	// Nicht alle Interrupts sind im Mikrocontroller aktiv. Überprüfen sie dazu das Handbuch (Reference Manual) des Mikrocontrollers.
	uint8_t bitPosition = IRQNumber%4*4;
	uint32_t* reg;
	if(EnorDi == ENABLE)
	{
		//ToDo: Programmieren der entsprechenden ISERx register
		switch(IRQNumber/4){
			case (0): reg = (uint32_t*)NVIC_ISER0;break;
			case (1): reg = (uint32_t*)NVIC_ISER1;break;
			case (2): reg = (uint32_t*)NVIC_ISER2;break;
			case (3): reg = (uint32_t*)NVIC_ISER3;break;
		}
		reg &= ~(0b1111 << bitPosition);
		reg |= (0b0001 << bitPosition);
	}
	else
	{
		//ToDo: Programmieren der entsprechenden ICERx register
		switch(IRQNumber/4){
			case (0): reg = (uint32_t*)NVIC_ICER0;break;
			case (1): reg = (uint32_t*)NVIC_ICER1;break;
			case (2): reg = (uint32_t*)NVIC_ICER2;break;
			case (3): reg = (uint32_t*)NVIC_ICER3;break;
		}
		reg &= ~(0b1111 << bitPosition);
		reg |= (0b0001 << bitPosition);
	}
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// Abfrage und zurücksetzen des EXTI-PR bits
}

// ####################################### ENDE IRQ ###################################################################
