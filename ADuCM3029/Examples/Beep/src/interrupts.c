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
 * @date        25/September/2019
 * @version     25/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void GP_Tmr0_Int_Handler ( void )
{
	/* Check if TMR0 interrupt pending	 */
	if ( ( pADI_TMR0->STAT & ( 1U << BITP_TMR_STAT_TIMEOUT ) ) == ( 1U << BITP_TMR_STAT_TIMEOUT ) )
	{
		/* Turn on the LED	 */
		pADI_GPIO2->SET	|=	 DS3;

		/* Next action	 */
		myState	 =	 1UL;

		/* Clear IRQ	 */
		pADI_TMR0->CLRINT	|=	 ( 1U << BITP_TMR_CLRINT_TIMEOUT );
	}
}



/**
 * @brief       void Beep_Int_Handler  ( void )
 * @details     BEEP subroutine.
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
 * @date        25/September/2019
 * @version     25/September/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Beep_Int_Handler ( void )
{
	/* Tone A has ended	 */
	if ( ( pADI_BEEP0->STAT & ( 1U << BITP_BEEP_STAT_AENDED ) ) == ( 1U << BITP_BEEP_STAT_AENDED ) )
	{
		/* Clear flag	 */
		pADI_BEEP0->STAT	|=	 ( 1U << BITP_BEEP_STAT_AENDED );

		/* Turn off the LED	 */
		pADI_GPIO2->CLR	|=	 DS3;
	}
}
