/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
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
 * @date        8/June/2017
 * @version     8/June/2017      The ORIGIN
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
 * @brief       void conf_LFCLK  ( void )
 * @details     It turns the internal LFCLK clock on for RTCs.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_LFCLK  ( void )
{
    NRF_CLOCK->LFCLKSRC             =   ( CLOCK_LFCLKSRC_SRC_RC << CLOCK_LFCLKSRC_SRC_Pos );
    NRF_CLOCK->EVENTS_LFCLKSTARTED  =   0;
    NRF_CLOCK->TASKS_LFCLKSTART     =   1;

    while ( NRF_CLOCK->EVENTS_LFCLKSTARTED == 0 )       // [TODO] Insert a counter! otherwise if there is a problem it will get block!!!
    {
        //Do nothing.
    }

    NRF_CLOCK->EVENTS_LFCLKSTARTED  =   0;
}


/**
 * @brief       void conf_RTC0  ( void )
 * @details     Tick will create an interrupt every 125ms.
 *
 *              RTC0:
 *                  * Prescaler:            4095   ( f_RTC0 = ( 32.768kHz / ( 4095 + 1 ) ) = 8Hz ( 125ms ) ).
 *                  * Interrupt ENABLE.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_RTC0  ( void )
{
    NRF_RTC0->TASKS_STOP  =   1;
    NRF_RTC0->PRESCALER   =   4095 ;                                                                      // f_RTC0 = ( 32.768kHz / ( 4095 + 1 ) ) = 8Hz ( 125ms )
    NRF_RTC0->TASKS_CLEAR =   1;                                                                          // clear the task first to be usable for later.


    NRF_RTC0->INTENSET   |=   ( RTC_INTENSET_TICK_Enabled << RTC_INTENSET_TICK_Pos );
    NRF_RTC0->EVTENSET   |=   ( RTC_EVTENSET_TICK_Enabled << RTC_EVTENSET_TICK_Pos );


    NVIC_EnableIRQ ( RTC0_IRQn );                                                                         // Enable Interrupt for the RTC0 in the core.
}



/**
 * @brief       void conf_SWI  ( void )
 * @details     Enable 4 software interrupts.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
void conf_SWI  ( void )
{
    NVIC_EnableIRQ ( SWI0_IRQn );                                                                         // Enable Interrupt for the SWI0 in the core.
    NVIC_EnableIRQ ( SWI1_IRQn );                                                                         // Enable Interrupt for the SWI1 in the core.
    NVIC_EnableIRQ ( SWI2_IRQn );                                                                         // Enable Interrupt for the SWI2 in the core.
    NVIC_EnableIRQ ( SWI3_IRQn );                                                                         // Enable Interrupt for the SWI3 in the core.
    NVIC_EnableIRQ ( SWI4_IRQn );                                                                         // Enable Interrupt for the SWI4 in the core.
    // NVIC_EnableIRQ ( SWI5_IRQn );                                                                         // Enable Interrupt for the SWI5 in the core.
}

