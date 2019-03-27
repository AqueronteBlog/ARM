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
void UARTE0_UART0_IRQHandler ( void )
{
  /* Reception */
  if ( ( NRF_UARTE0->EVENTS_ENDRX != 0 ) && ( NRF_UARTE0->INTENSET & UARTE_INTENSET_ENDRX_Msk ) )
  {
      NRF_UARTE0->EVENTS_RXDRDY  = 0;
  }

  /* Transmission */
  if ( ( NRF_UARTE0->EVENTS_ENDTX != 0 ) && ( NRF_UARTE0->INTENSET & UARTE_INTENSET_ENDTX_Msk ) )
  {
    TX_inProgress  =   NO;
    
    // Clear UARTE TX event flag.
    NRF_UARTE0->EVENTS_TXDRDY = 0;
  }
}