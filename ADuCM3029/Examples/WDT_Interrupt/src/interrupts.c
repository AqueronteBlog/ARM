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
 * @version     14/June/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void WDog_Tmr_Int_Handler ( void )
{
	myState	 =	 1UL;
}
