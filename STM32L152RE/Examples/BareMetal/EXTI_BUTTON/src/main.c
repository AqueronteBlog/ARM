/**
 * @brief       main.c
 * @details     [todo].
 *
 * 				The SysTick is configured to generate an interrupt every ~1ms.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
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
	NUCLEOL152_pin_name_t	myLED1 = LED_1;

	Conf_GPIO 	 ();
	Conf_CLK  	 ();

	mySystemCoreClock	 =	 2097000U;			// SYSCLK = 2.907 MHz
	Conf_SYSTICK ( mySystemCoreClock/1000 );	// Milli seconds, SysTick will be disabled although


	while ( 1 )
	{
		// Change the state of the LED every ~0.5s
		if ( myDelay > 500 )
		{
		// Reset Delay
			myDelay	 =	 0;

		// Blink LED
			if ( ( GPIOA->ODR & GPIO_ODR_ODR_5 ) == GPIO_ODR_ODR_5 )
				GPIOA->BRR	=	( 1 << myLED1 );							// Turn it OFF
			else
				GPIOA->BSRR	=	( 1 << myLED1 );							// Turn it ON
		}
	}
}
