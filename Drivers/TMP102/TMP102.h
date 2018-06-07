/**
 * @brief       SI7021.h
 * @details     I2C HUMIDITY AND TEMPERATURE SENSOR.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/February/2018
 * @version     5/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    SI7021_ADDRESS     =   0x40                                                         /*!<   SI7021 I2C Address                                   */
} SI7021_address_t;


// REGISTERS
/**
  * @brief   COMMAND CODE
  */
typedef enum
{
    SI7021_MEASURE_RELATIVE_HUMIDITY_HOLD_MASTER_MODE           =   0xE5,               /*!<  Measure Relative Humidity, Hold Master Mode           */
    SI7021_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE        =   0xF5,               /*!<  Measure Relative Humidity, No Hold Master Mode        */
    SI7021_MEASURE_TEMPERATURE_HOLD_MASTER_MODE                 =   0xE3,               /*!<  Measure Temperature, Hold Master Mode                 */
    SI7021_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE              =   0xF3,               /*!<  Measure Temperature, No Hold Master Mode              */
    SI7021_READ_TEMPERATURE_VALUE_FROM_PREVIOUS_RH_MEASUREMENT  =   0xE0,               /*!<  Read Temperature Value from Previous RH Measurement   */
    SI7021_RESET                                                =   0xFE,               /*!<  Reset                                                 */
    SI7021_WRITE_RH_T_USER_REGISTER_1                           =   0xE6,               /*!<  Write RH/T User Register 1                            */
    SI7021_READ_RH_T_USER_REGISTER_1                            =   0xE7,               /*!<  Read RH/T User Register 1                             */
    SI7021_WRITE_HEATER_CONTROL_REGISTER                        =   0x51,               /*!<  Write Heater Control Register                         */
    SI7021_READ_HEATER_CONTROL_REGISTER                         =   0x11,               /*!<  Read Heater Control Register                          */
    SI7021_READ_ELECTRONIC_ID_FIRST_BYTE_CMD1                   =   0xFA,               /*!<  Read Electronic ID 1st Byte                           */
    SI7021_READ_ELECTRONIC_ID_FIRST_BYTE_CMD2                   =   0x0F,               /*!<  Read Electronic ID 1st Byte                           */
    SI7021_READ_ELECTRONIC_ID_SECOND_BYTE_CMD1                  =   0xFC,               /*!<  Read Electronic ID 2nd Byte                           */
    SI7021_READ_ELECTRONIC_ID_SECOND_BYTE_CMD2                  =   0xC9,               /*!<  Read Electronic ID 2nd Byte                           */
    SI7021_READ_FIRMWARE_VERSION_CMD1                           =   0x84,               /*!<  Read Firmware Revision                                */
    SI7021_READ_FIRMWARE_VERSION_CMD2                           =   0xB8                /*!<  Read Firmware Revision                                */
} SI7021_command_code_t;



// MASTER MODE
/**
  * @brief   MEASUREMENT RESOLUTION
  */
typedef enum
{
    SI7021_HOLD_MASTER_MODE                 =   0x01,           /*!<  SI7021 HOLD MASTER MODE enabled                       */
    SI7021_NO_HOLD_MASTER_MODE              =   0x00            /*!<  SI7021 NO HOLD MASTER MODE enabled                    */
} SI7021_master_mode_t;



// USER REGISTER 1
/*
    NOTE:   Reset Settings = 0011_1010.
            Except where noted, reserved register bits will always read back as '1' and are not affected by write operations. For
            future compatibility, it is recommended that prior to a write operation, registers should be read. Then the values read
            from the RSVD bits should be written back unchanged during the write operation.
*/
/**
  * @brief   MEASUREMENT RESOLUTION
  */
typedef enum
{
    SI7021_RESOLUTION_MASK                  =   0x81,           /*!<  SI7021 Measurement Resolution                         */
    SI7021_RESOLUTION_RH_12_TEMP_14         =   0x00,           /*!<  SI7021 12b RH 14b Temp.                               */
    SI7021_RESOLUTION_RH_8_TEMP_12          =   0x01,           /*!<  SI7021 9b  RH 12b Temp.                               */
    SI7021_RESOLUTION_RH_10_TEMP_13         =   0x80,           /*!<  SI7021 10b RH 13b Temp.                               */
    SI7021_RESOLUTION_RH_11_TEMP_11         =   0x81            /*!<  SI7021 11b RH 11b Temp.                               */
} SI7021_measurement_resolution_t;



/**
  * @brief   VDDS
  */
/*
    NOTE:   The minimum recommended operating voltage is 1.9 V. A transition
            of the VDD status bit from 0 to 1 indicates that VDD is
            between 1.8 V and 1.9 V. If the VDD drops below 1.8 V, the
            device will no longer operate correctly.
*/
typedef enum
{
    SI7021_VDDS_STATUS_MASK                 =   0x40,           /*!<  SI7021 VDD mask.                                      */
    SI7021_VDDS_STATUS_VDD_OK               =   ( 0 << 6 ),     /*!<  VDD OK.                                               */
    SI7021_VDDS_STATUS_VDD_LOW              =   ( 1 << 6 )      /*!<  VDD Low.                                              */
} SI7021_vdds_status_t;



/**
  * @brief   HTRE
  */
typedef enum
{
    SI7021_HTRE_MASK                        =   0x03,           /*!<  SI7021 HTRE Mask                                   */
    SI7021_HTRE_ENABLED                     =   ( 1 << 2 ),     /*!<  SI7021 On-chip Heater Enable                          */
    SI7021_HTRE_DISABLED                    =   ( 0 << 2 )      /*!<  SI7021 On-chip Heater Disable                         */
} SI7021_heater_t;






#ifndef SI7021_VECTOR_STRUCT_H
#define SI7021_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint32_t ElectronicSerialNumber_LSB;
    uint32_t ElectronicSerialNumber_MSB;

    uint8_t  FirmwareRevision;
    uint8_t  BatteryStatus;
} SI7021_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SI7021_SUCCESS     =       0,
    SI7021_FAILURE     =       1
} SI7021_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SI7021_status_t  SI7021_Init                        ( I2C_parameters_t myI2Cparameters );

/** It configures the device: resolution and heater.
  */
SI7021_status_t  SI7021_Conf                        ( I2C_parameters_t myI2Cparameters, SI7021_measurement_resolution_t myResolution, SI7021_heater_t myHeater );

/** It performs a software reset.
  */
SI7021_status_t  SI7021_SoftReset                   ( I2C_parameters_t myI2Cparameters );

/** It gets the electronic serial number.
  */
SI7021_status_t  SI7021_GetElectronicSerialNumber   ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* mySerialNumber );

/** It gets the firmware revision.
  */
SI7021_status_t  SI7021_GetFirmwareRevision         ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myFirmwareRevision );

/** It sets the heater current.
*/
SI7021_status_t  SI7021_SetHeaterCurrent            ( I2C_parameters_t myI2Cparameters, uint8_t myHeaterCurrent );

/** It performs a new temperature measurement.
  */
SI7021_status_t  SI7021_TriggerTemperature          ( I2C_parameters_t myI2Cparameters, SI7021_master_mode_t myMode );

/** It read the temperature.
  */
SI7021_status_t  SI7021_ReadTemperature             ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myTemperature );

/** It reads the raw data from temperature.
  */
SI7021_status_t  SI7021_ReadRawTemperature          ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myTemperature );

/** It reads the raw temperature data after a relative humidity measurement was done.
  */
SI7021_status_t  SI7021_ReadRawTemperatureFromRH    ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myTemperature );

/** It reads the temperature after a relative humidity measurement was done.
  */
SI7021_status_t  SI7021_ReadTemperatureFromRH       ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myTemperature );

/** It performs a new relative humidity measurement.
  */
SI7021_status_t  SI7021_TriggerHumidity             ( I2C_parameters_t myI2Cparameters, SI7021_master_mode_t myMode );

/** It reads the relative humidity.
  */
SI7021_status_t  SI7021_ReadHumidity                ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myHumidity );

/** It reads the raw data from relative humidity.
  */
SI7021_status_t  SI7021_ReadRawHumidity             ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myHumidity );

/** It gets the battery status.
  */
SI7021_status_t  SI7021_GetBatteryStatus            ( I2C_parameters_t myI2Cparameters, SI7021_vector_data_t* myBatteryStatus );
