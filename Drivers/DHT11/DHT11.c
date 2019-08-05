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
 * @brief       DHT11_Init ( DHT11_comm_t myDHT11 )
 *
 * @details     It configures the GPIO for the DHT11 device. Output pin and high output ( bus released )
 *
 * @param[in]    myDHT11: GPIO parameters for this device.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DHT11_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        01/August/2019
 * @version     02/August/2019   [todo]
 *              01/August/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DHT11_status_t DHT11_Init ( DHT11_comm_t myDHT11 )
{
  DHT11_status_t aux =  DHT11_SUCCESS;

  //aux  =   i2c_init ( myI2Cparameters );



  return  aux;
}



