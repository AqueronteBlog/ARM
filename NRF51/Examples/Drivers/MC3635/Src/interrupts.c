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
 *              One byte was just sent.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/March/2018
 * @version     13/March/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void UART0_IRQHandler(void)
{
    /* Transmission */
    if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
    {
        // Clear UART TX event flag.
        NRF_UART0->EVENTS_TXDRDY = 0;

        // 3-Bytes more have to be sent
        if ( dataToBeTX  < 3 )                      // 1 - 4 = 3. NOTE: One byte was just transmitted previously.
        {
        // Transmit data
            NRF_UART0->TXD   =   *myPtr++;
            dataToBeTX++;
        }
        else
        {
        // Everything was transmitted, stop the UART
            NRF_UART0->TASKS_STOPTX      =   1;
            dataToBeTX                   =   0;
            TX_inProgress                =   NO;
        }
    }
}
