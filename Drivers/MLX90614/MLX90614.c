/**
 * @brief       MLX90614.c
 * @details     Single and Dual Zone Infra Red Thermometer.
 *              Function file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        23/December/2017
 * @version     23/December/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "MLX90614.h"


/**
 * @brief       MLX90614_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MLX90614_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        23/December/2017
 * @version     23/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}



/**
 * @brief       MLX90614_GetID_Numbers ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It gets the ID numbers.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myID:              ID numbers.
 *
 *
 * @return       Status of MLX90614_GetID_Numbers.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_GetID_Numbers ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myID )
{
    uint8_t      cmd[]       =   { 0, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the ID 0
    cmd[0]   =   MLX90614_ID_NUMBER_0;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    myID->ID[0]  =   ( ( cmd[1] << 8 ) | cmd[0] );


    // It gets the ID 1
    cmd[0]   =   MLX90614_ID_NUMBER_1;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    myID->ID[1]  =   ( ( cmd[1] << 8 ) | cmd[0] );


    // It gets the ID 2
    cmd[0]   =   MLX90614_ID_NUMBER_2;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    myID->ID[2]  =   ( ( cmd[1] << 8 ) | cmd[0] );


    // It gets the ID 3
    cmd[0]   =   MLX90614_ID_NUMBER_3;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    myID->ID[3]  =   ( ( cmd[1] << 8 ) | cmd[0] );




    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}


/**
 * @brief       MLX90614_ReadRawTA ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It raw ambient temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTA:           Raw ambient temperature.
 *
 *
 * @return       Status of MLX90614_ReadRawTA.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_ReadRawTA ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTA )
{
    uint8_t      cmd[]       =   { MLX90614_TA, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the raw ambient temperature
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    myRawTA->RawTA  =   ( ( cmd[1] << 8 ) | cmd[0] );
    myRawTA->PEC    =   cmd[2];

    // Check if flag error is triggered ( faulty if so )
    if ( ( myRawTA->RawTA & MLX90614_FLAG_ERROR ) == MLX90614_FLAG_ERROR )
        return   MLX90614_FAILURE;


    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}


/**
 * @brief       MLX90614_ReadTA ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It ambient temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTA:              Ambient temperature in Celsius.
 *
 *
 * @return       Status of MLX90614_ReadTA.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_ReadTA ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myTA )
{
    uint8_t      cmd[]       =   { MLX90614_TA, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the raw ambient temperature
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    myTA->TA  =   ( MLX90614_KELVIN_CONVERSION * ( ( ( cmd[1] << 8 ) | cmd[0] ) ) ) - MLX90614_KELVIN_TO_CELSIUS;
    myTA->PEC =   cmd[2];

    // Check if flag error is triggered ( faulty if so )
    if ( ( cmd[1] & ( MLX90614_FLAG_ERROR >> 8 ) ) == ( MLX90614_FLAG_ERROR >> 8 ) )
        return   MLX90614_FAILURE;


    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}


/**
 * @brief       MLX90614_ReadRawTObj1 ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It raw object 1 temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTObj1:        Raw object 1 temperature.
 *
 *
 * @return       Status of MLX90614_ReadRawTObj1.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_ReadRawTObj1 ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTObj1 )
{
    uint8_t      cmd[]       =   { MLX90614_TOBJ_1, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the raw object 1 temperature
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    myRawTObj1->RawTObj1  =   ( ( cmd[1] << 8 ) | cmd[0] );
    myRawTObj1->PEC       =   cmd[2];

    // Check if flag error is triggered ( faulty if so )
    if ( ( myRawTObj1->RawTObj1 & MLX90614_FLAG_ERROR ) == MLX90614_FLAG_ERROR )
        return   MLX90614_FAILURE;


    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}


/**
 * @brief       MLX90614_ReadTObj1 ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It object 1 temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTObj1:           Object 1 temperature in Celsius.
 *
 *
 * @return       Status of MLX90614_ReadTObj1.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_ReadTObj1 ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myTObj1 )
{
    uint8_t      cmd[]       =   { MLX90614_TOBJ_1, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the raw object 1 temperature
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    myTObj1->TObj1  =   ( MLX90614_KELVIN_CONVERSION * ( ( ( cmd[1] << 8 ) | cmd[0] ) ) ) - MLX90614_KELVIN_TO_CELSIUS;
    myTObj1->PEC    =   cmd[2];

    // Check if flag error is triggered ( faulty if so )
    if ( ( cmd[1] & ( MLX90614_FLAG_ERROR >> 8 ) ) == ( MLX90614_FLAG_ERROR >> 8 ) )
        return   MLX90614_FAILURE;


    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}


/**
 * @brief       MLX90614_ReadRawTObj2 ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It raw object 2 temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTObj1:        Raw object 2 temperature.
 *
 *
 * @return       Status of MLX90614_ReadRawTObj2.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_ReadRawTObj2 ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myRawTObj2 )
{
    uint8_t      cmd[]       =   { MLX90614_TOBJ_2, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the raw object 1 temperature
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    myRawTObj2->RawTObj2  =   ( ( cmd[1] << 8 ) | cmd[0] );
    myRawTObj2->PEC       =   cmd[2];

    // Check if flag error is triggered ( faulty if so )
    if ( ( myRawTObj2->RawTObj2 & MLX90614_FLAG_ERROR ) == MLX90614_FLAG_ERROR )
        return   MLX90614_FAILURE;


    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}


/**
 * @brief       MLX90614_ReadTObj2 ( I2C_parameters_t , MLX90614_vector_data_t* )
 *
 * @details     It object 2 temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTObj2:           Object 2 temperature in Celsius.
 *
 *
 * @return       Status of MLX90614_ReadTObj2.
 *
 *
 * @author      Manuel Caballero
 * @date        25/December/2017
 * @version     25/December/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
MLX90614_status_t  MLX90614_ReadTObj2 ( I2C_parameters_t myI2Cparameters, MLX90614_vector_data_t*  myTObj2 )
{
    uint8_t      cmd[]       =   { MLX90614_TOBJ_2, 0, 0 };
    uint32_t     aux         =   0;


    // It gets the raw object 2 temperature
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    myTObj2->TObj2  =   ( MLX90614_KELVIN_CONVERSION * ( ( ( cmd[1] << 8 ) | cmd[0] ) ) ) - MLX90614_KELVIN_TO_CELSIUS;
    myTObj2->PEC    =   cmd[2];

    // Check if flag error is triggered ( faulty if so )
    if ( ( cmd[1] & ( MLX90614_FLAG_ERROR >> 8 ) ) == ( MLX90614_FLAG_ERROR >> 8 ) )
        return   MLX90614_FAILURE;


    if ( aux == I2C_SUCCESS )
        return   MLX90614_SUCCESS;
    else
        return   MLX90614_FAILURE;
}

