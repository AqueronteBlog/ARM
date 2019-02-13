/**
 * @brief       SX128X.c
 * @details     SX1280/SX1281. Long Range, Low Power, 2.4 GHz Transceiver with Ranging Capability.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/January/2019
 * @version     29/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "SX128X.h"


/**
 * @brief       SX128X_Init ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPI_parameters:       SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SX128X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t SX128X_Init ( SPI_parameters_t mySPI_parameters )
{
    spi_status_t aux;

    aux  =   spi_init ( mySPI_parameters );



    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       GetStatus ( SPI_parameters_t, SX128X_data_t* )
 *
 * @details     It gets the transceiver status.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   myStatus:          Status of the transceiver.
 *
 *
 * @return       Status of GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        07/February/2019
 * @version     07/February/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t GetStatus ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myStatus )
{
    uint8_t      cmd   =    0U;
    spi_status_t aux;

    /* Send command  */
    cmd     =   SX128X_GET_STATUS;
    aux     =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

    /* Parse the data    */
    myStatus->status     =   cmd;




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetSleep ( SPI_parameters_t , SX128X_set_sleep_sleep_config0_t , SX128X_set_sleep_sleep_config1_t , SX128X_set_sleep_sleep_config2_t )
 *
 * @details     It sets the transceiver to Sleep mode with the lowest current consumption possible.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myDataRAM:         Data RAM behavior.
 * @param[in]    myDataBuffer:      Data Buffer behavior.
 * @param[in]    myInstructionRAM:  Instruction RAM behavior.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetSleep.
 *
 *
 * @author      Manuel Caballero
 * @date        10/February/2019
 * @version     10/February/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t SetSleep ( SPI_parameters_t mySPI_parameters, SX128X_set_sleep_sleep_config0_t myDataRAM, SX128X_set_sleep_sleep_config1_t myDataBuffer, SX128X_set_sleep_sleep_config2_t myInstructionRAM )
{
    uint8_t      cmd[2]   =    { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]  =   SX128X_SET_SLEEP;
    cmd[1]  =   ( myDataRAM | myDataBuffer | myInstructionRAM );
    aux     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetStandby ( SPI_parameters_t , SX128X_set_standby_standbyconfig_t )
 *
 * @details     It sets the transceiver to Stand-by mode.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myDataRAM:         Data RAM behavior.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetStandby.
 *
 *
 * @author      Manuel Caballero
 * @date        11/February/2019
 * @version     11/February/2019   The ORIGIN
 * @pre         After power on or application of a reset, the transceiver will enter in STDBY_RC mode running with a 13 MHz RC clock.
 * @warning     N/A.
 */
SX128X_status_t SetStandby ( SPI_parameters_t mySPI_parameters, SX128X_set_standby_standbyconfig_t myStandbyConfig )
{
    uint8_t      cmd[2]   =    { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]  =   SX128X_SET_STANDBY;
    cmd[1]  =   myStandbyConfig;
    aux     =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetFs ( SPI_parameters_t )
 *
 * @details     It sets the device in Frequency Synthesizer mode where the PLL is locked to the carrier frequency.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetFs.
 *
 *
 * @author      Manuel Caballero
 * @date        11/February/2019
 * @version     11/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetFs ( SPI_parameters_t mySPI_parameters )
{
    uint8_t      cmd   =    0U;
    spi_status_t aux;

    /* Send command  */
    cmd  =   SX128X_SET_FS;
    aux  =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetTx ( SPI_parameters_t , SX128X_set_tx_rx_timeout_definition_t, uint16_t )
 *
 * @details     It sets the device in Transmit mode.
 *
 *                  Time-out duration = periodBase * periodBaseCount
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myPeriodBase:      periodBase.
 * @param[in]    myperiodBaseCount: periodBaseCount.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetTx.
 *
 *
 * @author      Manuel Caballero
 * @date        12/February/2019
 * @version     12/February/2019   The ORIGIN
 * @pre         If myperiodBaseCount = 0x0000, No time-out, Tx Single mode, the device will stay in Tx Mode until the packet is
 *              transmitted and returns in STDBY_RC mode upon completion.
 * @pre         If myperiodBaseCount = Others, Time-out active. The device remains in Rx mode, it returns automatically to STDBY_RC mode
 *              on timer end-of-count or when a packet has been received. As soon as a packet is detected, the timer is automatically
 *              disabled to allow complete reception of the packet.
 * @warning     Clear IRQ status before using this command.
 */
SX128X_status_t SetTx ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myperiodBaseCount )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_TX;
    cmd[1]   =   myPeriodBase;
    cmd[2]   =   (uint8_t)( ( myperiodBaseCount & 0xFF00 ) >> 8U );
    cmd[3]   =   (uint8_t)( myperiodBaseCount & 0x00FF );
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetRx ( SPI_parameters_t , SX128X_set_tx_rx_timeout_definition_t, uint16_t )
 *
 * @details     It sets the device in Receiver mode.
 *
 *                  Time-out duration = periodBase * periodBaseCount
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myPeriodBase:      periodBase.
 * @param[in]    myperiodBaseCount: periodBaseCount.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetRx.
 *
 *
 * @author      Manuel Caballero
 * @date        12/February/2019
 * @version     12/February/2019   The ORIGIN
 * @pre         If myperiodBaseCount = 0x0000, No time-out. Rx Single mode. The device will stay in Rx mode until a
 *              reception occurs and the devices return in STDBY_RC mode upon completion.
 * @pre         If myperiodBaseCount = 0xFFFF, Rx Continuous mode. The device remains in Rx mode until the host sends
 *              a command to change the operation mode. The device can receive several packets. Each time a packet is
 *              received, a 'packet received' indication is given to the host and the device will continue to search for a new packet.
 * @pre         If myperiodBaseCount = Others, Time-out active. The device remains in Rx mode, it returns automatically to STDBY_RC mode
 *              on timer end-of-count or when a packet has been received. As soon as a packet is detected, the timer is automatically
 *              disabled to allow complete reception of the packet.
 * @warning     The IRQ status should be cleared prior to using this command.
 */
SX128X_status_t SetRx ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myperiodBaseCount )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_RX;
    cmd[1]   =   myPeriodBase;
    cmd[2]   =   (uint8_t)( ( myperiodBaseCount & 0xFF00 ) >> 8U );
    cmd[3]   =   (uint8_t)( myperiodBaseCount & 0x00FF );
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetRxDutyCycle ( SPI_parameters_t , SX128X_set_tx_rx_timeout_definition_t, uint16_t , uint16_t )
 *
 * @details     It sets the transceiver in sniff mode, so that it regularly looks for new packets ( duty cycled operation ).
 *
 *                  The Sleep mode duration is defined by:
 *
 *                      - Sleep Duration = PeriodBase * sleepPeriodBaseCount
 *
 *                  The Rx mode duration is defined by:
 *
 *                      - Rx Duration = PeriodBase * rxPeriodBaseCount
 *
 * @param[in]    mySPI_parameters:          SPI parameters.
 * @param[in]    myPeriodBase:              periodBase.
 * @param[in]    myRxPeriodBaseCount:       rxPeriodBaseCount.
 * @param[in]    mySleepPeriodBaseCount:    sleepPeriodBaseCount.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetRxDutyCycle.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         If rxPeriodBaseCount = 0x0000, The transceiver waits until a packet is found. Once found, the transceiver goes to STDBY_RC mode
 *              after sending an RxDone IRQ to the host.
 * @pre         If rxPeriodBaseCount = Others, The device will stay in Rx Mode until the end of the timer when the device returns in Sleep mode for
 *              Sleep duration.
 * @pre         If myperiodBaseCount = Others, Time-out active. The device remains in Rx mode, it returns automatically to STDBY_RC mode
 *              on timer end-of-count or when a packet has been received. As soon as a packet is detected, the timer is automatically
 *              disabled to allow complete reception of the packet.
 * @warning     The command SetLongPreamble must be issued prior to SetRxDutyCycle.
 * @warning     To use the RxDone interrupt, you have to enable the corresponding IRQ prior to enter Duty cycled operation. To enable the RxDone IRQ,
 *              refer to the command SetDioIrqParams().
 */
SX128X_status_t SetRxDutyCycle ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myRxPeriodBaseCount, uint16_t mySleepPeriodBaseCount )
{
    uint8_t      cmd[6]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_RX_DUTY_CYCLE;
    cmd[1]   =   myPeriodBase;
    cmd[2]   =   (uint8_t)( ( myRxPeriodBaseCount & 0xFF00 ) >> 8U );
    cmd[3]   =   (uint8_t)( myRxPeriodBaseCount & 0x00FF );
    cmd[4]   =   (uint8_t)( ( mySleepPeriodBaseCount & 0xFF00 ) >> 8U );
    cmd[5]   =   (uint8_t)( mySleepPeriodBaseCount & 0x00FF );
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetLongPreamble ( SPI_parameters_t , SX128X_set_long_preamble_t )
 *
 * @details     It sets the transceiver into Long Preamble mode, and can only be used with either the LoRa mode and GFSK mode.
 *
 *               - In GFSK only, the SetTx arguments do not define a timeout anymore, but the duration of the preamble part of GFSK
 *                 packet. Therefore, there is no TxTimeout interrupt generated in GFSK mode. In LoRa, SetTx behavior is not changed.
 *
 *               - In GFSK only with LongPreamble mode, the preamble detection mode is activated. The command SetRx can then
 *                 generate an interrupt for Preamble detection.
 *
 *               - In GFSK and LoRa, the behavior of RxDutyCycle is modified so that if a preamble is detected, the Rx window is
 *                 extended by SleepPeriod + 2 * RxPeriod.
 *
 *
 * @param[in]    mySPI_parameters:        SPI parameters.
 * @param[in]    myLongPreambleStatus:    Enable/Disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetLongPreamble.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetLongPreamble ( SPI_parameters_t mySPI_parameters, SX128X_set_long_preamble_t myLongPreambleStatus )
{
    uint8_t      cmd[2]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_LONG_PREAMBLE;
    cmd[1]   =   myLongPreambleStatus;
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetCAD ( SPI_parameters_t )
 *
 * @details     ( Channel Activity Detection ) can be used only in LoRa packet type. The Channel Activity Detection is a LoRa specific mode of operation
 *              where the device searches for a LoRa signal. After search has completed, the device returns to STDBY_RC mode. The length of the search is
 *              configured via SetCadParams() command. At the end of search period the device always sends the CadDone IRQ. If a valid signal has been
 *              detected it also generates the CadDetected IRQ.
 *
 *              This mode of operation is especially useful in all the applications requiring Listen before Talk.
 *
 *
 * @param[in]    mySPI_parameters:        SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetCAD.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetCAD ( SPI_parameters_t mySPI_parameters )
{
    uint8_t      cmd  =   0U;
    spi_status_t aux;

    /* Send command  */
    cmd   =   SX128X_SET_CAD;
    aux   =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetTxContinuousWave ( SPI_parameters_t )
 *
 * @details     It is a test command to generate a Continuous Wave (RF tone) at a selected frequency and output power.
 *              The device remains in Tx Continuous Wave until the host sends a mode configuration command. This
 *              command is available for all packet types.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetTxContinuousWave.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetTxContinuousWave ( SPI_parameters_t mySPI_parameters )
{
    uint8_t      cmd  =   0U;
    spi_status_t aux;

    /* Send command  */
    cmd   =   SX128X_SET_TX_CONTINUOUS_WAVE;
    aux   =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetTxContinuousPreamble ( SPI_parameters_t )
 *
 * @details     It is a test command to generate an infinite sequence of alternating '0's and '1's in GFSK,
 *              BLE, or FLRC modulation and symbol 0 in LoRa. The device remains in Tx Continuous Wave until
 *              the host sends a mode configuration command
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetTxContinuousPreamble.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetTxContinuousPreamble ( SPI_parameters_t mySPI_parameters )
{
    uint8_t      cmd  =   0U;
    spi_status_t aux;

    /* Send command  */
    cmd   =   SX128X_SET_TX_CONTINUOUS_PREAMBLE;
    aux   =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetAutoTx ( SPI_parameters_t , uint16_t )
 *
 * @details     BLE requires the transceiver to be able to send back a response 150us after a packet reception.
 *              This is carried out by sending the command SetAutoTx() which allows the transceiver to send a packet
 *              at a user programmable time ( time ) after the end of a packet reception. SetAutoTx() must be issued in STDBY_RC mode.
 *
 *              time is expressed in us. The delay between the packet reception end and the next packet transmission start is defined by:
 *
 *                  - Tx_Delay =  time + Offset
 *
 *              Here Offset is a time needed for the transceiver to switch modes and is equal to 33us. When this command is issued, each
 *              time the transceiver goes in Rx mode, it automatically switches to Tx and sends a packet in a predefined time TxDelay. To
 *              resume STDBY_RC after Rx, the command SetAutoTx is issued with 0x00 as time argument.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myTime:            Time.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetAutoTx.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetAutoTx ( SPI_parameters_t mySPI_parameters, uint16_t myTime )
{
    uint8_t      cmd[3]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_AUTO_TX;
    cmd[2]   =   (uint8_t)( ( myTime & 0xFF00 ) >> 8U );
    cmd[3]   =   (uint8_t)( myTime & 0x00FF );
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       SetAutoFs ( SPI_parameters_t , SX128X_set_auto_fs_t )
 *
 * @details     This feature modifies the chip behavior so that the state following a Rx or Tx operation is FS and not STDBY.
 *              This feature is to be used to reduce the switching time between consecutive Rx and/or Tx operations.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myAutoFsStatus:    Time.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetAutoFs.
 *
 *
 * @author      Manuel Caballero
 * @date        13/February/2019
 * @version     13/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetAutoFs ( SPI_parameters_t mySPI_parameters, SX128X_set_auto_fs_t myAutoFsStatus )
{
    uint8_t      cmd[2]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_AUTO_FS;
    cmd[2]   =   myAutoFsStatus;
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}
