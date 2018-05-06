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
 * @brief       MC3635_SetStandbyMode  ( I2C_parameters_t )
 *
 * @details     It puts the device into the STANDBY mode.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetStandbyMode.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        27/April/2018
 * @version     27/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MC3635_status_t  MC3635_SetStandbyMode ( I2C_parameters_t myI2Cparameters )
{
    uint8_t         cmd[] =   { MODE_C, 0 };
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );


    /* Update the register data */
    cmd[1] &=  ~MODE_C_MCTRL_MASK;
    cmd[1] |=   MODE_C_MCTRL_STANDBY;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetSleepMode  ( I2C_parameters_t )
 *
 * @details     It puts the device into the SLEEP mode.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetSleepMode.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        27/April/2018
 * @version     27/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MC3635_status_t  MC3635_SetSleepMode ( I2C_parameters_t myI2Cparameters )
{
    uint8_t         cmd[] =   { MODE_C, 0 };
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );


    /* Update the register data */
    cmd[1] &=  ~MODE_C_MCTRL_MASK;
    cmd[1] |=   MODE_C_MCTRL_SLEEP;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}


/**
 * @brief       MC3635_InitializationSequence  ( I2C_parameters_t )
 *
 * @details     It starts an initialization sequence ( recommended sequence ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_InitializationSequence.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         Data sheet APS-048-0044v1.5 p.22
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_InitializationSequence ( I2C_parameters_t myI2Cparameters )
{
    uint8_t         cmd[]    =   { 0, 0 };
    i2c_status_t    aux      =   0;


    /* Feature 1: Specify Interface */
    cmd[0]   =   FREG_1;
    cmd[1]   =   FREG_1_I2C_EN_ENABLED;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    /* Initialization Register 1 */
    cmd[0]   =   INIT_1;
    cmd[1]   =   INIT_1_INIT_1_FIXED_VALUE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    /* Drive Motion X */
    cmd[0]   =   DMX;
    cmd[1]   =   0x01;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    /* Drive Motion Y */
    cmd[0]   =   DMY;
    cmd[1]   =   0x80;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    /* Initialization Register 2 */
    cmd[0]   =   INIT_2;
    cmd[1]   =   INIT_2_INT_2_FIXED_VALUE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    /* Initialization Register 3 */
    cmd[0]   =   INIT_3;
    cmd[1]   =   INIT_3_INT_3_FIXED_VALUE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}


/**
 * @brief       MC3635_WriteScratchpadRegister  ( I2C_parameters_t , MC3635_data_t )
 *
 * @details     This register can store any 8-bit value and has no effect on hardware.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myScratchpadRegister:  Data to be written.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_WriteScratchpadRegister.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_WriteScratchpadRegister ( I2C_parameters_t myI2Cparameters, MC3635_data_t myScratchpadRegister )
{
    uint8_t         cmd[]    =   { 0, 0 };
    i2c_status_t    aux      =   0;


    /* Write the data */
    cmd[0]   =   SCRATCH;
    cmd[1]   =   myScratchpadRegister.scratch;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadScratchpadRegister  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads the scratch pad register.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myScratchpadRegister:  Data into SCRATCH register.
 *
 *
 * @return       Status of MC3635_ReadScratchpadRegister.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadScratchpadRegister ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myScratchpadRegister )
{
    uint8_t         cmd     =   SCRATCH;
    i2c_status_t    aux     =   0;

    /* Get the data */
    aux     =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &myScratchpadRegister->scratch, 1 );



    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetSoftwareReset  ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetSoftwareReset.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     Immediately after a RESET or power-up event, several registers must be written with initialization values,
 *              MC3635_InitializationSequence MUST be called.
 * @warning     It takes reset to be completed at least 1ms, the user MUST take care of this delay.
 */
MC3635_status_t  MC3635_SetSoftwareReset ( I2C_parameters_t myI2Cparameters )
{
    uint8_t         cmd[]   =   { RESET , 0 };
    i2c_status_t    aux     =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] |=   RESET_RESET_FORCE_POWER_ON_RESET;

    /* Write into the register */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );



    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetReload  ( I2C_parameters_t )
 *
 * @details     It performs a reload.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetReload.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         This bit must be cleared by software.
 * @warning     It takes reset to be completed at least 1ms, the user MUST take care of this delay.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_SetReload ( I2C_parameters_t myI2Cparameters )
{
    uint8_t         cmd[]        =   { RESET , 0 };
    uint32_t        myTimeOut    =   23232323;
    i2c_status_t    aux          =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] |=   RESET_RELOAD_RELOAD_REGISTER_FROM_OTP;


    /* Write into the register */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );


    /* Wait until the action was DONE */
    cmd[0]   =   EXT_STAT_2;
    do{
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
        aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );
        myTimeOut--;
    }while ( ( ( cmd[1] & EXT_STAT_2_OTP_BUSY_MASK ) == EXT_STAT_2_OTP_BUSY_OTP_POWERED ) && ( myTimeOut > 0 ) );


    /* Clear the flag   */
    cmd[0]  =   RESET;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] &=  ~RESET_RELOAD_MASK;
    cmd[1] |=   RESET_RELOAD_NORMAL_OPERATION;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( ( aux == I2C_SUCCESS ) && ( myTimeOut > 0 ) )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadExtendedStatusRegister2  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads the Extended Status Register 2.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myExt_stat_2:          The data of the register.
 *
 *
 * @return       Status of MC3635_ReadExtendedStatusRegister2.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadExtendedStatusRegister2 ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myExt_stat_2 )
{
    uint8_t         cmd   =   EXT_STAT_2;
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &myExt_stat_2->ext_stat_2, 1 );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadRawData  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads X, Y and Z raw data output.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myRawData:             Raw data for X, Y and Z axis.
 *
 *
 * @return       Status of MC3635_ReadRawData.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     1/May/2018        The device provides data in 'mg' already.
 *              26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadRawData ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myRawData )
{
    uint8_t         cmd[] =   { XOUT_LSB, 0, 0, 0, 0, 0 };
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data */
    myRawData->XAxis_mg    =  cmd[1];
    myRawData->XAxis_mg  <<=  8;
    myRawData->XAxis_mg   |=  cmd[0];

    myRawData->YAxis_mg    =  cmd[3];
    myRawData->YAxis_mg  <<=  8;
    myRawData->YAxis_mg   |=  cmd[2];

    myRawData->ZAxis_mg    =  cmd[5];
    myRawData->ZAxis_mg  <<=  8;
    myRawData->ZAxis_mg   |=  cmd[4];




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadStatusRegister1  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads the Status Register 1.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myStatus_1:            The data of the register.
 *
 *
 * @return       Status of MC3635_ReadStatusRegister1.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadStatusRegister1 ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myStatus_1 )
{
    uint8_t         cmd   =   STATUS_1;
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &myStatus_1->status_1, 1 );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadStatusRegister2  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads the Status Register 2.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myStatus_2:            The data of the register.
 *
 *
 * @return       Status of MC3635_ReadStatusRegister2.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadStatusRegister2 ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myStatus_2 )
{
    uint8_t         cmd   =   STATUS_2;
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &myStatus_2->status_2, 1 );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadFeatureRegister1  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads the Feature Register 1.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myFeatureRegister1:    The data of the register.
 *
 *
 * @return       Status of MC3635_ReadFeatureRegister1.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadFeatureRegister1 ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myFeatureRegister1 )
{
    uint8_t         cmd   =   FREG_1;
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &myFeatureRegister1->FeatureRegister1, 1 );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ReadFeatureRegister2  ( I2C_parameters_t , MC3635_data_t* )
 *
 * @details     It reads the Feature Register 2.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   myFeatureRegister2:    The data of the register.
 *
 *
 * @return       Status of MC3635_ReadFeatureRegister2.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MC3635_status_t  MC3635_ReadFeatureRegister2 ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myFeatureRegister2 )
{
    uint8_t         cmd   =   FREG_2;
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &myFeatureRegister2->FeatureRegister2, 1 );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_EnableAxis  ( I2C_parameters_t , MC3635_mode_c_mctrl_t , MC3635_mode_c_x_axis_pd_t , MC3635_mode_c_y_axis_pd_t , MC3635_mode_c_z_axis_pd_t )
 *
 * @details     It enables/disables X/Y/Z Axis.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myXAxis:           Enabled/Disabled.
 * @param[in]    myYAxis:           Enabled/Disabled.
 * @param[in]    myZAxis:           Enabled/Disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_EnableAxis.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     27/April/2018     The function was renamed and totally modified.
 *              26/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_EnableAxis ( I2C_parameters_t myI2Cparameters, MC3635_mode_c_x_axis_pd_t myXAxis, MC3635_mode_c_y_axis_pd_t myYAxis, MC3635_mode_c_z_axis_pd_t myZAxis )
{
    uint8_t         cmd[] =   { MODE_C, 0 };
    i2c_status_t    aux   =   0;


    /* Update the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] &=  ~( MODE_C_X_AXIS_PD_MASK | MODE_C_Y_AXIS_PD_MASK | MODE_C_Z_AXIS_PD_MASK );
    cmd[1] |=   ( myXAxis | myYAxis | myZAxis );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetStandbyClockRate  ( I2C_parameters_t , MC3635_sniff_c_stb_rate_t )
 *
 * @details     It sets the clock rate for STANDBY mode.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    mySTANDBY_ClockRate:   Wake Power Mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetStandbyClockRate.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        27/April/2018
 * @version     27/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_SetStandbyClockRate ( I2C_parameters_t myI2Cparameters, MC3635_sniff_c_stb_rate_t mySTANDBY_ClockRate )
{
    uint8_t         cmd[] =   { SNIFF_C, 0 };
    i2c_status_t    aux   =   0;


    /* Get the register data */
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );


    /* Update the register data */
    cmd[1] &=  ~SNIFF_C_STB_RATE_MASK;
    cmd[1] |=   mySTANDBY_ClockRate;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetMode  ( I2C_parameters_t , MC3635_mode_c_mctrl_t , MC3635_power_mode_t , MC3635_sample_rate_t )
 *
 * @details     It sets the device mode, power mode and the ODR.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMode:            Device mode: SNIFF, CWAKE or SWAKE.
 * @param[in]    myPowerMode:       Device power mode.
 * @param[in]    myODR:             Sample Rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetMode.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        27/April/2018
 * @version     27/April/2018     The ORIGIN
 * @pre         If you want to put the device into either STANDBY, SLEEP or TRIG mode, DO NOT use this function,
 *              just use the its own functions.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_SetMode ( I2C_parameters_t myI2Cparameters, MC3635_mode_c_mctrl_t myMode, MC3635_power_mode_t myPowerMode, MC3635_sample_rate_t myODR )
{
    uint8_t         cmd[] =   { 0, 0 };
    i2c_status_t    aux   =   0;


    /* CHECK INVALID MODES  */
    // TRIG, STANDBY and SLEEP mode have their own function, do NOT use this one!
    if ( ( myMode == MODE_C_MCTRL_STANDBY ) || ( myMode == MODE_C_MCTRL_SLEEP ) || ( myMode == MODE_C_MCTRL_TRIG ) )
    {
        return MC3635_FAILURE;
    }

    /* POWER MODE   */
    // Get the register data
    cmd[0]  =   PMCR;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    if ( myMode == MODE_C_MCTRL_SNIFF )
    {
        cmd[1] &=  ~PMCR_SPM_MASK;
        cmd[1] |=   ( myPowerMode << 4U );
    }
    else
    {
        cmd[1] &=  ~PMCR_CSPM_MASK;
        cmd[1] |=   ( myPowerMode << 0U );
    }

    // Update the register
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );



    /*  SAMPLE RATE FOR THE GIVEN MODE */
    // SNIFF mode
    if ( myMode == MODE_C_MCTRL_SNIFF )
    {
        cmd[0]  =   SNIFF_C;

        switch ( myPowerMode )
        {
        case ULTRA_LOW_POWER_MODE:
            if ( ( myODR == ODR_13 ) || ( myODR == ODR_14 ) )
            {
                return MC3635_FAILURE;
            }
            break;

        default:
        case LOW_POWER_MODE:
            if ( ( myODR == ODR_12 ) || ( myODR == ODR_13 ) || ( myODR == ODR_14 ) )
            {
                return MC3635_FAILURE;
            }
            break;

        case PRECISION:
            if ( ( myODR == ODR_9 ) || ( myODR == ODR_10 ) || ( myODR == ODR_11 ) || ( myODR == ODR_12 ) || ( myODR == ODR_13 ) || ( myODR == ODR_14 ) )
            {
                return MC3635_FAILURE;
            }
            break;
        }
    }
    // CWAKE and SWAKE mode
    else
    {
        cmd[0]  =   RATE_1;

        if ( ( myODR == ODR_0 ) || ( myODR == ODR_1 ) || ( myODR == ODR_2 ) || ( myODR == ODR_3 ) || ( myODR == ODR_4 ) || ( myODR == ODR_13 ) || ( myODR == ODR_14 ) )
        {
            return MC3635_FAILURE;
        }
        else
        {
            switch ( myPowerMode )
            {
            case ULTRA_LOW_POWER_MODE:
                if ( myODR == ODR_5 )
                {
                    return MC3635_FAILURE;
                }
                break;

            default:
            case LOW_POWER_MODE:
                if ( myODR == ODR_12 )
                {
                    return MC3635_FAILURE;
                }
                break;

            case PRECISION:
                if ( ( myODR == ODR_9 ) || ( myODR == ODR_10 ) || ( myODR == ODR_11 ) || ( myODR == ODR_12 ) )
                {
                    return MC3635_FAILURE;
                }
                break;
            }
        }
    }


    // Check if Specific setup steps are required
    if ( myODR == ODR_15 )
    {
        // Previous steps ( Step 1, Step 2 and Step 3 ) have to be implemented by the user before calling this function
        // Step 4 is implemented at the begging of this function.

        // Step 5: Point to set wake/sniff settings
        cmd[0]  =   RATE_1;
        cmd[1]  =   0x10;
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

        if ( cmd[0] == SNIFF_C )
        {
            // Step 6: Rate 15 setup 1 for sniff
            cmd[0]  =   TRIGC;
            cmd[1]  =   0x30;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 7: Rate 15 setup 2 for sniff
            cmd[0]  =   RATE_1;
            cmd[1]  =   0x30;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 8: Rate 15 setup 3 for sniff
            cmd[0]  =   TRIGC;
            cmd[1]  =   0x01;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 9: Point to value 1
            cmd[0]  =   RATE_1;
            cmd[1]  =   0x60;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 10: Write value 1
            cmd[0]  =   TRIGC;
            switch ( myPowerMode )
            {
                case ULTRA_LOW_POWER_MODE:
                    cmd[1]  =   0x52;
                    break;

                default:
                case LOW_POWER_MODE:
                    cmd[1]  =   0x72;
                    break;

                case PRECISION:
                    cmd[1]  =   0x32;
                    break;
            }

            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 11: Point to value 2
            cmd[0]  =   RATE_1;
            cmd[1]  =   0x70;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
        }
        else
        {
            // Step 6: Rate 15 setup 1 for the given device mode
            cmd[0]  =   TRIGC;
            cmd[1]  =   0x03;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 7: Rate 15 setup 2 for the given device mode
            cmd[0]  =   RATE_1;
            cmd[1]  =   0x20;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 8: Rate 15 setup 3 for the given device mode
            cmd[0]  =   TRIGC;
            cmd[1]  =   0x01;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 9: Point to value 1
            cmd[0]  =   RATE_1;
            cmd[1]  =   0x40;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 10: Write value 1
            cmd[0]  =   TRIGC;
            switch ( myPowerMode )
            {
                case ULTRA_LOW_POWER_MODE:
                    cmd[1]  =   0x52;
                    break;

                default:
                case LOW_POWER_MODE:
                    cmd[1]  =   0x72;
                    break;

                case PRECISION:
                    cmd[1]  =   0x32;
                    break;
            }

            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

            // Step 11: Point to value 2
            cmd[0]  =   RATE_1;
            cmd[1]  =   0x50;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
        }

        // Step 12: Write value 2
        cmd[0]  =   TRIGC;
        switch ( myPowerMode )
        {
            case ULTRA_LOW_POWER_MODE:
                cmd[1]  =   0x01;
                break;

            default:
            case LOW_POWER_MODE:
                cmd[1]  =   0x02;
                break;

            case PRECISION:
                cmd[1]  =   0x12;
                break;
        }
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );

        // Step 13: Apply the values
        cmd[0]  =   RATE_1;
        cmd[1]  =   0x0F;
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
    }
    else
    {
        // Get the register data
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
        aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );


        // Update the register data for the specific mode
        if ( cmd[0] == SNIFF_C )
        {
            cmd[1] &=  ~SNIFF_C_SNIFF_SR_MASK;
            cmd[1] |=   myODR;
        }
        else
        {
            cmd[1] &=  ~RATE_1_RR_MASK;
            cmd[1] |=   myODR;
        }

        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
    }


    /* DEVICE MODE */
    // Step 14: Go to the given device mode
    cmd[0]  =   MODE_C;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    cmd[1] &=  ~MODE_C_MCTRL_MASK;
    cmd[1] |=   myMode;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetTriggerMode  ( I2C_parameters_t , MC3635_mode_c_trig_cmd_t , uint8_t , MC3635_sniff_c_stb_rate_t )
 *
 * @details     It sets the TRIGGER mode.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myTriggerEnable:       Enable/Disable Trigger mode.
 * @param[in]    myTriggerSamples:      Number of samples for the trigger mode.
 * @param[in]    mySTANDBY_ClockRate:   ODR for the trigger mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetTriggerMode.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        27/April/2018
 * @version     27/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_SetTriggerMode ( I2C_parameters_t myI2Cparameters, MC3635_mode_c_trig_cmd_t myTriggerEnable, uint8_t myTriggerSamples,
                                         MC3635_sniff_c_stb_rate_t mySTANDBY_ClockRate )
{
    uint8_t         cmd[] =   { 0, 0 };
    i2c_status_t    aux   =   0;


    if ( myTriggerSamples == 0 )
    {
        return MC3635_FAILURE;
    }
    else
    {
        /* ODR */
        MC3635_SetStandbyClockRate ( myI2Cparameters, mySTANDBY_ClockRate );


        /* NUMBER OF SAMPLES    */
        cmd[0]  =   TRIGC;
        cmd[1]  =   myTriggerSamples;
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );


        /* TRIGGER MODE AND ENABLE/DISABLE TRIGGER  */
        // Get the register data
        cmd[0]  =   MODE_C;
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
        aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

        // Update the register data
        cmd[1] &=  ~( MODE_C_MCTRL_MASK | MODE_C_TRIG_CMD_MASK );
        cmd[1] |=   ( MODE_C_MCTRL_TRIG | myTriggerEnable );
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
    }




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ManualSniffReset  ( I2C_parameters_t , MC3635_sniffcf_c_sniff_reset_t )
 *
 * @details     It is a manual reset for the Sniff block.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySniffResetBit:   Sniff block reset.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_ManualSniffReset.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        30/April/2018
 * @version     30/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_ManualSniffReset ( I2C_parameters_t myI2Cparameters, MC3635_sniffcf_c_sniff_reset_t mySniffResetBit )
{
    uint8_t         cmd[] =   { SNIFFCF_C, 0 };
    i2c_status_t    aux   =   0;


    // Get the register data
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    // Update the register data
    cmd[1] &=  ~SNIFFCF_C_SNIFF_RESET_MASK;
    cmd[1] |=   mySniffResetBit;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_ConfSniffMode  ( I2C_parameters_t , MC3635_sniffcf_c_sniff_thadr_t , uint8_t , MC3635_sniffth_c_sniff_and_or_t , MC3635_sniffth_c_sniff_mode_t , MC3635_sniffcf_c_sniff_cnten_t ,
 *                                      MC3635_sniffcf_c_sniff_mux_t )
 *
 * @details     It configures the parameters for the SNIFF mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySniffADR:   Sniff block reset.
 * @param[in]    mySniffThreshold:   Sniff block reset.
 * @param[in]    mySniffLogicalMode:   Sniff block reset.
 * @param[in]    mySniffDeltaCount:   Sniff block reset.
 * @param[in]    mySniffEnableDetectionCount:   Sniff block reset.
 * @param[in]    mySniffMux:   Sniff block reset.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_ConfSniffMode.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        1/May/2018
 * @version     1/May/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_ConfSniffMode ( I2C_parameters_t myI2Cparameters, MC3635_sniffcf_c_sniff_thadr_t mySniffADR, uint8_t mySniffThreshold, MC3635_sniffth_c_sniff_and_or_t mySniffLogicalMode,
                                        MC3635_sniffth_c_sniff_mode_t mySniffDeltaCount, MC3635_sniffcf_c_sniff_cnten_t mySniffEnableDetectionCount, MC3635_sniffcf_c_sniff_mux_t mySniffMux )
{
    uint8_t         cmd[] =   { 0, 0 };
    i2c_status_t    aux   =   0;


    /* SNIFF THRESHOLD, LOGICAL MODE and DELTA COUNT */
    // If threshold is selected:        0<= mySniffThreshold <= 63
    // If detection count is selected:  0 < mySniffThreshold <= 62
    if ( ( ( ( mySniffADR == SNIFFCF_C_SNIFF_THADR_SNIFF_THRESHOLD_X_AXIS ) || ( mySniffADR == SNIFFCF_C_SNIFF_THADR_SNIFF_THRESHOLD_Y_AXIS ) || ( mySniffADR == SNIFFCF_C_SNIFF_THADR_SNIFF_THRESHOLD_Z_AXIS ) )  && ( mySniffThreshold > 63 ) ) ||
        ( ( mySniffADR == SNIFFCF_C_SNIFF_THADR_SNIFF_DETECTION_X_AXIS ) || ( mySniffADR == SNIFFCF_C_SNIFF_THADR_SNIFF_DETECTION_Y_AXIS ) || ( mySniffADR == SNIFFCF_C_SNIFF_THADR_SNIFF_DETECTION_Z_AXIS ) )  && ( ( mySniffThreshold == 0 ) || ( mySniffThreshold > 62 ) ) )
    {
        return   MC3635_FAILURE;
    }
    else
    {
        // Update the register data
        cmd[0]  =   SNIFFTH_C;
        cmd[1]  =   ( mySniffADR | mySniffLogicalMode | mySniffDeltaCount );
        aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
    }

    /* SNIFF THRESHOLD ADDRESS, DETECTION COUNT and MUX */
    // Get the register data
    cmd[0]  =   SNIFFCF_C;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    // Update the register data
    cmd[1] &=  ~( SNIFFCF_C_SNIFF_THADR_MASK | SNIFFCF_C_SNIFF_CNTEN_MASK | SNIFFCF_C_SNIFF_MUX_MASK );
    cmd[1] |=   ( mySniffADR | mySniffEnableDetectionCount | mySniffMux );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );





    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetResolution  ( I2C_parameters_t , MC3635_range_c_res_t )
 *
 * @details     It sets the accelerometer resolution.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myResolution:      Resolution.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetResolution.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        6/May/2018
 * @version     6/May/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_SetResolution ( I2C_parameters_t myI2Cparameters, MC3635_range_c_res_t myResolution )
{
    uint8_t         cmd[] =   { RANGE_C, 0 };
    i2c_status_t    aux   =   0;


    // Get the register data
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    // Update the register data
    cmd[1] &=  ~RANGE_C_RES_MASK;
    cmd[1] |=   myResolution;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetRange  ( I2C_parameters_t , MC3635_range_c_range_t )
 *
 * @details     It sets the accelerometer range.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myRange:           Range.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetRange.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        6/May/2018
 * @version     6/May/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The device MUST be in STANDBY mode, the user has to call this function
 *              first: MC3635_SetStandbyMode.
 */
MC3635_status_t  MC3635_SetRange ( I2C_parameters_t myI2Cparameters, MC3635_range_c_range_t myRange )
{
    uint8_t         cmd[] =   { RANGE_C, 0 };
    i2c_status_t    aux   =   0;


    // Get the register data
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT  );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );

    // Update the register data
    cmd[1] &=  ~RANGE_C_RANGE_MASK;
    cmd[1] |=   myRange;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}
