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
 * @details     [todo] It handles both reading and transmitting data through the UART.
 *
 *              The reading is just one byte and the transmission finishes when
 *              the character '\n' is found.
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


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     [todo] Timer interruption. Checks if there is an interruption
 *              of Timer0 and changes the state of the LED1 and LED4.
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
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        /*
		if ( ( changeLEDsSTATE & ( 1UL << LED1 ) ) == ( 1UL << LED1 ) )
        {
        // Turn off the LED1
            NRF_GPIO->OUTSET =   ( 1UL << LED1 );
            changeLEDsSTATE  &=  ~( 1UL << LED1 );
        }
		else
        {
        // Turn on the LED1
            NRF_GPIO->OUTCLR =  ( 1UL << LED1 );
            changeLEDsSTATE  |=  ( 1UL << LED1 );
        }
        */

        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event
    }
}
