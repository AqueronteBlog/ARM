/**
 * @brief       MC3635.c
 * @details     3-Axis Accelerometer.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018    The ORIGIN
 * @pre         Although the MC3635 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

 #include "MC3635.h"


/**
 * @brief       MC3635_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   MC3635_SUCCESS;
    else
        return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_Conf  ( I2C_parameters_t , AXDL345_bw_rate_low_power_t , AXDL345_bw_rate_rate_t ,
 *                              MC3635_data_format_int_invert_t , MC3635_data_format_full_res_t , MC3635_data_format_justify_t ,
 *                              MC3635_data_format_range_t )
 *
 * @details     It initializes the MC3635.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    LOWPOWER:          If the device works in low power mode or not.
 * @param[in]    RATE:              Bandwidth rate.
 * @param[in]    INT_INVERT:        If the interrupts to active high or low.
 * @param[in]    FULLRESOLUTION:    If the device works in full resolution mode or not ( 10-bit mode ).
 * @param[in]    JUSTIFY:           If the device works in left-justified (MSB) mode or not.
 * @param[in]    RANGE:             g range.
 *
 * @param[out]   N/A.
 *
 * @return       Status of MC3635_Init.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_Conf   ( I2C_parameters_t myI2Cparameters, AXDL345_bw_rate_low_power_t LOWPOWER, AXDL345_bw_rate_rate_t RATE,
                                   MC3635_data_format_int_invert_t INT_INVERT, MC3635_data_format_full_res_t FULLRESOLUTION, MC3635_data_format_justify_t JUSTIFY,
                                   MC3635_data_format_range_t RANGE )
{
    uint8_t     cmd[]               =   { MC3635_BW_RATE, 0 };
    uint32_t    aux                 =    0;


    // BANDWIDTH RATE.
    // Rate
    if ( ( RATE >= BW_RATE_RATE_0_10HZ ) && ( RATE <= BW_RATE_RATE_3200HZ ) )
        cmd[1]   |=   RATE;
    else
        return   MC3635_FAILURE;

    // Normal mode or Low Power mode
    if ( LOWPOWER == BW_RATE_LOW_POWER_Enabled ){
        if ( ( RATE >= BW_RATE_RATE_12_5HZ ) && ( RATE <= BW_RATE_RATE_400HZ ) )
            cmd[1]   |=  ( 1 << 4 );
        else
            return   MC3635_FAILURE;
    }

    aux = i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );


    // DATA FORMAT
    cmd[0]   =   MC3635_DATA_FORMAT;
    cmd[1]   =   0;

    // Interrupt Invert
    if ( INT_INVERT == DATA_FORMAT_INT_INVERT_Enabled )
        cmd[1]   |=  ( 1 << 5 );

    // Full Resolution
    if ( FULLRESOLUTION == DATA_FORMAT_FULL_RES_Enabled )
        cmd[1]   |=  ( 1 << 3 );

    // Justify
    if ( JUSTIFY == DATA_FORMAT_JUSTIFY_Enabled )
        cmd[1]   |=  ( 1 << 2 );

    // Range
    if ( ( RANGE >= DATA_FORMAT_RANGE_2_G ) && ( RANGE <= DATA_FORMAT_RANGE_16_G )  )
        cmd[1]   |=  RANGE;
    else
        return   MC3635_FAILURE;

    aux = i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}
