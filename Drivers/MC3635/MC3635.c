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
 * @warning     N/A.
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
 * @warning     N/A.
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


    /* Put the device in Standby mode */
    // [TODO]

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
 */
MC3635_status_t  MC3635_SetReload ( I2C_parameters_t myI2Cparameters )
{
    uint8_t         cmd[]        =   { RESET , 0 };
    uint32_t        myTimeOut    =   23232323;
    i2c_status_t    aux          =   0;


    /* Put the device in Standby mode */
    // [TODO]

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
 * @version     26/April/2018     The ORIGIN
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
    myRawData->XRawAxis    =  cmd[1];
    myRawData->XRawAxis  <<=  8;
    myRawData->XRawAxis   |=  cmd[0];

    myRawData->YRawAxis    =  cmd[3];
    myRawData->YRawAxis  <<=  8;
    myRawData->YRawAxis   |=  cmd[2];

    myRawData->ZRawAxis    =  cmd[5];
    myRawData->ZRawAxis  <<=  8;
    myRawData->ZRawAxis   |=  cmd[4];




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
 * @brief       MC3635_SetModeControl  ( I2C_parameters_t , MC3635_mode_c_mctrl_t , MC3635_mode_c_x_axis_pd_t ,
                                         MC3635_mode_c_y_axis_pd_t , MC3635_mode_c_z_axis_pd_t , MC3635_mode_c_trig_cmd_t , uint8_t )
 *
 * @details     It sets mode control of the device and if the trigger bit is enabled, the number
 *              of samples to be acquired is given as well.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myOperationalMode: Operational Mode for the device: Sleep/Standby/Sniff/CWake/SWake/Trig.
 * @param[in]    myXAxis:           Enabled/Disabled.
 * @param[in]    myYAxis:           Enabled/Disabled.
 * @param[in]    myZAxis:           Enabled/Disabled.
 * @param[in]    myTriggerEnable:   Enabled/Disabled.
 * @param[in]    myTriggerSamples:  Number of Samples for triggering.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetModeControl.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MC3635_status_t  MC3635_SetModeControl ( I2C_parameters_t myI2Cparameters, MC3635_mode_c_mctrl_t myOperationalMode, MC3635_mode_c_x_axis_pd_t myXAxis,
                                         MC3635_mode_c_y_axis_pd_t myYAxis, MC3635_mode_c_z_axis_pd_t myZAxis, MC3635_mode_c_trig_cmd_t myTriggerEnable,
                                         uint8_t myTriggerSamples )
{
    uint8_t         cmd[] =   { MODE_C, 0 };
    i2c_status_t    aux   =   0;


    /* Update the trigger samples if it is needed */
    if ( myTriggerEnable == MODE_C_TRIG_CMD_ENABLED )
    {
        /* It has to be at least 1 */
        if ( myTriggerSamples == 0 )
        {
            return   MC3635_FAILURE;
        }
        else
        {
            /* Put the device in Standby mode */
            // [TODO]

            /* Update the register data */
            cmd[0]  =   TRIGC;
            cmd[1]  =   myTriggerSamples;
            aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );
        }
    }


    /* Update the register data */
    cmd[0]  =   MODE_C;
    cmd[1]  =   ( myOperationalMode | myXAxis | myYAxis | myZAxis | myTriggerEnable );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}



/**
 * @brief       MC3635_SetWakePowerModeODR  ( I2C_parameters_t , MC3635_pmcr_cspm_t , MC3635_odr_t )
 *
 * @details     It sets the power mode and ODR for wake modes.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPowerMode:       Wake Power Mode.
 * @param[in]    myODR:             ODR for the chosen wake power mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MC3635_SetWakePowerModeODR.
 *
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2018
 * @version     26/April/2018     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MC3635_status_t  MC3635_SetWakePowerModeODR ( I2C_parameters_t myI2Cparameters, MC3635_pmcr_cspm_t myPowerMode, MC3635_odr_t myODR )
{
    uint8_t         cmd[] =   { RATE_1, 0 };
    i2c_status_t    aux   =   0;


//    /* Update the register data */
//    cmd[0]  =   MODE_C;
//    cmd[1]  =   ( myOperationalMode | myXAxis | myYAxis | myZAxis | myTriggerEnable );
//    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT  );




    if ( aux == I2C_SUCCESS )
       return   MC3635_SUCCESS;
    else
       return   MC3635_FAILURE;
}
