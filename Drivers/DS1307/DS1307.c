/**
 * @brief       DS1307.c
 * @details     64 x 8, Serial, I2C Real-Time Clock.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/July/2018
 * @version     28/July/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "DS1307.h"


/**
 * @brief       DS1307_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        28/July/2018
 * @version     28/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DS1307_status_t  DS1307_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   DS1307_SUCCESS;
    else
        return   DS1307_FAILURE;
}



/**
 * @brief       DS1307_ReadTemperatureRegister ( I2C_parameters_t , DS1307_vector_data_t* )
 *
 * @details     It gets the temperature register value ( raw temperature ).
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myTemperatureRegister: Temperature register value ( raw temperature ).
 *
 *
 * @return       Status of DS1307_ReadTemperatureRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        28/July/2018
 * @version     28/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_ReadTemperatureRegister ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTemperatureRegister )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read TEMPERATURE REGISTER to mask it */
    cmd[0]   =   DS1307_TEMPERATURE_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myTemperatureRegister->TemperatureRegister   =   ( cmd[0] << 8 );
    myTemperatureRegister->TemperatureRegister  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
        return   DS1307_SUCCESS;
    else
        return   DS1307_FAILURE;
}

