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
 * @brief       void ADC_IRQHandler ()
 * @details     ADC measurement is completed, data ready.
 *
 *              Start transmitting the data through the UART.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/July/2017
 * @version     11/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void ADC_IRQHandler()
{
    if ( ( NRF_ADC->EVENTS_END != 0 ) && ( NRF_ADC->BUSY == 0 ) )
    {
        myADCvalue                   =   ( NRF_ADC->RESULT & 0x000000FF);   // Read raw ADC

        NRF_ADC->EVENTS_END          =   0;                                 // Clear ( flag )
    }
}

