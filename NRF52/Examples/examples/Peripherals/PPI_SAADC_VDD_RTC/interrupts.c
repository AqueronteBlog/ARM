/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void RTC2_IRQHandler ()
 * @details     RTC2 interruption. Checks if there is an interruption
 *              of RTC2 on channel 0.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void RTC2_IRQHandler()
{
  if ( ( NRF_RTC2->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_RTC2->INTENSET & RTC_INTENSET_COMPARE0_Msk ) != 0 ) )
  {
    /* Enable SAADC   */
    NRF_SAADC->ENABLE  =   ( SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos );


    NRF_RTC2->CC[0]             +=   200;             // New interruption on 2s
    NRF_RTC2->EVENTS_COMPARE[0]  =   0;               // Clear ( flag ) compare register 0 event
  }
}



/**
 * @brief       void SAADC_IRQHandler ()
 * @details     SAADC interruption. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void SAADC_IRQHandler()
{
  /* STARTED event  */
  if ( ( NRF_SAADC->EVENTS_STARTED != 0UL ) && ( ( NRF_SAADC->INTENSET & SAADC_INTENSET_STARTED_Msk ) != 0UL ) )
  {
    /* Do a SAADC sample, will put the result in the configured RAM buffer   */
    NRF_SAADC->TASKS_SAMPLE  =   1UL;


    NRF_SAADC->EVENTS_STARTED = 0UL;             // Clear ( flag )
  }
  
  /* END event   */
  if ( ( NRF_SAADC->EVENTS_END != 0UL ) && ( ( NRF_SAADC->INTENSET & SAADC_INTENSET_END_Msk ) != 0UL ) )
  {
    if ( ( NRF_SAADC->RESULT.AMOUNT & SAADC_RESULT_AMOUNT_AMOUNT_Msk ) != 0 )
    {
      myADCDoneFlag  =   1UL;
    }


    NRF_SAADC->EVENTS_END = 0UL;                 // Clear ( flag )
  }

  /* STOPPED event  */
  if ( ( NRF_SAADC->EVENTS_STOPPED != 0UL ) && ( ( NRF_SAADC->INTENSET & SAADC_INTENSET_STOPPED_Msk ) != 0UL ) )
  {
    /* Disable SAADC   */
    NRF_SAADC->ENABLE  =   ( SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos );


    NRF_SAADC->EVENTS_STOPPED = 0UL;             // Clear ( flag )
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
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
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