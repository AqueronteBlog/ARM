/**
 * @brief       BMP085.c
 * @details     Digital pressure sensor.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "BMP085.h"


/**
 * @brief       BMP085_Init   ( NRF_TWI_Type* , BMP085_address_t , Vector_cal_coeff_t* )
 *
 * @details     It gets the calibration coefficients.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 *
 * @param[out]   Vector_cal_coeff_t:    Calibration coefficients.
 *
 *
 * @return       Status of BMP085_GetCalibrationCoefficients.
 *
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
BMP085_status_t  BMP085_GetCalibrationCoefficients  ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_cal_coeff_t* myCalCoeff )
{
    uint8_t     cmd[22]             =   { 0 };
    uint32_t    aux                 =    0;

    cmd[0]   =   BMP085_AC1_MSB;

    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[0], 22 );

    // Parse the data
    myCalCoeff->AC1  =   ( cmd[0]  << 8 ) | cmd[1];
    myCalCoeff->AC2  =   ( cmd[2]  << 8 ) | cmd[3];
    myCalCoeff->AC3  =   ( cmd[4]  << 8 ) | cmd[5];
    myCalCoeff->AC4  =   ( cmd[6]  << 8 ) | cmd[7];
    myCalCoeff->AC5  =   ( cmd[8]  << 8 ) | cmd[9];
    myCalCoeff->AC6  =   ( cmd[10] << 8 ) | cmd[11];
    myCalCoeff->B1   =   ( cmd[12] << 8 ) | cmd[13];
    myCalCoeff->B2   =   ( cmd[14] << 8 ) | cmd[15];
    myCalCoeff->MB   =   ( cmd[16] << 8 ) | cmd[17];
    myCalCoeff->MC   =   ( cmd[18] << 8 ) | cmd[19];
    myCalCoeff->MD   =   ( cmd[20] << 8 ) | cmd[21];



    if ( aux == I2C_SUCCESS )
       return   BMP085_SUCCESS;
    else
       return   BMP085_FAILURE;
}


/**
 * @brief       BMP085_TriggerTemperature   ( NRF_TWI_Type* , BMP085_address_t )
 *
 * @details     It triggers a new temperature measurement.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of BMP085_TriggerTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The user MUST respect the maximum temperature conversion time, in this
 *              case, that value is 4.5ms.
 */
BMP085_status_t  BMP085_TriggerTemperature  ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR )
{
    uint8_t     cmd[]             =   { BMP085_CONTROL, BMP085_TRIGGER_TEMPERATURE };
    uint32_t    aux               =    0;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   BMP085_SUCCESS;
    else
       return   BMP085_FAILURE;
}


/**
 * @brief       BMP085_ReadRawTemperature   ( NRF_TWI_Type* , BMP085_address_t , Vector_temp_f* )
 *
 * @details     It reads an uncompensated temperature.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 *
 * @param[out]   myRawTemperature:      Uncompensated temperature.
 *
 *
 * @return       Status of BMP085_ReadRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017   The ORIGIN
 * @pre         BMP085_TriggerTemperature function MUST be called before calling this one.
 * @warning     The user MUST respect the maximum temperature conversion time, in this
 *              case, that value is 4.5ms.
 */
BMP085_status_t  BMP085_ReadRawTemperature  ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_temp_f* myRawTemperature )
{
    uint8_t     cmd[]             =   { BMP085_READ_TEMPERATURE, 0 };
    uint32_t    aux               =    0;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[0], 2 );


    // Parse the data
    myRawTemperature->Temperature    =   ( cmd[0] << 8 ) | cmd[1];



    if ( aux == I2C_SUCCESS )
       return   BMP085_SUCCESS;
    else
       return   BMP085_FAILURE;
}


/**
 * @brief       BMP085_TriggerPressure   ( NRF_TWI_Type* , BMP085_address_t, BMP085_pressure_osrs_t )
 *
 * @details     It triggers a new pressure measurement.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myResolution:          Pressure resolution.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of BMP085_TriggerPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017   The ORIGIN
 * @pre         NaN
 * @warning     The user MUST respect the maximum pressure conversion time:
 *                  Ultra Low Power Mode:   4.5ms.
 *                  Standard Mode:          7.5ms.
 *                  High Resolution Mode:   13.5ms.
 *                  Ultra High Res. Mode:   25.5ms.
 */
BMP085_status_t  BMP085_TriggerPressure  ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, BMP085_pressure_osrs_t myResolution )
{
    uint8_t     cmd[]             =   { BMP085_CONTROL, BMP085_TRIGGER_PRESSURE };
    uint32_t    aux               =    0;

    // adjust the pressure resolution
    cmd[1]   |=   ( myResolution << 6 );


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 2, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   BMP085_SUCCESS;
    else
       return   BMP085_FAILURE;
}


/**
 * @brief       BMP085_ReadRawPressure   ( NRF_TWI_Type* , BMP085_address_t , Vector_pressure_f* )
 *
 * @details     It reads an uncompensated temperature.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 *
 * @param[out]   myRawPressure:         Uncompensated temperature.
 *
 *
 * @return       Status of BMP085_ReadRawPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017   The ORIGIN
 * @pre         BMP085_TriggerPressure function MUST be called before calling this one.
 * @warning     The user MUST respect the maximum pressure conversion time:
 *                  Ultra Low Power Mode:   4.5ms.
 *                  Standard Mode:          7.5ms.
 *                  High Resolution Mode:   13.5ms.
 *                  Ultra High Res. Mode:   25.5ms.
 */
BMP085_status_t  BMP085_ReadRawPressure ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_pressure_f* myRawPressure )
{
    uint8_t     cmd[]             =   { BMP085_READ_PRESSURE, 0, 0 };
    uint32_t    aux               =    0;


    aux = i2c_write ( myinstance, ADDR, &cmd[0], 1, I2C_STOP_BIT );
    aux = i2c_read  ( myinstance, ADDR, &cmd[0], 3 );


    // Parse the data
    myRawPressure->Pressure    =   ( cmd[0] << 16 ) | ( cmd[1] << 8 ) | cmd[2];



    if ( aux == I2C_SUCCESS )
       return   BMP085_SUCCESS;
    else
       return   BMP085_FAILURE;
}
