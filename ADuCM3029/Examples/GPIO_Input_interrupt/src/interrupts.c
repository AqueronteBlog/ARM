/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/July/2019
 * @version     04/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void GPIO_A_Int_Handler  ( void )
 * @details     GPIO_A subroutine.
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
 * @date        04/July/2019
 * @version     04/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void GPIO_A_Int_Handler ( void )
{
	/* Check if GPIO_A and GPIO34 interrupt pending	 */
	if ( ( pADI_GPIO2->INT & S4 ) == S4 )
	{
		/* Next action	 */
		myState	 =	 1UL;

		/* Clear flag	 */
		pADI_GPIO2->INT	|=	 S4;
	}
}
