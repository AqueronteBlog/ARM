/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: TMP102.
 * 				A new temperature measurement is sampled every 1 second and transmitted through
 * 				the UART (115200 baud).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/July/2019
 * @version     25/July/2019    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "TMP102.h"


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
	uint8_t  			 myMessage[ TX_BUFF_SIZE ];
	I2C_parameters_t     myTMP102_I2C_parameters;
	TMP102_vector_data_t myTMP102_Data;
	TMP102_status_t      aux;

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
	myTMP102_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	myTMP102_I2C_parameters.sda         	 =    I2C0_SDA;
	myTMP102_I2C_parameters.scl         	 =    I2C0_SCL;
	myTMP102_I2C_parameters.addr        	 =    TMP102_ADDRESS_A0_GROUND;
	myTMP102_I2C_parameters.freq        	 =    100000;
	myTMP102_I2C_parameters.pclkFrequency	 =	  6400000;
	myTMP102_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	myTMP102_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   TMP102_Init ( myTMP102_I2C_parameters );

	/* Read TLOW value */
	aux  =   TMP102_Read_T_LOW_Register         ( myTMP102_I2C_parameters, &myTMP102_Data );

	/* Read THIGH value */
	aux  =   TMP102_Read_T_HIGH_Register        ( myTMP102_I2C_parameters, &myTMP102_Data );

	/* Set polarity LOW */
	aux  =   TMP102_SetPolarityAlertPinOutput   ( myTMP102_I2C_parameters, TMP102_CONFIGURATION_POL_ALERT_PIN_ACTIVE_LOW );

	/* Set Normal mode operation */
	aux  =   TMP102_SetModeOperation            ( myTMP102_I2C_parameters, TMP102_CONFIGURATION_EM_NORMAL_MODE_OPERATION );

	/* Set Conversion Rate: 4Hz */
	aux  =   TMP102_SetConversionRate           ( myTMP102_I2C_parameters, TMP102_CONFIGURATION_CR_4_HZ );

	/* Set Shutdown mode */
	aux  =   TMP102_SetShutdownMode             ( myTMP102_I2C_parameters, TMP102_CONFIGURATION_SD_ENABLED );


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

		if ( myState != 0U )
		{
			/* Turn both LEDs on	 */
			pADI_GPIO1->SET	|=	 DS4;
			pADI_GPIO2->SET	|=	 DS3;

			/* New reading */
			aux  =   TMP102_TriggerSingleTemperatureConversion ( myTMP102_I2C_parameters );

			/* Wait until the conversion is finished    */
			do
			{
				aux      =   TMP102_ReadConfigurationRegister ( myTMP102_I2C_parameters, &myTMP102_Data );
			}while( ( myTMP102_Data.ConfigurationRegister & TMP102_CONFIGURATION_OS_MASK ) == TMP102_CONFIGURATION_OS_BUSY );   // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
			                                                                                                                    // [WORKAROUND] Insert a counter.

			/* Read the new temperature value */
			aux  =   TMP102_GetTemperature ( myTMP102_I2C_parameters, &myTMP102_Data );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "T: %0.4f C\r\n", myTMP102_Data.Temperature );

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

