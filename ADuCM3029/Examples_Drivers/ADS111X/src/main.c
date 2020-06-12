/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: ADS111X.
 * 				A new sample is read every 1 second and transmitted through the UART (115200 baud)
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "ADS111X.h"


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t  myState	 =	 0UL;   /*!<   State that indicates when to perform the next action   */
volatile uint8_t   *myPtr;             	/*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	uint8_t  			myMessage[ TX_BUFF_SIZE ];
	I2C_parameters_t    myADS111X_I2C_parameters;
//	ADS111X_data_t 		myADS111X_Data;
//	ADS111X_status_t  	aux;

	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */
	SystemInit ();

	conf_CLK  	();
	conf_GPIO 	();
	conf_UART 	();
	conf_Timer0 ();


	/* I2C definition   */
//	myADS111X_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
//	myADS111X_I2C_parameters.sda         	 =    I2C0_SDA;
//	myADS111X_I2C_parameters.scl         	 =    I2C0_SCL;
//	myADS111X_I2C_parameters.addr        	 =    ADS111X_ADDRESS;
//	myADS111X_I2C_parameters.freq        	 =    100000;
//	myADS111X_I2C_parameters.pclkFrequency 	 =	  6400000;
//	myADS111X_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
//	myADS111X_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	//aux  =   ADS111X_Init ( myADS111X_I2C_parameters );

	/* Get the device type version	 */
	//aux	 =	 ADS111X_GetDeviceType ( myADS111X_I2C_parameters, &myADS111X_Data.hw_version );





	/* Enable Timer0	 */
	pADI_TMR0->CTL	|=	 ( 1U << BITP_TMR_CTL_EN );


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

			/* Get the temperature value	 */
			//aux  	 =   ADS111X_GetDeviceTemperature ( myADS111X_I2C_parameters, &myADS111X_Data.device_temp );


//			/* Transmit data through the UART	 */
//			sprintf ( (char*)myMessage, "White counter: %d | Lux: %0.4f lx\r\n", myADS111X_Data.white_channel_output_data, myADS111X_Data.light_level );
//
//			/* Check that is safe to send data	 */
//			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );
//
//			/* Transmit data back	 */
//			myPtr            =   &myMessage[0];
//			pADI_UART0->TX	 =	 *myPtr;
//
//			/* Transmit Buffer Empty Interrupt: Enabled	 */
//			pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables and turn both LEDs off	 */
			myState	 		 =	 0UL;
			pADI_GPIO1->CLR	|=	 DS4;
			pADI_GPIO2->CLR	|=	 DS3;
		}
	}

	/* It should never reach here	 */
	return 0;
}

