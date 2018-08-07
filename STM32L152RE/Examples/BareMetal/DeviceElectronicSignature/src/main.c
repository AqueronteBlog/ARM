/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the internal peripheral RTC using the
 * 				periodic wake-up timer. The LED will change its state every 1 second.
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

volatile uint32_t myState;                        	/*!<   State that indicates when to perform an ADC sample	*/
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      	/*!<   Message to be transmitted through the UART         	*/
volatile uint8_t  *myPtr;                         	/*!<   Pointer to point out myMessage                     	*/




/**@brief Function for application main entry.
 */
int main ( void )
{
	Conf_GPIO 	 ();
	Conf_CLK  	 ();
	Conf_USART 	 ( UART_CLK, 115200 );				// 115200 Baud Rate
	Conf_RTC     ();


	while ( 1 )
	{
		//HAL_PWR_EnterSTOPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );

		if ( myState == 1UL )
		{
			GPIOA->BSRR	 =	 ( 1UL << LED_1 );						// Turn it ON

			sprintf ( (char*)myMessage, "Flash Size: %x\r\n", F_SIZE );


			myPtr   	 =   &myMessage[0];
			UART5->DR	 =	 *myPtr;
			UART5->CR1	|=	 USART_CR1_TE;							// Transmitter Enabled


			/* Reset variables	 */
			myState	 	=	 0;
			GPIOA->BRR	=	( 1 << LED_1 );							// Turn it OFF
		}
	}
}
