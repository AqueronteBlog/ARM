/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs and SPI0's chip select.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ )
    {
      NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );
      
      NRF_P0->OUTSET        =   ( 1 << i );
    }


    NRF_P0->PIN_CNF[SPI0_CS]   =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                   ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                   ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                   ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                   ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
    
    NRF_P0->OUTSET             =   ( 1 << SPI0_CS );                                                  // Release the SPI's bus
}


/**
 * @brief       void conf_SPI0  ( void )
 * @details     It configures the SPI0 ( Master ).
 *
 *              SPI0:
 *                  * Frequency:            1Mbps.
 *                  * Mode:                 0 ( CPOL: 0 | CPHA: 0 ).
 *                  * Transmit MSB first.
 *                  * Interrupt ENABLE.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_SPI0  ( void )
{
    /* GPIO according to Table 221: GPIO configuration ( Reference Manual p.133 ) */
    NRF_GPIO->OUTSET             =   ( 0 << SPI0_MOSI );
    NRF_GPIO->OUTSET             =   ( 0 << SPI0_SCK  );
    NRF_GPIO->DIRCLR             =   ( 1 << SPI0_MISO );
    NRF_GPIO->DIRSET             =   ( 1 << SPI0_MOSI );
    NRF_GPIO->DIRSET             =   ( 1 << SPI0_SCK  );

    /* Disable the SPI0 */
    NRF_SPI0->ENABLE        =   ( SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos );

    /* Configure the SPI0 behavior */
    NRF_SPI0->CONFIG        =   ( SPI_CONFIG_ORDER_MsbFirst     << SPI_CONFIG_ORDER_Pos ) |
                                ( SPI_CONFIG_CPHA_Leading       << SPI_CONFIG_CPHA_Pos  ) |
                                ( SPI_CONFIG_CPOL_ActiveHigh    << SPI_CONFIG_CPOL_Pos );

    /* Configure the frequency */
    NRF_SPI0->FREQUENCY     =   ( SPI_FREQUENCY_FREQUENCY_M1 << SPI_FREQUENCY_FREQUENCY_Pos );              // f_SPI0 = 1Mbps

    /* Configure the pins */
    NRF_SPI0->PSELSCK       =   SPI0_SCK;
    NRF_SPI0->PSELMOSI      =   SPI0_MOSI;
    NRF_SPI0->PSELMISO      =   SPI0_MISO;

    /* Enable interrupt */
    NRF_SPI0->INTENSET      =   ( SPI_INTENCLR_READY_Enabled << SPI_INTENCLR_READY_Pos );


    NVIC_EnableIRQ ( SPI0_TWI0_IRQn );                                                                      // Enable Interrupt for the SPI0 in the core.

    /* Enable the SPI0 */
    NRF_SPI0->ENABLE        =   ( SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos );
}


/**
 * @brief       void conf_SPIS1  ( void )
 * @details     It configures the SPIS1 ( Slave ).
 *
 *              SPI1:
 *                  * Mode:                 0 ( CPOL: 0 | CPHA: 0 ).
 *                  * Transmit MSB first.
 *                  * Interrupt ENABLE.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_SPIS1  ( void )
{
    /* Initialize data */
    mySPIS_RX                =   0;
    mySPIS_TX                =   0xBE;


    /* GPIO according to Table 235: Pin configuration ( Reference Manual p.137 ) */
    NRF_GPIO->DIRCLR         =   ( 1 << SPIS1_SCK  );
    NRF_GPIO->DIRCLR         =   ( 1 << SPIS1_MOSI );
    NRF_GPIO->DIRCLR         =   ( 1 << SPIS1_MISO );
    NRF_GPIO->DIRCLR         =   ( 1 << SPIS1_CS   );


    /* Disable the SPIS1 */
    NRF_SPIS1->ENABLE        =   ( SPIS_ENABLE_ENABLE_Disabled << SPIS_ENABLE_ENABLE_Pos );

    /* Configure the SPIS1 behavior */
    NRF_SPIS1->CONFIG        =   ( SPIS_CONFIG_ORDER_MsbFirst   << SPIS_CONFIG_ORDER_Pos ) |
                                 ( SPIS_CONFIG_CPHA_Leading     << SPIS_CONFIG_CPHA_Pos  ) |
                                 ( SPIS_CONFIG_CPOL_ActiveHigh  << SPIS_CONFIG_CPOL_Pos  );

    /* Configure the pins */
    NRF_SPIS1->PSELSCK       =   SPIS1_SCK;
    NRF_SPIS1->PSELMOSI      =   SPIS1_MOSI;
    NRF_SPIS1->PSELMISO      =   SPIS1_MISO;
    NRF_SPIS1->PSELCSN       =   SPIS1_CS;


    /* Configure Maximum number of bytes in receive/transmit buffer */
    NRF_SPIS1->MAXRX         =   ( 1 << SPIS_MAXRX_MAXRX_Pos );
    NRF_SPIS1->MAXTX         =   ( 1 << SPIS_MAXTX_MAXTX_Pos );

    NRF_SPIS1->RXDPTR        =   (uint32_t)&mySPIS_RX;
    NRF_SPIS1->TXDPTR        =   (uint32_t)&mySPIS_TX;

    /* Configure Default characters */
    NRF_SPIS1->DEF           =   ( 0x00  << SPIS_DEF_DEF_Pos );
    NRF_SPIS1->ORC           =   ( 0x23  << SPIS_ORC_ORC_Pos );


    /* Reset STATUS register and events */
    NRF_SPIS1->STATUS        =   ( SPIS_STATUS_OVERREAD_Clear << SPIS_STATUS_OVERREAD_Pos ) |
                                 ( SPIS_STATUS_OVERFLOW_Clear << SPIS_STATUS_OVERFLOW_Pos );

    NRF_SPIS1->EVENTS_END       =   0;
    NRF_SPIS1->EVENTS_ACQUIRED  =   0;


    /* Enable interrupt */
    NRF_SPIS1->INTENSET      =   ( SPIS_INTENCLR_END_Enabled       << SPIS_INTENCLR_END_Pos       ) |
                                 ( SPIS_INTENCLR_ACQUIRED_Enabled  << SPIS_INTENCLR_ACQUIRED_Pos  );
    NRF_SPIS1->SHORTS        =   ( SPIS_SHORTS_END_ACQUIRE_Enabled << SPIS_SHORTS_END_ACQUIRE_Pos );


    NVIC_EnableIRQ ( SPI1_TWI1_IRQn );                                                                      // Enable Interrupt for the SPIS1 in the core.


    /* Enable SPI slave device */
    NRF_SPIS1->ENABLE        =   ( SPIS_ENABLE_ENABLE_Enabled << SPIS_ENABLE_ENABLE_Pos );


    NRF_SPIS1->TASKS_RELEASE =   1;
}


/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channel will create an interrupt. Channel zero at 1s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 500000 * ( f_Timer0 )^( -1 ) ) = ( 500000 * ( 500kHz )^( -1 ) ) ~ 1s.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
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

    NRF_TIMER0->CC[0]       =   500000;                                                                     // ( 500000 * ( f_Timer0 )^( -1 ) ) = ( 500000 * ( 500kHz )^( -1 ) ) ~ 1s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] event.


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}
