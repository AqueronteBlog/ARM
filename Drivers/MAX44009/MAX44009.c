/**
 * @brief       MAX44009.c
 * @details     Industry's Lowest-Power Ambient Light Sensor with ADC.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "MAX44009.h"


/**
 * @brief       MAX44009_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX44009_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_ReadInterruptStatus ( I2C_parameters_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the interrupt status value.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myInterruptStatus:     Interrupt status register.
 *
 *
 * @return       Status of MAX44009_ReadInterruptStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_ReadInterruptStatus ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myInterruptStatus )
{
    uint8_t      cmd    =    0U;
    i2c_status_t aux;


    /* Read INTERRUPT STATUS register    */
    cmd      =   MAX44009_INTERRUPT_STATUS;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd, 1U );


    /* Parse data   */
    myInterruptStatus->interruptStatus   =   ( cmd & INTERRUPT_STATUS_INTS_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_InterrupEnable ( I2C_parameters_t , MAX44009_interrupt_enable_ints_t )
 *
 * @details     It enables/disables the interrupt.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myInterruptEnable      Enable/Disable the interrupt.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX44009_InterrupEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_InterrupEnable ( I2C_parameters_t myI2Cparameters, MAX44009_interrupt_enable_ints_t myInterruptEnable )
{
    uint8_t      cmd[]    =  { 0U, 0U };
    i2c_status_t aux;


    /* Update the register   */
    cmd[0]   =   MAX44009_INTERRUPT_ENABLE;
    cmd[1]   =   myInterruptEnable;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_Configuration ( I2C_parameters_t , MAX44009_configuration_cont_t , MAX44009_configuration_manual_t , MAX44009_configuration_cdr_t , MAX44009_configuration_tim_t )
 *
 * @details     It configures the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myContinuousMode:  Default/Continuous mode.
 * @param[in]    myManualMode:      Default/Manual mode.
 * @param[in]    myCurrentRatio:    Current division ratio.
 * @param[in]    myIntegrationTime: Integration time.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MAX44009_Configuration.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         In automatic mode ( MANUAL = 0 ), reading the contents of TIM<2:0> and CDR bits reflects the automatically generated values from an internal timing register and are read-only.
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_Configuration ( I2C_parameters_t myI2Cparameters, MAX44009_configuration_cont_t myContinuousMode, MAX44009_configuration_manual_t myManualMode,
                                            MAX44009_configuration_cdr_t myCurrentRatio, MAX44009_configuration_tim_t myIntegrationTime )
{
    uint8_t      cmd[]    =  { 0U, 0U };
    i2c_status_t aux;


    /* Update the register   */
    cmd[0]   =   MAX44009_CONFIGURATION;

    /* In automatic mode ( MANUAL = 0 ), reading the contents of TIM<2:0> and CDR bits reflects the automatically generated values from an internal timing register and are read-only  */
    if ( myManualMode == CONFIGURATION_MANUAL_MANUAL_MODE )
    {
        cmd[1]   =   ( myContinuousMode | myManualMode | myCurrentRatio | myIntegrationTime );
    }
    else
    {
        cmd[1]   =   ( myContinuousMode | myManualMode );
    }

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_GetCurrentDivisionRatio ( I2C_parameters_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the current division ratio.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCDR:             Current Division Ratio value
 *
 *
 * @return       Status of MAX44009_GetCurrentDivisionRatio.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_GetCurrentDivisionRatio ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myCDR )
{
    uint8_t      cmd    =   0U;
    i2c_status_t aux;


    /* Read the CONFIGURATION register   */
    cmd  =   MAX44009_CONFIGURATION;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

    /* Parse the data    */
    myCDR->cdr   =   ( cmd & CONFIGURATION_CDR_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_GetIntegrationTime ( I2C_parameters_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the integration time.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTIM:             Integration Time value
 *
 *
 * @return       Status of MAX44009_GetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_GetIntegrationTime ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myTIM )
{
    uint8_t      cmd    =   0U;
    i2c_status_t aux;


    /* Read the CONFIGURATION register   */
    cmd  =   MAX44009_CONFIGURATION;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

    /* Parse the data    */
    myTIM->tim   =   ( cmd & CONFIGURATION_TIM_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_GetLux ( I2C_parameters_t , MAX44009_device_resolution_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the Lux value regarding of the resolution.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myResolution:      Resolution.
 *
 * @param[out]   myLux:             Lux value
 *
 *
 * @return       Status of MAX44009_GetLux.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     17/September/2018   Exponent was fixed it must have been shifted 4 position to the right.
 *                                  Pow function was used.
 *              14/September/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_GetLux ( I2C_parameters_t myI2Cparameters, MAX44009_device_resolution_t myResolution, MAX44009_vector_data_t* myLux )
{
    uint8_t      cmd        =   0U;
    uint8_t      exponent   =   0U;
    uint8_t      mantissa   =   0U;
    float        mulFactor  =   0.0f;
    i2c_status_t aux;


    /* Read the LUX HIGH BYTE register   */
    cmd  =   MAX44009_LUX_HIGH_BYTE;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );


    /* Check the resolution  */
    exponent   =   ( cmd & LUX_HIGH_BYTE_EXPONENT_MASK );
    exponent >>=   4U;
    mantissa   =   ( cmd & LUX_HIGH_BYTE_MANTISSA_MASK );
    if ( myResolution == RESOLUTION_NORMAL_RESOLUTION )
    {
        mulFactor  =   0.72f;
    }
    else
    {
        cmd  =   MAX44009_LUX_LOW_BYTE;
        aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
        aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

        mantissa    <<=  4U;
        mantissa     |=  ( cmd & LUX_LOW_BYTE_MANTISSA_MASK );

        mulFactor     =   0.045f;
    }


    /* Calculate the Lux value   */
    myLux->lux   =   (float)( pow( 2.0, exponent ) * mantissa * mulFactor );




    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_SetUpperThreshold ( I2C_parameters_t , MAX44009_vector_data_t )
 *
 * @details     It sets the upper threshold high-byte.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myUpperThreshold:  Upper threshold Lux value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of MAX44009_SetUpperThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         The Upper Threshold High-Byte register exponent with the four most significant bits of the mantissa sets the upper trip
 *              level for interrupt functionality.
 *
 *              Upper lux threshold = 2^( exponent ) x mantissa x 0.045
 *
 *              exponent: BITS<7:4>, mantissa: BITS<3:0>
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_SetUpperThreshold ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t myUpperThreshold )
{
    uint8_t      cmd[]   =   { 0U, 0U };
    i2c_status_t aux;


    /* Update the register value   */
    cmd[0]  =   MAX44009_UPPER_THRESHOLD_HIGH_BYTE;
    cmd[1]  =   myUpperThreshold.lux_upper_threshold;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_SetLowerThreshold ( I2C_parameters_t , MAX44009_vector_data_t )
 *
 * @details     It sets the lower threshold high-byte.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myLowerThreshold:  Lower threshold Lux value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of MAX44009_SetLowerThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         The Lower Threshold High-Byte register exponent with the four most significant bits of the mantissa sets the lower trip
 *              level for interrupt functionality.
 *
 *              Lower lux threshold = 2^( exponent ) x mantissa x 0.045
 *
 *              exponent: BITS<7:4>, mantissa: BITS<3:0>
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_SetLowerThreshold ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t myLowerThreshold )
{
    uint8_t      cmd[]   =   { 0U, 0U };
    i2c_status_t aux;


    /* Update the register value   */
    cmd[0]  =   MAX44009_LOWER_THRESHOLD_HIGH_BYTE;
    cmd[1]  =   myLowerThreshold.lux_lower_threshold;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_GetUpperThreshold ( I2C_parameters_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the upper threshold high-byte.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myUpperThreshold:  Upper threshold raw data
 *
 *
 * @return       Status of MAX44009_GetUpperThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         The Upper Threshold High-Byte register exponent with the four most significant bits of the mantissa sets the upper trip
 *              level for interrupt functionality.
 *
 *              Upper lux threshold = 2^( exponent ) x mantissa x 0.045
 *
 *              exponent: BITS<7:4>, mantissa: BITS<3:0>
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_GetUpperThreshold ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myUpperThreshold )
{
    uint8_t      cmd   =   0U;
    i2c_status_t aux;


    /* Get the register value  */
    cmd  =   MAX44009_UPPER_THRESHOLD_HIGH_BYTE;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &myUpperThreshold->lux_upper_threshold, 1U );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_GetLowerThreshold ( I2C_parameters_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the lower threshold high-byte.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myLowerThreshold:  Lower threshold raw data
 *
 *
 * @return       Status of MAX44009_GetLowerThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         The Lower Threshold High-Byte register exponent with the four most significant bits of the mantissa sets the lower trip
 *              level for interrupt functionality.
 *
 *              Lower lux threshold = 2^( exponent ) x mantissa x 0.045
 *
 *              exponent: BITS<7:4>, mantissa: BITS<3:0>
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_GetLowerThreshold ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myLowerThreshold )
{
    uint8_t      cmd   =   0U;
    i2c_status_t aux;


    /* Get the register value  */
    cmd  =   MAX44009_LOWER_THRESHOLD_HIGH_BYTE;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &myLowerThreshold->lux_lower_threshold, 1U );



    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_SetThresholdTimer ( I2C_parameters_t , MAX44009_vector_data_t )
 *
 * @details     It sets the threshold timer register.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myThresholdTimer_us:   Time delay in us.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of MAX44009_SetThresholdTimer.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         The value in this register sets the time used to control this delay
 *
 *              Time delay = ( 128xT7 + 64xT6 + 32xT5 + 16xT4 + 8xT3 + 4xT2 + 2xT1 + T0 ) x 100ms
 *
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_SetThresholdTimer ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t myThresholdTimer_us )
{
    uint8_t      cmd[]   =   { 0U, 0U };
    i2c_status_t aux;


    /* Maximum delay is 25.5ms   */
    if ( myThresholdTimer_us.threshold_timer_us > 25500U )
    {
        return   MAX44009_FAILURE;
    }


    /* Update the register value  */
    cmd[0]  =   MAX44009_THRESHOLD_TIMER;
    cmd[1]  =   ( myThresholdTimer_us.threshold_timer_us / 100U );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}



/**
 * @brief       MAX44009_GetThresholdTimer ( I2C_parameters_t , MAX44009_vector_data_t* )
 *
 * @details     It gets the threshold timer register.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myThresholdTimer_us:   Time delay in us.
 *
 *
 * @return       Status of MAX44009_GetThresholdTimer.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018   The ORIGIN
 * @pre         The value in this register gets the time used to control this delay
 *
 *              Time delay = ( 128xT7 + 64xT6 + 32xT5 + 16xT4 + 8xT3 + 4xT2 + 2xT1 + T0 ) x 100ms
 *
 * @warning     N/A.
 */
MAX44009_status_t  MAX44009_GetThresholdTimer ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myThresholdTimer_us )
{
    uint8_t      cmd   =   0U;
    i2c_status_t aux;


    /* Get the register value  */
    cmd  =   MAX44009_THRESHOLD_TIMER;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );


    /* Parse the data    */
    myThresholdTimer_us->threshold_timer_us  =   ( (uint16_t)cmd * 100U );




    if ( aux == I2C_SUCCESS )
    {
        return   MAX44009_SUCCESS;
    }
    else
    {
        return   MAX44009_FAILURE;
    }
}
