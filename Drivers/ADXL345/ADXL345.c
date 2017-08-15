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
 * @brief       ADXL345_GetID   ( NRF_TWI_Type*, uint32_t, uint8_t* )
 *
 * @details     Reseting the data register value.
 *
 * @param[in]    myinstance:    Peripheral's Instance.
 * @param[in]    ADDR:          I2C Device's address.
 * @param[in]    myID:          Device's ID, it should be 0xE5.
 *
 * @param[out]   myID:          Device's ID, it should be 0xE5.
 *
 *
 * @return       Status of ADXL345_GetID.
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
 * @brief       ADXL345_Init  ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_bw_rate_low_power_t , AXDL345_bw_rate_rate_t ,
 *                              ADXL345_data_format_int_invert_t , ADXL345_data_format_full_res_t , ADXL345_data_format_justify_t ,
 *                              ADXL345_data_format_range_t )
 *
 * @details     It initializes the ADXL345.
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
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_Init.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        14/August/2017
 * @version     14/August/2017   The ORIGIN
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
    if ( LOWPOWER == BW_RATE_LOW_POWER_Enabled ){
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
        return   ADXL345_FAILURE;

    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_PowerMode      ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_power_ctl_measure_t )
 *
 * @details     It puts the ADXL345 in Measure or Standby mode.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    ADDR:              I2C Device's address.
 * @param[in]    MEASUREMODE:       It puts the ADXL345 in Standby mode or Measure mode.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_PowerMode.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        14/August/2017
 * @version     14/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_PowerMode      ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, AXDL345_power_ctl_measure_t MEASUREMODE )
{
    uint8_t     cmd[]               =   { ADXL345_POWER_CTL, 0 };
    uint32_t    aux                 =    0;


    // READ THE POWER_CTL REGISTER
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );


    // Normal mode or Low Power mode
    if ( MEASUREMODE == MEASURE_MODE ){
        cmd[1]   |=  ( 1 << 3 );
    }
    else{
        cmd[1]   &=  ~( 1 << 3 );
    }

    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_ReadRawData    ( NRF_TWI_Type* , ADXL345_address_t , Vector_t* )
 *
 * @details     It reads the raw data from ADXL345.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    ADDR:              I2C Device's address.
 * @param[in]    myXYZVector:       XAxis, YAxis and ZAxis.
 *
 * @param[out]   myXYZVector:       XAxis, YAxis and ZAxis.
 *
 * @return       Status of ADXL345_ReadRawData.
 *
 *
 * @author      Manuel Caballero
 * @date        14/August/2017
 * @version     14/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_ReadRawData    ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, Vector_t* myXYZVector )
{
    uint8_t     cmd[]               =   { ADXL345_DATAX0, 0, 0, 0, 0, 0, 0 };
    uint32_t    aux                 =    0;


    // Multiple-byte read: X, Y and Z Axis Raw Data
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 6 );


    // Parse the data
    myXYZVector->XAxis    =   ( ( cmd[2] << 8 ) | cmd[1] );
    myXYZVector->YAxis    =   ( ( cmd[4] << 8 ) | cmd[3] );
    myXYZVector->ZAxis    =   ( ( cmd[6] << 8 ) | cmd[5] );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_ReadScaledData    ( NRF_TWI_Type* , ADXL345_address_t , Vector_t* )
 *
 * @details     It reads the scaled data from ADXL345.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myScaled_XYZVector:    XAxis, YAxis and ZAxis.
 *
 * @param[out]   myScaled_XYZVector:    XAxis, YAxis and ZAxis.
 *
 * @return       Status of ADXL345_ReadScaledData.
 *
 *
 * @author      Manuel Caballero
 * @date        14/August/2017
 * @version     14/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_ReadScaledData ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, Vector_f* myScaled_XYZVector )
{
    uint8_t     cmd[]               =   { ADXL345_DATA_FORMAT };
    uint32_t    aux                 =    0;
    float       scaleFactor         =    0;

    Vector_t  myXYZ_RawVector, *myXYZ_RawVector_ptr = &myXYZ_RawVector;


    // Read the Raw data
    aux = ADXL345_ReadRawData ( myinstance, ADDR, &myXYZ_RawVector_ptr[0] );



    // Read DATA_FORMAT register to check if the device is working in Full Resolution and which Range
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[0], 1 );

    // Check if it is working in full resolution
    if ( ( cmd[0] & 0x08 )  ==  0x08 )
        scaleFactor  =   3.9;
    else{
        // Check which Range the device is working on
        switch ( cmd[0] & 0x03 ){
            case 0x00:
            // Range: ±2g
                scaleFactor  =   3.9;
                break;
            case 0x01:
            // Range: ±4g
                scaleFactor  =   7.8;
                break;
            case 0x02:
            // Range: ±8g
                scaleFactor  =   15.6;
                break;
            case 0x03:
            // Range: ±16g
                scaleFactor  =   31.2;
                break;
        }
    }


    // Update the value considering the right Scale Factor
    myScaled_XYZVector->Xmg_Axis    =   ( myXYZ_RawVector.XAxis ) * scaleFactor;
    myScaled_XYZVector->Ymg_Axis    =   ( myXYZ_RawVector.YAxis ) * scaleFactor;
    myScaled_XYZVector->Zmg_Axis    =   ( myXYZ_RawVector.ZAxis ) * scaleFactor;



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_GetRange    ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_data_format_range_t* )
 *
 * @details     It reads the current range value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myRANGE:               Range variable.
 *
 * @param[out]   myRANGE:               Current range.
 *
 * @return       Status of ADXL345_GetRange.
 *
 *
 * @author      Manuel Caballero
 * @date        15/August/2017
 * @version     15/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_GetRange  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_data_format_range_t* myRANGE )
{
    uint8_t     cmd[]               =   { ADXL345_DATA_FORMAT };
    uint32_t    aux                 =    0;


    // Read DATA_FORMAT register to get the current Range
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[0], 1 );

    // Update the Range variable
    *myRANGE =   ( cmd[0] & 0x03 );


    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}


/**
 * @brief       ADXL345_SetRange    ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_data_format_range_t )
 *
 * @details     It sets a new range value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myRANGE:               New Range value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetRange.
 *
 *
 * @author      Manuel Caballero
 * @date        15/August/2017
 * @version     15/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetRange  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_data_format_range_t myRANGE )
{
    uint8_t     cmd[]               =   { ADXL345_DATA_FORMAT, 0 };
    uint32_t    aux                 =    0;


    // Read DATA_FORMAT register to mask the Range value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );

    // Update the Range variable
    cmd[1]   =   ( cmd[1] & 0xFC ) | myRANGE;

    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_GetRate    ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_bw_rate_rate_t* )
 *
 * @details     It reads the current rate value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myRATE:                Rate variable.
 *
 * @param[out]   myRATE:                Current Rate value.
 *
 * @return       Status of ADXL345_GetRate.
 *
 *
 * @author      Manuel Caballero
 * @date        15/August/2017
 * @version     15/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_GetRate  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, AXDL345_bw_rate_rate_t* myRATE )
{
    uint8_t     cmd[]               =   { ADXL345_BW_RATE };
    uint32_t    aux                 =    0;


    // Read BW_RATE register to get the current Rate value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[0], 1 );


    // Update the Rate variable
    *myRATE =   ( cmd[0] & 0x0F );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetRate    ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_bw_rate_rate_t )
 *
 * @details     It sets a new rate value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myRATE :               New Rate value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetRate.
 *
 *
 * @author      Manuel Caballero
 * @date        15/August/2017
 * @version     15/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetRate  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, AXDL345_bw_rate_rate_t myRATE )
{
    uint8_t     cmd[]               =   { ADXL345_BW_RATE, 0 };
    uint32_t    aux                 =    0;


    // Read BW_RATE register to mask the Rate value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );


    // Check the new Rate value is in range and if the device is working in Low Power mode
    if ( ( myRATE >= BW_RATE_RATE_0_10HZ ) && ( myRATE <= BW_RATE_RATE_3200HZ ) ){
        if ( ( cmd[1] & 0x10) == 0x10 ){
           if ( ( myRATE >= BW_RATE_RATE_12_5HZ ) && ( myRATE <= BW_RATE_RATE_400HZ ) ){}
        }
    } else
        return   ADXL345_FAILURE;


    // Update the Rate variable
    cmd[1]    =   ( cmd[1] & 0xF0 ) | myRATE;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}
