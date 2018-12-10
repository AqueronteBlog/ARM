/**
 * @brief       TMP006.c
 * @details     Infrared Thermopile Sensor in Chip-Scale Package.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "TMP006.h"


/**
 * @brief       TMP006_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP006_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
TMP006_status_t  TMP006_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_GetManufacturerID ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It gets the manufacturer ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myManufacturerID:  Manufacturer ID.
 *
 *
 * @return       Status of TMP006_GetManufacturerID.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_GetManufacturerID ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myManufacturerID )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_MANUFACTURER_ID;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myManufacturerID->ManufacturerID   =   ( cmd[0] << 8U );
    myManufacturerID->ManufacturerID  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_GetDeviceID ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID.
 *
 *
 * @return       Status of TMP006_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_GetDeviceID ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myDeviceID )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_DEVICE_ID;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myDeviceID->DeviceID   =   ( cmd[0] << 8U );
    myDeviceID->DeviceID  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_ReadConfigurationRegister ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It reads the configuration register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myConfReg:       Configuration register value.
 *
 *
 * @return       Status of TMP006_ReadConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_ReadConfigurationRegister ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myConfReg )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myConfReg->ConfigurationRegister   =   ( cmd[0] << 8U );
    myConfReg->ConfigurationRegister  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_SoftwareReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP006_SoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_SoftwareReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~RST_BIT_MASK ) | RST_SOFTWARE_RESET );
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_SetModeOperation ( I2C_parameters_t , TMP006_mod_t )
 *
 * @details     It sets mode of operation.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myModeOpreation: Mode of operation ( low power mode ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP006_SetModeOperation.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_SetModeOperation ( I2C_parameters_t myI2Cparameters, TMP006_mod_t myModeOpreation )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~MOD_MASK ) | myModeOpreation );
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_SetConversionRate ( I2C_parameters_t , TMP006_cr_t )
 *
 * @details     It sets conversion rate.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConversionRate:  Conversion rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP006_SetConversionRate.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_SetConversionRate ( I2C_parameters_t myI2Cparameters, TMP006_cr_t myConversionRate )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~CR_MASK ) | myConversionRate );
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_SetnDRDY_EnableBit ( I2C_parameters_t , TMP006_en_t )
 *
 * @details     It sets conversion rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myEnableBit:     Enable bit pin behaviour.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP006_SetnDRDY_EnableBit.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_SetnDRDY_EnableBit ( I2C_parameters_t myI2Cparameters, TMP006_en_t myEnableBit )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~EN_MASK ) | myEnableBit );
    cmd[0]   =   TMP006_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_GetRawTemperature ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It reads raw temperature ( T_DIE ) value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature value.
 *
 *
 * @return       Status of TMP006_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_GetRawTemperature ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myRawTemperature )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_LOCAL_TEMPERATURE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myRawTemperature->TemperatureRegister   = cmd[0];
    myRawTemperature->TemperatureRegister <<= 8U;
    myRawTemperature->TemperatureRegister  |= cmd[1];
    
    /* Temperature register is configured as a 14-bit value   */
    myRawTemperature->TemperatureRegister >>= 2U;




    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_GetRawSensorVoltage ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It reads raw sensor voltage result ( V_SENSOR ) register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawVoltage:    Raw sensor voltage value.
 *
 *
 * @return       Status of TMP006_GetRawSensorVoltage.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP006_status_t  TMP006_GetRawSensorVoltage ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myRawVoltage )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   TMP006_SENSOR_VOLTAGE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myRawVoltage->SensorVoltageResultRegister   = cmd[0];
    myRawVoltage->SensorVoltageResultRegister <<= 8U;
    myRawVoltage->SensorVoltageResultRegister  |= cmd[1];
    



    if ( aux == I2C_SUCCESS )
    {
        return   TMP006_SUCCESS;
    }
    else
    {
        return   TMP006_FAILURE;
    }
}



/**
 * @brief       TMP006_CalculateTemperature ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It calculates the real temperature ( T_DIE ) value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRawTemperature:  Raw temperature value.
 *
 * @param[out]   myTemperature:     Real Temperature value.
 *
 *
 * @return       Status of TMP006_CalculateTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     TMP006_GetRawTemperature function must be called first.
 */
TMP006_status_t  TMP006_CalculateTemperature ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myTemperature  )
{
    uint16_t  aux  =   0U;

    aux  =   myTemperature->TemperatureRegister;

    /* Check if the temperature value is negative, MSB = 1  */
    if ( ( aux & 0x2000 ) == 0x2000 )
    {
      aux   =  ~aux;
      aux  +=   1U;
    }


    /* Parse the data   */
    myTemperature->TemperatureC   =  (float)( aux * TEMP_1LSB );                        // Celsius degrees
    myTemperature->TemperatureK   =  (float)( myTemperature->TemperatureC + 273.15 );   // Kelvins degrees



    return   TMP006_SUCCESS;
}



/**
 * @brief       TMP006_CalculateObjectTemperature ( I2C_parameters_t , TMP006_data_t* )
 *
 * @details     It calculates the real temperature ( T_DIE ) value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRawTemperature:  Raw temperature value.
 *
 * @param[out]   myObjTemperature:  Real Object Temperature value.
 *
 *
 * @return       Status of TMP006_CalculateObjectTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     TMP006_GetRawTemperature function must be called first.
 */
TMP006_status_t  TMP006_CalculateObjectTemperature ( I2C_parameters_t myI2Cparameters, TMP006_data_t* myObjTemperature  )
{
    float     s       =   0.0;
    float     v_os    =   0.0;
    float     f_v_obj =   0.0;
    uint16_t  aux     =   0U;

    /* Claculate the sensitivity of the thermopile sensor  */
    s  =   myObjTemperature->s0 * ( 1 + A1 * ( myObjTemperature->TemperatureK - T_REF ) + A2 * pow( ( myObjTemperature->TemperatureK - T_REF ), 2U ) );

    /* Calculate the offset voltage  */
    v_os   =   B0 + B1 * ( myObjTemperature->TemperatureK - T_REF ) + B2 * pow( ( myObjTemperature->TemperatureK - T_REF ), 2U );
    
    /* Model the Seebeck coefficients of the thermopile  */
    f_v_obj  =   ( myObjTemperature->SensorVoltageResultRegister - v_os ) + C2 * pow( ( myObjTemperature->SensorVoltageResultRegister - v_os ), 2U );
    
    /* Relates the radiant transfer of IR energy between the target object and the TMP006 and the conducted heat in the thermopile in the TMP006  */ 
    myObjTemperature->ObjectTemperatureK    =  sqrt( sqrt( pow( myObjTemperature->TemperatureK, 4U ) + ( f_v_obj / s ) ) );
    myObjTemperature->ObjectTemperatureC    =  ( myObjTemperature->ObjectTemperatureK - 273.15 );



    return   TMP006_SUCCESS;
}