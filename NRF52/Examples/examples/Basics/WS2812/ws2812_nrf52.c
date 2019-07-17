/**
 * @brief       ws2812_nrf52.c
 * @details     NRF52 WS2812 function libraries.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for NRF52 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "ws2812_nrf52.h"

/**
 * @brief       ws2812_init   ( WS2812_parameters_t )
 * @details     It configures the DIN pin as an output (LOW).
 *
 * @param[in]    myWS2812parameters:  WS2812 parameters.
 *
 * @param[out]   Status of ws2812_init.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
WS2812_con_status_t ws2812_init ( WS2812_parameters_t myWS2812parameters ) 
{
  /* DIN pin. GPIO output ( LOW ) */
  myWS2812parameters.DINport->OUTCLR                           =   ( 1UL << myWS2812parameters.DIN ); 

  myWS2812parameters.DINport->PIN_CNF[myWS2812parameters.DIN]  =  ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                                                  ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                                                  ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                                                  ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                                                  ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
 
  /* Peripheral configures successfully  */
  return WB2812_CON_SUCCESS;
}
