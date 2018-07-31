/**
 * @brief       i2c.h
 * @details     NRF52 I2C function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for NRF52 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf52_bitfields.h"

#ifndef NRF52_I2C_H_
#define NRF52_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    I2C_STOP_BIT    =   0x00,
    I2C_NO_STOP_BIT =   0x01
} i2c_stop_bit_t;

typedef enum
{
    I2C_TIMEOUT    =   232323
} i2c_timeouts_t;


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
    /* Port for pins: SDA and SCL  */
    NRF_GPIO_Type* SDAport;
    NRF_GPIO_Type* SCLport;

    /* Pin number  */
    uint32_t SDA;
    uint32_t SCL;

    /* I2C frequency   */
    uint32_t Freq;

    /* I2C Address   */
    uint32_t ADDR;


    /* I2C/TWI instance  */
    NRF_TWI_Type* TWIinstance;
} I2C_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** I2C writing function.
  */
i2c_status_t    i2c_write   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length, uint32_t i2c_generate_stop );

/** I2C reading function.
  */
i2c_status_t    i2c_read    ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length );

/** I2C init function.
  */
i2c_status_t    i2c_init    ( I2C_parameters_t myI2Cparameters );


#ifdef __cplusplus
}
#endif

#endif /* NRF52_I2C_H_ */