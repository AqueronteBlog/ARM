/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: Independent
 * 				Watch Dog ( IWDG ). Every one second, the IWDG will generate a reset.
 *
 * 				At the beginning of the firmware, the LED1 is OFF for a short period of time,
 * 				then it is turned ON.
 *
 * 				The rest of the time, the microcontroller is in standby mode ( low power ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     9/March/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with Atollic TrueSTUDIO for STM32
 *              ( v9.0.0 ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */


#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



int main ( void )
{
	Conf_GPIO 	 ();
	Conf_CLK  	 ();


	GPIOA->BRR		 =	( 1 << LED_1 );			// LED1 OFF

	for ( uint32_t i = 0; i < 23232; i++ );		// Small delay to see the changes when the IWDG resets the uC

	GPIOA->BSRR		=	( 1 << LED_1 );			// LED1 ON


	while ( 1 )
	{
		HAL_PWR_EnterSTANDBYMode ();
	}
}
