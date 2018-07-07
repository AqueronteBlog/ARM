/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/July/2018
 * @version     3/July/2018   The ORIGIN
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
 * @date        3/July/2018
 * @version     3/July/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
  uint32_t i = 0;
    
  /* Configure the LEDs  */
  for ( i = LED1; i < ( LED4 + 1 ); i++ )
  {
    NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                              ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                              ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                              ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                              ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );

    NRF_P0->OUTSET        =   ( 1 << i );
  }
}


/**
 * @brief       void conf_GPIOTE  ( void )
 * @details     It configures GPIOTE like PORT EVENT.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/July/2018
 * @version     3/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIOTE  ( void )
{
  uint32_t i = 0;
  
  /* Disable interrupts on the PORT event  */
  NRF_GPIOTE->INTENCLR    |=   ( GPIOTE_INTENCLR_PORT_Clear << GPIOTE_INTENCLR_PORT_Pos );
  

  /* Configure the Buttons  */
  for ( i = BTN1; i < ( BTN4 + 1 ); i++ )
  {
    NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    ) |
                              ( GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                              ( GPIO_PIN_CNF_PULL_Pullup        <<  GPIO_PIN_CNF_PULL_Pos   ) |
                              ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                              ( GPIO_PIN_CNF_SENSE_Low          <<  GPIO_PIN_CNF_SENSE_Pos  );
  }

  /* Clean PORT EVENT flag   */
  NRF_GPIOTE->EVENTS_PORT  =   0;


  /* Enable Interrupt  */
  NRF_GPIOTE->INTENSET   |=  ( GPIOTE_INTENSET_PORT_Set << GPIOTE_INTENSET_PORT_Pos );

  NVIC_EnableIRQ ( GPIOTE_IRQn );
}
