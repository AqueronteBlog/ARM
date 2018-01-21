/**
 * @brief       DS1624.h
 * @details     Digital Thermometer and Memory.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/January/2018
 * @version     18/January/2018    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "DS1624.h"


/**
 * @brief       DS1624_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS1624_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        18/January/2018
 * @version     18/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS1624_status_t  DS1624_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   DS1624_SUCCESS;
    else
        return   DS1624_FAILURE;
}



/**
 * @brief       DS1624_StartConvertTemperature ( I2C_parameters_t )
 *
 * @details     It triggers a new temperature conversion.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS1624_StartConvertTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        21/January/2018
 * @version     21/January/2018     The ORIGIN
 * @pre         Temperature Conversion Time ( t_TC ) 200ms maximum.
 * @warning     NaN.
 */
DS1624_status_t  DS1624_StartConvertTemperature ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd       =   DS1624_START_CONVERT_T;
    i2c_status_t aux       =   0;


    // It triggers a new temperature conversion
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   DS1624_SUCCESS;
    else
        return   DS1624_FAILURE;
}


/**
 * @brief       DS1624_StopConvertTemperature ( I2C_parameters_t )
 *
 * @details     It halts the temperature conversion.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS1624_StopConvertTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        21/January/2018
 * @version     21/January/2018     The ORIGIN
 * @pre         In continuous conversion mode, a StopConvertT command halt
 *              a continuous conversion. To restart, the StartConvertT
 *              command must be issued. In one-shot mode, a StartConvertT command
 *              must be issued for every temperature reading desired.
 * @warning     NaN.
 */
DS1624_status_t  DS1624_StopConvertTemperature ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd       =   DS1624_STOP_CONVERT_T;
    i2c_status_t aux       =   0;


    // It sends the command
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   DS1624_SUCCESS;
    else
        return   DS1624_FAILURE;
}
