/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/February/2018
 * @version     19/February/2018   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
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
    NRF_CLOCK->XTALFREQ             =   ( CLOCK_XTALFREQ_XTALFREQ_16MHz << CLOCK_XTALFREQ_XTALFREQ_Pos );
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
 * @date        5/May/2017
 * @version     23/May/2017     All the LEDs OFF at the beginning.
 *              5/May/2017      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ )
    {
        NRF_GPIO->OUTSET        =   ( 1 << i );

        NRF_GPIO->PIN_CNF[i]    =   GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    |
                                    GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  |
                                    GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                    GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                    GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;
    }
}


/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channels will create an interrupt about every 1s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (500kHz)^(-1) ) ~ 1s.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        2/August/2017
 * @version     2/August/2017   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_TIMER0  ( void )
{
    NRF_TIMER0->TASKS_STOP  =   1;
    NRF_TIMER0->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;                   // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   500000;                                                                    // ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (500KHz)^(-1) ) ~ 1s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0].


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}


/**
 * @brief       void conf_RADIO  ( void )
 * @details     [TODO]
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/January/2018
 * @version     19/January/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
void conf_RADIO  ( uint8_t* myPacketPointer )
{
    /* Reset to its initial state */
    NRF_RADIO->POWER     =   ( RADIO_POWER_POWER_Disabled << RADIO_POWER_POWER_Pos );
    NRF_RADIO->POWER     =   ( RADIO_POWER_POWER_Enabled  << RADIO_POWER_POWER_Pos );


    NRF_RADIO->MODE      =   ( RADIO_MODE_MODE_Nrf_2Mbit << RADIO_MODE_MODE_Pos );              // Radio with 2Mbit/s Nordic proprietary

    NRF_RADIO->PCNF0     =   ( 0 << RADIO_PCNF0_LFLEN_Pos ) |                                   // LENGTH:  0bits
                             ( 0 << RADIO_PCNF0_S0LEN_Pos ) |                                   // S0:      0bits
                             ( 0 << RADIO_PCNF0_S1LEN_Pos );                                    // S1:      0bits

    NRF_RADIO->PCNF1     =   ( 10                           << RADIO_PCNF1_MAXLEN_Pos  ) |      // Maximum length of packet payload: 10bytes
                             ( 10                           << RADIO_PCNF1_STATLEN_Pos ) |      // Static length in number of bytes: 10bytes
                             ( 2                            << RADIO_PCNF1_BALEN_Pos   ) |      // Total address of 3 bytes
                             ( RADIO_PCNF1_ENDIAN_Little    << RADIO_PCNF1_ENDIAN_Pos  ) |      // Little endian
                             ( RADIO_PCNF1_WHITEEN_Enabled  << RADIO_PCNF1_WHITEEN_Pos );       // Packet whitening enabled

    NRF_RADIO->DATAWHITEIV = ( ( 0x55 & RADIO_DATAWHITEIV_DATAWHITEIV_Msk ) << RADIO_DATAWHITEIV_DATAWHITEIV_Pos );  // Initialize whitening value


    NRF_RADIO->BASE0     =   ( 0x0000BEEF );                                                     // Base0: 0x00000BEEF
    NRF_RADIO->PREFIX0   =   ( ( 0x22 & RADIO_PREFIX0_AP0_Msk ) << RADIO_PREFIX0_AP0_Pos );      // 0x22 --> Prefix0 AP0



    // Use logical address 0 (BASE0 + PREFIX0 byte 0)
    NRF_RADIO->TXADDRESS =   ( ( 0 & RADIO_TXADDRESS_TXADDRESS_Msk ) << RADIO_TXADDRESS_TXADDRESS_Pos );


    // Initialize CRC (one bytes)
    NRF_RADIO->CRCCNF    =   ( RADIO_CRCCNF_LEN_One       << RADIO_CRCCNF_LEN_Pos      ) |
                             ( RADIO_CRCCNF_SKIPADDR_Skip << RADIO_CRCCNF_SKIPADDR_Pos );


    NRF_RADIO->CRCPOLY   =   ( 0x0000AAAA << RADIO_CRCPOLY_CRCPOLY_Pos );
    NRF_RADIO->CRCINIT   =   ( 0x12345678 << RADIO_CRCINIT_CRCINIT_Pos );


    // 0dBm Output Power @2400MHz
    NRF_RADIO->TXPOWER   =   ( RADIO_TXPOWER_TXPOWER_0dBm << RADIO_TXPOWER_TXPOWER_Pos );
    NRF_RADIO->FREQUENCY =   ( ( 0 & RADIO_FREQUENCY_FREQUENCY_Msk ) << RADIO_FREQUENCY_FREQUENCY_Pos );                            // Frequency = 2400 + FREQUENCY (MHz).


    // Configure Packet address
    NRF_RADIO->PACKETPTR =   ( uint32_t )&myPacketPointer[0];


    // Configure shortcuts.
    NRF_RADIO->SHORTS    =   ( RADIO_SHORTS_READY_START_Enabled << RADIO_SHORTS_READY_START_Pos ) |
                             ( RADIO_SHORTS_END_DISABLE_Enabled << RADIO_SHORTS_END_DISABLE_Pos );
}
