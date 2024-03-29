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


    /* Read TEMPERATURE REGISTER to mask it */
    cmd[0]   =   TMP102_TEMPERATURE_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
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


    /* Read TLOW REGISTER to mask it    */
    cmd[0]   =   TMP102_T_LOW_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
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


    /* Update TLOW REGISTER */
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


    /* Read THIGH REGISTER to mask it   */
    cmd[0]   =   TMP102_T_HIGH_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
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


    /* Update THIGH REGISTER    */
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


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myConfigurationRegister->ConfigurationRegister  =   ( cmd[0] << 8 );
    myConfigurationRegister->ConfigurationRegister |=   cmd[1];





    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_SetShutdownMode ( I2C_parameters_t , TMP102_configuration_shutdown_mode_t )
 *
 * @details     It enables shutdown/continuous mode operation.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySDMode:          Shutdown/continuous mode operation.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_SetShutdownMode.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_SetShutdownMode ( I2C_parameters_t myI2Cparameters, TMP102_configuration_shutdown_mode_t mySDMode )
{
    uint8_t      cmd[]    =  { 0, 0, 0 };
    uint16_t     myAuxReg =  0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_SD_MASK;
    myAuxReg   |=   mySDMode;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );

    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_SetThermostatMode ( I2C_parameters_t , TMP102_configuration_thermostat_mode_t )
 *
 * @details     It enables comparator/interrupt mode operation.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTMMode:          Comparator/interrupt mode operation.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_SetThermostatMode.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_SetThermostatMode ( I2C_parameters_t myI2Cparameters, TMP102_configuration_thermostat_mode_t myTMMode )
{
    uint8_t      cmd[]    =    { 0, 0, 0 };
    uint16_t     myAuxReg =    0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_TM_MASK;
    myAuxReg   |=   myTMMode;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );
    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_SetPolarityAlertPinOutput ( I2C_parameters_t , TMP102_configuration_polarity_t )
 *
 * @details     The polarity bit allows the user to adjust the polarity of the ALERT pin output.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPOLMode:         Polarity for ALERT pin output.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_SetPolarityAlertPinOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_SetPolarityAlertPinOutput ( I2C_parameters_t myI2Cparameters, TMP102_configuration_polarity_t myPOLMode )
{
    uint8_t      cmd[]    =  { 0, 0, 0 };
    uint16_t     myAuxReg =  0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_POL_MASK;
    myAuxReg   |=   myPOLMode;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );

    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_SetConsecutiveFaultsQueue ( I2C_parameters_t , TMP102_configuration_fault_queue_t )
 *
 * @details     The number of fault conditions required to generate an alert may be programmed using the fault queue.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myF1F0Mode:        Consecutive faults.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_SetConsecutiveFaultsQueue.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_SetConsecutiveFaultsQueue ( I2C_parameters_t myI2Cparameters, TMP102_configuration_fault_queue_t myF1F0Mode )
{
    uint8_t      cmd[]    =  { 0, 0, 0 };
    uint16_t     myAuxReg =  0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_F1F0_MASK;
    myAuxReg   |=   myF1F0Mode;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );

    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_TriggerSingleTemperatureConversion ( I2C_parameters_t )
 *
 * @details     When the device is in Shutdown Mode, writing a 1 to the OS bit starts a single temperature conversion.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_TriggerSingleTemperatureConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         The device has to be in shutdown mode in order to use this function.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_TriggerSingleTemperatureConversion ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]    =  { 0, 0, 0 };
    uint16_t     myAuxReg =  0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_OS_MASK;
    myAuxReg   |=   TMP102_CONFIGURATION_OS_START_SINGLE_TEMPERATURE_CONVERSION;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );

    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_SetModeOperation ( I2C_parameters_t , TMP102_configuration_extended_mode_bit_t )
 *
 * @details     It sets the device into Normal/Extended mode operation.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myEMMode:          Normal/Extended mode operation.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_SetModeOperation.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_SetModeOperation ( I2C_parameters_t myI2Cparameters, TMP102_configuration_extended_mode_bit_t myEMMode  )
{
    uint8_t      cmd[]    =  { 0, 0, 0 };
    uint16_t     myAuxReg =  0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_EM_MASK;
    myAuxReg   |=   myEMMode;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );

    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_SetConversionRate ( I2C_parameters_t , TMP102_configuration_conversion_rate_t )
 *
 * @details     It sets the conversion rate for the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myCR:              Conversion rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of TMP102_SetConversionRate.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     12/June/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_SetConversionRate ( I2C_parameters_t myI2Cparameters, TMP102_configuration_conversion_rate_t myCR  )
{
    uint8_t      cmd[]    =  { 0, 0, 0 };
    uint16_t     myAuxReg =  0;
    i2c_status_t aux;


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );


    /* Mask the result and update the register  */
    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    myAuxReg   &=  ~TMP102_CONFIGURATION_CR_MASK;
    myAuxReg   |=   myCR;

    cmd[1]      =   (uint8_t)( myAuxReg >> 8 );
    cmd[2]      =   (uint8_t)( myAuxReg & 0xFF );

    aux         =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}



/**
 * @brief       TMP102_GetTemperature ( I2C_parameters_t , TMP102_vector_data_t* )
 *
 * @details     It gets the temperature value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Current temperature.
 *
 *
 * @return       Status of TMP102_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2018
 * @version     18/June/2018   Negative temperature is processed properly.
 *              12/June/2018   The ORIGIN
 * @pre         The temperature Register variable is updated when this function is used.
 * @warning     N/A.
 */
TMP102_status_t  TMP102_GetTemperature ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperature )
{
    uint8_t      cmd[]       =   { 0, 0, 0 };
    uint32_t     myTempSig   =   0;
    uint16_t     myAuxReg    =   0;
    i2c_status_t aux;


    /* Read TEMPERATURE REGISTER  */
    cmd[0]   =   TMP102_TEMPERATURE_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );

    /* Update TEMPERATURE REGISTER  */
    myTemperature->TemperatureRegister   =   cmd[1];
    myTemperature->TemperatureRegister <<=   8;
    myTemperature->TemperatureRegister  |=   cmd[2];


    /* Read CONFIGURATION REGISTER  */
    cmd[0]   =   TMP102_CONFIGURATION_REGISTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2 );

    myAuxReg    =   cmd[1];
    myAuxReg  <<=   8;
    myAuxReg   |=   cmd[2];


    /* Check Extended-mode the sensor is working with    */
    if ( ( myAuxReg & TMP102_CONFIGURATION_EM_MASK ) == TMP102_CONFIGURATION_EM_NORMAL_MODE_OPERATION )
    {
        /* Normal mode 12-bit configuration   */
        myTemperature->TemperatureRegister >>=   4;
        myTempSig                            =   0x800;
    }
    else
    {
        /* Extended mode 13-bit configuration   */
        myTemperature->TemperatureRegister >>=   3;
        myTempSig                            =   0x1000;
    }


    /* Check if the temperature is positive/negative */
    if ( ( myTemperature->TemperatureRegister & myTempSig ) == myTempSig )
    {
        /* The temperature is NEGATIVE  */
        myTemperature->TemperatureRegister   =  ~myTemperature->TemperatureRegister;
        myTemperature->TemperatureRegister  +=   1;

        /* Update the temperature value */
        myTemperature->Temperature  =   ( -1.0 ) * ( (float)myTemperature->TemperatureRegister * 0.0625 );
    }
    else
    {
        /* The temperature is POSITIVE  */

        /* Update the temperature value */
        myTemperature->Temperature  =   ( (float)myTemperature->TemperatureRegister * 0.0625 );
    }




    if ( aux == I2C_SUCCESS )
        return   TMP102_SUCCESS;
    else
        return   TMP102_FAILURE;
}
