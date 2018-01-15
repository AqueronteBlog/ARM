/**
 * @brief       i2c.h
 * @details     STM32L152RE I2C function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018    The ORIGIN
 * @pre         NaN
 * @warning     This file is ONLY for STM32L152RE device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include "stm32l1xx.h"
//#include "stm32l152xe.h"


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
	I2C_STOP_BIT  	 =   0x00,
	I2C_NO_STOP_BIT  =   0x01,
	I2C_TIMEOUT		 =	 232323
} i2c_internal_constants_t;


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
	GPIO_TypeDef* SDAport;
	GPIO_TypeDef* SCLport;

    // Pin number
    uint32_t SDA;
    uint32_t SCL;

    // I2C frequency
    uint32_t Freq;

    // I2C Address
    uint32_t ADDR;


    // I2C/TWI instance
    I2C_TypeDef* I2Cinstance;
} I2C_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
i2c_status_t    i2c_write   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length, uint32_t i2c_generate_stop );
i2c_status_t    i2c_read    ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t length );
i2c_status_t    i2c_init    ( I2C_parameters_t myI2Cparameters );
