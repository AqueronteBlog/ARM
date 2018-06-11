/**
 * @brief       TMP102.c
 * @details     Low-Power Digital Temperature Sensor With SMBus and Two-Wire Serial.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/June/2018
 * @version     9/June/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "TMP102.h"


/**
 * @brief       TMP102_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        9/June/2018
 * @version     9/June/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
TMP102_status_t  TMP102_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_ReadTemperatureRegister ( I2C_parameters_t , TMP102_vector_data_t* )
 *
 * @details     It gets the temperature register value ( raw temperature ).
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myTemperatureRegister: Temperature register value ( raw temperature ).
 *
 *
 * @return       Status of TMP102_ReadTemperatureRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        11/June/2018
 * @version     11/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_ReadTemperatureRegister ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperatureRegister )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    // Read TEMPERATURE REGISTER to mask it
    cmd[0]   =   TMP102_TEMPERATURE_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse data
    myTemperatureRegister->TemperatureRegister   =   ( cmd[0] << 8 );
    myTemperatureRegister->TemperatureRegister  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}
