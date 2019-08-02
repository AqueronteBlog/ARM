/**
 * @brief       DHT11.c
 * @details     Temperature & humidity sensor complex with a calibrated digital signal output.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/August/2019
 * @version     01/August/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "DHT11.h"


/**
 * @brief       DHT11_Init ( I2C_parameters_t, DHT11_data_t );
 *
 * @details     [todo]It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDHT11:       Device to use.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DHT11_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        01/August/2019
 * @version     01/August/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DHT11_status_t DHT11_Init ( DHT11_data_t myDHT11  )
{
  //i2c_status_t aux =  I2C_SUCCESS;;

  //aux  =   i2c_init ( myI2Cparameters );



  if ( 0 == 0 )
  {
    return   DHT11_SUCCESS;
  }
  else
  {
    return   DHT11_FAILURE;
  }
}



