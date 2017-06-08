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
 * @details     [todo] Timer interruption. Checks if there is an interruption
 *              of Timer0 and changes the state of the LED1 and LED4.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
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
 * @details     [todo] Timer interruption. Checks if there is an interruption
 *              of Timer2 and changes the state of the LED3 every 1470 * 255us ~ 0.375s
 *
 *
 * @return      NaN
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
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

        NRF_RTC1->CC[0]      +=   200;
        NRF_RTC1->EVENTS_COMPARE[0] = 0;               // Clear ( flag ) compare register 0 event
    }
}
