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
    uint8_t      cmd[]              =   { 0, 0 };
    uint32_t     aux                =   0;
    uint32_t     Alarm1SecondAux    =   0;              // A1M1
    uint32_t     Alarm1MinuteAux    =   0;              // A1M2
    uint32_t     Alarm1HourAux      =   0;              // A1M3
    uint32_t     Alarm1DayDateAux   =   0;              // A1M4 & DYDT


    // Read all the registers involved in the alarm1
    // A1M1
    cmd[0]   =   DS3231_ALARM_1_SECONDS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm1SecondAux  =  ( cmd[1] & ~ALARM1_A1M1_MASK );

    // A1M2
    cmd[0]   =   DS3231_ALARM_1_MINUTES;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm1MinuteAux  =  ( cmd[1] & ~ALARM1_A1M2_MASK );

    // A1M3
    cmd[0]   =   DS3231_ALARM_1_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm1HourAux  =  ( cmd[1] & ~ALARM1_A1M3_MASK );

    // A1M4 & DY/#DT
    cmd[0]   =   DS3231_ALARM_1_DAY_DATE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm1DayDateAux  =  ( cmd[1] & ~( ALARM1_A1M4_MASK | ALARM1_DYDT_MASK ) );


    // Set all ( A1M1, A1M2, A1M3 A1M4 and DY/#DT ) to 0
    cmd[0]   =   DS3231_ALARM_1_SECONDS;
    cmd[1]   =   Alarm1SecondAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    cmd[0]   =   DS3231_ALARM_1_MINUTES;
    cmd[1]   =   Alarm1MinuteAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    cmd[0]   =   DS3231_ALARM_1_HOURS;
    cmd[1]   =   Alarm1HourAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    cmd[0]   =   DS3231_ALARM_1_DAY_DATE;
    cmd[1]   =   Alarm1DayDateAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );


    // Update the Alarm 1 rate
    switch ( myAlarm1 )
    {
    case ALARM1_ALARM_ONCE_PER_SECOND:
        cmd[0]   =   DS3231_ALARM_1_SECONDS;
        cmd[1]   =   ( Alarm1SecondAux | ALARM1_A1M1_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    case ALARM1_WHEN_SECONDS_MATCH:
        cmd[0]   =   DS3231_ALARM_1_MINUTES;
        cmd[1]   =   ( Alarm1MinuteAux | ALARM1_A1M2_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    case ALARM1_WHEN_MINUTES_AND_SECONDS_MATCH:
        cmd[0]   =   DS3231_ALARM_1_HOURS;
        cmd[1]   =   ( Alarm1HourAux | ALARM1_A1M3_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    case ALARM1_WHEN_HOURS_MINUTES_AND_SECONDS_MATCH:
        cmd[0]   =   DS3231_ALARM_1_DAY_DATE;
        cmd[1]   =   ( Alarm1DayDateAux | ALARM1_A1M4_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );
        break;

    default:
    case ALARM1_WHEN_DATE_HOURS_MINUTES_AND_SECONDS_MATCH:
        break;

    case ALARM1_WHEN_DAY_HOURS_MINUTES_AND_SECONDS_MATCH:
        cmd[0]   =   DS3231_ALARM_1_DAY_DATE;
        cmd[1]   =   ( Alarm1DayDateAux | ALARM1_DYDT_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );
        break;
    }





    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}


/**
 * @brief       DS3231_SetAlarm2 ( I2C_parameters_t , DS3231_alarm2_register_t )
 *
 * @details     It sets the alarm 2.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAlarm1:          Alarm 2 options.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_SetAlarm2.
 *
 *
 * @author      Manuel Caballero
 * @date        19/December/2017
 * @version     19/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_SetAlarm2   ( I2C_parameters_t myI2Cparameters, DS3231_alarm2_register_t myAlarm2 )
{
    uint8_t      cmd[]              =   { 0, 0 };
    uint32_t     aux                =   0;
    uint32_t     Alarm2MinuteAux    =   0;              // A2M2
    uint32_t     Alarm2HourAux      =   0;              // A2M3
    uint32_t     Alarm2DayDateAux   =   0;              // A2M3 & DYDT


    // Read all the registers involved in the alarm2
    // A2M2
    cmd[0]   =   DS3231_ALARM_2_MINUTES;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm2MinuteAux  =  ( cmd[1] & ~ALARM2_A2M2_MASK );

    // A2M3
    cmd[0]   =   DS3231_ALARM_2_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm2HourAux  =  ( cmd[1] & ~ALARM2_A2M3_MASK );

    // A2M4 & DY/#DT
    cmd[0]   =   DS3231_ALARM_2_DAY_DATE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    Alarm2DayDateAux  =  ( cmd[1] & ~( ALARM2_A2M4_MASK | ALARM2_DYDT_MASK ) );


    // Set all ( A2M2, A2M3 A2M4 and DY/#DT ) to 0
    cmd[0]   =   DS3231_ALARM_2_MINUTES;
    cmd[1]   =   Alarm2MinuteAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    cmd[0]   =   DS3231_ALARM_2_HOURS;
    cmd[1]   =   Alarm2HourAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    cmd[0]   =   DS3231_ALARM_2_DAY_DATE;
    cmd[1]   =   Alarm2DayDateAux;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );


    // Update the Alarm 2 rate
    switch ( myAlarm2 )
    {
    case ALARM2_ALARM_ONCE_PER_MINUTE:
        cmd[0]   =   DS3231_ALARM_2_MINUTES;
        cmd[1]   =   ( Alarm2MinuteAux | ALARM2_A2M2_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    case ALARM2_WHEN_MINUTES_MATCH:
        cmd[0]   =   DS3231_ALARM_2_HOURS;
        cmd[1]   =   ( Alarm2HourAux | ALARM2_A2M3_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    case ALARM2_WHEN_HOURS_MINUTES_MATCH:
        cmd[0]   =   DS3231_ALARM_2_DAY_DATE;
        cmd[1]   =   ( Alarm2DayDateAux | ALARM2_A2M4_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );
        break;

    default:
    case ALARM2_WHEN_DATE_HOURS_AND_MINUTES_MATCH:
        break;

    case ALARM2_WHEN_DAY_HOURS_AND_MINUTES_MATCH:
        cmd[0]   =   DS3231_ALARM_2_DAY_DATE;
        cmd[1]   =   ( Alarm2DayDateAux | ALARM2_DYDT_MASK );

        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );
        break;
    }





    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}


/**
 * @brief       DS3231_SetAlarmsInterrupt ( I2C_parameters_t , DS3231_control_status_alarm1_t , DS3231_control_status_alarm2_t )
 *
 * @details     It enables/disable alarm interrupts.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAlarm1:          Enable/Disable Alarm1 interrupt.
 * @param[in]    myAlarm2:          Enable/Disable Alarm2 interrupt.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_SetAlarmsInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        19/December/2017
 * @version     19/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_SetAlarmsInterrupt   ( I2C_parameters_t myI2Cparameters, DS3231_control_status_alarm1_t myAlarm1, DS3231_control_status_alarm2_t myAlarm2 )
{
    uint8_t      cmd[]              =   { DS3231_CONTROL, 0 };
    uint32_t     aux                =   0;


    // Read the Control Register
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    // Parse the data
    cmd[1]  &=  ~( CONTROL_STATUS_ALARM1_MASK | CONTROL_STATUS_ALARM2_MASK );
    cmd[1]  |=   ( myAlarm1 | myAlarm2 );


    // If both alarms are off then, disables the alarm interrupts, enables them otherwise.
    if ( ( myAlarm1 == CONTROL_STATUS_ALARM1_DISABLED ) && ( myAlarm2 == CONTROL_STATUS_ALARM2_DISABLED ) )
        cmd[1]  &=  ~CONTROL_STATUS_INTERRUPT_CONTROL_MASK;
    else
        cmd[1]  |=   CONTROL_STATUS_INTERRUPT_CONTROL_INT;


    // Update the register
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}


/**
 * @brief       DS3231_SetSquareWaveOutput ( I2C_parameters_t , DS3231_control_status_rate_select_t )
 *
 * @details     It enables/disable the square-wave output.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRate:            Square-wave output frequency.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_SetSquareWaveOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        19/December/2017
 * @version     19/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_SetSquareWaveOutput ( I2C_parameters_t myI2Cparameters, DS3231_control_status_rate_select_t myRate )
{
    uint8_t      cmd[]              =   { DS3231_CONTROL, 0 };
    uint32_t     aux                =   0;


    // Read the Control Register
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    // Parse the data
    cmd[1]  &=  ~CONTROL_STATUS_RATE_SELECT_MASK;
    cmd[1]  |=   myRate;


    // Enable the square-wave output.
    cmd[1]  &=  ~CONTROL_STATUS_INTERRUPT_CONTROL_MASK;


    // Update the register
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}


/**
 * @brief       DS3231_GetDate ( I2C_parameters_t , DS3231_vector_date_time_t* )
 *
 * @details     It gets the date.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myDate:            Current Date.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_GetDate.
 *
 *
 * @author      Manuel Caballero
 * @date        19/December/2017
 * @version     19/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_GetDate ( I2C_parameters_t myI2Cparameters, DS3231_vector_date_time_t* myDate )
{
    uint8_t      cmd     =   0;
    uint32_t     aux     =   0;


    // Read Date Register
    cmd  =   DS3231_DATE;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myDate->Date         =   _MYBCD_TO_DECIMAL( cmd );

    // Read Month Register
    cmd  =   DS3231_MONTH_CENTURY;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myDate->Month        =   _MYBCD_TO_DECIMAL( cmd & MONTH_MONTH_MASK );
    myDate->Century      =   _MYBCD_TO_DECIMAL( cmd & MONTH_CENTURY_MASK );

    // Read Year Register
    cmd  =   DS3231_YEAR;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myDate->Year         =   _MYBCD_TO_DECIMAL( cmd );

    // Read Day of the Week Register
    cmd  =   DS3231_DAY;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myDate->DayOfWeek    =   _MYBCD_TO_DECIMAL( cmd );




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}


/**
 * @brief       DS3231_SetDate ( I2C_parameters_t , DS3231_vector_date_time_t )
 *
 * @details     It sets the date.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTime:            Date to store.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_SetDate.
 *
 *
 * @author      Manuel Caballero
 * @date        20/December/2017
 * @version     20/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_SetDate ( I2C_parameters_t myI2Cparameters, DS3231_vector_date_time_t myDate )
{
    uint8_t      cmd[]   =   { 0, 0 };
    uint32_t     aux     =   0;


    // Update Date Register
    cmd[0]  =   DS3231_DATE;
    cmd[1]  =   _MYDECIMAL_TO_BCD( myDate.Date );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    // Update Month Register
    cmd[0]  =   DS3231_MONTH_CENTURY;
    cmd[1]  =   _MYDECIMAL_TO_BCD( myDate.Month | myDate.Century );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    // Update Year Register
    cmd[0]  =   DS3231_YEAR;
    cmd[1]  =   _MYDECIMAL_TO_BCD( myDate.Year );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    // Update Day Register
    cmd[0]  =   DS3231_DAY;
    cmd[1]  =   _MYDECIMAL_TO_BCD( myDate.DayOfWeek );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}


/**
 * @brief       DS3231_GetTime ( I2C_parameters_t , DS3231_vector_date_time_t* )
 *
 * @details     It gets the time in decimal.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTime:            Current Time.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_GetTime.
 *
 *
 * @author      Manuel Caballero
 * @date        19/December/2017
 * @version     19/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_GetTime ( I2C_parameters_t myI2Cparameters, DS3231_vector_date_time_t* myTime )
{
    uint8_t      cmd     =   0;
    uint32_t     aux     =   0;


    // Read Hours Register
    cmd  =   DS3231_HOURS;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myTime->Hours        =   _MYBCD_TO_DECIMAL( ( cmd & ~( HOURS_nAM_PM_MASK | HOURS_12_n24_MASK ) ) );
    myTime->Mode_nAM_PM  =   ( cmd & HOURS_nAM_PM_MASK );
    myTime->Mode_12_n24  =   ( cmd & HOURS_12_n24_MASK );

    // Read Minutes Register
    cmd  =   DS3231_MINUTES;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myTime->Minutes  =   _MYBCD_TO_DECIMAL( cmd );

    // Read Seconds Register
    cmd  =   DS3231_SECONDS;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1 );

    myTime->Seconds  =   _MYBCD_TO_DECIMAL( cmd );




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}

/**
 * @brief       DS3231_SetTime ( I2C_parameters_t , DS3231_vector_date_time_t )
 *
 * @details     It sets the time in BCD.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTime:            Time to store.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_SetTime.
 *
 *
 * @author      Manuel Caballero
 * @date        19/December/2017
 * @version     19/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_SetTime ( I2C_parameters_t myI2Cparameters, DS3231_vector_date_time_t myTime )
{
    uint8_t      cmd[]   =   { 0, 0 };
    uint32_t     aux     =   0;


    // Update Hours Register
    cmd[0]  =   DS3231_HOURS;
    cmd[1]  =   ( _MYDECIMAL_TO_BCD( myTime.Hours ) | myTime.Mode_12_n24 | myTime.Mode_nAM_PM );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    // Update Minutes Register
    cmd[0]  =   DS3231_MINUTES;
    cmd[1]  =   _MYDECIMAL_TO_BCD( myTime.Minutes );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );

    // Update Seconds Register
    cmd[0]  =   DS3231_SECONDS;
    cmd[1]  =   _MYDECIMAL_TO_BCD( myTime.Seconds );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}



/**
 * @brief       DS3231_GetControlStatusRegister ( I2C_parameters_t , DS3231_vector_data_t* )
 *
 * @details     It gets the Control/Status register.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myControlStatusReg:    Current value of the Register.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of DS3231_GetControlStatusRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        20/December/2017
 * @version     20/December/2017     The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
DS3231_status_t  DS3231_GetControlStatusRegister ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t* myControlStatusReg )
{
    uint8_t      cmd     =   DS3231_CONTROL_STATUS;
    uint32_t     aux     =   0;


    // Read Control/Status Register
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &myControlStatusReg->Control_Status_Register, 1 );




    if ( aux == I2C_SUCCESS )
        return   DS3231_SUCCESS;
    else
        return   DS3231_FAILURE;
}
