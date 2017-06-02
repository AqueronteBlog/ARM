/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     2/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void UART0_IRQHandler ()
 * @details     [TODO] Timer interruption. Checks if there is an interruption
 *              of Timer0 and changes the state of the LED1 and LED4.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     2/June/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void UART0_IRQHandler(void)
{
    /* Reception */
    if ( ( NRF_UART0->EVENTS_RXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_RXDRDY_Msk ) )
    {
        NRF_UART0->EVENTS_RXDRDY  = 0;
    }

    /* Transmission */
    if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
    {
        // Clear UART TX event flag.
        NRF_UART0->EVENTS_TXDRDY = 0;
        //on_uart_event(ON_TX_READY);
    }
}
