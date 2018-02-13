/**
 * @brief       BME680.h
 * @details     Low power gas, pressure, temperature & humidity sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/February/2018
 * @version     13/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef BME680_H_
#define BME680_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   DEFAULT ADDRESSES. NOTE: The SDO pin cannot be left floating, if left floating, the
  *                                   I2C address will be undefined.
  */
typedef enum
{
    BME680_ADDRESS_SDO_TO_GND     =   0x76,         /*!<   BME680 I2C Address: SDO connected to GND         */
    BME680_ADDRESS_SDO_TO_VDD     =   0x77          /*!<   BME680 I2C Address: SDO connected to VDD         */
} BME680_address_t;


// REGISTERS
/**
  * @brief   REGISTERS: MEMORY MAP
  */
typedef enum
{
    BME680_STATUS           =   0x73,               /*!<  Selects memory map page in SPI mode               */
    BME680_RESET            =   0xE0,               /*!<  Soft-reset register                               */
    BME680_ID               =   0xD0,               /*!<  Chip ID                                           */
    BME680_CONFIG           =   0x75,               /*!<  IIR filter control                                */
    BME680_CTRL_MEAS        =   0x74,               /*!<  Oversampling setting for temperature and pressure */
    BME680_CTRL_HUM         =   0x72,               /*!<  Humidity sensor over sampling control             */
    BME680_CTRL_GAS_1       =   0x71,               /*!<  Heater  profile selection                         */
    BME680_CTRL_GAS_0       =   0x70,               /*!<  Heater off                                        */
    BME680_GAS_WAIT_9       =   0x6D,               /*!<  Gas sensor wait time                              */
    BME680_GAS_WAIT_0       =   0x64,               /*!<  Gas sensor wait time                              */
    BME680_RES_HEAT_9       =   0x63,               /*!<  Target heater resistance                          */
    BME680_RES_HEAT_0       =   0x5A,               /*!<  Target heater resistance                          */
    BME680_IDAC_HEAT_9      =   0x59,               /*!<  Heater current                                    */
    BME680_IDAC_HEAT_0      =   0x50,               /*!<  Heater current                                    */
    BME680_GAS_R_LSB        =   0x2B,               /*!<  Gas resistance data                               */
    BME680_GAS_R_MSB        =   0x2A,               /*!<  Gas resistance data                               */
    BME680_HUM_LSB          =   0x26,               /*!<  Humidity data                                     */
    BME680_HUM_MSB          =   0x25,               /*!<  Humidity data                                     */
    BME680_TEMP_XLSB        =   0x24,               /*!<  Temperature data                                  */
    BME680_TEMP_LSB         =   0x23,               /*!<  Temperature data                                  */
    BME680_TEMP_MSB         =   0x22,               /*!<  Temperature data                                  */
    BME680_PRESS_XLSB       =   0x21,               /*!<  Pressure data                                     */
    BME680_PRESS_LSB        =   0x20,               /*!<  Pressure data                                     */
    BME680_PRESS_MSB        =   0x1F,               /*!<  Pressure data                                     */
    BME680_MEAS_STATUS_0    =   0x1D,               /*!<  New data status                                   */
} BME680_registers_t;



// MASTER MODE
/**
  * @brief   MEASUREMENT RESOLUTION
  */
typedef enum
{
    BME680_HOLD_MASTER_MODE                 =   0x01,           /*!<  BME680 HOLD MASTER MODE enabled                       */
    BME680_NO_HOLD_MASTER_MODE              =   0x00            /*!<  BME680 NO HOLD MASTER MODE enabled                    */
} BME680_master_mode_t;



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
    BME680_RESOLUTION_MASK                  =   0x81,           /*!<  BME680 Measurement Resolution                         */
    BME680_RESOLUTION_RH_12_TEMP_14         =   0x00,           /*!<  BME680 12b RH 14b Temp.                               */
    BME680_RESOLUTION_RH_8_TEMP_12          =   0x01,           /*!<  BME680 9b  RH 12b Temp.                               */
    BME680_RESOLUTION_RH_10_TEMP_13         =   0x80,           /*!<  BME680 10b RH 13b Temp.                               */
    BME680_RESOLUTION_RH_11_TEMP_11         =   0x81            /*!<  BME680 11b RH 11b Temp.                               */
} BME680_measurement_resolution_t;



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
    BME680_VDDS_STATUS_MASK                 =   0x40,           /*!<  BME680 VDD mask.                                      */
    BME680_VDDS_STATUS_VDD_OK               =   ( 0 << 6 ),     /*!<  VDD OK.                                               */
    BME680_VDDS_STATUS_VDD_LOW              =   ( 1 << 6 )      /*!<  VDD Low.                                              */
} BME680_vdds_status_t;



/**
  * @brief   HTRE
  */
typedef enum
{
    BME680_HTRE_MASK                        =   0x03,           /*!<  BME680 HTRE Mask                                   */
    BME680_HTRE_ENABLED                     =   ( 1 << 2 ),     /*!<  BME680 On-chip Heater Enable                          */
    BME680_HTRE_DISABLED                    =   ( 0 << 2 )      /*!<  BME680 On-chip Heater Disable                         */
} BME680_heater_t;






#ifndef BME680_VECTOR_STRUCT_H
#define BME680_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint32_t ElectronicSerialNumber_LSB;
    uint32_t ElectronicSerialNumber_MSB;

    uint8_t  FirmwareRevision;
    uint8_t  BatteryStatus;
} BME680_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    BME680_SUCCESS     =       0,
    BME680_FAILURE     =       1
} BME680_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
BME680_status_t  BME680_Init                        ( I2C_parameters_t myI2Cparameters );

/** It configures the device: resolution and heater.
  */
BME680_status_t  BME680_Conf                        ( I2C_parameters_t myI2Cparameters, BME680_measurement_resolution_t myResolution, BME680_heater_t myHeater );

/** It performs a software reset.
  */
BME680_status_t  BME680_SoftReset                   ( I2C_parameters_t myI2Cparameters );

/** It gets the electronic serial number.
  */
BME680_status_t  BME680_GetElectronicSerialNumber   ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* mySerialNumber );

/** It gets the firmware revision.
  */
BME680_status_t  BME680_GetFirmwareRevision         ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myFirmwareRevision );

/** It sets the heater current.
*/
BME680_status_t  BME680_SetHeaterCurrent            ( I2C_parameters_t myI2Cparameters, uint8_t myHeaterCurrent );

/** It performs a new temperature measurement.
  */
BME680_status_t  BME680_TriggerTemperature          ( I2C_parameters_t myI2Cparameters, BME680_master_mode_t myMode );

/** It read the temperature.
  */
BME680_status_t  BME680_ReadTemperature             ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It reads the raw data from temperature.
  */
BME680_status_t  BME680_ReadRawTemperature          ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It reads the raw temperature data after a relative humidity measurement was done.
  */
BME680_status_t  BME680_ReadRawTemperatureFromRH    ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It reads the temperature after a relative humidity measurement was done.
  */
BME680_status_t  BME680_ReadTemperatureFromRH       ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It performs a new relative humidity measurement.
  */
BME680_status_t  BME680_TriggerHumidity             ( I2C_parameters_t myI2Cparameters, BME680_master_mode_t myMode );

/** It reads the relative humidity.
  */
BME680_status_t  BME680_ReadHumidity                ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myHumidity );

/** It reads the raw data from relative humidity.
  */
BME680_status_t  BME680_ReadRawHumidity             ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myHumidity );

/** It gets the battery status.
  */
BME680_status_t  BME680_GetBatteryStatus            ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myBatteryStatus );


#ifdef __cplusplus
}
#endif

#endif /* BME680_H */
