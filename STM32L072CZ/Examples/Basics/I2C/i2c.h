/**
 * @brief       i2c.h
 * @details     STM32L072CZ I2C function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for STM32L072CZ device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "stm32l0xx_hal.h"

#ifndef STM32L072CZ_I2C_H_
#define STM32L072CZ_I2C_H_

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
    I2C_SUCCESS  	     			=   0x00,
    I2C_FAILURE  		 			=   0x01,
	I2C_WRONG_FREQUENCY  			=   0x02
} i2c_status_t;


/**
  * @brief   I2C PARAMETERS
  */
typedef struct{
    /* Port for pins: SDA and SCL  */
	GPIO_TypeDef* sdaPort;
	GPIO_TypeDef* sclPort;

    /* Pin number  */
    uint32_t sda;
    uint32_t scl;

    /* I2C frequency   */
    uint32_t freq;

    /* I2C Address   */
    uint32_t addr;

    /* I2C instance  */
    I2C_TypeDef* i2cInstance;

    /* Core clock that drives the I2C peripheral	 */
    uint32_t pclkFrequency;
} I2C_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** I2C writing function.
  */
i2c_status_t    i2c_write   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length, i2c_stop_bit_t i2c_generate_stop );

/** I2C reading function.
  */
i2c_status_t    i2c_read    ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length );

/** I2C init function.
  */
i2c_status_t    i2c_init    ( I2C_parameters_t myI2Cparameters );


#ifdef __cplusplus
}
#endif

#endif /* STM32L072CZ_I2C_H_ */
