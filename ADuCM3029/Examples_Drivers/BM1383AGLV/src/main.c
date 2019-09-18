/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: BM1383AGLV.
 * 				A new temperature and pressure measurement is sampled every 1 second and transmitted through
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
#include "BM1383AGLV.h"


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
	I2C_parameters_t     myBM1383AGLV_I2C_parameters;
	BM1383AGLV_data_t 	 myBM1383AGLV_Data;
	BM1383AGLV_status_t  aux;

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
	myBM1383AGLV_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	myBM1383AGLV_I2C_parameters.sda         	 =    I2C0_SDA;
	myBM1383AGLV_I2C_parameters.scl         	 =    I2C0_SCL;
	myBM1383AGLV_I2C_parameters.addr        	 =    BM1383AGLV_ADDRESS;
	myBM1383AGLV_I2C_parameters.freq        	 =    100000;
	myBM1383AGLV_I2C_parameters.pclkFrequency	 =	  6400000;
	myBM1383AGLV_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	myBM1383AGLV_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   BM1383AGLV_Init ( myBM1383AGLV_I2C_parameters );

	/* Get device IDs	 */
	aux	 =	 BM1383AGLV_GetDeviceID ( myBM1383AGLV_I2C_parameters, &myBM1383AGLV_Data );

	/* Configure the device: 1 sample | DRDY pin disabled | One-shot mode	 */
	myBM1383AGLV_Data.ave_num	 =	 MODE_CONTROL_AVE_NUM_SINGLE;
	myBM1383AGLV_Data.dren		 =	 MODE_CONTROL_DREN_DRDY_DISABLE;

	/* Measurement control block is ACTIVE	 */
	myBM1383AGLV_Data.rstb	 =	 RESET_RSTB_ACTIVE;
	aux	 =	 BM1383AGLV_SetSoftReset ( myBM1383AGLV_I2C_parameters, myBM1383AGLV_Data );

	/* Device in Active mode	 */
	myBM1383AGLV_Data.pwr_down	 =	 POWER_DOWN_PWR_DOWN_ACTIVE;
	aux	 =	 BM1383AGLV_SetPowerDown ( myBM1383AGLV_I2C_parameters, myBM1383AGLV_Data );


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

			/* Trigegr a new sample	 */
			myBM1383AGLV_Data.mode		 =	 MODE_CONTROL_MODE_ONE_SHOT;
			aux	 =	 BM1383AGLV_SetModeControl ( myBM1383AGLV_I2C_parameters, myBM1383AGLV_Data );

			/* Wait until the conversion is finished    */
			do
			{
				aux      =   BM1383AGLV_GetStatus ( myBM1383AGLV_I2C_parameters, &myBM1383AGLV_Data );
			}while( ( myBM1383AGLV_Data.rd_drdy & STATUS_RD_DRDY_MASK ) == STATUS_RD_DRDY_DATA_MEASURING );   // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
						                                                                                      // [WORKAROUND] Insert a counter.

			/* Get pressure */
			aux  =   BM1383AGLV_GetPressure ( myBM1383AGLV_I2C_parameters, &myBM1383AGLV_Data );

			/* Get temperature	 */
			aux  =   BM1383AGLV_GetTemperature ( myBM1383AGLV_I2C_parameters, &myBM1383AGLV_Data );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "P: %0.2f hPa | T: %0.2f C\r\n", myBM1383AGLV_Data.pressure, myBM1383AGLV_Data.temperature );

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

