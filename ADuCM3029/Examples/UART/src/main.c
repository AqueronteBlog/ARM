/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the internal peripheral: WDT on watchdog configuration.
 * 				Both LEDs blink every 1 second.
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/July/2019
 * @version     09/July/2019    The ORIGIN
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
	conf_WDT  ();

	/* Check if the reset was caused by the WDT	 */
	if ( ( pADI_PMG0->RST_STAT & ( 1U << BITP_PMG_RST_STAT_WDRST ) ) == ( 1U << BITP_PMG_RST_STAT_WDRST ) )
	{
		/* Both LEDs OFF	 */
		pADI_GPIO2->CLR	 =	 DS3;
		pADI_GPIO1->CLR	 =	 DS4;

		/* Clear flag	 */
		pADI_PMG0->RST_STAT	|=	 ( 1U << BITP_PMG_RST_STAT_WDRST );
	}


	while ( 1 )
	{
		/* Low power mode: Flexi Mode	 */
		pADI_PMG0->PWRKEY	 =	 0x4859;
		pADI_PMG0->PWRMOD	&=	~( 0b11 << BITP_PMG_PWRMOD_MODE );
		pADI_PMG0->PWRKEY	 =	 0x0000;

		/* Disable key protection for clock oscillator	 */
		pADI_CLKG0_OSC->KEY	 =	 0xCB14U;

		/* Clocks to all peripherals are gated off	 */
		pADI_CLKG0_CLK->CTL5	|=	 ( 1U << BITP_CLKG_CLK_CTL5_PERCLKOFF );

		/* Block registers	 */
		pADI_CLKG0_OSC->KEY	 =	 0x0000U;

		/* Enter in low power Flexi mode	 */
		__WFI();
	}

	/* It should never reach here	 */
	return 0;
}

