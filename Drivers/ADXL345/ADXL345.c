/**
 * @brief       ADXL345.c
 * @details     3-Axis, ±2 g/±4 g/±8 g/±16 g Digital Accelerometer.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/August/2017
 * @version     11/August/2017    The ORIGIN
 * @pre         Although the ADXL345 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "ADXL345.h"


/**
 * @brief       uint32_t  ADXL345_GetID   ( NRF_TWI_Type*, uint32_t, uint8_t* )
 * @details     Reseting the data register value.
 *
 * @param[in]    myinstance:    Peripheral's Instance.
 * @param[in]    ADDR:          I2C Device's address.
 * @param[in]    myID:          Device's ID, it should be 0xE5.
 *
 * @param[out]   Status of ADXL345_GetID.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        11/August/2017
 * @version     11/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
uint32_t  ADXL345_GetID   ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* myID )
{
    uint8_t     cmd[]               =   { ADXL345_DEVID };
    uint32_t    aux                 =    0;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &myID[0], 1 );

    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}
