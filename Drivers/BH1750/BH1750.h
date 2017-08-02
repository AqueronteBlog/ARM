/**
 * @brief       BH1750.h
 * @details     Digital 16-bit Serial Output Type Ambient Light Sensor IC.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/August/2017
 * @version     2/August/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
#define BH1750_ADDR_L                                               0x23
#define BH1750_ADDR_H                                               0x5C

/**
  * @brief   COMMAND REGISTERS
  */
#define BH1750_POWER_DOWN                                           0x00
#define BH1750_POWER_ON                                             0x01
#define BH1750_RESET                                                0x07
#define BH1750_CONTINUOUSLY_H_RESOLUTION_MODE                       0x10
#define BH1750_CONTINUOUSLY_H_RESOLUTION_MODE2                      0x11
#define BH1750_CONTINUOUSLY_L_RESOLUTION_MODE                       0x13
#define BH1750_ONE_TIME_H_RESOLUTION_MODE                           0x20
#define BH1750_ONE_TIME_H_RESOLUTION_MODE2                          0x21
#define BH1750_ONE_TIME_L_RESOLUTION_MODE                           0x23


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
uint32_t  HTU21D_Init               ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint32_t MODE, uint32_t RESOLUTION, uint32_t HEATER );
uint32_t  HTU21D_SoftReset          ( NRF_TWI_Type* myinstance, uint32_t ADDR );
uint32_t  HTU21D_TriggerTemperature ( NRF_TWI_Type* myinstance, uint32_t ADDR );
uint32_t  HTU21D_ReadTemperature    ( NRF_TWI_Type* myinstance, uint32_t ADDR, float* mytemperature );
uint32_t  HTU21D_ReadRawTemperature ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* myRawtemperature );
uint32_t  HTU21D_TriggerHumidity    ( NRF_TWI_Type* myinstance, uint32_t ADDR );
uint32_t  HTU21D_ReadHumidity       ( NRF_TWI_Type* myinstance, uint32_t ADDR, float* myhumidity );
uint32_t  HTU21D_ReadRawHumidity    ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* myRawhumidity );
uint32_t  HTU21D_BatteryStatus      ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* battStatus );
