/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/February/2018
 * @version     17/February/2018   The ORIGIN
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
 * @brief       void conf_WDT  ( void )
 * @details     It configures WDT to overflow every 1.5s and produces an interrupt.
 *
 *              WDT:
 *                  * Overflow:     Timeout = ( CRV + 1 )/32768 = ( 49151 + 1 )/32768 = 1.5s.
 *                  * WDT running on both SLEEP and HALT mode.
 *                  * Interrupt ENABLE.
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/February/2018
 * @version     18/February/2018   The ORIGIN
 * @pre         When started, the watchdog will automatically force the 32.768 kHz RC oscillator on 
 *              as long as no other 32.768 kHz clock source is running and generating the 32.768 kHz 
 *              system clock.
 * @warning     N/A
 */
void conf_WDT  ( void )
{
    NRF_WDT->CONFIG         =   ( WDT_CONFIG_SLEEP_Run << WDT_CONFIG_SLEEP_Pos ) |
                                ( WDT_CONFIG_HALT_Run  << WDT_CONFIG_HALT_Pos  );

    NRF_WDT->CRV            =   49151;                                                          // Timeout = ( CRV + 1 )/32768 = ( 49151 + 1 )/32768 = 1.5s
    NRF_WDT->RREN          |=   ( WDT_RREN_RR0_Enabled << WDT_RREN_RR0_Pos );                   // Enable reload register 0

    NRF_WDT->INTENSET       =   ( WDT_INTENSET_TIMEOUT_Enabled << WDT_INTENSET_TIMEOUT_Pos );   // Interruption enabled


    NVIC_EnableIRQ ( WDT_IRQn );                                                                // Enable Interrupt for WDT.
}
