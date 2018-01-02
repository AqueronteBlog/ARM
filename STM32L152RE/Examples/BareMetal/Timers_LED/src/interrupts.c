/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "interrupts.h"

/**
 * @brief       void EXTI15_10_IRQHandler ()
 * @details     If EXTI13 happens, change the status of
 * 				the LED1 then.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        30/December/2017
 * @version     30/December/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void EXTI15_10_IRQHandler(void)
{
	NUCLEOL152_button_pinout_t myUserButton = BUTTON_1;
	NUCLEOL152_led_pinout_t    myLED1		= LED_1;


	// EXTI13
    if( ( EXTI->IMR & ( 1 << myUserButton ) ) && ( EXTI->PR & ( 1 << myUserButton ) ) )
    {
    	// Check last status of the LED1
    	if ( ( GPIOA->ODR & ( 1 << myLED1 ) ) == ( 1 << myLED1 ) )
    		GPIOA->BRR	=	( 1 << myLED1 );							// Turn it OFF
    	else
    		GPIOA->BSRR	=	( 1 << myLED1 );							// Turn it ON

    	EXTI->PR	|=	 EXTI_PR_PR13 ;
    }
}
