/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: HDC2080.
 * 				A new temperature and humidity measurement is sampled every 1 second and transmitted through
 * 				the UART (115200 baud).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/October/2019
 * @version     10/October/2019    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "HDC2080.h"


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
	uint8_t  			myMessage[ TX_BUFF_SIZE ];
	I2C_parameters_t    myHDC2080_I2C_parameters;
	HDC2080_data_t 	 	myHDC2080_Data;
	HDC2080_status_t  	aux;

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
	myHDC2080_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	myHDC2080_I2C_parameters.sda         	 =    I2C0_SDA;
	myHDC2080_I2C_parameters.scl         	 =    I2C0_SCL;
	myHDC2080_I2C_parameters.addr        	 =    HDC2080_ADDRESS_GND;
	myHDC2080_I2C_parameters.freq        	 =    100000;
	myHDC2080_I2C_parameters.pclkFrequency	 =	  6400000;
	myHDC2080_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	myHDC2080_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   HDC2080_Init ( myHDC2080_I2C_parameters );

	/* Perform a software reset */
	aux	 =	 HDC2080_SetSoftReset ( myHDC2080_I2C_parameters );
	do{
		aux	 =	 HDC2080_GetSoftReset ( myHDC2080_I2C_parameters, &myHDC2080_Data );
	}while( ( myHDC2080_Data.soft_res & RESET_DRDY_INT_CONF_SOFT_RES_MASK ) == RESET_DRDY_INT_CONF_SOFT_RES_RESET );

	/* Get Manufacturer IDs	 */
	aux	 =	 HDC2080_GetManufacturerID ( myHDC2080_I2C_parameters, &myHDC2080_Data );

	/* Get device IDs	 */
	aux	 =	 HDC2080_GetDeviceID ( myHDC2080_I2C_parameters, &myHDC2080_Data );

	/* Auto measurement mode: Disable (  Initiate measurement via I2C )	 */
	myHDC2080_Data.amm	 =	 RESET_DRDY_INT_CONF_AMM_DISABLED;
	aux	 =	 HDC2080_SetAutoMeasurementMode ( myHDC2080_I2C_parameters, myHDC2080_Data );

	/* Heater off	 */
	myHDC2080_Data.heater_en	 =	 RESET_DRDY_INT_CONF_HEAT_EN_OFF;
	aux	 =	 HDC2080_SetHeaterMode ( myHDC2080_I2C_parameters, myHDC2080_Data );

	/* DRDY/INT_EN pin configuration: High Z	 */
	myHDC2080_Data.drdy_intEn	 =	 RESET_DRDY_INT_CONF_DRDY_INT_EN_HIGH_Z;
	aux	 =	 HDC2080_SetHeaterMode ( myHDC2080_I2C_parameters, myHDC2080_Data );

	/* All interrupts are disabled	 */
	myHDC2080_Data.drdy_enable	=	 INTERRUPT_DRDY_DRDY_ENABLE_INTERRUPT_DISABLE;
	myHDC2080_Data.th_enable	=	 INTERRUPT_DRDY_TH_ENABLE_INTERRUPT_DISABLE;
	myHDC2080_Data.tl_enable	=	 INTERRUPT_DRDY_TL_ENABLE_INTERRUPT_DISABLE;
	myHDC2080_Data.hh_enable	=	 INTERRUPT_DRDY_HH_ENABLE_INTERRUPT_DISABLE;
	myHDC2080_Data.hl_enable	=	 INTERRUPT_DRDY_HL_ENABLE_INTERRUPT_DISABLE;
	aux						 	=	 HDC2080_SetInterruptConfiguration ( myHDC2080_I2C_parameters, myHDC2080_Data );

	/* Measurement configuration: Humidity and Temperature 14-bit resolution. Both measurement enabled	 */
	myHDC2080_Data.tres			=	 MEASUREMENT_CONF_TRES_14_BIT;
	myHDC2080_Data.hres			=	 MEASUREMENT_CONF_HRES_14_BIT;
	myHDC2080_Data.meas_conf	=	 MEASUREMENT_CONF_MEAS_CONF_HUMIDITY_TEMPERATURE;
	aux						 	=	 HDC2080_SetMeasurementConf ( myHDC2080_I2C_parameters, myHDC2080_Data );


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

			/* Trigger a new sample	 */
			aux	 =	 HDC2080_StartMeasurementTrigger ( myHDC2080_I2C_parameters );

			/* Wait until the conversion is finished    */
			do
			{
				aux      =   HDC2080_GetMeasurementTrigger ( myHDC2080_I2C_parameters, &myHDC2080_Data );
			}while( ( myHDC2080_Data.meas_trig & MEASUREMENT_CONF_MEAS_TRIG_MASK ) != MEASUREMENT_CONF_MEAS_TRIG_NO_ACTION );    // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
						                                                                                      	  	  	  	  	 // [WORKAROUND] Insert a counter.

			/* Get temperature */
			aux  =   HDC2080_GetTemperature ( myHDC2080_I2C_parameters, &myHDC2080_Data );

			/* Get humidity	 */
			aux  =   HDC2080_GetHumidity ( myHDC2080_I2C_parameters, &myHDC2080_Data );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "T: %0.2f C | RH: %0.2f %%\r\n", myHDC2080_Data.temperature, myHDC2080_Data.humidity );

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

