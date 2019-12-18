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
 * @brief       void LPTIM_IRQHandler ()
 * @details     [todo]If LPTIM happens, change the status of the LED1 then.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void LPTIM1_IRQHandler(void)
{
	if ( ( LPTIM1->ISR & LPTIM_ISR_ARRM_Msk ) == LPTIM_ISR_ARRM )
    {
    	/* Check last status of the LED1	 */
    	if ( ( GPIOB->ODR & ( 1 << LD1 ) ) == ( 1 << LD1 ) )
    	{
    		GPIOB->BRR	=	( 1 << LD1 );		// Turn it OFF
    	}
    	else
    	{
    		GPIOB->BSRR	=	( 1 << LD1 );		// Turn it ON
    	}

    	/* Clear flag	 */
    	LPTIM1->ICR	|=	 LPTIM_ICR_ARRMCF;
    }
}
