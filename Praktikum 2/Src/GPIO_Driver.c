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
		//2. Konfiguration des entsprechenden GPIO-Ports in SYSCFG_EXTICR
		//3  Aktivieren des EXTI Interrupts handling in IMR-Register
	 }
	 
	// ####################################### ENDE IRQ #####################################################################
	
	 //Konfigurieren des Output-Speeds
	 
	 //Konfigurieren des Pull-up/down Settings
	 
	 //Konfigurieren des Output modus
	 
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
	if(Value <= 1){
		uint16_t new_val = Value; //0000 0000 0000 0001 | 0
		new_val = (new_val << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber); // shifte 1 oder 0 an die PinNumber, an der wir ausgeben wollen
		pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber); // lösche die Stelle im Output Register der Pinnumber
		pGPIO_Handle->pGPIOx->OUTPUT_DATA_REG |= new_val; // 16 Bit Register mit new_val verodern, um an der jeweiligen Pin-Stelle 1 oder 0 zu schreiben
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
	if(EnorDi == ENABLE)
	{
		//ToDo: Programmieren der entsprechenden ISERx register
	}
	else
	{
		//ToDo: Programmieren der entsprechenden ICERx register
	}
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// Abfrage und zurücksetzen des EXTI-PR bits
}

// ####################################### ENDE IRQ ###################################################################
