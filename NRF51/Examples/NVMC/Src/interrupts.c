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
 * @pre         The LED1 are connected like Common Anode.
 * @warning     NaN
 */
void RTC0_IRQHandler()
{
    if ( ( NRF_RTC0->EVENTS_TICK != 0 ) && ( ( NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Enabled ) != 0 ) )
    {
        NRF_RTC0->EVENTS_TICK    =   0;                                     // Reset flag

        /*
        // Change state of the LED1
		if ( ( changeLEDsSTATE & ( 1UL << LED1 ) ) == ( 1UL << LED1 ) )
        {
        // Turn off the LED1
            NRF_GPIO->OUTSET =   ( 1UL << LED1 );
            changeLEDsSTATE  &=  ~( 1UL << LED1 );
        }
		else
        {
        // Turn on the LED1
            NRF_GPIO->OUTCLR =  ( 1UL << LED1 );
            changeLEDsSTATE  |=  ( 1UL << LED1 );
        }
        */
    }
}
