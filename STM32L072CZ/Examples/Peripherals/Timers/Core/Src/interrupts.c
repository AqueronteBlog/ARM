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
 * @version     03/October/2019   LED1 is on port B instead of port A.
 * 				01/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void TIM2_IRQHandler(void)
{
	if ( ( TIM2->SR & TIM_SR_UIF_Msk ) == TIM_SR_UIF )
    {
    	/* Check last status of the LED1	 */
    	if ( ( GPIOB->ODR & ( 1 << LD1 ) ) == ( 1 << LD1 ) )
    		GPIOB->BRR	=	( 1 << LD1 );							// Turn it OFF
    	else
    		GPIOB->BSRR	=	( 1 << LD1 );							// Turn it ON

    	/* Clear flag	 */
    	TIM2->SR	&=	~TIM_SR_UIF;
    }
}



/**
 * @brief       void TIM6_IRQHandler ()
 * @details     If TIM6 happens, change the status of the LED2 then.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/October/2019
 * @version     03/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void TIM6_IRQHandler(void)
{
	if ( ( TIM6->SR & TIM_SR_UIF_Msk ) == TIM_SR_UIF )
    {
    	/* Check last status of the LED2	 */
    	if ( ( GPIOA->ODR & ( 1 << LD2 ) ) == ( 1 << LD2 ) )
    		GPIOA->BRR	=	( 1 << LD2 );							// Turn it OFF
    	else
    		GPIOA->BSRR	=	( 1 << LD2 );							// Turn it ON

    	/* Clear flag	 */
    	TIM6->SR	&=	~TIM_SR_UIF;
    }
}
