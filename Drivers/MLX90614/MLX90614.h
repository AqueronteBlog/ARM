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



// COMMANDS
/**
  * @brief   FLAGS
  */
typedef enum
{
    FLAG_EEBUSY_HIGH    =   ( 1 << 7 ),           /*!<  The previous write/erase EEPROM access is still in progress. High active      */
    FLAG_EEBUSY_LOW     =   ( 0 << 7 ),           /*!<  The previous write/erase EEPROM access is still in progress. LOW              */
    FLAG_EE_DEAD_HIGH   =   ( 1 << 5 ),           /*!<  EEPROM double error has occurred. High active                                 */
    FLAG_EE_DEAD_LOW    =   ( 0 << 5 ),           /*!<  EEPROM double error has occurred. LOW                                         */
    FLAG_INIT_LOW       =   ( 0 << 4 ),           /*!<  POR initialization routine is still ongoing. Low active                       */
    FLAG_INIT_HIGH      =   ( 1 << 4 )            /*!<  POR initialization routine is still ongoing. HIGH                             */
} MLX90614_flags_t;


/**
  * @brief   CONFIG REGISTER 1
  */
// IIR
typedef enum
{
    CONFIGREG1_IIR_MASK =   ( 7 << 0 ),         /*!<  IIR Mask                                                                      */
    CONFIGREG1_IIR_100  =   ( 4 << 0 ),         /*!<  IIR (100%) a1=1, b1=0                                                         */
    CONFIGREG1_IIR_80   =   ( 5 << 0 ),         /*!<  IIR (80%) a1=0.8, b1=0.2                                                      */
    CONFIGREG1_IIR_67   =   ( 6 << 0 ),         /*!<  IIR (67%) a1=0.666, b1=0.333                                                  */
    CONFIGREG1_IIR_57   =   ( 7 << 0 ),         /*!<  IIR (57%) a1=0.571, b1=0.428                                                  */
    CONFIGREG1_IIR_50   =   ( 0 << 0 ),         /*!<  IIR (50%) a1=0.5, b1=0.5                                                      */
    CONFIGREG1_IIR_25   =   ( 1 << 0 ),         /*!<  IIR (25%) a1=0.25, b1=0.75                                                    */
    CONFIGREG1_IIR_17   =   ( 2 << 0 ),         /*!<  IIR (17%) a1=0.166(6), b1=0.83(3)                                             */
    CONFIGREG1_IIR_13   =   ( 3 << 0 )          /*!<  IIR (13%) a1=0.125, b1=0.875                                                  */
} MLX90614_configregister1_iir_t;


// TEMPERATURE SOURCES
typedef enum
{
    CONFIGREG1_TEMP_MASK        =   ( 3 << 4 ),     /*!<  Temp Mask                                                                 */
    CONFIGREG1_TEMP_TA_TOBJ1    =   ( 0 << 4 ),     /*!<  Ta, Tobj1                                                                 */
    CONFIGREG1_TEMP_TA_TOBJ2    =   ( 1 << 4 ),     /*!<  Ta, Tobj2                                                                 */
    CONFIGREG1_TEMP_TOBJ2       =   ( 2 << 4 ),     /*!<  Tobj2                                                                     */
    CONFIGREG1_TEMP_TOBJ1_TOBJ2 =   ( 3 << 4 )      /*!<  Tobj1, Tobj2                                                              */
} MLX90614_configregister1_temp_t;






#ifndef MLX90614_VECTOR_STRUCT_H
#define MLX90614_VECTOR_STRUCT_H
typedef struct
{
    uint16_t                        RawTA;
    uint16_t                        RawTObj1;
    uint16_t                        RawTObj2;
    uint8_t                         PEC;

    float                           TA;
    float                           TObj1;
    float                           TObj2;

    uint16_t                        ID[4];
    float                           Emissivity;
    MLX90614_configregister1_iir_t  IIR;
    MLX90614_flags_t                Flags;
    MLX90614_configregister1_temp_t TempSource;
} MLX90614_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
#define MLX90614_KELVIN_TO_CELSIUS  273.15
#define MLX90614_KELVIN_CONVERSION  0.02

// MACRO: round function
#define _MYROUND( x ) ({        \
        uint32_t aux_pre;       \
        float    aux_x;         \
                                \
        aux_x    =   (x);       \
        aux_pre  =   (x);       \
        aux_x   -=   aux_pre;   \
        aux_x   *=   10;        \
                                \
        if ( aux_x >= 5 )       \
            aux_pre++;          \
                                \
        aux_pre;                \
        })


typedef enum
{
    MLX90614_SUCCESS            =   0,
    MLX90614_FAILURE            =   1,

    MLX90614_TIMEOUT            =   2*65535,
    MLX90614_FLAG_ERROR         =   0x8000
} MLX90614_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
MLX90614_status_t  MLX90614_Init                    ( I2C_parameters_t myI2Cparameters );

/** It gets the ID numbers.
      */
MLX90614_status_t  MLX90614_GetID_Numbers           ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myID );

/** It reads the raw ambient temperature.
      */
MLX90614_status_t  MLX90614_ReadRawTA               ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTA );

/** It reads the ambient temperature in Celsius degrees.
      */
MLX90614_status_t  MLX90614_ReadTA                  ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myTA );

/** It reads the raw object 1 temperature.
      */
MLX90614_status_t  MLX90614_ReadRawTObj1            ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTObj1 );

/** It reads the object 1 temperature.
      */
MLX90614_status_t  MLX90614_ReadTObj1               ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myObj1 );

/** It reads the raw object 2 temperature.
      */
MLX90614_status_t  MLX90614_ReadRawTObj2            ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTObj2 );

/** It reads the object 2 temperature.
      */
MLX90614_status_t  MLX90614_ReadTObj2               ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myObj2 );

/** It gets the Emissivity correction coefficient.
      */
MLX90614_status_t  MLX90614_GetEmissivity           ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t* myEmissivity );

/** It sets the Emissivity correction coefficient.
      */
MLX90614_status_t  MLX90614_SetEmissivity           ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t myEmissivity );

/** It gets the IIR.
      */
MLX90614_status_t  MLX90614_GetIIR                  ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t* myIIR );

/** It sets the IIR.
      */
MLX90614_status_t  MLX90614_SetIIR                  ( I2C_parameters_t myI2Cparameters, MLX90614_configregister1_iir_t myIIR );

/** It gets the Temperature Source.
      */
MLX90614_status_t  MLX90614_GetTemperatureSource    ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t* myTempSource );

/** It sets the Temperature Source.
      */
MLX90614_status_t  MLX90614_SetTemperatureSource    ( I2C_parameters_t myI2Cparameters, MLX90614_configregister1_temp_t myTempSource );

/** It gets the FLAGS.
      */
MLX90614_status_t  MLX90614_GetFLAGS                ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t* myFlags );
