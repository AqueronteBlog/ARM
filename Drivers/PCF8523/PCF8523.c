/**
 * @brief       PCF8523.h
 * @details     Real-Time Clock (RTC) and calendar.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "PCF8523.h"


/**
 * @brief       PCF8523_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



