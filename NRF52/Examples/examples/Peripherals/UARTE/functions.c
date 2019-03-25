/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN   
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
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN
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
    // NRF_UART0->TASKS_STARTTX     =   1;
    NRF_UART0->TASKS_STARTRX     =   1;                                                                     // Enable reception
}
