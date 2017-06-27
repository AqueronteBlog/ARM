/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/June/2017
 * @version     26/June/2017   The ORIGIN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void GPIOTE_IRQHandler ()
 * @details     Button 1 generates an interruption on channel 0.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/June/2017
 * @version     26/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void GPIOTE_IRQHandler()
{
    // Channel 0
    if ( ( NRF_GPIOTE->EVENTS_IN[0] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk ) != 0 ) )
    {
        startCycle     =  1;                                // Start a new reading cycle.

        NRF_GPIOTE->EVENTS_IN[0] = 0;                       // Clear ( flag )
    }
}


/**
 * @brief       void UART0_IRQHandler ()
 * @details     It transmits the data through the UART.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/June/2017
 * @version     26/June/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void UART0_IRQHandler(void)
{
    /* Transmission */
    if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
    {
        // Clear UART TX event flag.
        NRF_UART0->EVENTS_TXDRDY = 0;

        // Send only 3-Bytes
        if ( dataToBeTX  < ( sizeof( NRF_FICR->CODESIZE ) - 1 ) )           // sizeof( NRF_FICR->CODESIZE ) - 1 ) = 4 - 1 = 3. NOTE: One byte was just transmitted previously.
        {
        // Transmit data
            myTX             =   ( myTX >> 8 );
            NRF_UART0->TXD   =   ( myTX & 0x000000FF );
            dataToBeTX++;
        }
        else
        {
        // Everything was transmitted, stop the UART and reset variables
            TX_inProgress                =   NO;
            dataToBeTX                   =   0;
            NRF_UART0->TASKS_STOPTX      =   1;
        }
    }
}
