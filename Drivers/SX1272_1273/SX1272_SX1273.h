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
  * @brief   REGISTER MAP, FSK/OOK MODE
  */
/**
  * @brief   REG_FIFO
  */
typedef enum
{
  FSK_OOK_REGFIFO_FIFO_MASK                     =   0xFF         /*!<  FIFO data input/output                                             */
} fsk_ook_reg_fifo_t;


/* FSK/OOK: Registers for Common settings   */
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
  FSK_OOK_REGOPMODE_LONG_RANGE_MODE_MASK          =   ( 1U << 7U ), /*!<  LongRangeMode Mask                                              */
  FSK_OOK_REGOPMODE_LONG_RANGE_MODE_FSK_OOK_MODE  =   ( 0U << 7U ), /*!<  LongRangeMode FSK/OOK mode                          [ Default ] */
  FSK_OOK_REGOPMODE_LONG_RANGE_MODE_LORA_MODE     =   ( 1U << 7U )  /*!<  LongRangeMode LoRa mode                                         */
} fsk_ook_regopmode_long_range_mode_t;


/**
  * ModulationType <6:5>
  *
  *   NOTE: Modulation scheme.
  */
typedef enum
{
  FSK_OOK_REGOPMODE_MODULATION_TYPE_MASK        =   ( 0b11 << 5U ), /*!<  ModulationType Mask                                             */
  FSK_OOK_REGOPMODE_MODULATION_TYPE_FSK         =   ( 0b00 << 5U ), /*!<  FSK                                                 [ Default ] */
  FSK_OOK_REGOPMODE_MODULATION_TYPE_OOK         =   ( 0b01 << 5U )  /*!<  OOK                                                             */
} fsk_ook_regopmode_modulation_type_t;


/**
  * ModulationShaping <4:3>
  *
  *   NOTE: Data shaping.
  */
typedef enum
{
  FSK_OOK_REGOPMODE_MODULATION_SHAPING_MASK           =   ( 0b11 << 3U ), /*!<  ModulationShaping Mask                                                */
  FSK_OOK_REGOPMODE_FSK_MODULATION_SHAPING_NO_SHAPING =   ( 0b00 << 3U ), /*!<  FSK:  no shaping                                    [ Default ]       */
  FSK_OOK_REGOPMODE_FSK_MODULATION_SHAPING_BT_1_0     =   ( 0b01 << 3U ), /*!<  FSK:  Gaussian filter BT = 1.0                                        */
  FSK_OOK_REGOPMODE_FSK_MODULATION_SHAPING_BT_0_5     =   ( 0b10 << 3U ), /*!<  FSK:  Gaussian filter BT = 0.5                                        */
  FSK_OOK_REGOPMODE_FSK_MODULATION_SHAPING_BT_0_3     =   ( 0b11 << 3U ), /*!<  FSK:  Gaussian filter BT = 0.3                                        */
  FSK_OOK_REGOPMODE_OOK_MODULATION_SHAPING_NO_SHAPING =   ( 0b00 << 3U ), /*!<  OOK:  no shaping                                    [ Default ]       */
  FSK_OOK_REGOPMODE_OOK_MODULATION_SHAPING_1          =   ( 0b01 << 3U ), /*!<  OOK:  filtering with f_cutoff = bit_rate                              */
  FSK_OOK_REGOPMODE_OOK_MODULATION_SHAPING_2          =   ( 0b10 << 3U )  /*!<  OOK:  filtering with f_cutoff = 2*bit_rate (for bit_rate < 125 kbps)  */
} fsk_ook_regopmode_modulation_shaping_t;


/**
  * Mode <2:0>
  *
  *   NOTE: Transceiver modes.
  */
typedef enum
{
  FSK_OOK_REGOPMODE_MODE_MASK                   =   ( 0b111 << 0U ),  /*!<  Mode Mask                                                       */
  FSK_OOK_REGOPMODE_MODE_SLEEP_MODE             =   ( 0b000 << 0U ),  /*!<  Sleep mode                                                      */
  FSK_OOK_REGOPMODE_MODE_STDBY_MODE             =   ( 0b001 << 0U ),  /*!<  Stdby mode                                          [ Default ] */
  FSK_OOK_REGOPMODE_MODE_FSTX_MODE              =   ( 0b010 << 0U ),  /*!<  FS mode TX (FSTx)                                               */
  FSK_OOK_REGOPMODE_MODE_TX_MODE                =   ( 0b011 << 0U ),  /*!<  Transmitter mode (Tx)                                           */
  FSK_OOK_REGOPMODE_MODE_FSRX_MODE              =   ( 0b100 << 0U ),  /*!<  FS mode RX (FSRx)                                               */
  FSK_OOK_REGOPMODE_MODE_RX_MODE                =   ( 0b101 << 0U )   /*!<  Receiver mode (Rx)                                              */
} fsk_ook_regopmode_mode_t;


/**
  * @brief   REG_BITRATE_MSB (Default: 0x1A)
  *
  *   NOTE: MSB of Bit Rate (chip rate if Manchester encoding is enabled).
  */
typedef enum
{
  FSK_OOK_REGBITRATEMSB_BIT_RATE_MASK           =   0xFF         /*!<  BitRate mask                                                      */
} fsk_ook_regbitratemsb_bit_rate_t;


/**
  * @brief   REG_BITRATE_LSB (Default: 0x1B)
  *
  *   NOTE: LSB of bit rate (chip rate if Manchester encoding is enabled).
  */
typedef enum
{
  FSK_OOK_REGBITRATELSB_BIT_RATE_MASK           =   0xFF         /*!<  BitRate mask                                                      */
} fsk_ook_regbitratelsb_bit_rate_t;


/**
  * @brief   REG_FDEV_MSB
  */
/**
  * Fdev <5:0>
  *
  *   NOTE: MSB of the frequency deviation (Default: 0x00).
  */
typedef enum
{
  FSK_OOK_REGFDEVMSB_FDEV_MASK                  =   ( 0b111111 << 0U )  /*!<  Fdev mask                                                      */
} fsk_ook_regfdevmsb_fdev_t;


/**
  * @brief   REG_FDEV_LSB (Default: 0x52)
  *
  *   NOTE: LSB of the frequency deviation.
  */
typedef enum
{
  FSK_OOK_REGFDEVLSB_FDEV_MASK                  =   0xFF                /*!<  Fdev mask                                                      */
} fsk_ook_regfdevlsb_fdev_t;


/**
  * @brief   REG_FRF_MSB (Default: 0xE4)
  *
  *   NOTE: MSB of the RF carrier frequency.
  */
typedef enum
{
  FSK_OOK_REGFRFMSB_FRF_MASK                    =   0xFF                /*!<  Frf mask                                                      */
} fsk_ook_regfrfmsb_frf_t;


/**
  * @brief   REG_FRF_MIB (Default: 0xC0)
  *
  *   NOTE: MIB of the RF carrier frequency.
  */
typedef enum
{
  FSK_OOK_REGFRFMIB_FRF_MASK                    =   0xFF                /*!<  Frf mask                                                      */
} fsk_ook_regfrfmib_frf_t;


/**
  * @brief   REG_FRF_LSB (Default: 0x00)
  *
  *   NOTE: LSB of RF carrier frequency.
  */
typedef enum
{
  FSK_OOK_REGFRFLSB_FRF_MASK                    =   0xFF                /*!<  Frf mask                                                      */
} fsk_ook_regfrflsb_frf_t;


/* FSK/OOK: Registers for the Transmitter   */
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
  FSK_OOK_REGPACONFIG_PA_SELECT_MASK            =   ( 1U << 7U ),       /*!<  PaSelect mask                                                 */
  FSK_OOK_REGPACONFIG_PA_SELECT_RFO_PIN         =   ( 0U << 7U ),       /*!<  RFO pin. Maximum power of +13 dBm                 [ Default ] */
  FSK_OOK_REGPACONFIG_PA_SELECT_PA_BOOST        =   ( 1U << 7U )        /*!<  PA_BOOST pin. Maximum power of +20 dBm                        */
} fsk_ook_regpaconfig_pa_select_t;


/**
  * OutputPower <3:0>
  *
  *   NOTE: Output power setting, with 1dB steps
  *           - Pout = 2 + OutputPower  [dBm], on PA_BOOST pin
  *           - Pout = -1 + OutputPower [dBm], on RFO pin
  */
typedef enum
{
  FSK_OOK_REGPACONFIG_OUTPUT_POWER_MASK         =   ( 0b1111 << 0U )    /*!<  OutputPower mask                                              */
} fsk_ook_regpaconfig_output_power_t;


/**
  * @brief   REG_PA_RAMP
  */
/**
  * LowPnTxPllOff <4>
  *
  *   NOTE: Select a higher power, lower phase noise PLL only when the transmitter is used.
  */
typedef enum
{
  FSK_OOK_REGPARAMP_LOW_PN_TX_PLL_OFF_MASK    =   ( 1U << 4U ),       /*!<  LowPnTxPllOff mask                                            */
  FSK_OOK_REGPARAMP_LOW_PN_TX_PLL_OFF_0       =   ( 0U << 4U ),       /*!<  Standard PLL used in Rx mode, Lower PN PLL in Tx              */
  FSK_OOK_REGPARAMP_LOW_PN_TX_PLL_OFF_1       =   ( 1U << 4U )        /*!<  Standard PLL used in both Tx and Rx modes         [ Default ] */
} fsk_ook_regparamp_low_pn_tx_pll_off_t;


/**
  * PaRamp <3:0>
  *
  *   NOTE: Select a higher power, lower phase noise PLL only when the transmitter is used.
  */
typedef enum
{
  FSK_OOK_REGPARAMP_PA_RAMP_MASK              =   ( 0b1111 << 0U ),   /*!<  PaRamp mask                                                   */
  FSK_OOK_REGPARAMP_PA_RAMP_3_4_MS            =   ( 0b0000 << 0U ),   /*!<  PaRamp 3.4 ms                                                 */
  FSK_OOK_REGPARAMP_PA_RAMP_2_MS              =   ( 0b0001 << 0U ),   /*!<  PaRamp 2 ms                                                   */
  FSK_OOK_REGPARAMP_PA_RAMP_1_MS              =   ( 0b0010 << 0U ),   /*!<  PaRamp 1 ms                                                   */
  FSK_OOK_REGPARAMP_PA_RAMP_500_US            =   ( 0b0011 << 0U ),   /*!<  PaRamp 500 us                                                 */
  FSK_OOK_REGPARAMP_PA_RAMP_250_US            =   ( 0b0100 << 0U ),   /*!<  PaRamp 250 us                                                 */
  FSK_OOK_REGPARAMP_PA_RAMP_125_US            =   ( 0b0101 << 0U ),   /*!<  PaRamp 125 us                                                 */
  FSK_OOK_REGPARAMP_PA_RAMP_100_US            =   ( 0b0110 << 0U ),   /*!<  PaRamp 100 us                                                 */
  FSK_OOK_REGPARAMP_PA_RAMP_62_US             =   ( 0b0111 << 0U ),   /*!<  PaRamp 62 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_50_US             =   ( 0b1000 << 0U ),   /*!<  PaRamp 50 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_40_US             =   ( 0b1001 << 0U ),   /*!<  PaRamp 40 us                                      [ Default ] */
  FSK_OOK_REGPARAMP_PA_RAMP_31_US             =   ( 0b1010 << 0U ),   /*!<  PaRamp 31 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_25_US             =   ( 0b1011 << 0U ),   /*!<  PaRamp 25 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_20_US             =   ( 0b1100 << 0U ),   /*!<  PaRamp 20 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_15_US             =   ( 0b1101 << 0U ),   /*!<  PaRamp 15 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_12_US             =   ( 0b1110 << 0U ),   /*!<  PaRamp 12 us                                                  */
  FSK_OOK_REGPARAMP_PA_RAMP_10_US             =   ( 0b1111 << 0U )    /*!<  PaRamp 10 us                                                  */
} fsk_ook_regparamp_pa_ramp_t;


/**
  * @brief   REG_OCP
  */
/**
  * OcpOn <5>
  *
  *   NOTE: Enables overload current protection (OCP) for the PA.
  */
typedef enum
{
  FSK_OOK_REGOCP_OCP_ON_MASK              =   ( 1U << 5U ),       /*!<  OcpOn mask                                                    */
  FSK_OOK_REGOCP_OCP_ON_OCP_DISABLED      =   ( 0U << 5U ),       /*!<  OCP disabled                                                  */
  FSK_OOK_REGOCP_OCP_ON_OCP_ENABLED       =   ( 1U << 5U )        /*!<  OCP enabled                                       [ Default ] */
} fsk_ook_regocp_ocp_on_t;


/**
  * OcpTrim <4:0> (Default: 0x0B)
  *
  *   NOTE: Trimming of OCP current:
  *           - I_max = 45+5*OcpTrim [mA]   if OcpTrim <= 15 (120 mA) 
  *           - I_max = -30+10*OcpTrim [mA] if 15 < OcpTrim <= 27 (130 to 240 mA)
  *           - I_max = 240mA for higher settings
  *         Default I_max = 100mA
  */
typedef enum
{
  FSK_OOK_REGOCP_OCP_TRIM_MASK            =   ( 0b11111 << 0U )   /*!<  OcpTrim mask                                                  */
} fsk_ook_regocp_ocp_trim_t;


/* FSK/OOK: Registers for the Receiver   */
/**
  * @brief   REG_LNA
  */
/**
  * LnaGain <7:5>
  *
  *   NOTE: Selects PA output pin.
  */
typedef enum
{
  FSK_OOK_REGLNA_LNA_GAIN_MASK              =   ( 0b111 << 5U ),  /*!<  LnaGain mask                                                  */
  FSK_OOK_REGLNA_LNA_GAIN_G1                =   ( 0b001 << 5U ),  /*!<  G1 = highest gain                                 [ Default ] */
  FSK_OOK_REGLNA_LNA_GAIN_G2                =   ( 0b010 << 5U ),  /*!<  G2 = highest gain – 6 dB                                      */
  FSK_OOK_REGLNA_LNA_GAIN_G3                =   ( 0b011 << 5U ),  /*!<  G3 = highest gain – 12 dB                                     */
  FSK_OOK_REGLNA_LNA_GAIN_G4                =   ( 0b100 << 5U ),  /*!<  G4 = highest gain – 24 dB                                     */
  FSK_OOK_REGLNA_LNA_GAIN_G5                =   ( 0b101 << 5U ),  /*!<  G5 = highest gain – 36 dB                                     */
  FSK_OOK_REGLNA_LNA_GAIN_G6                =   ( 0b110 << 5U )   /*!<  G6 = highest gain – 48 dB                                     */
} fsk_ook_reglna_lna_gain_t;


/**
  * LnaBoost <1:0>
  *
  *   NOTE: Improves the system Noise Figure at the expense of Rx current consumption.
  */
typedef enum
{
  FSK_OOK_REGLNA_LNA_BOOST_MASK                 =   ( 0b11 << 0U ), /*!<  LnaBoost mask                                                 */
  FSK_OOK_REGLNA_LNA_BOOST_DEFAULT_SETTING      =   ( 0b00 << 0U ), /*!<  Default setting, meeting the specification        [ Default ] */
  FSK_OOK_REGLNA_LNA_BOOST_IMPROVED_SENSITIVITY =   ( 0b11 << 0U )  /*!<  Improved sensitivity                                          */
} fsk_ook_reglna_lna_boost_t;


/**
  * @brief   REG_RX_CONFIG
  */
/**
  * RestartRxOnCollision <7>
  *
  *   NOTE: Turns on the mechanism restarting the receiver automatically if it gets saturated or a packet collision is detected.
  */
typedef enum
{
  FSK_OOK_REGRXCONFIG_RESTART_RX_ON_COLLISION_MASK                  =   ( 1U << 7U ), /*!<  RestartRxOnCollision mask                                                 */
  FSK_OOK_REGRXCONFIG_RESTART_RX_ON_COLLISION_NO_AUTOMATIC_RESTART  =   ( 0U << 7U ), /*!<  No automatic Restart                                          [ Default ] */
  FSK_OOK_REGRXCONFIG_RESTART_RX_ON_COLLISION_AUTOMATIC_RESTART_ON  =   ( 1U << 7U )  /*!<  Automatic restart On                                                      */
} fsk_ook_regrxconfig_restart_rx_on_collision_t;


/**
  * RestartRxWithoutPllLock <6>
  *
  *   NOTE: Triggers a manual Restart of the Receiver chain when set to 1. Use this bit when there is no frequency change, RestartRxWithPllLock otherwise.
  */
typedef enum
{
  FSK_OOK_REGRXCONFIG_RESTART_RX_WITHOUT_PLL_LOCK_MASK  =   ( 1U << 6U ), /*!<  RestartRxWithoutPllLock mask                                              */
  FSK_OOK_REGRXCONFIG_RESTART_RX_WITHOUT_PLL_LOCK       =   ( 1U << 6U )  /*!<  RestartRxWithoutPllLock                                                   */
} fsk_ook_regrxconfig_restart_rx_without_pll_lock_t;


/**
  * RestartRxWithPllLock <5>
  *
  *   NOTE: Triggers a manual Restart of the Receiver chain when set to 1. Use this bit when there is a frequency change, requiring some time for the PLL to re-lock.
  */
typedef enum
{
  FSK_OOK_REGRXCONFIG_RESTART_RX_WITH_PLL_LOCK_MASK  =   ( 1U << 5U ), /*!<  RestartRxWithPllLock mask                                              */
  FSK_OOK_REGRXCONFIG_RESTART_RX_WITH_PLL_LOCK       =   ( 1U << 5U )  /*!<  RestartRxWithPllLock                                                   */
} fsk_ook_regrxconfig_restart_rx_with_pll_lock_t;


/**
  * AfcAutoOn <4>
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_REGRXCONFIG_AFC_AUTO_ON_MASK          =   ( 1U << 4U ), /*!<  AfcAutoOn mask                                                        */
  FSK_OOK_REGRXCONFIG_AFC_AUTO_ON_NO_AFC        =   ( 0U << 4U ), /*!<  No AFC performed at receiver startup                      [ Default ] */
  FSK_OOK_REGRXCONFIG_AFC_AUTO_ON_AFC           =   ( 1U << 4U )  /*!<  AFC is performed at each receiver startup                             */
} fsk_ook_regrxconfig_afc_auto_on_t;


/**
  * AgcAutoOn <3>
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_REGRXCONFIG_AGC_AUTO_ON_MASK          =   ( 1U << 3U ), /*!<  AfcAutoOn mask                                                        */
  FSK_OOK_REGRXCONFIG_AGC_AUTO_ON_0             =   ( 0U << 3U ), /*!<  LNA gain forced by the LnaGain Setting                                */
  FSK_OOK_REGRXCONFIG_AGC_AUTO_ON_1             =   ( 1U << 3U )  /*!<  LNA gain is controlled by the AGC                         [ Default ] */
} fsk_ook_regrxconfig_agc_auto_on_t;


/**
  * RxTrigger <2:0>
  *
  *   NOTE: Selects the event triggering AGC and/or AFC at receiver startup.
  */
typedef enum
{
  FSK_OOK_REGRXCONFIG_RX_TRIGGER_MASK           =   ( 0b111 << 0U ) /*!<  RxTrigger mask                                                      */
} fsk_ook_regrxconfig_rx_trigger_t;


/**
  * @brief   REG_RSSI_CONFIG
  */
/**
  * RssiOffset <7:3>
  *
  *   NOTE: Signed RSSI offset, to compensate for the possible losses/gains in the front-end (LNA, SAW filter...) 1dB / LSB, 2’s complement format.
  */
typedef enum
{
  FSK_OOK_REGRSSICONFIG_RSSI_OFFSET_MASK        =   ( 0b11111 << 3U ) /*!<  RssiOffset mask                                                   */
} fsk_ook_regrssiconfig_rssi_offset_t;


/**
  * RssiSmoothing <2:0>
  *
  *   NOTE: Defines the number of samples taken to average the RSSI result.
  */
typedef enum
{
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_MASK         =   ( 0b111 << 0U ),  /*!<  RssiSmoothing mask                                                */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_2_SAMPLES    =   ( 0b000 << 0U ),  /*!<  2 samples used                                                    */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_4_SAMPLES    =   ( 0b001 << 0U ),  /*!<  4 samples used                                                    */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_8_SAMPLES    =   ( 0b010 << 0U ),  /*!<  8 samples used                                        [ Default ] */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_16_SAMPLES   =   ( 0b011 << 0U ),  /*!<  16 samples used                                                   */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_32_SAMPLES   =   ( 0b100 << 0U ),  /*!<  32 samples used                                                   */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_64_SAMPLES   =   ( 0b101 << 0U ),  /*!<  64 samples used                                                   */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_128_SAMPLES  =   ( 0b110 << 0U ),  /*!<  128 samples used                                                  */
  FSK_OOK_REGRSSICONFIG_RSSI_SMOOTHING_256_SAMPLES  =   ( 0b111 << 0U )   /*!<  256 samples used                                                  */
} fsk_ook_regrssiconfig_rssi_smoothing_t;


/**
  * @brief   REG_RSSI_COLLISION (Default: 0x0A)
  *
  *   NOTE: Sets the threshold used to consider that an interferer is detected, witnessing a packet collision. 1dB/LSB (only RSSI increase) Default: 10dB.
  */
typedef enum
{
  FSK_OOK_REGRSSICOLLISION_RSSI_COLLISION_THRESHOLD_MASK  =   0xFF        /*!<  RssiCollisionThreshold mask                                       */
} fsk_ook_regrssicollision_rssi_collision_threshold_t;


/**
  * @brief   REG_RSSI_THRESH (Default: 0xFF)
  *
  *   NOTE: RSSI trigger level for the Rssi interrupt: - RssiThreshold / 2 [dBm].
  */
typedef enum
{
  FSK_OOK_REGRSSITHRESH_RSSI_THRESHOLD_MASK         =   0xFF              /*!<  RssiThreshold mask                                                */
} fsk_ook_regrssithresh_rssi_threshold_t;


/**
  * @brief   REG_RSSI_VALUE 
  *
  *   NOTE: Absolute value of the RSSI in dBm, 0.5dB steps: - RssiThreshold / 2 [dBm].
  */
typedef enum
{
  FSK_OOK_REGRSSIVALUE_RSSI_VALUE_MASK              =   0xFF              /*!<  RssiValue mask                                                    */
} fsk_ook_regrssivalue_rssi_value_t;


/**
  * @brief   REG_RX_BW
  */
/**
  * RxBwMant <4:3>
  *
  *   NOTE: Channel filter bandwidth control.
  */
typedef enum
{
  FSK_OOK_REGRXBW_RX_BW_MANT_MASK                   =   ( 0b11 << 3U ),    /*!<  RxBwMant mask                                                     */
  FSK_OOK_REGRXBW_RX_BW_MANT_16                     =   ( 0b00 << 3U ),    /*!<  RxBwMant = 16                                                     */
  FSK_OOK_REGRXBW_RX_BW_MANT_20                     =   ( 0b01 << 3U ),    /*!<  RxBwMant = 20                                                     */
  FSK_OOK_REGRXBW_RX_BW_MANT_24                     =   ( 0b10 << 3U )     /*!<  RxBwMant = 24                                         [ Default ] */
} fsk_ook_regrxbw_rx_bw_mant_t;


/**
  * RxBwExp <2:0> (Default: 0x05)
  *
  *   NOTE: Channel filter bandwidth control.
  */
typedef enum
{
  FSK_OOK_REGRXBW_RX_BW_EXP_MASK                    =   ( 0b111 << 0U )    /*!<  RxBwExp mask                                                       */
} fsk_ook_regrxbw_rx_bw_exp_t;


/**
  * @brief   REG_AFC_BW
  */
/**
  * RxBwMantAfc <4:3> (Default: 0x01)
  *
  *   NOTE: RxBwMant parameter used during the AFC.
  */
typedef enum
{
  FSK_OOK_REGAFCBW_RX_BW_MANT_AFC_MASK                =   ( 0b11 << 3U )     /*!<  RxBwMantAfc mask                                                 */
} fsk_ook_regafcbw_rx_bw_mant_afc_t;


/**
  * RxBwExpAfc <2:0> (Default: 0x03)
  *
  *   NOTE: RxBwExp parameter used during the AFC.
  */
typedef enum
{
  FSK_OOK_REGAFCBW_RX_BW_EXP_AFC_MASK                 =   ( 0b111 << 0U )    /*!<  RxBwMantAfc mask                                                 */
} fsk_ook_regafcbw_rx_bw_exp_afc_t;


/**
  * @brief   REG_OOK_PEAK
  */
/**
  * BitSyncOn <5>
  *
  *   NOTE: Enables the Bit Synchronizer.
  */
typedef enum
{
  FSK_OOK_REGOOKPEAK_BIT_SYNC_ON_MASK               =   ( 1U << 5U ),       /*!<  BitSyncOn mask                                                    */
  FSK_OOK_REGOOKPEAK_BIT_SYNC_ON_DISABLED           =   ( 0U << 5U ),       /*!<  Bit Sync disabled (not possible in Packet mode)                   */
  FSK_OOK_REGOOKPEAK_BIT_SYNC_ON_ENABLED            =   ( 1U << 5U )        /*!<  Bit Sync enabled                                      [ Default ] */
} fsk_ook_regookpeak_bit_sync_on_t;


/**
  * OokThreshType <4:3>
  *
  *   NOTE: Selects the type of threshold in the OOK data slicer.
  */
typedef enum
{
  FSK_OOK_REGOOKPEAK_OOK_THRESH_TYPE_MASK           =   ( 0b11 << 3U ),     /*!<  OokThreshType mask                                                */
  FSK_OOK_REGOOKPEAK_OOK_THRESH_TYPE_FIX_THRESHOLD  =   ( 0b00 << 3U ),     /*!<  fixed threshold                                                   */
  FSK_OOK_REGOOKPEAK_OOK_THRESH_TYPE_PEAK_MODE      =   ( 0b01 << 3U ),     /*!<  peak mode                                             [ Default ] */
  FSK_OOK_REGOOKPEAK_OOK_THRESH_TYPE_AVERAGE_MODE   =   ( 0b10 << 3U )      /*!<  average mode                                                      */
} fsk_ook_regookpeak_ook_thresh_type_t;


/**
  * OokPeakTheshStep <2:0>
  *
  *   NOTE: Size of each decrement of the RSSI threshold in the OOK demodulator.
  */
typedef enum
{
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_MASK      =   ( 0b111 << 0U ),    /*!<  OokPeakTheshStep mask                                             */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_0_5_DB    =   ( 0b000 << 0U ),    /*!<  0.5 dB                                                [ Default ] */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_1_0_DB    =   ( 0b001 << 0U ),    /*!<  1.0 dB                                                            */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_1_5_DB    =   ( 0b010 << 0U ),    /*!<  1.5 dB                                                            */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_2_0_DB    =   ( 0b011 << 0U ),    /*!<  2.0 dB                                                            */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_3_0_DB    =   ( 0b100 << 0U ),    /*!<  3.0 dB                                                            */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_4_0_DB    =   ( 0b101 << 0U ),    /*!<  4.0 dB                                                            */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_5_0_DB    =   ( 0b110 << 0U ),    /*!<  5.0 dB                                                            */
  FSK_OOK_REGOOKPEAK_OOK_PEAK_THRESH_STEP_6_0_DB    =   ( 0b111 << 0U )     /*!<  6.0 dB                                                            */
} fsk_ook_regookpeak_ook_peak_thresh_step_t;


/**
  * @brief   REG_OOK_FIX (Default: 0x0C)
  *
  *   NOTE: Fixed threshold for the Data Slicer in OOK mode Floor threshold for the Data Slicer in OOK when Peak mode is used.
  */
typedef enum
{
  FSK_OOK_REGOOKFIX_OKK_FIXED_THRESHOLD_MASK          =   0xFF              /*!<  OokFixedThreshold mask                                            */
} fsk_ook_regookfix_ook_fixed_threshold_t;


/**
  * @brief   REG_OOK_AVG
  */
/**
  * OokPeakThreshDec <7:5>
  *
  *   NOTE: Enables the Bit Synchronizer.
  */
typedef enum
{
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_MASK        =   ( 0b111 << 5U ),    /*!<  OokPeakThreshDec mask                                             */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_0           =   ( 0b000 << 5U ),    /*!<  once per chip                                         [ Default ] */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_1           =   ( 0b001 << 5U ),    /*!<  once every 2 chips                                                */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_2           =   ( 0b010 << 5U ),    /*!<  once every 4 chips                                                */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_3           =   ( 0b011 << 5U ),    /*!<  once every 8 chips                                                */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_4           =   ( 0b100 << 5U ),    /*!<  twice in each chip                                                */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_5           =   ( 0b101 << 5U ),    /*!<  4 times in each chip                                              */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_6           =   ( 0b110 << 5U ),    /*!<  8 times in each chip                                              */
  FSK_OOK_REGOOKAVG_OOK_PEAK_THRESH_DEC_7           =   ( 0b111 << 5U )     /*!<  16 times in each chip                                             */
} fsk_ook_regookavg_ook_peak_thresh_dec_t;


/**
  * OokAverageOffset <3:2>
  *
  *   NOTE: Static offset added to the threshold in average mode in order to reduce glitching activity (OOK only).
  */
typedef enum
{
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_OFFSET_MASK         =   ( 0b11 << 2U ),     /*!<  OokAverageOffset mask                                             */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_OFFSET_0_0_DB       =   ( 0b00 << 2U ),     /*!<  0.0 dB                                                [ Default ] */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_OFFSET_2_0_DB       =   ( 0b01 << 2U ),     /*!<  2.0 dB                                                            */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_OFFSET_4_0_DB       =   ( 0b10 << 2U ),     /*!<  4.0 dB                                                            */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_OFFSET_6_0_DB       =   ( 0b11 << 2U )     /*!<  6.0 dB                                                            */
} fsk_ook_regookavg_ook_average_offset_t;


/**
  * OokAverageThreshFilt <1:0>
  *
  *   NOTE: Filter coefficients in average mode of the OOK demodulator.
  */
typedef enum
{
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_THRESH_FILT_MASK    =   ( 0b11 << 0U ),     /*!<  OokAverageThreshFilt mask                                         */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_THRESH_FILT_0       =   ( 0b00 << 0U ),     /*!<  f_C ˜ chip rate / 32.p                                            */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_THRESH_FILT_1       =   ( 0b01 << 0U ),     /*!<  f_C ˜ chip rate / 8.p                                             */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_THRESH_FILT_2       =   ( 0b10 << 0U ),     /*!<  f_C ˜ chip rate / 4.p                                 [ Default ] */
  FSK_OOK_REGOOKAVG_OOK_AVERAGE_THRESH_FILT_3       =   ( 0b11 << 0U )      /*!<  f_C ˜ chip rate / 2.p                                             */
} fsk_ook_regookavg_ook_average_thresh_filt_t;


/**
  * @brief   REG_AFC_FEI
  */
/**
  * AgcStart <4> (Default: 0x00)
  *
  *   NOTE: Triggers an AGC sequence when set to 1.
  */
typedef enum
{
  FSK_OOK_REGAFCFEI_AGC_START_MASK                    =   ( 1U << 4U )      /*!<  AgcStart mask                                                    */
} fsk_ook_regafcfei_agc_start_t;


/**
  * AfcClear <1> (Default: 0x00)
  *
  *   NOTE: Clear AFC register set in Rx mode. Always reads 0.
  */
typedef enum
{
  FSK_OOK_REGAFCFEI_AFC_CLEAR_MASK                    =   ( 1U << 1U )      /*!<  AfcClear mask                                                    */
} fsk_ook_regafcfei_afc_clear_t;


/**
  * AfcAutoClearOn <0> 
  *
  *   NOTE: Only valid if AfcAutoOn is set.
  */
typedef enum
{
  FSK_OOK_REGAFCFEI_AFC_AUTO_CLEAR_ON_MASK            =   ( 1U << 0U ),     /*!<  AfcAutoClearOn mask                                                                 */
  FSK_OOK_REGAFCFEI_AFC_AUTO_CLEAR_ON_NOT_CLEAR       =   ( 0U << 0U ),     /*!<  AFC register is not cleared at the beginning of the automatic AFC phase [ Default ] */
  FSK_OOK_REGAFCFEI_AFC_AUTO_CLEAR_ON_CLEAR           =   ( 1U << 0U )      /*!<  AFC register is cleared at the beginning of the automatic AFC phase                 */
} fsk_ook_regafcfei_afc_auto_clear_on_t;


/**
  * @brief   REG_AFC_MSB (Default: 0x00)
  *
  *   NOTE: MSB of the AfcValue, 2's complement format. Can be used to overwrite the current AFC value.
  */
typedef enum
{
  FSK_OOK_REGAFCMSB_AFC_VALUE_MASK                      =   0xFF            /*!<  AfcValue mask                                                   */
} fsk_ook_regafcmsb_afc_value_t;


/**
  * @brief   REG_AFC_LSB (Default: 0x00)
  *
  *   NOTE: LSB of the AfcValue, 2's complement format. Can be used to overwrite the current AFC value.
  */
typedef enum
{
  FSK_OOK_REGAFCLSB_AFC_VALUE_MASK                      =   0xFF            /*!<  AfcValue mask                                                   */
} fsk_ook_regafclsb_afc_value_t;


/**
  * @brief   REG_FEI_MSB 
  *
  *   NOTE: MSB of the measured frequency offset, 2's complement. Must be read before RegFeiLsb.
  */
typedef enum
{
  FSK_OOK_REGFEIMSB_FEI_VALUE_MASK                      =   0xFF            /*!<  FeiValue mask                                                   */
} fsk_ook_regfeimsb_fei_value_t;


/**
  * @brief   REG_FEI_LSB 
  *
  *   NOTE: LSB of the measured frequency offset, 2's complement Frequency error = FeiValue x Fstep.
  */
typedef enum
{
  FSK_OOK_REGFEILSB_FEI_VALUE_MASK                      =   0xFF            /*!<  FeiValue mask                                                   */
} fsk_ook_regfeilsb_fei_value_t;


/**
  * @brief   REG_PREAMBLE_DETECT
  */
/**
  * PreambleDetectorOn <7>
  *
  *   NOTE: Enables Preamble detector when set to 1. The AGC settings supersede this bit during the startup / AGC phase.
  */
typedef enum
{   
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_ON_MASK       =   ( 1U << 7U ),     /*!<  PreambleDetectorOn mask                                           */
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_ON_TURNED_OFF =   ( 0U << 7U ),     /*!<  Turned off                                                        */
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_ON_TURNED_ON  =   ( 1U << 7U )      /*!<  Turned on                                             [ Default ] */
} fsk_ook_regpreambledetect_preamble_detector_on_t;


/**
  * PreambleDetectorSize <6:5>
  *
  *   NOTE: Number of Preamble bytes to detect to trigger an interrupt.
  */
typedef enum
{   
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_SIZE_MASK     =   ( 0b11 << 5U ),   /*!<  PreambleDetectorSize mask                                         */
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_SIZE_1_BYTE   =   ( 0b00 << 5U ),   /*!<  1 byte                                                            */
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_SIZE_2_BYTE   =   ( 0b01 << 5U ),   /*!<  2 byte                                                [ Default ] */
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_SIZE_3_BYTE   =   ( 0b10 << 5U )    /*!<  3 byte                                                            */
} fsk_ook_regpreambledetect_preamble_detector_size_t;


/**
  * PreambleDetectorTol <4:0> (Default: 0x0A)
  *
  *   NOTE: Number or chip errors tolerated over PreambleDetectorSize. 4 chips per bit.
  */
typedef enum
{   
  FSK_OOK_REGPREAMBLEDETECT_PREAMBLE_DETECTOR_TOL_MASK      =   ( 0b11111 << 0U ) /*!<  PreambleDetectorTol mask                                          */
} fsk_ook_regpreambledetect_preamble_detector_tol_t;


/**
  * @brief   REG_RX_TIMEOUT_1 (Default: 0x00)
  *
  *   NOTE: Timeout interrupt is generated TimeoutRxRssi *16*T bit after switching to Rx mode if Rssi interrupt doesn’t occur (i.e. RssiValue > RssiThreshold) 0x00: TimeoutRxRssi is disabled.
  */
typedef enum
{
  FSK_OOK_REGTIMEOUT1_TIMEOUT_RX_RSSI_MASK              =   0xFF            /*!<  TimeoutRxRssi mask                                              */
} fsk_ook_regrxtimeout1_timeout_rx_rssi_t;


/**
  * @brief   REG_RX_TIMEOUT_2 (Default: 0x00)
  *
  *   NOTE: Timeout interrupt is generated TimeoutRxPreamble *16*T bit after switching to Rx mode if Preamble interrupt doesn’t occur 0x00: TimeoutRxPreamble is disabled.
  */
typedef enum
{
  FSK_OOK_REGTIMEOUT2_TIMEOUT_RX_PREAMBLE_MASK          =   0xFF            /*!<  TimeoutRxPreamble mask                                          */
} fsk_ook_regrxtimeout2_timeout_rx_preamble_t;


/**
  * @brief   REG_RX_TIMEOUT_3 (Default: 0x00)
  *
  *   NOTE: Timeout interrupt is generated TimeoutRxPreamble *16*T bit after switching to Rx mode if Preamble interrupt doesn’t occur 0x00: TimeoutRxPreamble is disabled.
  */
typedef enum
{
  FSK_OOK_REGTIMEOUT3_TIMEOUT_SIGNAL_SYNC_MASK          =   0xFF            /*!<  TimeoutSignalSync mask                                          */
} fsk_ook_regrxtimeout3_timeout_sygnal_sync_t;


/**
  * @brief   REG_RX_TIMEOUT_3 (Default: 0x00)
  *
  *   NOTE: Additional delay before an automatic receiver restart is launched: Delay = InterPacketRxDelay*4*Tbit.
  */
typedef enum
{
  FSK_OOK_REGTIMEOUT3_INTER_PACKET_RX_DELAY_MASK        =   0xFF            /*!<  InterPacketRxDelay mask                                        */
} fsk_ook_regrxtimeout3_inter_packet_rx_delay_t;


/* FSK/OOK: RC Oscillator registers   */
/**
  * @brief   REG_OSC
  */
/**
  * RcCalStart <3>
  *
  *   NOTE: Triggers the calibration of the RC oscillator when set. Always reads 0. RC calibration must be triggered in Standby mode.
  */
typedef enum
{
  FSK_OOK_REGOSC_RC_CAL_START_MASK                      =   ( 1U << 3U )    /*!<  RcCalStart mask                                               */
} fsk_ook_regosc_rc_cal_start_t;


/**
  * ClkOut <2:0>
  *
  *   NOTE: Selects CLKOUT frequency.
  */
typedef enum
{
  FSK_OOK_REGOSC_CLK_OUT_MASK                           =   ( 0b111 << 0U ),  /*!<  ClkOut mask                                                   */
  FSK_OOK_REGOSC_CLK_OUT_0                              =   ( 0b000 << 0U ),  /*!<  FXOSC                                                         */
  FSK_OOK_REGOSC_CLK_OUT_1                              =   ( 0b001 << 0U ),  /*!<  FXOSC / 2                                                     */
  FSK_OOK_REGOSC_CLK_OUT_2                              =   ( 0b010 << 0U ),  /*!<  FXOSC / 4                                                     */
  FSK_OOK_REGOSC_CLK_OUT_3                              =   ( 0b011 << 0U ),  /*!<  FXOSC / 8                                                     */
  FSK_OOK_REGOSC_CLK_OUT_4                              =   ( 0b100 << 0U ),  /*!<  FXOSC / 16                                                    */
  FSK_OOK_REGOSC_CLK_OUT_5                              =   ( 0b101 << 0U ),  /*!<  FXOSC / 32                                                    */
  FSK_OOK_REGOSC_CLK_OUT_6                              =   ( 0b110 << 0U ),  /*!<  RC (automatically enabled)                                    */
  FSK_OOK_REGOSC_CLK_OUT_7                              =   ( 0b111 << 0U )   /*!<  OFF                                               [ Default ] */
} fsk_ook_regosc_clk_out_t;


/* FSK/OOK: Packet Handling registers   */
/**
  * @brief   REG_PREAMBLE_MSB (Default: 0x00)
  *
  *   NOTE: Size of the preamble to be sent (from TxStartCondition fulfilled). (MSB byte).
  */
typedef enum
{
  FSK_OOK_REGPREAMBLEMSB_PREAMBLE_SIZE_MASK               =   0xFF            /*!<  PreambleSize mask                                             */
} fsk_ook_regpreamblemsb_preamble_size_t;


/**
  * @brief   REG_PREAMBLE_LSB (Default: 0x00)
  *
  *   NOTE: Size of the preamble to be sent (from TxStartCondition fulfilled). (LSB byte).
  */
typedef enum
{
  FSK_OOK_REGPREAMBLELSB_PREAMBLE_SIZE_MASK               =   0xFF            /*!<  PreambleSize mask                                             */
} fsk_ook_regpreamblelsb_preamble_size_t;


/**
  * @brief   REG_SYNC_CONFIG
  */
/**
  * AutoRestartRxMode <7:6>
  *
  *   NOTE: Controls the automatic restart of the receiver after the reception of a valid packet (PayloadReady or CrcOk).
  */
typedef enum
{
  FSK_OOK_REGSYNCCONFIG_AUTO_RESTART_RX_MODE_MASK                               =   ( 0b11 << 6U ),   /*!<  AutoRestartRxMode mask                                      */
  FSK_OOK_REGSYNCCONFIG_AUTO_RESTART_RX_MODE_OFF                                =   ( 0b00 << 6U ),   /*!<  Off                                                         */
  FSK_OOK_REGSYNCCONFIG_AUTO_RESTART_RX_MODE_ON_WITHOUT_WAIT_FOR_PLL_TO_RELOCK  =   ( 0b01 << 6U ),   /*!<  On, without waiting for the PLL to re-lock      [ Default ] */
  FSK_OOK_REGSYNCCONFIG_AUTO_RESTART_RX_MODE_ON_WAIT_FOR_PLL_TO_LOCK            =   ( 0b10 << 6U )    /*!<  On, wait for the PLL to lock (frequency changed)            */
} fsk_ook_regsyncconfig_auto_restart_rx_mode_t;


/**
  * PreamblePolarity <5>
  *
  *   NOTE: Sets the polarity of the Preamble.
  */
typedef enum
{
  FSK_OOK_REGSYNCCONFIG_PREAMBLE_POLARITY_MASK            =   ( 1U << 5U ),   /*!<  PreamblePolarity mask                                        */
  FSK_OOK_REGSYNCCONFIG_PREAMBLE_POLARITY_0XAA            =   ( 0U << 5U ),   /*!<  PreamblePolarity 0xAA                            [ Default ] */
  FSK_OOK_REGSYNCCONFIG_PREAMBLE_POLARITY_0X55            =   ( 1U << 5U )    /*!<  PreamblePolarity 0x55                                        */
} fsk_ook_regsyncconfig_preamble_polarity_t;


/**
  * SyncOn <4>
  *
  *   NOTE: Enables the Sync word generation and detection.
  */
typedef enum
{
  FSK_OOK_REGSYNCCONFIG_SYNC_ON_MASK                      =   ( 1U << 4U ),   /*!<  SyncOn mask                                                 */
  FSK_OOK_REGSYNCCONFIG_SYNC_ON_OFF                       =   ( 0U << 4U ),   /*!<  SyncOn Off                                                  */
  FSK_OOK_REGSYNCCONFIG_SYNC_ON_ON                        =   ( 1U << 4U )    /*!<  SyncOn On                                       [ Default ] */
} fsk_ook_regsyncconfig_sync_on_t;


/**
  * FifoFillCondition <3>
  *
  *   NOTE: FIFO filling condition.
  */
typedef enum
{
  FSK_OOK_REGSYNCCONFIG_FIFO_FILL_CONDITION_MASK          =   ( 1U << 3U ),   /*!<  FifoFillCondition mask                                      */
  FSK_OOK_REGSYNCCONFIG_FIFO_FILL_CONDITION_0             =   ( 0U << 3U ),   /*!<  if SyncAddress interrupt occurs                 [ Default ] */
  FSK_OOK_REGSYNCCONFIG_FIFO_FILL_CONDITION_1             =   ( 1U << 3U )    /*!<  as long as FifoFillCondition is set                         */
} fsk_ook_regsyncconfig_fifo_fill_condition_t;


/**
  * SyncSize <2:0> (Default: 0x03)
  *
  *   NOTE: Size of the Sync word:
  *           - ( SyncSize + 1) bytes, ( SyncSize ) bytes if ioHomeOn =1
  */
typedef enum
{
  FSK_OOK_REGSYNCCONFIG_SYNC_SIZE_MASK                    =   ( 0b111 << 0U ) /*!<  SyncSize mask                                               */
} fsk_ook_regsyncconfig_sync_size_t;


/**
  * @brief   REG_SYNC_VALUE_1 (Default: 0x01)
  *
  *   NOTE: 1st byte of Sync word. (MSB byte) Used if SyncOn is set.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE1_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue1_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_2 (Default: 0x01)
  *
  *   NOTE: 2nd byte of Sync word Used if SyncOn is set and (SyncSize +1) >= 2.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE2_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue2_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_3 (Default: 0x01)
  *
  *   NOTE: 3rd byte of Sync word. Used if SyncOn is set and (SyncSize +1) >= 3.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE3_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue3_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_4 (Default: 0x01)
  *
  *   NOTE: 4rd byte of Sync word. Used if SyncOn is set and (SyncSize +1) >= 4.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE4_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue4_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_5 (Default: 0x01)
  *
  *   NOTE: 5rd byte of Sync word. Used if SyncOn is set and (SyncSize +1) >= 5.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE5_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue5_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_6 (Default: 0x01)
  *
  *   NOTE: 6rd byte of Sync word. Used if SyncOn is set and (SyncSize +1) >= 6.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE6_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue6_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_7 (Default: 0x01)
  *
  *   NOTE: 7rd byte of Sync word. Used if SyncOn is set and (SyncSize +1) >= 7.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE7_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue7_sync_value_t;


/**
  * @brief   REG_SYNC_VALUE_8 (Default: 0x01)
  *
  *   NOTE: 8rd byte of Sync word. Used if SyncOn is set and (SyncSize +1) = 8.
  */
typedef enum
{
  FSK_OOK_REGSYNCVALUE8_SYNC_VALUE_MASK                   =   0xFF            /*!<  SyncValue mask                                              */
} fsk_ook_regsyncvalue8_sync_value_t;


/**
  * @brief   REG_PACKET_CONFIG_1
  */
/**
  * PacketFormat <7>
  *
  *   NOTE: Defines the packet format used.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG1_PACKET_FORMAT_MASK             =   ( 1U << 7U ),   /*!<  PacketFormat mask                                           */
  FSK_OOK_REGPACKETCONFIG1_PACKET_FORMAT_FIXED_LENGTH     =   ( 0U << 7U ),   /*!<  Fixed length                                                */
  FSK_OOK_REGPACKETCONFIG1_PACKET_FORMAT_VARIABLE_LENGTH  =   ( 1U << 7U )    /*!<  Variable length                                 [ Default ] */
} fsk_ook_regpacketconfig1_packet_format_t;


/**
  * DcFree <6:5>
  *
  *   NOTE: Defines DC-free encoding/decoding performed.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG1_DC_FREE_MASK                   =   ( 0b11 << 5U ), /*!<  DcFree mask                                                 */
  FSK_OOK_REGPACKETCONFIG1_DC_FREE_NONE                   =   ( 0b00 << 5U ), /*!<  None (Off)                                      [ Default ] */
  FSK_OOK_REGPACKETCONFIG1_DC_FREE_MANCHESTER             =   ( 0b01 << 5U ), /*!<  Manchester                                                  */
  FSK_OOK_REGPACKETCONFIG1_DC_FREE_WHITENING              =   ( 0b10 << 5U )  /*!<  Whitening                                                   */
} fsk_ook_regpacketconfig1_dc_free_t;


/**
  * CrcOn <4>
  *
  *   NOTE: Enables CRC calculation/check (Tx/Rx).
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG1_CRC_ON_MASK                    =   ( 1U << 4U ),   /*!<  CrcOn mask                                                  */
  FSK_OOK_REGPACKETCONFIG1_CRC_ON_OFF                     =   ( 0U << 4U ),   /*!<  CrcOn off                                                   */
  FSK_OOK_REGPACKETCONFIG1_CRC_ON_ON                      =   ( 1U << 4U )    /*!<  CrcOn on                                        [ Default ] */
} fsk_ook_regpacketconfig1_crc_on_t;


/**
  * CrcAutoClearOff <3>
  *
  *   NOTE: Defines the behavior of the packet handler when CRC check fails.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG1_CRC_AUTO_CLEAR_OFF_MASK            =   ( 1U << 3U ), /*!<  CrcAutoClearOff mask                                                                        */
  FSK_OOK_REGPACKETCONFIG1_CRC_AUTO_CLEAR_OFF_CLEAR_FIFO      =   ( 0U << 3U ), /*!<  Clear FIFO and restart new packet reception. No PayloadReady interrupt issued   [ Default ] */
  FSK_OOK_REGPACKETCONFIG1_CRC_AUTO_CLEAR_OFF_NOT_CLEAR_FIFO  =   ( 1U << 3U )  /*!<  Do not clear FIFO. PayloadReady interrupt issued                                            */
} fsk_ook_regpacketconfig1_crc_auto_clear_off_t;


/**
  * AddressFiltering <2:1>
  *
  *   NOTE: Defines address based filtering in Rx.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG1_ADDRESS_FILTERING_MASK         =   ( 0b11 << 1U ), /*!<  AddressFiltering mask                                       */
  FSK_OOK_REGPACKETCONFIG1_ADDRESS_FILTERING_0            =   ( 0b00 << 1U ), /*!<  None (Off)                                      [ Default ] */
  FSK_OOK_REGPACKETCONFIG1_ADDRESS_FILTERING_1            =   ( 0b01 << 1U ), /*!<  Address field must match NodeAddress                        */
  FSK_OOK_REGPACKETCONFIG1_ADDRESS_FILTERING_2            =   ( 0b10 << 1U )  /*!<  Address field must match NodeAddress or BroadcastAddress    */
} fsk_ook_regpacketconfig1_address_filtering_t;


/**
  * CrcWhiteningType <0>
  *
  *   NOTE: Selects the CRC and whitening algorithms.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG1_CRC_WHITENING_TYPE_MASK        =   ( 1U << 0U ),   /*!<  CrcWhiteningType mask                                         */
  FSK_OOK_REGPACKETCONFIG1_CRC_WHITENING_TYPE_0           =   ( 0U << 0U ),   /*!<  CCITT CRC implementation with standard whitening  [ Default ] */
  FSK_OOK_REGPACKETCONFIG1_CRC_WHITENING_TYPE_1           =   ( 1U << 0U )    /*!<  IBM CRC implementation with alternate whitening               */
} fsk_ook_regpacketconfig1_crc_whitening_type_t;


/**
  * @brief   REG_PACKET_CONFIG_2
  */
/**
  * DataMode <6>
  *
  *   NOTE: Data processing mode.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG2_DATA_MODE_MASK                 =   ( 1U << 6U ),   /*!<  DataMode mask                                               */
  FSK_OOK_REGPACKETCONFIG2_DATA_MODE_CONTINUOUS_MODE      =   ( 0U << 6U ),   /*!<  Continuous mode                                             */
  FSK_OOK_REGPACKETCONFIG2_DATA_MODE_PACKET_MODE          =   ( 1U << 6U )    /*!<  Packet mode                                     [ Default ] */
} fsk_ook_regpacketconfig2_data_mode_t;


/**
  * IoHomeOn <5>
  *
  *   NOTE: Enables the io-homecontrol compatibility mode.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG2_IO_HOME_ON_MASK                =   ( 1U << 5U ),   /*!<  IoHomeOn mask                                               */
  FSK_OOK_REGPACKETCONFIG2_IO_HOME_ON_DISABLED            =   ( 0U << 5U ),   /*!<  Disabled                                        [ Default ] */
  FSK_OOK_REGPACKETCONFIG2_IO_HOME_ON_ENABLED             =   ( 1U << 5U )    /*!<  Enabled                                                     */
} fsk_ook_regpacketconfig2_io_home_on_t;


/**
  * IoHomePowerFrame <4> (Default: 0x00)
  *
  *   NOTE: reserved - Linked to io-homecontrol compatibility mode.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG2_IO_HOME_POWER_FRAME_MASK       =   ( 1U << 4U )    /*!<  IoHomePowerFrame mask                                       */
} fsk_ook_regpacketconfig2_io_home_power_frame_t;


/**
  * BeaconOn <3> (Default: 0x00)
  *
  *   NOTE: Enables the Beacon mode in Fixed packet format.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG2_BEACON_ON_MASK                 =   ( 1U << 3U )    /*!<  BeaconOn mask                                               */
} fsk_ook_regpacketconfig2_beacon_on_t;


/**
  * PayloadLength <2:0> (Default: 0x00)
  *
  *   NOTE: Packet Length Most significant bits.
  */
typedef enum
{
  FSK_OOK_REGPACKETCONFIG2_PAYLOAD_LENGTH_MASK            =   ( 0b111 << 0U ) /*!<  PayloadLength mask                                          */
} fsk_ook_regpacketconfig2_payload_length_t;


/**
  * @brief   REG_PAYLOAD_LENGTH (Default: 0x40)
  *
  *   NOTE: If PacketFormat = 0 (fixed), payload length.
  *         If PacketFormat = 1 (variable), max length in Rx, not used in Tx.
  */
typedef enum
{
  FSK_OOK_REGPAYLOADLENGTH_PAYLOAD_LENGTH_MASK            =   0xFF            /*!<  PayloadLength mask                                          */
} fsk_ook_regpayloadlength_payload_length_t;


/**
  * @brief   REG_NODE_ADRS (Default: 0x00)
  *
  *   NOTE: Node address used in address filtering.
  */
typedef enum
{
  FSK_OOK_REGNODEADRS_NODE_ADDRESS_MASK                   =   0xFF            /*!<  NodeAddress mask                                            */
} fsk_ook_regnodeadrs_node_address_t;


/**
  * @brief   REG_BROADCAST_ADRS (Default: 0x00)
  *
  *   NOTE: Broadcast address used in address filtering.
  */
typedef enum
{
  FSK_OOK_REGBROADCASTADRS_BROADCAST_ADDRESS_MASK         =   0xFF            /*!<  BroadcastAddress mask                                       */
} fsk_ook_regbroadcastadrs_broadcast_address_t;


/**
  * @brief   REG_FIFO_THRESH
  */
/**
  * TxStartCondition <7>
  *
  *   NOTE: Defines the condition to start packet transmission.
  */
typedef enum
{
  FSK_OOK_REGFIFOTHRESH_TX_START_CONDITION_MASK           =   ( 1U << 7U ),   /*!<  TxStartCondition mask                                                   */
  FSK_OOK_REGFIFOTHRESH_TX_START_CONDITION_FIFO_LEVEL     =   ( 0U << 7U ),   /*!<  FifoLevel (i.e. the number of bytes in the FIFO exceeds FifoThreshold)  */
  FSK_OOK_REGFIFOTHRESH_TX_START_CONDITION_FIFO_EMPTY     =   ( 1U << 7U )    /*!<  FifoEmpty goes low (i.e. at least one byte in the FIFO)     [ Default ] */
} fsk_ook_regfifothresh_tx_start_condition_t;


/**
  * FifoThreshold <5:0> (Default: 0x0F)
  *
  *   NOTE: Used to trigger FifoLevel interrupt, when: number of bytes in FIFO >= FifoThreshold + 1.
  */
typedef enum
{
  FSK_OOK_REGFIFOTHRESH_FIFO_THRESHOLD_MASK               =   ( 0b111111 << 0U )  /*!<  FifoThreshold mask                                          */
} fsk_ook_regfifothresh_fifo_threshold_t;


/* FSK/OOK: Sequencer registers   */
/**
  * @brief   REG_SEQ_CONFIG_1
  */
/**
  * SequencerStart <7>
  *
  *   NOTE: Controls the top level Sequencer When set to '1', executes the 'Start' transition. The sequencer can only be enabled when the chip is in Sleep or Standby mode.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_SEQUENCER_START_MASK              =   ( 1U << 7U ),     /*!<  SequencerStart mask                                           */
  FSK_OOK_REGSEQCONFIG1_SEQUENCER_START_START_TRANSITION  =   ( 1U << 7U )      /*!<  executes the 'Start' transition                               */
} fsk_ook_regseqconfig1_sequencer_start_t;


/**
  * SequencerStop <6>
  *
  *   NOTE: Forces the Sequencer Off. Always reads '0'.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_SEQUENCER_STOP_MASK                =   ( 1U << 6U ),     /*!<  SequencerStop mask                                            */
  FSK_OOK_REGSEQCONFIG1_SEQUENCER_STOP_FORCE_SEQUENCER_OFF =   ( 1U << 6U )      /*!<  Forces the Sequencer Off                                      */
} fsk_ook_regseqconfig1_sequencer_stop_t;


/**
  * IdleMode <5>
  *
  *   NOTE: Selects chip mode during the state.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_IDLE_MODE_MASK                    =   ( 1U << 5U ),     /*!<  IdleMode mask                                                 */
  FSK_OOK_REGSEQCONFIG1_IDLE_MODE_STANDBY_MODE            =   ( 0U << 5U ),     /*!<  Standby mode                                      [ Default ] */
  FSK_OOK_REGSEQCONFIG1_IDLE_MODE_SLEEP_MODE              =   ( 1U << 5U )      /*!<  Sleep mode                                                    */
} fsk_ook_regseqconfig1_idle_mode_t;


/**
  * FromStart <4:3>
  *
  *   NOTE: Controls the Sequencer transition when SequencerStart is set to 1 in Sleep or Standby mode.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_FROM_START_MASK                       =   ( 0b11 << 3U ), /*!<  FromStart mask                                                */
  FSK_OOK_REGSEQCONFIG1_FROM_START_TO_LOW_POWER_SELECTION     =   ( 0b00 << 3U ), /*!<  to LowPowerSelection                              [ Default ] */
  FSK_OOK_REGSEQCONFIG1_FROM_START_TO_RECEIVE_STATE           =   ( 0b01 << 3U ), /*!<  to Receive state                                              */
  FSK_OOK_REGSEQCONFIG1_FROM_START_TO_TRANSMIT_STATE          =   ( 0b10 << 3U ), /*!<  to Transmit state                                             */
  FSK_OOK_REGSEQCONFIG1_FROM_START_TO_TX_STATE_ON_FIFO_LEVEL  =   ( 0b11 << 3U )  /*!<  to Transmit state on a FifoLevel interrupt                    */
} fsk_ook_regseqconfig1_from_start_t;


/**
  * LowPowerSelection <2>
  *
  *   NOTE: Selects the Sequencer LowPower state after a to LowPowerSelection transition.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_LOW_POWER_SELECTION_MASK          =   ( 1U << 2U ),     /*!<  LowPowerSelection mask                                              */
  FSK_OOK_REGSEQCONFIG1_LOW_POWER_SELECTION_0             =   ( 0U << 2U ),     /*!<  SequencerOff state with chip on Initial mode            [ Default ] */
  FSK_OOK_REGSEQCONFIG1_LOW_POWER_SELECTION_1             =   ( 1U << 2U )      /*!<  Idle state with chip on Standby or Sleep mode depending on IdleMode */
} fsk_ook_regseqconfig1_low_power_selection_t;


/**
  * FromIdle <1>
  *
  *   NOTE: Controls the Sequencer transition from the Idle state on a T1 interrupt.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_FROM_IDLE_MASK                    =   ( 1U << 1U ),     /*!<  FromIdle mask                                                 */
  FSK_OOK_REGSEQCONFIG1_FROM_IDLE_TO_TRANSMIT_STATE       =   ( 0U << 1U ),     /*!<  to Transmit state                                 [ Default ] */
  FSK_OOK_REGSEQCONFIG1_FROM_IDLE_TO_RECEIVE_STATE        =   ( 1U << 1U )      /*!<  to Receive state                                              */
} fsk_ook_regseqconfig1_from_idle_t;


/**
  * FromTransmit <0>
  *
  *   NOTE: Controls the Sequencer transition from the Transmit state.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG1_FROM_TRANSMIT_MASK                    =   ( 1U << 0U ),   /*!<  FromTransmit mask                                             */
  FSK_OOK_REGSEQCONFIG1_FROM_TRANSMIT_TO_LOW_POWER_SELECTION  =   ( 0U << 0U ),   /*!<  to LowPowerSelection on a PacketSent interrupt    [ Default ] */
  FSK_OOK_REGSEQCONFIG1_FROM_TRANSMIT_TO_RECEIVE_STATE        =   ( 1U << 0U )    /*!<  to Receive state on a PacketSent interrupt                    */
} fsk_ook_regseqconfig1_from_transmit_t;


/**
  * @brief   REG_SEQ_CONFIG_2
  */
/**
  * FromReceive <7:5>
  *
  *   NOTE: Controls the Sequencer transition from the Receive state.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_MASK                 =   ( 0b111 << 5U ),  /*!<  FromReceive mask                                              */
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_0                    =   ( 0b001 << 5U ),  /*!<  to PacketReceived state on a PayloadReady interrupt           */
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_1                    =   ( 0b010 << 5U ),  /*!<  to LowPowerSelection on a PayloadReady interrupt              */
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_2                    =   ( 0b011 << 5U ),  /*!<  to PacketReceived state on a CrcOk interrupt                  */
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_3                    =   ( 0b100 << 5U ),  /*!<  to SequencerOff state on a Rssi interrupt                     */
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_4                    =   ( 0b101 << 5U ),  /*!<  to SequencerOff state on a SyncAddress interrupt              */
  FSK_OOK_REGSEQCONFIG2_FROM_RECEIVE_5                    =   ( 0b110 << 5U )   /*!<  to SequencerOff state on a PreambleDetect interrupt           */
} fsk_ook_regseqconfig2_from_receive_t;


/**
  * FromRxTimeout <4:3>
  *
  *   NOTE: Controls the state-machine transition from the Receive state on a RxTimeout interrupt (and on PayloadReady if FromReceive = 011).
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG2_FROM_RX_TIMEOUT_MASK                    =   ( 0b11 << 3U ), /*!<  FromRxTimeout mask                                            */
  FSK_OOK_REGSEQCONFIG2_FROM_RX_TIMEOUT_TO_RECEIVE_STATE        =   ( 0b00 << 3U ), /*!<  to Receive State, via ReceiveRestart              [ Default ] */
  FSK_OOK_REGSEQCONFIG2_FROM_RX_TIMEOUT_TO_TRANSMIT_STATE       =   ( 0b01 << 3U ), /*!<  to Transmit state                                             */
  FSK_OOK_REGSEQCONFIG2_FROM_RX_TIMEOUT_TO_LOW_POWER_SELECTION  =   ( 0b10 << 3U ), /*!<  to LowPowerSelection                                          */
  FSK_OOK_REGSEQCONFIG2_FROM_RX_TIMEOUT_SEQUENCER_OFF_STATE     =   ( 0b11 << 3U )  /*!<  to SequencerOff state                                         */
} fsk_ook_regseqconfig2_from_rx_timeout_t;


/**
  * FromPacketReceived <2:0>
  *
  *   NOTE: Controls the state-machine transition from the PacketReceived state.
  */
typedef enum
{
  FSK_OOK_REGSEQCONFIG2_FROM_PACKET_RECEIVED_MASK                   =   ( 0b111 << 0U ), /*!<  FromPacketReceived mask                                  */
  FSK_OOK_REGSEQCONFIG2_FROM_PACKET_RECEIVED_TO_SEQUENCER_OFF_STATE =   ( 0b000 << 0U ), /*!<  to SequencerOff state                        [ Default ] */
  FSK_OOK_REGSEQCONFIG2_FROM_PACKET_RECEIVED_TO_TRANSMIT_STATE      =   ( 0b001 << 0U ), /*!<  to Transmit state on a FifoEmpty interrupt               */
  FSK_OOK_REGSEQCONFIG2_FROM_PACKET_RECEIVED_TO_LOW_POWER_SELECTION =   ( 0b010 << 0U ), /*!<  to LowPowerSelection                                     */
  FSK_OOK_REGSEQCONFIG2_FROM_PACKET_RECEIVED_TO_RECEIVE_VIA_FS_MODE =   ( 0b011 << 0U ), /*!<  to Receive via FS mode, if frequency was changed         */
  FSK_OOK_REGSEQCONFIG2_FROM_PACKET_RECEIVED_TO_RECEIVE_STATE       =   ( 0b100 << 0U )  /*!<  to Receive state (no frequency change)                   */
} fsk_ook_regseqconfig2_from_packet_received_t;


/**
  * @brief   REG_TIMER_RESOL
  */
/**
  * Timer1Resolution <3:2>
  *
  *   NOTE: Resolution of Timer 1.
  */
typedef enum
{
  FSK_OOK_REGTIMERRESOL_TIMER1_RESOLUTION_MASK            =   ( 0b11 << 2U ),   /*!<  Timer1Resolution mask                                         */
  FSK_OOK_REGTIMERRESOL_TIMER1_RESOLUTION_TIMER1_DISABLED =   ( 0b00 << 2U ),   /*!<  Timer1 disabled                                   [ Default ] */
  FSK_OOK_REGTIMERRESOL_TIMER1_RESOLUTION_64_US           =   ( 0b01 << 2U ),   /*!<  64 us                                                         */
  FSK_OOK_REGTIMERRESOL_TIMER1_RESOLUTION_4_1_MS          =   ( 0b10 << 2U ),   /*!<  4.1 ms                                                        */
  FSK_OOK_REGTIMERRESOL_TIMER1_RESOLUTION_262_MS          =   ( 0b11 << 2U )    /*!<  262 ms                                                        */
} fsk_ook_regtimerresol_timer1_resolution_t;


/**
  * Timer2Resolution <1:0>
  *
  *   NOTE: Resolution of Timer 2.
  */
typedef enum
{
  FSK_OOK_REGTIMERRESOL_TIMER2_RESOLUTION_MASK            =   ( 0b11 << 0U ),   /*!<  Timer2Resolution mask                                         */
  FSK_OOK_REGTIMERRESOL_TIMER2_RESOLUTION_TIMER2_DISABLED =   ( 0b00 << 0U ),   /*!<  Timer2 disabled                                   [ Default ] */
  FSK_OOK_REGTIMERRESOL_TIMER2_RESOLUTION_64_US           =   ( 0b01 << 0U ),   /*!<  64 us                                                         */
  FSK_OOK_REGTIMERRESOL_TIMER2_RESOLUTION_4_1_MS          =   ( 0b10 << 0U ),   /*!<  4.1 ms                                                        */
  FSK_OOK_REGTIMERRESOL_TIMER2_RESOLUTION_262_MS          =   ( 0b11 << 0U )    /*!<  262 ms                                                        */
} fsk_ook_regtimerresol_timer2_resolution_t;


/**
  * @brief   REG_TIMER1_COEF (Default: 0xF5)
  *
  *   NOTE: Multiplying coefficient for Timer 1.
  */
typedef enum
{
  FSK_OOK_REGTIMER1COEF_TIMER1_COEFFICIENT_MASK           =   0xFF              /*!<  Timer1Coefficient mask                                        */
} fsk_ook_regtimer1coef_timer1_coefficient_t;


/**
  * @brief   REG_TIMER2_COEF (Default: 0x20)
  *
  *   NOTE: Multiplying coefficient for Timer 2.
  */
typedef enum
{
  FSK_OOK_REGTIMER2COEF_TIMER2_COEFFICIENT_MASK           =   0xFF              /*!<  Timer2Coefficient mask                                        */
} fsk_ook_regtimer2coef_timer2_coefficient_t;


/* FSK/OOK: Service registers   */
/**
  * @brief   REG_IMAGE_CAL
  */
/**
  * AutoImageCalOn <7>
  *
  *   NOTE: Resolution of Timer 1.
  */
typedef enum
{
  FSK_OOK_REGIMAGECAL_AUTO_IMAGE_CAL_ON_MASK              =   ( 1U << 7U ),     /*!<  AutoImageCalOn mask                                                               */
  FSK_OOK_REGIMAGECAL_AUTO_IMAGE_CAL_ON_0                 =   ( 0U << 7U ),     /*!<  Calibration of the receiver depending on the temperature is disabled  [ Default ] */
  FSK_OOK_REGIMAGECAL_AUTO_IMAGE_CAL_ON_1                 =   ( 1U << 7U )      /*!<  Calibration of the receiver depending on the temperature enabled                  */
} fsk_ook_regimagecal_auto_image_cal_on_t;


/**
  * ImageCalRunning <5>
  *
  *   NOTE: Set to 1 while the Image and RSSI calibration are running. Toggles back to 0 when the process is completed.
  */
typedef enum
{
  FSK_OOK_REGIMAGECAL_IMAGE_CAL_RUNNING_MASK              =   ( 1U << 5U )      /*!<  ImageCalRunning mask                                          */
} fsk_ook_regimagecal_image_cal_running_t;


/**
  * TempChange <3>
  *
  *   NOTE: IRQ flag witnessing a temperature change exceeding TempThreshold since the last Image and RSSI calibration.
  */
typedef enum
{
  FSK_OOK_REGIMAGECAL_TEMP_CHANGE_MASK                    =   ( 1U << 3U )      /*!<  TempChange mask                                               */
} fsk_ook_regimagecal_temp_change_t;


/**
  * TempThreshold <2:1>
  *
  *   NOTE: Temperature change threshold to trigger a new I/Q calibration.
  */
typedef enum
{
  FSK_OOK_REGIMAGECAL_TEMP_THRESHOLD_MASK                 =   ( 0b11 << 1U ),     /*!<  TempThreshold mask                                            */
  FSK_OOK_REGIMAGECAL_TEMP_THRESHOLD_5_C                  =   ( 0b00 << 1U ),     /*!<  TempThreshold 5C                                              */
  FSK_OOK_REGIMAGECAL_TEMP_THRESHOLD_10_C                 =   ( 0b01 << 1U ),     /*!<  TempThreshold 10C                                 [ Default ] */
  FSK_OOK_REGIMAGECAL_TEMP_THRESHOLD_15_C                 =   ( 0b10 << 1U ),     /*!<  TempThreshold 15C                                             */
  FSK_OOK_REGIMAGECAL_TEMP_THRESHOLD_20_C                 =   ( 0b11 << 1U )      /*!<  TempThreshold 20C                                             */
} fsk_ook_regimagecal_temp_threshold_t;


/**
  * TempMonitorOff <0>
  *
  *   NOTE: Controls the temperature monitor operation.
  */
typedef enum
{
  FSK_OOK_REGIMAGECAL_TEMP_MONITOR_OFF_MASK                     =   ( 1U << 0U ),   /*!<  TempMonitorOff mask                                                           */
  FSK_OOK_REGIMAGECAL_TEMP_MONITOR_OFF_TEMP_MONITORING_DONE     =   ( 0U << 0U ),   /*!<  Temperature monitoring done in all modes except Sleep and Standby [ Default ] */
  FSK_OOK_REGIMAGECAL_TEMP_MONITOR_OFF_TEMP_MONITORING_STOPPED  =   ( 1U << 0U )    /*!<  Temperature monitoring stopped                                                */
} fsk_ook_regimagecal_temp_monitor_off_t;


/**
  * @brief   REG_TEMP 
  *
  *   NOTE: Measured temperature -1°C per Lsb Needs calibration for absolute accuracy.
  */
typedef enum
{
  FSK_OOK_REGTEMP_TEMP_VALUE_MASK                           =   0xFF              /*!<  TempValue mask                                                */
} fsk_ook_regtemp_temp_value_t;


/**
  * @brief   REG_LOW_BAT
  */
/**
  * LowBatOn <3>
  *
  *   NOTE: Low Battery detector enable signal.
  */
typedef enum
{
  FSK_OOK_REGLOWBAT_LOW_BAT_ON_MASK                       =   ( 1U << 3U ),     /*!<  LowBatOn mask                                                   */
  FSK_OOK_REGLOWBAT_LOW_BAT_ON_DISABLED                   =   ( 0U << 3U ),     /*!<  LowBat detector disabled                            [ Default ] */
  FSK_OOK_REGLOWBAT_LOW_BAT_ON_ENABLED                    =   ( 1U << 3U )      /*!<  LowBat detector enabled                                         */
} fsk_ook_reglowbat_low_bat_on_t;


/**
  * LowBatTrim <2:0>
  *
  *   NOTE: Trimming of the LowBat threshold.
  */
typedef enum
{
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_MASK                     =   ( 0b111 << 0U ),  /*!<  LowBatTrim mask                                                 */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_1_695_V                  =   ( 0b000 << 0U ),  /*!<  LowBatTrim 1.695 V                                              */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_1_764_V                  =   ( 0b001 << 0U ),  /*!<  LowBatTrim 1.764 V                                              */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_1_835_V                  =   ( 0b010 << 0U ),  /*!<  LowBatTrim 1.835 V                                  [ Default ] */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_1_905_V                  =   ( 0b011 << 0U ),  /*!<  LowBatTrim 1.905 V                                              */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_1_976_V                  =   ( 0b100 << 0U ),  /*!<  LowBatTrim 1.976 V                                              */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_2_045_V                  =   ( 0b101 << 0U ),  /*!<  LowBatTrim 2.045 V                                              */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_2_116_V                  =   ( 0b110 << 0U ),  /*!<  LowBatTrim 2.116 V                                              */
  FSK_OOK_REGLOWBAT_LOW_BAT_TRIM_2_185_V                  =   ( 0b111 << 0U )   /*!<  LowBatTrim 2.185 V                                              */
} fsk_ook_reglowbat_low_bat_trim_t;


/* FSK/OOK: Status registers   */
/**
  * @brief   REG_IRQ_FLAGS_1
  */
/**
  * ModeReady <7>
  *
  *   NOTE: Set when the operation mode requested in Mode, is ready.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_MODE_RADY_MASK                     =   ( 1U << 7U ),     /*!<  ModeReady mask                                                  */
  FSK_OOK_REGIRQFLAGS1_MODE_RADY_HIGH                     =   ( 1U << 7U ),     /*!<  ModeReady High                                                  */
  FSK_OOK_REGIRQFLAGS1_MODE_RADY_LOW                      =   ( 0U << 7U )      /*!<  ModeReady Low                                                   */
} fsk_ook_regirqflags1_mode_ready_t;


/**
  * RxReady <6>
  *
  *   NOTE: Set in Rx mode, after RSSI, AGC and AFC. Cleared when leaving Rx.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_RX_READY_MASK                      =   ( 1U << 6U ),     /*!<  RxReady mask                                                    */
  FSK_OOK_REGIRQFLAGS1_RX_READY_HIGH                      =   ( 1U << 6U ),     /*!<  RxReady High                                                    */
  FSK_OOK_REGIRQFLAGS1_RX_READY_LOW                       =   ( 0U << 6U )      /*!<  RxReady Low                                                     */
} fsk_ook_regirqflags1_rx_ready_t;


/**
  * TxReady <5>
  *
  *   NOTE: Set in Tx mode, after PA ramp-up. Cleared when leaving Tx.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_TX_READY_MASK                      =   ( 1U << 5U ),     /*!<  TxReady mask                                                    */
  FSK_OOK_REGIRQFLAGS1_TX_READY_HIGH                      =   ( 1U << 5U ),     /*!<  TxReady High                                                    */
  FSK_OOK_REGIRQFLAGS1_TX_READY_LOW                       =   ( 0U << 5U )      /*!<  TxReady Low                                                     */
} fsk_ook_regirqflags1_tx_ready_t;


/**
  * PllLock <4>
  *
  *   NOTE: Set (in FS, Rx or Tx) when the PLL is locked. Cleared when it is not.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_PLL_LOCK_MASK                      =   ( 1U << 4U ),     /*!<  PllLock mask                                                    */
  FSK_OOK_REGIRQFLAGS1_PLL_LOCK_HIGH                      =   ( 1U << 4U ),     /*!<  PllLock High                                                    */
  FSK_OOK_REGIRQFLAGS1_PLL_LOCK_LOW                       =   ( 0U << 4U )      /*!<  PllLock Low                                                     */
} fsk_ook_regirqflags1_pll_lock_t;


/**
  * Rssi <3>
  *
  *   NOTE: Set in Rx when the RssiValue exceeds RssiThreshold. Cleared when leaving Rx or setting this bit to 1.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_RSSI_MASK                          =   ( 1U << 3U ),     /*!<  Rssi mask                                                       */
  FSK_OOK_REGIRQFLAGS1_RSSI_HIGH                          =   ( 1U << 3U ),     /*!<  Rssi High                                                       */
  FSK_OOK_REGIRQFLAGS1_RSSI_LOW                           =   ( 0U << 3U )      /*!<  Rssi Low                                                        */
} fsk_ook_regirqflags1_rssi_t;


/**
  * Timeout <2>
  *
  *   NOTE: Set when a timeout occurs Cleared when leaving Rx or FIFO is emptied.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_TIMEOUT_MASK                       =   ( 1U << 2U ),     /*!<  Timeout mask                                                    */
  FSK_OOK_REGIRQFLAGS1_TIMEOUT_HIGH                       =   ( 1U << 2U ),     /*!<  Timeout High                                                    */
  FSK_OOK_REGIRQFLAGS1_TIMEOUT_LOW                        =   ( 0U << 2U )      /*!<  Timeout Low                                                     */
} fsk_ook_regirqflags1_timeout_t;


/**
  * PreambleDetect <1>
  *
  *   NOTE: Set when the Preamble Detector has found valid Preamble. bit clear when set to 1.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_PREAMBLE_DETECT_MASK               =   ( 1U << 1U ),     /*!<  PreambleDetect mask                                             */
  FSK_OOK_REGIRQFLAGS1_PREAMBLE_DETECT_HIGH               =   ( 1U << 1U ),     /*!<  PreambleDetect High                                             */
  FSK_OOK_REGIRQFLAGS1_PREAMBLE_DETECT_LOW                =   ( 0U << 1U )      /*!<  PreambleDetect Low                                              */
} fsk_ook_regirqflags1_preamble_detect_t;


/**
  * SyncAddressMatch <0>
  *
  *   NOTE: Set when Sync and Address (if enabled) are detected. Cleared when leaving Rx or FIFO is emptied. This bit is read only in Packet mode, rwc in Continuous mode.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS1_SYNC_ADDRESS_MATCH_MASK            =   ( 1U << 0U ),     /*!<  SyncAddressMatch mask                                           */
  FSK_OOK_REGIRQFLAGS1_SYNC_ADDRESS_MATCH_HIGH            =   ( 1U << 0U ),     /*!<  SyncAddressMatch High                                           */
  FSK_OOK_REGIRQFLAGS1_SYNC_ADDRESS_MATCH_LOW             =   ( 0U << 0U )      /*!<  SyncAddressMatch Low                                            */
} fsk_ook_regirqflags1_sync_address_match_t;


/**
  * @brief   REG_IRQ_FLAGS_2
  */
/**
  * FifoFull <7>
  *
  *   NOTE: Set when FIFO is full (i.e. contains 66 bytes), else cleared.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_FIFO_FULL_MASK                     =   ( 1U << 7U ),     /*!<  FifoFull mask                                                   */
  FSK_OOK_REGIRQFLAGS2_FIFO_FULL_HIGH                     =   ( 1U << 7U ),     /*!<  FifoFull High                                                   */
  FSK_OOK_REGIRQFLAGS2_FIFO_FULL_LOW                      =   ( 0U << 7U )      /*!<  FifoFull Low                                                    */
} fsk_ook_regirqflags2_fifo_full_t;


/**
  * FifoEmpty <6>
  *
  *   NOTE: Set when FIFO is empty, and cleared when there is at least 1 byte in the FIFO.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_FIFO_EMPTY_MASK                    =   ( 1U << 6U ),     /*!<  FifoEmpty mask                                                  */
  FSK_OOK_REGIRQFLAGS2_FIFO_EMPTY_HIGH                    =   ( 1U << 6U ),     /*!<  FifoEmpty High                                                  */
  FSK_OOK_REGIRQFLAGS2_FIFO_EMPTY_LOW                     =   ( 0U << 6U )      /*!<  FifoEmpty Low                                                   */
} fsk_ook_regirqflags2_fifo_empty_t;


/**
  * FifoLevel <5>
  *
  *   NOTE: Set when the number of bytes in the FIFO strictly exceeds FifoThreshold , else cleared.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_FIFO_LEVEL_MASK                    =   ( 1U << 5U ),     /*!<  FifoLevel mask                                                  */
  FSK_OOK_REGIRQFLAGS2_FIFO_LEVEL_HIGH                    =   ( 1U << 5U ),     /*!<  FifoLevel High                                                  */
  FSK_OOK_REGIRQFLAGS2_FIFO_LEVEL_LOW                     =   ( 0U << 5U )      /*!<  FifoLevel Low                                                   */
} fsk_ook_regirqflags2_fifo_level_t;


/**
  * FifoOverrun <4>
  *
  *   NOTE: Set when FIFO overrun occurs. (except in Sleep mode) Flag(s) and FIFO are cleared when this bit is set. The FIFO then becomes immediately available for the next transmission / reception.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_FIFO_OVERRUN_MASK                  =   ( 1U << 4U ),     /*!<  FifoOverrun mask                                                */
  FSK_OOK_REGIRQFLAGS2_FIFO_OVERRUN_HIGH                  =   ( 1U << 4U ),     /*!<  FifoOverrun High                                                */
  FSK_OOK_REGIRQFLAGS2_FIFO_OVERRUN_LOW                   =   ( 0U << 4U )      /*!<  FifoOverrun Low                                                 */
} fsk_ook_regirqflags2_fifo_overrun_t;


/**
  * PacketSent <3>
  *
  *   NOTE: Set in Tx when the complete packet has been sent. Cleared when exiting Tx.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_PACKET_SENT_MASK                   =   ( 1U << 3U ),     /*!<  PacketSent mask                                                 */
  FSK_OOK_REGIRQFLAGS2_PACKET_SENT_HIGH                   =   ( 1U << 3U ),     /*!<  PacketSent High                                                 */
  FSK_OOK_REGIRQFLAGS2_PACKET_SENT_LOW                    =   ( 0U << 3U )      /*!<  PacketSent Low                                                  */
} fsk_ook_regirqflags2_packet_sent_t;


/**
  * PayloadReady <2>
  *
  *   NOTE: Set in Rx when the payload is ready (i.e. last byte received and CRC, if enabled and CrcAutoClearOff is cleared , is Ok). Cleared when FIFO is empty.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_PAYLOAD_READY_MASK                 =   ( 1U << 2U ),     /*!<  PayloadReady mask                                               */
  FSK_OOK_REGIRQFLAGS2_PAYLOAD_READY_HIGH                 =   ( 1U << 2U ),     /*!<  PayloadReady High                                               */
  FSK_OOK_REGIRQFLAGS2_PAYLOAD_READY_LOW                  =   ( 0U << 2U )      /*!<  PayloadReady Low                                                */
} fsk_ook_regirqflags2_payload_ready_t;


/**
  * CrcOk <1>
  *
  *   NOTE: Set in Rx when the CRC of the payload is Ok. Cleared when FIFO is empty.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_CRC_OK_MASK                        =   ( 1U << 1U ),     /*!<  CrcOk mask                                                      */
  FSK_OOK_REGIRQFLAGS2_CRC_OK_HIGH                        =   ( 1U << 1U ),     /*!<  CrcOk High                                                      */
  FSK_OOK_REGIRQFLAGS2_CRC_OK_LOW                         =   ( 0U << 1U )      /*!<  CrcOk Low                                                       */
} fsk_ook_regirqflags2_crc_ok_t;


/**
  * LowBat <0>
  *
  *   NOTE: Set when the battery voltage drops below the Low Battery threshold. Cleared only when set to 1 by the user.
  */
typedef enum
{
  FSK_OOK_REGIRQFLAGS2_LOW_BAT_MASK                       =   ( 1U << 0U ),     /*!<  LowBat mask                                                     */
  FSK_OOK_REGIRQFLAGS2_LOW_BAT_HIGH                       =   ( 1U << 0U ),     /*!<  LowBat High                                                     */
  FSK_OOK_REGIRQFLAGS2_LOW_BAT_LOW                        =   ( 0U << 0U )      /*!<  LowBat Low                                                      */
} fsk_ook_regirqflags2_low_bat_t;


/**
  * @brief   REG_DIO_MAPPING1
  */
/**
  * Dio0Mapping <7:6>
  *
  *   NOTE: DIO0 Mapping.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING1_DIO0_MAPPING_MASK                  =   ( 0b11 << 6U )  /*!<  Dio0Mapping mask                                                */
} fsk_ook_regdiomapping1_dio0_mapping_t;


/**
  * Dio1Mapping <5:4>
  *
  *   NOTE: DIO1 Mapping.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING1_DIO1_MAPPING_MASK                  =   ( 0b11 << 4U )  /*!<  Dio1Mapping mask                                                */
} fsk_ook_regdiomapping1_dio1_mapping_t;


/**
  * Dio2Mapping <3:2>
  *
  *   NOTE: DIO2 Mapping.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING1_DIO2_MAPPING_MASK                  =   ( 0b11 << 2U )  /*!<  Dio2Mapping mask                                                */
} fsk_ook_regdiomapping1_dio2_mapping_t;


/**
  * Dio3Mapping <1:0>
  *
  *   NOTE: DIO3 Mapping.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING1_DIO3_MAPPING_MASK                  =   ( 0b11 << 0U )  /*!<  Dio3Mapping mask                                                */
} fsk_ook_regdiomapping1_dio3_mapping_t;



/**
  * @brief   REG_DIO_MAPPING2
  */
/**
  * Dio4Mapping <7:6>
  *
  *   NOTE: DIO4 Mapping.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING2_DIO4_MAPPING_MASK                  =   ( 0b11 << 6U )  /*!<  Dio4Mapping mask                                                */
} fsk_ook_regdiomapping2_dio4_mapping_t;


/**
  * Dio5Mapping <5:4>
  *
  *   NOTE: DIO5 Mapping.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING2_DIO5_MAPPING_MASK                  =   ( 0b11 << 4U )  /*!<  Dio5Mapping mask                                                */
} fsk_ook_regdiomapping2_dio5_mapping_t;


/**
  * MapPreambleDetect <0>
  *
  *   NOTE: Allows the mapping of either Rssi Or PreambleDetect to the DIO pins.
  */
typedef enum
{
  FSK_OOK_REGDIOMAPPING2_MAP_PREAMBLE_DETECT_MASK             =   ( 1U << 0U ), /*!<  MapPreambleDetect mask                                          */
  FSK_OOK_REGDIOMAPPING2_MAP_PREAMBLE_DETECT_RSSI             =   ( 0U << 0U ), /*!<  Rssi interrupt                                      [ Default ] */
  FSK_OOK_REGDIOMAPPING2_MAP_PREAMBLE_DETECT_PREAMBLE_DETECT  =   ( 1U << 0U )  /*!<  PreambleDetect interrupt                                        */
} fsk_ook_regdiomapping2_map_preamble_detect_t;


/**
  * @brief   DIO MAPPING: CONTINUOUS MODE
  */
/**
  * DIO0 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO0_CONTINUOUS_MODE_0             =   0U,             /*!<  Rx: SyncAddress | Tx: TxReady                       [ Default ] */
  FSK_OOK_DIOMAPPING_DIO0_CONTINUOUS_MODE_1             =   1U,             /*!<  Rx: Rssi/PreambleDetect                                         */
  FSK_OOK_DIOMAPPING_DIO0_CONTINUOUS_MODE_2             =   2U,             /*!<  Rx: RxReady | Tx: TxReady                                       */
  FSK_OOK_DIOMAPPING_DIO0_CONTINUOUS_MODE_3             =   3U              /*!<  None                                                            */
} fsk_ook_diomapping_dio0_continuous_mode_t;


/**
  * DIO1 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO1_CONTINUOUS_MODE_0             =   0U,             /*!<  Rx: Dclk | Tx: Dclk                                 [ Default ] */
  FSK_OOK_DIOMAPPING_DIO1_CONTINUOUS_MODE_1             =   1U,             /*!<  Rx: Rssi/PreambleDetect                                         */
  FSK_OOK_DIOMAPPING_DIO1_CONTINUOUS_MODE_2             =   2U,             /*!<  None                                                            */
  FSK_OOK_DIOMAPPING_DIO1_CONTINUOUS_MODE_3             =   3U              /*!<  None                                                            */
} fsk_ook_diomapping_dio1_continuous_mode_t;


/**
  * DIO2 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO2_CONTINUOUS_MODE_0             =   0U,             /*!<  Rx: Data | Tx: Data                                 [ Default ] */
  FSK_OOK_DIOMAPPING_DIO2_CONTINUOUS_MODE_1             =   1U,             /*!<  Rx: Data | Tx: Data                                             */
  FSK_OOK_DIOMAPPING_DIO2_CONTINUOUS_MODE_2             =   2U,             /*!<  Rx: Data | Tx: Data                                             */
  FSK_OOK_DIOMAPPING_DIO2_CONTINUOUS_MODE_3             =   3U              /*!<  Rx: Data | Tx: Data                                             */
} fsk_ook_diomapping_dio2_continuous_mode_t;


/**
  * DIO3 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO3_CONTINUOUS_MODE_0             =   0U,             /*!<  Rx: Timeout                                                                                 [ Default ] */
  FSK_OOK_DIOMAPPING_DIO3_CONTINUOUS_MODE_1             =   1U,             /*!<  Rx: Rssi/PreambleDetect                                                                                 */
  FSK_OOK_DIOMAPPING_DIO3_CONTINUOUS_MODE_2             =   2U,             /*!<  None                                                                                                    */
  FSK_OOK_DIOMAPPING_DIO3_CONTINUOUS_MODE_3             =   3U              /*!<  Standby: TempChange/LowBat | FSRx/Tx: TempChange/LowBat | Rx: TempChange/LowBat | Tx: TempChange/LowBat */
} fsk_ook_diomapping_dio3_continuous_mode_t;


/**
  * DIO4 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO4_CONTINUOUS_MODE_0             =   0U,             /*!<  FSRx/Tx: TempChange/LowBat | Rx: TempChange/LowBat | Tx: TempChange/LowBat  [ Default ] */
  FSK_OOK_DIOMAPPING_DIO4_CONTINUOUS_MODE_1             =   1U,             /*!<  FSRx/Tx: PllLock | Rx: PllLock | Tx: PllLock                                            */
  FSK_OOK_DIOMAPPING_DIO4_CONTINUOUS_MODE_2             =   2U,             /*!<  Rx: TimeOut                                                                             */
  FSK_OOK_DIOMAPPING_DIO4_CONTINUOUS_MODE_3             =   3U              /*!<  Standby: ModeReady | FSRx/Tx: ModeReady | Rx: ModeReady | Tx: ModeReady                 */
} fsk_ook_diomapping_dio4_continuous_mode_t;


/**
  * DIO5 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO5_CONTINUOUS_MODE_0             =   0U,             /*!<  Sleep: ClkOut if RC | Standby: ClkOut | FSRx/Tx: ClkOut | Rx: ClkOut | Tx: ClkOut [ Default ] */
  FSK_OOK_DIOMAPPING_DIO5_CONTINUOUS_MODE_1             =   1U,             /*!<  FSRx/Tx: PllLock | Rx: PllLock | Tx: PllLock                                                  */
  FSK_OOK_DIOMAPPING_DIO5_CONTINUOUS_MODE_2             =   2U,             /*!<  Rx: Rssi/PreambleDetect                                                                       */
  FSK_OOK_DIOMAPPING_DIO5_CONTINUOUS_MODE_3             =   3U              /*!<  Standby: ModeReady | FSRx/Tx: ModeReady | Rx: ModeReady | Tx: ModeReady                       */
} fsk_ook_diomapping_dio5_continuous_mode_t;


/**
  * @brief   DIO MAPPING: PACKET MODE
  */
/**
  * DIO0 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO0_PACKET_MODE_0                 =   0U,             /*!<  Rx: PayloadReady | Tx: PacketSent                                                           [ Default ] */
  FSK_OOK_DIOMAPPING_DIO0_PACKET_MODE_1                 =   1U,             /*!<  Rx: CrcOk                                                                                               */
  FSK_OOK_DIOMAPPING_DIO0_PACKET_MODE_2                 =   2U,             /*!<  None                                                                                                    */
  FSK_OOK_DIOMAPPING_DIO0_PACKET_MODE_3                 =   3U              /*!<  Standby: TempChange/LowBat | FSRx/Tx: TempChange/LowBat | Rx: TempChange/LowBat | Tx: TempChange/LowBat */
} fsk_ook_diomapping_dio0_packet_mode_t;


/**
  * DIO1 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO1_PACKET_MODE_0                   =   0U,             /*!<  Sleep: FifoLevel | Standby: FifoLevel | FSRx/Tx: FifoLevel | Rx: FifoLevel | Tx: FifoLevel  [ Default ] */
  FSK_OOK_DIOMAPPING_DIO1_PACKET_MODE_1                   =   1U,             /*!<  Sleep: FifoEmpty | Standby: FifoEmpty | FSRx/Tx: FifoEmpty | Rx: FifoEmpty | Tx: FifoEmpty              */
  FSK_OOK_DIOMAPPING_DIO1_PACKET_MODE_2                   =   2U,             /*!<  Sleep: FifoFull  | Standby: FifoFull  | FSRx/Tx: FifoFull  | Rx: FifoFull  | Tx: FifoFull               */
  FSK_OOK_DIOMAPPING_DIO1_PACKET_MODE_3                   =   3U              /*!<  None                                                                                                    */
} fsk_ook_diomapping_dio1_packet_mode_t;


/**
  * DIO2 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO2_PACKET_MODE_0                   =   0U,             /*!<  Sleep: FifoFull  | Standby: FifoFull  | FSRx/Tx: FifoFull  | Rx: FifoFull  | Tx: FifoFull     [ Default ] */
  FSK_OOK_DIOMAPPING_DIO2_PACKET_MODE_1                   =   1U,             /*!<  Rx: RxReady                                                                                               */
  FSK_OOK_DIOMAPPING_DIO2_PACKET_MODE_2                   =   2U,             /*!<  Sleep: FifoFull  | Standby: FifoFull  | FSRx/Tx: FifoFull  | Rx: TimeOut   | Tx: FifoFull                 */
  FSK_OOK_DIOMAPPING_DIO2_PACKET_MODE_3                   =   3U              /*!<  Sleep: FifoFull  | Standby: FifoFull  | FSRx/Tx: FifoFull  | Rx: SyncAddress | Tx: FifoFull               */
} fsk_ook_diomapping_dio2_packet_mode_t;


/**
  * DIO3 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO3_PACKET_MODE_0                   =   0U,             /*!<  Sleep: FifoEmpty  | Standby: FifoEmpty  | FSRx/Tx: FifoEmpty  | Rx: FifoEmpty   | Tx: FifoEmpty   [ Default ] */
  FSK_OOK_DIOMAPPING_DIO3_PACKET_MODE_1                   =   1U,             /*!<  Tx: TxReady                                                                                                   */
  FSK_OOK_DIOMAPPING_DIO3_PACKET_MODE_2                   =   2U,             /*!<  Sleep: FifoEmpty  | Standby: FifoEmpty  | FSRx/Tx: FifoEmpty  | Rx: FifoEmpty   | Tx: FifoEmpty               */
  FSK_OOK_DIOMAPPING_DIO3_PACKET_MODE_3                   =   3U              /*!<  Sleep: FifoEmpty  | Standby: FifoEmpty  | FSRx/Tx: FifoEmpty  | Rx: FifoEmpty   | Tx: FifoEmpty               */
} fsk_ook_diomapping_dio3_packet_mode_t;


/**
  * DIO4 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO4_PACKET_MODE_0                   =   0U,             /*!<  Standby: TempChange/LowBat | FSRx/Tx: TempChange/LowBat | Rx: TempChange/LowBat | Tx: TempChange/LowBat [ Default ] */
  FSK_OOK_DIOMAPPING_DIO4_PACKET_MODE_1                   =   1U,             /*!<  FSRx/Tx: PllLock | Rx: PllLock | Tx: PllLock                                                                        */
  FSK_OOK_DIOMAPPING_DIO4_PACKET_MODE_2                   =   2U,             /*!<  Rx: TimeOut                                                                                                         */
  FSK_OOK_DIOMAPPING_DIO4_PACKET_MODE_3                   =   3U              /*!<  Rx: Rssi/PreambleDetect                                                                                             */
} fsk_ook_diomapping_dio4_packet_mode_t;


/**
  * DIO5 MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  FSK_OOK_DIOMAPPING_DIO5_PACKET_MODE_0                   =   0U,             /*!<  Sleep: ClkOut if RC | Standby: ClkOut | FSRx/Tx: ClkOut | Rx: ClkOut | Tx: ClkOut [ Default ] */
  FSK_OOK_DIOMAPPING_DIO5_PACKET_MODE_1                   =   1U,             /*!<  FSRx/Tx: PllLock | Rx: PllLock | Tx: PllLock                                                  */
  FSK_OOK_DIOMAPPING_DIO5_PACKET_MODE_2                   =   2U,             /*!<  Rx: Data | Tx: Data                                                                           */
  FSK_OOK_DIOMAPPING_DIO5_PACKET_MODE_3                   =   3U              /*!<  Standby: ModeReady | FSRx/Tx: ModeReady | Rx: ModeReady | Tx: ModeReady                       */
} fsk_ook_diomapping_dio5_packet_mode_t;



/* FSK/OOK: Version register   */
/**
  * @brief   REG_VERSION
  *
  *          NOTE: Version code of the chip. Bits 7-4 give the full revision number; bits 3-0 give the metal mask revision number
  */
typedef enum
{
  FSK_OOK_REGVERSION_VERSION_MASK                         =   0xFF,             /*!<  Version mask                                                    */
  FSK_OOK_REGVERSION_VERSION                              =   0x22              /*!<  Version value                                                   */
} fsk_ook_regversion_version_t;


/* FSK/OOK: Additional registers   */
/**
  * @brief   REG_AGC_REF
  */
/**
  * AgcReferenceLevel <5:0> (Default: 0x13)
  *
  *   NOTE: Sets the floor reference for all AGC thresholds: 
  *           AGC Reference [dBm] = -174 dBm + 10*log(2* RxBw ) + SNR + AgcReferenceLevel SNR = 8 dB, fixed value.
  */
typedef enum
{
  FSK_OOK_REGAGCREF_AGC_REFERENCE_LEVEL_MASK              =   ( 0b111111 << 0U ) /*!<  AgcReferenceLevel mask                                          */
} fsk_ook_regagcref_agc_reference_level_t;


/**
  * @brief   REG_AGC_THRESH1
  */
/**
  * AgcStep1 <4:0> (Default: 0x0E)
  *
  *   NOTE: Defines the 1st AGC Threshold.
  */
typedef enum
{
  FSK_OOK_REGAGCTHRESH1_AGC_STEP_1_MASK                   =   ( 0b11111 << 0U )   /*!<  AgcStep1 mask                                                 */
} fsk_ook_regagcthresh1_agc_step_1_t;


/**
  * @brief   REG_AGC_THRESH2
  */
/**
  * AgcStep2 <7:4> (Default: 0x05)
  *
  *   NOTE: Defines the 2nd AGC Threshold.
  */
typedef enum
{
  FSK_OOK_REGAGCTHRESH2_AGC_STEP_2_MASK                   =   ( 0b1111 << 4U )   /*!<  AgcStep2 mask                                                 */
} fsk_ook_regagcthresh2_agc_step_2_t;


/**
  * AgcStep3 <3:0> (Default: 0x0B)
  *
  *   NOTE: Defines the 3rd AGC Threshold.
  */
typedef enum
{
  FSK_OOK_REGAGCTHRESH2_AGC_STEP_3_MASK                   =   ( 0b1111 << 0U )   /*!<  AgcStep3 mask                                                 */
} fsk_ook_regagcthresh2_agc_step_3_t;


/**
  * @brief   REG_AGC_THRESH3
  */
/**
  * AgcStep4 <7:4> (Default: 0x0D)
  *
  *   NOTE: Defines the 4th AGC Threshold.
  */
typedef enum
{
  FSK_OOK_REGAGCTHRESH3_AGC_STEP_4_MASK                   =   ( 0b1111 << 4U )   /*!<  AgcStep4 mask                                                 */
} fsk_ook_regagcthresh3_agc_step_4_t;


/**
  * AgcStep5 <3:0> (Default: 0x0B)
  *
  *   NOTE: Defines the 5th AGC Threshold.
  */
typedef enum
{
  FSK_OOK_REGAGCTHRESH3_AGC_STEP_5_MASK                   =   ( 0b1111 << 0U )   /*!<  AgcStep5 mask                                                 */
} fsk_ook_regagcthresh3_agc_step_5_t;


/**
  * @brief   REG_PLL_HOP
  */
/**
  * FastHopOn <7> 
  *
  *   NOTE: Bypasses the main state machine for a quick frequency hop. Writing RegFrfLsb will trigger the frequency change.
  */
typedef enum
{
  FSK_OOK_REGPLLHOP_FAST_HOP_ON_MASK                      =   ( 1U << 7U ),     /*!<  FastHopOn mask                                                */
  FSK_OOK_REGPLLHOP_FAST_HOP_ON_0                         =   ( 0U << 7U ),     /*!<  Frf is validated when FSTx or FSRx is requested   [ Default ] */
  FSK_OOK_REGPLLHOP_FAST_HOP_ON_1                         =   ( 1U << 7U )      /*!<  Frf is validated triggered when RegFrfLsb is written          */
} fsk_ook_regpllhop_fast_hop_on_t;


/**
  * PaManualDutyCycle <3:0> (Default: 0x0E)
  *
  *   NOTE: See app note 1200.32.
  */
typedef enum
{
  FSK_OOK_REGPLLHOP_PA_MANUAL_DUTY_CYCLE_MASK               =   ( 0b1111 << 0U ) /*!<  PaManualDutyCycle mask                                        */
} fsk_ook_regpllhop_pa_manual_duty_cycle_t;


/**
  * @brief   REG_TCXO
  */
/**
  * TcxoInputOn <4> 
  *
  *   NOTE: Controls the crystal oscillator.
  */
typedef enum
{
  FSK_OOK_REGTCXO_TCXO_INPUT_ON_MASK                      =   ( 1U << 4U ),     /*!<  TcxoInputOn mask                                              */
  FSK_OOK_REGTCXO_TCXO_INPUT_ON_0                         =   ( 0U << 4U ),     /*!<  Crystal Oscillator with external Crystal          [ Default ] */
  FSK_OOK_REGTCXO_TCXO_INPUT_ON_1                         =   ( 1U << 4U )      /*!<  External clipped sine TCXO AC-connected to XTA pin            */
} fsk_ook_regtcxo_tcxo_input_on_t;


/**
  * @brief   REG_PA_DAC
  */
/**
  * PaDac <2:0> 
  *
  *   NOTE: Enables the +20 dBm option on PA_BOOST pin.
  */
typedef enum
{
  FSK_OOK_REGPADAC_PA_DAC_MASK                            =   ( 0b111 << 0U ),  /*!<  PaDac mask                                                    */
  FSK_OOK_REGPADAC_PA_DAC_DEFAULT_VALUE                   =   ( 0x04 << 0U ),   /*!<  Default value                                     [ Default ] */
  FSK_OOK_REGPADAC_PA_DAC_PLUS_20_DBM                     =   ( 0x07 << 0U )    /*!<  +20 dBm on PA_BOOST when OutputPower = 1111                   */
} fsk_ook_regpadac_pa_dac_t;


/**
  * @brief   REG_PLL
  */
/**
  * PllBandwidth <7:6> 
  *
  *   NOTE: Controls the PLL bandwidth.
  */
typedef enum
{
  FSK_OOK_REGPLL_PLL_BANDWIDTH_MASK                     =   ( 0b11 << 6U ),   /*!<  PllBandwidth mask                                             */
  FSK_OOK_REGPLL_PLL_BANDWIDTH_75_KHZ                   =   ( 0b00 << 6U ),   /*!<  PllBandwidth 75 kHz                                           */
  FSK_OOK_REGPLL_PLL_BANDWIDTH_150_KHZ                  =   ( 0b01 << 6U ),   /*!<  PllBandwidth 150 kHz                                          */
  FSK_OOK_REGPLL_PLL_BANDWIDTH_225_KHZ                  =   ( 0b10 << 6U ),   /*!<  PllBandwidth 225 kHz                                          */
  FSK_OOK_REGPLL_PLL_BANDWIDTH_300_KHZ                  =   ( 0b11 << 6U )    /*!<  PllBandwidth 300 kHz                              [ Default ] */
} fsk_ook_regpll_pll_bandwidth_t;


/**
  * @brief   REG_PLL_LOW_PN
  */
/**
  * PllBandwidth <7:6> 
  *
  *   NOTE: Controls the Low Phase Noise PLL bandwidth.
  */
typedef enum
{
  FSK_OOK_REGPLLLOWPN_PLL_BANDWIDTH_MASK                =   ( 0b11 << 6U ),   /*!<  PllBandwidth mask                                             */
  FSK_OOK_REGPLLLOWPN_PLL_BANDWIDTH_75_KHZ              =   ( 0b00 << 6U ),   /*!<  PllBandwidth 75 kHz                                           */
  FSK_OOK_REGPLLLOWPN_PLL_BANDWIDTH_150_KHZ             =   ( 0b01 << 6U ),   /*!<  PllBandwidth 150 kHz                                          */
  FSK_OOK_REGPLLLOWPN_PLL_BANDWIDTH_225_KHZ             =   ( 0b10 << 6U ),   /*!<  PllBandwidth 225 kHz                                          */
  FSK_OOK_REGPLLLOWPN_PLL_BANDWIDTH_300_KHZ             =   ( 0b11 << 6U )    /*!<  PllBandwidth 300 kHz                              [ Default ] */
} fsk_ook_regplllowpn_pll_bandwidth_t;


/**
  * @brief   REG_PA_MANUAL
  */
/**
  * ManualPaControl <4> 
  *
  *   NOTE: See AN1200.32.
  */
typedef enum
{
  FSK_OOK_REGPAMANUAL_MANUAL_PA_CONTROL_MASK            =   ( 1U << 4U ),     /*!<  PllBandwidth mask                                             */
  FSK_OOK_REGPAMANUAL_MANUAL_PA_CONTROL_DISABLED        =   ( 0U << 4U ),     /*!<  disables manual PA control                        [ Default ] */
  FSK_OOK_REGPAMANUAL_MANUAL_PA_CONTROL_ENABLED         =   ( 1U << 4U )      /*!<  enables manual PA control                                     */
} fsk_ook_regpamanual_manual_pa_control_t;


/**
  * @brief   REG_FORMER_TEMP
  *
  *           NOTE: Temperature saved during the latest IQ (RSSI and Image) calibrated. Same format as TempValue in RegTemp
  */
typedef enum
{
  FSK_OOK_REGFORMERTEMP_FORMER_TEMP_MASK                =   0xFF              /*!<  FormerTemp mask                                               */
} fsk_ook_regformertemp_former_temp_t;


/**
  * @brief   REG_BIT_RATE_FRAC
  *
  *           NOTE: Fractional part of the bit rate divider (Only valid for FSK)
  */
typedef enum
{
  FSK_OOK_REGBITRATEFRAC_BIT_RATE_FRAC_MASK             =   0xFF              /*!<  BitRateFrac mask                                              */
} fsk_ook_recbitratefrac_bit_rate_frac_t;




/**
  * @brief   REGISTER MAP, LORA MODE
  */
/**
  * @brief   REG_FIFO
  */
typedef enum
{
  LORA_REGFIFO_FIFO_MASK                        =   0xFF         /*!<  LoRa base-band FIFO data input/output. FIFO is cleared an not accessible when device is in SLEEP mode */
} lora_reg_fifo_t;


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
  * @brief   REG_FR_MSB
  */
typedef enum
{
  LORA_REG_FR_MSB_MASK                            =   0xFF              /*!<  MSB of RF carrier frequency ( Default: 0xE4 )                   */
} lora_reg_fr_msb_t;


/**
  * @brief   REG_FR_MIB
  */
typedef enum
{
  LORA_REG_FR_MIB_MASK                            =   0xFF              /*!<  MIB of RF carrier frequency ( Default: 0xC0 )                   */
} lora_reg_fr_mib_t;


/**
  * @brief   REG_FR_LSB
  */
typedef enum
{
  LORA_REG_FR_LSB_MASK                            =   0xFF              /*!<  LSB of RF carrier frequency ( Default: 0x00 )                   */
} lora_reg_fr_lsb_t;


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
  LORA_REGPACONFIG_OUTPUT_POWER_MASK              =   ( 0b1111 << 0U )    /*!<  OutputPower Mask                                                */
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


/**
  * @brief   REG_LNA
  */
/**
  * LnaGain <7:5>
  *
  *   NOTE: LNA gain setting.
  */
typedef enum
{
  LORA_REGLNA_LNA_GAIN_MASK                         =   ( 0b111 << 5U ),  /*!<  LnaGain Mask                                                  */
  LORA_REGLNA_LNA_GAIN_NOT_USED                     =   ( 0b000 << 5U ),  /*!<  LnaGain not used                                              */
  LORA_REGLNA_LNA_GAIN_G1                           =   ( 0b001 << 5U ),  /*!<  LnaGain G1 maximum gain                           [ Default ] */
  LORA_REGLNA_LNA_GAIN_G2                           =   ( 0b010 << 5U ),  /*!<  LnaGain G2                                                    */
  LORA_REGLNA_LNA_GAIN_G3                           =   ( 0b011 << 5U ),  /*!<  LnaGain G3                                                    */
  LORA_REGLNA_LNA_GAIN_G4                           =   ( 0b100 << 5U ),  /*!<  LnaGain G4                                                    */
  LORA_REGLNA_LNA_GAIN_G5                           =   ( 0b101 << 5U ),  /*!<  LnaGain G5                                                    */
  LORA_REGLNA_LNA_GAIN_G6                           =   ( 0b110 << 5U )   /*!<  LnaGain G6 minimum gain                                       */
} lora_reglna_lna_gain_t;


/**
  * LnaBoost <1:0>
  *
  *   NOTE: N/A.
  */
typedef enum
{
  LORA_REGLNA_LNA_BOOST_MASK                        =   ( 0b11 << 0U ),   /*!<  LnaBoost Mask                                                 */
  LORA_REGLNA_LNA_BOOST_DEFAULT_LNA_CURRENT         =   ( 0b00 << 0U ),   /*!<  LnaBoost Default LNA current                      [ Default ] */
  LORA_REGLNA_LNA_BOOST_ON                          =   ( 0b11 << 0U )    /*!<  LnaBoost  Boost on, 150% LNA current                          */
} lora_reglna_lna_boost_t;


/**
  * @brief   REG_FIFO_ADDR_PTR
  */
typedef enum
{
  LORA_REG_FIFO_ADDR_PTR_MASK                        =   0xFF              /*!<  SPI interface address pointer in FIFO data buffer ( Default: 0x00 )  */
} lora_reg_fifo_addr_ptr_t;


/**
  * @brief   REG_FIFO_TX_BASE_ADDR
  */
typedef enum
{
  LORA_REG_FIFO_TX_BASE_ADDR_MASK                    =   0xFF              /*!<  Write base address in FIFO data buffer for TX modulator ( Default: 0x80 )  */
} lora_reg_fifo_tx_base_addr_t;


/**
  * @brief   REG_FIFO_RX_BASE_ADDR
  */
typedef enum
{
  LORA_REG_FIFO_RX_BASE_ADDR_MASK                    =   0xFF              /*!<  Read base address in FIFO data buffer for RX demodulator ( Default: 0x00 )  */
} lora_reg_fifo_rx_base_addr_t;


/**
  * @brief   REG_FIFO_RX_CURRENT_ADDR
  */
typedef enum
{
  LORA_REG_FIFO_RX_CURRENT_ADDR_MASK                 =   0xFF              /*!<  Start address (in data buffer) of last packet received         */
} lora_reg_fifo_rx_current_addr_t;


/**
  * @brief   REG_IRQ_FLAGS_MASK
  */
typedef enum
{
  LORA_REG_IRQ_FLAGS_MASK_MASK                        =   0xFF,             /*!<  RegIrqFlagsMask Mask                                                                                            */
  LORA_REG_IRQ_FLAGS_MASK_RX_TIMEOUT_MASK             =   ( 1U << 7U ),     /*!<  Timeout interrupt mask: setting this bit masks the corresponding IRQ in RegIrqFlags                             */
  LORA_REG_IRQ_FLAGS_MASK_RX_DONE_MASK                =   ( 1U << 6U ),     /*!<  Packet reception complete interrupt mask: setting this bit masks the corresponding IRQ in RegIrqFlags           */
  LORA_REG_IRQ_FLAGS_MASK_PAYLOAD_CRC_ERROR_MASK      =   ( 1U << 5U ),     /*!<  Payload CRC error interrupt mask: setting this bit masks the corresponding IRQ in RegIrqFlags                   */
  LORA_REG_IRQ_FLAGS_MASK_VALID_HEADER_MASK           =   ( 1U << 4U ),     /*!<  Valid header received in Rx mask: setting this bit masks the corresponding IRQ in RegIrqFlags                   */
  LORA_REG_IRQ_FLAGS_MASK_TX_DONE_MASK                =   ( 1U << 3U ),     /*!<  FIFO Payload transmission complete interrupt mask: setting this bit masks the corresponding IRQ in RegIrqFlags  */
  LORA_REG_IRQ_FLAGS_MASK_CAD_DONE_MASK               =   ( 1U << 2U ),     /*!<  CAD complete interrupt mask: setting this bit masks the corresponding IRQ in RegIrqFlags                        */
  LORA_REG_IRQ_FLAGS_MASK_FHSS_CHANGE_CHANNEL_MASK    =   ( 1U << 1U ),     /*!<  FHSS change channel interrupt mask: setting this bit masks the corresponding IRQ in RegIrqFlags                 */
  LORA_REG_IRQ_FLAGS_MASK_CAD_DETECTED_MASK           =   ( 1U << 0U )      /*!<  Cad Detected Interrupt Mask: setting this bit masks the corresponding IRQ in RegIrqFlags                        */
} lora_reg_irq_flags_mask_t;


/**
  * @brief   REG_IRQ_FLAGS
  */
typedef enum
{
  LORA_REG_IRQ_FLAGS_MASK                             =   0xFF,             /*!<  RegIrqFlags Mask                                                            */
  LORA_REG_IRQ_FLAGS_RX_TIMEOUT                       =   ( 1U << 7U ),     /*!<  Timeout interrupt: writing a 1 clears the IRQ                               */
  LORA_REG_IRQ_FLAGS_RX_DONE                          =   ( 1U << 6U ),     /*!<  Packet reception complete interrupt: writing a 1 clears the IRQ             */
  LORA_REG_IRQ_FLAGS_PAYLOAD_CRC_ERROR                =   ( 1U << 5U ),     /*!<  Payload CRC error interrupt: writing a 1 clears the IRQ                     */
  LORA_REG_IRQ_FLAGS_VALID_HEADER                     =   ( 1U << 4U ),     /*!<  Valid header received in Rx: writing a 1 clears the IRQ                     */
  LORA_REG_IRQ_FLAGS_TX_DONE                          =   ( 1U << 3U ),     /*!<  FIFO Payload transmission complete interrupt: writing a 1 clears the IRQ    */
  LORA_REG_IRQ_FLAGS_CAD_DONE                         =   ( 1U << 2U ),     /*!<  CAD complete: write to clear: writing a 1 clears the IRQ                    */
  LORA_REG_IRQ_FLAGS_FHSS_CHANGE_CHANNEL              =   ( 1U << 1U ),     /*!<  FHSS change channel interrupt: writing a 1 clears the IRQ                   */
  LORA_REG_IRQ_FLAGS_CAD_DETECTED                     =   ( 1U << 0U )      /*!<  Valid Lora signal detected during CAD operation: writing a 1 clears the IRQ */
} lora_reg_irq_flags_t;


/**
  * @brief   REG_RX_NB_BYTES
  */
typedef enum
{
  LORA_REGRXNBBYTES_FIFO_RX_BYTES_NB_MASK             =   0xFF              /*!<  Number of payload bytes of latest packet received             */
} lora_regrxnbbytes_fifo_rx_bytes_nb_t;


/**
  * @brief   REG_RX_HEADER_CNT_VALUE_MSB
  */
typedef enum
{
  LORA_REGRXHEADERCNTVALUEMSB_VALID_HEADER_CNT_MSB_MASK =   0xFF            /*!<  Number of valid headers received since last transition into Rx mode, MSB(15:8). Header and packet counters are reseted in Sleep mode  */
} lora_regrxheadercntvaluemsb_valid_header_cnt_msb_t;


/**
  * @brief   REG_RX_HEADER_CNT_VALUE_LSB
  */
typedef enum
{
  LORA_REGRXHEADERCNTVALUELSB_VALID_HEADER_CNT_LSB_MASK =   0xFF            /*!<  Number of valid headers received since last transition into Rx mode, LSB(7:0). Header and packet counters are reseted in Sleep mode   */
} lora_regrxheadercntvaluelsb_valid_header_cnt_lsb_t;


/**
  * @brief   REG_RX_PACKET_CNT_VALUE_MSB
  */
typedef enum
{
  LORA_REGRXPACKETCNTVALUEMSB_VALID_PACKET_CNT_MSB_MASK =   0xFF            /*!<  Number of valid packets received since last transition into Rx mode, MSB(15:8). Header and packet counters are reseted in Sleep mode  */
} lora_regrxpacketcntvaluemsb_valid_packet_cnt_msb_t;


/**
  * @brief   REG_RX_PACKET_CNT_VALUE_LSB
  */
typedef enum
{
  LORA_REGRXPACKETCNTVALUEMSB_VALID_PACKET_CNT_LSB_MASK =   0xFF            /*!<  Number of valid packets received since last transition into Rx mode, LSB(7:0). Header and packet counters are reseted in Sleep mode */
} lora_regrxpacketcntvaluemsb_valid_packet_cnt_lsb_t;


/**
  * @brief   REG_MODEM_STAT
  */
/**
  * RxCodingRate <7:5>
  *
  *   NOTE: Coding rate of last header received.
  */
typedef enum
{
  LORA_REGMODEMSTAT_RX_CODING_RATE_MASK             =   ( 0b111 << 5U )     /*!<  RxCodingRate Mask                                             */
} lora_regmodemstat_rx_coding_rate_t;


/**
  * ModemStatus <4:0>
  *
  *   NOTE: Coding rate of last header received.
  */
typedef enum
{
  LORA_REGMODEMSTAT_MODEM_STATUS_MASK                 =   ( 0b1111 << 0U ), /*!<  ModemStatus Mask                                              */
  LORA_REGMODEMSTAT_MODEM_STATUS_MODEM_CLEAR          =   ( 1U << 4U ),     /*!<  Modem clear ( Default: '1' )                                  */
  LORA_REGMODEMSTAT_MODEM_STATUS_HEADER_INFO_VALID    =   ( 1U << 3U ),     /*!<  Header info valid ( Default: '0' )                            */
  LORA_REGMODEMSTAT_MODEM_STATUS_RX_ON_GOING          =   ( 1U << 2U ),     /*!<  RX on-going ( Default: '0' )                                  */
  LORA_REGMODEMSTAT_MODEM_STATUS_SIGNAL_SYNCHRONIZED  =   ( 1U << 1U ),     /*!<  Signal synchronized ( Default: '0' )                          */
  LORA_REGMODEMSTAT_MODEM_STATUS_SIGNAL_DETECTED      =   ( 1U << 0U )      /*!<  Signal detected ( Default: '0' )                              */
} lora_regmodemstat_modem_status_t;


/**
  * @brief   REG_PKT_SNR_VALUE
  */
typedef enum
{
  LORA_REGPKTSNRVALUE_PACKET_SNR_MASK                 =   0xFF                /*!<  Estimation of SNR on last packet received.In two’s compliment format mutiplied by 4 */
} lora_regpktsnrvaluet_packet_snr_t;


/**
  * @brief   REG_PKT_RSSI_VALUE
  *
  *   NOTE: 
  *     - RSSI[dBm] = - 139 + PacketRssi                   (when SNR >= 0)
  *     - RSSI[dBm] = - 139 + PacketRssi + PacketSnr*0.25  (when SNR < 0)
  */
typedef enum
{
  LORA_REGPKTRSSIVALUE_PACKET_RSSI_MASK             =   0xFF                /*!<  RSSI of the latest packet received (dBm)                      */
} lora_regpktrssivalue_pkt_rssi_t;


/**
  * @brief   REG_RSSI_VALUE
  *
  *   NOTE: 
  *     - RSSI[dBm] = -139 + Rssi
  */
typedef enum
{
  LORA_REGRSSIVALUE_RSSI_MASK                       =   0xFF                /*!<  Current RSSI value (dBm)                                      */
} lora_regrssivalue_rssi_t;


/**
  * @brief   REG_HOP_CHANNEL
  */
/**
  * PllTimeout <7>
  *
  *   NOTE: PLL failed to lock while attempting a TX/RX/CAD operation.
  */
typedef enum
{
  LORA_REGHOPCHANNEL_PLL_TIMEOUT_MASK               =   ( 1U << 7U ),      /*!<  PllTimeout Mask                                                */
  LORA_REGHOPCHANNEL_PLL_TIMEOUT_PLL_DID_NOT_LOCK   =   ( 1U << 7U ),      /*!<  PLL did not lock                                               */
  LORA_REGHOPCHANNEL_PLL_TIMEOUT_PLL_DID_LOCK       =   ( 0U << 7U )       /*!<  PLL did lock                                                   */
} lora_reghopchannel_pll_timeout_t;


/**
  * CrcOnPayload <6>
  *
  *   NOTE: CRC Information extracted from the received packet header (Explicit header mode only).
  */
typedef enum
{
  LORA_REGHOPCHANNEL_CRC_ON_PAYLOAD_MASK            =   ( 1U << 6U ),      /*!<  CrcOnPayload Mask                                              */
  LORA_REGHOPCHANNEL_CRC_ON_PAYLOAD_CRC_OFF         =   ( 0U << 6U ),      /*!<  Header indicates CRC off                                       */
  LORA_REGHOPCHANNEL_CRC_ON_PAYLOAD_CRC_ON          =   ( 1U << 6U )       /*!<  Header indicates CRC on                                        */
} lora_reghopchannel_crc_on_payload_t;


/**
  * FhssPresentChannel <5:0>
  *
  *   NOTE: Current value of frequency hopping channel in use.
  */
typedef enum
{
  LORA_REGHOPCHANNEL_FHSS_PRESENT_CHANNEL_MASK        =   ( 0b111111 << 0U ) /*!<  FhssPresentChannel Mask                                      */
} lora_reghopchannel_fhss_present_channel_t;


/**
  * @brief   REG_MODEM_CONFIG_1
  */
/**
  * Bw <7:6>
  *
  *   NOTE: Signal bandwidth.
  */
typedef enum
{
  LORA_REGMODEMCONFIG1_BW_MASK                      =   ( 0b11 << 6U ),    /*!<  Bw Mask                                                        */
  LORA_REGMODEMCONFIG1_BW_125_KHZ                   =   ( 0b00 << 6U ),    /*!<  Bw 125 kHz                                         [ Default ] */
  LORA_REGMODEMCONFIG1_BW_250_KHZ                   =   ( 0b01 << 6U ),    /*!<  Bw 250 kHz                                                     */
  LORA_REGMODEMCONFIG1_BW_500_KHZ                   =   ( 0b10 << 6U )     /*!<  Bw 500 kHz                                                     */
} lora_regmodemconfig1_bw_t;


/**
  * CodingRate <5:3>
  *
  *   NOTE: Error coding rate.
  */
typedef enum
{
  LORA_REGMODEMCONFIG1_CODING_RATE_MASK             =   ( 0b111 << 3U ),   /*!<  CodingRate Mask                                                */
  LORA_REGMODEMCONFIG1_CODING_RATE_4_5              =   ( 0b001 << 3U ),   /*!<  CodingRate 4/5                                     [ Default ] */
  LORA_REGMODEMCONFIG1_CODING_RATE_4_6              =   ( 0b010 << 3U ),   /*!<  CodingRate 4/6                                                 */
  LORA_REGMODEMCONFIG1_CODING_RATE_4_7              =   ( 0b011 << 3U ),   /*!<  CodingRate 4/7                                                 */
  LORA_REGMODEMCONFIG1_CODING_RATE_4_8              =   ( 0b100 << 3U )    /*!<  CodingRate 4/8                                                 */
} lora_regmodemconfig1_coding_rate_t;


/**
  * ImplicitHeaderModeOn <2>
  *
  *   NOTE: N/A.
  */
typedef enum
{
  LORA_REGMODEMCONFIG1_IMPLICIT_HEADER_MODE_ON_MASK                 =   ( 1U << 2U ), /*!<  ImplicitHeaderModeOn Mask                            */
  LORA_REGMODEMCONFIG1_IMPLICIT_HEADER_MODE_ON_EXPLICIT_HEADER_MODE =   ( 0U << 2U ), /*!<  Explicit Header mode                     [ Default ] */
  LORA_REGMODEMCONFIG1_IMPLICIT_HEADER_MODE_ON_IMPLICIT_HEADER_MODE =   ( 1U << 2U )  /*!<  Implicit Header mode                                 */
} lora_regmodemconfig1_implicit_header_mode_on_t;


/**
  * RxPayloadCrcOn <1>
  *
  *   NOTE: If CRC is needed, RxPayloadCrcOn should be set:
  *           - in Implicit header mode: on Tx and Rx side
  *           - in Explicit header mode: on the Tx side alone (recovered from the header in Rx side)
  */
typedef enum
{
  LORA_REGMODEMCONFIG1_RX_PAYLOAD_CRC_ON_MASK        =   ( 1U << 1U ),    /*!<  RxPayloadCrcOn Mask                                             */
  LORA_REGMODEMCONFIG1_RX_PAYLOAD_CRC_ON_CRC_DISABLE =   ( 0U << 1U ),    /*!<  CRC disable                                         [ Default ] */
  LORA_REGMODEMCONFIG1_RX_PAYLOAD_CRC_ON_CRC_ENABLE  =   ( 1U << 1U )     /*!<  CRC enable                                                      */
} lora_regmodemconfig1_rx_payload_crc_on_t;


/**
  * LowDataRateOptimize <0>
  *
  *   NOTE: If CRC is needed, RxPayloadCrcOn should be set:
  *           - in Implicit header mode: on Tx and Rx side
  *           - in Explicit header mode: on the Tx side alone (recovered from the header in Rx side)
  */
typedef enum
{
  LORA_REGMODEMCONFIG1_LOW_DATA_RATE_OPTIMIZE_MASK    =   ( 1U << 0U ),    /*!<  LowDataRateOptimize Mask                                                 */
  LORA_REGMODEMCONFIG1_LOW_DATA_RATE_OPTIMIZE_DISABLE =   ( 0U << 0U ),    /*!<  LowDataRateOptimize disable                                  [ Default ] */
  LORA_REGMODEMCONFIG1_LOW_DATA_RATE_OPTIMIZE_ENABLE  =   ( 1U << 0U )     /*!<  LowDataRateOptimize enable; mandated for SF11 and SF12 with BW = 125 kHz */
} lora_regmodemconfig1_low_data_rate_optimize_t;


/**
  * @brief   REG_MODEM_CONFIG_2
  */
/**
  * SpreadingFactor <7:4>
  *
  *   NOTE: SF rate (expressed as a base-2 logarithm).
  */
typedef enum
{
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_MASK        =   ( 0b1111 << 4U ), /*!<  SpreadingFactor Mask                                            */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_6           =   ( 0b0110 << 4U ), /*!<  SpreadingFactor  6:   64 chips/symbol                           */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_7           =   ( 0b0111 << 4U ), /*!<  SpreadingFactor  7:  128 chips/symbol               [ Default ] */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_8           =   ( 0b1000 << 4U ), /*!<  SpreadingFactor  8:  256 chips/symbol                           */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_9           =   ( 0b1001 << 4U ), /*!<  SpreadingFactor  9:  542 chips/symbol                           */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_10          =   ( 0b1010 << 4U ), /*!<  SpreadingFactor 10: 1024 chips/symbol                           */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_11          =   ( 0b1011 << 4U ), /*!<  SpreadingFactor 11: 2048 chips/symbol                           */
  LORA_REGMODEMCONFIG2_SPREADING_FACTOR_12          =   ( 0b1100 << 4U )  /*!<  SpreadingFactor 12: 4096 chips/symbol                           */
} lora_regmodemconfig2_spreading_factor_t;


/**
  * TxContinuousMode <3>
  *
  *   NOTE: N/A.
  */
typedef enum
{
  LORA_REGMODEMCONFIG2_TX_CONTINUOUS_MODE_MASK            =   ( 1U << 3U ), /*!<  TxContinuousMode Mask                                                               */
  LORA_REGMODEMCONFIG2_TX_CONTINUOUS_MODE_NORMAL_MODE     =   ( 0U << 3U ), /*!<  Normal mode, a single packet is sent                                    [ Default ] */
  LORA_REGMODEMCONFIG2_TX_CONTINUOUS_MODE_CONTINUOUS_MODE =   ( 1U << 3U )  /*!<  Continuous mode, send multiple packets across the FIFO (used for spectral analysis) */
} lora_regmodemconfig2_tx_continuous_mode_t;


/**
  * AgcAutoOn <2>
  *
  *   NOTE: N/A.
  */
typedef enum
{
  LORA_REGMODEMCONFIG2_AGC_AUTO_ON_MASK                     =   ( 1U << 2U ), /*!<  AgcAutoOn Mask                                                  */
  LORA_REGMODEMCONFIG2_AGC_AUTO_ON_SET_BY_REGISTER_LNA_GAIN =   ( 0U << 2U ), /*!<  LNA gain set by register LnaGain                                */
  LORA_REGMODEMCONFIG2_AGC_AUTO_ON_SET_BY_INTERNAL_AGC_LOOP =   ( 1U << 2U )  /*!<  LNA gain set by the internal AGC loop               [ Default ] */
} lora_regmodemconfig2_agc_auto_on_t;


/**
  * SymbTimeout(9:8) <1:0>
  *
  *   NOTE: RX Time-Out MSB (Default: 0x00)
  */
typedef enum
{
  LORA_REGMODEMCONFIG2_SYM_TIMEOUT_MASK                     =   ( 0b11 << 0U )  /*!<  SymbTimeout Mask                                              */
} lora_regmodemconfig2_symb_timeout_t;


/**
  * @brief   REG_SYMB_TIMEOUT_LSB (Default: 0x64)
  *
  *   NOTE: RX Time-Out LSB. RX operation time-out value expressed as number of symbols:
  *           - TimeOut = SymbTimeout * Ts
  */
typedef enum
{
  LORA_REGSYMBTIMEOUTLSB_SYMB_TIMEOUT_MASK                  =   0xFF            /*!<  SymbTimeout LSB Mask                                          */
} lora_regsymbtimeoutlsb_symb_timeout_t;


/**
  * @brief   REG_PREAMBLE_MSB (Default: 0x00)
  *
  *   NOTE: Preamble length MSB, = PreambleLength + 4.25 Symbols
  */
typedef enum
{
  LORA_REGPREAMBLEMSB_PREAMBLE_LENGTH_MASK                  =   0xFF            /*!<  RegPreambleMsb Mask                                           */
} lora_regpreamblemsb_preamble_length_t;


/**
  * @brief   REG_PREAMBLE_LSB (Default: 0x08)
  *
  *   NOTE: Preamble Length LSB
  */
typedef enum
{
  LORA_REGPREAMBLELSB_PREAMBLE_LENGTH_MASK                  =   0xFF            /*!<  RegPreambleLsb Mask                                           */
} lora_regpreamblelsb_preamble_length_t;


/**
  * @brief   REG_PAYLOAD_LENGTH (Default: 0x01)
  *
  *   NOTE: Payload length in bytes. The register needs to be set in implicit header mode for the expected packet length. A '0' value is not permitted
  */
typedef enum
{
  LORA_REGPAYLOADLENGTH_PAYLOAD_LENGTH_MASK                 =   0xFF            /*!<  PayloadLength Mask                                            */
} lora_regpayloadlength_payload_length_t;


/**
  * @brief   REG_MAX_PAYLOAD_LENGTH (Default: 0xFF)
  *
  *   NOTE: Maximum payload length; if header payload length exceeds value a header CRC error is generated. Allows filtering of packet with a bad size
  */
typedef enum
{
  LORA_REGMAXPAYLOADLENGTH_PAYLOAD_MAX_LENGTH_MASK          =   0xFF            /*!<  PayloadMaxLength Mask                                         */
} lora_regmaxpayloadlength_payload_max_length_t;


/**
  * @brief   REG_HOP_PERIOD (Default: 0x00)
  *
  *   NOTE: Symbol periods between frequency hops. (0 = disabled). 1st hop always happen after the 1st header symbol
  */
typedef enum
{
  LORA_REGHOPPERIOD_FREQ_HOPPING_PERIOD_MASK                =   0xFF            /*!<  FreqHoppingPeriod Mask                                        */
} lora_reghopperiod_freq_hopping_period_t;


/**
  * @brief   REG_FIFO_RX_BYTE_ADDR 
  *
  *   NOTE: Current value of RX databuffer pointer (address of last byte written by Lora receiver)
  */
typedef enum
{
  LORA_REGFIFORXBYTEADDR_FIFO_RX_BYTE_ADDR_PTR_MASK         =   0xFF            /*!<  FifoRxByteAddrPtr Mask                                        */
} lora_regfiforxbyteaddr_fifo_rx_byte_addr_ptr_t;


/**
  * @brief   REG_FEI_MSB (Default: 0x00)
  *
  *   NOTE: Estimated frequency error from modem in 2's compliment format. MSB of RF Frequency error
  */
typedef enum
{
  LORA_REGFEIMSB_FREQ_ERROR_MASK                            =   0xFF            /*!<  FreqError Mask                                                */
} lora_regfeimsb_freq_error_t;


/**
  * @brief   REG_FEI_MIB (Default: 0x00)
  *
  *   NOTE: Middle byte of RF Frequency Error
  */
typedef enum
{
  LORA_REGFEIMIB_FREQ_ERROR_MASK                            =   0xFF            /*!<  FreqError Mask                                                */
} lora_regfeimib_freq_error_t;


/**
  * @brief   REG_FEI_LSB (Default: 0x00)
  *
  *   NOTE: LSB of RF Frequency Error
  */
typedef enum
{
  LORA_REGFEILSB_FREQ_ERROR_MASK                            =   0xFF            /*!<  FreqError Mask                                                */
} lora_regfeilsb_freq_error_t;


/**
  * @brief   REG_RSSI_WIDEBAND 
  *
  *   NOTE: Wideband RSSI measurement used to locally generate a random number
  */
typedef enum
{
  LORA_REGRSSIWIDEBAND_RSSI_WIDEBAND_MASK                   =   0xFF            /*!<  RegRssiWideband Mask                                          */
} lora_regrssiwideband_rssi_wideband_t;


/**
  * @brief   REG_DETECT_OPTIMIZE
  */
/**
  * AutomaticIFOn <7>
  *
  *   NOTE: Should be set to 0x0 after each reset (POR on manual) See errata note for more information.
  */
typedef enum
{
  LORA_REGDETECTOPTIMIZE_AUTOMATIC_IF_ON_MASK       =   ( 1U << 7U ),     /*!<  AutomaticIFOn Mask                                              */
  LORA_REGDETECTOPTIMIZE_AUTOMATIC_IF_ON_HIGH       =   ( 1U << 7U ),     /*!<  AutomaticIFOn value: '1'                            [ Default ] */
  LORA_REGDETECTOPTIMIZE_AUTOMATIC_IF_ON_LOW        =   ( 0U << 7U )      /*!<  AutomaticIFOn value: '0'                                        */
} lora_regdetectoptimize_automatic_if_on_t;


/**
  * DetectionOptimize <2:0>
  *
  *   NOTE: LoRa detection Optimize.
  */
typedef enum
{
  LORA_REGDETECTOPTIMIZE_DETECTION_OPTIMIZE_MASK        =   ( 0b111 << 0U ),  /*!<  DetectionOptimize Mask                                          */
  LORA_REGDETECTOPTIMIZE_DETECTION_OPTIMIZE_SF7_TO_SF12 =   ( 0b011 << 0U ),  /*!<  DetectionOptimize SF7 to SF12                       [ Default ] */
  LORA_REGDETECTOPTIMIZE_DETECTION_OPTIMIZE_SF6         =   ( 0b101 << 0U )   /*!<  DetectionOptimize SF6                                           */
} lora_regdetectoptimize_detection_optimize_t;


/**
  * @brief   REG_INVERT_IQ
  */
/**
  * InvertIQRX <6>
  *
  *   NOTE: Invert the LoRa I and Q signals in RX path.
  */
typedef enum
{
  LORA_REGINVERTIQ_INVERT_IQ_RX_MASK                =   ( 1U << 6U ),     /*!<  InvertIQRX Mask                                                 */
  LORA_REGINVERTIQ_INVERT_IQ_RX_NORMAL_MODE         =   ( 0U << 6U ),     /*!<  Normal mode                                         [ Default ] */
  LORA_REGINVERTIQ_INVERT_IQ_RX_INVERTED_MODE       =   ( 1U << 6U )      /*!<  I and Q signals are inverted                                    */
} lora_reginvertiq_invert_iq_rx_t;


/**
  * InvertIQTX <0>
  *
  *   NOTE: Invert the LoRa I and Q signals in TX path.
  */
typedef enum
{
  LORA_REGINVERTIQ_INVERT_IQ_TX_MASK                =   ( 1U << 0U ),     /*!<  InvertIQTX Mask                                                 */
  LORA_REGINVERTIQ_INVERT_IQ_TX_NORMAL_MODE         =   ( 0U << 0U ),     /*!<  Normal mode                                         [ Default ] */
  LORA_REGINVERTIQ_INVERT_IQ_TX_INVERTED_MODE       =   ( 1U << 0U )      /*!<  I and Q signals are inverted                                    */
} lora_reginvertiq_invert_iq_tx_t;


/**
  * @brief   REG_SYNC_WORD (Default: 0x12)
  *
  *   NOTE: LoRa Sync Word Value 0x34 is reserved for LoRaWAN networks
  */
typedef enum
{
  LORA_REGSYNCWORD_SYNC_WORD_MASK                     =   0xFF,           /*!<  SyncWord Mask                                                   */
  LORA_REGSYNCWORD_SYNC_WORD_LORAWAN_NETWORKS         =   0x34            /*!<  SyncWord LoRaWAN networks                                       */
} lora_regsyncword_sync_word_t;


/**
  * @brief   REG_INVERT_IQ_2 (Default: 0x1D)
  *
  *   NOTE: Set to 0x19 when RX inverted IQ is set. See AN1200.24
  */
typedef enum
{
  LORA_REGINVERTIQ2_INVERT_IQ_2_MASK                  =   0xFF,           /*!<  InvertIQ2 Mask                                                  */
  LORA_REGINVERTIQ2_INVERT_IQ_2_RX_INVERTED_IQ_SET    =   0x19            /*!<  InvertIQ2 RX inverted IQ is set                                 */
} lora_reginvertiq2_invert_iq_2_t;


/**
  * @brief   REG_CHIRP_FILTER (Default: 0xA0)
  *
  *   NOTE: Set to 0x31 for ETSI-G1 compliance with 14 dBm RF output power when using bandwidth 500 kHz
  */
typedef enum
{
  LORA_REGCHIRPFILTER_MASK                            =   0xFF,           /*!<  RegChirpFilter Mask                                             */
  LORA_REGCHIRPFILTER_ETSI_G1_COMPLIANCE              =   0x31            /*!<  RegChirpFilter ETSI-G1 compliance                               */
} lora_regchirpfilter_t;


/**
  * @brief   DIO MAPPING: LORA MODE
  */
/**
  * ALL DIOs MAPPING
  *
  *   NOTE: N/A.
  */
typedef enum
{
  LORA_DIOMAPPING_ALL_LORA_MODE_0                     =   0U,             /*!<  DIO5: ModeReady | DIO4: CadDetected | DIO3: CadDone         | DIO2: FhssChangeChannel | DIO1: RxTimeout         | DIO0: RxDone  [ Default ] */
  LORA_DIOMAPPING_ALL_LORA_MODE_1                     =   1U,             /*!<  DIO5: ClkOut    | DIO4: PllLock     | DIO3: ValidHeader     | DIO2: FhssChangeChannel | DIO1: FhssChangeChannel | DIO0: TxDone              */
  LORA_DIOMAPPING_ALL_LORA_MODE_2                     =   2U,             /*!<  DIO5: ClkOut    | DIO4: PllLock     | DIO3: PayloadCrcError | DIO2: FhssChangeChannel | DIO1: CadDetected       | DIO0: CadDone             */
  LORA_DIOMAPPING_ALL_LORA_MODE_3                     =   3U              /*!<  None                                                                                                                                        */
} lora_diomapping_all_lora_mode_t;


/**
  * @brief   POWER AMPLIFIER MODE SELECTION
  */
typedef enum
{
  LORA_PA_PA0_OUTPUT_ON_RFIO                          =   0U,             /*!<  PA0 output on pin RFO ( -1 to +14 dBm )                                       */
  LORA_PA_PA1_PA2_COMBINED_ON_PA_BOOST                =   1U,             /*!<  PA1 and PA2 combined on pin PA_BOOST ( +2 to +17 dBm )                        */
  LORA_PA_PA1_PA2_ON_PA_BOOST_HIGH_OUTPUT_20_DBM      =   2U              /*!<  PA1+PA2 on PA_BOOST with high output power +20 dBm settings ( +5 to +20 dBm ) */
} lora_pa_mode_t;


/**
  * @brief   REG_PA_DAC
  */
typedef enum
{
  LORA_REGPADAC_PA_DAC_MASK                            =   0xFF,            /*!<  PaDac mask                                                    */
  LORA_REGPADAC_PA_DAC_DEFAULT_VALUE                   =   0x84,            /*!<  Default value PA0 or +17dBm                       [ Default ] */
  LORA_REGPADAC_PA_DAC_PLUS_20_DBM                     =   0x87             /*!<  Value for High Power +20dBm                                   */
} lora_regpadac_pa_dac_t;






/**
  * @brief   CONSTANTS
  */
#define F_XOSC    32000000                        /*!<  F_XOSC in MHz               */
#define F_2POW19  524288                          /*!<  2^19                        */


/**
  * @brief   USER VARIABLES
  */
#ifndef SX1272_SX1273_VECTOR_STRUCT_H
#define SX1272_SX1273_VECTOR_STRUCT_H
typedef struct
{
  float                       t_a;              /*!<  Ambient temperature value     */
  uint16_t                    t_a_raw;          /*!<  Raw ambient temperature value */

  float                       t_upper;          /*!<  T_UPPER limit                 */
  float                       t_lower;          /*!<  T_LOWER limit                 */
  float                       t_crit;           /*!<  T_CRIT limit                  */
    
  /* Long range mode   */
  lora_regopmode_long_range_mode_t  mode;       /*!<  FSK/OOK or LoRa               */
  
  /* LoRa parameters   */
  lora_regmodemconfig2_spreading_factor_t         sf;                       /*!<  LoRa: Spreading factor                    */
  lora_regmodemconfig1_coding_rate_t              cr;                       /*!<  LoRa: Coding rate                         */
  lora_regmodemconfig1_bw_t                       bw;                       /*!<  LoRa: Bandwidth                           */
  uint16_t                                        preamble;                 /*!<  LoRa: Preamble:  6 - 65535                */
  lora_regmodemconfig1_implicit_header_mode_on_t  headerMode;               /*!<  LoRa: Header mode                         */
  lora_regmodemconfig1_low_data_rate_optimize_t   lowDataRateOptimization;  /*!<  LoRa: Low Data Rate Optimization          */
  uint8_t                                         hopPeriod;                /*!<  LoRa: Frequency Hopping period            */
  lora_regopmode_mode_t                           loraOperatingMode;        /*!<  LoRa: Operating mode functionality        */
  float                                           frequency;                /*!<  LoRa: Frequency in Hz                     */
  
  /* RF settings   */
  lora_pa_mode_t                                  paSelect;                 /*!<  LoRa: Power Amplifier output pin          */
  int8_t                                          p_out;                    /*!<  LoRa: PA max output power in dBmn          */
  lora_regpadac_pa_dac_t                          paDac;                    /*!<  LoRa: Higher power settings of the PA     */


  uint8_t                     deviceID;         /*!<  Device ID                     */
  uint8_t                     deviceRevision;   /*!<  Device Revision               */
} SX1272_SX1273_lora_data_t;
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
SX1272_SX1273_status_t SX1272_SX1273_Init               ( SPI_parameters_t mySPIparameters                                                        );

/** It sets the long range mode: FSK/OOK mode or LoRa mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_SetMode            ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myMode                      );

/** It gets the long range mode: FSK/OOK mode or LoRa mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_GetMode            ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myMode                     );

/** It sets the spreading factor value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetSF         ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t mySF                        );

/** It gets the spreading factor value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetSF         ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* mySF                       );

/** It sets the coding rate value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetCR         ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myCR                        );

/** It gets the coding rate value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetCR         ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myCR                       );

/** It sets the bandwidth value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetBW         ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myBW                        );

/** It gets the bandwidth value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetBW         ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myBW                       );

/** It sets the preamble value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetPreamble   ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myPreamble                  );

/** It gets the preamble value.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetPreamble   ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myPreamble                 );

/** It sets the header mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetHeaderMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myHeaderMode                );

/** It gets the header mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetHeaderMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myHeaderMode               );

/** It sets the Low Data Rate Optimization mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetLowDataRateOptimization ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myLowDataRateOptimization  );

/** It gets Low Data Rate Optimization mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetLowDataRateOptimization ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myLowDataRateOptimization );

/** It sets the Frequency Hopping Period mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetHopPeriod  ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myHopPeriod                 );

/** It gets Frequency Hopping Period mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetHopPeriod  ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myHopPeriod                );

/** It sets the LoRa operating mode functionality.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetOperatingMode    ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myLoRaOperatingMode         );

/** It gets LoRa operating mode functionality.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetOperatingMode    ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myLoRaOperatingMode        );

/** It allows access to FSK registers page located in address space ( 0x0D:0x3F ) while in LoRa mode.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetAccessSharedReg  ( SPI_parameters_t mySPIparameters, lora_regopmode_access_shared_reg_t myAccessSharedReg  );

/** It sets the frequency.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetFrequency   ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myFrequency                );

/** It gets the frequency.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetFrequency   ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myFrequency               );

/** It sets the RF power amplifier block.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetPowerAmplifier ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myPaConfig             );

/** It gets the RF power amplifier block.
  */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetPowerAmplifier ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myPaConfig             );