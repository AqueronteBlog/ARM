/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/July/2018
 * @version     6/July/2018   The ORIGIN
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
 * @date        6/July/2018
 * @version     6/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void UART0_IRQHandler(void)
{
  /* Transmission */
  if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) != 0 )
  {
    // Clear UART TX event flag.
    NRF_UART0->EVENTS_TXDRDY = 0;

    // Stop transmitting data when that character is found
    if ( *myPtr  == '\n' )
    {
      NRF_UART0->TASKS_STOPTX      =   1;
    }
    else
    {
      NRF_UART0->TXD   =   *++myPtr;
    }
  }
}



/**
 * @brief       void TEMP_IRQHandler ()
 * @details     Temperature measurement complete, data ready.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/July/2018
 * @version     6/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void TEMP_IRQHandler()
{
  if ( NRF_TEMP->EVENTS_DATARDY != 0 )
  {
    myTEMPFlag                   =   1;

    myTEMP                       =   NRF_TEMP->TEMP;                    // Read raw temperature
    
    NRF_TEMP->EVENTS_DATARDY     =   0;                                 // Clear ( flag )
  }
}



/**
 * @brief       void RTC2_IRQHandler ()
 * @details     RTC2 interruption.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/July/2018
 * @version     6/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void RTC2_IRQHandler()
{
  if ( ( NRF_RTC2->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_RTC2->INTENSET & RTC_INTENSET_COMPARE0_Msk ) != 0 ) )
  {
      myState                      =   1;               // Change the variable

      NRF_RTC2->CC[0]             +=   100;             // New interruption on 1s
      NRF_RTC2->EVENTS_COMPARE[0]  =   0;               // Clear ( flag ) compare register 0 event
  }
}