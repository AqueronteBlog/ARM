/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/March/2018
 * @version     27/March/2018   The ORIGIN
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
 * @brief       void conf_PWM0  ( void )
 * @details     It configures the PWM0 peripheral for 4 channels.
 *
 *              PWM frequency:  
 *                  * f_PWM = 4Hz ( COUNTER = T_PWM / T_PWM_CLK = ( 4 / 125kHz )^( -1 ) = 31250 ) 
 *
 *              Channel0:
 *                  * LED1.
 *                  * Duty cycle: 50% ( COUNTER * 0.5 = 15625 ).
 *                  * Polarity: LOW.
 *
 *              Channel1:
 *                  * LED2.
 *                  * Duty cycle: 50% ( COUNTER * 0.5 = 15625 ).
 *                  * Polarity: HIGH.
 *
 *              Channel2:
 *                  * LED3.
 *                  * Duty cycle: 50% ( COUNTER * 0.5 = 15625 ).
 *                  * Polarity: LOW.
 *
 *              Channel3:
 *                  * LED4.
 *                  * Duty cycle: 50% ( COUNTER * 0.5 = 15625 ).
 *                  * Polarity: HIGH.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/March/2018
 * @version     29/March/2018   PWM0 frequency was updated to 4Hz.
 *              28/March/2018   PWM0 function was completed, the comments were updated too.
 *              27/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_PWM0  ( void )
{
  /* Duty cycle for 4 channels  */
  uint16_t pwm_seq[]     =   { 15625, 15625 | 0x8000, 15625, 15625 | 0x8000 };

  
  /* Connect 4 channels  */
  NRF_PWM0->PSEL.OUT[0]  =  ( LED1                           << PWM_PSEL_OUT_PIN_Pos      ) | 
                            ( PWM_PSEL_OUT_CONNECT_Connected << PWM_PSEL_OUT_CONNECT_Pos  );

  NRF_PWM0->PSEL.OUT[1]  =  ( LED2                           << PWM_PSEL_OUT_PIN_Pos      ) |
                            ( PWM_PSEL_OUT_CONNECT_Connected << PWM_PSEL_OUT_CONNECT_Pos  );
  
  NRF_PWM0->PSEL.OUT[2]  =  ( LED3                           << PWM_PSEL_OUT_PIN_Pos      ) | 
                            ( PWM_PSEL_OUT_CONNECT_Connected << PWM_PSEL_OUT_CONNECT_Pos  );

  NRF_PWM0->PSEL.OUT[3]  =  ( LED4                           << PWM_PSEL_OUT_PIN_Pos      ) |
                            ( PWM_PSEL_OUT_CONNECT_Connected << PWM_PSEL_OUT_CONNECT_Pos  );


  /* PWM0 Enabled  */
  NRF_PWM0->ENABLE      =   ( PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos );
  
  /* PWM0 UP mode */
  NRF_PWM0->MODE        =   ( PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos );
  
  /* f_PWM_CLK = 125khz */
  NRF_PWM0->PRESCALER   =   ( PWM_PRESCALER_PRESCALER_DIV_128 << PWM_PRESCALER_PRESCALER_Pos );
  
  /* f_PWM0 = ( 125kHz / 31250 ) = 4Hz ( 250ms ) */
  NRF_PWM0->COUNTERTOP  =   ( 31250 << PWM_COUNTERTOP_COUNTERTOP_Pos );                 
  
  /* LOPP disabled */
  NRF_PWM0->LOOP        =   ( PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos );
  
  /* LOAD Individual mode */
  NRF_PWM0->DECODER     =   ( PWM_DECODER_LOAD_Individual   << PWM_DECODER_LOAD_Pos ) |
                            ( PWM_DECODER_MODE_RefreshCount << PWM_DECODER_MODE_Pos );
  
  /* Pointer to the duty cycle in RAM and amount of data */
  NRF_PWM0->SEQ[0].PTR  =   ( (uint32_t)( pwm_seq ) << PWM_SEQ_PTR_PTR_Pos );

  NRF_PWM0->SEQ[0].CNT  =   ( ( sizeof( pwm_seq ) / sizeof( uint16_t ) ) << PWM_SEQ_CNT_CNT_Pos );

  /* No delay */
  NRF_PWM0->SEQ[0].REFRESH  = 0;
  NRF_PWM0->SEQ[0].ENDDELAY = 0;
  
  /* It starts PWM0 */
  NRF_PWM0->TASKS_SEQSTART[0] = 1;
}


