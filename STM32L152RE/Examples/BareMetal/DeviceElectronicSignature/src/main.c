/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the internal peripheral RTC using the
 * 				periodic wake-up timer. The LED will change its state every 1 second.
 *
 * 				The microcontroller will remain in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with Atollic TrueSTUDIO for STM32
 *              ( v9.0.1 ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */


#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



/**@brief Constants.
 */
#define F_SIZE	( *(uint16_t *) ( 0x1FF800CC ) )			/*!< Flash size register ( Cat.5 )						*/

#define U_ID1	( *(uint32_t *) ( 0x1FF800D0 ) )
#define U_ID2	( *(uint32_t *) ( 0x1FF800D0 + 0x04 ) )		/*!< Unique device ID registers ( 96 bits )( Cat.5 )	*/
#define U_ID3	( *(uint32_t *) ( 0x1FF800D0 + 0x14 ) )



/**@brief Variables.
 */
volatile uint32_t myLEDstate	 =	 0;						/*!< LED state                         					*/




/**@brief Function for application main entry.
 */
int main ( void )
{
	Conf_GPIO 	 ();
	Conf_CLK  	 ();
	Conf_RTC     ();



	while ( 1 )
	{
		HAL_PWR_EnterSTOPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
	}
}
