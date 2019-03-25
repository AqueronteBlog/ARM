/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void UART0_IRQHandler ()
 * @details     It handles both reading and transmitting data through the UART0.
 *
 *              The reading is just one byte and the transmission finishes when
 *              the character '\n' is found.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
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
        NRF_UART0->EVENTS_TXDRDY = 0;

        // Stop transmitting data when that character is found
        if ( *myPtr  == '\n' )
        {
            NRF_UART0->TASKS_STOPTX      =   1;
            TX_inProgress                =   NO;
        }
        else
        {
            NRF_UART0->TXD   =   *++myPtr;
        }
    }
}