/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_LFCLK  ( void )
 * @details     It turns the internal LFCLK clock on for RTCs.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_LFCLK  ( void )
{
  NRF_CLOCK->LFCLKSRC             =   ( CLOCK_LFCLKSRC_SRC_RC << CLOCK_LFCLKSRC_SRC_Pos );
  NRF_CLOCK->EVENTS_LFCLKSTARTED  =   0UL;
  NRF_CLOCK->TASKS_LFCLKSTART     =   1UL;

  while ( NRF_CLOCK->EVENTS_LFCLKSTARTED == 0UL )       // [TODO] Insert a counter! otherwise if there is a problem it will get block!!!
  {
    //Do nothing.
  }

  NRF_CLOCK->EVENTS_LFCLKSTARTED  =   0UL;
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
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN   
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
 * @brief       void conf_PPI  ( void )
 * @details     It interconnects NRF_TIMER0->EVENTS_COMPARE[0] with NRF_SAADC->TASKS_START.
 *
 *              Channel 0:
 *                  * Event: NRF_RTC2->EVENTS_COMPARE[0].
 *                  * Task:  NRF_SAADC->TASKS_START.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_PPI  ( void )
{
  NRF_PPI->CH[0].EEP   =   ( uint32_t )&NRF_RTC2->EVENTS_COMPARE[0];
  NRF_PPI->CH[0].TEP   =   ( uint32_t )&NRF_SAADC->TASKS_START;

  /* Enable PPI channel 0  */
  NRF_PPI->CHEN        =   ( PPI_CHEN_CH0_Enabled << PPI_CHEN_CH0_Pos );
}



/**
 * @brief       void conf_SAADC  ( uint32_t* )
 * @details     It configures SAADC.
 *
 *              Channel 0:
 *                - VDD
 *                - One-shot mode
 *                - Gain: 1/6
 *                - Internal reference
 *                - Resolution: 8-bit
 *
 * @param[in]    myADC_Result: Data RAM region.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_SAADC  ( volatile int16_t* myADC_Result )
{
  /* Disable SAADC   */
  NRF_SAADC->ENABLE  =   ( SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos );

  /* PSELP: ch0 -> VDD   */
  NRF_SAADC->CH[0].PSELP   =   ( SAADC_CH_PSELP_PSELP_VDD << SAADC_CH_PSELP_PSELP_Pos );

  /* PSELN: In single-ended mode, the negative input will be shorted to ground internally   */
//  NRF_SAADC->CH[0].PSELN   =   ( SAADC_CH_PSELN_PSELN_NC << SAADC_CH_PSELN_PSELN_Pos );

  /* Positive channel resistor control: bypass
     Negative channel resistor control: bypass
     Gain:                              1/6
     Reference control:                 Internal ( ~0.6V )
     Acquisition time:                  ~3us
     Mode:                              Single ended ( PSELN will be ignored, negative input to ADC shorted to GND )
     Burst mode:                        Disabled ( normal operation )
  */
  NRF_SAADC->CH[0].CONFIG  =   ( SAADC_CH_CONFIG_RESP_Bypass      << SAADC_CH_CONFIG_RESP_Pos   ) |
                               ( SAADC_CH_CONFIG_RESN_Bypass      << SAADC_CH_CONFIG_RESN_Pos   ) |
                               ( SAADC_CH_CONFIG_GAIN_Gain1_6     << SAADC_CH_CONFIG_GAIN_Pos   ) |
                               ( SAADC_CH_CONFIG_REFSEL_Internal  << SAADC_CH_CONFIG_REFSEL_Pos ) |
                               ( SAADC_CH_CONFIG_TACQ_3us         << SAADC_CH_CONFIG_TACQ_Pos   ) |
                               ( SAADC_CH_CONFIG_MODE_SE          << SAADC_CH_CONFIG_MODE_Pos   ) |
                               ( SAADC_CH_CONFIG_BURST_Disabled   << SAADC_CH_CONFIG_BURST_Pos  );
  

  /* RESOLUTION: 8-bits  */
  NRF_SAADC->RESOLUTION  =   ( SAADC_RESOLUTION_VAL_8bit << SAADC_RESOLUTION_VAL_Pos );

  /* SAMPLING MODE: Triggering TASKS_SAMPLE ( not continuous mode )   */
  NRF_SAADC->SAMPLERATE  =   ( SAADC_SAMPLERATE_MODE_Task << SAADC_SAMPLERATE_MODE_Pos );

  /* NUMBER OF CHANNELS ENABLED: Just one channel ( ch0 -> VDD )  */
  NRF_SAADC->RESULT.MAXCNT   =   ( ( 1UL & SAADC_RESULT_MAXCNT_MAXCNT_Msk ) << SAADC_RESULT_MAXCNT_MAXCNT_Pos );

  /* DATA POINTER  */
  NRF_SAADC->RESULT.PTR  =   (uint32_t)myADC_Result;
  
  /* Enable SAADC   */
  NRF_SAADC->ENABLE  =   ( SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos );

  /* CALIBRATION: Calibrate the SAADC ( only needs to be done once in a while )   */
  NRF_SAADC->TASKS_CALIBRATEOFFSET =   1UL;
  while ( NRF_SAADC->EVENTS_CALIBRATEDONE == 0UL );   // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
                                                      // [WORKAROUND] Insert a counter.
  NRF_SAADC->EVENTS_CALIBRATEDONE  =   0UL; 

  /* Disable SAADC   */
  NRF_SAADC->ENABLE  =   ( SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos );
  
  /* Enable interrupts   */
  NRF_SAADC->INTENSET   =   ( SAADC_INTENSET_STARTED_Set << SAADC_INTENSET_STARTED_Pos ) |
                            ( SAADC_INTENSET_STOPPED_Set << SAADC_INTENSET_STOPPED_Pos ) |
                            ( SAADC_INTENSET_END_Set     << SAADC_INTENSET_END_Pos     );        

  NVIC_EnableIRQ ( SAADC_IRQn );                      // Enable Interrupt for the SAADC in the core.
}



/**
 * @brief       void conf_RTC2  ( void )
 * @details     Channel 0 will create an interrupt every 2s.
 *
 *              RTC1:
 *                  * Prescaler:            327   ( f_RTC2 = ( 32.768kHz / ( 327 + 1 ) ) ~ 99.9Hz ( ~10ms ) ).
 *                  * Channel 0:            10ms*200 = 2s
 *                  * Interrupt ENABLE.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_RTC2  ( void )
{
  NRF_RTC2->TASKS_STOP  =   1;
  NRF_RTC2->PRESCALER   =   327;                                                                        // f_RTC2 = ( 32.768kHz / ( 32767 + 1 ) ) = 1Hz ( 1s )
  NRF_RTC2->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

  NRF_RTC2->CC[0]       =   200;                                                                        // ( 200 * (f_RTC2)^(-1) ) = ( 200 * (99.9Hz)^(-1) ) ~ 2s

  NRF_RTC2->INTENSET    =   ( RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos );
  NRF_RTC2->EVTENSET    =   ( RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos );


  NVIC_EnableIRQ ( RTC2_IRQn );                                                                         // Enable Interrupt for the RTC2 in the core.
}



/**
 * @brief       void conf_Uart  ( void )
 * @details     Uart0 with the following features:
 *
 *                  * Baud Rate:    230400
 *                  * No Parity.
 *                  * No Flow Control.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/August/2018
 * @version     1/August/2018   The ORIGIN
 * @pre         Only TX pin will be configured.
 * @warning     N/A.
 */
void conf_UART  ( void )
{
  /* GPIO according to Table 273: GPIO configuration ( Reference Manual p.151 ) */
  NRF_GPIO->OUTSET             =   ( 1 << UART0_TX );
  // NRF_GPIO->DIRCLR             =   ( 1 << UART0_RX );
  NRF_GPIO->DIRSET             =   ( 1 << UART0_TX );

  /* Stop UART0 */
  NRF_UART0->TASKS_STOPRX      =   1;
  NRF_UART0->TASKS_STOPTX      =   1;

  NRF_UART0->ENABLE            =   UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;

  /* Configure the pins */
  NRF_UART0->PSELRTS           =   0xFFFFFFFF;
  NRF_UART0->PSELCTS           =   0xFFFFFFFF;
  NRF_UART0->PSELTXD           =   UART0_TX;
  NRF_UART0->PSELRXD           =   0xFFFFFFFF;

  /* BaudRate & Configuration */
  NRF_UART0->BAUDRATE          =   UART_BAUDRATE_BAUDRATE_Baud230400 << UART_BAUDRATE_BAUDRATE_Pos;
  NRF_UART0->CONFIG            =   ( UART_CONFIG_HWFC_Disabled   << UART_CONFIG_HWFC_Pos   ) |
                                   ( UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos );
  /* Configure Interrupts */
  NRF_UART0->INTENSET          =   ( UART_INTENSET_TXDRDY_Enabled << UART_INTENSET_TXDRDY_Pos );

  NVIC_ClearPendingIRQ    ( UART0_IRQn );
  NVIC_SetPriority        ( UART0_IRQn, 0 );                                                              // Maximum priority
  NVIC_EnableIRQ          ( UART0_IRQn );                                                                 // Enable Interrupt for the UART0 in the core.

  /* Enable UART0 */
  NRF_UART0->ENABLE            =   UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos;                  // UART0 ENABLED
  // NRF_UART0->TASKS_STARTTX     =   1;
  // NRF_UART0->TASKS_STARTRX     =   1;                                                                  // Enable reception
}
