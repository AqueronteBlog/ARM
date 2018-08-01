/**
 * @brief       DS1307.c
 * @details     64 x 8, Serial, I2C Real-Time Clock.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/July/2018
 * @version     28/July/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "DS1307.h"


/**
 * @brief       DS1307_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        28/July/2018
 * @version     28/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
DS1307_status_t  DS1307_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   DS1307_SUCCESS;
    else
        return   DS1307_FAILURE;
}



/**
 * @brief       DS1307_SquareWaveOutput ( I2C_parameters_t , DS1307_control_sqwe_t , DS1307_control_rate_select_t )
 *
 * @details     It configures the square-wave output.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySQWE:            Square-wave output enabled/disabled.
 * @param[in]    myRateSelect:      Rate select.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_SquareWaveOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_SquareWaveOutput ( I2C_parameters_t myI2Cparameters, DS1307_control_sqwe_t mySQWE, DS1307_control_rate_select_t myRateSelect )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read CONTROL REGISTER to mask it */
    cmd[0]   =   DS1307_CONTROL;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( CONTROL_SQWE_MASK | CONTROL_RS_MASK );
    cmd[1]  |=   ( mySQWE | myRateSelect );
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_ConfOutput ( I2C_parameters_t , DS1307_control_out_t )
 *
 * @details     It configures the output pin ( OUT ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myOUT:             OUT pin High/Low.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_ConfOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     Square-wave output must be disabled.
 */
DS1307_status_t  DS1307_ConfOutput ( I2C_parameters_t myI2Cparameters, DS1307_control_out_t myOUT )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read CONTROL REGISTER to mask it */
    cmd[0]   =   DS1307_CONTROL;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( CONTROL_OUT_MASK );
    cmd[1]  |=   myOUT;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_SetTime ( I2C_parameters_t , DS1307_vector_data_t )
 *
 * @details     It sets the time ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTime:            Time in BCD mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_SetTime.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: 20:35.59 24h --> 0x203559 24h Enabled.
 *              i.e2: 08:35.59 12h --> 0x083559 12h Enabled ( PM ).
 * @warning     N/A.
 */
DS1307_status_t  DS1307_SetTime ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myTime )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* SECONDS   */
    /* Read SECONDS REGISTER to mask it */
    cmd[0]   =   DS1307_SECONDS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( SECONDS_10SECONDS_MASK | SECONDS_SECONDS_MASK );
    cmd[1]  |=   ( myTime.BCDTime & ( SECONDS_10SECONDS_MASK | SECONDS_SECONDS_MASK ) );
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    /* MINUTES   */
    /* Read MINUTES REGISTER to mask it */
    cmd[0]   =   DS1307_MINUTES;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( MINUTES_10MINUTES_MASK | MINUTES_MINUTES_MASK );
    cmd[1]  |=   ( ( myTime.BCDTime >> 8U ) & ( MINUTES_10MINUTES_MASK | MINUTES_MINUTES_MASK ) );
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    /* HOURS   */
    /* Read HOURS REGISTER to mask it */
    cmd[0]   =   DS1307_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Mask the register   */
    cmd[1]  &=  ~( HOURS_MODE_MASK | HOUR_10HOUR_MASK | HOUR_HOURS_MASK );

    /* Check if it is 12h or 24h mode    */
    if ( myTime.Time12H_24HMode ==  HOURS_MODE_24H )
    {
        cmd[1]  |=   ( ( ( myTime.BCDTime >> 16U ) & ( HOUR_10HOUR_MASK | HOUR_HOURS_MASK ) ) | myTime.Time12H_24HMode );
    }
    else
    {
        cmd[1]  |=   ( ( ( myTime.BCDTime >> 16U ) & ( HOUR_10HOUR_MASK | HOUR_HOURS_MASK ) ) | ( myTime.Time12H_24HMode | myTime.TimeAM_PM_Mode ) );
    }

    /* Update the register   */
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_GetTime ( I2C_parameters_t , DS1307_vector_data_t* )
 *
 * @details     It gets the time ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTime:            Time in BCD mode.
 *
 *
 * @return       Status of DS1307_GetTime.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: 20:35.59 24h --> 0x203559 24h Enabled.
 *              i.e2: 08:35.59 12h --> 0x083559 12h Enabled ( PM ).
 * @warning     N/A.
 */
DS1307_status_t  DS1307_GetTime ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTime )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* HOURS   */
    /* Read HOURS REGISTER  */
    cmd[0]   =   DS1307_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Parse the data    */
    myTime->BCDTime   =   ( cmd[1] & ( HOUR_10HOUR_MASK | HOUR_HOURS_MASK ) );


    /* Check if it is 12h or 24h mode    */
    if ( ( cmd[1] & HOURS_MODE_MASK ) ==  HOURS_MODE_24H )
    {
        /* 24h mode  */
        myTime->Time12H_24HMode  =   HOURS_MODE_24H;

        /* Update the PM/AM mode variable    */
        if ( ( cmd[1] & ( HOUR_10HOUR_MASK | HOUR_HOURS_MASK ) ) >=  0x12 )
        {
            myTime->TimeAM_PM_Mode   =   HOURS_MODE_PM;
        }
        else
        {
            myTime->TimeAM_PM_Mode   =   HOURS_MODE_AM;
        }
    }
    else
    {
        /* 12h mode  */
        myTime->Time12H_24HMode  =   HOURS_MODE_12H;
        myTime->TimeAM_PM_Mode   =   ( cmd[1] & HOURS_MODE_AM_PM_MASK );
        myTime->BCDTime         &=  ~( HOURS_MODE_AM_PM_MASK );
    }

    myTime->BCDTime <<=   8U;



    /* MINUTES   */
    /* Read MINUTES REGISTER to mask it */
    cmd[0]   =   DS1307_MINUTES;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Parse the data    */
    cmd[1]  &=   ( MINUTES_10MINUTES_MASK | MINUTES_MINUTES_MASK );
    myTime->BCDTime  |=   cmd[1];
    myTime->BCDTime <<=   8U;



    /* SECONDS   */
    /* Read SECONDS REGISTER to mask it */
    cmd[0]   =   DS1307_SECONDS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Parse the data   */
    cmd[1]  &=   ( SECONDS_10SECONDS_MASK | SECONDS_SECONDS_MASK );
    myTime->BCDTime |=   cmd[1];





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_SetDayOfTheWeek ( I2C_parameters_t , DS1307_vector_data_t )
 *
 * @details     It sets the day of the week.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myDayOfTheWeek:    Day of the week.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_SetDayOfTheWeek.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_SetDayOfTheWeek ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myDayOfTheWeek )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read DAY REGISTER to mask it */
    cmd[0]   =   DS1307_DAY;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( DAY_MASK );
    cmd[1]  |=   myDayOfTheWeek.DayOfTheWeek;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_GetDayOfTheWeek ( I2C_parameters_t , DS1307_vector_data_t )
 *
 * @details     It gets the day of the week.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDayOfTheWeek:    Day of the week.
 *
 *
 * @return       Status of DS1307_GetDayOfTheWeek.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_GetDayOfTheWeek ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myDayOfTheWeek )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read DAY REGISTER to mask it */
    cmd[0]   =   DS1307_DAY;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Parse the data   */
    myDayOfTheWeek->DayOfTheWeek     =   (DS1307_day_t)( cmd[1] & DAY_MASK );





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_SetDate ( I2C_parameters_t , DS1307_vector_data_t )
 *
 * @details     It sets the date ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myDate:            Date.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_SetDate.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: 01:  0x01.
 *              i.e2: 12:  0x12.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_SetDate ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myDate )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Check date limits     */
    if ( ( myDate.BCDDate >= 0x01 ) && ( myDate.BCDDate <= 0x31 ) )
    {
        /* Read DATE REGISTER to mask it */
        cmd[0]   =   DS1307_DATE;
        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
        aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


        /* Update the register   */
        cmd[1]  &=  ~( DATE_10DATE_MASK | DATE_DATE_MASK );
        cmd[1]  |=   myDate.BCDDate;
        aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
    }
    else
    {
        return DS1307_FAILURE;
    }




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_GetDate ( I2C_parameters_t , DS1307_vector_data_t* )
 *
 * @details     It gets the date ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDate:            Date.
 *
 *
 * @return       Status of DS1307_GetDate.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: 01:  0x01.
 *              i.e2: 12:  0x12.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_GetDate ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myDate )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read DATE REGISTER to mask it */
    cmd[0]   =   DS1307_DATE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Parse the data   */
    myDate->BCDDate   =  ( cmd[1] & ( DATE_10DATE_MASK | DATE_DATE_MASK ) );




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_SetMonth ( I2C_parameters_t , DS1307_vector_data_t )
 *
 * @details     It sets the month ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMonth:           Month.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_SetMonth.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: January:  0x01.
 *              i.e2: December: 0x12.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_SetMonth ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myMonth )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read MONTH REGISTER to mask it */
    cmd[0]   =   DS1307_MONTH;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( MONTH_10MONTH_MASK | MONTH_MONTH_MASK );
    cmd[1]  |=   myMonth.BCDMonth;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_GetMonth ( I2C_parameters_t , DS1307_vector_data_t* )
 *
 * @details     It gets the month ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myMonth:           Month.
 *
 *
 * @return       Status of DS1307_GetMonth.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: January:  0x01.
 *              i.e2: December: 0x12.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_GetMonth ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myMonth )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read MONTH REGISTER to mask it */
    cmd[0]   =   DS1307_MONTH;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Parse the data   */
    myMonth->BCDMonth   =   (DS1307_month_t)( cmd[1] & ( MONTH_10MONTH_MASK | MONTH_MONTH_MASK ) );




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_SetYear ( I2C_parameters_t , DS1307_vector_data_t )
 *
 * @details     It sets the year ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myYear:            Year.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_SetYear.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: 2000:  0x00.
 *              i.e2: 2018:  0x18.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_SetYear ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myYear )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Update the register   */
    cmd[0]   =   DS1307_YEAR;
    cmd[1]   =   myYear.BCDYear;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_GetYear ( I2C_parameters_t , DS1307_vector_data_t* )
 *
 * @details     It gets the year ( BCD mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myYear:            Year.
 *
 *
 * @return       Status of DS1307_GetYear.
 *
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
 * @pre         i.e1: 2000:  0x00.
 *              i.e2: 2018:  0x18.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_GetYear ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myYear )
{
    uint8_t      cmd    =    0;

    i2c_status_t aux;


    /* Read YEAR REGISTER to mask it */
    cmd      =   DS1307_YEAR;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &myYear->BCDYear, 1U );





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_OscillatorMode ( I2C_parameters_t , DS1307_seconds_ch_t )
 *
 * @details     It enables/disabled the oscillator.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myOscillator:      Oscillator enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_OscillatorMode.
 *
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         The clock can be halted whenever the timekeeping functions are not required,
 *              which minimizes current ( I_BATDR ).
 * @warning     N/A.
 */
DS1307_status_t  DS1307_OscillatorMode ( I2C_parameters_t myI2Cparameters, DS1307_seconds_ch_t myOscillator )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;


    /* Read SECONDS REGISTER to mask it */
    cmd[0]   =   DS1307_SECONDS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    /* Update the register   */
    cmd[1]  &=  ~( SECONDS_CH_MASK );
    cmd[1]  |=   myOscillator;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_WriteByteRAM ( I2C_parameters_t , uint8_t , uint8_t )
 *
 * @details     It writes a byte into the RAM memory.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myByte:            Byte to be written.
 * @param[in]    myAddress:         Address to write the byte.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of DS1307_WriteByteRAM.
 *
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_WriteByteRAM ( I2C_parameters_t myI2Cparameters, uint8_t myByte, uint8_t myAddress )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;

    
    /* Check RAM memory limits   */
    if ( ( myAddress >= 0x08 ) && ( myAddress <= 0x3F ) )
    {
      /* Write data into the RAM memory   */
      cmd[0]   =   myAddress;
      cmd[1]   =   myByte;
      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
    }
    else
    {
        return DS1307_FAILURE;
    }

    


    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_ReadByteRAM ( I2C_parameters_t , uint8_t* , uint8_t )
 *
 * @details     It reads a byte from the RAM memory.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAddress:         Address to write the byte.
 *
 * @param[out]   myByte:            Byte to be read.
 *
 *
 * @return       Status of DS1307_ReadByteRAM.
 *
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_ReadByteRAM ( I2C_parameters_t myI2Cparameters, uint8_t* myByte, uint8_t myAddress )
{
    uint8_t      cmd    =    0;

    i2c_status_t aux;

    
    /* Check RAM memory limits   */
    if ( ( myAddress >= 0x08 ) && ( myAddress <= 0x3F ) )
    {
      /* Read data from the RAM memory   */
      cmd   =   myAddress;
      aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
      aux   =   i2c_read  ( myI2Cparameters, myByte, 1U );
    }
    else
    {
        return DS1307_FAILURE;
    }





    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}



/**
 * @brief       DS1307_EraseByteRAM ( I2C_parameters_t , uint8_t )
 *
 * @details     It ereases a byte into the RAM memory.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAddress:         Address to write the byte.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of DS1307_EraseByteRAM.
 *
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
DS1307_status_t  DS1307_EraseByteRAM ( I2C_parameters_t myI2Cparameters, uint8_t myAddress )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;

    
    /* Check RAM memory limits   */
    if ( ( myAddress >= 0x08 ) && ( myAddress <= 0x3F ) )
    {
      /* Write data into the RAM memory   */
      cmd[0]   =   myAddress;
      cmd[1]   =   0xFF;
      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
    }
    else
    {
        return DS1307_FAILURE;
    }


    if ( aux == I2C_SUCCESS )
    {
        return   DS1307_SUCCESS;
    }
    else
    {
        return   DS1307_FAILURE;
    }
}