/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        21/June/2017
 * @version     21/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void UART0_IRQHandler ()
 * @details     It handles both reading and transmitting data through the UART.
 *
 *              The reading is just one byte and the transmission is one byte too.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        21/June/2017
 * @version     21/June/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void UART0_IRQHandler(void)
{
    /* Reception */
    if ( ( NRF_UART0->EVENTS_RXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_RXDRDY_Msk ) )
    {
        NRF_UART0->EVENTS_RXDRDY  = 0;
        myRX_buff = ( uint8_t )( NRF_UART0->RXD & 0xFF );
    }

    /* Transmission */
    if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
    {
        // Clear UART TX event flag.
        NRF_UART0->EVENTS_TXDRDY =   0;

        NRF_UART0->TASKS_STOPTX  =   1;
        TX_inProgress            =   NO;
    }
}
