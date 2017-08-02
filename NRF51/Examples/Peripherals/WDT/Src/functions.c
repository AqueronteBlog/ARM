/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/April/2017
 * @version     21/June/2017    WDT function added.
 *              12/April/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
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
 * @brief       void conf_WDT  ( void )
 * @details     It configures WDT to overflow every 1.5s and produces an interrupt.
 *
 *              WDT:
 *                  * Overflow:     Timeout = ( CRV + 1 )/32768 = ( 49151 + 1 )/32768 = 1.5s.
 *                  * WDT running on both SLEEP and HALT mode.
 *                  * Interrupt ENABLE.
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        21/June/2017
 * @version     21/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
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
