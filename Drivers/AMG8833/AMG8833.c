/**
 * @brief       AMG8833.c
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

#include "AMG8833.h"


/**
 * @brief       AMG8833_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AMG8833_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_GetManufacturerID ( I2C_parameters_t , AMG8833_data_t* )
 *
 * @details     It gets the manufacturer ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myManufacturerID:  Manufacturer ID.
 *
 *
 * @return       Status of AMG8833_GetManufacturerID.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_GetManufacturerID ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myManufacturerID )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_MANUFACTURER_ID;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myManufacturerID->ManufacturerID   =   ( cmd[0] << 8U );
    myManufacturerID->ManufacturerID  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_GetDeviceID ( I2C_parameters_t , AMG8833_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID.
 *
 *
 * @return       Status of AMG8833_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_GetDeviceID ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myDeviceID )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_DEVICE_ID;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myDeviceID->DeviceID   =   ( cmd[0] << 8U );
    myDeviceID->DeviceID  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_ReadConfigurationRegister ( I2C_parameters_t , AMG8833_data_t* )
 *
 * @details     It reads the configuration register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myConfReg:       Configuration register value.
 *
 *
 * @return       Status of AMG8833_ReadConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_ReadConfigurationRegister ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myConfReg )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myConfReg->ConfigurationRegister   =   ( cmd[0] << 8U );
    myConfReg->ConfigurationRegister  |=   cmd[1];




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_SoftwareReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AMG8833_SoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_SoftwareReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~RST_BIT_MASK ) | RST_SOFTWARE_RESET );
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_SetModeOperation ( I2C_parameters_t , AMG8833_mod_t )
 *
 * @details     It sets mode of operation.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myModeOpreation: Mode of operation ( low power mode ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AMG8833_SetModeOperation.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_SetModeOperation ( I2C_parameters_t myI2Cparameters, AMG8833_mod_t myModeOpreation )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~MOD_MASK ) | myModeOpreation );
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_SetConversionRate ( I2C_parameters_t , AMG8833_cr_t )
 *
 * @details     It sets conversion rate.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConversionRate:  Conversion rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AMG8833_SetConversionRate.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_SetConversionRate ( I2C_parameters_t myI2Cparameters, AMG8833_cr_t myConversionRate )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~CR_MASK ) | myConversionRate );
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_SetnDRDY_EnableBit ( I2C_parameters_t , AMG8833_en_t )
 *
 * @details     It sets conversion rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myEnableBit:     Enable bit pin behaviour.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AMG8833_SetnDRDY_EnableBit.
 *
 *
 * @author      Manuel Caballero
 * @date        7/December/2018
 * @version     7/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_SetnDRDY_EnableBit ( I2C_parameters_t myI2Cparameters, AMG8833_en_t myEnableBit )
{
    uint8_t      cmd[]    =    { 0U, 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 2U );

    /* Mask the option and update the register   */
    cmd[2]   =   cmd[1];
    cmd[1]   =   ( ( cmd[0] & ~EN_MASK ) | myEnableBit );
    cmd[0]   =   AMG8833_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_GetRawTemperature ( I2C_parameters_t , AMG8833_data_t* )
 *
 * @details     It reads raw temperature ( T_DIE ) value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature value.
 *
 *
 * @return       Status of AMG8833_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_GetRawTemperature ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myRawTemperature )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_LOCAL_TEMPERATURE;
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
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_GetRawSensorVoltage ( I2C_parameters_t , AMG8833_data_t* )
 *
 * @details     It reads raw sensor voltage result ( V_SENSOR ) register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawVoltage:    Raw sensor voltage value.
 *
 *
 * @return       Status of AMG8833_GetRawSensorVoltage.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AMG8833_status_t  AMG8833_GetRawSensorVoltage ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myRawVoltage )
{
    uint8_t      cmd[]    =    { 0U, 0U };
    i2c_status_t aux;


    /* Read the register */
    cmd[0]   =   AMG8833_SENSOR_VOLTAGE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myRawVoltage->SensorVoltageResultRegister   = cmd[0];
    myRawVoltage->SensorVoltageResultRegister <<= 8U;
    myRawVoltage->SensorVoltageResultRegister  |= cmd[1];
    



    if ( aux == I2C_SUCCESS )
    {
        return   AMG8833_SUCCESS;
    }
    else
    {
        return   AMG8833_FAILURE;
    }
}



/**
 * @brief       AMG8833_CalculateTemperature ( AMG8833_data_t* )
 *
 * @details     It calculates the real temperature ( T_DIE ) value.
 *
 * @param[in]    myRawTemperature:  Raw temperature value.
 *
 * @param[out]   myTemperature:     Real Temperature value.
 *
 *
 * @return       Status of AMG8833_CalculateTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     AMG8833_GetRawTemperature function must be called first.
 */
AMG8833_status_t  AMG8833_CalculateTemperature ( AMG8833_data_t* myTemperature  )
{
    uint8_t   myDataPosNeg  =   0U;
    uint16_t  aux           =   0U;

    aux  =   myTemperature->TemperatureRegister;

    /* Check if the temperature value is negative, MSB = 1  */
    if ( ( aux & 0x2000 ) == 0x2000 )
    {
      aux   =  ~aux;
      aux  +=   1U;

      myDataPosNeg   =   1U;
    }


    /* Parse the data   */
    myTemperature->TemperatureC   =  (float)( aux * TEMP_1LSB );                        // Celsius degrees
    
    if ( myDataPosNeg == 1U )
    {
      myTemperature->TemperatureC  *=  -1.0;
    }
    
    myTemperature->TemperatureK   =  (float)( myTemperature->TemperatureC + 273.15 );   // Kelvins degrees



    return   AMG8833_SUCCESS;
}



/**
 * @brief       AMG8833_CalculateSensorVoltage ( AMG8833_data_t* )
 *
 * @details     It calculates the real sensor voltage ( V_SENSOR ) value.
 *
 * @param[in]    SensorVoltageResultRegister:  Raw sensor voltage value.
 *
 * @param[out]   myV_sensor:                   Real sensor voltage value.
 *
 *
 * @return       Status of AMG8833_CalculateSensorVoltage.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     AMG8833_GetRawSensorVoltage function must be called first.
 */
AMG8833_status_t  AMG8833_CalculateSensorVoltage ( AMG8833_data_t* myV_sensor  )
{
    uint8_t   myDataPosNeg  =   0U;
    uint16_t  aux           =   0U;

    aux  =   myV_sensor->SensorVoltageResultRegister;

    /* Check if the sensor voltage value is negative, MSB = 1  */
    if ( ( aux & 0x8000 ) == 0x8000 )
    {
      aux   =  ~aux;
      aux  +=   1U;

      myDataPosNeg   =   1U;
    }

    /* Parse the data   */
    myV_sensor->V_Sensor   =  (float)( aux * SVOL_1LSB / 1000000000.0 ); 
                           
    if ( myDataPosNeg == 1U )
    {
      myV_sensor->V_Sensor  *=  -1.0;
    }



    return   AMG8833_SUCCESS;
}



/**
 * @brief       AMG8833_CalculateObjectTemperature ( AMG8833_data_t* )
 *
 * @details     It calculates the real temperature ( T_DIE ) value.
 *
 * @param[in]    myRawTemperature:  Raw temperature value.
 *
 * @param[out]   myObjTemperature:  Real Object Temperature value.
 *
 *
 * @return       Status of AMG8833_CalculateObjectTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        10/December/2018
 * @version     10/December/2018   The ORIGIN
 * @pre         N/A.
 * @warning     AMG8833_CalculateTemperature and AMG8833_GetRawSensorVoltage functions must be called first.
 */
AMG8833_status_t  AMG8833_CalculateObjectTemperature ( AMG8833_data_t* myObjTemperature  )
{
    double s       =   0.0;
    double v_os    =   0.0;
    double f_v_obj =   0.0;


    /* Claculate the sensitivity of the thermopile sensor  */
    s  =   myObjTemperature->s0 * ( 1 + A1 * ( myObjTemperature->TemperatureK - T_REF ) + A2 * pow( ( myObjTemperature->TemperatureK - T_REF ), 2U ) );

    /* Calculate the offset voltage  */
    v_os   =   B0 + B1 * ( myObjTemperature->TemperatureK - T_REF ) + B2 * pow( ( myObjTemperature->TemperatureK - T_REF ), 2U );
    
    /* Model the Seebeck coefficients of the thermopile  */
    f_v_obj  =   ( myObjTemperature->V_Sensor - v_os ) + C2 * pow( ( myObjTemperature->V_Sensor - v_os ), 2U );
    
    /* Relates the radiant transfer of IR energy between the target object and the AMG8833 and the conducted heat in the thermopile in the AMG8833  */ 
    myObjTemperature->ObjectTemperatureK    =  sqrt( sqrt( pow( myObjTemperature->TemperatureK, 4U ) + ( f_v_obj / s ) ) );
    myObjTemperature->ObjectTemperatureC    =  ( myObjTemperature->ObjectTemperatureK - 273.15 );



    return   AMG8833_SUCCESS;
}