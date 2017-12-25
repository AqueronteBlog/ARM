/**
 * @brief       MLX90614.h
 * @details     Single and Dual Zone Infra Red Thermometer.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        23/December/2017
 * @version     23/December/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES.
  */
typedef enum
{
    MLX90614_ADDRESS     =   0x5A                   /*!<   Address                                            */
} MLX90614_address_t;


// COMMANDS
/**
  * @brief   COMMANDS
  */
typedef enum
{
    MLX90614_RAM_ACCESS     =   0b00011111,         /*!<  Seconds. RANGE 00-59                                  */
    MLX90614_EEPROM_ACCESS  =   0b00100000,         /*!<  LSB of Temp                                           */
    MLX90614_FLAGS          =   0b11110000,         /*!<  LSB of Temp                                           */
    MLX90614_SLEEP          =   0b11111111          /*!<  LSB of Temp                                           */
} MLX90614_command_t;


// REGISTERS
/**
  * @brief   EEPROM REGISTERS
  */
typedef enum
{
    MLX90614_TO_MAX                             =   ( MLX90614_EEPROM_ACCESS | 0x00  ),   /*!<  To max                              */
    MLX90614_TO_MIN                             =   ( MLX90614_EEPROM_ACCESS | 0x01  ),   /*!<  To min                              */
    MLX90614_PWMCTRL                            =   ( MLX90614_EEPROM_ACCESS | 0x02  ),   /*!<  PWMCTRL                             */
    MLX90614_TA_RANGE                           =   ( MLX90614_EEPROM_ACCESS | 0x03  ),   /*!<  Ta range                            */
    MLX90614_EMISSIVITY_CORRECTION_COEFFICIENT  =   ( MLX90614_EEPROM_ACCESS | 0x04  ),   /*!<  Emissivity correction coefficient   */
    MLX90614_CONFIG_REGISTER_1                  =   ( MLX90614_EEPROM_ACCESS | 0x05  ),   /*!<  Config Register1                    */
    MLX90614_SMBUS_ADDRESS                      =   ( MLX90614_EEPROM_ACCESS | 0x0E  ),   /*!<  SMBus address (LSByte only)         */
    MLX90614_ID_NUMBER_0                        =   ( MLX90614_EEPROM_ACCESS | 0x0C  ),   /*!<  ID number                           */
    MLX90614_ID_NUMBER_1                        =   ( MLX90614_EEPROM_ACCESS | 0x0D  ),   /*!<  ID number                           */
    MLX90614_ID_NUMBER_2                        =   ( MLX90614_EEPROM_ACCESS | 0x0E  ),   /*!<  ID number                           */
    MLX90614_ID_NUMBER_3                        =   ( MLX90614_EEPROM_ACCESS | 0x0F  )    /*!<  ID number                           */
} MLX90614_eeprom_registers_t;


/**
  * @brief   RAM REGISTERS
  */
typedef enum
{
    MLX90614_RAW_DATA_IR_CHANNEL_1              =   ( MLX90614_RAM_ACCESS & 0x04  ),    /*!<  Raw data IR channel 1                 */
    MLX90614_RAW_DATA_IR_CHANNEL_2              =   ( MLX90614_RAM_ACCESS & 0x05  ),    /*!<  Raw data IR channel 2                 */
    MLX90614_TA                                 =   ( MLX90614_RAM_ACCESS & 0x06  ),    /*!<  TA                                    */
    MLX90614_TOBJ_1                             =   ( MLX90614_RAM_ACCESS & 0x07  ),    /*!<  TOBJ 1                                */
    MLX90614_TOBJ_2                             =   ( MLX90614_RAM_ACCESS & 0x08  )     /*!<  TOBJ 2                                */
} MLX90614_ram_registers_t;







#ifndef MLX90614_VECTOR_STRUCT_H
#define MLX90614_VECTOR_STRUCT_H
typedef struct
{
    uint16_t RawTA;
    uint16_t RawTObj1;
    uint16_t RawTObj2;
    uint8_t  PEC;

    float    TA;
    float    TObj1;
    float    TObj2;

    uint16_t ID[4];
} MLX90614_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
#define MLX90614_KELVIN_TO_CELSIUS  273.15
#define MLX90614_KELVIN_CONVERSION  0.02

typedef enum
{
    MLX90614_SUCCESS            =   0,
    MLX90614_FAILURE            =   1,

    MLX90614_FLAG_ERROR         =   0x8000
} MLX90614_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
MLX90614_status_t  MLX90614_Init            ( I2C_parameters_t myI2Cparameters );

/** It gets the ID numbers.
      */
MLX90614_status_t  MLX90614_GetID_Numbers   ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myID );

/** It reads the raw ambient temperature.
      */
MLX90614_status_t  MLX90614_ReadRawTA       ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTA );

/** It reads the ambient temperature in Celsius degrees.
      */
MLX90614_status_t  MLX90614_ReadRawTA       ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myTA );

/** It reads the raw object 1 temperature.
      */
MLX90614_status_t  MLX90614_ReadRawTObj1    ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTObj1 );

/** It reads the object 1 temperature.
      */
MLX90614_status_t  MLX90614_ReadTObj1       ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myObj1 );

/** It reads the raw object 2 temperature.
      */
MLX90614_status_t  MLX90614_ReadRawTObj2    ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTObj2 );

/** It reads the object 2 temperature.
      */
MLX90614_status_t  MLX90614_ReadTObj2       ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myObj2 );

