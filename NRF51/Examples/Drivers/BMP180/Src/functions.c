/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/September/2018
 * @version     10/September/2018   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0 ( SDK 1.1.0 ).
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"



/**
 * @brief       void conf_LFCLK  ( void )
 * @details     It turns the internal LFCLK clock on for RTCs.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/September/2018
 * @version     10/September/2018   The ORIGIN
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
 * @date        10/September/2018
 * @version     10/September/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ ){
            NRF_GPIO->OUTSET        =   ( 1 << i );

            NRF_GPIO->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    )|
                                        ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  )|
                                        ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   )|
                                        ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  )|
                                        ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );
    }
}


/**
 * @brief       void conf_RTC1  ( void )
 * @details     Channel 0 will create an interrupt every 2s.
 *
 *              RTC1:
 *                  * Prescaler:            327   ( f_RTC1 = ( 32.768kHz / ( 327 + 1 ) ) ~ 99.9Hz ( ~10ms ) ).
 *                  * Channel 0:            10ms*200 = 2s
 *                  * Interrupt ENABLE.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/September/2018
 * @version     10/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_RTC1  ( void )
{
    NRF_RTC1->TASKS_STOP  =   1UL;
    NRF_RTC1->PRESCALER   =   327UL;                                                                      // f_RTC1 = ( 32.768kHz / ( 327 + 1 ) ) ~ 99.9Hz ( ~10ms )
    NRF_RTC1->TASKS_CLEAR =   1UL;                                                                        // clear the task first to be usable for later.

    NRF_RTC1->CC[0]       =   200UL;                                                                      // ( 200 * (f_RTC1)^(-1) ) = ( 200 * (99.9Hz)^(-1) ) ~ 2s

    NRF_RTC1->INTENSET    =   ( RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos );
    NRF_RTC1->EVTENSET    =   ( RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos );


    NVIC_EnableIRQ ( RTC1_IRQn );                                                                         // Enable Interrupt for the RTC1 in the core.
}



/**
 * @brief       void conf_Uart  ( void )
 * @details     Uart0 with the following features:
 *
 *                  * Baud Rate:    115200
 *                  * No Parity.
 *                  * No Flow Control.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/September/2018
 * @version     10/September/2018    The ORIGIN
 * @pre         Only TX pin will be configured.
 * @warning     N/A.
 */
void conf_UART  ( void )
{
    /* GPIO according to Table 273: GPIO configuration ( Reference Manual p.151 ) */
    NRF_GPIO->OUTSET             =   ( 1UL << UART0_TX );
    // NRF_GPIO->DIRCLR             =   ( 1 << UART0_RX );
    NRF_GPIO->DIRSET             =   ( 1UL << UART0_TX );

    /* Stop UART0 */
    NRF_UART0->TASKS_STOPRX      =   1UL;
    NRF_UART0->TASKS_STOPTX      =   1UL;

    NRF_UART0->ENABLE            =   ( UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos );

    /* Configure the pins */
    NRF_UART0->PSELRTS           =   0xFFFFFFFF;
    NRF_UART0->PSELCTS           =   0xFFFFFFFF;
    NRF_UART0->PSELTXD           =   UART0_TX;
    NRF_UART0->PSELRXD           =   0xFFFFFFFF;

    /* BaudRate & Configuration */
    NRF_UART0->BAUDRATE          =   ( UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos );
    NRF_UART0->CONFIG            =   ( UART_CONFIG_HWFC_Disabled   << UART_CONFIG_HWFC_Pos   ) |
                                     ( UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos );
    /* Configure Interrupts */
    NRF_UART0->INTENSET          =   ( UART_INTENSET_TXDRDY_Enabled << UART_INTENSET_TXDRDY_Pos );

    NVIC_ClearPendingIRQ    ( UART0_IRQn );
    NVIC_SetPriority        ( UART0_IRQn, 0 );                                                              // Maximum priority
    NVIC_EnableIRQ          ( UART0_IRQn );                                                                 // Enable Interrupt for the UART0 in the core.

    /* Enable UART0 */
    NRF_UART0->ENABLE            =   ( UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos );              // UART0 ENABLED
    // NRF_UART0->TASKS_STARTTX     =   1;
    // NRF_UART0->TASKS_STARTRX     =   1;                                                                  // Enable reception
}
