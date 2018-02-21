/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/February/2018
 * @version     21/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"

/**
 * @brief       void conf_CLK  ( void )
 * @details     It activates the external HFCLK crystal oscillator ( 16MHz ).
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        21/June/2017
 * @version     21/June/2017      The ORIGIN
 * @pre         NaN
 * @warning     In case to use a 32MHz crystal oscillator, it also has to be configured
 *              in system_nrf51.c file ( #define __SYSTEM_CLOCK (16000000UL) )
 */
void conf_CLK  ( void )
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED  =   0;                      // Reset flag
    NRF_CLOCK->TASKS_HFCLKSTART     =   1;                      // Start External crystal CLK

    while ( NRF_CLOCK->EVENTS_HFCLKSTARTED  !=   1 );           // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
                                                                // [WORKAROUND] Insert a counter.
}

/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/February/2018
 * @version     13/February/2018   All the LEDs OFF at the beginning.
 *              12/February/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO(void) {
  uint32_t i = 0;

  for ( i = LED1; i < ( LED4 + 1 ); i++ ) {
    NRF_P0->OUTSET     = ( 1 <<  i);

    NRF_P0->PIN_CNF[i] = ( GPIO_PIN_CNF_DIR_Output        << GPIO_PIN_CNF_DIR_Pos   ) |
                         ( GPIO_PIN_CNF_INPUT_Disconnect  << GPIO_PIN_CNF_INPUT_Pos ) |
                         ( GPIO_PIN_CNF_PULL_Disabled     << GPIO_PIN_CNF_PULL_Pos  ) |
                         ( GPIO_PIN_CNF_DRIVE_S0S1        << GPIO_PIN_CNF_DRIVE_Pos ) |
                         ( GPIO_PIN_CNF_SENSE_Disabled    << GPIO_PIN_CNF_SENSE_Pos );
  }
}

/**
 * @brief       void conf_RADIO  ( void )
 * @details     [TODO]
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/February/2018
 * @version     21/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
void conf_RADIO(uint8_t *myPacketPointer) {
  /* Reset to its initial state */
  NRF_RADIO->POWER = ( RADIO_POWER_POWER_Disabled << RADIO_POWER_POWER_Pos );
  NRF_RADIO->POWER = ( RADIO_POWER_POWER_Enabled  << RADIO_POWER_POWER_Pos );     // A little delay may be inserted!

  // Configure radio with 2Mbit Nordic proprietary mode
  NRF_RADIO->MODE  = ( RADIO_MODE_MODE_Nrf_2Mbit << RADIO_MODE_MODE_Pos );

  // Configure packet: NO S0,S1 or Length fields & 8-bit preamble.
  NRF_RADIO->PCNF0 = ( 0                            << RADIO_PCNF0_LFLEN_Pos  ) |
                     ( 0                            << RADIO_PCNF0_S0LEN_Pos  ) |
                     ( 0                            << RADIO_PCNF0_S1LEN_Pos  ) |
                     ( RADIO_PCNF0_S1INCL_Automatic << RADIO_PCNF0_S1INCL_Pos ) |
                     ( RADIO_PCNF0_PLEN_8bit        << RADIO_PCNF0_PLEN_Pos   );

  // Configure static payload length of 20bytes. 3 bytes address, little endian with whitening enabled.
  NRF_RADIO->PCNF1 = ( 20                           << RADIO_PCNF1_MAXLEN_Pos) |
                     ( 20                           << RADIO_PCNF1_STATLEN_Pos) |
                     ( 2                            << RADIO_PCNF1_BALEN_Pos) |
                     ( RADIO_PCNF1_ENDIAN_Little    << RADIO_PCNF1_ENDIAN_Pos) |
                     ( RADIO_PCNF1_WHITEEN_Enabled  << RADIO_PCNF1_WHITEEN_Pos);

  // Whitening value
  NRF_RADIO->DATAWHITEIV = ( ( 0x55 & RADIO_DATAWHITEIV_DATAWHITEIV_Msk ) << RADIO_DATAWHITEIV_DATAWHITEIV_Pos );

  // Configure address Prefix0 and Base0
  NRF_RADIO->BASE0   = ( 0x0000BEEF );
  NRF_RADIO->PREFIX0 = ( ( 0x22 & RADIO_PREFIX0_AP0_Msk ) << RADIO_PREFIX0_AP0_Pos );

  // Use logical address 0 ( BASE0 and PREFIX0 byte 0 )
  NRF_RADIO->RXADDRESSES = ( RADIO_RXADDRESSES_ADDR0_Disabled << RADIO_RXADDRESSES_ADDR0_Pos );

  // Initialize CRC ( two bytes )
  NRF_RADIO->CRCCNF    =   (RADIO_CRCCNF_LEN_Two << RADIO_CRCCNF_LEN_Pos) |
                           (RADIO_CRCCNF_SKIPADDR_Skip << RADIO_CRCCNF_SKIPADDR_Pos);

  NRF_RADIO->CRCPOLY   =   ( 0x0000AAAA << RADIO_CRCPOLY_CRCPOLY_Pos );
  NRF_RADIO->CRCINIT   =   ( 0x12345678 << RADIO_CRCINIT_CRCINIT_Pos );

  // Enable fast rampup, new in nRF52
  NRF_RADIO->MODECNF0  =   ( RADIO_MODECNF0_DTX_B0  << RADIO_MODECNF0_DTX_Pos ) |
                           ( RADIO_MODECNF0_RU_Fast << RADIO_MODECNF0_RU_Pos  );

  // Output Power: 0dBm  @2400MHz
  NRF_RADIO->TXPOWER   =   ( RADIO_TXPOWER_TXPOWER_0dBm << RADIO_TXPOWER_TXPOWER_Pos );
  NRF_RADIO->FREQUENCY =   ( ( 0 & RADIO_FREQUENCY_FREQUENCY_Msk ) << RADIO_FREQUENCY_FREQUENCY_Pos );      // Frequency = 2400 + FREQUENCY (MHz).


  // Configure address of the packet and logic address to use
  NRF_RADIO->PACKETPTR =   ( uint32_t )&myPacketPointer[0];

  // Configure shortcuts.
  NRF_RADIO->SHORTS    =   ( RADIO_SHORTS_READY_START_Enabled << RADIO_SHORTS_READY_START_Pos ) |
                           ( RADIO_SHORTS_END_DISABLE_Enabled << RADIO_SHORTS_END_DISABLE_Pos );
}