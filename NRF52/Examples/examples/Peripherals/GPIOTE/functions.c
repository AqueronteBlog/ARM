/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/March/2018
 * @version     7/March/2018   The ORIGIN
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
      NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );

      NRF_P0->OUTSET        =   ( 1 << i );
    }

    for ( i = BTN1; i < ( BTN4 + 1 ); i++ )
    {
      NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                ( GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                ( GPIO_PIN_CNF_PULL_Pullup        <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                ( GPIO_PIN_CNF_SENSE_Low          <<  GPIO_PIN_CNF_SENSE_Pos  );
    }
}


/**
 * @brief       void conf_GPIOTE  ( void )
 * @details     It configures GPIOTE channels.
 *
 *                  - BTN1. IN0.
 *                  - BTN2. IN1.
 *                  - BTN3. IN2.
 *                  - BTN4. IN3.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/March/2018
 * @version     7/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIOTE  ( void )
{
    uint32_t i = 0;

    // Channel 0
    NRF_GPIOTE->CONFIG[0]    =    ( GPIOTE_CONFIG_POLARITY_HiToLo   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                  ( BTN1                            << GPIOTE_CONFIG_PSEL_Pos       ) |
                                  ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );

    NRF_GPIOTE->INTENSET  = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;

    // Channel 1
    NRF_GPIOTE->CONFIG[1]    =    ( GPIOTE_CONFIG_POLARITY_HiToLo   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                  ( BTN2                            << GPIOTE_CONFIG_PSEL_Pos       ) |
                                  ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );

    NRF_GPIOTE->INTENSET  = GPIOTE_INTENSET_IN1_Set << GPIOTE_INTENSET_IN1_Pos;

    // Channel 2
    NRF_GPIOTE->CONFIG[2]    =    ( GPIOTE_CONFIG_POLARITY_HiToLo   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                  ( BTN3                            << GPIOTE_CONFIG_PSEL_Pos       ) |
                                  ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );

    NRF_GPIOTE->INTENSET  = GPIOTE_INTENSET_IN2_Set << GPIOTE_INTENSET_IN2_Pos;

    // Channel 3
    NRF_GPIOTE->CONFIG[3]    =    ( GPIOTE_CONFIG_POLARITY_HiToLo   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                  ( BTN4                            << GPIOTE_CONFIG_PSEL_Pos       ) |
                                  ( GPIOTE_CONFIG_MODE_Event        << GPIOTE_CONFIG_MODE_Pos       );

    NRF_GPIOTE->INTENSET  = GPIOTE_INTENSET_IN3_Set << GPIOTE_INTENSET_IN3_Pos;



    // Reset the events
    for ( i = BTN1; i < ( BTN4 + 1 ); i++ )
        NRF_GPIOTE->EVENTS_IN[i - BTN1] = 0;

    /*
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Enabled << GPIOTE_INTENSET_IN0_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN1_Enabled << GPIOTE_INTENSET_IN1_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN2_Enabled << GPIOTE_INTENSET_IN2_Pos;
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Enabled << GPIOTE_INTENSET_IN3_Pos;
    */

    // Enable Interrupt
    NVIC_EnableIRQ ( GPIOTE_IRQn );
}
