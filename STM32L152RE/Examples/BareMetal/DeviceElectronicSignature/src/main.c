/**
 * @brief       main.c
 * @details     This example shows how to read the internal Device Electronic Signature ( flash size and
 * 				ID ). Every two seconds, the data will be transmitted through the UART ( 230400 baud rate ).
 *
 * 				The microcontroller will remain in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with Atollic TrueSTUDIO for STM32
 *              ( v9.0.1 ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */
#include <stdio.h>

#include "stm32l1xx.h"
#include "stm32l1xx_hal.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



/**@brief Constants.
 */
#define TX_BUFF_SIZE  128	                     			/*!<   UART buffer size                              	*/
#define UART_CLK	  16000000UL                   			/*!<   UART f_CK = 16 MHz                              	*/

#define F_SIZE	( *(uint16_t *) ( 0x1FF800CC ) )			/*!< Flash size register ( Cat.5 )						*/

#define U_ID1	( *(uint32_t *) ( 0x1FF800D0 ) )
#define U_ID2	( *(uint32_t *) ( 0x1FF800D0 + 0x04 ) )		/*!< Unique device ID registers ( 96 bits )( Cat.5 )	*/
#define U_ID3	( *(uint32_t *) ( 0x1FF800D0 + 0x14 ) )



/**@brief Variables.
 */
volatile uint32_t mySystemCoreClock;				/*!<  System CLK in MHz  		   							*/
volatile uint32_t myUARTClock;						/*!<  UART CLK in MHz  		   	   							*/

volatile uint32_t myState;                        	/*!<  State that indicates when performs a new reading		*/
volatile uint32_t myUART_TxEnd;                     /*!<  It indicates when an UART transmission is finished	*/
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      	/*!<  Message to be transmitted through the UART         	*/
volatile uint8_t  *myPtr;                         	/*!<  Pointer to point out myMessage                     	*/




/**@brief Function for application main entry.
 */
int main ( void )
{
	Conf_GPIO 	 ();
	Conf_CLK  	 ();
	Conf_USART 	 ( UART_CLK, 230400 );				// 230400 Baud Rate
	Conf_RTC     ();


	/* Range 2: System frequency up to 16 MHz	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG ( PWR_REGULATOR_VOLTAGE_SCALE2 );


	while ( 1 )
	{
		/* Low power: Stop mode	 */
		HAL_PWR_EnterSTOPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );

		/* Re-configure the CLKs	 */
		Conf_CLK ();

		/* Check myState	 */
		if ( myState == 1UL )
		{
			GPIOA->BSRR	 =	 ( 1UL << LED_1 );					// Turn it ON

			/* Parse the data	 */
			sprintf ( (char*)myMessage, "Flash Size: %d Kbytes | ID1: %x, ID2: %x, ID3: %x\r\n", F_SIZE, (unsigned int)U_ID1, (unsigned int)U_ID2, (unsigned int)U_ID3 );

			/* Transmit data through the UART	 */
			myPtr   	 =   &myMessage[0];
			USART2->DR	 =	 *myPtr;
			USART2->CR1	|=	 USART_CR1_TE;						// Transmitter Enabled

			/* Low power: Sleep mode, wait until all data was sent through the UART	 */
			do{
				HAL_PWR_EnterSLEEPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
			}while ( myUART_TxEnd == 0UL );


			/* Reset variables	 */
			myUART_TxEnd	 =	 0UL;
			myState	 		 =	 0UL;
			GPIOA->BRR		 =	( 1UL << LED_1 );				// Turn it OFF
		}
	}
}
