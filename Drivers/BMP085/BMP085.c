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
 * @pre         FIFO functions are NOT implemented.
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
 * @param[in]    myRATE:                New Rate value.
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



/**
 * @brief       ADXL345_SetFreeFallThreshold ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new free fall threshold value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myThreshold:           The free fall threshold.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetFreeFallThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 62.5mg/LSB, and the recommended value is between
 *              300mg ( 5*62.5 = 312.5mg ) - 600mg ( 9*62.5 = 562.5mg ).
 */
ADXL345_status_t  ADXL345_SetFreeFallThreshold ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myThreshold )
{
    uint8_t     cmd[]               =   { ADXL345_THRESH_FF, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myThreshold;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetFreeFallDuration  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new free fall duration value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myDuration:            The free fall duration.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetFreeFallDuration.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 5ms/LSB, and the recommended value is between
 *              100ms ( 5*20 = 100ms ) - 350ms ( 70*5 = 350ms ).
 */
ADXL345_status_t  ADXL345_SetFreeFallDuration  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myDuration )
{
    uint8_t     cmd[]               =   { ADXL345_TIME_FF, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myDuration;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetTapThreshold ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new tap threshold value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myThreshold:           The tap threshold.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetTapThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 62.5mg/LSB. A value of 0 may result in undesirable
 *              behavior if single tap/double tap interrupts are enabled.
 */
ADXL345_status_t  ADXL345_SetTapThreshold ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myThreshold )
{
    uint8_t     cmd[]               =   { ADXL345_THRESH_TAP, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myThreshold;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetTapDuration  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new tap duration value. Representing the maximum time that an
 *              event must be above the THRESH_TAP threshold to qualify as a tap event.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myDuration:            The tap duration.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetTapDuration.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 625µs/LSB. A value of 0 disables the single tap/double tap functions.
 */
ADXL345_status_t  ADXL345_SetTapDuration  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myDuration )
{
    uint8_t     cmd[]               =   { ADXL345_DUR, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myDuration;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetDoubleTapLatency  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new latency value. Representing the wait time from the detection of a tap
 *              event to the start of the time window ( defined by the window register ) during which
 *              a possible second tap event can be detected.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myLatency:             The latency value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetDoubleTapLatency.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 1.25ms/LSB. A value of 0 disables the double tap function.
 */
ADXL345_status_t  ADXL345_SetDoubleTapLatency ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myLatency )
{
    uint8_t     cmd[]               =   { ADXL345_LATENT, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myLatency;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetDoubleTapWindow  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new window value. Representing the amount of time after the expiration of the
 *              latency time (determined by the latent register) during which a second valid tap can begin.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myWindow:              The window value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetDoubleTapWindow.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap function.
 */
ADXL345_status_t  ADXL345_SetDoubleTapWindow ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myWindow )
{
    uint8_t     cmd[]               =   { ADXL345_WINDOW, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myWindow;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetActivityThreshold  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new activity threshold value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myActivityThreshold:   The activity threshold value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetActivityThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 62.5mg/LSB. A value of 0 may result in undesirable behavior
 *              if the activity interrupt is enabled.
 */
ADXL345_status_t  ADXL345_SetActivityThreshold ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myActivityThreshold )
{
    uint8_t     cmd[]               =   { ADXL345_THRESH_ACT, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myActivityThreshold;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetInactivityThreshold  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new inactivity threshold value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myInactivityThreshold: The inactivity threshold value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetInactivityThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 62.5mg/LSB. A value of 0 may result in undesirable behavior if
 *              the inactivity interrupt is enabled.
 */
ADXL345_status_t  ADXL345_SetInactivityThreshold ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myInactivityThreshold )
{
    uint8_t     cmd[]               =   { ADXL345_THRESH_INACT, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myInactivityThreshold;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetTimeInactivity  ( NRF_TWI_Type* , ADXL345_address_t , uint8_t )
 *
 * @details     It sets a new time inactivity value. Representing the amount of time that acceleration
 *              must be less than the value in the THRESH_INACT register for inactivity to be declared.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myTimeInactivity:      The time inactivity value.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetTimeInactivity.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The scale factor is 1 sec/LSB.
 */
ADXL345_status_t  ADXL345_SetTimeInactivity ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t myTimeInactivity )
{
    uint8_t     cmd[]               =   { ADXL345_TIME_INACT, 0 };
    uint32_t    aux                 =    0;

    cmd[1]   =   myTimeInactivity;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetActivity_AC_DC_Coupled  ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_act_inact_ctl_activity_dc_coupled_t )
 *
 * @details     It sets Activity in DC or AC coupled mode.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myDC_Coupled:          DC/AC mode.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetActivity_AC_DC_Coupled.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetActivity_AC_DC_Coupled    ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_act_inact_ctl_activity_dc_coupled_t myDC_Coupled )
{
    uint8_t     cmd[]               =   { ADXL345_ACT_INACT_CTL, 0 };
    uint32_t    aux                 =    0;


    // Read ACT_INACT_CTL register to mask the ACT ac/dc ( D7 ) value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );


    if ( myDC_Coupled == ACTIVITY_DC_Enabled )
        cmd[1]   &=   0x7F;
    else
        cmd[1]   |=   0x80;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetInactivity_AC_DC_Coupled  ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_act_inact_ctl_inactivity_dc_coupled_t )
 *
 * @details     It sets Inactivity in DC or AC coupled mode.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myDC_Coupled:          DC/AC mode.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetInactivity_AC_DC_Coupled.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetInactivity_AC_DC_Coupled   ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_act_inact_ctl_inactivity_dc_coupled_t myDC_Coupled )
{
    uint8_t     cmd[]               =   { ADXL345_ACT_INACT_CTL, 0 };
    uint32_t    aux                 =    0;


    // Read ACT_INACT_CTL register to mask the INACT ac/dc ( D3 ) value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );


    if ( myDC_Coupled == INACTIVITY_DC_Enabled )
        cmd[1]   &=   0xF7;
    else
        cmd[1]   |=   0x08;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetActivity_Axis  ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_act_inact_ctl_activity_axis_t )
 *
 * @details     It sets the axis to be enabled for Activity.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myAxisEnabled:         Enable axis.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetActivity_Axis.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetActivity_Axis  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_act_inact_ctl_activity_axis_t myAxisEnabled )
{
    uint8_t     cmd[]               =   { ADXL345_ACT_INACT_CTL, 0 };
    uint32_t    aux                 =    0;


    // Read ACT_INACT_CTL register to mask the axis ( D6 - D4 ) value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );

    // Clear all the Axis
    cmd[1]   &=   0x8F;

    // Evaluate which axis to be enabled
    switch ( myAxisEnabled ){
        case ACT_X_Enabled:
            cmd[1]   |=   0x40;
            break;

        case ACT_Y_Enabled:
            cmd[1]   |=   0x20;
            break;

        case ACT_Z_Enabled:
            cmd[1]   |=   0x10;
            break;

        case ACT_YZ_Enabled:
            cmd[1]   |=   0x30;
            break;

        case ACT_XZ_Enabled:
            cmd[1]   |=   0x50;
            break;

        case ACT_XY_Enabled:
            cmd[1]   |=   0x60;
            break;

        case ACT_XYZ_Enabled:
            cmd[1]   |=   0x70;
            break;

        default:
        case ACT_XYZ_Disabled:
            cmd[1]   &=   0x8F;
            break;
    }


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetInactivity_Axis  ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_act_inact_ctl_inactivity_axis_t )
 *
 * @details     It sets the axis to be enabled for Inactivity.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myAxisEnabled:         Enable axis.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetInactivity_Axis.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetInactivity_Axis    ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_act_inact_ctl_inactivity_axis_t myAxisEnabled )
{
    uint8_t     cmd[]               =   { ADXL345_ACT_INACT_CTL, 0 };
    uint32_t    aux                 =    0;


    // Read ACT_INACT_CTL register to mask the axis ( D2 - D0 ) value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );

    // Clear all the Axis
    cmd[1]   &=   0xF8;

    // Evaluate which axis to be enabled
    switch ( myAxisEnabled ){
        case INACT_X_Enabled:
            cmd[1]   |=   0x04;
            break;

        case INACT_Y_Enabled:
            cmd[1]   |=   0x02;
            break;

        case INACT_Z_Enabled:
            cmd[1]   |=   0x01;
            break;

        case INACT_YZ_Enabled:
            cmd[1]   |=   0x03;
            break;

        case INACT_XZ_Enabled:
            cmd[1]   |=   0x05;
            break;

        case INACT_XY_Enabled:
            cmd[1]   |=   0x06;
            break;

        case INACT_XYZ_Enabled:
            cmd[1]   |=   0x07;
            break;

        default:
        case INACT_XYZ_Disabled:
            cmd[1]   &=   0xF8;
            break;
    }


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetTap_Axis  ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_tap_axes_axis_t )
 *
 * @details     It sets the axis to be enabled for One/Double tap.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myAxisEnabled:         Enable axis.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetTap_Axis.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetTap_Axis   ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_tap_axes_axis_t myAxisEnabled )
{
    uint8_t     cmd[]               =   { ADXL345_TAP_AXES, 0 };
    uint32_t    aux                 =    0;


    // Read TAP_AXES register to mask the axis ( D2 - D0 ) value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );

    // Clear all the Axis
    cmd[1]   &=   0xF8;

    // Evaluate which axis to be enabled
    switch ( myAxisEnabled ){
        case TAP_X_Enabled:
            cmd[1]   |=   0x04;
            break;

        case TAP_Y_Enabled:
            cmd[1]   |=   0x02;
            break;

        case TAP_Z_Enabled:
            cmd[1]   |=   0x01;
            break;

        case TAP_YZ_Enabled:
            cmd[1]   |=   0x03;
            break;

        case TAP_XZ_Enabled:
            cmd[1]   |=   0x05;
            break;

        case TAP_XY_Enabled:
            cmd[1]   |=   0x06;
            break;

        case TAP_XYZ_Enabled:
            cmd[1]   |=   0x07;
            break;

        default:
        case TAP_XYZ_Disabled:
            cmd[1]   &=   0xF8;
            break;
    }


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetDouble_Suppress  ( NRF_TWI_Type* , ADXL345_address_t , ADXL345_tap_axes_suppress_t )
 *
 * @details     Setting the suppress bit suppresses double tap detection if acceleration greater than the value
 *              in THRESH_TAP is present between taps.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    mySuppressEnabled:     Enable/Disable.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetDouble_Suppress.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetDouble_Suppress    ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, ADXL345_tap_axes_suppress_t mySuppressEnabled )
{
    uint8_t     cmd[]               =   { ADXL345_TAP_AXES, 0 };
    uint32_t    aux                 =    0;


    // Read TAP_AXES register to mask the suppress ( D3 ) value
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );

    // Clear the current value
    cmd[1]   &=   0xF7;


    if ( mySuppressEnabled  ==  SUPPRESS_Enabled )
        cmd[1]   |=   0x08;



    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_Read_ACT_TAP_STATUS   ( NRF_TWI_Type*, uint32_t, uint8_t* )
 *
 * @details     It reads the ACT_TAP_STATUS register.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    ADDR:              I2C Device's address.
 * @param[in]    myACT_TAP_STATUS:  Status variable.
 *
 * @param[out]   myACT_TAP_STATUS:  Current ACT_TAP_STATUS.
 *
 *
 * @return       Status of ADXL345_Read_ACT_TAP_STATUS.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_Read_ACT_TAP_STATUS   ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t* myACT_TAP_STATUS )
{
    uint8_t     cmd[]               =   { ADXL345_ACT_TAP_STATUS };
    uint32_t    aux                 =    0;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &myACT_TAP_STATUS[0], 1 );

    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_EnableInterrupts  ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_int_map_t )
 *
 * @details     It enables the interrupts.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myInterruptsMap:       Map the interrupt sources.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_EnableInterrupts.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_EnableInterrupts  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, AXDL345_int_map_t myInterruptsMap )
{
    uint8_t     cmd[]               =   { ADXL345_INT_ENABLE, 0 };
    uint32_t    aux                 =    0;


    // Clear the current value
    cmd[1]    =   myInterruptsMap;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_SetInterruptsMap  ( NRF_TWI_Type* , ADXL345_address_t , AXDL345_int_map_t, AXDL345_int_pin_t )
 *
 * @details     It links the interrupt sources to the right pin ( 1 or 2 ).
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myInterruptsMap:       Interrupt sources.
 * @param[in]    myInterruptPin:        Map the interrupt source to pin 1 or 2.
 *
 * @param[out]   NaN.
 *
 * @return       Status of ADXL345_SetInterruptsMap.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_SetInterruptsMap  ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, AXDL345_int_map_t myInterruptsMap, AXDL345_int_pin_t myInterruptPin )
{
    uint8_t     cmd[]               =   { ADXL345_INT_MAP, 0 };
    uint32_t    aux                 =    0;


    // Read INT_MAP register to mask the interrupts
    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[1], 1 );


    if ( myInterruptPin == INT1_PIN )
        cmd[1]    &=   ~myInterruptsMap;
    else
        cmd[1]    |=   myInterruptsMap;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}



/**
 * @brief       ADXL345_ReadInterruptSource   ( NRF_TWI_Type*, uint32_t, uint8_t* )
 *
 * @details     It reads the interrupt sources.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    ADDR:              I2C Device's address.
 * @param[in]    myIntSource:       Status variable.
 *
 * @param[out]   myIntSource:       Current ACT_TAP_STATUS.
 *
 *
 * @return       Status of ADXL345_ReadInterruptSource.
 *
 *
 * @author      Manuel Caballero
 * @date        18/August/2017
 * @version     18/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
ADXL345_status_t  ADXL345_ReadInterruptSource   ( NRF_TWI_Type* myinstance, ADXL345_address_t ADDR, uint8_t* myIntSource )
{
    uint8_t     cmd[]               =   { ADXL345_INT_SOURCE };
    uint32_t    aux                 =    0;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &myIntSource[0], 1 );

    if ( aux == I2C_SUCCESS )
       return   ADXL345_SUCCESS;
    else
       return   ADXL345_FAILURE;
}
