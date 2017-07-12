/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/July/2017
 * @version     12/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void RTC0_IRQHandler ()
 * @details     [todo] RTC0 interruption. xxx.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/July/2017
 * @version     12/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void RTC0_IRQHandler()
{
    if ( ( NRF_RTC0->EVENTS_TICK != 0 ) && ( ( NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Enabled ) != 0 ) )
    {
        writeNVMC                =   YES;

        NRF_RTC0->EVENTS_TICK    =   0;         // Reset flag
    }
}
