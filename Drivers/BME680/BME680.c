/**
 * @brief       BME680.c
 * @details     Low power gas, pressure, temperature & humidity sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/February/2018
 * @version     13/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "BME680.h"


/**
 * @brief       BME680_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BME680_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        5/February/2018
 * @version     5/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BME680_status_t  BME680_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   BME680_SUCCESS;
    else
        return   BME680_FAILURE;
}



/**
 * @brief       BME680_GetCalibrationData ( I2C_parameters_t , BME680_calibration_data_t* )
 *
 * @details     It configures the device: resolution and heater.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCalibrationData: par_g1, par_g2, par_g3, res_heat_range and res_heat_val.
 *
 *
 * @return       Status of BME680_GetCalibrationData.
 *
 *
 * @author      Manuel Caballero
 * @date        20/February/2018
 * @version     20/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BME680_status_t  BME680_GetCalibrationData ( I2C_parameters_t myI2Cparameters, BME680_calibration_data_t* myCalibrationData )
{
    uint8_t      cmd[]    =    { 0, 0 };

    i2c_status_t aux;       // BME680_PAR_G1


    // Get par_g1 value
    cmd[0]   =   BME680_PAR_G1;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &myCalibrationData->par_g1, 1 );

    // Get par_g2 value
    cmd[0]   =   BME680_PAR_G2;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &myCalibrationData->par_g2, 1 );




    if ( aux == I2C_SUCCESS )
        return   BME680_SUCCESS;
    else
        return   BME680_FAILURE;
}
