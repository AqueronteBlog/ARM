/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "interrupts.h"



/**
 * @brief       void WWDG_IRQHandler ( void )
 * @details     WWDG subroutine.
 *
 *
 * @param[in]    N/A.
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void WWDG_IRQHandler ( void )
{
	/* Early wakeup Interrupt	 */
	if ( ( WWDG->SR & WWDG_SR_EWIF_Msk ) == WWDG_SR_EWIF )
	{
		GPIOA->BSRR		=	( 1 << LED_1 );			// LED1 ON

		/* Clear flags	 */
		WWDG->SR	&=	~WWDG_SR_EWIF;
	}
}
