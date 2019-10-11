/**
 * @brief       HDC2080.c
 * @details     Low-Power Humidity and Temperature Digital Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/October/2019
 * @version     10/October/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "HDC2080.h"


/**
 * @brief       HDC2080_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        10/October/2019
 * @version     10/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}
