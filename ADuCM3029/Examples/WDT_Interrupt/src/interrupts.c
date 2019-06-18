/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/June/2019
 * @version     13/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void WDog_Tmr_Int_Handler  ( void )
 * @details     WDT subroutine.
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
 * @date        14/June/2019
 * @version     17/June/2019    Clear IRQ was added and check the source of the
 * 								interrupt.
 * 				14/June/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void WDog_Tmr_Int_Handler ( void )
{
	/* Check if WDT interrupt pending	 */
	if ( ( pADI_WDT0->STAT & ( 1U << BITP_WDT_STAT_IRQ ) ) == ( 1U << BITP_WDT_STAT_IRQ ) )
	{
		/* New action	 */
		myState	 =	 1UL;

		/* Clear IRQ	 */
		pADI_WDT0->RESTART	 =	 0xCCCC;
	}
}
