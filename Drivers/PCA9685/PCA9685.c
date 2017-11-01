/**
 * @brief       PCA9685.h
 * @details     16-channel, 12-bit PWM Fm+ I2C-bus LED controller.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/October/2017
 * @version     31/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "PCA9685.h"


/**
 * @brief       PCA9685_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2017
 * @version     31/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}



/**
 * @brief       PCA9685_SoftReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        1/November/2017
 * @version     1/November/2017     The ORIGIN
 * @pre         The device will be ready to be addressed again within
 *              the specified bus free time ( t_BUF ).
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_SoftReset   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd   =   SWRST;
    i2c_status_t aux;


    myI2Cparameters.ADDR    =   GENERAL_CALL_ADDRESS;


    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}
