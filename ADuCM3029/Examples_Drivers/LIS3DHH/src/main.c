/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: LIS3DHH.
 * 				It gets a new acceleration data and temperature data every 250ms and then, it is sent through
 * 				the UART (115200 baud).
 *
 * 				The rest of the time, the microcontroller is in low-power: Flexi Mode.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <sys/platform.h>
#include "adi_initialize.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "LIS3DHH.h"


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
	spi_parameters_t     myLIS3DHH_SPI_parameters;
	LIS3DHH_user_data_t  myLIS3DHH_Data;
	LIS3DHH_status_t     aux;

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
//	myLIS3DHH_SPI_parameters.i2cInstance 	 =    pADI_I2C0;
//	myLIS3DHH_SPI_parameters.sda         	 =    I2C0_SDA;
//	myLIS3DHH_SPI_parameters.scl         	 =    I2C0_SCL;
//	myLIS3DHH_SPI_parameters.addr        	 =    LIS3DHH_ADDRESS_A0_GROUND;
//	myLIS3DHH_SPI_parameters.freq        	 =    100000;
//	myLIS3DHH_SPI_parameters.pclkFrequency	 =	  6400000;
//	myLIS3DHH_SPI_parameters.sdaPort     	 =    pADI_GPIO0;
//	myLIS3DHH_SPI_parameters.sclPort     	 =    pADI_GPIO0;

	/* Configure I2C peripheral */
	aux  =   LIS3DHH_Init ( myLIS3DHH_SPI_parameters );

	/* Get device ID */
	aux  =   LIS3DHH_GetDeviceIdentification	( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.who_am_i );

	/* Reset the device, wait until the device resets */
	aux  =   LIS3DHH_SoftwareReset ( myLIS3DHH_SPI_parameters );
	do{
		LIS3DHH_GetSoftwareResetStatus ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.sw_reset );
	}while( myLIS3DHH_Data.sw_reset == CTRL_REG1_SW_RESET_RESET_DEVICE );

	/* Set register address auto incremented */
	myLIS3DHH_Data.if_add_inc	=	 CTRL_REG1_IF_ADD_INC_ENABLED;
	aux  =   LIS3DHH_SetRegisterAutoIncrement ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.if_add_inc );

	/* Set block data update: Continuous */
	myLIS3DHH_Data.bdu	=	 CTRL_REG1_BDU_CONTINUOUS_UPDATE;
	aux  =   LIS3DHH_SetBlockDataUpdate	( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.bdu );

	/* Set Digital filtering selection: FIR Linear Phase */
	myLIS3DHH_Data.dsp_lp_type	 =	 CTRL_REG4_DSP_LP_TYPE_FIR_LINEAR_PHASE;
	aux  =   LIS3DHH_SetDigitalFilter ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.dsp_lp_type );

	/* Set User-selectable bandwidth: 440Hz */
	myLIS3DHH_Data.dsp_bw_sel	 =	 CTRL_REG4_DSP_BW_SEL_440_HZ_TYP;
	aux  =   LIS3DHH_SetUserBandwidth ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.dsp_bw_sel );

	/* Set Self-test enable: Self-test disabled ( Normal mode ) */
	myLIS3DHH_Data.st	 =	 CTRL_REG4_ST_NORMAL_MODE;
	aux  =   LIS3DHH_SetSelfTest ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.st );

	/* Push-pull/open drain selection on INT2 pin: push-pull mode */
	myLIS3DHH_Data.pp_od_int2	 =	 CTRL_REG4_PP_OD_INT2_PUSH_PULL_MODE;
	aux  =   LIS3DHH_SetINT2_PinMode ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.pp_od_int2 );

	/* Push-pull/open drain selection on INT1 pin: push-pull mode */
	myLIS3DHH_Data.pp_od_int1	 =	 CTRL_REG4_PP_OD_INT1_PUSH_PULL_MODE;
	aux  =   LIS3DHH_SetINT1_PinMode ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.pp_od_int1 );

	/* FIFO memory enable: disabled */
	myLIS3DHH_Data.fifo_en	 =	 CTRL_REG4_FIFO_EN_DISABLED;
	aux  =   LIS3DHH_SetFIFO_MemoryEnable ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.fifo_en );

	/* Disables the SPI high speed configuration for the FIFO block */
	myLIS3DHH_Data.fifo_spi_hs_on	 =	 CTRL_REG5_FIFO_SPI_HS_ON_DISABLED;
	aux  =   LIS3DHH_SetFIFO_SPI_HighSpeed ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.fifo_spi_hs_on );

	/* Bypass mode. FIFO turned off, FIFO threshold level setting = 0 */
	myLIS3DHH_Data.fifo.fmode	 =	 FIFO_CTRL_FMODE_FIFO_OFF;
	myLIS3DHH_Data.fifo.fth		 =	 0U;
	aux  =   LIS3DHH_SetFIFO_Control ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.fifo );

	/* Power mode: Normal mode */
	myLIS3DHH_Data.norm_mod_en	 =	 CTRL_REG1_NORM_MOD_EN_ENABLED;
	aux  =   LIS3DHH_SetPowerMode ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.norm_mod_en );



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

			/* Wait until new data is available	 */
			do
			{
				aux	 =	 LIS3DHH_GetStatusRegister ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.status );
			}while( ( myLIS3DHH_Data.status & STATUS_ZYXDA_MASK ) != STATUS_ZYXDA_NEW_DATA );   			// [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
			                                                                                                // [WORKAROUND] Insert a counter.

			/* Read the new acceleration data, X-axis, Y-axis and Z-axis */
			aux  =   LIS3DHH_GetAccelerationData ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.acc );

			/* Read the new temperature value */
			aux  =   LIS3DHH_GetRawTemperature ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.out_temp );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "X: %0.3f mG | Y: %0.3f mG | Z: %0.3f mG |T: %0.2f C\r\n", myLIS3DHH_Data.acc.acc.out_x, myLIS3DHH_Data.acc.acc.out_y, myLIS3DHH_Data.acc.acc.out_z, myLIS3DHH_Data.out_temp.temperature );

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

