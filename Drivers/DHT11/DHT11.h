/**
 * @brief       DHT11.h
 * @details     Temperature & humidity sensor complex with a calibrated digital signal output.
 *              Header file.
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


#include "stdint.h"
#include "stdbool.h"


/**
  * @brief   DEVICE DELAYS.
  *           NOTE: Values in microseconds.
  */
typedef enum
{
    DHT11_START_SIGNAL              =   18000,         /*!<  Master: Start communication                    */
    DHT11_WAIT_FOR_SENSOR_RESPONSE  =   40             /*!<  Master: Wait for sensor response               */
} DHT11_device_delays_t;


/**
  * @brief   DEVICE BUS STATUS.
  *           NOTE: N/A.
  */
typedef enum
{
    DHT11_PIN_HIGH    =   1U,                           /*!<  Pin high                                        */
    DHT11_PIN_LOW     =   0U,                           /*!<  Pin low                                         */
    DHT11_PIN_UNKNOWN =   2U                            /*!<  Pin unknown                                     */
} DHT11_device_bus_status_t;




/**
  * @brief   ERROR STATUS. INTERNAL CONSTANTS
  */
typedef enum
{
    DHT11_SUCCESS               =   0U,   /*!<  Communication success                           */
    DHT11_FAILURE               =   1U,   /*!<  Communication failure                           */
    DHT11_DATA_CORRUPTED        =   2U    /*!<  Checksum error                                  */
} DHT11_status_t;





/**
  * @brief   TYPEDEF DEFINITIONS.
  */
/**
  * @brief   SET PIN HIGH OR LOW.
  *           NOTE: The user MUST take care of these function. Bus communication function pointer which should be 
  *                 mapped to the platform specific.
  */
typedef DHT11_status_t (*dht11_comm_out_fptr_t)( uint8_t myDHT11pin );

/**
  * @brief   READ PIN.
  *           NOTE: The user MUST take care of these function. Bus communication function pointer which should be 
  *                 mapped to the platform specific.
  */
typedef DHT11_status_t (*dht11_comm_in_fptr_t)( uint8_t myDHT11pin, DHT11_device_bus_status_t* myDHT11pinStatus );

/**
  * @brief   DEVICE DELAYS.
  *           NOTE: Delay function pointer which should be mapped to the platform specific.
  */
typedef DHT11_status_t (*dht11_delay_fptr_t)( uint32_t myDHT11delay );




#ifndef DHT11_VECTOR_STRUCT_H
#define DHT11_VECTOR_STRUCT_H
typedef struct{
    /* DHT11: Pin  */
    uint8_t                   pin;
    
    /* DHT11: Set up the pin as an output: Low status  */
    dht11_comm_out_fptr_t     dht11_set_low;

    /* DHT11: Set up the pin as an output: High status  */
    dht11_comm_out_fptr_t     dht11_set_high;

    /* DHT11: Read pin  */
    dht11_comm_in_fptr_t      dht11_read_pin;

    /* DHT11: Delay function  */
    dht11_delay_fptr_t        dht11_delay_us;
} DHT11_comm_t;


typedef struct
{
  /* Outputs  */
  float     temperature;              /*!<  Temperature value                                       */
  float     humidity;                 /*!<  Relative humidity value                                 */

  uint16_t  rawTemperature;           /*!<  Temperature raw value                                   */
  uint16_t  rawHumidity;              /*!<  Relative humidity raw value                             */

  uint8_t   checksum;                 /*!<  Checksum                                                */
} DHT11_data_t;
#endif







/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the GPIO peripheral.
  */
DHT11_status_t DHT11_Init       ( DHT11_comm_t myDHT11                          );

/** It gets the raw data: Temperature, Humidity and Checksum.
  */
DHT11_status_t DHT11_GetRawData ( DHT11_comm_t myDHT11, DHT11_data_t* myRawData );


