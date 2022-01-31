/**
 * @brief       AHT20.h
 * @details     Humidity and Temperature Sensor.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/January/2022
 * @version     31/January/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    AHT20_ADDRESS     =   0x38                                                         /*!<   AHT20 I2C Address                                   */
} AHT20_address_t;




/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
    AHT20_TRIGGER_TEMPERATURE_MEASUREMENT_HOLD_MASTER      =   0xE3,               /*!<  Hold master                       */
    AHT20_TRIGGER_HUMIDITY_MEASUREMENT_HOLD_MASTER         =   0xE5,               /*!<  Hold master                       */
    AHT20_TRIGGER_TEMPERATURE_MEASUREMENT_NO_HOLD_MASTER   =   0xF3,               /*!<  No Hold master                    */
    AHT20_TRIGGER_HUMIDITY_MEASUREMENT_NO_HOLD_MASTER      =   0xF5,               /*!<  No Hold master                    */
    AHT20_WRITE_REGISTER                                   =   0xE6,               /*!<  Write register                    */
    AHT20_READ_REGISTER                                    =   0xE7,               /*!<  Read register                     */
    AHT20_SOFT_RESET                                       =   0xFE                /*!<  Software reset                    */
} AHT20_command_registers_t;



// MASTER MODE
/**
  * @brief   MODE
  */
typedef enum
{
    AHT20_HOLD_MASTER_MODE                 =   0x01,           /*!<  AHT20 HOLD MASTER MODE enabled                       */
    AHT20_NO_HOLD_MASTER_MODE              =   0x00            /*!<  AHT20 NO HOLD MASTER MODE enabled                    */
} AHT20_master_mode_t;



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
    USER_REGISTER_RESOLUTION_MASK                =   0x81,           /*!<  AHT20 Measurement Resolution                         */
    USER_REGISTER_RESOLUTION_12RH_14TEMP         =   0x00,           /*!<  AHT20 12b RH 14b Temp.                               */
    USER_REGISTER_RESOLUTION_8RH_12TEMP          =   0x01,           /*!<  AHT20 9b  RH 12b Temp.                               */
    USER_REGISTER_RESOLUTION_10RH_13TEMP         =   0x80,           /*!<  AHT20 10b RH 13b Temp.                               */
    USER_REGISTER_RESOLUTION_11RH_11TEMP         =   0x81            /*!<  AHT20 11b RH 11b Temp.                               */
} AHT20_measurement_resolution_t;



/**
  * @brief   STATUS END OF BATTERY
  */
typedef enum
{
    USER_REGISTER_STATUS_END_BATTERY_MASK         =   0x40,           /*!<  End battery mask                                      */
    USER_REGISTER_STATUS_END_BATTERY_HIGH_2V25    =   0x40,           /*!<  VDD > 2.25V.                                          */
    USER_REGISTER_STATUS_END_BATTERY_LOW_2V25     =   0x00            /*!<  VDD < 2.25V.                                          */
} AHT20_status_end_battery_t;



/**
  * @brief   ON-CHIP HEATER
  */
typedef enum
{
    USER_REGISTER_HEATER_MASK                     =   0x04,           /*!<  ON-chip heater mask                                   */
    USER_REGISTER_HEATER_ENABLED                  =   0x04,           /*!<  Heater enabled.                                       */
    USER_REGISTER_HEATER_DISABLED                 =   0x00            /*!<  Heater disabled.                                      */
} AHT20_on_chip_heater_t;



/**
  * @brief   OTP RELOAD
  */
typedef enum
{
    USER_REGISTER_OTP_MASK                        =   0x02,           /*!<  OTP heater mask                                       */
    USER_REGISTER_OTP_ENABLED                     =   0x00,           /*!<  OTP enabled.                                          */
    USER_REGISTER_OTP_DISABLED                    =   0x02            /*!<  OTP disabled.                                         */
} AHT20_otp_t;



#ifndef AHT20_VECTOR_STRUCT_H
#define AHT20_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint8_t  BatteryStatus;
} AHT20_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AHT20_SUCCESS     =       0,
    AHT20_FAILURE     =       1
} AHT20_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
AHT20_status_t  AHT20_Init               ( I2C_parameters_t myI2Cparameters );
AHT20_status_t  AHT20_Conf               ( I2C_parameters_t myI2Cparameters, AHT20_measurement_resolution_t myResolution, AHT20_on_chip_heater_t myHeater );
AHT20_status_t  AHT20_SoftReset          ( I2C_parameters_t myI2Cparameters );
AHT20_status_t  AHT20_TriggerTemperature ( I2C_parameters_t myI2Cparameters, AHT20_master_mode_t myMode );
AHT20_status_t  AHT20_ReadTemperature    ( I2C_parameters_t myI2Cparameters, AHT20_vector_data_t* myTemperature );
AHT20_status_t  AHT20_ReadRawTemperature ( I2C_parameters_t myI2Cparameters, AHT20_vector_data_t* myRawTemperature );
AHT20_status_t  AHT20_TriggerHumidity    ( I2C_parameters_t myI2Cparameters, AHT20_master_mode_t myMode );
AHT20_status_t  AHT20_ReadHumidity       ( I2C_parameters_t myI2Cparameters, AHT20_vector_data_t* myHumidity );
AHT20_status_t  AHT20_ReadRawHumidity    ( I2C_parameters_t myI2Cparameters, AHT20_vector_data_t* myRawHumidity );
AHT20_status_t  AHT20_BatteryStatus      ( I2C_parameters_t myI2Cparameters, AHT20_vector_data_t* myBattStatus );
