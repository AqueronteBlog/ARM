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
 * @date        18/October/2017
 * @version     18/October/2017   The ORIGIN
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
 * @brief       PCA9685_SetPins ( I2C_parameters_t , PCA9685_vector_data_t )
 *
 * @details     It configures the port of the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfDATA:        Data to set up the device.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_SetPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     18/October/2017     Adapted to the new I2C driver.
 *              11/October/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_SetPins   ( I2C_parameters_t myI2Cparameters, PCA9685_vector_data_t  myConfDATA )
{
    uint32_t     aux     =    0;


    // Configure the ports of the device
    aux = i2c_write ( myI2Cparameters, &myConfDATA.data, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}



/**
 * @brief       PCA9685_ReadPins ( I2C_parameters_t , PCA9685_vector_data_t*  )
 *
 * @details     It gets the data from the device ( port status ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myReadDATA:        ADC result into the chosen channel.
 *
 *
 * @return       Status of PCA9685_ReadPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     18/October/2017     Adapted to the new I2C driver.
 *              11/October/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_ReadPins ( I2C_parameters_t myI2Cparameters, PCA9685_vector_data_t* myReadDATA )
{
    uint32_t     aux  =    0;


    // Read the port
    aux = i2c_read ( myI2Cparameters, &myReadDATA->data, 1 );




    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}
