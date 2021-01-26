/**
 * @brief       SHT3X.c
 * @details     Humidity and Temperature Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

 #include "SHT3X.h"


 /**
 * @brief       SHT3X_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SHT3X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   SHT3X_SUCCESS;
    }
    else
    {
        return   SHT3X_FAILURE;
    }
}



/**
 * @brief       SHT3X_Conf    ( I2C_parameters_t  )
 * @details     It configures the SHT3X device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myResolution:      SHT3X Resolution.
 * @param[in]    myHeater:          SHT3X Heater EN/Abled or Disabled.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_Init.
 *
 * @author      Manuel Caballero
 * @date        3/September/2018
 * @version     3/September/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_Conf    ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]   =    { 0, 0 };
    i2c_status_t aux;


    /*
        Reserved bits must not be changed. Therefore, for any writing to user register, default values of reserved bits must be read first
        Datasheet: 5.6. User register p.19/14.
    */
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[1], 1U );


    aux = i2c_write  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   SHT3X_SUCCESS;
    }
    else
    {
        return   SHT3X_FAILURE;
    }
}
