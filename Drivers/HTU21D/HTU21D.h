/**
 * @brief       HTU21D.h
 * @details     Digital Relative Humidity sensor with Temperature output.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    HTU21D_ADDRESS     =   0x40                                                         /*!<   HTU21D I2C Address                                   */
} HTU21D_address_t;




/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
    HTU21D_TRIGGER_TEMPERATURE_MEASUREMENT_HOLD_MASTER      =   0xE3,               /*!<  Hold master                       */
    HTU21D_TRIGGER_HUMIDITY_MEASUREMENT_HOLD_MASTER         =   0xE5,               /*!<  Hold master                       */
    HTU21D_TRIGGER_TEMPERATURE_MEASUREMENT_NO_HOLD_MASTER   =   0xF3,               /*!<  No Hold master                    */
    HTU21D_TRIGGER_HUMIDITY_MEASUREMENT_NO_HOLD_MASTER      =   0xF5,               /*!<  No Hold master                    */
    HTU21D_WRITE_REGISTER                                   =   0xE6,               /*!<  Write register                    */
    HTU21D_READ_REGISTER                                    =   0xE7,               /*!<  Read register                     */
    HTU21D_SOFT_RESET                                       =   0xFE                /*!<  Software reset                    */
} HTU21D_command_registers_t;



// MASTER MODE
/**
  * @brief   MODE
  */
typedef enum
{
    HTU21D_HOLD_MASTER_MODE                 =   0x01,           /*!<  HTU21D HOLD MASTER MODE enabled                       */
    HTU21D_NO_HOLD_MASTER_MODE              =   0x00            /*!<  HTU21D NO HOLD MASTER MODE enabled                    */
} HTU21D_master_mode_t;



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
    USER_REGISTER_RESOLUTION_MASK                =   0x81,           /*!<  HTU21D Measurement Resolution                         */
    USER_REGISTER_RESOLUTION_12RH_14TEMP         =   0x00,           /*!<  HTU21D 12b RH 14b Temp.                               */
    USER_REGISTER_RESOLUTION_8RH_12TEMP          =   0x01,           /*!<  HTU21D 9b  RH 12b Temp.                               */
    USER_REGISTER_RESOLUTION_10RH_13TEMP         =   0x80,           /*!<  HTU21D 10b RH 13b Temp.                               */
    USER_REGISTER_RESOLUTION_11RH_11TEMP         =   0x81            /*!<  HTU21D 11b RH 11b Temp.                               */
} HTU21D_measurement_resolution_t;



/**
  * @brief   STATUS END OF BATTERY
  */
typedef enum
{
    USER_REGISTER_STATUS_END_BATTERY_MASK         =   0x40,           /*!<  End battery mask                                      */
    USER_REGISTER_STATUS_END_BATTERY_HIGH_2V25    =   0x40,           /*!<  VDD > 2.25V.                                          */
    USER_REGISTER_STATUS_END_BATTERY_LOW_2V25     =   0x00            /*!<  VDD < 2.25V.                                          */
} HTU21D_status_end_battery_t;



/**
  * @brief   ON-CHIP HEATER
  */
typedef enum
{
    USER_REGISTER_HEATER_MASK                     =   0x04,           /*!<  ON-chip heater mask                                   */
    USER_REGISTER_HEATER_ENABLED                  =   0x04,           /*!<  Heater enabled.                                       */
    USER_REGISTER_HEATER_DISABLED                 =   0x00            /*!<  Heater disabled.                                      */
} HTU21D_on_chip_heater_t;



/**
  * @brief   OTP RELOAD
  */
typedef enum
{
    USER_REGISTER_OTP_MASK                        =   0x02,           /*!<  OTP heater mask                                       */
    USER_REGISTER_OTP_ENABLED                     =   0x00,           /*!<  OTP enabled.                                          */
    USER_REGISTER_OTP_DISABLED                    =   0x02            /*!<  OTP disabled.                                         */
} HTU21D_otp_t;



#ifndef HTU21D_VECTOR_STRUCT_H
#define HTU21D_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint8_t  BatteryStatus;
} HTU21D_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    HTU21D_SUCCESS     =       0,
    HTU21D_FAILURE     =       1
} HTU21D_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
HTU21D_status_t  HTU21D_Init               ( I2C_parameters_t myI2Cparameters );
HTU21D_status_t  HTU21D_Conf               ( I2C_parameters_t myI2Cparameters, HTU21D_measurement_resolution_t myResolution, HTU21D_on_chip_heater_t myHeater );
HTU21D_status_t  HTU21D_SoftReset          ( I2C_parameters_t myI2Cparameters );
HTU21D_status_t  HTU21D_TriggerTemperature ( I2C_parameters_t myI2Cparameters, HTU21D_master_mode_t myMode );
HTU21D_status_t  HTU21D_ReadTemperature    ( I2C_parameters_t myI2Cparameters, HTU21D_vector_data_t* myTemperature );
HTU21D_status_t  HTU21D_ReadRawTemperature ( I2C_parameters_t myI2Cparameters, HTU21D_vector_data_t* myRawTemperature );
HTU21D_status_t  HTU21D_TriggerHumidity    ( I2C_parameters_t myI2Cparameters, HTU21D_master_mode_t myMode );
HTU21D_status_t  HTU21D_ReadHumidity       ( I2C_parameters_t myI2Cparameters, HTU21D_vector_data_t* myHumidity );
HTU21D_status_t  HTU21D_ReadRawHumidity    ( I2C_parameters_t myI2Cparameters, HTU21D_vector_data_t* myRawHumidity );
HTU21D_status_t  HTU21D_BatteryStatus      ( I2C_parameters_t myI2Cparameters, HTU21D_vector_data_t* myBattStatus );
