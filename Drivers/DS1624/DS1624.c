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
 * @date        1/December/2017
 * @version     1/December/2017   The ORIGIN
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
 * @brief       DS1624_ReadTemperature ( I2C_parameters_t , DS1624_vector_data_t* )
 *
 * @details     It gets the temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Temperature data.
 *
 *
 * @return       Status of DS1624_ReadTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        11/December/2017
 * @version     11/December/2017     The ORIGIN
 * @pre         The temperature registers are updated after each user-initiated conversion and on every 64-second conversion.
 * @warning     NaN.
 */
DS1624_status_t  DS1624_ReadTemperature   ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t*  myTemperature )
{
//    uint8_t      cmd[]       =   { DS1624_MSB_TEMPERATURE, 0 };
    uint32_t     aux         =   0;
//
//
//    // It gets the temperature
//    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
//    aux = i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
//
//
//    // Parse the data
//    // 1. Check if the Temperature is positive or negative
//    if ( ( cmd[0] & 0b10000000 ) == 0b00000000 )
//        myTemperature->Temperature   =   cmd[0];                           // Positive value
//    else
//        myTemperature->Temperature   =   -1.0 * ( ( ~cmd[0] ) + 1 );       // Negative value
//
//
//    // 2. Decimal part. 0.25°C resolution
//    switch( cmd[1] )
//    {
//        // x.00°C
//    default:
//    case 0b00000000:
//        break;
//
//        // x.25°C
//    case 0b01000000:
//        myTemperature->Temperature  +=    0.25;
//        break;
//
//        // x.50°C
//    case 0b10000000:
//        myTemperature->Temperature  +=    0.50;
//        break;
//
//        // x.75°C
//    case 0b11000000:
//        myTemperature->Temperature  +=    0.75;
//        break;
//    }




    if ( aux == I2C_SUCCESS )
        return   DS1624_SUCCESS;
    else
        return   DS1624_FAILURE;
}
