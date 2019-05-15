/**
 * @brief       SX1272_SX1273.h
 * @details     SX1272/73 - 860 MHz to 1020 MHz Low Power Long Range Transceiver.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/April/2019
 * @version     29/April/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/**
  * @brief   REGISTER TABLE SUMMARY
  */
/** FSK/OOK and LoRa common registers.
  */
typedef enum
{
  SX1272_SX1273_REG_FIFO                        =   0x00,   /*!<  FIFO read/write access                                */
  SX1272_SX1273_REG_OP_MODE                     =   0x01,   /*!<  Operating mode & LoRa/FSK selection                   */
  SX1272_SX1273_REG_FRF_MSB                     =   0x06,   /*!<  RF Carrier Frequency, Most Significant Bits           */
  SX1272_SX1273_REG_FRF_MID                     =   0x07,   /*!<  RF Carrier Frequency, Intermediate Bits               */
  SX1272_SX1273_REG_FRF_LSB                     =   0x08,   /*!<  RF Carrier Frequency, Least Significant Bits          */
  SX1272_SX1273_REG_PA_CONFIG                   =   0x09,   /*!<  PA selection and Output Power control                 */
  SX1272_SX1273_REG_PA_RAMP                     =   0x0A,   /*!<  Control of PA ramp time, low phase noise PLL          */
  SX1272_SX1273_REG_OCP                         =   0x0B,   /*!<  Over Current Protection control                       */
  SX1272_SX1273_REG_LNA                         =   0x0C,   /*!<  LNA settings                                          */
  SX1272_SX1273_REG_DIO_MAPPING1                =   0x40,   /*!<  Mapping of pins DIO0 to DIO3                          */
  SX1272_SX1273_REG_DIO_MAPPING2                =   0x41,   /*!<  Mapping of pins DIO4 and DIO5, ClkOut frequency       */
  SX1272_SX1273_REG_VERSION                     =   0x42,   /*!<  Semtech ID relating the silicon revision              */
  SX1272_SX1273_REG_AGC_REF                     =   0x43,   /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_AGC_THRESH1                 =   0x44,   /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_AGC_THRESH2                 =   0x45,   /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_AGC_THRESH3                 =   0x46,   /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_PLL_HOP                     =   0x4B,   /*!<  Control the fast frequency hopping mode               */
  SX1272_SX1273_REG_TCXO                        =   0x58,   /*!<  TCXO or XTAL input setting                            */
  SX1272_SX1273_REG_PA_DAC                      =   0x5A,   /*!<  Higher power settings of the PA                       */
  SX1272_SX1273_REG_PLL                         =   0x5C,   /*!<  Control of the PLL bandwidth                          */
  SX1272_SX1273_REG_PLL_LOW_PN                  =   0x5E,   /*!<  Control of the Low Phase Noise PLL bandwidth          */
  SX1272_SX1273_REG_PA_MANUAL                   =   0x63,   /*!<  Enables manual PA control                             */
  SX1272_SX1273_REG_FORMER_TEMP                 =   0x6C,   /*!<  Stored temperature during the former IQ Calibration   */
  SX1272_SX1273_REG_BIT_RATE_FRAC               =   0x70    /*!<  Fractional part in the Bit Rate division ratio        */
} SX1272_SX1273_fsk_ook_lora_common_registers_t;


/** LoRa registers.
  */
typedef enum
{
  SX1272_SX1273_LORA_REG_FIFO_ADDR_PTR           =   0x0D,  /*!<  FIFO SPI pointer                                      */
  SX1272_SX1273_LORA_REG_FIFO_TX_BASE_ADDR       =   0x0E,  /*!<  Start Tx data                                         */
  SX1272_SX1273_LORA_REG_FIFO_RX_BASE_ADDR       =   0x0F,  /*!<  Start Rx data                                         */
  SX1272_SX1273_LORA_FIFO_RX_CURRENT_ADDR        =   0x10,  /*!<  Start address of last packet received                 */
  SX1272_SX1273_LORA_REG_IRQ_FLAGS_MASK          =   0x11,  /*!<  Optional IRQ flag mask                                */
  SX1272_SX1273_LORA_REG_IRQ_FLAGS               =   0x12,  /*!<  IRQ flags                                             */
  SX1272_SX1273_LORA_REG_RX_NB_BYTES             =   0x13,  /*!<  Number of received bytes                              */
  SX1272_SX1273_LORA_REG_RX_HEADER_CNT_VALUE_MSB =   0x14,  /*!<  Number of valid headers received                      */
  SX1272_SX1273_LORA_REG_RX_HEADER_CNT_VALUE_LSB =   0x15,  /*!<  Number of valid headers received                      */
  SX1272_SX1273_LORA_REG_RX_PACKET_CNT_VALUE_MSB =   0x16,  /*!<  Number of valid packets received                      */
  SX1272_SX1273_LORA_REG_RX_PACKET_CNT_VALUE_LSB =   0x17,  /*!<  Number of valid packets received                      */
  SX1272_SX1273_LORA_REG_MODEM_STAT              =   0x18,  /*!<  Live LoRa modem status                                */
  SX1272_SX1273_LORA_REG_PKT_SNR_VALUE           =   0x19,  /*!<  Espimation of last packet SNR                         */
  SX1272_SX1273_LORA_REG_PKT_RSSI_VALUE          =   0x1A,  /*!<  RSSI of last packet                                   */
  SX1272_SX1273_LORA_REG_RSSI_VALUE              =   0x1B,  /*!<  Current RSSI                                          */
  SX1272_SX1273_LORA_REG_HOP_CHANNEL             =   0x1C,  /*!<  FHSS start channel                                    */
  SX1272_SX1273_LORA_REG_MODEM_CONFIG1           =   0x1D,  /*!<  Modem PHY config 1                                    */
  SX1272_SX1273_LORA_REG_MODEM_CONFIG2           =   0x1E,  /*!<  Modem PHY config 2                                    */
  SX1272_SX1273_LORA_REG_SYMB_TIMEOUT_LSB        =   0x1F,  /*!<  Receiver timeout value                                */
  SX1272_SX1273_LORA_REG_PREAMBLE_MSB            =   0x20,  /*!<  Size of preamble                                      */
  SX1272_SX1273_LORA_REG_PREAMBLE_LSB            =   0x21,  /*!<  Size of preamble                                      */
  SX1272_SX1273_LORA_REG_PAYLOAD_LENGTH          =   0x22,  /*!<  LoRa payload length                                   */
  SX1272_SX1273_LORA_REG_MAX_PAYLOAD_LENGTH      =   0x23,  /*!<  LoRa maximum payload length                           */
  SX1272_SX1273_LORA_REG_HOP_PERIOD              =   0x24,  /*!<  FHSS Hop period                                       */
  SX1272_SX1273_LORA_REG_FIFO_RX_BYTE_ADDR       =   0x25,  /*!<  Address of last byte written in FIFO                  */
  SX1272_SX1273_LORA_REG_FEI_MSB                 =   0x28,  /*!<  Estimated frequency error                             */
  SX1272_SX1273_LORA_REG_FEI_MIB                 =   0x29,  /*!<  Estimated frequency error                             */
  SX1272_SX1273_LORA_REG_FEI_LSB                 =   0x2A,  /*!<  Estimated frequency error                             */
  SX1272_SX1273_LORA_REG_RSSI_WIDE_BAND          =   0x2C,  /*!<  Wideband RSSI measurement                             */
  SX1272_SX1273_LORA_REG_DETECT_OPTIMIZE         =   0x31,  /*!<  LoRa detection Optimize for SF6                       */
  SX1272_SX1273_LORA_REG_INVERT_IQ               =   0x33,  /*!<  Invert LoRa I and Q signals                           */
  SX1272_SX1273_LORA_REG_DETECTION_THRESHOLD     =   0x37,  /*!<  Change the LoRa Detection threshold for SF6           */
  SX1272_SX1273_LORA_REG_SYNC_WORD               =   0x39,  /*!<  LoRa Sync Word                                        */
  SX1272_SX1273_LORA_REG_INVERT_IQ2              =   0x3B   /*!<  Optimize for inverted IQ                              */
} SX1272_SX1273_lora_registers_t;


/** FSK/OOK registers.
  */
typedef enum
{
  SX1272_SX1273_FSK_REG_BIT_RATE_MSB            =   0x02,  /*!<  Bit Rate setting, Most Significant Bits                */
  SX1272_SX1273_FSK_REG_BIT_RATE_LSB            =   0x03,  /*!<  Bit Rate setting, Least Significant Bits               */
  SX1272_SX1273_FSK_REG_BIT_FDEV_MSB            =   0x04,  /*!<  Frequency Deviation setting, Most Significant Bits     */
  SX1272_SX1273_FSK_REG_BIT_FDEV_LSB            =   0x05,  /*!<  Frequency Deviation setting, Least Significant Bits    */
  SX1272_SX1273_FSK_REG_RX_CONFIG               =   0x0D,  /*!<  AFC, AGC, ctrl                                         */
  SX1272_SX1273_FSK_REG_RSSI_CONFIG             =   0x0E,  /*!<  RSSI                                                   */
  SX1272_SX1273_FSK_REG_RSSI_COLLISION          =   0x0F,  /*!<  RSSI Collision detector                                */
  SX1272_SX1273_FSK_REG_RSSI_THRESH             =   0x10,  /*!<  RSSI Threshold control                                 */
  SX1272_SX1273_FSK_REG_RSSI_VALUE              =   0x11,  /*!<  RSSI value in dBm                                      */
  SX1272_SX1273_FSK_REG_RX_BW                   =   0x12,  /*!<  Channel Filter BW Control                              */
  SX1272_SX1273_FSK_REG_AFC_BW                  =   0x13,  /*!<  AFC Channel Filter BW                                  */
  SX1272_SX1273_FSK_REG_OOK_PEAK                =   0x14,  /*!<  OOK demodulator                                        */
  SX1272_SX1273_FSK_REG_OOK_FIX                 =   0x15,  /*!<  Threshold of the OOK demod                             */
  SX1272_SX1273_FSK_REG_OOK_AVG                 =   0x16,  /*!<  Average of the OOK demod                               */
  SX1272_SX1273_FSK_REG_AFC_FEI                 =   0x1A,  /*!<  AFC and FEI control                                    */
  SX1272_SX1273_FSK_REG_AFC_MSB                 =   0x1B,  /*!<  Frequency correction value of the AFC                  */
  SX1272_SX1273_FSK_REG_AFC_LSB                 =   0x1C,  /*!<  Frequency correction value of the AFC                  */
  SX1272_SX1273_FSK_REG_FEI_MSB                 =   0x1D,  /*!<  Value of the calculated frequency error                */
  SX1272_SX1273_FSK_REG_FEI_LSB                 =   0x1E,  /*!<  Value of the calculated frequency error                */
  SX1272_SX1273_FSK_REG_PREAMBLE_DETECT         =   0x1F,  /*!<  Settings of the Preamble Detector                      */
  SX1272_SX1273_FSK_REG_RX_TIMEOUT_1            =   0x20,  /*!<  Timeout Rx request and RSSI                            */
  SX1272_SX1273_FSK_REG_RX_TIMEOUT_2            =   0x21,  /*!<  Timeout RSSI and PayloadReady                          */
  SX1272_SX1273_FSK_REG_RX_TIMEOUT_3            =   0x22,  /*!<  Timeout RSSI and SyncAddress                           */
  SX1272_SX1273_FSK_REG_RX_DELAY                =   0x23,  /*!<  Delay between Rx cycles                                */
  SX1272_SX1273_FSK_REG_OSC                     =   0x24,  /*!<  RC Oscillators Settings, CLKOUT frequency              */
  SX1272_SX1273_FSK_REG_PREAMBLE_MSB            =   0x25,  /*!<  Preamble length, MSB                                   */
  SX1272_SX1273_FSK_REG_PREAMBLE_LSB            =   0x26,  /*!<  Preamble length, LSB                                   */
  SX1272_SX1273_FSK_REG_SYNC_CONFIG             =   0x27,  /*!<  Sync Word Recognition control                          */
  SX1272_SX1273_FSK_REG_SYNC_VALUE_1            =   0x28,  /*!<  Sync Word bytes, 1 through 8                           */
  SX1272_SX1273_FSK_REG_SYNC_VALUE_2            =   0x29,  /*!<  Sync Word bytes, 1 through 8                           */
  SX1272_SX1273_FSK_REG_SYNC_VALUE_3            =   0x2A,  /*!<  Sync Word bytes, 1 through 8                           */
  SX1272_SX1273_FSK_REG_SYNC_VALUE_4            =   0x2B,  /*!<  Sync Word bytes, 1 through 8                           */
  SX1272_SX1273_FSK_REG_SYNC_VALUE_5            =   0x2C,  /*!<  Sync Word bytes, 1 through 8                           */
  SX1272_SX1273_FSK_REG_SYNC_VALUE_6_8          =   0x2D,  /*!<  Sync Word bytes, 1 through 8                           */
  SX1272_SX1273_FSK_REG_PACKET_CONFIG_1         =   0x30,  /*!<  Packet mode settings                                   */
  SX1272_SX1273_FSK_REG_PACKET_CONFIG_2         =   0x31,  /*!<  Packet mode settings                                   */
  SX1272_SX1273_FSK_REG_PAYLOAD_LENGHT          =   0x32,  /*!<  Payload length setting                                 */
  SX1272_SX1273_FSK_REG_NODE_ADRS               =   0x33,  /*!<  Node address                                           */
  SX1272_SX1273_FSK_REG_BROADCAST_ADRS          =   0x34,  /*!<  Broadcast address                                      */
  SX1272_SX1273_FSK_REG_FIFO_THRESH             =   0x35,  /*!<  Fifo threshold, Tx start condition                     */
  SX1272_SX1273_FSK_REG_SEQ_CONFIG_1            =   0x36,  /*!<  Top level Sequencer settings                           */
  SX1272_SX1273_FSK_REG_SEQ_CONFIG_2            =   0x37,  /*!<  Top level Sequencer settings                           */
  SX1272_SX1273_FSK_REG_TIMER_RESOL             =   0x38,  /*!<  Timer 1 and 2 resolution control                       */
  SX1272_SX1273_FSK_REG_TIMER1_COEF             =   0x39,  /*!<  Timer 1 setting                                        */
  SX1272_SX1273_FSK_REG_TIMER2_COEF             =   0x3A,  /*!<  Timer 2 setting                                        */
  SX1272_SX1273_FSK_REG_IMAGE_CALC              =   0x3B,  /*!<  Image calibration engine control                       */
  SX1272_SX1273_FSK_REG_TEMP                    =   0x3C,  /*!<  Temperature Sensor value                               */
  SX1272_SX1273_FSK_REG_LOW_BAT                 =   0x3D,  /*!<  Low Battery Indicator Settings                         */
  SX1272_SX1273_FSK_REG_IRQ_FLAGS_1             =   0x3E,  /*!<  Status register: PLL Lock state, Timeout, RSSI         */
  SX1272_SX1273_FSK_REG_IRQ_FLAGS_2             =   0x3F   /*!<  Status register: FIFO handling flags, Low Battery      */
} SX1272_SX1273_fsk_ook_registers_t;



/**
  * @brief   REGISTER MAP, LORA MODE
  */
/**
  * @brief   REG_FIFO
  */
typedef enum
{
  LORA_REGFIFO_FIFO_MASK                        =   0xFF         /*!<  LoRa base-band FIFO data input/output. FIFO is cleared an not accessible when device is in SLEEP mode */
} lora_regreg_fifo_t;


/**
  * @brief   REG_OP_MODE
  */
/**
  * LongRangeMode <7>
  *
  *   NOTE: This bit can be modified only in Sleep mode. A write operation on other device modes is ignored.
  */
typedef enum
{
  LORA_REGOPMODE_LONG_RANGE_MODE_MASK           =   ( 1U << 7U ),   /*!<  LongRangeMode Mask                                              */
  LORA_REGOPMODE_LONG_RANGE_MODE_FSK_OOK_MODE   =   ( 0U << 7U ),   /*!<  LongRangeMode FSK/OOK mode                          [ Default ] */
  LORA_REGOPMODE_LONG_RANGE_MODE_LORA_MODE      =   ( 1U << 7U )    /*!<  LongRangeMode LoRa mode                                         */
} lora_regopmode_long_range_mode_t;


/**
  * AccesSharedReg <6>
  *
  *   NOTE: This bit operates when device is in Lora mode; if set it allows access to FSK registers page located in address space (0x0D:0x3F) 
  *         while in LoRa mode.
  */
typedef enum
{
  LORA_REGOPMODE_ACCESS_SHARED_REG_MASK           =   ( 1U << 6U ),   /*!<  AccesSharedReg Mask                                             */
  LORA_REGOPMODE_ACCESS_SHARED_REG_LORA_REGISTERS =   ( 0U << 6U ),   /*!<  Access LoRa registers page 0x0D: 0x3F               [ Default ] */
  LORA_REGOPMODE_ACCESS_SHARED_REG_FSK_REGISTERS  =   ( 1U << 6U )    /*!<  Access FSK registers page (in mode LoRa) 0x0D: 0x3F             */
} lora_regopmode_access_shared_reg_t;


/**
  * Mode <2:0>
  *
  *   NOTE: This bit operates when device is in Lora mode; if set it allows access to FSK registers page located in address space (0x0D:0x3F) 
  *         while in LoRa mode.
  */
typedef enum
{
  LORA_REGOPMODE_MODE_MASK                        =   ( 0b111 << 0U ),  /*!<  Mode Mask                                                       */
  LORA_REGOPMODE_MODE_SLEEP                       =   ( 0b000 << 0U ),  /*!<  SLEEP                                                           */
  LORA_REGOPMODE_MODE_STDBY                       =   ( 0b001 << 0U ),  /*!<  STDBY                                               [ Default ] */
  LORA_REGOPMODE_MODE_FSTX                        =   ( 0b010 << 0U ),  /*!<  Frequency synthesis TX (FSTX)                                   */
  LORA_REGOPMODE_MODE_TX                          =   ( 0b011 << 0U ),  /*!<  Transmit (TX)                                                   */
  LORA_REGOPMODE_MODE_FSRX                        =   ( 0b100 << 0U ),  /*!<  Frequency synthesis RX (FSRX)                                   */
  LORA_REGOPMODE_MODE_RXCONTINUOUS                =   ( 0b101 << 0U ),  /*!<  Receive continuous (RXCONTINUOUS)                               */
  LORA_REGOPMODE_MODE_RXSINGLE                    =   ( 0b110 << 0U ),  /*!<  Receive single (RXSINGLE)                                       */
  LORA_REGOPMODE_MODE_CAD                         =   ( 0b111 << 0U )   /*!<  Channel activity detection (CAD)                                */
} lora_regopmode_mode_t;


/**
  * @brief   REG_PA_CONFIG
  */
/**
  * PaSelect <7>
  *
  *   NOTE: Selects PA output pin.
  */
typedef enum
{
  LORA_REGPACONFIG_PA_SELECT_MASK                 =   ( 1U << 7U ),     /*!<  PaSelect Mask                                                   */
  LORA_REGPACONFIG_PA_SELECT_RFIO_PIN             =   ( 0U << 7U ),     /*!<  Output power is limited to 13 dBm                   [ Default ] */
  LORA_REGPACONFIG_PA_SELECT_PA_BOOST_PIN         =   ( 1U << 7U )      /*!<  Output power is limited to 20 dBm                               */
} lora_regpaconfig_pa_select_t;


/**
  * OutputPower <3:0>
  *
  *   NOTE: Power amplifier max output power.
  *           - Pout =  2 + OutputPower(3:0) on PA_BOOST
  *           - Pout = -1 + OutputPower(3:0) on RFIO
  */
typedef enum
{
  LORA_REGPACONFIG_OUTPUT_POWER_MASK              =   ( 0b1111 << 7U )    /*!<  OutputPower Mask                                                */
} lora_regpaconfig_output_power_t;


/**
  * @brief   REG_PA_RAMP
  */
/**
  * LowPnTxPllOff <4>
  *
  *   NOTE: Selects PA output pin.
  */
typedef enum
{
  LORA_REGPARAMP_LOW_PN_TX_PLL_OFF_MASK                 =   ( 1U << 4U ),   /*!<  LowPnTxPllOff Mask                                                        */
  LORA_REGPARAMP_LOW_PN_TX_PLL_OFF_RX_AND_TX            =   ( 1U << 4U ),   /*!<  Low consumption PLL is used in receive and transmit mode      [ Default ] */
  LORA_REGPARAMP_LOW_PN_TX_PLL_OFF_RX_AND_LOW_PHASE_TX  =   ( 0U << 4U )    /*!<  Low consumption PLL in receive mode, low phase noise PLL in transmit mode */
} lora_regparamp_low_pn_tx_pll_off_t;


/**
  * PaRamp <3:0>
  *
  *   NOTE: Rise/Fall time of ramp up/down in FSK.
  */
typedef enum
{
  LORA_REGPARAMP_PA_RAMP_MASK                       =   ( 0b1111 << 0U ),   /*!<  PaRamp Mask                                                   */
  LORA_REGPARAMP_PA_RAMP_3_4_MS                     =   ( 0b0000 << 0U ),   /*!<  3.4 ms                                                        */
  LORA_REGPARAMP_PA_RAMP_2_MS                       =   ( 0b0001 << 0U ),   /*!<  2 ms                                                          */
  LORA_REGPARAMP_PA_RAMP_1_MS                       =   ( 0b0010 << 0U ),   /*!<  1 ms                                                          */
  LORA_REGPARAMP_PA_RAMP_500_US                     =   ( 0b0011 << 0U ),   /*!<  500 us                                                        */
  LORA_REGPARAMP_PA_RAMP_250_US                     =   ( 0b0100 << 0U ),   /*!<  250 us                                                        */
  LORA_REGPARAMP_PA_RAMP_125_US                     =   ( 0b0101 << 0U ),   /*!<  125 us                                                        */
  LORA_REGPARAMP_PA_RAMP_100_US                     =   ( 0b0110 << 0U ),   /*!<  100 us                                                        */
  LORA_REGPARAMP_PA_RAMP_62_US                      =   ( 0b0111 << 0U ),   /*!<  62 us                                                         */
  LORA_REGPARAMP_PA_RAMP_50_US                      =   ( 0b1000 << 0U ),   /*!<  50 us                                                         */
  LORA_REGPARAMP_PA_RAMP_40_US                      =   ( 0b1001 << 0U ),   /*!<  40 us                                                         */
  LORA_REGPARAMP_PA_RAMP_31_US                      =   ( 0b1010 << 0U ),   /*!<  31 us                                                         */
  LORA_REGPARAMP_PA_RAMP_25_US                      =   ( 0b1011 << 0U ),   /*!<  25 us                                                         */
  LORA_REGPARAMP_PA_RAMP_20_US                      =   ( 0b1100 << 0U ),   /*!<  20 us                                                         */
  LORA_REGPARAMP_PA_RAMP_15_US                      =   ( 0b1101 << 0U ),   /*!<  15 us                                                         */
  LORA_REGPARAMP_PA_RAMP_12_US                      =   ( 0b1110 << 0U ),   /*!<  12 us                                                         */
  LORA_REGPARAMP_PA_RAMP_10_US                      =   ( 0b1111 << 0U )    /*!<  10 us                                                         */
} lora_regparamp_pa_ramp_t;


/**
  * @brief   REG_OCP
  */
/**
  * OcpOn <5>
  *
  *   NOTE: Enables overload current protection (OCP) for PA.
  */
typedef enum
{
  LORA_REGOCP_OCP_ON_MASK                           =   ( 1U << 5U ),   /*!<  OcpOn Mask                                                    */
  LORA_REGOCP_OCP_ON_DISABLED                       =   ( 0U << 5U ),   /*!<  OCP disabled                                                  */
  LORA_REGOCP_OCP_ON_ENABLED                        =   ( 1U << 5U )    /*!<  OCP enabled                                       [ Default ] */
} lora_regocp_ocp_on_t;


/**
  * OcpTrim <4:0>
  *
  *   NOTE: Trimming of OCP current ( Default I_max = 100mA ).
  *           - I_max =  45+5*OcpTrim  [mA] if OcpTrim <= 15      (120 mA) 
  *           - I_max = -30+10*OcpTrim [mA] if 15 < OcpTrim <= 27 (130 to 240 mA)
  *           - I_max =  240mA for higher settings
  */
typedef enum
{
  LORA_REGOCP_OCP_TRIM_MASK                         =   ( 0b11111 << 0U ) /*!<  OcpTrim Mask                                                  */
} lora_regocp_ocp_trim_t;




#ifndef SX1272_SX1273_VECTOR_STRUCT_H
#define SX1272_SX1273_VECTOR_STRUCT_H
typedef struct
{
    float                       t_a;              /*!<  Ambient temperature value     */
    uint16_t                    t_a_raw;          /*!<  Raw ambient temperature value */

    float                       t_upper;          /*!<  T_UPPER limit                 */
    float                       t_lower;          /*!<  T_LOWER limit                 */
    float                       t_crit;           /*!<  T_CRIT limit                  */

    uint16_t                    manufacturerID;   /*!<  Manufacturer ID               */
    uint8_t                     deviceID;         /*!<  Device ID                     */
    uint8_t                     deviceRevision;   /*!<  Device Revision               */
} SX1272_SX1273_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SX1272_SX1273_SUCCESS     =       0,
    SX1272_SX1273_FAILURE     =       1
} SX1272_SX1273_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
  */
SX1272_SX1273_status_t SX1272_SX1273_Init               ( SPI_parameters_t mySPIparameters                                                              );

/** It gets CONFIG register value.
  */
//SX1272_SX1273_status_t SX1272_SX1273_GetCONFIG          ( SPI_parameters_t mySPIparameters, SX1272_SX1273_config_reg_t* myCONFIG                              );
