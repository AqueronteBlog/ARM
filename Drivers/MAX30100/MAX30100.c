/**
 * @brief       MAX30100.c
 * @details     Pulse Oximeter and Heart-Rate Sensor IC for Wearable Health.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/July/2018
 * @version     9/July/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "MAX30100.h"


/**
 * @brief       MAX30100_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        9/July/2018
 * @version     9/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_ReadInterruptStatus ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It gets the interrupt status value.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myInterruptStatus:     Interrupt status register.
 *
 *
 * @return       Status of MAX30100_ReadInterruptStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_ReadInterruptStatus ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myInterruptStatus )
{
    uint8_t      cmd    =    0;

    i2c_status_t aux;


    /* Read INTERRUPT STATUS register    */
    cmd      =   MAX30100_INTERRUPT_STATUS;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd, 1 );


    /* Parse data   */
    myInterruptStatus->InterruptStatus   =   cmd;



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_InterrupEnable ( I2C_parameters_t , uint8_t )
 *
 * @details     It sets which interrupt is enabled/disabled.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myInterruptEnable      Interrupts to be enabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_InterrupEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_InterrupEnable ( I2C_parameters_t myI2Cparameters, uint8_t myInterruptEnable )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read INTERRUPT ENABLE register    */
    cmd[0]   =   MAX30100_INTERRUPT_ENABLE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~( INTERRUPT_ENABLE_ENB_A_FULL_MASK | INTERRUPT_ENABLE_ENB_TEP_RDY_MASK | INTERRUPT_ENABLE_ENB_HR_RDY_MASK | INTERRUPT_ENABLE_ENB_SO2_RDY_MASK );
    cmd[1]  |=   myInterruptEnable;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_ShutdownControl ( I2C_parameters_t , MAX30100_mode_configuration_shdn_t )
 *
 * @details     It sets the power mode.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myPowerMode            power mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_ShutdownControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_ShutdownControl ( I2C_parameters_t myI2Cparameters, MAX30100_mode_configuration_shdn_t myPowerMode )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read MODE CONFIGURATION register    */
    cmd[0]   =   MAX30100_MODE_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~MODE_CONFIGURATION_SHDN_MASK;
    cmd[1]  |=   myPowerMode;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_SoftwareReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_SoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         The RESET bit is cleared automatically back to zero after the reset sequence is completed.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_SoftwareReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read MODE CONFIGURATION register    */
    cmd[0]   =   MAX30100_MODE_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~MODE_CONFIGURATION_RESET_MASK;
    cmd[1]  |=   MODE_CONFIGURATION_RESET_ENABLE;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_TriggerTemperature ( I2C_parameters_t )
 *
 * @details     It initiates a single temperature reading from the temperature sensor.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_TriggerTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         This bit is cleared automatically back to zero at the conclusion of the temperature
 *              reading when the bit is set to one in heart rate or SpO2 mode.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_TriggerTemperature ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read MODE CONFIGURATION register    */
    cmd[0]   =   MAX30100_MODE_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~MODE_CONFIGURATION_TEMP_EN_MASK;
    cmd[1]  |=   MODE_CONFIGURATION_TEMP_EN_ENABLE;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_ModeControl ( I2C_parameters_t , MAX30100_mode_configuration_mode_t )
 *
 * @details     It sets the operating state of the MAX30100.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 * @param[in]    myModeControl:       Mode Control.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_ModeControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         Changing modes does not change any other setting, nor does it erase any previously stored
 *              data inside the data registers.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_ModeControl ( I2C_parameters_t myI2Cparameters, MAX30100_mode_configuration_mode_t myModeControl )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read MODE CONFIGURATION register    */
    cmd[0]   =   MAX30100_MODE_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~MODE_CONFIGURATION_MODE_MASK;
    cmd[1]  |=   myModeControl;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_SpO2_HighResolution ( I2C_parameters_t , MAX30100_spo2_configuration_spo2_hi_res_en_t )
 *
 * @details     It sets the SpO2 ADC resolution is 16-bit with 1.6ms LED pulse width.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myRes:                 SpO2 High Resolution Enable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_SpO2_HighResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_SpO2_HighResolution ( I2C_parameters_t myI2Cparameters, MAX30100_spo2_configuration_spo2_hi_res_en_t myRes )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read SPO2 CONFIGURATION register    */
    cmd[0]   =   MAX30100_SPO2_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~SPO2_CONFIGURATION_SPO2_HI_RES_EN_MASK;
    cmd[1]  |=   myRes;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_SpO2_SampleRateControl ( I2C_parameters_t , MAX30100_spo2_configuration_spo2_hi_res_en_t )
 *
 * @details     It defines the effective sampling rate.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    mySampleRate:          Effective sampling rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_SpO2_SampleRateControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     The allowed sample rates for both SpO2 and HR mode are summarized in Table 8 and Table 9 in the Data-sheet.
 *              The user MUST take care of this.
 */
MAX30100_status_t  MAX30100_SpO2_SampleRateControl ( I2C_parameters_t myI2Cparameters, MAX30100_spo2_configuration_spo2_sr_t mySampleRate )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read SPO2 CONFIGURATION register    */
    cmd[0]   =   MAX30100_SPO2_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~SPO2_CONFIGURATION_SPO2_SR_MASK;
    cmd[1]  |=   mySampleRate;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_LED_PulseWidthControl ( I2C_parameters_t , MAX30100_vector_data_t )
 *
 * @details     It sets the LED pulse width.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 * @param[in]    myLEDWidth:          Effective sampling rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_LED_PulseWidthControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     The allowed sample rates for both SpO2 and HR mode are summarized in Table 8 and Table 9 in the Data-sheet.
 *              The user MUST take care of this.
 */
MAX30100_status_t  MAX30100_LED_PulseWidthControl ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t myLEDWidth )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read SPO2 CONFIGURATION register    */
    cmd[0]   =   MAX30100_SPO2_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~SPO2_CONFIGURATION_LED_PW_MASK;
    cmd[1]  |=   myLEDWidth.Resolution;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_SetRed_LED_CurrentControl ( I2C_parameters_t , MAX30100_led_configuration_red_pa_t )
 *
 * @details     It sets the current level of the Red LED.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRedLED:          Current level of the Red LED.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_SetRed_LED_CurrentControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_SetRed_LED_CurrentControl ( I2C_parameters_t myI2Cparameters, MAX30100_led_configuration_red_pa_t myRedLED )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read LED CONFIGURATION register    */
    cmd[0]   =   MAX30100_LED_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~LED_CONFIGURATION_RED_PA_MASK;
    cmd[1]  |=   myRedLED;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_SetIR_LED_CurrentControl ( I2C_parameters_t , MAX30100_led_configuration_red_pa_t )
 *
 * @details     It sets the current level of the IR LED.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRedLED:          Current level of the IR LED.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX30100_SetIR_LED_CurrentControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_SetIR_LED_CurrentControl ( I2C_parameters_t myI2Cparameters, MAX30100_led_configuration_ir_pa_t myIRLED )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read LED CONFIGURATION register    */
    cmd[0]   =   MAX30100_LED_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    /* Parse data   */
    cmd[1]  &=  ~LED_CONFIGURATION_IR_PA_MASK;
    cmd[1]  |=   myIRLED;

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_GetRawTemperature ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It gets the raw temperature data ( temperature integer and temperature fraction ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Temperature integer and temperature fraction
 *
 *
 * @return       Status of MAX30100_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_GetRawTemperature ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myRawTemperature )
{
    uint8_t      cmd[]    =  { 0, 0 };

    i2c_status_t aux;


    /* Read TEMP_INTEGER and TEMP_FRACTION register ( auto-increment )    */
    cmd[0]   =   MAX30100_TEMP_INTEGER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse data   */
    myRawTemperature->Temp_Integer   =   cmd[0];
    myRawTemperature->Temp_Fraction  =   cmd[1];



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_GetTemperature ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It gets the temperature value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Temperature
 *
 *
 * @return       Status of MAX30100_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         This function updates both Temp_Integer and Temp_Fraction values.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_GetTemperature ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTemperature )
{
    MAX30100_status_t   myMAX30100Status;


    /* Get the raw temperature    */
    myMAX30100Status     =   MAX30100_GetRawTemperature ( myI2Cparameters, myTemperature );

    /* Process the temperature    */
    if ( ( myTemperature->Temp_Integer & 0x80 ) == 0x80 )
    {
        /* Negative temperature     */
        myTemperature->Temp_Integer   =  ~myTemperature->Temp_Integer;
        myTemperature->Temp_Integer  +=   1;

        myTemperature->Temperature   =   ( -1.0 ) * ( (float)( myTemperature->Temp_Integer + (float)( myTemperature->Temp_Fraction * 0.0625 ) ) );
    }
    else
    {
        /* Positive temperature     */
        myTemperature->Temperature   =   (float)( myTemperature->Temp_Integer + (float)( myTemperature->Temp_Fraction * 0.0625 ) );
    }





    if ( myMAX30100Status == MAX30100_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_GetRevisionID ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It gets the revision ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRevisionID:      Revision ID
 *
 *
 * @return       Status of MAX30100_GetRevisionID.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_GetRevisionID ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myRevisionID )
{
    uint8_t      cmd    =  0;

    i2c_status_t aux;


    /* Read REVISION ID register    */
    cmd      =   MAX30100_REVISION_ID;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    /* Parse data   */
    myRevisionID->RevisionID   =   cmd;



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_GetPartID ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It gets the part ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPartID:          Part ID
 *
 *
 * @return       Status of MAX30100_GetPartID.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_GetPartID ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myPartID )
{
    uint8_t      cmd    =  0;

    i2c_status_t aux;


    /* Read PART ID register    */
    cmd      =   MAX30100_PART_ID;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    /* Parse data   */
    myPartID->PartID   =   cmd;



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_PollingTemperatureConversion ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It gets the TEMP_EN value in Mode Configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTempFlag:        Temperature flag
 *
 *
 * @return       Status of MAX30100_PollingTemperatureConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_PollingTemperatureConversion ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTempFlag )
{
    uint8_t      cmd    =  0;

    i2c_status_t aux;


    /* Read MODE CONFIGURATION register    */
    cmd      =   MAX30100_MODE_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    /* Parse data   */
    myTempFlag->TemperatureFlag   =   (MAX30100_mode_configuration_temp_en_t)( cmd & MODE_CONFIGURATION_TEMP_EN_MASK );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_PollingSoftwareReset ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It checks if the software reset was completed by polling mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myResetFlag:       Reset flag
 *
 *
 * @return       Status of MAX30100_PollingSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_PollingSoftwareReset ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myResetFlag )
{
    uint8_t      cmd    =  0;

    i2c_status_t aux;


    /* Read MODE CONFIGURATION register    */
    cmd      =   MAX30100_MODE_CONFIGURATION;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    /* Parse data   */
    myResetFlag->ResetFlag   =   (MAX30100_mode_configuration_reset_t)( cmd & MODE_CONFIGURATION_RESET_MASK );



    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_ReadFIFO ( I2C_parameters_t , MAX30100_vector_data_t* , uint32_t )
 *
 * @details     It checks if the software reset was completed by polling mode.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myNumSamplesToRead:    Number of samples to read.
 *
 * @param[out]   myDATA:            Data from the FIFO
 *
 *
 * @return       Status of MAX30100_ReadFIFO.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_ReadFIFO ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myDATA, uint32_t myNumSamplesToRead )
{
    uint8_t      cmd[3]                 =  { 0 } ;
    uint32_t     num_available_samples   =   0;
    uint32_t     i                       =   0;
    i2c_status_t aux;


    /* Check the sample size     */
    if ( ( myNumSamplesToRead > 0 ) && ( myNumSamplesToRead < 17 ) )
    {
        /* FIRST TRANSACTION: Get the FIFO_WR_PTR, OVF_COUNTER and FIFO_RD_PTR    */
        cmd[0]   =   MAX30100_FIFO_WRITE_POINTER;
        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
        aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

        /* Parse data   */
        myDATA->FIFO_wr_ptr   =   ( cmd[0] & FIFO_FIFO_WRITE_POINTER_MASK );
        myDATA->OVF_counter   =   ( cmd[1] & FIFO_OVER_FLOW_COUNTER_MASK );
        myDATA->FIFO_rd_ptr   =   ( cmd[2] & FIFO_FIFO_READ_POINTER_MASK );


        /* If the FIFO is full, just start reading data  */
        if ( myDATA->OVF_counter == 0xF )
        {
            /* Get data from FIFO    */
            cmd[0]   =   MAX30100_FIFO_DATA_REGISTER;
            aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
            aux      =   i2c_read  ( myI2Cparameters, &myDATA->FIFO_buff[0], ( myNumSamplesToRead << 2U ) );

            /* Parse the data    */
            for ( i = 0; i < myNumSamplesToRead; i++ )
            {
                myDATA->FIFO_IR_samples[i]     =   myDATA->FIFO_buff[ ( i << 2 ) ];
                myDATA->FIFO_IR_samples[i]   <<=   8U;
                myDATA->FIFO_IR_samples[i]    |=   myDATA->FIFO_buff[ ( i << 2 ) + 1 ];

                myDATA->FIFO_RED_samples[i]    =   myDATA->FIFO_buff[ ( i << 2 ) + 2 ];
                myDATA->FIFO_RED_samples[i]  <<=   8U;
                myDATA->FIFO_RED_samples[i]   |=   myDATA->FIFO_buff[ ( ( i << 2 ) + 2 ) + 1 ];
            }
        }
        else
        {
            /* Evaluate the number of samples to be read from the FIFO    */
            num_available_samples    =   (uint32_t)( myDATA->FIFO_wr_ptr - myDATA->FIFO_rd_ptr );


            /* SECOND TRANSACTION: Read 'myNumSamplesToRead' samples from the FIFO    */
            if ( myNumSamplesToRead <= num_available_samples )
            {
                /* Get data from FIFO    */
                cmd[0]   =   MAX30100_FIFO_DATA_REGISTER;
                aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
                aux      =   i2c_read  ( myI2Cparameters, &myDATA->FIFO_buff[0], ( myNumSamplesToRead << 2U ) );

                /* Parse the data    */
                for ( i = 0; i < myNumSamplesToRead; i++ )
                {
                    myDATA->FIFO_IR_samples[i]     =   myDATA->FIFO_buff[ ( i << 2 ) ];
                    myDATA->FIFO_IR_samples[i]   <<=   8U;
                    myDATA->FIFO_IR_samples[i]    |=   myDATA->FIFO_buff[ ( i << 2 ) + 1 ];

                    myDATA->FIFO_RED_samples[i]    =   myDATA->FIFO_buff[ ( i << 2 ) + 2 ];
                    myDATA->FIFO_RED_samples[i]  <<=   8U;
                    myDATA->FIFO_RED_samples[i]   |=   myDATA->FIFO_buff[ ( ( i << 2 ) + 2 ) + 1 ];
                }
            }
            else
            {
                /* THIRD TRANSACTION: Write to FIFO_RD_PTR register. If the second transaction was successful, FIFO_RD_PTR points to the next sample in the FIFO,
                                      and this third transaction is not necessary. Otherwise, the processor updates the FIFO_RD_PTR appropriately, so that the samples are reread
                */

                // [TODO] NOT IMPLEMENTED

                return   MAX30100_FAILURE;
            }
        }
    }





    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}



/**
 * @brief       MAX30100_ClearFIFO ( I2C_parameters_t , MAX30100_vector_data_t* )
 *
 * @details     It clears the FIFO_WR_PTR, OVF_COUNTER, and FIFO_RD_PTR
 *              registers to all zeros (0x00) to ensure the FIFO is empty and in a known state.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDATA:            Data from the FIFO
 *
 *
 * @return       Status of MAX30100_ClearFIFO.
 *
 *
 * @author      Manuel Caballero
 * @date        12/July/2018
 * @version     12/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX30100_status_t  MAX30100_ClearFIFO ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myDATA )
{
    uint8_t      cmd[]    =  { 0, 0, 0, 0 } ;

    i2c_status_t aux;


    /* Update the FIFO_WR_PTR, FIFO_WR_PTR and OVF_COUNTER registers    */
    cmd[0]   =   MAX30100_FIFO_WRITE_POINTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    /* Get the FIFO_WR_PTR, OVF_COUNTER and FIFO_RD_PTR    */
    cmd[0]   =   MAX30100_FIFO_WRITE_POINTER;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 3 );


    /* Update data   */
    myDATA->FIFO_wr_ptr   =   ( cmd[0] & FIFO_FIFO_WRITE_POINTER_MASK );
    myDATA->OVF_counter   =   ( cmd[1] & FIFO_OVER_FLOW_COUNTER_MASK );
    myDATA->FIFO_rd_ptr   =   ( cmd[2] & FIFO_FIFO_READ_POINTER_MASK );




    if ( aux == I2C_SUCCESS )
        return   MAX30100_SUCCESS;
    else
        return   MAX30100_FAILURE;
}
