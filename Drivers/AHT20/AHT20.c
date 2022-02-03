/**
 * @brief       AHT20.h
 * @details     Humidity and Temperature Sensor.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/January/2022
 * @version     31/January/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "AHT20.h"


 /**
 * @brief       AHT20_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AHT20_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AHT20_status_t  AHT20_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_Calibrate    ( I2C_parameters_t )
 * @details     It calibrates the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AHT20_Calibrate
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AHT20_status_t  AHT20_Calibrate ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]	=	{ 0, 0, 0 };
    i2c_status_t aux;


    /* Update the register	*/
    cmd[0]	 =	 AHT20_INITIALIZATION;
    cmd[1]	 =	 INITIALIZATION_DATA_1;
    cmd[2]	 =	 INITIALIZATION_DATA_2;
    aux 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}



/**
 * @brief       AHT20_SoftReset    ( I2C_parameters_t )
 * @details     It performs a soft-reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AHT20_SoftReset
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022        The ORIGIN
 * @pre         The user must consider that the time required for soft-reset does not exceed 20 ms.
 * @warning     N/A.
 */
AHT20_status_t  AHT20_SoftReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Update the register	*/
    cmd	 =	 AHT20_SOFTRESET;
    aux	 =   i2c_write ( myI2Cparameters, (uint8_t*)&cmd, 1U, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   AHT20_SUCCESS;
    }
    else
    {
        return   AHT20_FAILURE;
    }
}
