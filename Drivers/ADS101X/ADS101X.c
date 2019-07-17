/**
 * @brief       ADS101X.c
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 3.3-kSPS, 12-Bit ADCs. With Internal Reference, Oscillator, and Programmable Comparator.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "ADS101X.h"


/**
 * @brief       ADS101X_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



