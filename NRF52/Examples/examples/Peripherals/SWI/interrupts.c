/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void RTC0_IRQHandler ()
 * @details     RTC0 interruption. Checks if there is an interruption
 *              of RTC0 and changes the state of the LED1 every ~ 125ms.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void RTC0_IRQHandler()
{
    if ( ( NRF_RTC0->EVENTS_TICK != 0 ) && ( ( NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Enabled ) != 0 ) )
    {
        NRF_RTC0->EVENTS_TICK    =   0;                                     // Reset flag

        // Change state of the LED1
	if ( ( changeLEDsSTATE & ( 1UL << LED1 ) ) == ( 1UL << LED1 ) )
        {
        // Turn off the LED1
            NRF_P0->OUTSET    =   ( 1UL << LED1 );
            changeLEDsSTATE  &=  ~( 1UL << LED1 );
        }
	else
        {
        // Turn on the LED1
            NRF_P0->OUTCLR    =  ( 1UL << LED1 );
            changeLEDsSTATE  |=  ( 1UL << LED1 );
        }
    }
}
