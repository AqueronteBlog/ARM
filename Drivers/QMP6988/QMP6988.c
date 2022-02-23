/**
 * @brief       QMP6988.h
 * @details     Digital Barometric Pressure Sensor.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/February/2022
 * @version     12/February/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "QMP6988.h"


 /**
 * @brief       QMP6988_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of QMP6988_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2022
 * @version     03/February/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetRawCompensationCoefficients ( I2C_parameters_t , QMP6988_raw_compensation_coefficients_t* )
 * @details     It gets the raw compensation coefficients.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawK:			Raw compensation coefficients.
 *
 *
 * @return      Status of QMP6988_GetRawCompensationCoefficients
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetRawCompensationCoefficients ( I2C_parameters_t myI2Cparameters, QMP6988_raw_compensation_coefficients_t* myRawK )
{
    uint8_t      cmd[25]	=	{ 0 };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_COE_B00_1;
    aux 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux 	|=   i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    myRawK->raw_b00		=	cmd[0];
    myRawK->raw_b00	  <<=	8U;
    myRawK->raw_b00	   |=	cmd[1];
    myRawK->raw_b00	  <<=	4U;
    myRawK->raw_b00	   |=	( ( cmd[24] & 0xF0 ) >> 4U );

    myRawK->raw_bt1		=	cmd[2];
    myRawK->raw_bt1	  <<=	8U;
    myRawK->raw_bt1	   |=	cmd[3];

    myRawK->raw_bt2		=	cmd[4];
    myRawK->raw_bt2	  <<=	8U;
    myRawK->raw_bt2	   |=	cmd[5];

    myRawK->raw_bp1		=	cmd[6];
    myRawK->raw_bp1	  <<=	8U;
    myRawK->raw_bp1	   |=	cmd[7];

    myRawK->raw_b11		=	cmd[8];
    myRawK->raw_b11	  <<=	8U;
    myRawK->raw_b11	   |=	cmd[9];

    myRawK->raw_bp2		=	cmd[10];
    myRawK->raw_bp2	  <<=	8U;
    myRawK->raw_bp2	   |=	cmd[11];

    myRawK->raw_b12		=	cmd[12];
    myRawK->raw_b12	  <<=	8U;
    myRawK->raw_b12	   |=	cmd[13];

    myRawK->raw_b21		=	cmd[14];
    myRawK->raw_b21	  <<=	8U;
    myRawK->raw_b21	   |=	cmd[15];

    myRawK->raw_bp3		=	cmd[16];
    myRawK->raw_bp3	  <<=	8U;
    myRawK->raw_bp3	   |=	cmd[17];

    myRawK->raw_a0		=	cmd[18];
    myRawK->raw_a0	  <<=	8U;
    myRawK->raw_a0	   |=	cmd[19];
    myRawK->raw_a0	  <<=	4U;
    myRawK->raw_a0	   |=	( cmd[24] & 0x0F );

    myRawK->raw_a1		=	cmd[20];
    myRawK->raw_a1	  <<=	8U;
    myRawK->raw_a1	   |=	cmd[21];

    myRawK->raw_a2		=	cmd[22];
    myRawK->raw_a2	  <<=	8U;
    myRawK->raw_a2	   |=	cmd[23];



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetChipID ( I2C_parameters_t , uint8_t* )
 * @details     It gets the chip ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myChipID:			Chip ID.
 *
 *
 * @return      Status of QMP6988_GetChipID
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetChipID ( I2C_parameters_t myI2Cparameters, uint8_t* myChipID )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_CHIP_ID;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux |=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myChipID = cmd;



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SoftReset ( I2C_parameters_t )
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SoftReset
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     The user must wait for at least 100us (Trst) after using this function.
 */
QMP6988_status_t  QMP6988_SoftReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_RESET;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetIIR_Filter ( I2C_parameters_t , QMP6988_iir_filter_t )
 * @details     It sets the IIR filter co-efficient.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]	 myFilter:			IIR filter
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetIIR_Filter
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetIIR_Filter ( I2C_parameters_t myI2Cparameters, QMP6988_iir_filter_t myFilter )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Write the register	*/
    cmd[0]	 =	 QMP6988_IIR_CNT;
    cmd[1]	 =	 myFilter;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetIIR_Filter ( I2C_parameters_t , QMP6988_iir_filter_t* )
 * @details     It gets the IIR filter co-efficient.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myFilter:			IIR filter.
 *
 *
 * @return      Status of QMP6988_GetIIR_Filter
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetIIR_Filter ( I2C_parameters_t myI2Cparameters, QMP6988_iir_filter_t* myFilter )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_IIR_CNT;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myFilter = (QMP6988_iir_filter_t)cmd;



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetMasterCodeI2C ( I2C_parameters_t , QMP6988_i2c_set_master_code_t )
 * @details     It sets the master code setting at I2C HS mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]	 myMasterCode:		Master code setting at I2C HS mode
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetMasterCodeI2C
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetMasterCodeI2C ( I2C_parameters_t myI2Cparameters, QMP6988_i2c_set_master_code_t myMasterCode )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Write the register	*/
    cmd[0]	 =	 QMP6988_I2C_SET;
    cmd[1]	 =	 myMasterCode;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetMasterCodeI2C ( I2C_parameters_t , QMP6988_i2c_set_master_code_t* )
 * @details     It gets the master code setting at I2C HS mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myMasterCode:		Master code setting at I2C HS mode.
 *
 *
 * @return      Status of QMP6988_GetMasterCodeI2C
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetMasterCodeI2C ( I2C_parameters_t myI2Cparameters, QMP6988_i2c_set_master_code_t* myMasterCode )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_I2C_SET;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myMasterCode = (QMP6988_i2c_set_master_code_t)cmd;



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetDeviceStat ( I2C_parameters_t , uint8_t* )
 * @details     It gets the device stat.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDeviceStat:		Device stat: Measure and OTP update.
 *
 *
 * @return      Status of QMP6988_GetDeviceStat
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetDeviceStat ( I2C_parameters_t myI2Cparameters, uint8_t* myDeviceStat )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_DEVICE_STAT;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myDeviceStat = cmd;



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetPowerMode ( I2C_parameters_t , QMP6988_ctrl_meas_power_mode_t )
 * @details     It sets the power mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPowerMode:   	Power mode setting.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetPowerMode
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetPowerMode ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_power_mode_t myPowerMode )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
     cmd[0]	 =	 QMP6988_CTRL_MEAS;
     aux	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
     aux	|=   i2c_read ( myI2Cparameters, &cmd[1], 1U );

    /* Update the register	*/
    cmd[0]	 =	 QMP6988_CTRL_MEAS;
    cmd[1]	&=	 ~CTRL_MEAS_POWER_MODE_MASK;
    cmd[1]	|=	 myPowerMode;
    aux	 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetPowerMode ( I2C_parameters_t , QMP6988_ctrl_meas_power_mode_t* )
 * @details     It gets the power mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPowerMode:   	Power mode setting.
 *
 *
 * @return      Status of QMP6988_GetPowerMode
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetPowerMode ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_power_mode_t* myPowerMode )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_CTRL_MEAS;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myPowerMode	 =	(QMP6988_ctrl_meas_power_mode_t)( cmd & CTRL_MEAS_POWER_MODE_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetTemperatureAverage ( I2C_parameters_t , QMP6988_ctrl_meas_temp_average_t )
 * @details     It sets the temperature averaging time.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTempAvrg:   		Temperature averaging time.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetTemperatureAverage
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetTemperatureAverage ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_temp_average_t myTempAvrg )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_CTRL_MEAS;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux	 	|=   i2c_read ( myI2Cparameters, &cmd[1], 1U );

    /* Update the register	*/
    cmd[0]	 =	 QMP6988_CTRL_MEAS;
    cmd[1]	&=	 ~CTRL_MEAS_TEMP_AVERAGE_MASK;
    cmd[1]	|=	 myTempAvrg;
    aux	 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetTemperatureAverage ( I2C_parameters_t , QMP6988_ctrl_meas_temp_average_t* )
 * @details     It gets the temperature averaging time.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTempAvrg:   		Temperature averaging time.
 *
 *
 * @return      Status of QMP6988_GetTemperatureAverage
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetTemperatureAverage ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_temp_average_t* myTempAvrg )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_CTRL_MEAS;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myTempAvrg	 =	(QMP6988_ctrl_meas_temp_average_t)( cmd & CTRL_MEAS_TEMP_AVERAGE_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetPressureAverage ( I2C_parameters_t , QMP6988_ctrl_meas_press_average_t )
 * @details     It sets the pressure averaging time.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPressAvrg:   	Pressure averaging time.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetPressureAverage
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetPressureAverage ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_press_average_t myPressAvrg )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_CTRL_MEAS;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux	 	|=   i2c_read ( myI2Cparameters, &cmd[1], 1U );

    /* Update the register	*/
    cmd[0]	 =	 QMP6988_CTRL_MEAS;
    cmd[1]	&=	 ~CTRL_MEAS_PRESS_AVERAGE_MASK;
    cmd[1]	|=	 myPressAvrg;
    aux	 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetPressureAverage ( I2C_parameters_t , QMP6988_ctrl_meas_press_average_t* )
 * @details     It gets the pressure averaging time.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPressAvrg:   	Pressure averaging time.
 *
 *
 * @return      Status of QMP6988_GetPressureAverage
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetPressureAverage ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_press_average_t* myPressAvrg )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_CTRL_MEAS;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myPressAvrg	 =	(QMP6988_ctrl_meas_press_average_t)( cmd & CTRL_MEAS_PRESS_AVERAGE_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetStandbyTimeSetting ( I2C_parameters_t , QMP6988_io_setup_t_standby_t )
 * @details     It sets the standby time setting.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myStandbyTime:   	Standby time setting.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetStandbyTimeSetting
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetStandbyTimeSetting ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_t_standby_t myStandbyTime )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_IO_SETUP;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux	 	|=   i2c_read ( myI2Cparameters, &cmd[1], 1U );

    /* Update the register	*/
    cmd[0]	 =	 QMP6988_IO_SETUP;
    cmd[1]	&=	 ~IO_SETUP_T_STANDBY_MASK;
    cmd[1]	|=	 myStandbyTime;
    aux	 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetStandbyTimeSetting ( I2C_parameters_t , QMP6988_io_setup_t_standby_t* )
 * @details     It gets the standby time setting.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStandbyTime:   	Standby time setting.
 *
 *
 * @return      Status of QMP6988_GetStandbyTimeSetting
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetStandbyTimeSetting ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_t_standby_t* myStandbyTime )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_IO_SETUP;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *myStandbyTime	 =	(QMP6988_io_setup_t_standby_t)( cmd & IO_SETUP_T_STANDBY_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetSPI_ModeSetting ( I2C_parameters_t , QMP6988_io_setup_spi3w_t )
 * @details     It sets the SPI mode setting (4 or 3 wire).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySPI:   			the SPI mode setting (4 or 3 wire).
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetSPI_ModeSetting
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetSPI_ModeSetting ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3w_t mySPI )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_IO_SETUP;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux	 	|=   i2c_read ( myI2Cparameters, &cmd[1], 1U );

    /* Update the register	*/
    cmd[0]	 =	 QMP6988_IO_SETUP;
    cmd[1]	&=	 ~IO_SETUP_SPI3W_MASK;
    cmd[1]	|=	 mySPI;
    aux	 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetSPI_ModeSetting ( I2C_parameters_t , QMP6988_io_setup_spi3w_t* )
 * @details     It gets the SPI mode setting (4 or 3 wire).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySPI:   			SPI mode setting (4 or 3 wire).
 *
 *
 * @return      Status of QMP6988_GetSPI_ModeSetting
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetSPI_ModeSetting ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3w_t* mySPI )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_IO_SETUP;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *mySPI	 =	(QMP6988_io_setup_spi3w_t)( cmd & IO_SETUP_SPI3W_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_SetSDI_Output ( I2C_parameters_t , QMP6988_io_setup_spi3_sdim_t )
 * @details     It sets the selected output type of SDI terminal.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySDI:   			Output type of SDI terminal.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of QMP6988_SetSDI_Output
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_SetSDI_Output ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3_sdim_t mySDI )
{
    uint8_t      cmd[2]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_IO_SETUP;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux	 	|=   i2c_read ( myI2Cparameters, &cmd[1], 1U );

    /* Update the register	*/
    cmd[0]	 =	 QMP6988_IO_SETUP;
    cmd[1]	&=	 ~IO_SETUP_SPI3_SDIM_MASK;
    cmd[1]	|=	 mySDI;
    aux	 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetSDI_Output ( I2C_parameters_t , QMP6988_io_setup_spi3_sdim_t* )
 * @details     It gets the selected output type of SDI terminal.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySDI:   			Output type of SDI terminal.
 *
 *
 * @return      Status of QMP6988_GetSDI_Output
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetSDI_Output ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3_sdim_t* mySDI )
{
    uint8_t      cmd	=	0U;
    i2c_status_t aux;


    /* Read the register	*/
    cmd	 =	 QMP6988_IO_SETUP;
    aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux	|=   i2c_read ( myI2Cparameters, &cmd, 1U );

    /* Parse the data	 */
    *mySDI	 =	(QMP6988_io_setup_spi3_sdim_t)( cmd & IO_SETUP_SPI3_SDIM_MASK );



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_GetRawMeasurements ( I2C_parameters_t , QMP6988_raw_measured_data_t* )
 * @details     It gets the raw temperature and pressure data.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myData:   			Raw pressure data and raw temperature data.
 *
 *
 * @return      Status of QMP6988_GetRawMeasurements
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
QMP6988_status_t  QMP6988_GetRawMeasurements ( I2C_parameters_t myI2Cparameters, QMP6988_raw_measured_data_t* myData )
{
    uint8_t      cmd[6]	=	{ 0U };
    i2c_status_t aux;


    /* Read the register	*/
    cmd[0]	 =	 QMP6988_PRESS_TXD2;
    aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux		|=   i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    myData->dp	  =	cmd[0];
    myData->dp	<<=	8U;
    myData->dp	 |=	cmd[1];
    myData->dp	<<=	8U;
    myData->dp	 |=	cmd[2];

    myData->dt	  =	cmd[3];
    myData->dt	<<=	8U;
    myData->dt	 |=	cmd[4];
    myData->dt	<<=	8U;
    myData->dt	 |=	cmd[5];


    //myData->dp	-=	8388608;
    //myData->dt	-=	8388608;



    if ( aux == I2C_SUCCESS )
    {
        return   QMP6988_SUCCESS;
    }
    else
    {
        return   QMP6988_FAILURE;
    }
}



/**
 * @brief       QMP6988_CalculateK ( float , float , uint16_t )
 * @details     It calculates the conversion factor. K = A + ( S * OTP ) / 32767.
 *
 * @param[in]    a:   	Conversion factor A.
 * @param[in]    s:   	Conversion factor S.
 * @param[in]    otp:   Raw Compensation Coefficient.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Compensation coefficients.
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
float  QMP6988_CalculateK ( float a, float s, uint16_t otp )
{
	return ( a + ( s * otp ) / 32767.0 );
}



/**
 * @brief       QMP6988_CalculateK0 ( uint32_t )
 * @details     It calculates the conversion factor. K = OTP / 16.
 *
 * @param[in]    otp:   Raw Compensation Coefficient.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Compensation coefficients.
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
float  QMP6988_CalculateK0 ( uint32_t otp )
{
	return ( otp / 16.0 );
}



/**
 * @brief       QMP6988_CalculateCompensationCoefficients ( QMP6988_raw_compensation_coefficients_t )
 * @details     It calculates the compensation coefficients.
 *
 * @param[in]    myRawK:   	Raw compensation coefficients.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Compensation coefficients.
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         Due to in the datasheet is not clear how to calculate the compensated values, those have been taken from the origin repo:
 * 				https://github.com/m5stack/UNIT_ENV/tree/master/src.
 * @warning     N/A.
 */
QMP6988_compensation_coefficients_t  QMP6988_CalculateCompensationCoefficients	( QMP6988_raw_compensation_coefficients_t myRawK )
{
	QMP6988_compensation_coefficients_t	auxK;

	auxK.a1		= 3608L * (int32_t)myRawK.raw_a1 - 1731677965L;
	auxK.a2		= 16889L * (int32_t)myRawK.raw_a2 - 87619360L;
	auxK.bt1	= 2982L * (int64_t)myRawK.raw_bt1 + 107370906L;
	auxK.bt2	= 329854L * (int64_t)myRawK.raw_bt2 + 108083093L;
	auxK.bp1	= 19923L * (int64_t)myRawK.raw_bp1 + 1133836764L;
	auxK.b11	= 2406L * (int64_t)myRawK.raw_b11 + 118215883L;
	auxK.bp2	= 3079L * (int64_t)myRawK.raw_bp2 - 181579595L;
	auxK.b12	= 6846L * (int64_t)myRawK.raw_b12 + 85590281L;
	auxK.b21	= 6846L * (int64_t)myRawK.raw_b21 + 85590281L;
	auxK.bp3	= 2915L * (int64_t)myRawK.raw_bp3 + 157155561L;

	auxK.a0		= myRawK.raw_a0;
	auxK.b00	= myRawK.raw_b00;


    return auxK;
}



/**
 * @brief       QMP6988_CalculateCompensatedMeasuredData ( QMP6988_raw_measured_data_t , QMP6988_compensation_coefficients_t )
 * @details     It calculates the compensated values: temperature and pressure.
 *
 * @param[in]    myData:   	Raw measured data: Temperature and Pressure.
 * @param[in]    myK:   	Raw compensation coefficients.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Compensated Temperature and Pressure values.
 *
 * @author      Manuel Caballero
 * @date        18/February/2022
 * @version     18/February/2022        The ORIGIN
 * @pre         Due to in the datasheet is not clear how to calculate the compensated values, those have been taken from the origin repo:
 * 				https://github.com/m5stack/UNIT_ENV/tree/master/src
 * @warning     N/A.
 */
QMP6988_compensated_measured_data_t	QMP6988_CalculateCompensatedMeasuredData ( QMP6988_raw_measured_data_t myData, QMP6988_compensation_coefficients_t myK )
{
	QMP6988_compensated_measured_data_t	auxData;
	int32_t  auxT, auxP;
	int64_t  wk1, wk2, wk3;
	int16_t  t_int;
	uint32_t p_int;


	/* Aux data	 */
	auxT	=	(int32_t)( myData.dt - 8388608 );
	auxP	=	(int32_t)( myData.dp - 8388608 );

	/* Calculate the compensated temperature	 */
	wk1 	= 	((int64_t)myK.a1 * (int64_t)auxT); 			// 31Q23+24-1=54 (54Q23)
	wk2 	= 	((int64_t)myK.a2 * (int64_t)auxT) >> 14; 	// 30Q47+24-1=53 (39Q33)
	wk2 	= 	(wk2 * (int64_t)auxT) >> 10; 				// 39Q33+24-1=62 (52Q23)
	wk2 	= 	((wk1 + wk2) / 32767) >> 19; 				// 54,52->55Q23 (20Q04)
	t_int 	= 	(int16_t)((myK.a0 + wk2) >> 4); 			// 21Q4 -> 17Q0

	auxData.temperature	=	(float)t_int / 256.0;

	/* Calculate the compensated pressure	 */
	wk1 	= 	((int64_t)myK.bt1 * (int64_t)t_int); 		// 28Q15+16-1=43 (43Q15)
	wk2 	= 	((int64_t)myK.bp1 * (int64_t)auxP) >> 5; 	// 31Q20+24-1=54 (49Q15)
	wk1    += 	wk2; 										// 43,49->50Q15
	wk2 	= 	((int64_t)myK.bt2 * (int64_t)t_int) >> 1; 	// 34Q38+16-1=49 (48Q37)
	wk2 	= 	(wk2 * (int64_t)t_int) >> 8; 				// 48Q37+16-1=63 (55Q29)
	wk3 	= 	wk2; 										// 55Q29
	wk2 	= 	((int64_t)myK.b11 * (int64_t)t_int) >> 4; 	// 28Q34+16-1=43 (39Q30)
	wk2 	= 	(wk2 * (int64_t)auxP) >> 1; 				// 39Q30+24-1=62 (61Q29)
	wk3    += 	wk2; 										// 55,61->62Q29
	wk2 	= 	((int64_t)myK.bp2 * (int64_t)auxP) >> 13; 	// 29Q43+24-1=52 (39Q30)
	wk2 	= 	(wk2 * (int64_t)auxP) >> 1; 				// 39Q30+24-1=62 (61Q29)
	wk3    += 	wk2; 										// 62,61->63Q29
	wk1    +=	wk3 >> 14; 									// Q29 >> 14 -> Q15
	wk2 	= 	((int64_t)myK.b12 * (int64_t)t_int); 		// 29Q53+16-1=45 (45Q53)
	wk2 	= 	(wk2 * (int64_t)t_int) >> 22; 				// 45Q53+16-1=61 (39Q31)
	wk2 	= 	(wk2 * (int64_t)auxP) >> 1; 				// 39Q31+24-1=62 (61Q30)
	wk3 	= 	wk2; 										// 61Q30
	wk2 	= 	((int64_t)myK.b21 * (int64_t)t_int) >> 6; 	// 29Q60+16-1=45 (39Q54)
	wk2 	= 	(wk2 * (int64_t)auxP) >> 23; 				// 39Q54+24-1=62 (39Q31)
	wk2 	= 	(wk2 * (int64_t)auxP) >> 1; 				// 39Q31+24-1=62 (61Q20)
	wk3    += 	wk2; 										// 61,61->62Q30
	wk2 	= 	((int64_t)myK.bp3 * (int64_t)auxP) >> 12; 	// 28Q65+24-1=51 (39Q53)
	wk2 	= 	(wk2 * (int64_t)auxP) >> 23; 				// 39Q53+24-1=62 (39Q30)
	wk2 	= 	(wk2 * (int64_t)auxP);	 					// 39Q30+24-1=62 (62Q30)
	wk3    += 	wk2; 										// 62,62->63Q30
	wk1    += 	wk3 >> 15; 									// Q30 >> 15 = Q15
	wk1    /= 	32767L;
	wk1   >>= 11; 											// Q15 >> 7 = Q4
	wk1    += myK.b00; 										// Q4 + 20Q4
	//wk1 >>= 4;
	p_int = (int32_t)wk1;

	auxData.pressure	=	(float)p_int / 16.0;

    return auxData;
}
