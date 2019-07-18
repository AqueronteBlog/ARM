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
 * @date        18/July/2019
 * @version     18/July/2019    The ORIGIN
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
#define TX_BUFF_SIZE  64                    /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint8_t  myState	 =	 0U;		/*!<   State that indicates when to perform the next action   */
volatile uint8_t  *myPtr;                   /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	uint8_t  myMessage[ TX_BUFF_SIZE ];

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */
	SystemInit ();

	/* Initialized the message	 */
	myMessage[ 0 ]   =  'L';
	myMessage[ 1 ]   =  'E';
	myMessage[ 2 ]   =  'D';
	myMessage[ 3 ]   =  ' ';
	myMessage[ 4 ]   =  ' ';
	myMessage[ 11 ]  =  '\n';


	conf_CLK  ();
	conf_GPIO ();
	conf_UART ();


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

		if ( myState != 0U )
		{
			/* Initialized the message	 */
			myMessage[ 5 ]   =  'T';
			myMessage[ 6 ]   =  'O';
			myMessage[ 7 ]   =  'G';
			myMessage[ 8 ]   =  'G';
			myMessage[ 9 ]   =  'L';
			myMessage[ 10 ]  =  'E';

			switch ( myState )
			{
				case '1':
					/* Toggle LED1	 */
					pADI_GPIO1->TGL	|=	 DS4;
					myMessage [ 3 ]	 =	 '1';
					break;

				case '2':
					/* Toggle LED2	 */
					pADI_GPIO2->TGL	|=	 DS3;
					myMessage [ 3 ]	 =   '2';
					break;

				default:
					/* Both LEDs off	 */
					pADI_GPIO1->CLR	|=	 DS4;
					pADI_GPIO2->CLR	|=	 DS3;

					/* Initialized the message	 */
					myMessage[ 3 ]   =  ' ';
					myMessage[ 5 ]   =  'E';
					myMessage[ 6 ]   =  'R';
					myMessage[ 7 ]   =  'R';
					myMessage[ 8 ]   =  'O';
					myMessage[ 9 ]   =  'R';
					myMessage[ 10 ]  =  '!';
					break;
			}

			/* Check that is safe to send data	 */
			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );

			/* Transmit data back	 */
			myPtr            =   &myMessage[0];
			pADI_UART0->TX	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables	 */
			myState	 =	 0U;
		}
	}

	/* It should never reach here	 */
	return 0;
}

