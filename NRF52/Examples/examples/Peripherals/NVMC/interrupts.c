/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/April/2018
 * @version     16/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void RTC0_IRQHandler ()
 * @details     RTC0 interruption. Every 125ms, it allows a new operation.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/April/2018
 * @version     16/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void RTC0_IRQHandler()
{
    if ( ( NRF_RTC0->EVENTS_TICK != 0 ) && ( ( NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Enabled ) != 0 ) )
    {
        writeNVMC                =   YES;

        NRF_RTC0->EVENTS_TICK    =   0;         // Reset flag
    }
}