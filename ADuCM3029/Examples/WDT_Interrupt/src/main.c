/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the internal peripheral: GPIO. Both LEDs blink every certain period of time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/June/2019
 * @version     13/June/2019    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include <sys/ADuCM302x.h>
#include <sys/ADuCM302x_device.h>
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
	conf_CLK  ();
	conf_GPIO ();
	conf_WDT  ();

	/* Enable interrupts	 */
	__enable_irq ();


	while ( 1 )
	{
		if ( myState == 1UL )
		{
			/* Disable interrupts	 */
			__disable_irq ();

			/* Blink LEDs	 */
			pADI_GPIO2->TGL	|=	 DS3;
			pADI_GPIO1->TGL	|=	 DS4;


			/* Reset variables	 */
			myState	 =	 0UL;

			/* Enable interrupts	 */
			__enable_irq ();
		}
	}

	/* It should never reach here	 */
	return 0;
}

