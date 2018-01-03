/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/January/2018
 * @version     2/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "interrupts.h"

/**
 * @brief       void TIM5_IRQHandler ()
 * @details     If TIM5 happens, change the status of
 * 				the LED1 then.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version     3/January/2018   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void TIM5_IRQHandler(void)
{
	NUCLEOL152_led_pinout_t    myLED1		= LED_1;


    if ( ( TIM5->SR & TIM_SR_UIF ) == TIM_SR_UIF )
    {
    	// Check last status of the LED1
    	if ( ( GPIOA->ODR & ( 1 << myLED1 ) ) == ( 1 << myLED1 ) )
    		GPIOA->BRR	=	( 1 << myLED1 );							// Turn it OFF
    	else
    		GPIOA->BSRR	=	( 1 << myLED1 );							// Turn it ON

    	TIM5->SR	&=	~TIM_SR_UIF;									// Clear flag
    }
}
