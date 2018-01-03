/**
 * @brief       main.c
 * @details     [todo].
 *
 * 				The rest of the time, the microcontroller is in stop mode ( low power ).
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
	Conf_GPIO 	 ();
	Conf_CLK  	 ();

	mySystemCoreClock	 =	 2097000U;			// SYSCLK = 2.097 MHz
	myTimerClock		 =	 2097000U;			// CK_INT = 2.097 MHz
	Conf_SYSTICK ( mySystemCoreClock/1000 );	// Milli seconds, SysTick will be disabled although
	Conf_TIMERS	 ( myTimerClock );


	TIM5->CR1	|=	 TIM_CR1_CEN;				// Enable TIM5 counter

	HAL_PWR_DisableSleepOnExit ();
	while ( 1 )
	{
		HAL_PWR_EnterSLEEPMode( PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI );
	}
}
