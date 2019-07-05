/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: GPIO input ( GPIO A interrupt ).
 * 				Both LEDs blink every time that there is a transition high-to-low on P2_02 ( GPIO34 ).
 *
 * 				The rest of the time, the microcontroller is in low-power mode: Flexi mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/July/2019
 * @version     04/July/2019    The ORIGIN
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
volatile uint32_t myState	 =	 0UL;		/*!<   State that indicates when to perform the next action     */




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
	SystemInit 	();

	conf_CLK  	();
	conf_GPIO 	();

	/* Enable interrupts	 */
	__enable_irq ();


	while ( 1 )
	{
		/* Low power mode: Flexi Mode	 */
		pADI_PMG0->PWRKEY	 =	 0x4859;
		pADI_PMG0->PWRMOD	&=	~( 0b11 << BITP_PMG_PWRMOD_MODE );
		pADI_PMG0->PWRKEY	 =	 0x0000;
		__WFI();

		/* Check for new action	 */
		if ( myState == 1UL )
		{
			/* Blink LED	 */
			pADI_GPIO2->TGL	|=	 DS3;
			pADI_GPIO1->TGL	|=	 DS4;

			/* Reset variables	 */
			myState = 0UL;
		}
	}

	/* It should never reach here	 */
	return 0;
}

