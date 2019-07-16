/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_CLK  ( void )
 * @details     It activates the external HFCLK crystal oscillator ( 64MHz ).
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
  NRF_CLOCK->EVENTS_HFCLKSTARTED  =   0UL;                                                        // Reset flag
  NRF_CLOCK->TASKS_HFCLKSTART     =   ( CLOCK_HFCLKSTAT_SRC_Xtal << CLOCK_HFCLKSTAT_SRC_Pos );    // Start External crystal CLK

  while ( NRF_CLOCK->EVENTS_HFCLKSTARTED  !=   1UL );                                             // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
                                                                                                  // [WORKAROUND] Insert a counter.
  NRF_CLOCK->EVENTS_HFCLKSTARTED   =   0UL;
  
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
  uint32_t i = 0UL;
  
  for ( i = LED1; i < ( LED4 + 1 ); i++ )
  {
    NRF_P0->OUTSET        =   ( 1UL << i );

    NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                              ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                              ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                              ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                              ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
  }
}


/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channel. Channel zero at 1s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt Enabled.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (500kHz)^(-1) ) ~ 1s
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_TIMER0  ( void )
{
  NRF_TIMER0->TASKS_STOP  =   1UL;
  NRF_TIMER0->MODE        =   ( TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos );
  NRF_TIMER0->PRESCALER   =   5UL;                                                                        // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
  NRF_TIMER0->BITMODE     =   ( TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos );               // 32 bit mode.
  NRF_TIMER0->TASKS_CLEAR =   1UL;                                                                        // clear the task first to be usable for later.

  NRF_TIMER0->CC[0]       =   ( 500000 );                                                                 // ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (500kHz)^(-1) ) ~ 1s

  NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );
  
  NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] event.


  NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}
