/**
 * @brief       DS1624.h
 * @details     Digital Thermometer and Memory.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/January/2018
 * @version     18/January/2018    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef DS1624_H_
#define DS1624_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   DEFAULT ADDRESSES. [ 0 : GND | 1 : VDD ]
  */
typedef enum
{
    DS1624_ADDRESS_0     =   ( 0b1001 << 3 ) | 0b000,              /*!<   Address A2 A1 A0: 000                */
    DS1624_ADDRESS_1     =   ( 0b1001 << 3 ) | 0b001,              /*!<   Address A2 A1 A0: 001                */
    DS1624_ADDRESS_2     =   ( 0b1001 << 3 ) | 0b010,              /*!<   Address A2 A1 A0: 010                */
    DS1624_ADDRESS_3     =   ( 0b1001 << 3 ) | 0b011,              /*!<   Address A2 A1 A0: 011                */
    DS1624_ADDRESS_4     =   ( 0b1001 << 3 ) | 0b100,              /*!<   Address A2 A1 A0: 100                */
    DS1624_ADDRESS_5     =   ( 0b1001 << 3 ) | 0b101,              /*!<   Address A2 A1 A0: 101                */
    DS1624_ADDRESS_6     =   ( 0b1001 << 3 ) | 0b110,              /*!<   Address A2 A1 A0: 110                */
    DS1624_ADDRESS_7     =   ( 0b1001 << 3 ) | 0b111               /*!<   Address A2 A1 A0: 111                */
} DS1624_address_t;


// DS1624 Command Set
/**
  * @brief   TEMPERATURE CONVERSION COMMANDS
  */
typedef enum
{
    DS1624_READ_TEMPERATURE     =   0xAA,               /*!<  Reads last converted temperature value from temperature register  */
    DS1624_START_CONVERT_T      =   0xEE,               /*!<  Initiates temperature conversion                                  */
    DS1624_STOP_CONVERT_T       =   0x22                /*!<  Halts temperature conversion                                      */
} DS1624_temperature_conversion_commands_t;


/**
  * @brief   THERMOSTAT COMMANDS. NOTE: Writing to the EEPROM typically requires 10ms at room temperature. After issuing a write
  *                                     command, no further reads or writes should be requested for at least 10ms.
  */
typedef enum
{
    DS1624_ACCESS_MEMORY        =   0x17,               /*!<  Reads or writes to 256-byte EEPROM memory                         */
    DS1624_ACCESS_CONFIG        =   0xAC                /*!<  Reads or writes configuration data to configuration register      */
} DS1624_thermostat_commands_t;



// ACCESS CONFIG ( CONFIGURATION/STATUS REGISTER )
/**
  * @brief   BIT7: DONE
  */
typedef enum
{
    ACCESS_CONFIG_DONE_MASK                     =   ( 1 << 7 ),                 /*!<  DONE Mask                                 */
    ACCESS_CONFIG_DONE_CONVERSION_COMPLETE      =   ( 1 << 7 ),                 /*!<  Conversion complete                       */
    ACCESS_CONFIG_DONE_CONVERSION_IN_PROGRESS   =   ( 0 << 7 )                  /*!<  Conversion in progress                    */
} DS1624_access_config_done_t;


/**
  * @brief   BIT0: 1SHOT
  */
typedef enum
{
    ACCESS_CONFIG_1SHOT_MASK                                =   ( 1 << 0 ),     /*!<  1SHOT Mask                                                                        */
    ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION          =   ( 1 << 0 ),     /*!<  Perform one temperature conversion upon receipt of the Start Convert T protocol   */
    ACCESS_CONFIG_1SHOT_CONTINUOUSLY_TEMPERATURE_CONVERSION =   ( 0 << 0 )      /*!<  Perform continuously temperature conversions                                      */
} DS1624_access_config_1shot_t;



// TEMPERATURE REGISTER
/**
  * @brief   MSB BIT15: SIGN
  */
typedef enum
{
    MSB_TEMPERATURE_SIGN_BIT_MASK               =   ( 1 << 7 ),                 /*!<  Temperature sign Mask                     */
    MSB_TEMPERATURE_SIGN_BIT_POSITIVE           =   ( 0 << 7 ),                 /*!<  Temperature is POSITIVE                   */
    MSB_TEMPERATURE_SIGN_BIT_NEGATIVE           =   ( 1 << 7 )                  /*!<  Temperature is NEGATIVE                   */
} DS1624_msb_temperature_sign_bit_t;





#ifndef DS1624_VECTOR_STRUCT_H
#define DS1624_VECTOR_STRUCT_H
typedef struct
{
    uint8_t MSBTemperature;
    uint8_t LSBTemperature;
    uint8_t Control_Status_Register;

    float   Temperature;
} DS1624_vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
#define DS1624_TEMPERATURE_RESOLUTION   0.0625

typedef enum
{
    DS1624_SUCCESS                   =   0,
    DS1624_FAILURE                   =   1,

    DS1624_TIMEOUT                   =   1000
} DS1624_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
DS1624_status_t  DS1624_Init                    ( I2C_parameters_t myI2Cparameters );

/** It triggers a new temperature measurement.
      */
DS1624_status_t  DS1624_StartConvertTemperature ( I2C_parameters_t myI2Cparameters );

/** It stops the current temperature conversion.
      */
DS1624_status_t  DS1624_StopConvertTemperature  ( I2C_parameters_t myI2Cparameters );

/** It reads the last raw temperature conversion result.
      */
DS1624_status_t  DS1624_ReadRawTemperature      ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t* myRawTemperature );

/** It reads the last temperature conversion result.
      */
DS1624_status_t  DS1624_ReadTemperature         ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t* myTemperature );

/** It reads the CONFIGURATION/STATUS register.
      */
DS1624_status_t  DS1624_GetStatusRegister       ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t* myStatusRegister );

/** It sets 1SHOT/Continuous temperature conversion mode.
      */
DS1624_status_t  DS1624_SetConversionMode       ( I2C_parameters_t myI2Cparameters, DS1624_access_config_1shot_t myConversionMode );




#ifdef __cplusplus
}
#endif

#endif /* DS1624_H */
