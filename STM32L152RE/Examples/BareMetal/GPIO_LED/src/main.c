/**
 * @brief       main.c
 * @details     This example shows how to configure the GPIO to turn on an LED as well
 * 				as the MCO ( output SYSCLK frequency ).
 *
 * 				The SysTick is configured to generate an interrupt every ~1ms.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with System Workbench for STM32
 *              ( v1.15.0.201708311556 ).
 * @warning     Although HAL driver was generated, it was not used for this example.
 */


#include "stm32l1xx.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



int main ( void )
{
	Conf_GPIO 	 ();
	Conf_CLK  	 ();

	mySystemCoreClock	 =	 2097000U;			// SYSCLK = 2.907 MHz
	Conf_SYSTICK ( mySystemCoreClock/1000 );	// Milli seconds


	while ( 1 )
	{
		// Change the state of the LED every ~0.5s
		if ( myDelay > 500 )
		{
		// Reset Delay
			myDelay	 =	 0;

		// Blink LED
			if ( ( GPIOA->ODR & GPIO_ODR_ODR_5 ) == GPIO_ODR_ODR_5 )
				GPIOA->BRR	=	GPIO_BRR_BR_5;							// Turn it OFF
			else
				GPIOA->BSRR	=	GPIO_BSRR_BS_5;							// Turn it ON
		}
	}
}
