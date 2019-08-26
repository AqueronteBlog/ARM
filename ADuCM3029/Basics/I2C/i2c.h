/**
 * @brief       i2c.h
 * @details     ADUCM3029 I2C function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        25/July/2019
 * @version     25/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for ADUCM3029 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <system_ADuCM3029.h>

#ifndef ADUCM3029_I2C_H_
#define ADUCM3029_I2C_H_

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
	I2C_WRONG_FREQUENCY  			=   0x02,
	I2C_SILICON_ANOMALY_21000011  	=   0x03			/*!<   It applies to revision 1.2	 */
} i2c_status_t;


/**
  * @brief   I2C PARAMETERS
  */
typedef struct{
    /* Port for pins: SDA and SCL  */
	ADI_GPIO_TypeDef* sdaPort;
	ADI_GPIO_TypeDef* sclPort;

    /* Pin number  */
    uint32_t sda;
    uint32_t scl;

    /* I2C frequency   */
    uint32_t freq;

    /* I2C Address   */
    uint32_t addr;

    /* I2C instance  */
    ADI_I2C_TypeDef* i2cInstance;

    /* Core clock that drives the I2C peripheral	 */
    uint32_t pclkFrequency;
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

#endif /* ADUCM3029_I2C_H_ */
