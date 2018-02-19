/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/February/2018
 * @version     19/February/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"

/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     There is a new interrupt every 1s, increment the myState variable
 *              so in the main can process that information.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/February/2018
 * @version     13/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        mySTATE  =   1;

        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                  // Clear ( flag ) compare register 0 event
    }
}



/**
 * @brief       void UART0_IRQHandler ()
 * @details     It sends the collected data from the external sensor through the UART.
 *
 *              One byte was just sent, so there are 1-Byte left
 *              waiting to be transmitted.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/February/2018
 * @version     13/February/2018   The ORIGIN
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
