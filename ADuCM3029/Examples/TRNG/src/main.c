/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: TRNG. Every 1 second a new random number
 * 				is generated and transmitted over the UART ( Baud: 115200 ).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/September/2019
 * @version     03/September/2019    The ORIGIN
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
#define TX_BUFF_SIZE		64  	        /*!<   UART buffer size                                      */


/**@brief Variables.
 */
volatile uint32_t  myState	 =	 0UL;		/*!<   State that indicates when to perform the next action   */
volatile uint8_t  *myPtr;                   /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	uint32_t myRNG	 =	 0UL;
	uint8_t  myMessage[ TX_BUFF_SIZE ];

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */
	SystemInit ();

	conf_CLK    ();
	conf_GPIO   ();
	conf_TRNG   ();
	conf_UART   ();
	conf_Timer0 ();


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

		if ( myState != 0UL )
		{
			/* Turn both LEDs on	 */
			pADI_GPIO1->SET	|=	 DS4;
			pADI_GPIO2->SET	|=	 DS3;

			/* Clear all the flags	 */
			myRNG			 =	 0UL;
			pADI_RNG0->STAT	|=	 ( ( 1U << BITP_RNG_STAT_STUCK ) | ( 1U << BITP_RNG_STAT_RNRDY ) );

			/* Enable and trigger the RNG for a new random number	 */
			pADI_RNG0->CTL	|=	 ( 1U << BITP_RNG_CTL_EN );

			/* Wait until there is a new random number	 */
			while ( ( pADI_RNG0->STAT & ( 1U << BITP_RNG_STAT_RNRDY ) ) != ( 1U << BITP_RNG_STAT_RNRDY ) );

			/* Get the new random data ( 8-bit )	 */
			myRNG	 =	 ( pADI_RNG0->DATA & 0xFF );

			/* Disable the RNG	 */
			pADI_RNG0->CTL	&=	~( 1U << BITP_RNG_CTL_EN );

			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "RNG: %ld\r\n", myRNG );

			/* Check that is safe to send data	 */
			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );

			/* Transmit data back	 */
			myPtr            =   &myMessage[0];
			pADI_UART0->TX	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables and turn both LEDs off	 */
			myState	 		 =	 0UL;
			pADI_GPIO1->CLR	|=	 DS4;
			pADI_GPIO2->CLR	|=	 DS3;
		}
	}

	/* It should never reach here	 */
	return 0;
}

