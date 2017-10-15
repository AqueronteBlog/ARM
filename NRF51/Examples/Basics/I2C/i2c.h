/**
 * @brief       i2c.h
 * @details     NRF51 I2C function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     This file is ONLY for NRF51 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"


/**
  * @brief   INTERNAL CONSTANTS
  */
#define I2C_STOP_BIT     0x00
#define I2C_NO_STOP_BIT  0x01


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    I2C_SUCCESS  =   0x00,
    I2C_FAILURE  =   0x01
} i2c_status_t;


/**
  * @brief   I2C PARAMETERS
  */
typedef struct{
    // Port for pins: SDA and SCL
    NRF_GPIO_Type* SDAport;
    NRF_GPIO_Type* SCLport;

    // Pin number
    uint32_t SDA;
    uint32_t SCL;

    // I2C frequency
    uint32_t Freq;

    // I2C Address
    uint32_t ADDR;


    // I2C/TWI instance
    NRF_TWI_Type* TWIinstance;
} I2C_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
// i2c_status_t    i2c_write   ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* i2c_buff, uint32_t length, uint32_t i2c_generate_stop );
// i2c_status_t    i2c_read    ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* i2c_buff, uint32_t length );
i2c_status_t    i2c_write   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length, uint32_t i2c_generate_stop );
i2c_status_t    i2c_read    ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length );
i2c_status_t    i2c_init    ( I2C_parameters_t myI2Cparameters );
