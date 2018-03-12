/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"

/**
 * @brief       void UART0_IRQHandler ()
 * @details     It sends the collected data from the external sensor through the UART.
 *
 *              One byte was just sent, so there are 1-Byte left
 *              waiting to be transmitted.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        25/January/2018
 * @version     25/January/2018   The ORIGIN
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

        // Send only 11-Bytes
        if ( dataToBeTX  < 1 )           // 2 - 1 = 1. NOTE: One byte was just transmitted previously.
        {
        // Transmit data
            NRF_UART0->TXD   =   *myPtr++;
            dataToBeTX++;
        }
        else
        {
        // Everything was transmitted, stop the UART and turn the LED1 off
            NRF_UART0->TASKS_STOPTX      =   1;
            dataToBeTX                   =   0;
            TX_inProgress                =   NO;
        }
    }
}


/**
 * @brief       void GPIOTE_IRQHandler ()
 * @details     [todo].
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/March/2018
 * @version     12/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void GPIOTE_IRQHandler()
{
    // Channel 0
    if ( ( NRF_GPIOTE->EVENTS_IN[0] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk ) != 0 ) )
    {
        mySTATE                  = 1;
        NRF_GPIOTE->EVENTS_IN[0] = 0;                      // Clear ( flag )
    }
}
