/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/November/2017
 * @version     8/November/2017   The ORIGIN
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
 * @version     23/May/2017     All the LEDs OFF at the beginning.
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
}




/**
 * @brief       void conf_GPIOTE  ( void )
 * @details     It configures GPIOTE channels.
 *
 *                  - LED1. IN0 ( Task ).
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/November/2017
 * @version     8/November/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void conf_GPIOTE  ( void )
{
    // Channel 0
    NRF_GPIOTE->CONFIG[0]    =    ( GPIOTE_CONFIG_POLARITY_Toggle   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                  ( LED1                            << GPIOTE_CONFIG_PSEL_Pos       ) |
                                  ( GPIOTE_CONFIG_MODE_Task         << GPIOTE_CONFIG_MODE_Pos       );



    // Reset the task
    NRF_GPIOTE->TASKS_OUT[LED1]  =   0;


    /*
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Enabled << GPIOTE_INTENSET_IN0_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN1_Enabled << GPIOTE_INTENSET_IN1_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN2_Enabled << GPIOTE_INTENSET_IN2_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Enabled << GPIOTE_INTENSET_IN3_Pos;
    */

    // Enable Interrupt
    // NVIC_EnableIRQ ( GPIOTE_IRQn );
}




/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channels will create an event about every 1s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt DISABLED.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (500kHz)^(-1) ) ~ 1s.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/November/2017
 * @version     8/November/2017   The ORIGIN
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

    NRF_TIMER0->CC[0]       =   500000;                                                                    // ( 500000 * (f_Timer0)^(-1) ) = ( 500000 * (500KHz)^(-1) ) ~ 1s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0].


    // NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}
