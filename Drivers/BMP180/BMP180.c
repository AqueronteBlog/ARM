/**
 * @brief       BMP180.c
 * @details     Digital Pressure Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

 #include "BMP180.h"


 /**
 * @brief       BMP180_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMP180_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BMP180_status_t  BMP180_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



/**
 * @brief       BMP180_Conf    ( I2C_parameters_t , BMP180_measurement_resolution_t , BMP180_on_chip_heater_t )
 * @details     It configures the BMP180 device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myResolution:      BMP180 Resolution.
 * @param[in]    myHeater:          BMP180 Heater EN/Abled or Disabled.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of BMP180_Init.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BMP180_status_t  BMP180_Conf    ( I2C_parameters_t myI2Cparameters, BMP180_measurement_resolution_t myResolution, BMP180_on_chip_heater_t myHeater )
{
    uint8_t      cmd[]   =    { BMP180_READ_USER_REGISTER, 0 };
    i2c_status_t aux;


    /*
        Reserved bits must not be changed. Therefore, for any writing to user register, default values of reserved bits must be read first
        Datasheet: 5.6. User register p.19/14.
    */
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[1], 1U );

    cmd[1]  &=  ~( USER_REGISTER_RESOLUTION_MASK | USER_REGISTER_STATUS_END_BATTERY_MASK | USER_REGISTER_HEATER_MASK | USER_REGISTER_OTP_MASK );
    cmd[1]  |=   ( myResolution | myHeater | USER_REGISTER_OTP_DISABLED );
    cmd[0]   =   BMP180_WRITE_USER_REGISTER;

    aux = i2c_write  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



 /**
 * @brief       BMP180_SoftReset   ( I2C_parameters_t )
 * @details     Rebooting the BMP180 sensor switching the power off and on again.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of BMP180_SoftReset.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         N/A
 * @warning     The soft reset takes less than 15ms. The user MUST take this into account.
 */
BMP180_status_t  BMP180_SoftReset   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd   =   BMP180_SOFT_RESET;
    i2c_status_t aux;


    aux = i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );


    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}


 /**
 * @brief       BMP180_TriggerTemperature   ( I2C_parameters_t , BMP180_master_mode_t )
 * @details     It triggers a new temperature measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMode:            Hold/No Hold mode.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of BMP180_TriggerTemperature.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         N/A
 * @warning     The user MUST respect the total conversion time.
 *              14-bit temperature: 66ms ( 85ms max )
 *              13-bit temperature: 33ms ( 43ms max )
 *              12-bit temperature: 17ms ( 22ms max )
 *              11-bit temperature:  9ms (  11ms max )
 */
BMP180_status_t  BMP180_TriggerTemperature    ( I2C_parameters_t myI2Cparameters, BMP180_master_mode_t myMode )
{
    uint8_t      cmd        =    0;
    uint8_t      myI2C_stop =    I2C_STOP_BIT;

    i2c_status_t aux;


    /* Check the mode if it is HOLD MASTER MODE, if so, not to generate a stop bit    */
    if ( myMode == BMP180_HOLD_MASTER_MODE )
    {
        cmd         =    BMP180_TRIGGER_TEMPERATURE_MEASUREMENT_HOLD_MASTER;
        myI2C_stop  =    I2C_NO_STOP_BIT;
    }
    else
    {
        cmd         =    BMP180_TRIGGER_TEMPERATURE_MEASUREMENT_NO_HOLD_MASTER;
        myI2C_stop  =    I2C_STOP_BIT;
    }


    aux = i2c_write ( myI2Cparameters, &cmd, 1U, myI2C_stop );


    /* NOTE: The user has to respect the total conversion time!  */




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}


 /**
 * @brief       BMP180_ReadTemperature   ( I2C_parameters_t , BMP180_vector_data_t* )
 * @details     It reads a new temperature measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Variable to store the temperature.
 *
 *
 * @return      Status of BMP180_ReadTemperature.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         CRC is NOT taken into account.
 * @warning     The measuring time depends on the chosen resolution. The user MUST take this into account.
 * @warning     BMP180_TriggerTemperature MUST be call before.
 */
BMP180_status_t  BMP180_ReadTemperature    ( I2C_parameters_t myI2Cparameters, BMP180_vector_data_t* myTemperature )
{
    uint8_t      cmd[]     =   { 0, 0, 0 };
    i2c_status_t aux;


    /* Read the temperature  */
    aux = i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myTemperature->Temperature     =   ( ( cmd[0] << 8U ) | cmd[1] );
    myTemperature->Temperature    /=   65536.0f;
    myTemperature->Temperature    *=   175.72f;
    myTemperature->Temperature    -=   46.85f;



    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



/**
 * @brief       BMP180_ReadRawTemperature   ( I2C_parameters_t , BMP180_vector_data_t* )
 * @details     It reads a new raw temperature measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Variable to store the temperature.
 *
 *
 * @return      Status of BMP180_ReadTemperature.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018       The ORIGIN
 * @pre         CRC is NOT taken into account.
 * @warning     The measuring time depends on the chosen resolution. The user MUST take this into account.
 * @warning     No Hold Master is ONLY implemented.
 * @warning     BMP180_TriggerTemperature MUST be call before.
 */
BMP180_status_t  BMP180_ReadRawTemperature    ( I2C_parameters_t myI2Cparameters, BMP180_vector_data_t* myRawTemperature )
{
    uint8_t      cmd[]         =   { 0, 0, 0 };
    i2c_status_t aux;


    /* Read the temperature  */
    aux = i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myRawTemperature->RawTemperature    =   ( ( cmd[0] << 8U ) | cmd[1] );




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}


 /**
 * @brief       BMP180_TriggerHumidity   ( I2C_parameters_t , BMP180_master_mode_t )
 * @details     It triggers a new humidity measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMode:            Hold/No Hold mode.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of BMP180_TriggerHumidity.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         N/A
 * @warning     The user MUST respect the total conversion time.
 *              12-bit RH: 22ms   ( 29ms max )
 *              11-bit RH: 12ms   ( 15ms max )
 *              10-bit RH:  7ms   (  9ms max )
 *               8-bit RH:  3ms   (  4ms max )
 */
BMP180_status_t  BMP180_TriggerHumidity    ( I2C_parameters_t myI2Cparameters, BMP180_master_mode_t myMode )
{
    uint8_t      cmd        =    0;
    uint8_t      myI2C_stop =    I2C_STOP_BIT;
    i2c_status_t aux;


    /* Check the mode if it is HOLD MASTER MODE, then not generate a stop bit    */
    if ( myMode == BMP180_HOLD_MASTER_MODE )
    {
        cmd         =    BMP180_TRIGGER_HUMIDITY_MEASUREMENT_HOLD_MASTER;
        myI2C_stop  =    I2C_NO_STOP_BIT;
    }
    else
    {
        cmd         =    BMP180_TRIGGER_HUMIDITY_MEASUREMENT_NO_HOLD_MASTER;
        myI2C_stop  =    I2C_STOP_BIT;
    }


    aux = i2c_write ( myI2Cparameters, &cmd, 1U, myI2C_stop );


    /* NOTE: The user has to respect the total conversion time!  */


    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}


/**
 * @brief       BMP180_ReadHumidity   ( I2C_parameters_t , BMP180_vector_data_t* )
 * @details     It reads a new humidity measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHumidity:        Variable to store the humidity.
 *
 *
 * @return      Status of BMP180_ReadHumidity.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         CRC is NOT taken into account.
 * @warning     The measuring time depends on the chosen resolution. The user MUST take this into account.
 * @warning     BMP180_TriggerHumidity MUST be call before.
 */
BMP180_status_t  BMP180_ReadHumidity    ( I2C_parameters_t myI2Cparameters, BMP180_vector_data_t* myHumidity )
{
    uint8_t      cmd[]   =    { 0, 0, 0 };
    i2c_status_t aux;


    /* Read the relative humidity  */
    aux = i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myHumidity->RelativeHumidity    =   ( ( cmd[0] << 8U ) | cmd[1] );
    myHumidity->RelativeHumidity   /=   65536.0f;
    myHumidity->RelativeHumidity   *=   125.0f;
    myHumidity->RelativeHumidity   -=   6.0f;




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



/**
 * @brief       BMP180_ReadRawHumidity   ( I2C_parameters_t , BMP180_vector_data_t* )
 * @details     It reads a new raw humidity measurement.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHumidity:        Variable to store the humidity.
 *
 *
 * @return      Status of BMP180_ReadHumidity.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018       The ORIGIN
 * @pre         CRC is NOT taken into account.
 * @warning     The measuring time depends on the chosen resolution. The user MUST take this into account.
 * @warning     No Hold Master is ONLY implemented.
 * @warning     BMP180_TriggerHumidity MUST be call before.
 */
BMP180_status_t  BMP180_ReadRawHumidity    ( I2C_parameters_t myI2Cparameters, BMP180_vector_data_t* myHumidity )
{
    uint8_t      cmd[]           =    { 0, 0, 0 };
    i2c_status_t aux;


    /* Read the relative humidity  */
    aux = i2c_read ( myI2Cparameters, &cmd[0], 3U );

    /* Parse the data   */
    myHumidity->RawRelativeHumidity    =   ( ( cmd[0] << 8U ) | cmd[1] );




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}


/**
 * @brief       BMP180_BatteryStatus   ( I2C_parameters_t , BMP180_vector_data_t* )
 * @details     It reads the user register to check the battery status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myBattStatus:      Variable to store the battery status.
 *
 *
 * @return      Status of BMP180_BatteryStatus.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         CRC is NOT taken into account.
 * @warning     N/A.
 */
BMP180_status_t  BMP180_BatteryStatus      ( I2C_parameters_t myI2Cparameters, BMP180_vector_data_t* myBattStatus )
{
    uint8_t      cmd     =   BMP180_READ_USER_REGISTER;
    i2c_status_t aux;


    /* Get the battery status    */
    aux = i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd, 1U );

    /* Parse the data    */
    myBattStatus->BatteryStatus   =   ( cmd & USER_REGISTER_STATUS_END_BATTERY_MASK );




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



/**
 * @brief       BMP180_GetSerialNumber   ( I2C_parameters_t , BMP180_vector_data_t* )
 * @details     It gets the serial number ( Electronic Identification Code ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySerialNumber:    Device serial number.
 *
 *
 * @return      Status of BMP180_GetSerialNumber.
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018        The ORIGIN
 * @pre         Composition of Serial Number: SNA_1 | SNA_0 | SNB_3 | SNB_2 | SNB_1 | SNB_0 | SNC_1 | SNC_0
 * @pre         CRC is NOT taken into account.
 * @warning     N/A.
 */
BMP180_status_t  BMP180_GetSerialNumber ( I2C_parameters_t myI2Cparameters, BMP180_vector_data_t* mySerialNumber )
{
    uint8_t      cmd[14]     =   { 0 };
    i2c_status_t aux;


    /* Serial number: first memory access    */
    cmd[0]   =   BMP180_SERIAL_NUMBER_FIRST_MEMORY_ACCESS_MSB;
    cmd[1]   =   BMP180_SERIAL_NUMBER_FIRST_MEMORY_ACCESS_LSB;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 8U );

    /* Serial number: second memory access    */
    cmd[8]   =   BMP180_SERIAL_NUMBER_SECOND_MEMORY_ACCESS_MSB;
    cmd[9]   =   BMP180_SERIAL_NUMBER_SECOND_MEMORY_ACCESS_LSB;
    aux      =   i2c_write ( myI2Cparameters, &cmd[8], 2U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[8], 6U );


    /* Parse the data    */
    mySerialNumber->SerialNumber     =   cmd[11];       // SNA_1
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[12];       // SNA_0
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[0];        // SNB_3
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[2];        // SNB_2
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[4];        // SNB_1
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[6];        // SNB_0
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[8];        // SNC_1
    mySerialNumber->SerialNumber   <<=   8U;

    mySerialNumber->SerialNumber    |=   cmd[9];        // SNC_0




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}
