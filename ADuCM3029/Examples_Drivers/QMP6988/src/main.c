/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: QMP6988.
 * 				A new sample is read every 1 second and transmitted through the UART (115200 baud)
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/February/2022
 * @version     12/February/2022    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.10.1.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
//#include "QMP6988.h"


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
	uint32_t 			i;
	uint8_t  			myMessage[ TX_BUFF_SIZE ];
//	I2C_parameters_t    myQMP6988_I2C_parameters;
//	QMP6988_user_data_t	myQMP6988_Data;
//	QMP6988_status_t  	aux;

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


//	/* I2C definition   */
//	myQMP6988_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
//	myQMP6988_I2C_parameters.sda         	 =    I2C0_SDA;
//	myQMP6988_I2C_parameters.scl         	 =    I2C0_SCL;
//	myQMP6988_I2C_parameters.addr        	 =    QMP6988_ADDRESS;
//	myQMP6988_I2C_parameters.freq        	 =    100000;
//	myQMP6988_I2C_parameters.pclkFrequency =	  6400000;
//	myQMP6988_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
//	myQMP6988_I2C_parameters.sclPort     	 =    pADI_GPIO0;
//
//	/* Configure I2C peripheral */
//	aux  =   QMP6988_Init ( myQMP6988_I2C_parameters );
//
//	/* Reset the device	 */
//	aux  =   QMP6988_SoftReset ( myQMP6988_I2C_parameters );



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

//			/* Trigger a new measurement data	 */
//			aux	 =	QMP6988_TriggerMeasurement ( myQMP6988_I2C_parameters );
//			for ( i = 0UL; i < 0x232; i++ ){}
//
//			/* Get the temperature value	 */
//			aux	 =	QMP6988_GetAllData ( myQMP6988_I2C_parameters, (QMP6988_user_data_t*)&myQMP6988_Data );
//
//			/* Process the temperature data	 */
//			myQMP6988_Data.temperature.temperature = QMP6988_ProcessTemperature ( myQMP6988_Data.temperature.raw_temperature );
//
//			/* Process the humidity data	 */
//			myQMP6988_Data.humidity.humidity = QMP6988_ProcessHumidity ( myQMP6988_Data.humidity.raw_humidity );
//
//
//			/* Transmit data through the UART	 */
//			sprintf ( (char*)myMessage, "Temp: %0.2f C | RH: %0.3f %%\r\n", myQMP6988_Data.temperature.temperature, myQMP6988_Data.humidity.humidity );

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
