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
 * @brief       void conf_UARTE  ( uint8_t* TX_buff, uint32_t TX_lenght, uint8_t* RX_buff, uint32_t RX_lenght )
 * @details     UartE with the following features:
 *
 *                  * Baud Rate:    230400 ( actual rate: 231884 )
 *                  * No Parity.
 *                  * No Flow Control.
 *                  * ENDTX and ENDRX Interrupts ENABLED.
 *
 * @param[in]    TX_buff:   TX buffer.
 * @param[in]    TX_lenght: Max TX data.
 * @param[in]    RX_buff:   RX buffer .
 * @param[in]    RX_lenght: Max RX data.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     31/March/2019   Comments were updated.
 *              26/March/2019   Most of the configuration is done, pointers must
 *                              still be defined.
 *              25/March/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_UARTE  ( uint8_t* TX_buff, uint32_t TX_lenght, uint8_t* RX_buff, uint32_t RX_lenght )
{
    /* GPIO according to Table 81: GPIO configuration before enabling peripheral ( Product Specification p.337 ) */
    NRF_P0->OUTSET               =   ( 1UL << UART0_TX );
    NRF_P0->DIRCLR               =   ( 1UL << UART0_RX );
    NRF_P0->DIRSET               =   ( 1UL << UART0_TX );

    /* Stop UARTE */
    NRF_UARTE0->TASKS_STOPRX     =   1UL;
    NRF_UARTE0->TASKS_STOPTX     =   1UL;

    NRF_UARTE0->ENABLE           =   ( UARTE_ENABLE_ENABLE_Disabled << UARTE_ENABLE_ENABLE_Pos );

    /* Configure the pins */
    NRF_UARTE0->PSEL.RTS         =   0xFFFFFFFF;
    NRF_UARTE0->PSEL.CTS         =   0xFFFFFFFF;
    NRF_UARTE0->PSEL.TXD         =   UART0_TX;
    NRF_UARTE0->PSEL.RXD         =   UART0_RX;

    /* BaudRate & Configuration */
    NRF_UARTE0->BAUDRATE         =   ( UARTE_BAUDRATE_BAUDRATE_Baud230400 << UARTE_BAUDRATE_BAUDRATE_Pos );
    NRF_UARTE0->CONFIG           =   ( UARTE_CONFIG_HWFC_Disabled   << UARTE_CONFIG_HWFC_Pos   ) |
                                     ( UARTE_CONFIG_PARITY_Excluded << UARTE_CONFIG_PARITY_Pos );
    
    /* Set EasyDMA for TX and RX   */
    NRF_UARTE0->TXD.PTR          =   (uint32_t)( (uint8_t *) TX_buff );
    NRF_UARTE0->TXD.MAXCNT       =   TX_lenght;

    NRF_UARTE0->RXD.PTR          =   (uint32_t)( (uint8_t *) RX_buff );
    NRF_UARTE0->RXD.MAXCNT       =   RX_lenght;

    /* Configure Interrupts */
    NRF_UARTE0->SHORTS           =   ( UARTE_SHORTS_ENDRX_STOPRX_Enabled << UARTE_SHORTS_ENDRX_STOPRX_Pos );
    NRF_UARTE0->INTENSET         =   ( UARTE_INTENSET_ENDRX_Enabled << UARTE_INTENSET_ENDRX_Pos ) |
                                     ( UARTE_INTENSET_ENDTX_Enabled << UARTE_INTENSET_ENDTX_Pos );

    NVIC_ClearPendingIRQ    ( UARTE0_UART0_IRQn );
    NVIC_SetPriority        ( UARTE0_UART0_IRQn, 0 );                                                      // Maximum priority
    NVIC_EnableIRQ          ( UARTE0_UART0_IRQn );                                                         // Enable Interrupt for the UART0 in the core.

    /* Enable UARTE */
    NRF_UARTE0->ENABLE          =   ( UARTE_ENABLE_ENABLE_Enabled << UARTE_ENABLE_ENABLE_Pos );             
    // NRF_UARTE0->TASKS_STARTTX    =   1UL;
    NRF_UARTE0->TASKS_STARTRX   =   1UL;                                                                   // Enable reception
}
