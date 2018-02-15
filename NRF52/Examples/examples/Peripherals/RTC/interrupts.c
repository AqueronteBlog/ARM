/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interrupt
 *              of Timer0 and changes the state of the LED1 and LED4.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        if ( ( changeLEDsSTATE & ( 1UL << LED1 ) ) == ( 1UL << LED1 ) )
        {
        // Turn off the LED1
            NRF_P0->OUTSET =   ( 1UL << LED1 );
            changeLEDsSTATE  &=  ~( 1UL << LED1 );
        }
        else
        {
        // Turn on the LED1
            NRF_P0->OUTCLR =  ( 1UL << LED1 );
            changeLEDsSTATE  |=  ( 1UL << LED1 );
        }

        NRF_TIMER0->CC[0]       +=   62500;
        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event
    }
    if ( ( NRF_TIMER0->EVENTS_COMPARE[1] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE1_Msk ) != 0 ) )
    {
	if ( ( changeLEDsSTATE & ( 1UL << LED4 ) ) == ( 1UL << LED4 ) )
        {
        // Turn off the LED4
            NRF_P0->OUTSET =   ( 1UL << LED4 );
            changeLEDsSTATE  &=  ~( 1UL << LED4 );
        }
	else
        {
        // Turn on the LED4
            NRF_P0->OUTCLR = ( 1UL << LED4 );
            changeLEDsSTATE  |= ( 1UL << LED4 );
        }

        NRF_TIMER0->CC[1]       +=   4*62500;
        NRF_TIMER0->EVENTS_COMPARE[1] = 0;                      // Clear ( flag ) compare register 0 event
    }
}




/**
 * @brief       void TIMER2_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interrupt
 *              of Timer2 and changes the state of the LED3 every 1477 * 254us ~ 0.375s
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     N/A
 */
void TIMER2_IRQHandler()
{
    if ( ( NRF_TIMER2->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        if ( my375msDelay < 1477 )
            my375msDelay++;
        else{
            if ( ( changeLEDsSTATE & ( 1UL << LED3 ) ) == ( 1UL << LED3 ) )
            {
            // Turn off the LED3
                NRF_P0->OUTSET =   ( 1UL << LED3 );
                changeLEDsSTATE  &=  ~( 1UL << LED3 );
            }
            else
            {
            // Turn on the LED3
                NRF_P0->OUTCLR =  ( 1UL << LED3 );
                changeLEDsSTATE  |=  ( 1UL << LED3 );
            }

            my375msDelay     =   0;                      // Reset counter
        }

        NRF_TIMER2->EVENTS_COMPARE[0] = 0;               // Clear ( flag ) compare register 0 event
    }
}
