/**
 * @brief       main.c
 * @details     This example shows how to work with the next internal peripheral: UART5. Every
 * 				time a '1' is received ( UART5_RX ), it sends the state of the port A ( GPIOA ) through
 * 				the UART ( UART5_TX )
 *
 * 				The rest of the time, the microcontroller is in sleep mode ( low power ).
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version     3/January/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with System Workbench for STM32
 *              ( v1.15.0.201708311556 ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */


#include "stm32l1xx.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



int main ( void )
{
	mySystemCoreClock	 =	 16000000U;			// SYSCLK = 16 MHz
	myUARTClock	 		 =	 16000000U;			// f_CK = 16 MHz

	Conf_GPIO 	 ();
	Conf_CLK  	 ();
	Conf_SYSTICK ( mySystemCoreClock/1000 );	// Milli seconds, SysTick will be disabled although
	Conf_UART 	 ( myUARTClock, 115200 );		// 115200 Baud Rate


	HAL_PWR_DisableSleepOnExit ();
	while ( 1 )
	{
		HAL_PWR_EnterSLEEPMode( PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI );
	}
}
