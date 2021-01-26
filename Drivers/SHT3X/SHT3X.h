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
    SHT3X_CLOCK_STRETCHING_ENABLED_REPEATABILITY_HIGH     = 0x2C06,   /*!<  High repeatability measurement with clock stretching enabled    */
    SHT3X_CLOCK_STRETCHING_ENABLED_REPEATABILITY_MEDIUM   = 0x2C0D,   /*!<  Medium repeatability measurement with clock stretching enabled  */
    SHT3X_CLOCK_STRETCHING_ENABLED_REPEATABILITY_LOW      = 0x2C10,   /*!<  Low repeatability measurement with clock stretching enabled     */
    
    SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_HIGH    = 0x2400,   /*!<  High repeatability measurement with clock stretching disabled   */
    SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_MEDIUM  = 0x240B,   /*!<  Medium repeatability measurement with clock stretching disabled */
    SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_LOW     = 0x2416,   /*!<  Low repeatability measurement with clock stretching disabled    */

    SHT3X_MPS_0_5_REPEATABILITY_HIGH                      = 0x2032,   /*!<  High repeatability 0.5 measurement per second                   */
    SHT3X_MPS_0_5_REPEATABILITY_MEDIUM                    = 0x2024,   /*!<  Medium repeatability 0.5 measurement per second                 */
    SHT3X_MPS_0_5_REPEATABILITY_LOW                       = 0x202F,   /*!<  Low repeatability 0.5 measurement per second                    */
    
    SHT3X_MPS_1_REPEATABILITY_HIGH                        = 0x2130,   /*!<  High repeatability 1 measurement per second                     */
    SHT3X_MPS_1_REPEATABILITY_MEDIUM                      = 0x2126,   /*!<  Medium repeatability 1 measurement per second                   */
    SHT3X_MPS_1_REPEATABILITY_LOW                         = 0x212D,   /*!<  Low repeatability 1 measurement per second                      */
    
    SHT3X_MPS_2_REPEATABILITY_HIGH                        = 0x2236,   /*!<  High repeatability 2 measurement per second                     */
    SHT3X_MPS_2_REPEATABILITY_MEDIUM                      = 0x2220,   /*!<  Medium repeatability 2 measurement per second                   */
    SHT3X_MPS_2_REPEATABILITY_LOW                         = 0x222B,   /*!<  Low repeatability 2 measurement per second                      */
    
    SHT3X_MPS_4_REPEATABILITY_HIGH                        = 0x2334,   /*!<  High repeatability 4 measurement per second                     */
    SHT3X_MPS_4_REPEATABILITY_MEDIUM                      = 0x2322,   /*!<  Medium repeatability 4 measurement per second                   */
    SHT3X_MPS_4_REPEATABILITY_LOW                         = 0x2329,   /*!<  Low repeatability 4 measurement per second                      */
    
    SHT3X_MPS_10_REPEATABILITY_HIGH                       = 0x2737,   /*!<  High repeatability 10 measurement per second                    */
    SHT3X_MPS_10_REPEATABILITY_MEDIUM                     = 0x2721,   /*!<  Medium repeatability 10 measurement per second                  */
    SHT3X_MPS_10_REPEATABILITY_LOW                        = 0x272A,   /*!<  Low repeatability 10 measurement per second                     */

    SHT3X_FETCH_DATA                                      = 0xE000,   /*!<  Fetch data command                                              */
    SHT3X_PERIODIC_MESUREMENT_WITH_ART                    = 0x2B32,   /*!<  ART command                                                     */
    SHT3X_BREAK                                           = 0x3093,   /*!<  Break command                                                   */
    SHT3X_SOFT_RESET                                      = 0x30A2,   /*!<  Software reset command                                          */
    SHT3X_HEATER_ENABLE                                   = 0x306D,   /*!<  Heater enable command                                           */
    SHT3X_HEATER_DISABLE                                  = 0x3066,   /*!<  Heater disable command                                          */
    SHT3X_STATUS_REGISTER                                 = 0xF32D,   /*!<  Status command                                                  */
    SHT3X_CLEAR_STATUS_REGISTER                           = 0x3041    /*!<  Clear Status register command                                   */
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
