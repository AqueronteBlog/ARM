/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: QMP6988.
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
#include "QMP6988.h"


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
	I2C_parameters_t    myQMP6988_I2C_parameters;
	QMP6988_user_data_t	myQMP6988_Data;
	QMP6988_status_t  	aux;

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
	myQMP6988_I2C_parameters.i2cInstance 	 =    pADI_I2C0;
	myQMP6988_I2C_parameters.sda         	 =    I2C0_SDA;
	myQMP6988_I2C_parameters.scl         	 =    I2C0_SCL;
	myQMP6988_I2C_parameters.addr        	 =    QMP6988_ADDRESS_SDO_LOW;
	myQMP6988_I2C_parameters.freq        	 =    100000;
	myQMP6988_I2C_parameters.pclkFrequency =	  6400000;
	myQMP6988_I2C_parameters.sdaPort     	 =    pADI_GPIO0;
	myQMP6988_I2C_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   QMP6988_Init ( myQMP6988_I2C_parameters );

	/* Reset the device	 */
	//aux  =   QMP6988_SoftReset ( myQMP6988_I2C_parameters );
	for ( i = 0UL; i < 0x232; i++ );

	/* Get chip ID */
	aux  =   QMP6988_GetChipID ( myQMP6988_I2C_parameters, &myQMP6988_Data.chip_id );

	/* Wait until the OTP values are available	 */
	do{
		aux  =   QMP6988_GetDeviceStat ( myQMP6988_I2C_parameters, &myQMP6988_Data.device_stat );
	}while( ( myQMP6988_Data.device_stat & DEVICE_STAT_OTP_UPDATE_MASK ) == DEVICE_STAT_OTP_UPDATE_BUSY );

	/* Raw compensation coefficients */
	aux  =   QMP6988_GetRawCompensationCoefficients	( myQMP6988_I2C_parameters, &myQMP6988_Data.raw_k );

	/* Calculate compensation coefficients */
	myQMP6988_Data.k  =   QMP6988_CalculateCompensationCoefficients	( myQMP6988_Data.raw_k );

	/* Temperature average: FILTER: N = 4 */
	myQMP6988_Data.filter = IIR_FILTER_N_4;
	aux  =   QMP6988_SetIIR_Filter ( myQMP6988_I2C_parameters, myQMP6988_Data.filter );

	/* Temperature average: TEMP_AVERAGE:  8 */
	myQMP6988_Data.temp_average = CTRL_MEAS_TEMP_AVERAGE_8;
	aux  =   QMP6988_SetTemperatureAverage ( myQMP6988_I2C_parameters, myQMP6988_Data.temp_average );

	/* Pressure average: PRESS_AVERAGE:  8 */
	myQMP6988_Data.press_average = CTRL_MEAS_PRESS_AVERAGE_8;
	aux  =   QMP6988_SetPressureAverage ( myQMP6988_I2C_parameters, myQMP6988_Data.press_average );

	/* Power mode: Sleep mode */
	myQMP6988_Data.power_mode = CTRL_MEAS_POWER_MODE_SLEEP_MODE;
	aux  =   QMP6988_SetPowerMode ( myQMP6988_I2C_parameters, myQMP6988_Data.power_mode );


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

			/* Power mode: Forced mode */
			myQMP6988_Data.power_mode = CTRL_MEAS_POWER_MODE_FORCED_MODE;
			aux  =   QMP6988_SetPowerMode ( myQMP6988_I2C_parameters, myQMP6988_Data.power_mode );

			/* Wait until a new set of data is available	 */
			do{
				aux  =   QMP6988_GetDeviceStat ( myQMP6988_I2C_parameters, &myQMP6988_Data.device_stat );
			}while( ( myQMP6988_Data.device_stat & DEVICE_STAT_MEASURE_MASK ) == DEVICE_STAT_MEASURE_BUSY );

			/* Get the raw data */
			aux  =   QMP6988_GetRawMeasurements ( myQMP6988_I2C_parameters, &myQMP6988_Data.raw_txd );

			/* Process both temperature and pressure data	 */
			myQMP6988_Data.txd	 =	QMP6988_CalculateCompensatedMeasuredData( myQMP6988_Data.raw_txd, myQMP6988_Data.k );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "Temp: %0.2f C | Press: %0.3f Pa\r\n", myQMP6988_Data.txd.temperature, myQMP6988_Data.txd.pressure );

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
