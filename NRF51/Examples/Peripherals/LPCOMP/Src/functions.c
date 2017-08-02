/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/July/2017
 * @version     14/July/2017    The ORIGIN
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
 * @brief       void conf_LPCOMP  ( void )
 * @details     It configures the LPCOMP peripheral.
 *
 *              LPCOMP:
 *                  * AIN2 ( P0.01 ).
 *                  * REFSEL: VDD*4/8
 *                  * Up-Interrupt Enabled
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/July/2017
 * @version     14/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void conf_LPCOMP  ( void )
{
    NRF_LPCOMP->TASKS_STOP  =   1;
    NRF_LPCOMP->ENABLE      =   ( LPCOMP_ENABLE_ENABLE_Disabled << LPCOMP_ENABLE_ENABLE_Pos );

    NRF_LPCOMP->PSEL        =   ( LPCOMP_PSEL_PSEL_AnalogInput2 << LPCOMP_PSEL_PSEL_Pos );
    NRF_LPCOMP->REFSEL      =   ( LPCOMP_REFSEL_REFSEL_SupplyFourEighthsPrescaling << LPCOMP_REFSEL_REFSEL_Pos );

    NRF_LPCOMP->INTENSET    =   ( LPCOMP_INTENSET_UP_Enabled << LPCOMP_INTENSET_UP_Pos );

    NRF_LPCOMP->ENABLE      =   ( LPCOMP_ENABLE_ENABLE_Enabled << LPCOMP_ENABLE_ENABLE_Pos );

    NRF_LPCOMP->TASKS_START =   1;


    NVIC_EnableIRQ ( LPCOMP_IRQn );                                                                         // Enable Interrupt for the LPCOMP in the core.
}

