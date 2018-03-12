/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs and P0.12 like input.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/March/2018
 * @version     12/March/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ ){
            NRF_GPIO->OUTSET        =   ( 1 << i );

            NRF_GPIO->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                        ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                        ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                        ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                        ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
    }

    NRF_GPIO->PIN_CNF[12]    =  ( GPIO_PIN_CNF_DIR_Input     <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                ( GPIO_PIN_CNF_INPUT_Connect <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                ( GPIO_PIN_CNF_PULL_Pullup   <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1    <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                ( GPIO_PIN_CNF_SENSE_Low     <<  GPIO_PIN_CNF_SENSE_Pos );

    NRF_GPIO->PIN_CNF[13]    =  ( GPIO_PIN_CNF_DIR_Input        <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                ( GPIO_PIN_CNF_INPUT_Connect    <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                ( GPIO_PIN_CNF_PULL_Disabled    <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1       <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled   <<  GPIO_PIN_CNF_SENSE_Pos );

    NRF_GPIO->PIN_CNF[14]    =  ( GPIO_PIN_CNF_DIR_Input        <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                ( GPIO_PIN_CNF_INPUT_Connect    <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                ( GPIO_PIN_CNF_PULL_Disabled    <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1       <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled   <<  GPIO_PIN_CNF_SENSE_Pos );
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
 * @date        20/June/2017
 * @version     20/June/2017   The ORIGIN
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
    NRF_UART0->BAUDRATE          =   UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos;
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


/**
 * @brief       void conf_GPIOTE  ( void )
 * @details     It configures GPIOTE channels.
 *
 *                  - P0.12. IN0.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/March/2018
 * @version     12/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIOTE  ( void )
{
    // Channel 0
    NRF_GPIOTE->CONFIG[0]    =  ( GPIOTE_CONFIG_POLARITY_LoToHi   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                ( 12                              << GPIOTE_CONFIG_PSEL_Pos       ) |
                                ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );

    NRF_GPIOTE->INTENSET     =  ( GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos );

//    // Channel 1
//    NRF_GPIOTE->CONFIG[1]    =  ( GPIOTE_CONFIG_POLARITY_LoToHi   << GPIOTE_CONFIG_POLARITY_Pos   ) |
//                                ( 13                              << GPIOTE_CONFIG_PSEL_Pos       ) |
//                                ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );
//
//    NRF_GPIOTE->INTENSET     =  ( GPIOTE_INTENSET_IN1_Set << GPIOTE_INTENSET_IN1_Pos );
//
//    // Channel 2
//    NRF_GPIOTE->CONFIG[2]    =  ( GPIOTE_CONFIG_POLARITY_LoToHi   << GPIOTE_CONFIG_POLARITY_Pos   ) |
//                                ( 14                              << GPIOTE_CONFIG_PSEL_Pos       ) |
//                                ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );
//
//    NRF_GPIOTE->INTENSET     =  ( GPIOTE_INTENSET_IN2_Set << GPIOTE_INTENSET_IN2_Pos );



    // Reset the events ( channel 0 )
    NRF_GPIOTE->EVENTS_IN[0] = 0;
//    NRF_GPIOTE->EVENTS_IN[1] = 0;
//    NRF_GPIOTE->EVENTS_IN[2] = 0;

    /*
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Enabled << GPIOTE_INTENSET_IN0_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN1_Enabled << GPIOTE_INTENSET_IN1_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN2_Enabled << GPIOTE_INTENSET_IN2_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Enabled << GPIOTE_INTENSET_IN3_Pos;
    */

    // Enable Interrupt
    NVIC_EnableIRQ ( GPIOTE_IRQn );
}
