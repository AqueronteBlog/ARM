/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: VEML6035.
 * 				A new sample is read every 1 second and transmitted through the UART (115200 baud).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "VEML6035.h"


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
	I2C_parameters_t    myVEML6035_I2C_parameters;
	VEML6035_data_t 	myVEML6035_Data;
	VEML6035_status_t  	aux;

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
	myVEML6035_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	myVEML6035_I2C_parameters.sda         	 =    I2C0_SDA;
	myVEML6035_I2C_parameters.scl         	 =    I2C0_SCL;
	myVEML6035_I2C_parameters.addr        	 =    VEML6035_ADDRESS;
	myVEML6035_I2C_parameters.freq        	 =    100000;
	myVEML6035_I2C_parameters.pclkFrequency =	  6400000;
	myVEML6035_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	myVEML6035_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   VEML6035_Init ( myVEML6035_I2C_parameters );

	/* Power off the device	 */
	myVEML6035_Data.configuration.als_sd	 =	 ALS_CONF_ALS_SD_SHUTDOWN;
	aux	 =	 VEML6035_SetShutDownMode ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set sensitivity: low sensitivity ( 1/8x )	 */
	myVEML6035_Data.configuration.als_sens	 =	 ALS_CONF_SENS_LOW_SENSITIVITY;
	aux	 =	 VEML6035_SetSensitivity ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set digital gain (DG): Double	 */
	myVEML6035_Data.configuration.als_dg	 =	 ALS_CONF_DG_DOUBLE;
	aux	 =	 VEML6035_SetDG ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set Gain: Double sensitivity	 */
	myVEML6035_Data.configuration.als_gain	 =	 ALS_CONF_GAIN_DOUBLE_SENSITIVITY;
	aux	 =	 VEML6035_SetGain ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set ALS integration time: Integration time 100ms	 */
	myVEML6035_Data.configuration.als_it	 =	 ALS_CONF_ALS_IT_100MS;
	aux	 =	 VEML6035_SetIntegrationTime ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set Channel enable function: ALS and WHITE CH enable	 */
	myVEML6035_Data.configuration.als_channel_en	 =	 ALS_CONF_ALS_CHANNEL_EN_ALS_WHITE_CH;
	aux	 =	 VEML6035_SetChannelEnable ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set Interrupt: INT disable	 */
	myVEML6035_Data.configuration.als_int_en	 =	 ALS_CONF_ALS_INT_EN_INT_DISABLE;
	aux	 =	 VEML6035_SetInterruptEnable ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Set Power safe mode: PSM WAIT 0.8s | PSM disabled	 */
	myVEML6035_Data.psm_wait	 =	 POWER_SAVING_PSM_WAIT_0_4_S;
	myVEML6035_Data.psm_en		 =	 POWER_SAVING_PSM_EN_ENABLE;
	aux	 =	 VEML6035_SetPowerSafeMode ( myVEML6035_I2C_parameters, myVEML6035_Data );

	/* Power on the device	 */
	myVEML6035_Data.configuration.als_sd	 =	 ALS_CONF_ALS_SD_POWER_ON;
	aux	 =	 VEML6035_SetShutDownMode ( myVEML6035_I2C_parameters, myVEML6035_Data );


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
			aux  	 =   VEML6035_GetALS_HighResOutputData ( myVEML6035_I2C_parameters, &myVEML6035_Data );

			/* Get the raw white channel output data	 */
			aux  	 =   VEML6035_GetWhiteChannelOutputData ( myVEML6035_I2C_parameters, &myVEML6035_Data );

			/* Calculate light data and resolution	 */
			VEML6035_CalculateLuxLevel ( &myVEML6035_Data );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "White counter: %d | Lux: %0.4f lx\r\n", myVEML6035_Data.white_channel_output_data, myVEML6035_Data.light_level );

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

