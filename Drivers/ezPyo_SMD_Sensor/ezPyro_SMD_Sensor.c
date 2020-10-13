/**
 * @brief       ezPyro_SMD_Sensor.c
 * @details     [todo]ezPyro SMD I2C Pyroelectric Infrared Sensor. Single element or 2x2 array.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/October/2020
 * @version     13/October/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "ezPyro_SMD_Sensor.h"


/**
 * @brief       EZPYRO_SMD_SENSOR_Init   ( I2C_parameters_t )
 *
 * @details     [TODO]It configures the SPI pins and resets all the EZPYRO_SMD_SENSOR register ( default value ) and resets its status.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        13/October/2020
 * @version     13/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t  EZPYRO_SMD_SENSOR_Init ( I2C_parameters_t myI2C_parameters )
{
    uint8_t             cmd   =    0;
    i2c_status_t        myI2C_status;


    // Configure the I2C peripheral
    myI2C_status     =   i2c_init ( myI2C_parameters );




    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}
