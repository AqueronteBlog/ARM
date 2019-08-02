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





#ifndef DHT11_VECTOR_STRUCT_H
#define DHT11_VECTOR_STRUCT_H
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
  * @brief   ERROR STATUS. INTERNAL CONSTANTS
  */
typedef enum
{
    DHT11_SUCCESS               =   0U,   /*!<  Communication success                           */
    DHT11_FAILURE               =   1U,   /*!<  Communication failure                           */
    DHT11_DATA_CORRUPTED        =   2U    /*!<  Checksum error                                  */
} DHT11_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
//DHT11_status_t DHT11_Init                   ( I2C_parameters_t myI2Cparameters, DHT11_data_t myDHT11  );




