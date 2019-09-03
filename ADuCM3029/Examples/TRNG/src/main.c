/**
 * @brief       main.c
 * @details     [todo] This example shows how to work with the internal peripheral: ADC and the built-in Temperature sensor with
 * 				external reference ( VREF MUST be connected to 3.3V ).
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
#define	RG					1.18			/*!<   Temperature: Constant parameter                       */
#define	R_VIRTUAL_REFERENCE	1.223331		/*!<   Temperature: Constant parameter                       */
#define	IDEAL_SENSITIVITY	0.001392736		/*!<   Temperature: Constant parameter                       */


/**@brief Variables.
 */
volatile uint32_t  myState	 =	 0UL;		/*!<   State that indicates when to perform the next action   */
volatile uint8_t  *myPtr;                   /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	uint16_t myTemperatureCode1	=	0UL;
	uint16_t myTemperatureCode2	=	0UL;
	float	 myTemperature	 	=	0UL;
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
	conf_ADC    ();
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

			/* Get temperature value	 */
			pADI_ADC0->CNV_CFG	|=	 ( ( 1U << BITP_ADC_CNV_CFG_TMP ) | ( 1U << BITP_ADC_CNV_CFG_SINGLE )  );		// Enable TMP and start new conversion
			while ( ( pADI_ADC0->STAT & ( 1U << BITP_ADC_STAT_TMPDONE ) ) != ( 1U <<BITP_ADC_STAT_TMPDONE ) );
			pADI_ADC0->STAT	|=	 ( ( 1U << BITP_ADC_STAT_TMPDONE ) | ( 1U << BITP_ADC_STAT_CALDONE ) );				// Clear flag

			myTemperatureCode1	 =	 pADI_ADC0->TMP_OUT;


			pADI_ADC0->CNV_CFG	&=	~( 1U << BITP_ADC_CNV_CFG_TMP );												// Disable TMP
			pADI_ADC0->CNV_CFG	|=	 ( ( 1U << BITP_ADC_CNV_CFG_TMP2 ) | ( 1U << BITP_ADC_CNV_CFG_SINGLE ) );		// Enable TMP2 and start new conversion
			while ( ( pADI_ADC0->STAT & ( 1U << BITP_ADC_STAT_TMP2DONE ) ) != ( 1U <<BITP_ADC_STAT_TMP2DONE ) );
			pADI_ADC0->STAT	|=	 ( ( 1U << BITP_ADC_STAT_TMP2DONE ) | ( 1U << BITP_ADC_STAT_CALDONE ) );			// Clear flag

			myTemperatureCode2	|=	 pADI_ADC0->TMP2_OUT;

			pADI_ADC0->CNV_CFG	&=	~( 1U << BITP_ADC_CNV_CFG_TMP2 );												// Disable TMP2

			/* Calculate the temperature value in Celsius degrees	 */
			myTemperature	 =	 ( ( myTemperatureCode1 / ( myTemperatureCode2 + RG * myTemperatureCode1 ) ) * ( R_VIRTUAL_REFERENCE / IDEAL_SENSITIVITY ) ) - 273.15;



			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "T: %0.2f C\r\n", myTemperature );


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

