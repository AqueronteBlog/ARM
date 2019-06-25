/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/June/2019
 * @version     25/June/2019   The ORIGIN
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
 * @date        25/June/2019
 * @version     25/June/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void GP_Tmr0_Int_Handler ( void )
{
	/* Check if TMR0 interrupt pending	 */
	if ( ( pADI_TMR0->STAT & ( 1U << BITP_TMR_STAT_TIMEOUT ) ) == ( 1U << BITP_TMR_STAT_TIMEOUT ) )
	{
		/* Blink LED	 */
		pADI_GPIO2->TGL	|=	 DS3;

		/* Clear IRQ	 */
		pADI_TMR0->CLRINT	|=	 ( 1U << BITP_TMR_CLRINT_TIMEOUT );
	}
}



/**
 * @brief       void GP_Tmr1_Int_Handler  ( void )
 * @details     TMR1 subroutine.
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
 * @date        25/June/2019
 * @version     25/June/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void GP_Tmr1_Int_Handler ( void )
{
	/* Check if TMR1 interrupt pending	 */
	if ( ( pADI_TMR1->STAT & ( 1U << BITP_TMR_STAT_TIMEOUT ) ) == ( 1U << BITP_TMR_STAT_TIMEOUT ) )
	{
		/* Blink LED	 */
		pADI_GPIO1->TGL	|=	 DS4;

		/* Clear IRQ	 */
		pADI_TMR1->CLRINT	|=	 ( 1U << BITP_TMR_CLRINT_TIMEOUT );
	}
}
