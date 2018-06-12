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



/**
 * @brief       TMP102_Read_T_LOW_Register ( I2C_parameters_t , TMP102_vector_data_t* )
 *
 * @details     It gets the low temperature register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTLOW_Register:   T_LOW register.
 *
 *
 * @return       Status of TMP102_Read_T_LOW_Register.
 *
 *
 * @author      Manuel Caballero
 * @date        11/June/2018
 * @version     11/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_Read_T_LOW_Register ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTLOW_Register )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    // Read TLOW REGISTER to mask it
    cmd[0]   =   TMP102_T_LOW_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse data
    myTLOW_Register->TLOW_Register  =   ( cmd[0] << 8 );
    myTLOW_Register->TLOW_Register |=   cmd[1];





    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_Write_T_LOW_Register ( I2C_parameters_t , TMP102_vector_data_t )
 *
 * @details     It updates the low temperature register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTLOW_Register:   New T_LOW value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_Write_T_LOW_Register.
 *
 *
 * @author      Manuel Caballero
 * @date        11/June/2018
 * @version     11/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_Write_T_LOW_Register ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t myTLOW_Register )
{
    uint8_t      cmd[]    =    { 0, 0, 0 };

    i2c_status_t aux;


    // Update TLOW REGISTER
    cmd[0]   =   TMP102_T_LOW_REGISTER;
    cmd[1]   =   ( myTLOW_Register.TLOW_Register >> 8 ) & 0xFF;                                                       // MSB
    cmd[2]   =   ( myTLOW_Register.TLOW_Register & 0xFF );                                                            // LSB
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );





    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_Read_T_HIGH_Register ( I2C_parameters_t , TMP102_vector_data_t* )
 *
 * @details     It gets the high temperature register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTHIGH_Register:  T_HIGH register.
 *
 *
 * @return       Status of TMP102_Read_T_HIGH_Register.
 *
 *
 * @author      Manuel Caballero
 * @date        11/June/2018
 * @version     11/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_Read_T_HIGH_Register ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTHIGH_Register )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    // Read THIGH REGISTER to mask it
    cmd[0]   =   TMP102_T_HIGH_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse data
    myTHIGH_Register->THIGH_Register  =   ( cmd[0] << 8 );
    myTHIGH_Register->THIGH_Register |=   cmd[1];





    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_Write_T_HIGH_Register ( I2C_parameters_t , TMP102_vector_data_t )
 *
 * @details     It updates the high temperature register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTHIGH_Register:  New T_HIGH value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_Write_T_HIGH_Register.
 *
 *
 * @author      Manuel Caballero
 * @date        11/June/2018
 * @version     11/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_Write_T_HIGH_Register ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t myTHIGH_Register )
{
    uint8_t      cmd[]    =    { 0, 0, 0 };

    i2c_status_t aux;


    // Update THIGH REGISTER
    cmd[0]   =   TMP102_T_HIGH_REGISTER;
    cmd[1]   =   ( myTHIGH_Register.THIGH_Register >> 8 ) & 0xFF;                                                   // MSB
    cmd[2]   =   ( myTHIGH_Register.THIGH_Register & 0xFF );                                                        // LSB
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );





    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_ReadConfigurationRegister ( I2C_parameters_t , TMP102_vector_data_t* )
 *
 * @details     It gets the configuration register value.
 *
 * @param[in]    myI2Cparameters:           I2C parameters.
 *
 * @param[out]   myConfigurationRegister:   Configuration register value.
 *
 *
 * @return       Status of TMP102_ReadConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        11/June/2018
 * @version     11/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_ReadConfigurationRegister ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myConfigurationRegister )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    // Read CONFIGURATION REGISTER
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse data
    myConfigurationRegister->ConfigurationRegister  =   ( cmd[0] << 8 );
    myConfigurationRegister->ConfigurationRegister |=   cmd[1];





    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}
