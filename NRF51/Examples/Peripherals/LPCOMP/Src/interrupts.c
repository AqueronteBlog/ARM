/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/July/2017
 * @version     14/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void LPCOMP_IRQHandler ()
 * @details     [TODO] XXX.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/July/2017
 * @version     14/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void LPCOMP_IRQHandler()
{
    if ( ( NRF_LPCOMP->EVENTS_UP != 0 ) && ( NRF_LPCOMP->INTENSET & LPCOMP_INTENSET_UP_Msk ) )
    {
        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );                   // Turn the LED1 on

        NRF_LPCOMP->EVENTS_UP        =   0;                                 // Clear ( flag )
    }
}

