/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_CLK  ( void )
 * @details     It activates the external HFCLK crystal oscillator ( 64MHz ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
  NRF_CLOCK->EVENTS_HFCLKSTARTED  =   0;                                                          // Reset flag
  NRF_CLOCK->TASKS_HFCLKSTART     =   ( CLOCK_HFCLKSTAT_SRC_Xtal << CLOCK_HFCLKSTAT_SRC_Pos );    // Start External crystal CLK

  while ( NRF_CLOCK->EVENTS_HFCLKSTARTED  !=   1 );                                               // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
                                                                                                  // [WORKAROUND] Insert a counter.
}



/**
 * @brief       void conf_LFCLK  ( void )
 * @details     It turns the internal LFCLK clock on for RTCs.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_LFCLK  ( void )
{
  NRF_CLOCK->LFCLKSRC             =   ( CLOCK_LFCLKSRC_SRC_RC << CLOCK_LFCLKSRC_SRC_Pos );
  NRF_CLOCK->EVENTS_LFCLKSTARTED  =   0;
  NRF_CLOCK->TASKS_LFCLKSTART     =   1;

  while ( NRF_CLOCK->EVENTS_LFCLKSTARTED == 0 )       // [TODO] Insert a counter! otherwise if there is a problem it will get block!!!
  {
      //Do nothing.
  }

  NRF_CLOCK->EVENTS_LFCLKSTARTED  =   0;
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
  uint32_t i = 0;

  for ( i = LED1; i < ( LED4 + 1 ); i++ )
  {
    NRF_P0->OUTSET        =   ( 1 << i );

    NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                              ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                              ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                              ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                              ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
  }
}


/**
 * @brief       void conf_Uart0  ( void )
 * @details     Uart0 with the following features:
 *
 *                  * Baud Rate:    115200
 *                  * No Parity.
 *                  * No Flow Control.
 *                  * RX Interrupt ENABLE.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_UART0  ( void )
{
  /* GPIO according to Table 128: GPIO configuration ( Product Specification p.531 ) */
  NRF_P0->OUTSET               =   ( 1 << UART0_TX );
  NRF_P0->DIRCLR               =   ( 1 << UART0_RX );
  NRF_P0->DIRSET               =   ( 1 << UART0_TX );

  /* Stop UART0 */
  NRF_UART0->TASKS_STOPRX      =   1;
  NRF_UART0->TASKS_STOPTX      =   1;

  NRF_UART0->ENABLE            =   UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;

  /* Configure the pins */
  NRF_UART0->PSELRTS           =   0xFFFFFFFF;
  NRF_UART0->PSELCTS           =   0xFFFFFFFF;
  NRF_UART0->PSELTXD           =   UART0_TX;
  NRF_UART0->PSELRXD           =   UART0_RX;

  /* BaudRate & Configuration */
  NRF_UART0->BAUDRATE          =   ( UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos );
  NRF_UART0->CONFIG            =   ( UART_CONFIG_HWFC_Disabled   << UART_CONFIG_HWFC_Pos   ) |
                                   ( UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos );
  /* Configure Interrupts */
  NRF_UART0->INTENSET          =   ( UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos ) |
                                   ( UART_INTENSET_TXDRDY_Enabled << UART_INTENSET_TXDRDY_Pos );

  NVIC_ClearPendingIRQ    ( UART0_IRQn );
  NVIC_SetPriority        ( UART0_IRQn, 0 );                                                              // Maximum priority
  NVIC_EnableIRQ          ( UART0_IRQn );                                                                 // Enable Interrupt for the UART0 in the core.

  /* Enable UART0 */
  NRF_UART0->ENABLE            =   ( UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos );              // UART0 ENABLED
//  NRF_UART0->TASKS_STARTTX     =   1;
//  NRF_UART0->TASKS_STARTRX     =   1;                                                                     // Enable reception
}



/**
 * @brief       void conf_TEMP  ( void )
 * @details     It enables TEMP sensor with interruption enable.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018   The ORIGIN
 * @version     14/July/2018   The ORIGIN   The ORIGIN
 * @pre         Time required for temperature measurement ~ 35us ( Product Specification v1.4. 27 Temperature sensor (TEMP) ).
 * @pre         In order to be accurate, the measurement has to be performed while the HFCLK crystal oscillator is selected as clock
 *              source.
 * @warning     N/A.
 */
void conf_TEMP  ( void )
{
  NRF_TEMP->TASKS_STOP  =   1;
  NRF_TEMP->INTENSET    =   ( TEMP_INTENSET_DATARDY_Enabled << TEMP_INTENSET_DATARDY_Pos );

  NVIC_EnableIRQ ( TEMP_IRQn );                                                                   // Enable Interrupt for the TEMP in the core.
}



/**
 * @brief       void conf_RTC2  ( void )
 * @details     Channel 0 will create an interrupt every 1s.
 *
 *              RTC1:
 *                  * Prescaler:            327   ( f_RTC2 = ( 32.768kHz / ( 327 + 1 ) ) ~ 99.9Hz ( ~10ms ) ).
 *                  * Channel 0:            10ms*100 = 1s
 *                  * Interrupt ENABLE.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_RTC2  ( void )
{
  NRF_RTC2->TASKS_STOP  =   1;
  NRF_RTC2->PRESCALER   =   327;                                                                        // f_RTC2 = ( 32.768kHz / ( 327 + 1 ) ) ~ 99.9Hz ( ~10ms ) ).
  NRF_RTC2->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

  NRF_RTC2->CC[0]       =   100;                                                                        // ( 100 * (f_RTC2)^(-1) ) = ( 100 * (99.9Hz)^(-1) ) ~ 1s

  NRF_RTC2->INTENSET    =   ( RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos );
  NRF_RTC2->EVTENSET    =   ( RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos );

  NVIC_EnableIRQ ( RTC2_IRQn );                                                                         // Enable Interrupt for the RTC2 in the core.
}



/**
 * @brief       void conf_PPI  ( void )
 * @details     It sets up one PPI channel.
 *
 *              Channel 0:
 *                  * Event: NRF_RTC2->EVENTS_COMPARE[0].
 *                  * Task:  NRF_TEMP->TASKS_START.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2017
 * @version     14/July/2017   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_PPI  ( void )
{
    NRF_PPI->CH[0].EEP   =   ( uint32_t )&NRF_RTC2->EVENTS_COMPARE[0];
    NRF_PPI->CH[0].TEP   =   ( uint32_t )&NRF_TEMP->TASKS_START;


    /* Enable PPI channel 0  */
    NRF_PPI->CHEN        =   ( PPI_CHEN_CH0_Enabled << PPI_CHEN_CH0_Pos );
}
