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
 * @brief       ADXL345_status_t  ADXL345_GetID   ( NRF_TWI_Type*, uint32_t, uint8_t* )
 *
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
ADXL345_status_t  ADXL345_GetID   ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t* myID )
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



/**
 * @brief       ADXL345_status_t  ADXL345_Init  ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_bw_rate_low_power_t , AXDL345_bw_rate_rate_t ,
 *                                        ADXL345_data_format_int_invert_t , ADXL345_data_format_full_res_t , ADXL345_data_format_justify_t ,
 *                                        ADXL345_data_format_range_t )
 *
 * @details     Reseting the data register value.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    ADDR:              I2C Device's address.
 * @param[in]    LOWPOWER:          If the device works in low power mode or not.
 * @param[in]    RATE:              Bandwidth rate.
 * @param[in]    INT_INVERT:        If the interrupts to active high or low.
 * @param[in]    FULLRESOLUTION:    If the device works in full resolution mode or not ( 10-bit mode ).
 * @param[in]    JUSTIFY:           If the device works in left-justified (MSB) mode or not.
 * @param[in]    RANGE:             g range.
 *
 * @param[out]   Status of ADXL345_Init.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        11/August/2017
 * @version     11/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_Init   ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, AXDL345_bw_rate_low_power_t LOWPOWER, AXDL345_bw_rate_rate_t RATE,
                                   ADXL345_data_format_int_invert_t INT_INVERT, ADXL345_data_format_full_res_t FULLRESOLUTION, ADXL345_data_format_justify_t JUSTIFY,
                                   ADXL345_data_format_range_t RANGE )
{
    uint8_t     cmd[]               =   { ADXL345_BW_RATE, 0 };
    uint32_t    aux                 =    0;


    // BANDWIDTH RATE.
    // Rate
    if ( ( RATE >= BW_RATE_RATE_0_10HZ ) && ( RATE <= BW_RATE_RATE_3200HZ ) )
        cmd[1]   |=   RATE;
    else
        return   ADXL345_FAILURE;

    // Normal mode or Low Power mode
    if ( LOWPOWER == true ){
        if ( ( RATE >= BW_RATE_RATE_12_5HZ ) && ( RATE <= BW_RATE_RATE_400HZ ) )
            cmd[1]   |=  ( 1 << 4 );
        else
            return   ADXL345_FAILURE;
    }

    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );


    // DATA FORMAT
    cmd[0]   =   ADXL345_DATA_FORMAT;
    cmd[1]   =   0;

    // Interrupt Invert
    if ( INT_INVERT == true )
        cmd[1]   |=  ( 1 << 5 );

    // Full Resolution
    if ( FULLRESOLUTION == true )
        cmd[1]   |=  ( 1 << 3 );

    // Justify
    if ( JUSTIFY == true )
        cmd[1]   |=  ( 1 << 2 );

    // Range
    if ( ( RANGE >= DATA_FORMAT_RANGE_2_G ) && ( RANGE <= DATA_FORMAT_RANGE_16_G )  )
        cmd[1]   |=  RANGE;
    else
        return   ADXL345_FAILURE;

    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}
