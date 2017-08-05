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
#define BH1750_POWER_DOWN                                           0x00        /*!<   No active state                                                                                                                                  */
#define BH1750_POWER_ON                                             0x01        /*!<   Waiting for measurement command                                                                                                                  */
#define BH1750_RESET                                                0x07        /*!<   Reset Data register value. Reset command is not acceptable in Power Down mode                                                                    */
#define BH1750_CONTINUOUSLY_H_RESOLUTION_MODE                       0x10        /*!<   Start measurement at 1lx resolution. Measurement Time is typically 120ms                                                                         */
#define BH1750_CONTINUOUSLY_H_RESOLUTION_MODE2                      0x11        /*!<   Start measurement at 0.5lx resolution. Measurement Time is typically 120ms                                                                       */
#define BH1750_CONTINUOUSLY_L_RESOLUTION_MODE                       0x13        /*!<   Start measurement at 4lx resolution. Measurement Time is typically 16ms                                                                          */
#define BH1750_ONE_TIME_H_RESOLUTION_MODE                           0x20        /*!<   Start measurement at 1lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement           */
#define BH1750_ONE_TIME_H_RESOLUTION_MODE2                          0x21        /*!<   Start measurement at 0.5lx resolution. Measurement Time is typically 120ms. It is automatically set to Power Down mode after measurement         */
#define BH1750_ONE_TIME_L_RESOLUTION_MODE                           0x23        /*!<   Start measurement at 4lx resolution. Measurement Time is typically 16ms. It is automatically set to Power Down mode after measurement            */


/**
  * @brief   INTERNAL CONSTANTS
  */
#define BH1750_SUCCESS                                              0x00
#define BH1750_FAILURE                                              0x01



/**
  * @brief   INTERNAL VARIABLES
  */
uint32_t    BH1750_Mode;



/**
  * @brief   FUNCTION PROTOTYPES
  */
uint32_t  BH1750_PowerDown          ( NRF_TWI_Type* myinstance, uint32_t ADDR );
uint32_t  BH1750_PowerOn            ( NRF_TWI_Type* myinstance, uint32_t ADDR );
uint32_t  BH1750_ResetDataRegister  ( NRF_TWI_Type* myinstance, uint32_t ADDR );
uint32_t  BH1750_TriggerMeasurement ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint32_t MODE );
uint32_t  BH1750_NewSensitivity     ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t newSensitivity );
uint32_t  BH1750_ReadRawData        ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* myRawData );
uint32_t  BH1750_ReadLux            ( NRF_TWI_Type* myinstance, uint32_t ADDR, float* myLux );
