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
 * @details     It sets the pin 'high' level to release the bus.
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
 * @version     06/August/2019   The bus is released when the pin is 'High'.
 *              01/August/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DHT11_status_t DHT11_Init ( DHT11_comm_t myDHT11 )
{
  DHT11_status_t aux =  DHT11_SUCCESS;
  
  aux |=   myDHT11.dht11_set_high ( myDHT11.pin );



  return  aux;
}



/**
 * @brief       DHT11_GetRawData ( DHT11_comm_t myDHT11 , DHT11_data_t* )
 *
 * @details     It gets the raw data: Temperature, Humidity and Checksum.
 *
 * @param[in]    myDHT11: GPIO parameters for this device.
 *
 * @param[out]   myRawData: Raw data: Temperature, Humidity and Checksum.
 *
 *
 * @return       Status of DHT11_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        06/August/2019
 * @version     06/August/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DHT11_status_t DHT11_GetRawData ( DHT11_comm_t myDHT11, DHT11_data_t* myRawData )
{
  DHT11_device_bus_status_t* pinStatus;
  DHT11_status_t             aux       =  DHT11_SUCCESS;
  
  /* The communication starts with the bus on 'high' level   */
  aux |=   myDHT11.dht11_set_high ( myDHT11.pin );

  /* 1. MCU sends a start signal  */
  aux |=   myDHT11.dht11_set_low ( myDHT11.pin );
  aux |=   myDHT11.dht11_delay_us ( DHT11_START_SIGNAL );
  
  /* 2. MCU waits for DHT11 response   */
  aux |=   myDHT11.dht11_set_high ( myDHT11.pin );
  
  *pinStatus   =   DHT11_PIN_UNKNOWN;
  do{
    aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &(*pinStatus) );
  }while ( *pinStatus == ( DHT11_PIN_HIGH << myDHT11.pin ) );


  return  aux;
}

