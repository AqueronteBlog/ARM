/**
 * @brief       BMP180.c
 * @details     Digital Pressure Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

 #include "BMP180.h"


 /**
 * @brief       BMP180_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMP180_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BMP180_status_t  BMP180_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



/**
 * @brief       BMP180_GetID    ( I2C_parameters_t , BMP180_data_t* )
 * @details     It gets the chip-ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myID:   Chip-ID
 *
 *
 * @return      Status of BMP180_GetID.
 *
 * @author      Manuel Caballero
 * @date        8/September/2018
 * @version     8/September/2018    The ORIGIN
 * @pre         It must be 0x55.
 * @warning     N/A.
 */
BMP180_status_t  BMP180_GetID ( I2C_parameters_t myI2Cparameters, BMP180_data_t* myID )
{
    uint8_t      cmd   =    0U;
    i2c_status_t aux;


    /* Get ID    */
    cmd  =   BMP180_ID;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &myID->id, 1U );




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



 /**
 * @brief       BMP180_SoftReset   ( I2C_parameters_t )
 * @details     It performs a soft reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of BMP180_SoftReset.
 *
 * @author      Manuel Caballero
 * @date        8/September/2018
 * @version     8/September/2018        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BMP180_status_t  BMP180_SoftReset   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd[]   =   { 0, 0 };
    i2c_status_t aux;


    cmd[0]   =   BMP180_SOFT_RESET;
    cmd[1]   =   SOFT_SOFT_RESET;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}


 /**
 * @brief       BMP180_Get_Cal_Param   ( I2C_parameters_t , BMP180_calibration_data_t* )
 * @details     It reads the calibration data.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCalibrationData: Calibration data from the sensor.
 *
 *
 * @return      Status of BMP180_Get_Cal_Param.
 *
 * @author      Manuel Caballero
 * @date        9/September/2018
 * @version     9/September/2018        The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
BMP180_status_t  BMP180_Get_Cal_Param ( I2C_parameters_t myI2Cparameters, BMP180_calibration_data_t* myCalibrationData )
{
    uint8_t      cmd[22]    =    { 0U };
    uint8_t      myI2C_stop =    I2C_STOP_BIT;

    i2c_status_t aux;


    /* Read out all calibration data from the sensor ( auto-increment )    */
    cmd[0]   =   BMP180_AC1_MSB;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    /* Parse the data  */
    myCalibrationData->ac1    =   cmd[0];
    myCalibrationData->ac1  <<=   8U;
    myCalibrationData->ac1   |=   cmd[1];

    myCalibrationData->ac2    =   cmd[2];
    myCalibrationData->ac2  <<=   8U;
    myCalibrationData->ac2   |=   cmd[3];

    myCalibrationData->ac3    =   cmd[4];
    myCalibrationData->ac3  <<=   8U;
    myCalibrationData->ac3   |=   cmd[5];

    myCalibrationData->ac4    =   cmd[6];
    myCalibrationData->ac4  <<=   8U;
    myCalibrationData->ac4   |=   cmd[7];

    myCalibrationData->ac5    =   cmd[8];
    myCalibrationData->ac5  <<=   8U;
    myCalibrationData->ac5   |=   cmd[9];

    myCalibrationData->ac6    =   cmd[10];
    myCalibrationData->ac6  <<=   8U;
    myCalibrationData->ac6   |=   cmd[11];

    myCalibrationData->b1     =   cmd[12];
    myCalibrationData->b1   <<=   8U;
    myCalibrationData->b1    |=   cmd[13];

    myCalibrationData->b2     =   cmd[14];
    myCalibrationData->b2   <<=   8U;
    myCalibrationData->b2    |=   cmd[15];

    myCalibrationData->mb     =   cmd[16];
    myCalibrationData->mb   <<=   8U;
    myCalibrationData->mb    |=   cmd[17];

    myCalibrationData->mc     =   cmd[18];
    myCalibrationData->mc   <<=   8U;
    myCalibrationData->mc    |=   cmd[19];

    myCalibrationData->md     =   cmd[20];
    myCalibrationData->md   <<=   8U;
    myCalibrationData->md    |=   cmd[21];





    if ( aux == I2C_SUCCESS )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}



/**
 * @brief       BMP180_Get_UT   ( I2C_parameters_t , BMP180_uncompensated_data_t* )
 * @details     It reads uncompensated temperature value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myUT:              Uncompensated temperature value.
 *
 *
 * @return      Status of BMP180_Get_UT.
 *
 * @author      Manuel Caballero
 * @date        9/September/2018
 * @version     9/September/2018        The ORIGIN
 * @pre         This function checks the bit SCO until the conversion is complete instead of
 *              4.5ms.
 * @warning     N/A
 */
BMP180_status_t  BMP180_Get_UT ( I2C_parameters_t myI2Cparameters, BMP180_uncompensated_data_t* myUT )
{
    uint8_t      cmd[]      =    { 0U, 0U };
    uint8_t      myI2C_stop =    I2C_STOP_BIT;
    uint32_t     myTimeout  =    0U;
    i2c_status_t aux;


    /* Read out the uncompensated temperature data    */
    cmd[0]   =   BMP180_CTRL_MEAS;
    cmd[1]   =   BMP180_TRIGGER_TEMPERATURE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    /* Wait until conversion is complete or timeout  */
    myTimeout    =   0x232323;
    do{
        cmd[0]   =   BMP180_CTRL_MEAS;
        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
        aux      =   i2c_read  ( myI2Cparameters, &cmd[0], 1U );
        myTimeout--;
    }while ( ( ( cmd[0] & CTRL_MEAS_SCO_MASK ) == CTRL_MEAS_SCO_CONVERSION_IN_PROGRESS ) && ( myTimeout > 0U ) );


    /* Parse the data only if not timeout    */
    if ( myTimeout > 0U )
    {
        cmd[0]   =   BMP180_OUT_MSB;
        aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
        aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

        /* Parse the data  */
        myUT->ut    =   cmd[0];
        myUT->ut  <<=   8U;
        myUT->ut   |=   cmd[1];
    }





    if ( ( aux == I2C_SUCCESS ) && ( myTimeout > 0U ) )
    {
        return   BMP180_SUCCESS;
    }
    else
    {
        return   BMP180_FAILURE;
    }
}
