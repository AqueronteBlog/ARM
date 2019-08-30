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
 * @param[in]    myDHT11:   GPIO parameters for this device.
 *
 * @param[out]   myRawData: Raw data: Temperature, Humidity and Checksum.
 *
 *
 * @return       Status of DHT11_GetRawData.
 *
 *
 * @author      Manuel Caballero
 * @date        06/August/2019
 * @version     08/August/2019   Timeout was added.
 *              06/August/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DHT11_status_t DHT11_GetRawData ( DHT11_comm_t myDHT11, DHT11_data_t* myRawData )
{
  uint8_t                   auxChecksum  =  0U;
  uint8_t                   countData    =  0U;
  uint64_t                  rawAuxData   =  0UL;
  uint32_t                  timeoutDHT11 =  0UL;
  DHT11_device_bus_status_t pinStatus    =  DHT11_PIN_UNKNOWN;
  DHT11_status_t            aux          =  DHT11_SUCCESS;
  
  /* The communication starts with the bus on 'high' level   */
  aux |=   myDHT11.dht11_set_high ( myDHT11.pin );

  /* 1. MCU sends a start signal  */
  aux |=   myDHT11.dht11_set_low ( myDHT11.pin );
  aux |=   myDHT11.dht11_delay_us ( DHT11_START_SIGNAL );
  
  /* 2. MCU waits for DHT11 response   */
  aux |=   myDHT11.dht11_set_high ( myDHT11.pin );
  
  pinStatus      =   DHT11_PIN_UNKNOWN;
  timeoutDHT11   =   DHT11_TIMEOUT;
  do{
    aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &pinStatus );
    timeoutDHT11--;
  }while ( ( pinStatus == DHT11_PIN_HIGH ) && ( timeoutDHT11 > 0UL ) );
  
  /* If timeout means that the device does not work properly, it may be stuck  */
  if ( timeoutDHT11 == 0UL )
  {
    return  DHT11_BUS_TIMEOUT;
  }
  
  /* 3. DHT11 sends out response signal  */
  pinStatus      =   DHT11_PIN_UNKNOWN;
  timeoutDHT11   =   DHT11_TIMEOUT;
  do{
    aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &pinStatus );
    timeoutDHT11--;
  }while ( ( pinStatus == DHT11_PIN_LOW ) && ( timeoutDHT11 > 0UL ) );
  
  /* If timeout means that the device does not work properly, it may be stuck  */
  if ( timeoutDHT11 == 0UL )
  {
    return  DHT11_BUS_TIMEOUT;
  }

  pinStatus      =   DHT11_PIN_UNKNOWN;
  timeoutDHT11   =   DHT11_TIMEOUT;
  do{
    aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &pinStatus );
    timeoutDHT11--;
  }while ( ( pinStatus == DHT11_PIN_HIGH ) && ( timeoutDHT11 > 0UL ) );
  
  /* If timeout means that the device does not work properly, it may be stuck  */
  if ( timeoutDHT11 == 0UL )
  {
    return  DHT11_BUS_TIMEOUT;
  }

  /* 4. DHT11 sends output data  */
  for ( countData = 0U; countData < 40U; countData++ )
  {
    /* Next bit  */
    rawAuxData <<=   1UL;
    
    /* 4.1. DHT11 starts transmit 1-bit   */
    pinStatus      =   DHT11_PIN_UNKNOWN;
    timeoutDHT11   =   DHT11_TIMEOUT;
    do{
      aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &pinStatus );
      timeoutDHT11--;
    }while ( ( pinStatus == DHT11_PIN_LOW ) && ( timeoutDHT11 > 0UL ) );
    
    /* If timeout means that the device does not work properly, it may be stuck  */
    if ( timeoutDHT11 == 0UL )
    {
      return  DHT11_BUS_TIMEOUT;
    }

    /* 4.2. MCU wait for sampling data   */
    aux |=   myDHT11.dht11_delay_us ( DHT11_SAMPLE_DATA );

    /* 4.3. MCU samples data   */
    pinStatus   =   DHT11_PIN_UNKNOWN;
    aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &pinStatus );
    if ( pinStatus == DHT11_PIN_LOW )
    {
      /* Data means '0'   */
      rawAuxData  |=   0UL;
    }
    else
    {
      /* Data means '1'  */
      rawAuxData  |=   1UL;

      /* Wait fpr sync   */
      pinStatus      =   DHT11_PIN_UNKNOWN;
      timeoutDHT11   =   DHT11_TIMEOUT;
      do{
        aux |=   myDHT11.dht11_read_pin ( myDHT11.pin, &pinStatus );
        timeoutDHT11--;
      }while ( ( pinStatus == DHT11_PIN_HIGH ) && ( timeoutDHT11 > 0UL ) );

      /* If timeout means that the device does not work properly, it may be stuck  */
      if ( timeoutDHT11 == 0UL )
      {
        return  DHT11_BUS_TIMEOUT;
      }
    }
  }

  
  /* Parse data  */
  myRawData->rawHumidity     =   (uint16_t)( ( rawAuxData & 0xFFFF000000 ) >> 24U );
  myRawData->rawTemperature  =   (uint16_t)( ( rawAuxData & 0x0000FFFF00 ) >> 8U );
  myRawData->checksum        =   (uint8_t)( rawAuxData & 0x00000000FF );

  /* Check checksum  */
  auxChecksum  =   (uint8_t)( ( ( myRawData->rawHumidity & 0xFF00 ) >> 8U ) + ( myRawData->rawHumidity & 0x00FF ) + ( ( myRawData->rawTemperature & 0xFF00 ) >> 8U ) ) + ( myRawData->rawTemperature & 0x00FF );
  if ( auxChecksum == myRawData->checksum )
  {
    myRawData->checksumStatus   =   DHT11_CHECKSUM_OK;
  }
  else
  {
    myRawData->checksumStatus   =   DHT11_CHECKSUM_ERROR;
  }



  if ( myRawData->checksumStatus == DHT11_CHECKSUM_ERROR )
  {
    return  DHT11_DATA_CORRUPTED;
  }
  else
  {
    return  aux;
  }
}



/**
 * @brief       DHT11_GetData ( DHT11_comm_t myDHT11 , DHT11_data_t* )
 *
 * @details     It gets the current data: Temperature, Humidity and Checksum.
 *
 * @param[in]    myDHT11: GPIO parameters for this device.
 *
 * @param[out]   myData:  Current data: Temperature, Humidity and Checksum.
 *
 *
 * @return       Status of DHT11_GetData.
 *
 *
 * @author      Manuel Caballero
 * @date        06/August/2019
 * @version     08/August/2019   Unneccessary code was removed.
 *              06/August/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DHT11_status_t DHT11_GetData ( DHT11_comm_t myDHT11, DHT11_data_t* myData )
{
  uint8_t        auxChecksum  =  0U;
  DHT11_status_t aux          =  DHT11_SUCCESS;
  
  /* Get the raw data to be processed   */
  aux |=   DHT11_GetRawData ( myDHT11, &(*myData) );

  /* Parse the data  */
  myData->humidity     =   (uint8_t)( myData->rawHumidity >> 8U );
  myData->temperature  =   (uint8_t)( myData->rawTemperature >> 8U );
  
  
  return  aux;
}

