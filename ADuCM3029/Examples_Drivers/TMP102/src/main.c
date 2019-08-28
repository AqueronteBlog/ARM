/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the internal peripheral: UART.
 * 				If '1' is received, LED1 is turned on, if '2' is received, the LED2 is turned on.
 * 				A message will be transmitted back, any other value will turn both LEDs off.
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

	conf_CLK  ();
	conf_GPIO ();
	//conf_UART ();

	//adi_i2c_ReadWrite


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

	while (1)
	{
		/* I2C driver test */
		myTMP102_Data.THIGH_Register	 =	 0x2323;
		aux  =   TMP102_Write_T_HIGH_Register ( myTMP102_I2C_parameters, myTMP102_Data );

		myTMP102_Data.THIGH_Register	 =	 0x00;
		aux  =   TMP102_Read_T_HIGH_Register ( myTMP102_I2C_parameters, &myTMP102_Data );
	}


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


			/* Check that is safe to send data	 */
			while( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) == ~( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) );

			/* Transmit data back	 */
			myPtr            =   &myMessage[0];
			pADI_UART0->TX	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ETBEI );

			/* Reset variables	 */
			myState	 =	 0U;
		}
	}

	/* It should never reach here	 */
	return 0;
}

