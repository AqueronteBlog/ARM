/**
 * @brief       AS3933.c
 * @details     3D Low Frequency Wakeup Receiver.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "AS3933.h"


/**
 * @brief       AS3933_Init   ( SPI_parameters_t )
 *
 * @details     It configures the SPI pins and resets all the AS3933 register ( default value ) and resets its status.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     27/February/2018   PRESET_DEFAULT and CLEAR_WAKE functions were added.
 *              22/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS3933_status_t  AS3933_Init ( SPI_parameters_t mySPI_parameters )
{
    uint8_t             cmd   =    0;
    spi_status_t        mySPI_status;


    // Configure the SPI peripheral
    mySPI_status     =   spi_init ( mySPI_parameters );


    // Set the device in listening mode
    cmd              =   ( AS3933_DIRECT_COMMAND | CLEAR_WAKE );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd, 1, &cmd, 0 );

    // Sets all register in the default mode
    cmd              =   ( AS3933_DIRECT_COMMAND | PRESET_DEFAULT );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd, 1, &cmd, 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetLowPowerMode   ( SPI_parameters_t , AS3933_channels_enable_t , AS3933_scanning_mode_t , AS3933_r4_t_off_value_t  )
 *
 * @details     It configures the low power mode.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myEnabledChannels: Number of channels enabled.
 * @param[in]    myLowPowerMode:    Low power mode.
 * @param[in]    myT_Off:           Period only if ON/OFF mode is selected ( in myLowPowerMode ), it is ignored otherwise.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetLowPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        27/February/2018
 * @version     27/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     Data-sheet p.14 8.1.1 Listening Mode. It is NOT clear which channels have to be enabled according to the
 *              low power mode: '...If the three dimensional detection is not required, then it is possible to deactivate one
 *              or more channels. In case only two channels are required, then the deactivated channel must be the number
 *              three; while in case only one channel is needed, then the active channel must be the number one'.
 *
 *              Data-sheet p.37 8.10 Channel Selection in Scanning Mode and ON/OFF Mode: 'In case only 2 channels are active and
 *              one of the Low Power modes is enabled, then the channels 1 and 3 have to be active. If the chip works in On-Off
 *              mode and only one channel is active then the active channel has to be the channel 1.'.
 *
 *              This function follows the methodology in: Low Power Modes/Channels enabled: Data-sheet p.37 8.10 Channel
 *              Selection in Scanning Mode and ON/OFF Mode.
 */
AS3933_status_t  AS3933_SetLowPowerMode ( SPI_parameters_t mySPI_parameters, AS3933_channels_enable_t myEnabledChannels, AS3933_scanning_mode_t myLowPowerMode, AS3933_r4_t_off_value_t myT_Off )
{
    uint8_t             cmd[]   =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R0 register
    cmd[0]           =   ( AS3933_READ | AS3933_R0 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Channels 1:3
    cmd[1] &=   ~( EN_A1_MASK | EN_A2_MASK | EN_A3_MASK );

    // Mask Scanning Mode
    cmd[1] &=   ~( MUX_123_MASK | ON_OFF_MASK );



    // Set the channels enabled
    switch ( myEnabledChannels )
    {
    case AS3933_CH1_OFF_CH2_OFF_CH3_OFF:
        cmd[1] &=   ( EN_A1_DISABLED | EN_A2_DISABLED | EN_A3_DISABLED );
        break;

    case AS3933_CH1_ON_CH2_OFF_CH3_OFF:
        cmd[1] |=   ( EN_A1_ENABLED );
        break;

    case AS3933_CH1_OFF_CH2_ON_CH3_OFF:
        cmd[1] |=   ( EN_A2_ENABLED );
        break;

    case AS3933_CH1_ON_CH2_ON_CH3_OFF:
        cmd[1] |=   ( EN_A1_ENABLED | EN_A2_ENABLED );
        break;

    case AS3933_CH1_OFF_CH2_OFF_CH3_ON:
        cmd[1] |=   ( EN_A3_ENABLED );
        break;

    case AS3933_CH1_ON_CH2_OFF_CH3_ON:
        cmd[1] |=   ( EN_A1_ENABLED | EN_A3_ENABLED );
        break;

    case AS3933_CH1_OFF_CH2_ON_CH3_ON:
        cmd[1] |=   ( EN_A2_ENABLED | EN_A3_ENABLED );
        break;

    default:
    case AS3933_CH1_ON_CH2_ON_CH3_ON:
        cmd[1] |=   ( EN_A1_ENABLED | EN_A2_ENABLED | EN_A3_ENABLED );
        break;
    }


    // Set Scanning mode
    switch ( myLowPowerMode )
    {
    default:
    case AS3933_STANDARD_LISTENING_MODE:
        break;

    case AS3933_SCANNING_MODE:
        if ( ( myEnabledChannels == AS3933_CH1_ON_CH2_OFF_CH3_ON )  || ( myEnabledChannels == AS3933_CH1_ON_CH2_ON_CH3_ON )  || ( myEnabledChannels == AS3933_CH1_ON_CH2_OFF_CH3_OFF ) ||
             ( myEnabledChannels == AS3933_CH1_OFF_CH2_ON_CH3_OFF ) || ( myEnabledChannels == AS3933_CH1_OFF_CH2_OFF_CH3_ON ) )
            cmd[1] |=   ( MUX_123_ENABLED );
        else
            return   AS3933_FAILURE;

        break;

    case AS3933_ON_OFF_MODE:
        if ( ( myEnabledChannels == AS3933_CH1_ON_CH2_OFF_CH3_ON ) || ( myEnabledChannels == AS3933_CH1_ON_CH2_ON_CH3_ON ) || ( myEnabledChannels == AS3933_CH1_ON_CH2_OFF_CH3_OFF ) )
            cmd[1] |=   ( ON_OFF_ENABLED );
        else
            return   AS3933_FAILURE;
        break;
    }

    // Update power mode and active channels
    cmd[0]           =   ( AS3933_WRITE | AS3933_R0 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );



    if ( myLowPowerMode == AS3933_ON_OFF_MODE )
    {
        // Read R4 register
        cmd[0]           =    ( AS3933_READ | AS3933_R4 );
        mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

        // Mask T_OFF
        cmd[1]          &=   ~( T_OFF_MASK );

        // Update Off time in ON/OFF operation mode
        cmd[1]          |=    ( myT_Off );

        cmd[0]           =    ( AS3933_WRITE | AS3933_R4 );
        mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );
    }



    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetArtificialWakeUp   ( SPI_parameters_t , AS3933_r8_t_auto_value_t )
 *
 * @details     It configures the artificial wakeup.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myArtificialWakeUp:    Period only if ON/OFF mode is selected ( in myLowPowerMode ), it is ignored otherwise.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetArtificialWakeUp.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetArtificialWakeUp ( SPI_parameters_t mySPI_parameters, AS3933_r8_t_auto_value_t myArtificialWakeUp )
{
    uint8_t             cmd[]   =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R8 register
    cmd[0]           =   ( AS3933_READ | AS3933_R8 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Artificial wakeup
    cmd[1] &=   ~( T_AUTO_MASK );

    // Update the value
    cmd[1] |=    myArtificialWakeUp;


    // Update artificial wakeup
    cmd[0]           =   ( AS3933_WRITE | AS3933_R8 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_ReadFalseWakeUpRegister   ( SPI_parameters_t , AS3933_data_t* )
 *
 * @details     It gets feedback on the surrounding environment reading the false wakeup register.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myF_WAKE:              F_WAKE register.
 *
 *
 * @return       Status of AS3933_ReadFalseWakeUpRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS3933_status_t  AS3933_ReadFalseWakeUpRegister ( SPI_parameters_t mySPI_parameters, AS3933_data_t* myF_WAKE )
{
    uint8_t             cmd   =    ( AS3933_READ | AS3933_R13 );
    spi_status_t        mySPI_status;


    // Read R13 register
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd, 1, (uint8_t*)( &myF_WAKE->f_wake ), 1 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetClockGenerator   ( SPI_parameters_t , AS3933_r1_en_xtal_value_t, AS3933_r16_clock_gen_dis_value_t )
 *
 * @details     It configures the clock generator.
 *
 * @param[in]    mySPI_parameters:              SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myClockGenerator:              Enable/Disable external crystal oscillator.
 * @param[in]    myClockGeneratorOutputMode:    Enable/Disable the clock generator output signal displayed on CL_DAT pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetClockGenerator.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetClockGenerator ( SPI_parameters_t mySPI_parameters, AS3933_r1_en_xtal_value_t myClockGenerator, AS3933_r16_clock_gen_dis_value_t myClockGeneratorOutputMode )
{
    uint8_t             cmd[]   =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Configure the Crystal oscillator
    // Read R1 register
    cmd[0]           =   ( AS3933_READ | AS3933_R1 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Crystal oscillator
    cmd[1] &=   ~( EN_XTAL_MASK );

    // Update the value
    cmd[1] |=    myClockGenerator;


    // Update Crystal oscillator
    cmd[0]           =   ( AS3933_WRITE | AS3933_R1 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );


    // Configure the Clock Generator Output
    // Read R16 register
    cmd[0]           =   ( AS3933_READ | AS3933_R16 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Clock Generator output signal
    cmd[1] &=   ~( CLOCK_GEN_DIS_MASK );

    // Update the value
    cmd[1] |=    myClockGeneratorOutputMode;


    // Update Clock Generator output signal
    cmd[0]           =   ( AS3933_WRITE | AS3933_R16 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_CalibrateRC_Oscillator   ( SPI_parameters_t , AS3933_r1_en_xtal_value_t, AS3933_r16_clock_gen_dis_value_t )
 *
 * @details     It calibrates RC oscillator.
 *
 * @param[in]    mySPI_parameters:              SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_CalibrateRC_Oscillator.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     12/March/2018       The timeout was removed, the bits for calibration are checked instead.
 *              28/February/2018    The ORIGIN
 * @pre         RC-Oscillator: Self Calibration is ONLY available.
 * @pre         There is NO need to calibrate the RC oscillator if the crystal oscillator is enabled.
 * @warning     In case the pattern detection and the Manchester decoder are not enabled ( R1<1>=0 and R1<3>=1 ) the calibration on the RC-oscillator
 *              is not needed. Should this not be the case, the RC-oscillator has to be calibrated.
 */
AS3933_status_t  AS3933_CalibrateRC_Oscillator ( SPI_parameters_t mySPI_parameters )
{
    uint8_t             cmd         =    0;
    spi_status_t        mySPI_status;


    // Start the calibration
    cmd              =   ( AS3933_DIRECT_COMMAND | CALIB_RCO_LC );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd, 1, &cmd, 0 );


    // RC oscillator will be calibrated when RC_CAL_OK = '1' ( R14<6> )
    do{
        cmd              =   ( AS3933_READ | AS3933_R14 );
        mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd, 1, &cmd, 1 );
    } while ( ( ( cmd & RC_CAL_OK_MASK ) != RC_CAL_OK_HIGH ) && ( ( cmd & RC_CAL_KO_MASK ) != RC_CAL_KO_HIGH ) );



    if ( ( mySPI_status == SPI_SUCCESS ) && ( ( cmd & RC_CAL_KO_MASK ) != RC_CAL_KO_HIGH ) )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetAntennaDamper   ( SPI_parameters_t , AS3933_r1_att_on_value_t, AS3933_r4_d_res_value_t )
 *
 * @details     It configures the antenna damper and its shunt resistor.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myAntennaDamperMode:   Enable/Disable antenna dumper.
 * @param[in]    myShuntResistor:       Configure antenna dumping resistor.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetAntennaDamper.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetAntennaDamper ( SPI_parameters_t mySPI_parameters, AS3933_r1_att_on_value_t myAntennaDamperMode, AS3933_r4_d_res_value_t myShuntResistor )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Configure Antenna dumper
    // Read R1 register
    cmd[0]           =   ( AS3933_READ | AS3933_R1 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Antenna dumper
    cmd[1]          &=  ~( ATT_ON_MASK );

    // Update Antenna dumper
    cmd[0]           =   ( AS3933_WRITE | AS3933_R1 );
    cmd[1]          |=   ( myAntennaDamperMode );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );


    // Configure Antenna dumper resistor
    // Read R4 register
    cmd[0]           =   ( AS3933_READ | AS3933_R4 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Antenna dumper resistor
    cmd[1]          &=  ~( D_RES_MASK );

    // Update Antenna dumper resistor
    cmd[0]           =   ( AS3933_WRITE | AS3933_R4 );
    cmd[1]          |=   ( myShuntResistor );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetEnvelopDetector   ( SPI_parameters_t , AS3933_r3_fs_env_value_t )
 *
 * @details     It configures the envelop detector for different symbol rates.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    mySymbolRates:     Envelop detector time constant.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetEnvelopDetector.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetEnvelopDetector ( SPI_parameters_t mySPI_parameters, AS3933_r3_fs_env_value_t mySymbolRates )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R3 register
    cmd[0]           =   ( AS3933_READ | AS3933_R3 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Symbol rate
    cmd[1]          &=  ~( FS_ENV_MASK );

    // Update symbol rate
    cmd[0]           =   ( AS3933_WRITE | AS3933_R3 );
    cmd[1]          |=   ( mySymbolRates );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );





    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetDataSlicer   ( SPI_parameters_t , AS3933_r1_abs_hy_value_t , AS3933_r3_fs_scl_value_t )
 *
 * @details     It configures the data slicer for different preamble length.
 *
 * @param[in]    mySPI_parameters:          SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myAbsoluteThresholdMode:   Enable Data slicer absolute reference.
 * @param[in]    myMinimumPreambleLength:   Data slices time constant.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetDataSlicer.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetDataSlicer ( SPI_parameters_t mySPI_parameters, AS3933_r1_abs_hy_value_t myAbsoluteThresholdMode, AS3933_r3_fs_scl_value_t myMinimumPreambleLength )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Configure Data slicer absolute reference
    // Read R1 register
    cmd[0]           =   ( AS3933_READ | AS3933_R1 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Data slicer absolute reference
    cmd[1]          &=  ~( ABS_HY_MASK );

    // Update symbol rate
    cmd[0]           =   ( AS3933_WRITE | AS3933_R1 );
    cmd[1]          |=   ( myAbsoluteThresholdMode );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );


    // Configure Data slices time constant
    // Read R3 register
    cmd[0]           =   ( AS3933_READ | AS3933_R3 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Data slices time constant
    cmd[1]          &=  ~( FS_SCL_MASK );

    // Update Data slices time constant
    cmd[0]           =   ( AS3933_WRITE | AS3933_R3 );
    cmd[1]          |=   ( myMinimumPreambleLength );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetComparatorHysteresis   ( SPI_parameters_t , AS3933_r3_hy_pos_value_t , AS3933_r3_hy_20m_value_t )
 *
 * @details     It configures the hysteresis on the data slicer comparator.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myHysteresisMode:  Data slicer hysteresis, edge.
 * @param[in]    myHysteresisRange: Data slicer hysteresis, comparator.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetComparatorHysteresis.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetComparatorHysteresis ( SPI_parameters_t mySPI_parameters, AS3933_r3_hy_pos_value_t myHysteresisMode, AS3933_r3_hy_20m_value_t myHysteresisRange )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R3 register
    cmd[0]           =   ( AS3933_READ | AS3933_R3 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask both hysteresis edge and comparator
    cmd[1]          &=  ~( HY_POS_MASK | HY_20M_MASK );

    // Update hysteresis on the data slicer comparator
    cmd[0]           =   ( AS3933_WRITE | AS3933_R3 );
    cmd[1]          |=   ( myHysteresisMode | myHysteresisRange );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetGainReduction   ( SPI_parameters_t , AS3933_r4_gr_value_t )
 *
 * @details     It configures the gain reduction.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myGainReductionValue:  Gain reduction.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetGainReduction.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetGainReduction ( SPI_parameters_t mySPI_parameters, AS3933_r4_gr_value_t myGainReductionValue )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R4 register
    cmd[0]           =   ( AS3933_READ | AS3933_R4 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Gain reduction
    cmd[1]          &=  ~( GR_MASK );

    // Update Gain reduction
    cmd[0]           =   ( AS3933_WRITE | AS3933_R4 );
    cmd[1]          |=   ( myGainReductionValue );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetOperatingFrequencyRange   ( SPI_parameters_t , AS3933_r8_band_sel_value_t )
 *
 * @details     It configures the operating frequency range.
 *
 * @param[in]    mySPI_parameters:          SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myOperatingFrequencyRange: Band selection.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetOperatingFrequencyRange.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetOperatingFrequencyRange ( SPI_parameters_t mySPI_parameters, AS3933_r8_band_sel_value_t myOperatingFrequencyRange )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R8 register
    cmd[0]           =   ( AS3933_READ | AS3933_R8 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Band selection
    cmd[1]          &=  ~( BAND_SEL_MASK );

    // Update Band selection
    cmd[0]           =   ( AS3933_WRITE | AS3933_R8 );
    cmd[1]          |=   ( myOperatingFrequencyRange );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetFrequencyDetectionTolerance   ( SPI_parameters_t , AS3933_tolerance_settings_t )
 *
 * @details     It configures the frequency detection tolerance.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myTolerance:       Tolerance band.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetFrequencyDetectionTolerance.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetFrequencyDetectionTolerance ( SPI_parameters_t mySPI_parameters, AS3933_tolerance_settings_t myTolerance )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R2 register
    cmd[0]           =   ( AS3933_READ | AS3933_R2 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Tolerance band
    cmd[1]          &=  ~( AS3933_TOLERANCE_MASK );

    // Update Tolerance band
    cmd[0]           =   ( AS3933_WRITE | AS3933_R2 );
    cmd[1]          |=   ( myTolerance );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetGainBoost   ( SPI_parameters_t , AS3933_r2_g_boost_value_t )
 *
 * @details     It configures the +3dB gain boost.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myGainBoostMode:   Enable/Disable +3dB Amplifier Gain Boost.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetGainBoost.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetGainBoost ( SPI_parameters_t mySPI_parameters, AS3933_r2_g_boost_value_t myGainBoostMode )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R2 register
    cmd[0]           =   ( AS3933_READ | AS3933_R2 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Gain boost
    cmd[1]          &=  ~( G_BOOST_MASK );

    // Update Gain boost
    cmd[0]           =   ( AS3933_WRITE | AS3933_R2 );
    cmd[1]          |=   ( myGainBoostMode );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetAGC   ( SPI_parameters_t , AS3933_r1_agc_tlim_value_t , AS3933_r1_agc_ud_value_t )
 *
 * @details     It configures the Automatic Gain Control ( AGC ).
 *
 * @param[in]    mySPI_parameters:          SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myAGC_CarrierBurstMode:    Enable/Disable AGC acting only on the first carrier burst.
 * @param[in]    myAGC_OperatingDirection:  Configure AGC direction operating.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetAGC.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetAGC ( SPI_parameters_t mySPI_parameters, AS3933_r1_agc_tlim_value_t myAGC_CarrierBurstMode, AS3933_r1_agc_ud_value_t myAGC_OperatingDirection )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R1 register
    cmd[0]           =   ( AS3933_READ | AS3933_R1 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask both AGC acting only on the first carrier burst and AGC direction operating
    cmd[1]          &=  ~( AGC_TLIM_MASK | AGC_UD_MASK );

    // Update both AGC acting only on the first carrier burst and AGC direction operating
    cmd[0]           =   ( AS3933_WRITE | AS3933_R1 );
    cmd[1]          |=   ( myAGC_CarrierBurstMode | myAGC_OperatingDirection );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetDataMask   ( SPI_parameters_t , AS3933_r0_dat_mask_value_t )
 *
 * @details     It configures the mask data before wakeup.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myDataMaskMode:    Mask data on DAT pin before wakeup happens.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetDataMask.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetDataMask ( SPI_parameters_t mySPI_parameters, AS3933_r0_dat_mask_value_t myDataMaskMode )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R0 register
    cmd[0]           =   ( AS3933_READ | AS3933_R0 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Mask data on DAT pin before wakeup happens
    cmd[1]          &=  ~( DAT_MASK_MASK );

    // Update Mask data on DAT pin before wakeup happens
    cmd[0]           =   ( AS3933_WRITE | AS3933_R0 );
    cmd[1]          |=   ( myDataMaskMode );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetCorrelator   ( SPI_parameters_t , AS3933_r1_en_wpat_value_t , AS3933_r0_patt32_value_t , AS3933_r7_t_hbit_value_t , AS3933_r1_en_manch_value_t )
 *
 * @details     It configures the correlator and the Manchester Decoder.
 *
 * @param[in]    mySPI_parameters:          SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myCorrelatorMode:          Enable/Disable Correlator.
 * @param[in]    mySymbolPattern:           Pattern extended.
 * @param[in]    myRate:                    Bit rate definition.
 * @param[in]    myManchesterDecoderMode:   Enable/Disable Manchester decoder.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetCorrelator.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetCorrelator ( SPI_parameters_t mySPI_parameters, AS3933_r1_en_wpat_value_t myCorrelatorMode, AS3933_r0_patt32_value_t mySymbolPattern, AS3933_r7_t_hbit_value_t myRate,
                                        AS3933_r1_en_manch_value_t myManchesterDecoderMode )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Configure Correlator mode and Manchester decoder mode
    // Read R1 register
    cmd[0]           =   ( AS3933_READ | AS3933_R1 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask both Correlator mode and Manchester decoder mode
    cmd[1]          &=  ~( EN_WPAT_MASK | EN_MANCH_MASK );

    // Update both Correlator mode and Manchester decoder mode
    cmd[0]           =   ( AS3933_WRITE | AS3933_R1 );
    cmd[1]          |=   ( myCorrelatorMode | myManchesterDecoderMode );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );


    // Configure Pattern extended
    // Read R0 register
    cmd[0]           =   ( AS3933_READ | AS3933_R0 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Pattern extended
    cmd[1]          &=  ~( PATT32_MASK );

    // Update Pattern extended
    cmd[0]           =   ( AS3933_WRITE | AS3933_R0 );
    cmd[1]          |=   ( mySymbolPattern );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );


    // Configure Bit rate definition
    // Read R7 register
    cmd[0]           =   ( AS3933_READ | AS3933_R7 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Bit rate definition
    cmd[1]          &=  ~( T_HBIT_MASK );

    // Update Bit rate definition
    cmd[0]           =   ( AS3933_WRITE | AS3933_R7 );
    cmd[1]          |=   ( myRate );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );





    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetWakeUpPattern   ( SPI_parameters_t , AS3933_data_t )
 *
 * @details     It sets the wakeup pattern ( Manchester ).
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myWakeUpPattern:   PATT1B and PATT2B ( Manchester ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetWakeUpPattern.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetWakeUpPattern ( SPI_parameters_t mySPI_parameters, AS3933_data_t myWakeUpPattern )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Update PATT2B
    cmd[0]           =   ( AS3933_WRITE | AS3933_R5 );
    cmd[1]           =   ( myWakeUpPattern.patt2b );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );

    // Update PATT1B
    cmd[0]           =   ( AS3933_WRITE | AS3933_R6 );
    cmd[1]           =   ( myWakeUpPattern.patt1b );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_GetWakeUpPattern   ( SPI_parameters_t , AS3933_data_t* )
 *
 * @details     It gets the wakeup pattern ( Manchester ).
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myWakeUpPattern:   PATT1B and PATT2B ( Manchester ).
 *
 *
 * @return       Status of AS3933_GetWakeUpPattern.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_GetWakeUpPattern ( SPI_parameters_t mySPI_parameters, AS3933_data_t* myWakeUpPattern )
{
    uint8_t             cmd       =    0;
    spi_status_t        mySPI_status;


    // Read R5 register
    cmd              =   ( AS3933_READ | AS3933_R5 );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd, 1, &myWakeUpPattern->patt2b, 1 );

    // Read R6 register
    cmd              =   ( AS3933_READ | AS3933_R6 );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd, 1, &myWakeUpPattern->patt1b, 1 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetAutomaticTimeOut   ( SPI_parameters_t , AS3933_r7_t_out_value_t )
 *
 * @details     It sets the automatic time-out setup.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myAutomaticTimeOut:    Automatic time-out.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetAutomaticTimeOut.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetAutomaticTimeOut ( SPI_parameters_t mySPI_parameters, AS3933_r7_t_out_value_t myAutomaticTimeOut )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R7 register
    cmd[0]           =   ( AS3933_READ | AS3933_R7 );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Automatic time-out
    cmd[1]          &=  ~( T_OUT_MASK );

    // Update Automatic time-out
    cmd[0]           =   ( AS3933_WRITE | AS3933_R7 );
    cmd[1]          |=   ( myAutomaticTimeOut );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetParallelTuningCapacitance   ( SPI_parameters_t , AS3933_parallel_tuning_channels_t , AS3933_parallel_tuning_capacitance_t )
 *
 * @details     It sets the parallel tuning capacitance on the chosen channel.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myChannel:             Channel for Parallel Tuning Capacitance.
 * @param[in]    myAddedCapacitance:    Parallel Tuning Capacitance.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_SetParallelTuningCapacitance.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     28/February/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetParallelTuningCapacitance ( SPI_parameters_t mySPI_parameters, AS3933_parallel_tuning_channels_t myChannel, AS3933_parallel_tuning_capacitance_t myAddedCapacitance )
{
    uint8_t             cmd[]       =    { 0, 0 };
    spi_status_t        mySPI_status;

    AS3933_spi_command_structure_registers_t    myAuxRegister;


    // Select the channel
    switch ( myChannel ){
        default:
        case AS3933_CHANNEL_LF1P:
            myAuxRegister    =   AS3933_R17;
            break;

       case AS3933_CHANNEL_LF2P:
           myAuxRegister    =   AS3933_R18;
            break;

       case AS3933_CHANNEL_LF3P:
           myAuxRegister    =   AS3933_R19;
            break;
    }


    // Read register
    cmd[0]           =   ( AS3933_READ | myAuxRegister );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[1], 1 );

    // Mask Parallel Tuning Capacitance
    cmd[1]          &=  ~( AS3933_CAPACITANCE_MASK );

    // Update Parallel Tuning Capacitance
    cmd[0]           =   ( AS3933_WRITE | myAuxRegister );
    cmd[1]          |=   ( myAddedCapacitance );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );





    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_GetRSSI   ( SPI_parameters_t , AS3933_data_t* )
 *
 * @details     It gets the RSSI for all channels.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myChannelRSSI:     RSSI.
 *
 *
 * @return       Status of AS3933_GetRSSI.
 *
 *
 * @author      Manuel Caballero
 * @date        28/February/2018
 * @version     12/March/2018       Auto-increment does NOT work when the registers are read
 *              28/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_GetRSSI ( SPI_parameters_t mySPI_parameters, AS3933_data_t* myChannelRSSI )
{
    uint8_t             cmd[]       =    { 0, 0, 0 };
    spi_status_t        mySPI_status;


    // Get RSSI1
    // Read R10 register
    cmd[0]           =   ( AS3933_READ | AS3933_R10 );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[0], 1 );

    // Parse the data
    myChannelRSSI->rssi1     =   ( cmd[0] & RSSI1_MASK );       // Channel1: RSSI1


    // Get RSSI3
    // Read R11 register
    cmd[0]           =   ( AS3933_READ | AS3933_R11 );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[0], 1 );

    // Parse the data
    myChannelRSSI->rssi3     =   ( cmd[0] & RSSI3_MASK );       // Channel1: RSSI1


    // Get RSSI2
    // Read R12 register
    cmd[0]           =   ( AS3933_READ | AS3933_R12 );
    mySPI_status     =    spi_transfer ( mySPI_parameters, &cmd[0], 1, &cmd[0], 1 );

    // Parse the data
    myChannelRSSI->rssi2     =   ( cmd[0] & RSSI2_MASK );       // Channel1: RSSI1





    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}



/**
 * @brief       AS3933_Send_DirectCommand   ( SPI_parameters_t , AS3933_spi_direct_commands_t )
 *
 * @details     It sends a direct command.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myDirectCommand:   Direct command to be sent.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_Send_DirectCommand.
 *
 *
 * @author      Manuel Caballero
 * @date        4/March/2018
 * @version     4/March/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS3933_status_t  AS3933_Send_DirectCommand ( SPI_parameters_t mySPI_parameters, AS3933_spi_direct_commands_t myDirectCommand )
{
    uint8_t             cmd         =    0;
    spi_status_t        mySPI_status;


    // Send a direct command
    cmd              =   ( AS3933_DIRECT_COMMAND | myDirectCommand );
    mySPI_status     =   spi_transfer ( mySPI_parameters, &cmd, 1, &cmd, 0 );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}
