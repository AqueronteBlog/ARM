/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/October/2019
 * @version     01/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "interrupts.h"


/**
 * @brief       void TIM2_IRQHandler ()
 * @details     If TIM2 happens, change the status of the LED1 then.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/October/2019
 * @version     01/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void TIM2_IRQHandler(void)
{
	if ( ( TIM2->SR & TIM_SR_UIF_Msk ) == TIM_SR_UIF )
    {
    	/* Check last status of the LED1	 */
    	if ( ( GPIOA->ODR & ( 1 << LD1 ) ) == ( 1 << LD1 ) )
    		GPIOA->BRR	=	( 1 << LD1 );							// Turn it OFF
    	else
    		GPIOA->BSRR	=	( 1 << LD1 );							// Turn it ON

    	/* Clear flag	 */
    	TIM2->SR	&=	~TIM_SR_UIF;
    }
}
