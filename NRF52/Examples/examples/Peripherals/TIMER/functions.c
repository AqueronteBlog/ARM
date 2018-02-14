/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
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
 * @date        12/February/2018
 * @version     13/February/2018   All the LEDs OFF at the beginning.
 *              12/February/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED4 + 1 ); i++ )
    {
      NRF_P0->OUTSET        =   ( 1 << i );

      NRF_P0->PIN_CNF[i]    =   GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    |
                                GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  |
                                GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;
    }
}


/**
 * @brief       void conf_TIMER0  ( void )
 * @details     It configures Timer0 to overflow every 0.5s and produces an interrupt.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Overflow:             ( 250000 * (f_Timer0)^(-1) ) = ( 250000 * ( 500kHz )^( -1 ) ) ~ 0.5s.
 *                  * Interrupt ENABLE.
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/February/2018
 * @version     12/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_TIMER0  ( void )
{
    NRF_TIMER0->TASKS_STOP  =   1;
    NRF_TIMER0->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;                   // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   250000;                                                                     // ( 250000 * (f_Timer0)^(-1) ) = ( 125000 * (500kHz)^(-1) ) ~ 0.5s

    NRF_TIMER0->INTENSET    =   TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;

    NRF_TIMER0->SHORTS      =   TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;     // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] event.


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}
