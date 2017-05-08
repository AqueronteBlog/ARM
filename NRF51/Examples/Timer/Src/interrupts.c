/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     5/May/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interruption
 *              of Timer0 and changes the state of the LEDs.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     5/May/2017   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     NaN
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
		if ( ( changeLEDsSTATE & ( 1 << LED1 ) ) == ( 1 << LED1 ) )
        {
        // Turn off all the LEDs
            NRF_GPIO->OUTSET |=   ( 1 << LED1 );
            changeLEDsSTATE  &=  ~( 1 << LED1 );
        }
		else
        {
        // Turn on all the LEDs
            NRF_GPIO->OUTCLR |=  ( 1 << LED1 );
            changeLEDsSTATE  |=  ( 1 << LED1 );
        }

        NRF_TIMER0->CC[0]       +=   125001;
        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event
    }
    if ( ( NRF_TIMER0->EVENTS_COMPARE[1] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE1_Msk ) != 0 ) )
    {
		if ( ( changeLEDsSTATE & ( 1 << LED4 ) ) == ( 1 << LED4 ) )
        {
        // Turn off all the LEDs
            NRF_GPIO->OUTSET |=   ( 1 << LED4 );
            changeLEDsSTATE  &=  ~( 1 << LED4 );
        }
		else
        {
        // Turn on all the LEDs
            NRF_GPIO->OUTCLR |= ( 1 << LED4 );
            changeLEDsSTATE  |= ( 1 << LED4 );
        }

        NRF_TIMER0->CC[1]       +=   4*125000;
        NRF_TIMER0->EVENTS_COMPARE[1] = 0;                      // Clear ( flag ) compare register 0 event
    }
}
