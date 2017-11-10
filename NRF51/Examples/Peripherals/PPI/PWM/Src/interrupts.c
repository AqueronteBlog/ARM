/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        9/November/2017
 * @version     9/November/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. [todo].
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        10/November/2017
 * @version     10/November/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
/*
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        NRF_TIMER0->CC[0]       +=   500;
        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event
    }
    if ( ( NRF_TIMER0->EVENTS_COMPARE[1] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE1_Msk ) != 0 ) )
    {
    }
}
*/
