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
 * @brief       void conf_SPI0  ( void )
 * @details     [TODO] XXX.
 *
 *              SPI0:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
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
    NRF_TIMER0->TASKS_STOP  =   1;
    NRF_TIMER0->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;                   // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   125000;                                                                     // ( 125000 * (f_Timer0)^(-1) ) = ( 125000 * (1MHz)^(-1) ) ~ 0.125s
    NRF_TIMER0->CC[1]       =   4*125000;                                                                   // ( 4*125000 * (f_Timer0)^(-1) ) = ( 125000 * (1MHz)^(-1) ) ~ 0.5s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos ) |
                                ( TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos );

    //NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos );// |
    //NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE1_CLEAR_Enabled << TIMER_SHORTS_COMPARE1_CLEAR_Pos );     // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] and COMPARE[1] event.


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}


/**
 * @brief       void conf_SPIS1  ( void )
 * @details     [TODO] XXX.
 *
 *              SPIS1:
 *                  * Prescaler:            5   ( f_Timer0 = 1MHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_SPIS1  ( void )
{
    NRF_TIMER1->TASKS_STOP  =   1;
    NRF_TIMER1->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER1->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER1->BITMODE     =   TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;                   // 16 bit mode.
    NRF_TIMER1->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER1->CC[0]       =   25000;                                                                      // ( 25000 * (f_Timer0)^(-1) ) = ( 25000 * (1MHz)^(-1) ) = 25ms
    NRF_TIMER1->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER1 on COMPARE[0] event.
}

