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
 * @brief       void RTC1_Int_Handler  ( void )
 * @details     [todo]RTC1 subroutine.
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
void RTC1_Int_Handler ( void )
{
	/* Check if RTC1 interrupt pending	 */
	if ( ( pADI_RTC1->SR0 & ( 1U << BITP_RTC_SR0_ALMINT ) ) == ( 1U << BITP_RTC_SR0_ALMINT ) )
	{
		/* Blink LED	 */
		pADI_GPIO2->TGL	|=	 DS3;

		/* Clear Alarm Interrupt Source	 */
		pADI_RTC1->SR0	|=	 ( 1U << BITP_RTC_SR0_ALMINT );
	}
}
