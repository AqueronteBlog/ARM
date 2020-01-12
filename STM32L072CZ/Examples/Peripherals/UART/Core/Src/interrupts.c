/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "interrupts.h"


/**
 * @brief       void USART4_5_IRQHandler ()
 * @details     USART4 and USART5 interrupt subroutine.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/December/2019
 * @version     31/December/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void USART4_5_IRQHandler ( void )
{
	/* TX: TRANSMISSION COMPLETE	 */
	if ( ( USART5->ISR & USART_ISR_TC_Msk ) == 	USART_ISR_TC )
	{
		USART5->ICR	|=	 USART_ICR_TCCF ;						// Clear flag

		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{
			//myUART_TxEnd	 =	 1UL;
			USART5->CR1	&=	~USART_CR1_TE;						// Transmitter Disabled
		}
		else
		{
			USART5->TDR	 =	 *++myPtr;
		}
	}


	/* RX: RECEIVE	 */
	if ( ( USART5->ISR & USART_ISR_RXNE_Msk ) == USART_ISR_RXNE )
	{
		myRX	 =	 USART5->RDR;
	}
}
