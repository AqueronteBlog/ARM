/**
 * @brief       BME680.h
 * @details     Low power gas, pressure, temperature and humidity sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2018
 * @version     16/July/2018    The ORIGIN
 * @pre         Although the BME680 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C.
 * @pre         This files makes Bosh's driver compatible with our I2C driver.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "bme680_port.h"


/**
 * @brief       BME680_Init_I2C ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BME680_Init_I2C.
 *
 *
 * @author      Manuel Caballero
 * @date        16/July/2018
 * @version     16/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BME680_status_t  BME680_Init_I2C ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   BME680_SUCCESS;
    else
        return   BME680_FAILURE;
}



/**
 * @brief       user_delay_ms ( uint32_t )
 *
 * @details     Return control or wait, for a period amount of milliseconds
 *
 * @param[in]    period:       Delay in milliseconds.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BME680_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        16/July/2018
 * @version     16/July/2018   The ORIGIN
 * @pre         This is a Bosh pointer function adapted to our system.
 * @warning     N/A.
 */
void user_delay_ms ( uint32_t period )
{
    /*
     * Return control or wait,
     * for a period amount of milliseconds
     */
     nrf_delay_ms ( period );
}



/**
 * @brief       user_i2c_read ( uint8_t , uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
 *
 * @details     It adapts I2C reading functionality.
 *
 * @param[in]    dev_id:    I2C address.
 * @param[in]    reg_addr:  Register to be read.
 * @param[in]    len:       How many bytes to read.
 *
 * @param[out]   reg_data:  Result.
 *
 *
 * @return       Status of user_i2c_read.
 *
 *
 * @author      Manuel Caballero
 * @date        16/July/2018
 * @version     16/July/2018   The ORIGIN
 * @pre         This is a Bosh pointer function adapted to our system.
 * @warning     N/A.
 */
int8_t user_i2c_read ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    i2c_status_t aux;

    /* Read data    */
    myBME680_I2C_parameters.ADDR     =   dev_id;
    aux      =   i2c_write ( myBME680_I2C_parameters, &reg_addr, 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myBME680_I2C_parameters, &reg_data[0], len );


    if ( aux == I2C_SUCCESS )
    {
        rslt     =   BME680_SUCCESS;
    }
    else
    {
        rslt     =   BME680_FAILURE;
    }


    return rslt;
}



/**
 * @brief       user_i2c_write ( uint8_t , uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
 *
 * @details     It adapts I2C writing functionality.
 *
 * @param[in]    dev_id:    I2C address.
 * @param[in]    reg_addr:  Register to be read.
 * @param[out]   reg_data:  Data to be written.
 * @param[in]    len:       How many bytes to read.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of user_i2c_write.
 *
 *
 * @author      Manuel Caballero
 * @date        16/July/2018
 * @version     16/July/2018   The ORIGIN
 * @pre         This is a Bosh pointer function adapted to our system.
 * @warning     N/A.
 */
int8_t user_i2c_write ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len )
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Write      | (reg_data[0])       |
     * | Write      | (....)              |
     * | Write      | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    i2c_status_t aux;
    uint8_t      cmd[16] =  { 0 };
    uint32_t     i       =   0;

    /* Prepare the data to be sent   */
    cmd[0]   =   reg_addr;
    for ( i = 1; i <= len; i++ )
    {
        cmd[i]   =   reg_data[i - 1];
    }

    /* Write data    */
    myBME680_I2C_parameters.ADDR     =   dev_id;
    aux      =   i2c_write ( myBME680_I2C_parameters, &cmd[0], len + 1, I2C_STOP_BIT );


    if ( aux == I2C_SUCCESS )
    {
        rslt     =   BME680_SUCCESS;
    }
    else
    {
        rslt     =   BME680_FAILURE;
    }


    return rslt;
}
