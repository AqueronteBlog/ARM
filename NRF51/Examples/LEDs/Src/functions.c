#include "functions.h"

void conf_GPIO  ( void )
{
    uint32_t i = 0;

    for ( i = LED1; i < ( LED1 + 1 ); i++ )
        NRF_GPIO->PIN_CNF[i]    =   GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    |
                                    GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  |
                                    GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                    GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                    GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;
}



void conf_Timer0  ( void )
{
    NRF_TIMER0->MODE        =   TIMER_MODE_MODE_Timer;
    NRF_TIMER0->PRESCALER   =   5U;                             // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
    NRF_TIMER0->BITMODE     =   TIMER_BITMODE_BITMODE_32Bit;    // 32 bit mode.
    NRF_TIMER0->TASKS_CLEAR =   1;                              // clear the task first to be usable for later.

    NRF_TIMER0->CC[0]       =   125000;

    NRF_TIMER0->INTENSET    =   TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;


    NVIC_EnableIRQ ( TIMER0_IRQn );                             // Enable Interrupt for the Timer0 in the core.
}
