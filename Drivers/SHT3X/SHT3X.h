/**
 * @brief       SHT3X.h
 * @details     Humidity and Temperature Sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "i2c.h"


#ifndef SHT3X_H_
#define SHT3X_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    SHT3X_ADDRESS_A     =   0x44,             /*!<   SHT3X ADDR pin connected to logic low   */
    SHT3X_ADDRESS_B     =   0x45              /*!<   SHT3X ADDR pin connected to logic high  */
} SHT3X_address_t;



/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
    SHT3X_TRIGGER_TEMPERATURE_MEASUREMENT_HOLD_MASTER      =   0xE3,            /*!<  Hold master                           */
    SHT3X_TRIGGER_HUMIDITY_MEASUREMENT_HOLD_MASTER         =   0xE5,            /*!<  Hold master                           */
    SHT3X_TRIGGER_TEMPERATURE_MEASUREMENT_NO_HOLD_MASTER   =   0xF3,            /*!<  No Hold master                        */
    SHT3X_TRIGGER_HUMIDITY_MEASUREMENT_NO_HOLD_MASTER      =   0xF5,            /*!<  No Hold master                        */
    SHT3X_WRITE_USER_REGISTER                              =   0xE6,            /*!<  Write user register                   */
    SHT3X_READ_USER_REGISTER                               =   0xE7,            /*!<  Read user register                    */
    SHT3X_SOFT_RESET                                       =   0xFE,            /*!<  Software reset                        */
    SHT3X_SERIAL_NUMBER_FIRST_MEMORY_ACCESS_MSB            =   0xFA,            /*!<  Serial number first memory access     */
    SHT3X_SERIAL_NUMBER_FIRST_MEMORY_ACCESS_LSB            =   0x0F,            /*!<  Serial number first memory access     */
    SHT3X_SERIAL_NUMBER_SECOND_MEMORY_ACCESS_MSB           =   0xFC,            /*!<  Serial number second memory access    */
    SHT3X_SERIAL_NUMBER_SECOND_MEMORY_ACCESS_LSB           =   0xC9             /*!<  Serial number second memory access    */
} SHT3X_command_registers_t;



// MASTER MODE
/**
  * @brief   MODE
  */
typedef enum
{
    SHT3X_HOLD_MASTER_MODE                 =   0x01,           /*!<  SHT3X HOLD MASTER MODE enabled                       */
    SHT3X_NO_HOLD_MASTER_MODE              =   0x00            /*!<  SHT3X NO HOLD MASTER MODE enabled                    */
} SHT3X_master_mode_t;



// USER REGISTER
/*
    NOTE:   Reserved bits must not be changed and default
            values of respective reserved bits may change over time without prior notice. Therefore, for any writing to user
            register, default values of reserved bits must be read first.
*/
/**
  * @brief   RESOLUTION
  */
typedef enum
{
    USER_REGISTER_RESOLUTION_MASK                =   0x81,           /*!<  SHT3X Measurement Resolution                         */
    USER_REGISTER_RESOLUTION_12RH_14TEMP         =   0x00,           /*!<  SHT3X 12b RH 14b Temp.                               */
    USER_REGISTER_RESOLUTION_8RH_12TEMP          =   0x01,           /*!<  SHT3X 9b  RH 12b Temp.                               */
    USER_REGISTER_RESOLUTION_10RH_13TEMP         =   0x80,           /*!<  SHT3X 10b RH 13b Temp.                               */
    USER_REGISTER_RESOLUTION_11RH_11TEMP         =   0x81            /*!<  SHT3X 11b RH 11b Temp.                               */
} SHT3X_measurement_resolution_t;



/**
  * @brief   STATUS END OF BATTERY
  */
typedef enum
{
    USER_REGISTER_STATUS_END_BATTERY_MASK         =   0x40,           /*!<  End battery mask                                      */
    USER_REGISTER_STATUS_END_BATTERY_HIGH_2V25    =   0x00,           /*!<  VDD > 2.25V.                                          */
    USER_REGISTER_STATUS_END_BATTERY_LOW_2V25     =   0x40            /*!<  VDD < 2.25V.                                          */
} SHT3X_status_end_battery_t;



/**
  * @brief   ON-CHIP HEATER
  */
typedef enum
{
    USER_REGISTER_HEATER_MASK                     =   0x04,           /*!<  ON-chip heater mask                                   */
    USER_REGISTER_HEATER_ENABLED                  =   0x04,           /*!<  Heater enabled.                                       */
    USER_REGISTER_HEATER_DISABLED                 =   0x00            /*!<  Heater disabled.                                      */
} SHT3X_on_chip_heater_t;



/**
  * @brief   OTP RELOAD
  */
typedef enum
{
    USER_REGISTER_OTP_MASK                        =   0x02,           /*!<  OTP heater mask                                       */
    USER_REGISTER_OTP_ENABLED                     =   0x00,           /*!<  OTP enabled.                                          */
    USER_REGISTER_OTP_DISABLED                    =   0x02            /*!<  OTP disabled.                                         */
} SHT3X_otp_t;



#ifndef SHT3X_VECTOR_STRUCT_H
#define SHT3X_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint16_t RawRelativeHumidity;
    uint16_t RawTemperature;

    uint8_t  BatteryStatus;
    uint64_t SerialNumber;
} SHT3X_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SHT3X_SUCCESS     =       0,
    SHT3X_FAILURE     =       1
} SHT3X_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SHT3X_status_t  SHT3X_Init               ( I2C_parameters_t myI2Cparameters                                                                                 );

/** It configures the SHT3X device.
  */
SHT3X_status_t  SHT3X_Conf               ( I2C_parameters_t myI2Cparameters, SHT3X_measurement_resolution_t myResolution, SHT3X_on_chip_heater_t myHeater   );

/** Rebooting the SHT3X sensor switching the power off and on again.
  */
SHT3X_status_t  SHT3X_SoftReset          ( I2C_parameters_t myI2Cparameters                                                                                 );

/** It triggers a new temperature measurement.
  */
SHT3X_status_t  SHT3X_TriggerTemperature ( I2C_parameters_t myI2Cparameters, SHT3X_master_mode_t myMode                                                     );

/** It reads a new temperature measurement.
  */
SHT3X_status_t  SHT3X_ReadTemperature    ( I2C_parameters_t myI2Cparameters, SHT3X_vector_data_t* myTemperature                                             );

/** It reads a new raw temperature measurement.
  */
SHT3X_status_t  SHT3X_ReadRawTemperature ( I2C_parameters_t myI2Cparameters, SHT3X_vector_data_t* myRawTemperature                                          );

/** It triggers a new humidity measurement.
  */
SHT3X_status_t  SHT3X_TriggerHumidity    ( I2C_parameters_t myI2Cparameters, SHT3X_master_mode_t myMode                                                     );

/** It reads a new humidity measurement.
  */
SHT3X_status_t  SHT3X_ReadHumidity       ( I2C_parameters_t myI2Cparameters, SHT3X_vector_data_t* myHumidity                                                );

/** It reads a new raw humidity measurement.
  */
SHT3X_status_t  SHT3X_ReadRawHumidity    ( I2C_parameters_t myI2Cparameters, SHT3X_vector_data_t* myRawHumidity                                             );

/** It reads the user register to check the battery status.
  */
SHT3X_status_t  SHT3X_BatteryStatus      ( I2C_parameters_t myI2Cparameters, SHT3X_vector_data_t* myBattStatus                                              );

/** It gets the serial number ( Electronic Identification Code ).
  */
SHT3X_status_t  SHT3X_GetSerialNumber    ( I2C_parameters_t myI2Cparameters, SHT3X_vector_data_t* mySerialNumber                                            );


#ifdef __cplusplus
}
#endif

#endif /* SHT3X_H */
