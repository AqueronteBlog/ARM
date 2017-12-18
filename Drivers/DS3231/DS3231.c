/**
 * @brief       DS3231.h
 * @details     Extremely Accurate I2C-Integrated RTC/TCXO/Crystal.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "DS3231.h"


/**
 * @brief       DS3231_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ReadTemperature ( I2C_parameters_t , DS3231_vector_data_t* )
 *
 * @details     It gets the temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Temperature data.
 *
 *
 * @return       Status of DS3231_ReadTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        11/December/2017
 * @version     11/December/2017     The ORIGIN
 * @pre         The temperature registers are updated after each user-initiated conversion and on every 64-second conversion.
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ReadTemperature   ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t*  myTemperature )
{
    uint8_t      cmd[]       =   { DS3231_MSB_TEMPERATURE, 0 };
    uint32_t     aux         =   0;


    // It gets the temperature
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse the data
    // 1. Check if the Temperature is positive or negative
    if ( ( cmd[0] & 0b10000000 ) == 0b00000000 )
        myTemperature->Temperature   =   cmd[0];                           // Positive value
    else
        myTemperature->Temperature   =   -1.0 * ( ( ~cmd[0] ) + 1 );       // Negative value


    // 2. Decimal part. 0.25°C resolution
    switch( cmd[1] )
    {
        // x.00°C
    default:
    case 0b00000000:
        break;

        // x.25°C
    case 0b01000000:
        myTemperature->Temperature  +=    0.25;
        break;

        // x.50°C
    case 0b10000000:
        myTemperature->Temperature  +=    0.50;
        break;

        // x.75°C
    case 0b11000000:
        myTemperature->Temperature  +=    0.75;
        break;
    }




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ReadRawTemperature ( I2C_parameters_t , DS3231_vector_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw Temperature data.
 *
 *
 * @return       Status of DS3231_ReadTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        11/December/2017
 * @version     11/December/2017     The ORIGIN
 * @pre         The temperature registers are updated after each user-initiated conversion and on every 64-second conversion.
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ReadRawTemperature   ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t*  myRawTemperature )
{
    uint8_t      cmd[]       =   { DS3231_MSB_TEMPERATURE, 0 };
    uint32_t     aux         =   0;


    // It gets the temperature
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse the data
    myRawTemperature->MSBTemperature    =   cmd[0];
    myRawTemperature->LSBTemperature    =   cmd[1];




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_StartNewConvertTemperature  ( I2C_parameters_t )
 *
 * @details     It triggers a new temperature conversion.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_StartNewConvertTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        18/December/2017
 * @version     18/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_StartNewConvertTemperature  ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]  =   { DS3231_CONTROL_STATUS, 0 };
    uint32_t     aux    =   0;
    uint32_t     ii     =   0;


    // BSY MUST be checked before triggering a new temperature conversion
    do
    {
        aux  =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
        aux  =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

        ii++;
    }
    while ( ( ( cmd[1] & STATUS_BUSY_MASK ) != STATUS_BUSY_NOBUSY ) && ( ii < DS3231_TIMEOUT ) );


    // if something went wrong, there will not be a new temperature conversion
    cmd[0]  =   DS3231_CONTROL;
    if ( ii < DS3231_TIMEOUT )
    {
        // It triggers a new temperature conversion
        // It reads CONTROL register
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
        aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

        // Start a new temperature conversion
        cmd[1] |=   CONTROL_STATUS_CONVERT_TEMPERATURE_ENABLED;
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

        // Wait until the temperature conversion is completed
        ii   =   0;
        do
        {
            aux  =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
            aux  =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

            ii++;
        }
        while ( ( ( cmd[1] & CONTROL_STATUS_CONVERT_TEMPERATURE_MASK ) != CONTROL_STATUS_CONVERT_TEMPERATURE_DISABLED ) && ( ii < DS3231_TIMEOUT ) );
    }

    // If TIMEOUT happens, something went wrong!
    if ( ii >= DS3231_TIMEOUT )
        aux   =   I2C_FAILURE;




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ReadRawAging ( I2C_parameters_t , DS3231_vector_data_t* )
 *
 * @details     It gets the raw aging.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawAging:        Raw Aging data.
 *
 *
 * @return       Status of DS3231_ReadRawAging.
 *
 *
 * @author      Manuel Caballero
 * @date        12/December/2017
 * @version     12/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ReadRawAging ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t* myRawAging )
{
    uint8_t      cmd       =   DS3231_AGING_OFFSET;
    uint32_t     aux       =   0;


    // It gets the raw aging value
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &myRawAging->RawAging, 1 );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_Status32kHzPin ( I2C_parameters_t , DS3231_status_enable_32khz_output_t )
 *
 * @details     It enables/disables the 32kHz output pin.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    my32kHzPin:        32kHz pin enabled/disabled.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_Status32kHzPin.
 *
 *
 * @author      Manuel Caballero
 * @date        18/December/2017
 * @version     18/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_Status32kHzPin  ( I2C_parameters_t myI2Cparameters, DS3231_status_enable_32khz_output_t  my32kHzPin )
{
    uint8_t      cmd[]     =   { DS3231_CONTROL_STATUS, 0 };
    uint32_t     aux       =   0;


    // It reads the status register to parse the data
    aux  =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] &=  ~STATUS_ENABLE_32KHZ_OUTPUT_MASK;
    cmd[1] |=   my32kHzPin;

    // Update the register
    aux  =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_ClearAlarmFlag ( I2C_parameters_t , DS3231_status_alarm1_flag_t , DS3231_status_alarm2_flag_t )
 *
 * @details     It clears alarm flags.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myA1F:             Reset/Mask alarm 1 flag.
 * @param[in]    myA2F:             Reset/Mask alarm 2 flag.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_ClearAlarmFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        18/December/2017
 * @version     18/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_ClearAlarmFlag  ( I2C_parameters_t myI2Cparameters, DS3231_status_alarm1_flag_t myA1F, DS3231_status_alarm2_flag_t myA2F )
{
    uint8_t      cmd[]     =   { DS3231_CONTROL_STATUS, 0 };
    uint32_t     aux       =   0;


    // It reads the status register to parse the data
    aux  =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] &=  ~( STATUS_ALARM1_FLAG_MASK | STATUS_ALARM2_FLAG_MASK );
    cmd[1] |=   ( myA1F | myA2F );

    // Update the register
    aux  =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_SetAlarm1 ( I2C_parameters_t , DS3231_alarm1_register_t )
 *
 * @details     It sets the alarm 1.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAlarm1:          Alarm 1 options.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_SetAlarm1.
 *
 *
 * @author      Manuel Caballero
 * @date        18/December/2017
 * @version     18/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_SetAlarm1   ( I2C_parameters_t myI2Cparameters, DS3231_alarm1_register_t myAlarm1 )
{
    uint8_t      cmd[]     =   { 0, 0, 0, 0, 0, 0 };        // REGISTER | A1M1 | A1M2 | A1M3 | A1M4 | DYDT
    uint32_t     aux       =   0;


    // Read all the registers involved in the alarm1
    // A1M1
    cmd[0]   =   DS3231_ALARM_1_SECONDS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );
    cmd[1]  &=  ~ALARM1_A1M1_MASK;

    // A1M2
    cmd[0]   =   DS3231_ALARM_1_MINUTES;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[2], 1 );
    cmd[2]  &=  ~ALARM1_A1M2_MASK;

    // A1M3
    cmd[0]   =   DS3231_ALARM_1_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[3], 1 );
    cmd[3]  &=  ~ALARM1_A1M3_MASK;

    // A1M4 & DY/#DT
    cmd[0]   =   DS3231_ALARM_1_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[4], 1 );
    cmd[5]   =   ( cmd[4] & ~ALARM1_DYDT_MASK );
    cmd[4]  &=  ~ALARM1_A1M4_MASK;





    switch ( myAlarm1 )
    {
    case ALARM1_ALARM_ONCE_PER_SECOND:


    case ALARM1_WHEN_SECONDS_MATCH:

    case ALARM1_WHEN_MINUTES_AND_SECONDS_MATCH:

    case ALARM1_WHEN_HOURS_MINUTES_AND_SECONDS_MATCH:

    case ALARM1_WHEN_DATE_HOURS_MINUTES_AND_SECONDS_MATCH:

    case ALARM1_WHEN_DAY_HOURS_MINUTES_AND_SECONDS_MATCH:
        break;
    }


    // It reads the status register to parse the data
    aux  =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );






    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}
