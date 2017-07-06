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
#define USER_REGISTER_RESOLUTION_8RH_12TEMP                         0x40
#define USER_REGISTER_RESOLUTION_10RH_13TEMP                        0x80
#define USER_REGISTER_RESOLUTION_11RH_11TEMP                        0xC0

/* STATUS */
#define USER_REGISTER_STATUS_END_BATTERY_HIGH_2V25                  0x00
#define USER_REGISTER_STATUS_END_BATTERY_LOW_2V25                   0x20
#define USER_REGISTER_STATUS_END_BATTERY_MASK                       0x20

/* ON-CHIP HEATER */
#define USER_REGISTER_HEATER_ENABLED                                0x02
#define USER_REGISTER_HEATER_DISABLED                               0x00
#define USER_REGISTER_HEATER_MASK                                   0x02

/* OTP RELOAD */
#define USER_REGISTER_OTP_ENABLED                                   0x00
#define USER_REGISTER_OTP_DISABLED                                  0x01
#define USER_REGISTER_OTP_MASK                                      0x01



/**
  * @brief   INTERNAL CONSTANTS
  */
#define HTU21D_SUCCESS                                              0x00
#define HTU21D_FAILURE                                              0x01



uint32_t    HTU21D_SDA_pin;
uint32_t    HTU21D_SCL_pin;
uint32_t    HTU21D_Mode;



/**
  * @brief   HTU21D Init structure definition
  */
typedef struct
{
  uint32_t HTU21D_SDA;              /*!<    Specifies the SDA pin                                               */
  uint32_t HTU21D_SCL;              /*!<    Specifies the SCL pin                                               */
  uint32_t HTU21D_MODE;             /*!<    Specifies the HTU21D mode to work ( Hold Master or No Hold Master ) */
  uint32_t HTU21D_RESOLUTION;       /*!<    Specifies the HTU21D resolution according to the user register      */
  uint32_t HTU21D_ENABLE_HEATER;    /*!<    Specifies the HTU21D'heater according to the user register          */
}HTU21D_InitTypeDef;



/* FUNCTIONS PROTOTYPES */
uint8_t  HTU21D_Init        ( uint32_t SDA, uint32_t SCL, uint32_t MODE, uint32_t RESOLUTION, uint32_t HEATER );
uint8_t  HTU21D_SoftReset   ( void );
