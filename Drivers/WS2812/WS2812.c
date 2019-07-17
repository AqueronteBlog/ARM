/**
 * @brief       WS2812.c
 * @details     Intelligent control LED integrated light source.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "WS2812.h"


/**
 * @brief       WS2812_Init ( WB2812_parameters_t )
 *
 * @details     It configures the GPIO peripheral.
 *
 * @param[in]    myWB2812parameters:  GPIO parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of WS2812_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
WS2812_status_t WS2812_Init ( WS2812_parameters_t myWS2812parameters )
{
  WS2812_con_status_t aux;

  aux  =   ws2812_init ( myWS2812parameters );



  if ( aux == WB2812_CON_SUCCESS )
  {
    return   WS2812_SUCCESS;
  }
  else
  {
    return   WS2812_FAILURE;
  }
}



/**
 * @brief       WS2812_SendLEDsBuffer ( WS2812_num_leds_t, WS2812_data_t )
 *
 * @details     It sends data to the RGB LEDs.
 *
 * @param[in]    myLEDsBuffer:  Colour for the LEDs.
 * @param[in]    myNumLEDs:     Number of LEDs.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of WS2812_SendLEDsBuffer.
 *
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
WS2812_status_t WS2812_SendLEDsBuffer ( WS2812_num_leds_t* myLEDsBuffer, WS2812_data_t myNumLEDs )
{
  uint32_t  i           =   0UL;
  uint16_t  j           =   0UL;
  uint32_t  currentLED  =   0UL;

  for ( i = 0UL; i < myNumLEDs.numberOfLEDs; i++ )
  {
    currentLED   =   myLEDsBuffer[i].green;
    currentLED <<=   8U;
    currentLED  |=   myLEDsBuffer[i].red;
    currentLED <<=   8U;
    currentLED  |=   myLEDsBuffer[i].blue;

    for ( j = 0U; j < 24U; j++ )
    {

    }
  }




  return   WS2812_SUCCESS;
}

