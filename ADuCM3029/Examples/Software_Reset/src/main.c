/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the internal peripheral: UART.
 * 				If '1' is received, LED1 is turned on, if '2' is received, the LED2 is turned on.
 * 				A message will be transmitted back, any other value will turn both LEDs off.
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        23/July/2019
 * @version     23/July/2019    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"


/**@brief Constants.
 */



/**@brief Variables.
 */



/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */
	SystemInit ();

	conf_CLK  ();
	conf_GPIO ();

	/* Generate a little delay	 */
	for ( uint32_t i = 0UL; i < 0x23232; i++ );

	/* Check if the reset was provoked by the software reset	 */
	if ( ( pADI_PMG0->RST_STAT & ( 1U << BITP_PMG_RST_STAT_SWRST ) ) == ( 1U << BITP_PMG_RST_STAT_SWRST ) )
	{
		/* Turn both LEDs on	 */
		pADI_GPIO1->SET	|=	 DS4;
		pADI_GPIO2->SET	|=	 DS3;

		/* Clear flag	 */
		pADI_PMG0->RST_STAT	|=	 ( 1U << BITP_PMG_RST_STAT_SWRST );
	}

	/* Trigger a new software reset	 */
	pADI_NVIC0->INTAIRC	 =	 ( 0x05FA0004 << BITP_NVIC_INTAIRC_VALUE );


	while ( 1 )
	{
	}

	/* It should never reach here	 */
	return 0;
}

