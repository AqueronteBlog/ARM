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


    // Sets all register in the default mode
    cmd              =   ( AS3933_DIRECT_COMMAND | PRESET_DEFAULT );
    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd, 1, &cmd, 0, mySPI_parameters.CS, mySPI_parameters.CSport );

    // Set the device in listening mode
    cmd              =   ( AS3933_DIRECT_COMMAND | CLEAR_WAKE );
    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd, 1, &cmd, 0, mySPI_parameters.CS, mySPI_parameters.CSport );




    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetLowPowerMode   ( SPI_parameters_t , AS3933_channels_enable_t myEnabledChannels, AS3933_scanning_mode_t myLowPowerMode, AS3933_r4_t_off_value_t myT )
 *
 * @details     It configures the SPI pins and resets all the AS3933 register ( default value ) and resets its status.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myEnabledChannels: Number of channels enabled.
 * @param[in]    myLowPowerMode:    Low power mode.
 * @param[in]    myT:               Period only if ON/OFF mode is selected ( in myLowPowerMode ), it is ignored otherwise.
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
    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], 1, &cmd[1], 1, mySPI_parameters.CS, mySPI_parameters.CSport );

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
    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( myLowPowerMode == AS3933_ON_OFF_MODE )
    {
        // Read R4 register
        cmd[0]           =    ( AS3933_READ | AS3933_R4 );
        mySPI_status     =    spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], 1, &cmd[1], 1, mySPI_parameters.CS, mySPI_parameters.CSport );

        // Mask T_OFF
        cmd[1]          &=   ~( T_OFF_MASK );

        // Update Off time in ON/OFF operation mode
        cmd[1]          |=    ( myT_Off );

        cmd[0]           =    ( AS3933_WRITE | AS3933_R4 );
        mySPI_status     =    spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );
    }



    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}


/**
 * @brief       AS3933_SetArtificialWakeUp   ( SPI_parameters_t , AS3933_r8_t_auto_value_t )
 *
 * @details     It configures the SPI pins and resets all the AS3933 register ( default value ) and resets its status.
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
 * @date        27/February/2018
 * @version     27/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS3933_status_t  AS3933_SetArtificialWakeUp ( SPI_parameters_t mySPI_parameters, AS3933_r8_t_auto_value_t myArtificialWakeUp )
{
    uint8_t             cmd[]   =    { 0, 0 };
    spi_status_t        mySPI_status;


    // Read R0 register
    cmd[0]           =   ( AS3933_READ | AS3933_R0 );
    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], 1, &cmd[1], 1, mySPI_parameters.CS, mySPI_parameters.CSport );

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
    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( myLowPowerMode == AS3933_ON_OFF_MODE )
    {
        // Read R4 register
        cmd[0]           =    ( AS3933_READ | AS3933_R4 );
        mySPI_status     =    spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], 1, &cmd[1], 1, mySPI_parameters.CS, mySPI_parameters.CSport );

        // Mask T_OFF
        cmd[1]          &=   ~( T_OFF_MASK );

        // Update Off time in ON/OFF operation mode
        cmd[1]          |=    ( myT_Off );

        cmd[0]           =    ( AS3933_WRITE | AS3933_R4 );
        mySPI_status     =    spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );
    }



    if ( mySPI_status == SPI_SUCCESS )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}
