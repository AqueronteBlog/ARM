/**
 * @brief       TMP102.h
 * @details     Low-Power Digital Temperature Sensor With SMBus and Two-Wire Serial.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/June/2018
 * @version     9/June/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef TMP102_H_
#define TMP102_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    TMP102_ADDRESS_A0_GROUND     =   0b1001000,             /*!<   TMP102 I2C Address: A0 connected to Ground           */
    TMP102_ADDRESS_A0_VPOS       =   0b1001001,             /*!<   TMP102 I2C Address: A0 connected to V+               */
    TMP102_ADDRESS_A0_SDA        =   0b1001010,             /*!<   TMP102 I2C Address: A0 connected to SDA              */
    TMP102_ADDRESS_A0_SCL        =   0b1001011              /*!<   TMP102 I2C Address: A0 connected to SCL              */
} TMP102_addresses_t;


// REGISTERS
/**
  * @brief   REGISTERS BYTE
  */
typedef enum
{
    TMP102_TEMPERATURE_REGISTER     =   0x00,               /*!<  Temperature Register      ( Read Only  )              */
    TMP102_CONFIGURATION_REGISTER   =   0x01,               /*!<  Configuration Register    ( Read/Write )              */
    TMP102_T_LOW_REGISTER           =   0x02,               /*!<  T LOW Register            ( Read/Write )              */
    TMP102_T_HIGH_REGISTER          =   0x03                /*!<  T HIGH Register           ( Read/Write )              */
} TMP102_registers_byte_t;



// MASTER MODE
/**
  * @brief   MEASUREMENT RESOLUTION
  */
typedef enum
{
    TMP102_HOLD_MASTER_MODE                 =   0x01,           /*!<  TMP102 HOLD MASTER MODE enabled                       */
    TMP102_NO_HOLD_MASTER_MODE              =   0x00            /*!<  TMP102 NO HOLD MASTER MODE enabled                    */
} TMP102_master_mode_t;



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
    TMP102_RESOLUTION_MASK                  =   0x81,           /*!<  TMP102 Measurement Resolution                         */
    TMP102_RESOLUTION_RH_12_TEMP_14         =   0x00,           /*!<  TMP102 12b RH 14b Temp.                               */
    TMP102_RESOLUTION_RH_8_TEMP_12          =   0x01,           /*!<  TMP102 9b  RH 12b Temp.                               */
    TMP102_RESOLUTION_RH_10_TEMP_13         =   0x80,           /*!<  TMP102 10b RH 13b Temp.                               */
    TMP102_RESOLUTION_RH_11_TEMP_11         =   0x81            /*!<  TMP102 11b RH 11b Temp.                               */
} TMP102_measurement_resolution_t;



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
    TMP102_VDDS_STATUS_MASK                 =   0x40,           /*!<  TMP102 VDD mask.                                      */
    TMP102_VDDS_STATUS_VDD_OK               =   ( 0 << 6 ),     /*!<  VDD OK.                                               */
    TMP102_VDDS_STATUS_VDD_LOW              =   ( 1 << 6 )      /*!<  VDD Low.                                              */
} TMP102_vdds_status_t;



/**
  * @brief   HTRE
  */
typedef enum
{
    TMP102_HTRE_MASK                        =   0x03,           /*!<  TMP102 HTRE Mask                                   */
    TMP102_HTRE_ENABLED                     =   ( 1 << 2 ),     /*!<  TMP102 On-chip Heater Enable                          */
    TMP102_HTRE_DISABLED                    =   ( 0 << 2 )      /*!<  TMP102 On-chip Heater Disable                         */
} TMP102_heater_t;






#ifndef TMP102_VECTOR_STRUCT_H
#define TMP102_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint32_t ElectronicSerialNumber_LSB;
    uint32_t ElectronicSerialNumber_MSB;

    uint8_t  FirmwareRevision;
    uint8_t  BatteryStatus;
} TMP102_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    TMP102_SUCCESS     =       0,
    TMP102_FAILURE     =       1
} TMP102_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
TMP102_status_t  TMP102_Init                        ( I2C_parameters_t myI2Cparameters );

/** It configures the device: resolution and heater.
  */
TMP102_status_t  TMP102_Conf                        ( I2C_parameters_t myI2Cparameters, TMP102_measurement_resolution_t myResolution, TMP102_heater_t myHeater );

/** It performs a software reset.
  */
TMP102_status_t  TMP102_SoftReset                   ( I2C_parameters_t myI2Cparameters );

/** It gets the electronic serial number.
  */
TMP102_status_t  TMP102_GetElectronicSerialNumber   ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* mySerialNumber );

/** It gets the firmware revision.
  */
TMP102_status_t  TMP102_GetFirmwareRevision         ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myFirmwareRevision );

/** It sets the heater current.
*/
TMP102_status_t  TMP102_SetHeaterCurrent            ( I2C_parameters_t myI2Cparameters, uint8_t myHeaterCurrent );

/** It performs a new temperature measurement.
  */
TMP102_status_t  TMP102_TriggerTemperature          ( I2C_parameters_t myI2Cparameters, TMP102_master_mode_t myMode );

/** It read the temperature.
  */
TMP102_status_t  TMP102_ReadTemperature             ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperature );

/** It reads the raw data from temperature.
  */
TMP102_status_t  TMP102_ReadRawTemperature          ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperature );

/** It reads the raw temperature data after a relative humidity measurement was done.
  */
TMP102_status_t  TMP102_ReadRawTemperatureFromRH    ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperature );

/** It reads the temperature after a relative humidity measurement was done.
  */
TMP102_status_t  TMP102_ReadTemperatureFromRH       ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperature );

/** It performs a new relative humidity measurement.
  */
TMP102_status_t  TMP102_TriggerHumidity             ( I2C_parameters_t myI2Cparameters, TMP102_master_mode_t myMode );

/** It reads the relative humidity.
  */
TMP102_status_t  TMP102_ReadHumidity                ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myHumidity );

/** It reads the raw data from relative humidity.
  */
TMP102_status_t  TMP102_ReadRawHumidity             ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myHumidity );

/** It gets the battery status.
  */
TMP102_status_t  TMP102_GetBatteryStatus            ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myBatteryStatus );


#ifdef __cplusplus
}
#endif

#endif /* TMP102_H */
