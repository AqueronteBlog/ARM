/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs and SPI0's chip select.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     27/June/2017    SPI0's pin chip select added.
 *              23/May/2017     All the LEDs OFF at the beginning.
 *              5/May/2017      The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ ){
            NRF_GPIO->OUTSET        =   ( 1 << i );

            NRF_GPIO->PIN_CNF[i]    =   GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    |
                                        GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  |
                                        GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                        GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                        GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;
    }


    NRF_GPIO->OUTSET             =   ( 1 << SPI0_CS );                                                  // Release the SPI's bus
    NRF_GPIO->PIN_CNF[SPI0_CS]   =   GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    |
                                     GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  |
                                     GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                     GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                     GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;

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
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
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
 * @brief       void conf_TIMER0  ( void )
 * @details     One channel will create an interrupt. Channel zero at 1s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 1000000 * (f_Timer0)^(-1) ) = ( 1000000 * (1MHz)^(-1) ) ~ 1s.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/June/2017
 * @version     28/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_TIMER0  ( void )
{
    NRF_TIMER0->TASKS_STOP  =   1;
    NRF_TIMER0->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;                   // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   1000000;                                                                    // ( 1000000 * (f_Timer0)^(-1) ) = ( 1000000 * (1MHz)^(-1) ) ~ 1s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] event.


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}


