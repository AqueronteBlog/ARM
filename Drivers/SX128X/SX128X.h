/**
 * @brief       SX128X.h
 * @details     SX1280/SX1281. Long Range, Low Power, 2.4 GHz Transceiver with Ranging Capability.
 *              Header file.
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


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/**
  * @brief   LIST OF COMMANDS
  */
typedef enum
{
  SX128X_GET_STATUS                 =   0xC0,                       /*!<  Parameters: N/A                                                                                                                                   | Return: status                                                                                                */
  SX128X_WRITE_REGISTER             =   0x18,                       /*!<  Parameters: address[15:8], address[7:0], data[0:n]                                                                                                | Return: N/A                                                                                                   */
  SX128X_READ_REGISTER              =   0x19,                       /*!<  Parameters: address[15:8], address[7:0]                                                                                                           | Return: data[0:n-1]                                                                                           */
  SX128X_WRITE_BUFFER               =   0x1A,                       /*!<  Parameters: offset,data[0:n]                                                                                                                      | Return: N/A                                                                                                   */
  SX128X_READ_BUFFER                =   0x1B,                       /*!<  Parameters: offset                                                                                                                                | Return: data[0:n-1]                                                                                           */
  SX128X_SET_SLEEP                  =   0x84,                       /*!<  Parameters: sleepConfig                                                                                                                           | Return: N/A                                                                                                   */
  SX128X_SET_STANDBY                =   0x80,                       /*!<  Parameters: standbyConfig                                                                                                                         | Return: N/A                                                                                                   */
  SX128X_SET_FS                     =   0xC1,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_TX                     =   0x83,                       /*!<  Parameters: periodBase, periodBaseCount[15:8], periodBaseCount[7:0]                                                                               | Return: N/A                                                                                                   */
  SX128X_SET_RX                     =   0x82,                       /*!<  Parameters: periodBase, periodBaseCount[15:8], periodBaseCount[7:0]                                                                               | Return: N/A                                                                                                   */
  SX128X_SET_RX_DUTY_CYCLE          =   0x94,                       /*!<  Parameters: rxPeriodBase, rxPeriodBaseCount[15:8], rxPeriodBaseCount[7:0], sleepPeriodBase, sleepPeriodBaseCount[15:8], sleepPeriodBaseCount[7:0] | Return: N/A                                                                                                   */
  SX128X_SET_CAD                    =   0xC5,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_TX_CONTINUOUS_WAVE     =   0xD1,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_TX_CONTINUOUS_PREAMBLE =   0xD2,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_PACKET_TYPE            =   0x8A,                       /*!<  Parameters: packetType                                                                                                                            | Return: N/A                                                                                                   */
  SX128X_GET_PACKET_TYPE            =   0x03,                       /*!<  Parameters: N/A                                                                                                                                   | Return: packetType                                                                                            */
  SX128X_SET_RF_FREQUENCY           =   0x86,                       /*!<  Parameters: rfFrequency[23:16],rfFrequency[15:8], rfFrequency[7:0]                                                                                | Return: N/A                                                                                                   */
  SX128X_SET_TX_PARAMS              =   0x8E,                       /*!<  Parameters: power, rampTime                                                                                                                       | Return: N/A                                                                                                   */
  SX128X_SET_CAD_PARAMS             =   0x88,                       /*!<  Parameters: cadSymbolNum                                                                                                                          | Return: N/A                                                                                                   */
  SX128X_SET_BUFFER_BASE_ADDRESS    =   0x8F,                       /*!<  Parameters: txBaseAddress, rxBaseAddress                                                                                                          | Return: N/A                                                                                                   */
  SX128X_SET_MODULATION_PARAMS      =   0x8B,                       /*!<  Parameters: modParam1, modParam2, modParam3                                                                                                       | Return: N/A                                                                                                   */
  SX128X_SET_PACKET_PARAMS          =   0x8C,                       /*!<  Parameters: packetParam1, packetParam2, packetParam3, packetParam4, packetParam5, packetParam6, packetParam7                                      | Return: N/A                                                                                                   */
  SX128X_GET_RX_BUFFER_STATUS       =   0x17,                       /*!<  Parameters: N/A                                                                                                                                   | Return: payloadLength, rxBufferOffset                                                                         */
  SX128X_GET_PACKET_STATUS          =   0x1D,                       /*!<  Parameters: N/A                                                                                                                                   | Return: packetStatus[39:32], packetStatus[31:24], packetStatus[23:16], packetStatus[15:8], packetStatus[7:0]  */
  SX128X_GET_RSSI_INST              =   0x1F,                       /*!<  Parameters: N/A                                                                                                                                   | Return: rssiInst                                                                                              */
  SX128X_SET_DIO_IRQ_PARAMS         =   0x8D,                       /*!<  Parameters: irqMask[15:8], irqMask[7:0], dio1Mask[15:8],dio1Mask[7:0], dio2Mask[15:8], dio2Mask[7:0], dio3Mask[15:8], dio3Mask[7:0]               | Return: N/A                                                                                                   */
  SX128X_GET_IRQ_STATUS             =   0x15,                       /*!<  Parameters: N/A                                                                                                                                   | Return: irqStatus[15:8], irqStatus[7:0]                                                                       */
  SX128X_CLR_IRQ_STATUS             =   0x97,                       /*!<  Parameters: irqMask[15:8], irqMask[7:0]                                                                                                           | Return: N/A                                                                                                   */
  SX128X_SET_REGULATOR_MODE         =   0x96,                       /*!<  Parameters: regulatorMode                                                                                                                         | Return: N/A                                                                                                   */
  SX128X_SET_SAVE_CONTEXT           =   0xD5,                       /*!<  Parameters: N/A                                                                                                                                   | Return: N/A                                                                                                   */
  SX128X_SET_AUTO_FS                =   0x9E,                       /*!<  Parameters: 0x00: disable or 0x01: enable                                                                                                         | Return: N/A                                                                                                   */
  SX128X_SET_AUTO_TX                =   0x98,                       /*!<  Parameters: time                                                                                                                                  | Return: N/A                                                                                                   */
  SX128X_SET_PERF_COUNTER_MODE      =   0x9C,                       /*!<  Parameters: perfCounterMode                                                                                                                       | Return: N/A                                                                                                   */
  SX128X_SET_LONG_PREAMBLE          =   0x9B,                       /*!<  Parameters: enable                                                                                                                                | Return: N/A                                                                                                   */
  SX128X_SET_UART_SPEED             =   0x9D,                       /*!<  Parameters: uartSpeed                                                                                                                             | Return: N/A                                                                                                   */
  SX128X_SET_RANGING_ROLE           =   0xA3                        /*!<  Parameters: 0x00=Slave or 0x01=Master                                                                                                             | Return: N/A                                                                                                   */
} SX128X_commands_t;



/**
  * @brief   GET_STATUS
  */
/* CIRCUIT_MODE <7:5>: CIRCUIT MODE
 *    NOTE: N/A.
 */
typedef enum
{
    GET_STATUS_CIRCUIT_MODE_MASK       =   ( 0b111 << 5U ),             /*!<  CIRCUIT_MODE mask                                   */
    GET_STATUS_CIRCUIT_MODE_STDBY_RC   =   ( 0x02  << 5U ),             /*!<  CIRCUIT_MODE: STDBY_RC                              */
    GET_STATUS_CIRCUIT_MODE_STDBY_XOSC =   ( 0x03  << 5U ),             /*!<  CIRCUIT_MODE: STDBY_XOSC                            */
    GET_STATUS_CIRCUIT_MODE_FS         =   ( 0x04  << 5U ),             /*!<  CIRCUIT_MODE: FS                                    */
    GET_STATUS_CIRCUIT_MODE_RX         =   ( 0x05  << 5U ),             /*!<  CIRCUIT_MODE: RX                                    */
    GET_STATUS_CIRCUIT_MODE_TX         =   ( 0x06  << 5U )              /*!<  CIRCUIT_MODE: TX                                    */
} SX128X_get_status_circuit_mode_t;



/* COMMAND_STATUS <4:2>: COMMAND STATUS
 *    NOTE: N/A.
 */
typedef enum
{
    GET_STATUS_COMMAND_STATUS_MASK                                              =   ( 0b111 << 2U ),  /*!<  COMMAND_STATUS mask                                                                             */
    GET_STATUS_COMMAND_STATUS_TRANSCEIVER_HAS_SUCCESSFULLY_PROCESSED_COMMAND    =   ( 0x01  << 2U ),  /*!<  The command has been terminated correctly                                                       */
    GET_STATUS_COMMAND_STATUS_DATA_ARE_AVAILABLE_TO_HOST                        =   ( 0x02  << 2U ),  /*!<  A packet has been successfully received and data can be retrieved                               */
    GET_STATUS_COMMAND_STATUS_COMMAND_TIMEOUT                                   =   ( 0x03  << 2U ),  /*!<  A transaction from the host took too long to complete and triggered an internal watchdog        */
    GET_STATUS_COMMAND_STATUS_COMMAND_PROCESSING_ERROR                          =   ( 0x04  << 2U ),  /*!<  The transceiver was unable to process command                                                   */
    GET_STATUS_COMMAND_STATUS_FAILURE_TO_EXECUTE_COMMAND                        =   ( 0x05  << 2U ),  /*!<  The command was successfully processed, however the transceiver could not execute the command   */
    GET_STATUS_COMMAND_STATUS_COMMAND_TX_DONE                                   =   ( 0x06  << 2U )   /*!<  The transmission of the current packet has terminated                                           */
} SX128X_get_status_command_status_t;



/* BUSY <0>: BUSY
 *    NOTE: N/A.
 */
typedef enum
{
    GET_STATUS_BUSY_MASK                =   ( 0b1 << 0U ),                      /*!<  BUSY mask                                                     */
    GET_STATUS_BUSY_BUSY                =   ( 0b1 << 0U ),                      /*!<  Transceiver is processing command or doing internal operation */
    GET_STATUS_BUSY_NOT_BUSY            =   ( 0b0 << 0U )                       /*!<  Transceiver is released                                       */
} SX128X_get_status_busy_t;



/**
  * @brief   SET_SLEEP
  */
/* SLEEP CONFIG 0 <0>: DATA RAM
 *    NOTE: N/A.
 */
typedef enum
{
    SET_SLEEP_SLEEP_CONFIG0_MASK                                =   ( 0b1 << 0U ),   /*!<  SleepConfig[0] mask                                           */
    SET_SLEEP_SLEEP_CONFIG0_DATA_RAM_FLUSHED                    =   ( 0b0 << 0U ),   /*!<  SleepConfig[0] Data RAM is flushed during Sleep Mode          */
    SET_SLEEP_SLEEP_CONFIG0_DATA_RAM_IN_RETENTION_MODE          =   ( 0b1 << 0U )    /*!<  SleepConfig[0] Data RAM in retention mode                     */
} SX128X_set_sleep_sleep_config0_t;



/* SLEEP CONFIG 1 <1>: DATA BUFFER
 *    NOTE: N/A.
 */
typedef enum
{
    SET_SLEEP_SLEEP_CONFIG1_MASK                                =   ( 0b1 << 1U ),  /*!<  SleepConfig[1] mask                                           */
    SET_SLEEP_SLEEP_CONFIG1_DATA_BUFFER_FLUSHED                 =   ( 0b0 << 1U ),  /*!<  SleepConfig[1] Data buffer is flushed during Sleep Mode       */
    SET_SLEEP_SLEEP_CONFIG1_DATA_BUFFER_IN_RETENTION_MODE       =   ( 0b1 << 1U )   /*!<  SleepConfig[1] Data buffer in retention mode                  */
} SX128X_set_sleep_sleep_config1_t;



/* SLEEP CONFIG 2 <2>: INSTRUCTION RAM
 *    NOTE: N/A.
 */
typedef enum
{
    SET_SLEEP_SLEEP_CONFIG2_MASK                                =   ( 0b1 << 2U ),  /*!<  SleepConfig[2] mask                                           */
    SET_SLEEP_SLEEP_CONFIG2_INSTRUCTION_RAM_FLUSHED             =   ( 0b0 << 2U ),  /*!<  SleepConfig[2] Instruction RAM is flushed during Sleep Mode   */
    SET_SLEEP_SLEEP_CONFIG2_INSTRUCTION_RAM_IN_RETENTION_MODE   =   ( 0b1 << 2U )   /*!<  SleepConfig[2] Instruction RAM in retention mode              */
} SX128X_set_sleep_sleep_config2_t;



/**
  * @brief   SET_STANDBY
  */
/* STANDBYCONFIG <0>
 *    NOTE: N/A.
 */
typedef enum
{
    SET_STANDBY_MASK                                            =   ( 0b1 << 0U ),  /*!<  StandbyConfig mask                                            */
    SET_STANDBY_STANDBY_CONFIG_STDBY_RC                         =   ( 0b0 << 0U ),  /*!<  Device running on RC 13MHz, set STDBY_RC mode                 */
    SET_STANDBY_STANDBY_CONFIG_STDBY_XOSC                       =   ( 0b1 << 0U )   /*!<  Device running on XTAL 52MHz, set STDBY_XOSC mode             */
} SX128X_set_standby_standbyconfig_t;



/**
  * @brief   SET_TX/SET_RX
  */
/* TIME-OUT DEFINITION <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_TX_RX_TIMEOUT_STEP_MASK                                 =   0xFF,           /*!<  Time-out step mask                                            */
    SET_TX_RX_TIMEOUT_STEP_15_625_US                            =   0x00,           /*!<  Time-out step: 15.625us                                       */
    SET_TX_RX_TIMEOUT_STEP_62_5_US                              =   0x01,           /*!<  Time-out step: 62.5us                                         */
    SET_TX_RX_TIMEOUT_STEP_1_MS                                 =   0x02,           /*!<  Time-out step:  1ms                                           */
    SET_TX_RX_TIMEOUT_STEP_4_MS                                 =   0x03            /*!<  Time-out step:  4ms                                           */
} SX128X_set_tx_rx_timeout_definition_t;



/**
  * @brief   SET_LONG_PREAMBLE
  */
/* ENABLE/DISABLE <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_LONG_PREAMBLE_MASK                                      =   0x01,           /*!<  Long preamble mask                                            */
    SET_LONG_PREAMBLE_ENABLE                                    =   0x01,           /*!<  Long preamble: Enabled                                        */
    SET_LONG_PREAMBLE_DISABLE                                   =   0x00            /*!<  Long preamble: Disabled                                       */
} SX128X_set_long_preamble_t;



/**
  * @brief   SET_AUTO_FS
  */
/* ENABLE/DISABLE <7:0>:
 *    NOTE: N/A.
 */
typedef enum
{
    SET_AUTO_FS_MASK                                            =   0x01,           /*!<  Auto FS mask                                                  */
    SET_AUTO_FS_ENABLE                                          =   0x01,           /*!<  Auto FS: Enabled                                              */
    SET_AUTO_FS_DISABLE                                         =   0x00            /*!<  Auto FS: Disabled                                             */
} SX128X_set_auto_fs_t;



/**
  * @brief   SET_PACKET_TIME
  */
/* PACKET TYPE DEFINITION <7:0>: MODEM MODE OF OPERATION
 *    NOTE: N/A.
 */
typedef enum
{
    SET_PACKET_TIME_MASK                                        =   0x0F,           /*!<  Packet type mask                                              */
    SET_PACKET_TIME_PACKET_TYPE_GFSK                            =   0x00,           /*!<  Packet type: GFSK mode                              [default] */
    SET_PACKET_TIME_PACKET_TYPE_LORA                            =   0x01,           /*!<  Packet type: LoRa mode                                        */
    SET_PACKET_TIME_PACKET_TYPE_RANGING                         =   0x02,           /*!<  Packet type: Ranging Engine mode                              */
    SET_PACKET_TIME_PACKET_TYPE_FLRC                            =   0x03,           /*!<  Packet type: FLRC mode                                        */
    SET_PACKET_TIME_PACKET_TYPE_BLE                             =   0x04            /*!<  Packet type: BLE mode                                         */
} SX128X_set_packet_time_t;









#ifndef SX128X_VECTOR_STRUCT_H
#define SX128X_VECTOR_STRUCT_H
typedef struct
{
    uint8_t                     status;             /*!<  Status            */

    SX128X_set_packet_time_t    packetType;         /*!<  Packet type       */
} SX128X_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SX128X_SUCCESS     =       0,
    SX128X_FAILURE     =       1
} SX128X_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
  */
SX128X_status_t  SX128X_Init                ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It gets the transceiver status.
  */
SX128X_status_t  GetStatus                  ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myStatus                                                                                                                        );

// WriteCommand, ReadCommand, WriteBuffer, ReadBuffer

/** It sets the transceiver to Sleep mode with the lowest current consumption possible.
  */
SX128X_status_t  SetSleep                   ( SPI_parameters_t mySPI_parameters, SX128X_set_sleep_sleep_config0_t myDataRAM, SX128X_set_sleep_sleep_config1_t myDataBuffer, SX128X_set_sleep_sleep_config2_t myInstructionRAM   );

/** It sets the transceiver to Stand-by mode.
  */
SX128X_status_t  SetStandby                 ( SPI_parameters_t mySPI_parameters, SX128X_set_standby_standbyconfig_t myStandbyConfig                                                                                             );

/** It sets the device in Frequency Synthesizer mode where the PLL is locked to the carrier frequency.
  */
SX128X_status_t  SetFs                      ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It sets the device in Transmit mode.
  */
SX128X_status_t  SetTx                      ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myperiodBaseCount                                                                 );

/** It sets the device in Receiver mode.
  */
SX128X_status_t  SetRx                      ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myperiodBaseCount                                                                 );

/** It sets the transceiver in sniff mode, so that it regularly looks for new packets ( duty cycled operation ).
  */
SX128X_status_t  SetRxDutyCycle             ( SPI_parameters_t mySPI_parameters, SX128X_set_tx_rx_timeout_definition_t myPeriodBase, uint16_t myRxPeriodBaseCount, uint16_t mySleepPeriodBaseCount                              );

/** It sets the transceiver into Long Preamble mode, and can only be used with either the LoRa mode and GFSK mode.
  */
SX128X_status_t  SetLongPreamble            ( SPI_parameters_t mySPI_parameters, SX128X_set_long_preamble_t myLongPreambleStatus                                                                                                );

/** ( Channel Activity Detection ) can be used only in LoRa packet type. The Channel Activity Detection is a LoRa specific mode of operation where the device searches for a LoRa.
  */
SX128X_status_t  SetCAD                     ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It is a test command to generate a Continuous Wave (RF tone) at a selected frequency and output power.
  */
SX128X_status_t  SetTxContinuousWave        ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It is a test command to generate an infinite sequence of alternating '0's and '1's in GFSK, BLE, or FLRC modulation and symbol 0 in LoRa.
  */
SX128X_status_t  SetTxContinuousPreamble    ( SPI_parameters_t mySPI_parameters                                                                                                                                                 );

/** It sets the auto-Tx ( BLE requires sending back a response after a packet reception ).
  */
SX128X_status_t  SetAutoTx                  ( SPI_parameters_t mySPI_parameters, uint16_t myTime                                                                                                                                );

/** This feature modifies the chip behavior so that the state following a Rx or Tx operation is FS and not STDBY.
  */
SX128X_status_t  SetAutoFs                  ( SPI_parameters_t mySPI_parameters, SX128X_set_auto_fs_t myAutoFsStatus                                                                                                            );

/** It sets the transceiver radio frame out of a choice of 6 different packet types.
  */
SX128X_status_t  SetPacketType              ( SPI_parameters_t mySPI_parameters, SX128X_set_packet_time_t myPacketType                                                                                                          );

/** It returns the current operating packet type of the radio.
  */
SX128X_status_t  GetPacketType              ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myPacketType                                                                                                                    );

/** It is used to set the frequency of the RF frequency mode.
  */
SX128X_status_t  SetRfFrequency             ( SPI_parameters_t mySPI_parameters, uint32_t myRfFrequency                                                                                                                         );
