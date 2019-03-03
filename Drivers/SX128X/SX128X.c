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
    cmd[1]   =   (uint8_t)( ( myTime & 0xFF00 ) >> 8U );
    cmd[2]   =   (uint8_t)( myTime & 0x00FF );
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
    cmd[1]   =   myAutoFsStatus;
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
 * @brief       SetPacketType ( SPI_parameters_t , SX128X_set_packet_time_t )
 *
 * @details     It sets the transceiver radio frame out of a choice of 6 different packet types.
 *              Despite some of them using the same physical modem, they do not all share the same parameters.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myPacketType:      Packet type.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetPacketType.
 *
 *
 * @author      Manuel Caballero
 * @date        14/February/2019
 * @version     14/February/2019   The ORIGIN
 * @pre         Changing from one mode of operation to another is performed by sending the SetPacketType() command.
 *              The parameters from the previous mode are not kept internally. The transition must be performed in STDBY_RC mode.
 * @warning     The command SetPacketType() must be the first in a radio configuration sequence.
 */
SX128X_status_t SetPacketType ( SPI_parameters_t mySPI_parameters, SX128X_set_packet_time_t myPacketType )
{
    uint8_t      cmd[2]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_PACKET_TYPE;
    cmd[1]   =   myPacketType;
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
 * @brief       GetPacketType ( SPI_parameters_t , SX128X_data_t* )
 *
 * @details     It returns the current operating packet type of the radio.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   myPacketType:      Packet type.
 * @param[out]   myStatus:          Transceiver status.
 *
 *
 * @return       Status of GetPacketType.
 *
 *
 * @author      Manuel Caballero
 * @date        14/February/2019
 * @version     14/February/2019   The ORIGIN
 * @pre         It returns the transceiver status as well.
 * @warning     N/A.
 */
SX128X_status_t GetPacketType ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myPacketType )
{
    uint8_t      cmd[2]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_GET_PACKET_TYPE;
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data    */
    myPacketType->status     =   cmd[0];
    myPacketType->packetType =   (SX128X_set_packet_time_t)cmd[1];



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
 * @brief       SetRfFrequency ( SPI_parameters_t , uint32_t )
 *
 * @details     It is used to set the frequency of the RF frequency mode.
 *
 *                  F_RF = ( F_Xosc / 2^8 ) * rfFrequency
 *
 *              Note:
 *                  - F_Xosc = 52MHz ( PLL frequency is derived from the external crystal oscillator )
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myRfFrequency:     Frequency.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetRfFrequency.
 *
 *
 * @author      Manuel Caballero
 * @date        14/February/2019
 * @version     14/February/2019   The ORIGIN
 * @pre         myRfFrequency is 24-bit number.
 * @warning     N/A.
 */
SX128X_status_t SetRfFrequency ( SPI_parameters_t mySPI_parameters, uint32_t myRfFrequency )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;


    /* Check if the data is correct  */
    if ( myRfFrequency > 16777215 )
    {
        return   SX128X_FAILURE;
    }
    else
    {
        /* Send command  */
        cmd[0]   =   SX128X_SET_RF_FREQUENCY;
        cmd[1]   =   (uint8_t)( ( myRfFrequency >> 16U ) & 0xFF );
        cmd[2]   =   (uint8_t)( ( myRfFrequency >> 8U ) & 0xFF );
        cmd[4]   =   (uint8_t)( myRfFrequency & 0xFF );
        aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 1U );
    }




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
 * @brief       SetTxParams ( SPI_parameters_t , uint8_t , SX128X_set_tx_params_ramp_time_time_t )
 *
 * @details     It sets the Tx output power using parameter power and the Tx ramp time using parameter rampTime.
 *              This command is available for all packetType.
 *
 *              The output power ( P_out ) is defined by parameter power:
 *
 *                  - P_out = - 18 + power
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myPower:           SPI parameters.
 * @param[in]    myRampTime:        SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetTxParams.
 *
 *
 * @author      Manuel Caballero
 * @date        15/February/2019
 * @version     15/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetTxParams ( SPI_parameters_t mySPI_parameters, uint8_t myPower, SX128X_set_tx_params_ramp_time_time_t myRampTime )
{
    uint8_t      cmd[3]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_TX_PARAMS;
    cmd[1]   =   myPower;
    cmd[2]   =   myRampTime;
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
 * @brief       SetCadParams ( SPI_parameters_t , SX128X_set_cad_params_cad_symbol_num_t )
 *
 * @details     It defines the number of symbols on which Channel Activity Detected ( CAD ) operates.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myCadSymbolNum:    CAD symbol number.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetCadParams.
 *
 *
 * @author      Manuel Caballero
 * @date        15/February/2019
 * @version     15/February/2019   The ORIGIN
 * @pre         For symbols 1 and 2, there are higher risks of false detection.
 * @warning     N/A.
 */
SX128X_status_t SetCadParams ( SPI_parameters_t mySPI_parameters, SX128X_set_cad_params_cad_symbol_num_t myCadSymbolNum )
{
    uint8_t      cmd[2]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_CAD_PARAMS;
    cmd[1]   =   myCadSymbolNum;
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
 * @brief       SetBufferBaseAddress ( SPI_parameters_t , uint8_t , uint8_t )
 *
 * @details     It fixes the base address for the packet handing operation in Tx and Rx mode for all packet types.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myTxBaseAdress:    Tx base address.
 * @param[in]    myRxBaseAdress:    Rx base address.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetBufferBaseAddress.
 *
 *
 * @author      Manuel Caballero
 * @date        15/February/2019
 * @version     15/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetBufferBaseAddress ( SPI_parameters_t mySPI_parameters, uint8_t myTxBaseAdress, uint8_t myRxBaseAdress )
{
    uint8_t      cmd[3]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_BUFFER_BASE_ADDRESS;
    cmd[1]   =   myTxBaseAdress;
    cmd[2]   =   myRxBaseAdress;
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
 * @brief       SetModulationParams_GFSK_BLE ( SPI_parameters_t , SX128X_modulation_parameter_gfsk_ble_modparam1_t , SX128X_modulation_parameter_gfsk_ble_modparam2_t , SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t )
 *
 * @details     It configures the modulation parameters of the radio ( GFSK and BLE mode ).
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myModParam1:       BitrateBandwidth.
 * @param[in]    myModParam2:       ModulationIndex.
 * @param[in]    myModParam3:       ModulationShaping.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetModulationParams_GFSK_BLE.
 *
 *
 * @author      Manuel Caballero
 * @date        19/February/2019
 * @version     19/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetModulationParams_GFSK_BLE ( SPI_parameters_t mySPI_parameters, SX128X_modulation_parameter_gfsk_ble_modparam1_t myModParam1, SX128X_modulation_parameter_gfsk_ble_modparam2_t myModParam2, SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t myModParam3 )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_MODULATION_PARAMS;
    cmd[1]   =   myModParam1;
    cmd[2]   =   myModParam2;
    cmd[3]   =   myModParam3;
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
 * @brief       SetModulationParams_FLRC ( SPI_parameters_t , SX128X_modulation_parameter_flrc_modparam1_t , SX128X_modulation_parameter_flrc_modparam2_t , SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t )
 *
 * @details     It configures the modulation parameters of the radio ( FLRC mode ).
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myModParam1:       BitrateBandwidth.
 * @param[in]    myModParam2:       CodingRate.
 * @param[in]    myModParam3:       ModulationShaping.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetModulationParams_FLRC.
 *
 *
 * @author      Manuel Caballero
 * @date        19/February/2019
 * @version     19/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetModulationParams_FLRC ( SPI_parameters_t mySPI_parameters, SX128X_modulation_parameter_flrc_modparam1_t myModParam1, SX128X_modulation_parameter_flrc_modparam2_t myModParam2, SX128X_modulation_parameter_gfsk_ble_flrc_modparam3_t myModParam3 )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_MODULATION_PARAMS;
    cmd[1]   =   myModParam1;
    cmd[2]   =   myModParam2;
    cmd[3]   =   myModParam3;
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
 * @brief       SetModulationParams_LORA ( SPI_parameters_t , SX128X_modulation_parameter_lora_modparam1_t , SX128X_modulation_parameter_lora_modparam2_t , SX128X_modulation_parameter_lora_modparam3_t )
 *
 * @details     It configures the modulation parameters of the radio ( LoRa mode ).
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myModParam1:       SpreadingFactor.
 * @param[in]    myModParam2:       Bandwidth.
 * @param[in]    myModParam3:       CodingRate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetModulationParams_LORA.
 *
 *
 * @author      Manuel Caballero
 * @date        19/February/2019
 * @version     19/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetModulationParams_LORA ( SPI_parameters_t mySPI_parameters, SX128X_modulation_parameter_lora_modparam1_t myModParam1, SX128X_modulation_parameter_lora_modparam2_t myModParam2, SX128X_modulation_parameter_lora_modparam3_t myModParam3 )
{
    uint8_t      cmd[4]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_MODULATION_PARAMS;
    cmd[1]   =   myModParam1;
    cmd[2]   =   myModParam2;
    cmd[3]   =   myModParam3;
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
 * @brief       SetPacketParams_GFSK ( SPI_parameters_t , SX128X_packet_param1_preamble_length_t , SX128X_packet_param2_sync_word_length_t , SX128X_packet_param3_sync_word_match_t , SX128X_packet_param4_header_type_t , uint8_t , SX128X_packet_param6_crc_length_t , SX128X_packet_param7_whitening_t )
 *
 * @details     It sets the parameters of the packet handling block ( GFSK mode ).
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myPreambleLength:  Preamble Length     ( SetPacketParam1 ).
 * @param[in]    mySyncWordLength:  Sync Word Length    ( SetPacketParam2 ).
 * @param[in]    mySyncWordMatch:   Sync Word Match     ( SetPacketParam3 ).
 * @param[in]    myHeaderType:      Header Type         ( SetPacketParam4 ).
 * @param[in]    myPayloadLength:   Payload Length      ( SetPacketParam5 ).
 * @param[in]    myCrcLength:       CRC Length          ( SetPacketParam6 ).
 * @param[in]    myWhitening:       Whitening           ( SetPacketParam7 ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetPacketParams_GFSK.
 *
 *
 * @author      Manuel Caballero
 * @date        23/February/2019
 * @version     23/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetPacketParams_GFSK ( SPI_parameters_t mySPI_parameters, SX128X_packet_param1_preamble_length_t myPreambleLength, SX128X_packet_param2_sync_word_length_t mySyncWordLength, SX128X_packet_param3_sync_word_match_t mySyncWordMatch, SX128X_packet_param4_header_type_t myHeaderType, uint8_t myPayloadLength, SX128X_packet_param6_crc_length_t myCrcLength, SX128X_packet_param7_whitening_t myWhitening )
{
    uint8_t      cmd[8]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_PACKET_PARAMS;
    cmd[1]   =   myPreambleLength;
    cmd[2]   =   mySyncWordLength;
    cmd[3]   =   mySyncWordMatch;
    cmd[4]   =   myHeaderType;
    cmd[5]   =   myPayloadLength;
    cmd[6]   =   myCrcLength;
    cmd[7]   =   myWhitening;
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
 * @brief       SetPacketParams_FLRC ( SPI_parameters_t , SX128X_packet_param1_preamble_length_t , SX128X_packet_param2_sync_word_length_t , SX128X_packet_param3_sync_word_match_t , SX128X_packet_param4_header_type_t , uint8_t , SX128X_packet_param6_crc_length_t , SX128X_packet_param7_whitening_t )
 *
 * @details     It sets the parameters of the packet handling block ( FLRC mode ).
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myPreambleLength:  Preamble Length     ( SetPacketParam1 ).
 * @param[in]    mySyncWordLength:  Sync Word Length    ( SetPacketParam2 ).
 * @param[in]    mySyncWordMatch:   Sync Word Match     ( SetPacketParam3 ).
 * @param[in]    myHeaderType:      Header Type         ( SetPacketParam4 ).
 * @param[in]    myPayloadLength:   Payload Length      ( SetPacketParam5 ).
 * @param[in]    myCrcLength:       CRC Length          ( SetPacketParam6 ).
 * @param[in]    myWhitening:       Whitening           ( SetPacketParam7 ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetPacketParams_FLRC.
 *
 *
 * @author      Manuel Caballero
 * @date        23/February/2019
 * @version     23/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t SetPacketParams_FLRC ( SPI_parameters_t mySPI_parameters, SX128X_packet_param1_preamble_length_t myPreambleLength, SX128X_packet_param2_sync_word_length_t mySyncWordLength, SX128X_packet_param3_sync_word_match_t mySyncWordMatch, SX128X_packet_param4_header_type_t myHeaderType, uint8_t myPayloadLength, SX128X_packet_param6_crc_length_t myCrcLength, SX128X_packet_param7_whitening_t myWhitening )
{
    uint8_t      cmd[8]  =   { 0U };
    spi_status_t aux;

    /* myPayloadLength must be [ 6:127 ]   */
    if ( ( myPayloadLength < 6U ) || ( myPayloadLength > 127U ) )
    {
        return SX128X_FAILURE;
    }
    else
    {
        /* Send command  */
        cmd[0]   =   SX128X_SET_PACKET_PARAMS;
        cmd[1]   =   myPreambleLength;
        cmd[2]   =   mySyncWordLength;
        cmd[3]   =   mySyncWordMatch;
        cmd[4]   =   myHeaderType;
        cmd[5]   =   myPayloadLength;
        cmd[6]   =   myCrcLength;
        cmd[7]   =   myWhitening;
        aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );
    }



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
 * @brief       SetPacketParams_BLE ( SPI_parameters_t , SX128X_packet_param1_connection_state_t , SX128X_packet_param2_crc_t , SX128X_packet_param3_ble_test_payload_t , SX128X_packet_param4_whitening_t )
 *
 * @details     It sets the parameters of the packet handling block ( BLE mode ).
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 * @param[in]    myConnectionState: Connection State    ( SetPacketParam1 ).
 * @param[in]    myCrcLength:       CRC Length          ( SetPacketParam2 ).
 * @param[in]    myBleTestPayload:  BLE Test Payload    ( SetPacketParam3 ).
 * @param[in]    myWhitening:       Whitening           ( SetPacketParam4 ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetPacketParams_BLE.
 *
 *
 * @author      Manuel Caballero
 * @date        23/February/2019
 * @version     23/February/2019   The ORIGIN
 * @pre         SetPacketParam5, SetPacketParam6 and SetPacketParam7 are NOT used.
 * @warning     N/A.
 */
SX128X_status_t SetPacketParams_BLE ( SPI_parameters_t mySPI_parameters, SX128X_packet_param1_connection_state_t myConnectionState, SX128X_packet_param2_crc_t myCrcLength, SX128X_packet_param3_ble_test_payload_t myBleTestPayload, SX128X_packet_param4_whitening_t myWhitening )
{
    uint8_t      cmd[8]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_SET_PACKET_PARAMS;
    cmd[1]   =   myConnectionState;
    cmd[2]   =   myCrcLength;
    cmd[3]   =   myBleTestPayload;
    cmd[4]   =   myWhitening;
    cmd[5]   =   0x00;                          // Not used
    cmd[6]   =   0x00;                          // Not used
    cmd[7]   =   0x00;                          // Not used
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
 * @brief       SetPacketParams_LORA ( SPI_parameters_t , uint8_t , uint8_t , SX128X_packet_param2_header_type_t , uint8_t , SX128X_packet_param4_lora_crc_t , SX128X_packet_param5_lora_iq_t )
 *
 * @details     It sets the parameters of the packet handling block ( LoRa and Ranging Engine mode ).
 *
 *
 * @param[in]    mySPI_parameters:      SPI parameters.
 * @param[in]    myLORA_PBLE_LEN_MANT:  Connection State    ( SetPacketParam1 ).
 * @param[in]    myLORA_PBLE_LEN_EXP:   CRC Length          ( SetPacketParam1 ).
 * @param[in]    myHeaderType:          BLE Test Payload    ( SetPacketParam2 ).
 * @param[in]    myPayloadLength:       Whitening           ( SetPacketParam3 ).
 * @param[in]    myCRC:                 Whitening           ( SetPacketParam4 ).
 * @param[in]    myInvertIQ:            Whitening           ( SetPacketParam5 ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SetPacketParams_LORA.
 *
 *
 * @author      Manuel Caballero
 * @date        23/February/2019
 * @version     23/February/2019   The ORIGIN
 * @pre         SetPacketParam6 and SetPacketParam7 are NOT used.
 * @warning     N/A.
 */
SX128X_status_t SetPacketParams_LORA ( SPI_parameters_t mySPI_parameters, uint8_t myLORA_PBLE_LEN_MANT, uint8_t myLORA_PBLE_LEN_EXP, SX128X_packet_param2_header_type_t myHeaderType, uint8_t myPayloadLength, SX128X_packet_param4_lora_crc_t myCRC, SX128X_packet_param5_lora_iq_t myInvertIQ )
{
    uint8_t      cmd[8]  =   { 0U };
    spi_status_t aux;

    /* myLORA_PBLE_LEN_MANT and myLORA_PBLE_LEN_EXP must be [ 1:15 ]   */
    if ( ( ( myLORA_PBLE_LEN_MANT < 1U ) || ( myLORA_PBLE_LEN_MANT > 15U ) ) || ( ( myLORA_PBLE_LEN_EXP < 1U ) || ( myLORA_PBLE_LEN_EXP > 15U ) ) )
    {
        return SX128X_FAILURE;
    }
    else
    {
        /* Send command  */
        cmd[0]   =   SX128X_SET_PACKET_PARAMS;
        cmd[1]   =   myLORA_PBLE_LEN_EXP;
        cmd[1] <<=   4U;
        cmd[1]  |=   myLORA_PBLE_LEN_MANT;
        cmd[2]   =   myHeaderType;
        cmd[3]   =   myPayloadLength;
        cmd[4]   =   myCRC;
        cmd[5]   =   myInvertIQ;
        cmd[6]   =   0x00;                          // Not used
        cmd[7]   =   0x00;                          // Not used
        aux      =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );
    }



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
 * @brief       GetRxBufferStatus ( SPI_parameters_t , SX128X_data_t* )
 *
 * @details     It returns the length of the last received packet ( payloadLengthRx ) and the address of the first byte received ( rxBufferOffset ),
 *              it is applicable to all modems. The address is an offset relative to the first byte of the data buffer.
 *
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   myBufferStatus:    Status, rxPayloadLength and rxStartBufferPointer.
 *
 *
 * @return       Status of GetRxBufferStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        23/February/2019
 * @version     23/February/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX128X_status_t GetRxBufferStatus   ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myBufferStatus )
{
    uint8_t      cmd[3]  =   { 0U };
    spi_status_t aux;

    /* Send command  */
    cmd[0]   =   SX128X_GET_RX_BUFFER_STATUS;
    aux      =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data    */
    myBufferStatus->status                   =   cmd[0];
    myBufferStatus->rxPayloadLength          =   cmd[1];
    myBufferStatus->rxStartBufferPointer     =   cmd[2];



    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}

