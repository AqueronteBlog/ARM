/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/July/2018
 * @version     26/July/2018   The ORIGIN
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
 * @date        27/July/2018
 * @version     27/July/2018      The ORIGIN
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
 * @date        26/July/2018
 * @version     26/July/2018   The ORIGIN   
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
 * @date        27/July/2018
 * @version     27/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_SAADC  ( volatile uint32_t* myADC_Result )
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
                               ( SAADC_CH_CONFIG_TACQ_15us        << SAADC_CH_CONFIG_TACQ_Pos   ) |
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
}



/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channel. Channel zero at 2s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt Enabled.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 16*62500 * (f_Timer0)^(-1) ) = ( 16*62500 * (500kHz)^(-1) ) ~ 2s
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
 * @date        26/July/2018
 * @version     27/July/2018   Interrupt is enabled now.
 *              26/July/2018   The ORIGIN
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

  NRF_TIMER0->CC[0]       =   ( 16*62500 );                                                               // ( 16*62500 * (f_Timer0)^(-1) ) = ( 16*62500 * (500kHz)^(-1) ) ~ 2s

  NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );
  
  NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] event.


  NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
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
 * @date        27/July/2018
 * @version     27/July/2018   The ORIGIN
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
