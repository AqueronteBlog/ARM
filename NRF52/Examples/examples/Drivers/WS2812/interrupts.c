/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
  if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0UL ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0UL ) )
  {
    myState  =   1UL;


    NRF_TIMER0->EVENTS_COMPARE[0] = 0UL;                    // Clear ( flag ) compare register 0 event
  }
}
