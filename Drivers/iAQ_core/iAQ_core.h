/**
 * @brief       iAQ_Core.h
 * @details     Indoor air quality module, I2C interface.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/May/2018
 * @version     31/May/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef iAQ_Core_H_
#define iAQ_Core_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   DEFAULT ADDRESSES.
  */
typedef enum
{
    iAQ_Core_ADDRESS     =   0x5A                         /*!<   Address for iAQ_Core                */
} iAQ_Core_address_t;


// iAQ_Core DATA. NOTE: The I2C master can request up to 9 bytes.
/**
  * @brief   DATA POSITION
  */
typedef enum
{
    iAQ_Core_PREDICTION     =   0xFF0000000,               /*!<  Information Structure ( Prediction )                              */
    iAQ_Core_STATUS_FLAG    =   0x00F000000,               /*!<  Information Structure ( Status Flag )                             */
    iAQ_Core_RESIATNCE      =   0x0000FFF00,               /*!<  Information Structure ( Resistance )                              */
    iAQ_Core_TVOC           =   0x0000000FF                /*!<  Information Structure ( TVOC )                                    */
} iAQ_Core_data_position_t;


/**
  * @brief   STATUS FLAG. NOTE: If status is OK the data is valid. If the status is BUSY, the data integrity is not guaranteed for
  *                             variables of size > 8 bits, because the module may be updating a part of the variable. If the status
  *                             is ERROR constantly (or very frequently) this indicates that the module is reading non-realistic values,
  *                             and the sensor element is probably defective.
  */
typedef enum
{
    iAQ_Core_STATUS_OK        =   0x00,                     /*!<  Status Flag: OK                                                   */
    iAQ_Core_STATUS_BUSY      =   0x01,                     /*!<  Status Flag: OK                                                   */
} iAQ_Core_thermostat_commands_t;



// ACCESS CONFIG ( CONFIGURATION/STATUS REGISTER )
/**
  * @brief   BIT7: DONE
  */
typedef enum
{
    ACCESS_CONFIG_DONE_MASK                     =   ( 1 << 7 ),                 /*!<  DONE Mask                                 */
    ACCESS_CONFIG_DONE_CONVERSION_COMPLETE      =   ( 1 << 7 ),                 /*!<  Conversion complete                       */
    ACCESS_CONFIG_DONE_CONVERSION_IN_PROGRESS   =   ( 0 << 7 )                  /*!<  Conversion in progress                    */
} iAQ_Core_access_config_done_t;


/**
  * @brief   BIT0: 1SHOT
  */
typedef enum
{
    ACCESS_CONFIG_1SHOT_MASK                                =   ( 1 << 0 ),     /*!<  1SHOT Mask                                                                        */
    ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION          =   ( 1 << 0 ),     /*!<  Perform one temperature conversion upon receipt of the Start Convert T protocol   */
    ACCESS_CONFIG_1SHOT_CONTINUOUSLY_TEMPERATURE_CONVERSION =   ( 0 << 0 )      /*!<  Perform continuously temperature conversions                                      */
} iAQ_Core_access_config_1shot_t;



// TEMPERATURE REGISTER
/**
  * @brief   MSB BIT15: SIGN
  */
typedef enum
{
    MSB_TEMPERATURE_SIGN_BIT_MASK               =   ( 1 << 7 ),                 /*!<  Temperature sign Mask                     */
    MSB_TEMPERATURE_SIGN_BIT_POSITIVE           =   ( 0 << 7 ),                 /*!<  Temperature is POSITIVE                   */
    MSB_TEMPERATURE_SIGN_BIT_NEGATIVE           =   ( 1 << 7 )                  /*!<  Temperature is NEGATIVE                   */
} iAQ_Core_msb_temperature_sign_bit_t;





#ifndef iAQ_Core_VECTOR_STRUCT_H
#define iAQ_Core_VECTOR_STRUCT_H
typedef struct
{
    uint16_t pred;                              /*!<  Prediction (CO2 eq. ppm),  Typical Value: 450                     */
    uint8_t  status;                            /*!<  Status,                    Typical Value: 0                       */
    uint8_t  resistance;                        /*!<  Sensor resistance [Ohm],   Typical Value: 256431                  */
    uint16_t Tvoc;                              /*!<  Prediction (TVOC eq. ppb), Typical Value: 125                     */
} iAQ_Core_vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    iAQ_Core_SUCCESS                   =   0,
    iAQ_Core_FAILURE                   =   1,
} iAQ_Core_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
iAQ_Core_status_t iAQ_Core_Init                        ( I2C_parameters_t myI2Cparameters );

/** It triggers a new temperature measurement.
      */
iAQ_Core_status_t iAQ_Core_StartConvertTemperature     ( I2C_parameters_t myI2Cparameters );

/** It stops the current temperature conversion.
      */
iAQ_Core_status_t iAQ_Core_StopConvertTemperature      ( I2C_parameters_t myI2Cparameters );

/** It reads the last raw temperature conversion result.
      */
iAQ_Core_status_t iAQ_Core_ReadRawTemperature          ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myRawTemperature );

/** It reads the last temperature conversion result.
      */
iAQ_Core_status_t iAQ_Core_ReadTemperature             ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myTemperature );

/** It reads the CONFIGURATION/STATUS register.
      */
iAQ_Core_status_t iAQ_Core_GetStatusRegister           ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myStatusRegister );

/** It sets 1SHOT/Continuous temperature conversion mode.
      */
iAQ_Core_status_t iAQ_Core_SetConversionMode           ( I2C_parameters_t myI2Cparameters, iAQ_Core_access_config_1shot_t myConversionMode );

/** It checks if a temperature conversion is done.
      */
iAQ_Core_status_t iAQ_Core_IsTemperatureConversionDone ( I2C_parameters_t myI2Cparameters, iAQ_Core_access_config_done_t* myTemperatureConversionStatus );

/** It reads a certain number of bytes from EEPROM memory.
      */
iAQ_Core_status_t iAQ_Core_ReadBytesEEPROM             ( I2C_parameters_t myI2Cparameters, uint8_t myStartingAddress, uint8_t* myReadBytesEEPROM, uint8_t myLength );

/** It writes a certain number of bytes to EEPROM memory.
      */
iAQ_Core_status_t iAQ_Core_WriteBytesEEPROM            ( I2C_parameters_t myI2Cparameters, uint8_t myStartingAddress, uint8_t myWriteBytesEEPROM[], uint8_t myLength );



#ifdef __cplusplus
}
#endif

#endif /* iAQ_Core_H */
