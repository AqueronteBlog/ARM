/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
  if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0UL ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0UL ) )
  {
    myState  =   1UL;


    NRF_TIMER0->EVENTS_COMPARE[0] = 0UL;                    // Clear ( flag ) compare register 0 event
  }
}


/**
 * @brief       void UART0_IRQHandler ()
 * @details     It handles both reading and transmitting data through the UART0.
 *
 *              The reading is just one byte and the transmission finishes when
 *              the character '\n' is found.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void UART0_IRQHandler ( void )
{
  /* Transmission */
  if ( ( NRF_UART0->EVENTS_TXDRDY != 0UL ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
  {
    /* Clear UART TX event flag.    */
    NRF_UART0->EVENTS_TXDRDY   =   0UL;

    /* Stop transmitting data when that character is found */
    if ( *myPtr  == '\n' )
    {
      NRF_UART0->TASKS_STOPTX  =   1UL;
    }
    else
    {
      NRF_UART0->TXD   =   *++myPtr;
    }
  }
}