/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void RTC0_IRQHandler ()
 * @details     RTC0 interruption. Checks if there is an interruption
 *              of RTC0 and changes the state of the LED1 every ~ 125ms.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017   The ORIGIN
 * @pre         The LED1 are connected like Common Anode.
 * @warning     NaN
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
            NRF_GPIO->OUTSET =   ( 1UL << LED1 );
            changeLEDsSTATE  &=  ~( 1UL << LED1 );
        }
		else
        {
        // Turn on the LED1
            NRF_GPIO->OUTCLR =  ( 1UL << LED1 );
            changeLEDsSTATE  |=  ( 1UL << LED1 );
        }
    }
}




/**
 * @brief       void RTC1_IRQHandler ()
 * @details     RTC1 interruption. Checks if there is an interruption
 *              of RTC1 and changes the state of the LED4 every ~ 2s.
 *
 *
 * @return      NaN
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017   The ORIGIN
 * @pre         The LED4 is connected like Common Anode.
 * @warning     NaN
 */
void RTC1_IRQHandler()
{
    if ( ( NRF_RTC1->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_RTC1->INTENSET & RTC_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        if ( ( changeLEDsSTATE & ( 1UL << LED4 ) ) == ( 1UL << LED4 ) )
        {
        // Turn off the LED4
            NRF_GPIO->OUTSET =   ( 1UL << LED4 );
            changeLEDsSTATE  &=  ~( 1UL << LED4 );
        }
        else
        {
        // Turn on the LED4
            NRF_GPIO->OUTCLR  =  ( 1UL << LED4 );
            changeLEDsSTATE  |=  ( 1UL << LED4 );
        }

        NRF_RTC1->CC[0]             +=   200;             // New interruption on 2s
        NRF_RTC1->EVENTS_COMPARE[0]  =   0;               // Clear ( flag ) compare register 0 event
    }
}
