/**
 * @brief       DS3231.h
 * @details     Extremely Accurate I2C-Integrated RTC/TCXO/Crystal.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "DS3231.h"


/**
 * @brief       DS3231_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ReadTemperature ( I2C_parameters_t , DS3231_vector_data_t )
 *
 * @details     It gets the temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Temperature data.
 *
 *
 * @return       Status of DS3231_ReadTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        11/December/2017
 * @version     11/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ReadTemperature   ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t  myTemperature )
{
    uint8_t      cmd[]       =   { DS3231_MSB_TEMPERATURE, 0 };
    uint32_t     aux         =   0;


    // It gets the temperature
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse the data
    // 1. Check if the Temperature is positive or negative
    if ( ( cmd[0] & 0b10000000 ) == 0b00000000 )
        myTemperature.Temperature   =   cmd[0];                           // Positive value
    else
        myTemperature.Temperature   =   -1.0 * ( ( ~cmd[0] ) + 1 );       // Negative value


    // 2. Decimal part. 0.25°C resolution
    switch( cmd[1] )
    {
    // x.00°C
    default:
    case 0b00000000:
        break;

    // x.25°C
    case 0b01000000:
        myTemperature.Temperature  +=    0.25;
        break;

    // x.50°C
    case 0b10000000:
        myTemperature.Temperature  +=    0.50;
        break;

    // x.75°C
    case 0b11000000:
        myTemperature.Temperature  +=    0.75;
        break;
    }




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ReadRawTemperature ( I2C_parameters_t , DS3231_vector_data_t )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw Temperature data.
 *
 *
 * @return       Status of DS3231_ReadTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        11/December/2017
 * @version     11/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ReadRawTemperature   ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t  myRawTemperature )
{
    uint8_t      cmd[]       =   { DS3231_MSB_TEMPERATURE, 0 };
    uint32_t     aux         =   0;


    // It gets the temperature
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse the data
    myRawTemperature.MSBTemperature    =   cmd[0];
    myRawTemperature.LSBTemperature    =   cmd[1];




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ReadRawAging ( I2C_parameters_t , DS3231_vector_data_t )
 *
 * @details     It gets the raw aging.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawAging:        Raw Aging data.
 *
 *
 * @return       Status of DS3231_ReadRawAging.
 *
 *
 * @author      Manuel Caballero
 * @date        12/December/2017
 * @version     12/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ReadRawAging ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t myRawAging )
{
    uint8_t      cmd       =   DS3231_AGING_OFFSET;
    uint32_t     aux       =   0;


    // It gets the raw aging value
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &myRawAging.RawAging, 1 );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}
