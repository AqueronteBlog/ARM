/**
 * @brief       HTU21D.h
 * @details     Digital Relative Humidity sensor with Temperature output.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "HTU21D.h"


 /**
 * @brief       uint32_t  HTU21D_Init    ( uint32_t SDA, uint32_t SCL, uint32_t MODE, uint32_t RESOLUTION, uint32_t HEATER )
 * @details     Initialing the HTU21D and defines
 *
 * @param[in]    SDA:        I2C SDA pin.
 * @param[in]    SCL:        I2C SCL pin.
 * @param[in]    MODE:       HTU21D Hold Master or No Hold Master mode.
 * @param[in]    RESOLUTION: HTU21D Resolution.
 * @param[in]    HEATER:     HTU21D Heater Enabled or Disabled.
 *
 * @param[out]   Status of HTU21D_Init.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint32_t  HTU21D_Init    ( uint32_t MODE, uint8_t RESOLUTION, uint8_t HEATER )
{
    uint8_t     cmd [] = { HTU21D_READ_REGISTER, 0 };
    uint32_t    aux    =   0;


    HTU21D_Mode         =   MODE;
    HTU21D_Resolution   =   RESOLUTION;

// Reserved bits must not be changed. Therefore, for any writing to user register, default values of reserved bits must be read first
// Datasheet: User register p.13.
    aux = i2c_write ( &cmd[0], 1, I2C_STOP_BIT );
    aux = i2c_read  ( &cmd[0], 1 );

    cmd[0]          &=   ~( USER_REGISTER_RESOLUTION_MASK | USER_REGISTER_STATUS_END_BATTERY_MASK | USER_REGISTER_HEATER_MASK | USER_REGISTER_OTP_MASK );
    cmd[1]           =   ( cmd[0] | ( ( RESOLUTION | HEATER ) | USER_REGISTER_OTP_DISABLED ) );
    cmd[0]           =   HTU21D_WRITE_REGISTER;

    aux = i2c_write  ( &cmd[0], 2, I2C_STOP_BIT );

    /*
    // REad back the register
    cmd[0]           =   HTU21D_READ_REGISTER;
    aux = i2c_write ( &cmd[0], 1, I2C_STOP_BIT );
    aux = i2c_read  ( &cmd[0], 1 );
    */

    if ( aux == HTU21D_SUCCESS )
        return   HTU21D_SUCCESS;
    else
        return   HTU21D_FAILURE;

}



 /**
 * @brief       uint32_t  HTU21D_SoftReset   ( void )
 * @details     Rebooting the HTU21D sensor switching the power off and on again.
 *
 * @param[in]    NaN.
 *
 * @param[out]   Status of HTU21D_SoftReset.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     The soft reset takes less than 15ms. The user must take this
 *              into account.
 */
uint32_t  HTU21D_SoftReset   ( void )
{
    uint8_t     cmd [] = { HTU21D_SOFT_RESET };
    uint32_t    aux    =   0;

    aux = i2c_write ( &cmd[0], 1, I2C_STOP_BIT );

    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
    else
       return   HTU21D_FAILURE;
}


 /**
 * @brief       uint32_t  HTU21D_TriggerTemperature   ( void )
 * @details     Trigger a new temperature measurement.
 *
 * @param[in]    NaN.
 *
 * @param[out]   Status of HTU21D_TriggerTemperature.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     The measuring time depends on the chosen resolution. The user
 *              must take this into account.
 * @warning     No Hold Master is ONLY implemented.
 */
uint32_t  HTU21D_TriggerTemperature    ( void )
{
    uint8_t     cmd [] = { HTU21D_TRIGGER_TEMPERATURE_MEASUREMENT_NO_HOLD_MASTER };
    uint32_t    aux    =   0;


    aux = i2c_write ( &cmd[0], 1, I2C_STOP_BIT );

    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
    else
       return   HTU21D_FAILURE;
}


 /**
 * @brief       uint32_t  HTU21D_ReadTemperature   ( float* )
 * @details     Read a new temperature measurement.
 *
 * @param[in]    mytemperature:  Variable to store the temperature.
 *
 * @param[out]   Status of HTU21D_ReadTemperature.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     The measuring time depends on the chosen resolution. The user
 *              must take this into account.
 * @warning     No Hold Master is ONLY implemented.
 * @warning     HTU21D_TriggerTemperature MUST be call before.
 */
uint32_t  HTU21D_ReadTemperature    ( float* mytemperature )
{
    uint32_t    aux         =   0;
    uint8_t     myRawTemp[] =   { 0, 0, 0};


    aux = i2c_read ( &myRawTemp[0], 3 );

    *mytemperature    =   ( myRawTemp[0] << 8 ) | myRawTemp[1];
    *mytemperature   /=   65536.0;
    *mytemperature    =   ( *mytemperature * 175.72 ) - 46.85;

    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
    else
       return   HTU21D_FAILURE;
}


 /**
 * @brief       uint32_t  HTU21D_TriggerHumidity   ( void )
 * @details     Trigger a new humidity measurement.
 *
 * @param[in]    NaN.
 *
 * @param[out]   Status of HTU21D_TriggerHumidity.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     The measuring time depends on the chosen resolution. The user
 *              must take this into account.
 * @warning     No Hold Master is ONLY implemented.
 */
uint32_t  HTU21D_TriggerHumidity    ( void )
{
    uint8_t     cmd [] = { HTU21D_TRIGGER_HUMIDITY_MEASUREMENT_NO_HOLD_MASTER };
    uint32_t    aux    =   0;


    aux = i2c_write ( &cmd[0], 1, I2C_STOP_BIT );

    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
    else
       return   HTU21D_FAILURE;
}


/**
 * @brief       uint32_t  HTU21D_ReadHumidity   ( float* )
 * @details     Read a new humidity measurement.
 *
 * @param[in]    myhumidity:  Variable to store the humidity.
 *
 * @param[out]   Status of HTU21D_ReadHumidity.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     The measuring time depends on the chosen resolution. The user
 *              must take this into account.
 * @warning     No Hold Master is ONLY implemented.
 * @warning     HTU21D_TriggerHumidity MUST be call before.
 */
uint32_t  HTU21D_ReadHumidity    ( float* myhumidity )
{
    uint32_t    aux         =   0;
    uint8_t     myRawRH[] =   { 0, 0, 0};


    aux = i2c_read ( &myRawRH[0], 3 );

    *myhumidity    =   ( myRawRH[0] << 8 ) | myRawRH[1];
    *myhumidity   /=   65536.0;
    *myhumidity    =   ( *myhumidity * 125.0 ) - 6.0;


    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
    else
       return   HTU21D_FAILURE;
}


/**
 * @brief       uint32_t  HTU21D_BatteryStatus   ( void )
 * @details     Read the user register to check the battery status.
 *
 * @param[in]    NaN.
 *
 * @param[out]   Status of HTU21D_BatteryStatus.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint32_t  HTU21D_BatteryStatus      ( uint8_t* battStatus )
{
    uint8_t     cmd [] = { HTU21D_READ_REGISTER };
    uint32_t    aux    =   0;

    aux = i2c_write ( &cmd[0], 1, I2C_STOP_BIT );
    aux = i2c_read  ( battStatus, 1 );

    if ( aux == HTU21D_SUCCESS )
       return   HTU21D_SUCCESS;
    else
       return   HTU21D_FAILURE;
}
