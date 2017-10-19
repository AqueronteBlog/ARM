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
#define HTU21D_ADDR                                                 0x40

/**
  * @brief   COMMAND REGISTERS
  */
#define HTU21D_TRIGGER_TEMPERATURE_MEASUREMENT_HOLD_MASTER          0xE3
#define HTU21D_TRIGGER_HUMIDITY_MEASUREMENT_HOLD_MASTER             0xE5
#define HTU21D_TRIGGER_TEMPERATURE_MEASUREMENT_NO_HOLD_MASTER       0xF3
#define HTU21D_TRIGGER_HUMIDITY_MEASUREMENT_NO_HOLD_MASTER          0xF5
#define HTU21D_WRITE_REGISTER                                       0xE6
#define HTU21D_READ_REGISTER                                        0xE7
#define HTU21D_SOFT_RESET                                           0xFE

/**
  * @brief   USER REGISTER
  */
/* RESOLUTION */
#define USER_REGISTER_RESOLUTION_12RH_14TEMP                        0x00
#define USER_REGISTER_RESOLUTION_8RH_12TEMP                         0x01
#define USER_REGISTER_RESOLUTION_10RH_13TEMP                        0x80
#define USER_REGISTER_RESOLUTION_11RH_11TEMP                        0x81
#define USER_REGISTER_RESOLUTION_MASK                               0x81

/* STATUS */
#define USER_REGISTER_STATUS_END_BATTERY_HIGH_2V25                  0x00
#define USER_REGISTER_STATUS_END_BATTERY_LOW_2V25                   0x40
#define USER_REGISTER_STATUS_END_BATTERY_MASK                       0x40

/* ON-CHIP HEATER */
#define USER_REGISTER_HEATER_ENABLED                                0x04
#define USER_REGISTER_HEATER_DISABLED                               0x00
#define USER_REGISTER_HEATER_MASK                                   0x04

/* OTP RELOAD */
#define USER_REGISTER_OTP_ENABLED                                   0x00
#define USER_REGISTER_OTP_DISABLED                                  0x02
#define USER_REGISTER_OTP_MASK                                      0x02


/**
  * @brief   MODE
  */
#define HTU21D_MODE_HOLD_MASTER                                     0x00
#define HTU21D_MODE_NO_HOLD_MASTER                                  0x01


/**
  * @brief   INTERNAL CONSTANTS
  */
#define HTU21D_SUCCESS                                              0x00
#define HTU21D_FAILURE                                              0x01



/**
  * @brief   INTERNAL VARIABLES
  */
uint32_t    HTU21D_Mode;
uint32_t    HTU21D_Resolution;



/**
  * @brief   FUNCTION PROTOTYPES
  */
uint32_t  HTU21D_Init               ( I2C_parameters_t myI2Cparameters );
uint32_t  HTU21D_Conf               ( I2C_parameters_t myI2Cparameters, uint32_t MODE, uint32_t RESOLUTION, uint32_t HEATER );
uint32_t  HTU21D_SoftReset          ( I2C_parameters_t myI2Cparameters );
uint32_t  HTU21D_TriggerTemperature ( I2C_parameters_t myI2Cparameters );
uint32_t  HTU21D_ReadTemperature    ( I2C_parameters_t myI2Cparameters, float* mytemperature );
uint32_t  HTU21D_ReadRawTemperature ( I2C_parameters_t myI2Cparameters, uint8_t* myRawtemperature );
uint32_t  HTU21D_TriggerHumidity    ( I2C_parameters_t myI2Cparameters );
uint32_t  HTU21D_ReadHumidity       ( I2C_parameters_t myI2Cparameters, float* myhumidity );
uint32_t  HTU21D_ReadRawHumidity    ( I2C_parameters_t myI2Cparameters, uint8_t* myRawhumidity );
uint32_t  HTU21D_BatteryStatus      ( I2C_parameters_t myI2Cparameters, uint8_t* battStatus );
