/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "interrupts.h"

/**
 * @brief       void UART5_IRQHandler ()
 * @details     UART5 subroutine.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        4/January/2018
 * @version     5/January/2018   TC added, RX completed
 * 				4/January/2018   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void UART5_IRQHandler(void)
{
	myLED1 = LED_1;


	// TX: TRANSMISSION COMPLETE
	if ( ( UART5->SR & USART_SR_TC ) == USART_SR_TC )
	{
		UART5->SR	&=	~USART_SR_TC ;									// Clear flag

		UART5->CR1	&=	~USART_CR1_TE;									// Transmitter Disabled
	}


	// RX: RECEIVE
    if ( ( UART5->SR & USART_SR_RXNE ) == USART_SR_RXNE )
    {
    	UART5->SR	&=	~USART_SR_RXNE;									// Clear flag

    	// Change the state of the LED1 only if received data is 0x01
    	if ( ( UART5->DR & USART_DR_DR_Msk ) == '1' )
    	{
    		// Check last status of the LED1
    		if ( ( GPIOA->ODR & ( 1 << myLED1 ) ) == ( 1 << myLED1 ) )
    			GPIOA->BRR	=	( 1 << myLED1 );						// Turn it OFF
    		else
    			GPIOA->BSRR	=	( 1 << myLED1 );						// Turn it ON

    		// Transmit the state of port A through the UART
    		UART5->DR	 =	 ( GPIOA->ODR & 0xFF );
    		UART5->CR1	|=	 USART_CR1_TE;								// Transmitter Enabled
    	}
    }
}
