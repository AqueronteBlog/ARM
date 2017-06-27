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
 * @brief       void SPI0_IRQHandler ()
 * @details     [TODO] XXX.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     NaN
 */
void SPI0_IRQHandler()
{
    /*
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
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

        NRF_TIMER0->CC[0]       +=   125000;
        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event
    }
    */
}




/**
 * @brief       void SPIS1_IRQHandler ()
 * @details     [TODO] XXX
 *
 *
 * @return      NaN
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     NaN
 */
void SPIS1_IRQHandler()
{
    /*
    if ( ( NRF_TIMER2->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        if ( my375msDelay < 1470 )
            my375msDelay++;
        else{
            if ( ( changeLEDsSTATE & ( 1UL << LED3 ) ) == ( 1UL << LED3 ) )
            {
            // Turn off the LED3
                NRF_GPIO->OUTSET =   ( 1UL << LED3 );
                changeLEDsSTATE  &=  ~( 1UL << LED3 );
            }
            else
            {
            // Turn on the LED3
                NRF_GPIO->OUTCLR =  ( 1UL << LED3 );
                changeLEDsSTATE  |=  ( 1UL << LED3 );
            }

            my375msDelay     =   0;                      // Reset counter
        }

        NRF_TIMER2->EVENTS_COMPARE[0] = 0;               // Clear ( flag ) compare register 0 event
    }
    */
}
