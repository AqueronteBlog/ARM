/**
 * @brief       QMP6988.h
 * @details     Digital Barometric Pressure Sensor.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/February/2022
 * @version     12/February/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "QMP6988.h"


 /**
 * @brief       QMP6988_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of QMP6988_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_Calibrate    ( I2C_parameters_t )
 * @details     It calibrates the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_Calibrate
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_Calibrate ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]	=	{ 0, 0, 0 };
    i2c_status_t aux;


    /* Update the register	*/
    //cmd[0]	 =	 QMP6988_INITIALIZATION;
    cmd[1]	 =	 INITIALIZATION_DATA_1;
    cmd[2]	 =	 INITIALIZATION_DATA_2;
    aux 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}
