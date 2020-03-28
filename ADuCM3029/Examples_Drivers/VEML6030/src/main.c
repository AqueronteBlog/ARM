/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: VEML6030.
 * 				A new sample is read every 1 second and transmitted through
 * 				the UART (115200 baud).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/November/2019
 * @version     29/November/2019    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     NOT Tested!.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "VEML6030.h"


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
	I2C_parameters_t    myVEML6030_I2C_parameters;
	VEML6030_data_t 	myVEML6030_Data;
	VEML6030_status_t  	aux;

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
	myVEML6030_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	myVEML6030_I2C_parameters.sda         	 =    I2C0_SDA;
	myVEML6030_I2C_parameters.scl         	 =    I2C0_SCL;
	myVEML6030_I2C_parameters.addr        	 =    VEML6030_ADDRESS_GND;
	myVEML6030_I2C_parameters.freq        	 =    100000;
	myVEML6030_I2C_parameters.pclkFrequency =	  6400000;
	myVEML6030_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	myVEML6030_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   VEML6030_Init ( myVEML6030_I2C_parameters );

	/* Power on the device	 */
	myVEML6030_Data.als_sd	 =	 ALS_CONF_ALS_SD_POWER_ON;
	aux	 =	 VEML6030_SetConfiguration ( myVEML6030_I2C_parameters, myVEML6030_Data );

	/* Wait until the device is stable ( wait >= 2.5ms )	 */
	for ( uint32_t i = 0UL; i < 0x2323; i++);

	/* Configure the device: Integration time 100ms | Gain x1 | Interrupt disabled	 */
	myVEML6030_Data.als_it	 	 =	 ALS_CONF_ALS_IT_100MS;
	myVEML6030_Data.als_gain 	 =	 ALS_CONF_ALS_GAIN_X1;
	myVEML6030_Data.als_int_en	 =	 ALS_CONF_ALS_INT_EN_DISABLE;
	aux	 =	 VEML6030_SetConfiguration ( myVEML6030_I2C_parameters, myVEML6030_Data );


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

			/* Get the raw light data	 */
			aux  	 =   VEML6030_GetALS_OuputData ( myVEML6030_I2C_parameters, &myVEML6030_Data );

			/* Calculate light data and resolution	 */
			aux  	 =   VEML6030_CalculateLuxValue ( myVEML6030_I2C_parameters, &myVEML6030_Data );

			/* Power on the device: New sample	 */
			myVEML6030_Data.als_sd	 =	 ALS_CONF_ALS_SD_POWER_ON;
			aux	 =	 VEML6030_SetConfiguration ( myVEML6030_I2C_parameters, myVEML6030_Data );

			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "Raw Lux: %d | Lux: %0.4f lx\r\n", myVEML6030_Data.als_high_resolution_output_data, myVEML6030_Data.light_level );

			/* Check that is safe to send data	 */
			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );

			/* Transmit data back	 */
			myPtr            =   &myMessage[0];
			pADI_UART0->TX	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			//pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables and turn both LEDs off	 */
			myState	 		 =	 0UL;
			pADI_GPIO1->CLR	|=	 DS4;
			pADI_GPIO2->CLR	|=	 DS3;
		}
	}

	/* It should never reach here	 */
	return 0;
}

