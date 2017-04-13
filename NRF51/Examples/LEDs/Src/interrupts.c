#include "interrupts.h"


void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
		NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear compare register 0 event

		if ( changeLEDsSTATE == ON )
        {
            NRF_GPIO->OUTSET |= ( LED1 | LED2 | LED3 | LED4 );
            changeLEDsSTATE   =  OFF;
        }
		else
        {
            NRF_GPIO->OUTCLR |= ( LED1 | LED2 | LED3 | LED4 );
            changeLEDsSTATE   =  ON;
        }
    }
}
