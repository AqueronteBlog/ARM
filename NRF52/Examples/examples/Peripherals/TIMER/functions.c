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
 * @details     Two channels will create an interrupt. Channel zero at 0.125s and channel two at 0.5s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 62500 * (f_Timer0)^(-1) ) = ( 62500 * (500kHz)^(-1) ) ~ 0.125s.
 *
 *                 --- Channel 1:
 *                  * Overflow:             ( 4*62500 * (f_Timer0)^(-1) ) = ( 62500 * (500kHz)^(-1) ) ~ 0.5s.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_TIMER0  ( void )
{
    NRF_TIMER0->TASKS_STOP  =   1;
    NRF_TIMER0->MODE        =   ( TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos );
    NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   ( TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos );               // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   62500;                                                                      // ( 62500 * (f_Timer0)^(-1) ) = ( 62500 * (500kHz)^(-1) ) ~ 0.125s
    NRF_TIMER0->CC[1]       =   4*62500;                                                                    // ( 4*62500 * (f_Timer0)^(-1) ) = ( 4*62500 * (500kHz)^(-1) ) ~ 0.5s

    NRF_TIMER0->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos ) |
                                ( TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos );

    //NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos );// |
    //NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE1_CLEAR_Enabled << TIMER_SHORTS_COMPARE1_CLEAR_Pos );     // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] and COMPARE[1] event.


    NVIC_EnableIRQ ( TIMER0_IRQn );                                                                         // Enable Interrupt for the Timer0 in the core.
}


/**
 * @brief       void conf_TIMER1  ( void )
 * @details     Channel 0 overflows every 25ms.
 *
 *              Timer1:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 16-bits mode.
 *                  * Interrupt DISABLED.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 12500 * (f_Timer0)^(-1) ) = ( 12500 * (500kHz)^(-1) ) ~ 25ms.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_TIMER1  ( void )
{
    NRF_TIMER1->TASKS_STOP  =   1;
    NRF_TIMER1->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER1->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER1->BITMODE     =   TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;                   // 16 bit mode.
    NRF_TIMER1->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER1->CC[0]       =   12500;                                                                      // ( 12500 * (f_Timer0)^(-1) ) = ( 12500 * (500kHz)^(-1) ) = 25ms
    NRF_TIMER1->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER1 on COMPARE[0] event.
}




/**
 * @brief       void conf_TIMER2  ( void )
 * @details     Interrupt on Channel zero at 254us.
 *
 *              Timer2:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 8-bits mode.
 *                  * Interrupt ENABLE.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 127 * (f_Timer2)^(-1) ) = ( 255 * (500kHz)^(-1) ) ~ 254us
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */

void conf_TIMER2  ( void )
{
    NRF_TIMER2->TASKS_STOP  =   1;
    NRF_TIMER2->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER2->PRESCALER   =   5U;                                                                         // f_Timer2 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER2->BITMODE     =   TIMER_BITMODE_BITMODE_08Bit << TIMER_BITMODE_BITMODE_Pos;                   // 8 bit mode.
    NRF_TIMER2->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.

    NRF_TIMER2->CC[0]       =   127;                                                                        // ( 127 * (f_Timer2)^(-1) ) = ( 127 * (500kHz)^(-1) ) ~ 254us

    NRF_TIMER2->INTENSET    =   ( TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos );

    NRF_TIMER2->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER2 on COMPARE[0] event.


    NVIC_EnableIRQ ( TIMER2_IRQn );                                                                         // Enable Interrupt for the Timer2 in the core.
}




/**
 * @brief       void delay  ( void )
 * @details     Delay based on Timer1 ( channel 0 ). The time delay is about 10 * 25ms = 0.25s
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void delay  ( void )
{
    uint32_t i = 0;

    NRF_TIMER1->TASKS_START = 1;    // Start Timer1

    for ( i = 0; i < 10; i++ ){
            while ( NRF_TIMER1->EVENTS_COMPARE[0] == 0 );
            NRF_TIMER1->EVENTS_COMPARE[0]    =   0;
        }

    NRF_TIMER1->TASKS_STOP = 1;    // Stop Timer1
}
