/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/September/2019
 * @version     21/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void UART_Int_Handler  ( void )
 * @details     UART subroutine.
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/September/2019
 * @version     21/September/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void UART_Int_Handler ( void )
{
	/* Rx	 */
	if ( ( pADI_UART0->LSR & ( 1U << BITP_UART_LSR_DR ) ) == ( 1U << BITP_UART_LSR_DR ) )
	{
		/* Next action	 */
		myState	 =	 (uint8_t)( pADI_UART0->RX );
	}

	/* Tx	 */
	if ( ( ( pADI_UART0->LSR & ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) ==  ( ( 1U << BITP_UART_LSR_THRE ) | ( 1U << BITP_UART_LSR_TEMT ) ) ) )
	{
		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{
			pADI_UART0->IEN	&=	~( 1U << BITP_UART_IEN_ETBEI );
		}
		else
		{
			pADI_UART0->TX	 =	 *++myPtr;
		}
	}
}


