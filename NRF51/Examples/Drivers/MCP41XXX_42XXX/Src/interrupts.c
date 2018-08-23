/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/August/2018
 * @version     21/August/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"

/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interrupt.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/August/2018
 * @version     21/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0UL ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0UL ) )
    {
        myState  =   1UL;

        NRF_TIMER0->EVENTS_COMPARE[0] = 0UL;                  // Clear ( flag ) compare register 0 event
    }
}
