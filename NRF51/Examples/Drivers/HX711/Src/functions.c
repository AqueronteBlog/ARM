/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     30/June/2017    TWI0 pins added.
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

    /* TWI0 pins. GPIO according to Table 258: GPIO configuration ( Reference Manual p.145 ) */
    NRF_GPIO->PIN_CNF[TWI0_SCL]     =   GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    |
                                        GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  |
                                        GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                        GPIO_PIN_CNF_DRIVE_S0D1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                        GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;

    NRF_GPIO->PIN_CNF[TWI0_SDA]     =   GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    |
                                        GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  |
                                        GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                        GPIO_PIN_CNF_DRIVE_S0D1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                        GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;

}


/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channels will create an interrupt about every 0.5s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (1MHz)^(-1) ) ~ 0.5s.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/August/2017
 * @version     2/August/2017   The ORIGIN
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

    NRF_TIMER0->CC[0]       =   500000;                                                                    // ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (1MHz)^(-1) ) ~ 0.5s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0].


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}


/**
 * @brief       void conf_TWI0  ( void )
 * @details     It configures the TWI0 ( I2C ) module.
 *
 *              TWI0:
 *                  * f_TWI0:   400kHz
 *                  * Interrupt DISABLE
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        30/June/2017
 * @version     30/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_TWI0  ( void )
{
    /* Stop TWI0 */
    NRF_TWI0->TASKS_STOP     =   1;
    NRF_TWI0->ENABLE         =   ( TWI_ENABLE_ENABLE_Disabled  <<  TWI_ENABLE_ENABLE_Pos );


    /* Configure the pins */
    NRF_TWI0->PSELSCL        =   TWI0_SCL;
    NRF_TWI0->PSELSDA        =   TWI0_SDA;


    /* Configure the frequency */
    NRF_TWI0->FREQUENCY      =   ( TWI_FREQUENCY_FREQUENCY_K400 << TWI_FREQUENCY_FREQUENCY_Pos );


    /* Disable Interrupts, clear events and all the errors */
    NRF_TWI0->INTENCLR       =   ( TWI_INTENCLR_STOPPED_Clear  << TWI_INTENCLR_STOPPED_Pos  ) |
                                 ( TWI_INTENCLR_RXDREADY_Clear << TWI_INTENCLR_RXDREADY_Pos ) |
                                 ( TWI_INTENCLR_TXDSENT_Clear  << TWI_INTENCLR_TXDSENT_Pos  ) |
                                 ( TWI_INTENCLR_ERROR_Clear    << TWI_INTENCLR_ERROR_Pos    ) |
                                 ( TWI_INTENCLR_BB_Clear       << TWI_INTENCLR_BB_Pos       );

    NRF_TWI0->EVENTS_STOPPED    =   0;
    NRF_TWI0->EVENTS_RXDREADY   =   0;
    NRF_TWI0->EVENTS_TXDSENT    =   0;
    NRF_TWI0->EVENTS_ERROR      =   0;
    NRF_TWI0->EVENTS_BB         =   0;

    NRF_TWI0->ERRORSRC       =   ( TWI_ERRORSRC_OVERRUN_Clear << TWI_ERRORSRC_OVERRUN_Pos ) |
                                 ( TWI_ERRORSRC_ANACK_Clear   << TWI_ERRORSRC_ANACK_Pos   ) |
                                 ( TWI_ERRORSRC_DNACK_Clear   << TWI_ERRORSRC_DNACK_Pos   );

    /* Configure shorts */
    /*
    NRF_TWI0->SHORTS         =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos ) |
                                 ( TWI_SHORTS_BB_STOP_Enabled    << TWI_SHORTS_BB_STOP_Pos    );
    */

    /* Enable TWI0 */
    NRF_TWI0->ENABLE         =   ( TWI_ENABLE_ENABLE_Enabled  <<  TWI_ENABLE_ENABLE_Pos );
}

