/**
 * @brief       main.c
 * @details     [todo].
 *
 * 				The rest of the time, the microcontroller is in stop mode ( low power ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/March/2018
 * @version     1/March/2018   The ORIGIN
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

	mySystemCoreClock	 =	 2097000U;			// SYSCLK = 2.907 MHz
	Conf_SYSTICK ( mySystemCoreClock/1000 );	// Milli seconds, SysTick will be disabled although


	HAL_PWR_DisableSleepOnExit ();
	while ( 1 )
	{
		HAL_PWR_EnterSTOPMode( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
	}
}
