/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/November/2019
 * @version     04/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void GP_Tmr0_Int_Handler  ( void )
 * @details     TMR0 subroutine.
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
 * @date        04/November/2019
 * @version     04/November/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void GP_Tmr0_Int_Handler ( void )
{
	/* Check if TMR0 interrupt pending	 */
	if ( ( pADI_TMR0->STAT & ( 1U << BITP_TMR_STAT_TIMEOUT ) ) == ( 1U << BITP_TMR_STAT_TIMEOUT ) )
	{
		/* Next state	 */
		myState	 =	 1UL;

		/* Clear IRQ	 */
		pADI_TMR0->CLRINT	|=	 ( 1U << BITP_TMR_CLRINT_TIMEOUT );
	}
}



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
 * @date        25/July/2019
 * @version     25/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void UART_Int_Handler ( void )
{
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


