/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interruption
 *              of Timer0 and it changes the state of changeDP_status
 *              variable every ~ 1s.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        9/October/2017
 * @version     9/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
		NRF_GPIO->OUTCLR =  ( 1UL << LED1 );


        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event

        // New order to change the DP status
        if ( changeDP_status == ON )
        {
            changeDP_status  =   OFF;
        }
        else
        {
            changeDP_status  =   ON;
        }
    }
}
