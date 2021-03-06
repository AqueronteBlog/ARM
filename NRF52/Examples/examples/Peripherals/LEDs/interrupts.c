/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/February/2018
 * @version     12/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interruption
 *              of Timer0 and changes the state of the LEDs.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/February/2018
 * @version     12/February/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
	if ( changeLEDsSTATE == ON )
        {
        // Turn off all the LEDs
            NRF_P0->OUTSET |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );
            changeLEDsSTATE   =  OFF;
        }
	else
        {
        // Turn on all the LEDs
            NRF_P0->OUTCLR |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );
            changeLEDsSTATE   =  ON;
        }

        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event
    }
}
