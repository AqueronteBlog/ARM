/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        30/June/2017
 * @version     30/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void UART0_IRQHandler ()
 * @details     [todo] It sends the temperature through the UART.
 *
 *              One byte was just sent, so there are 3-Bytes left
 *              waiting to be transmitted.
 *
 *              The LED1 will be turned off to indicate that the whole
 *              process ( Read temperature + transmission ) was completed.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        20/June/2017
 * @version     20/June/2017   The ORIGIN
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
        if ( dataToBeTX  < ( sizeof( NRF_TEMP->TEMP ) - 1 ) )           // sizeof( NRF_TEMP->TEMP ) - 1 ) = 4 - 1 = 3. NOTE: One byte was just transmitted previously.
        {
        // Transmit data
            myTEMP           =   ( myTEMP >> 8 );
            NRF_UART0->TXD   =   ( myTEMP & 0x000000FF );
            dataToBeTX++;
        }
        else
        {
        // Everything was transmitted, stop the UART and turn the LED1 off
            NRF_UART0->TASKS_STOPTX      =   1;
            NRF_GPIO->OUTSET             =   ( 1UL << LED1 );
        }
    }
}


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     [todo] It starts a new conversion ( internal temperature ) every
 *              1 second.
 *
 *              Turn the LED1 on to indicate that the process has just been started.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        20/June/2017
 * @version     20/June/2017   The ORIGIN
 * @pre         The LED1 will be turned off again when the process is finished.
 * @warning     NaN
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        NRF_GPIO->OUTCLR         =   ( 1UL << LED1 );       // Turn the LED1 on
        NRF_TEMP->TASKS_START    =   1;                     // Start another temperature measurement ( one-shot )


        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                  // Clear ( flag ) compare register 0 event
    }
}
