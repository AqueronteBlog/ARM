/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2018
 * @version     17/July/2018   The ORIGIN
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
 * @date        17/July/2018
 * @version     17/July/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
  uint32_t i = 0;

  for ( i = LED1; i < ( LED4 + 1 ); i++ )
  {
    NRF_P0->OUTSET        =   ( 1 << i );

    NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                              ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                              ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                              ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                              ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
  }
}


/**
 * @brief       void conf_PPI  ( void )
 * @details     It sets up one PPI channel.
 *
 *              Channel 0:
 *                  * Event: NRF_RTC2->EVENTS_COMPARE[0].
 *                  * Task:  NRF_TEMP->TASKS_START.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2017
 * @version     17/July/2017   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_PPI  ( void )
{
    NRF_PPI->CH[0].EEP   =   ( uint32_t )&NRF_RTC2->EVENTS_COMPARE[0];
    NRF_PPI->CH[0].TEP   =   ( uint32_t )&NRF_TEMP->TASKS_START;


    /* Enable PPI channel 0  */
    NRF_PPI->CHEN        =   ( PPI_CHEN_CH0_Enabled << PPI_CHEN_CH0_Pos );
}
