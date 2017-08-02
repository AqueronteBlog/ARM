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
 * @date        22/June/2017
 * @version     22/June/2017   The ORIGIN
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

        // Evaluate the data
        if ( myRX_buff   ==  'm' )
        {
        // Random number request
            NRF_UART0->TASKS_STOPRX =   1;                          // Stop RX, it will be available again when the process is completed
            NRF_GPIO->OUTCLR        =   ( 1 << LED1 );              // Turn the LED1 on
            NRF_RNG->TASKS_START    =   1;                          // Start RNG
        }
    }

    /* Transmission */
    if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
    {
        // Clear UART TX event flag.
        NRF_UART0->EVENTS_TXDRDY =   0;

        // Data sent, restore parameters
        NRF_UART0->TASKS_STOPTX  =   1;
        NRF_UART0->TASKS_STARTRX =   1;
        NRF_GPIO->OUTSET         =   ( 1 << LED1 );
    }
}


/**
 * @brief       void RNG_IRQHandler ()
 * @details     It gets the random number and starts sending
 *              it through the UART.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/June/2017
 * @version     22/June/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void RNG_IRQHandler(void)
{
    if ( ( NRF_RNG->EVENTS_VALRDY != 0 ) && ( NRF_RNG->INTENSET & RNG_INTENSET_VALRDY_Msk ) )
    {
        NRF_RNG->EVENTS_VALRDY       =   0;

        myRandomNumber = NRF_RNG->VALUE;

        // Sent the data through the UART
        NRF_UART0->TASKS_STARTTX     =   1;
        NRF_UART0->TXD               =   myRandomNumber;
    }
}

