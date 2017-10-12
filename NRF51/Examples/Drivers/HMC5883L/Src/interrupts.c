/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     22/September/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"

/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     There is a new interrupt every 0.5s, change the myState variable
 *              so in the main can process that information.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        // Change the state of myState
        if ( mySTATE == 1 )
            mySTATE  =   0;
        else
            mySTATE  =   1;


        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                  // Clear ( flag ) compare register 0 event
    }
}



/**
 * @brief       void GPIOTE_IRQHandler ()
 * @details     It changes the state of the variable so in the main can process
 *              that information.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void GPIOTE_IRQHandler()
{
    // Channel 0
    if ( ( NRF_GPIOTE->EVENTS_IN[0] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk ) != 0 ) )
    {
		myPCF8574INT  =   1;


        NRF_GPIOTE->EVENTS_IN[0] = 0;                      // Clear ( flag )
    }
}
