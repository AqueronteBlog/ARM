/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     23/May/2017   Timer2 interrupt added.
 *              5/May/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interruption
 *              of Timer0 and changes the state of the LED1 and LED4.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     5/May/2017   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     NaN
 */
void TIMER0_IRQHandler()
{
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
    if ( ( NRF_TIMER0->EVENTS_COMPARE[1] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE1_Msk ) != 0 ) )
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
            NRF_GPIO->OUTCLR = ( 1UL << LED4 );
            changeLEDsSTATE  |= ( 1UL << LED4 );
        }

        NRF_TIMER0->CC[1]       +=   4*125000;
        NRF_TIMER0->EVENTS_COMPARE[1] = 0;                      // Clear ( flag ) compare register 0 event
    }
}




/**
 * @brief       void TIMER2_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interruption
 *              of Timer2 and changes the state of the LED3 every 1470 * 255us ~ 0.375s
 *
 *
 * @return      NaN
 *
 * @author      Manuel Caballero
 * @date        23/May/2017
 * @version     23/May/2017   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     NaN
 */
void TIMER2_IRQHandler()
{
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
}
