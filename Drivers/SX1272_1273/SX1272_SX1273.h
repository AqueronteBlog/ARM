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
  SX1272_SX1273_REG_FIFO          =   0x00,           /*!<  FIFO read/write access                                */
  SX1272_SX1273_REG_OP_MODE       =   0x01,           /*!<  Operating mode & LoRa/FSK selection                   */
  SX1272_SX1273_REG_FRF_MSB       =   0x06,           /*!<  RF Carrier Frequency, Most Significant Bits           */
  SX1272_SX1273_REG_FRF_MID       =   0x07,           /*!<  RF Carrier Frequency, Intermediate Bits               */
  SX1272_SX1273_REG_FRF_LSB       =   0x08,           /*!<  RF Carrier Frequency, Least Significant Bits          */
  SX1272_SX1273_REG_PA_CONFIG     =   0x09,           /*!<  PA selection and Output Power control                 */
  SX1272_SX1273_REG_PA_RAMP       =   0x0A,           /*!<  Control of PA ramp time, low phase noise PLL          */
  SX1272_SX1273_REG_OCP           =   0x0B,           /*!<  Over Current Protection control                       */
  SX1272_SX1273_REG_LNA           =   0x0C,           /*!<  LNA settings                                          */
  SX1272_SX1273_REG_DIO_MAPPING1  =   0x40,           /*!<  Mapping of pins DIO0 to DIO3                          */
  SX1272_SX1273_REG_DIO_MAPPING2  =   0x41,           /*!<  Mapping of pins DIO4 and DIO5, ClkOut frequency       */
  SX1272_SX1273_REG_VERSION       =   0x42,           /*!<  Semtech ID relating the silicon revision              */
  SX1272_SX1273_REG_AGC_REF       =   0x43,           /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_AGC_THRESH1   =   0x44,           /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_AGC_THRESH2   =   0x45,           /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_AGC_THRESH3   =   0x46,           /*!<  Adjustment of the AGC thresholds                      */
  SX1272_SX1273_REG_PLL_HOP       =   0x4B,           /*!<  Control the fast frequency hopping mode               */
  SX1272_SX1273_REG_TCXO          =   0x58,           /*!<  TCXO or XTAL input setting                            */
  SX1272_SX1273_REG_PA_DAC        =   0x5A,           /*!<  Higher power settings of the PA                       */
  SX1272_SX1273_REG_PLL           =   0x5C,           /*!<  Control of the PLL bandwidth                          */
  SX1272_SX1273_REG_PLL_LOW_PN    =   0x5E,           /*!<  Control of the Low Phase Noise PLL bandwidth          */
  SX1272_SX1273_REG_PA_MANUAL     =   0x63,           /*!<  Enables manual PA control                             */
  SX1272_SX1273_REG_FORMER_TEMP   =   0x6C,           /*!<  Stored temperature during the former IQ Calibration   */
  SX1272_SX1273_REG_BIT_RATE_FRAC =   0x70            /*!<  Fractional part in the Bit Rate division ratio        */
} SX1272_SX1273_fsk_ook_lora_common_registers_t;


/** LoRa registers.
  */
typedef enum
{
  SX1272_SX1273_REG_FIFO_ADDR_PTR           =   0x0D,  /*!<  FIFO SPI pointer                                      */
  SX1272_SX1273_REG_FIFO_TX_BASE_ADDR       =   0x0E,  /*!<  Start Tx data                                         */
  SX1272_SX1273_REG_FIFO_RX_BASE_ADDR       =   0x0F,  /*!<  Start Rx data                                         */
  SX1272_SX1273_FIFO_RX_CURRENT_ADDR        =   0x10,  /*!<  Start address of last packet received                 */
  SX1272_SX1273_REG_IRQ_FLAGS_MASK          =   0x11,  /*!<  Optional IRQ flag mask                                */
  SX1272_SX1273_REG_IRQ_FLAGS               =   0x12,  /*!<  IRQ flags                                             */
  SX1272_SX1273_REG_RX_NB_BYTES             =   0x13,  /*!<  Number of received bytes                              */
  SX1272_SX1273_REG_RX_HEADER_CNT_VALUE_MSB =   0x14,  /*!<  Number of valid headers received                      */
  SX1272_SX1273_REG_RX_HEADER_CNT_VALUE_LSB =   0x15,  /*!<  Number of valid headers received                      */
  SX1272_SX1273_REG_RX_PACKET_CNT_VALUE_MSB =   0x16,  /*!<  Number of valid packets received                      */
  SX1272_SX1273_REG_RX_PACKET_CNT_VALUE_LSB =   0x17,  /*!<  Number of valid packets received                      */
  SX1272_SX1273_REG_MODEM_STAT              =   0x18,  /*!<  Live LoRa modem status                                */
  SX1272_SX1273_REG_PKT_SNR_VALUE           =   0x19,  /*!<  Espimation of last packet SNR                         */
  SX1272_SX1273_REG_PKT_RSSI_VALUE          =   0x1A,  /*!<  RSSI of last packet                                   */
  SX1272_SX1273_REG_RSSI_VALUE              =   0x1B,  /*!<  Current RSSI                                          */
  SX1272_SX1273_REG_HOP_CHANNEL             =   0x1C,  /*!<  FHSS start channel                                    */
  SX1272_SX1273_REG_MODEM_CONFIG1           =   0x1D,  /*!<  Modem PHY config 1                                    */
  SX1272_SX1273_REG_MODEM_CONFIG2           =   0x1E,  /*!<  Modem PHY config 2                                    */
  SX1272_SX1273_REG_SYMB_TIMEOUT_LSB        =   0x1F,  /*!<  Receiver timeout value                                */
  SX1272_SX1273_REG_PREAMBLE_MSB            =   0x20,  /*!<  Size of preamble                                      */
  SX1272_SX1273_REG_PREAMBLE_LSB            =   0x21,  /*!<  Size of preamble                                      */
  SX1272_SX1273_REG_PAYLOAD_LENGTH          =   0x22,  /*!<  LoRa payload length                                   */
  SX1272_SX1273_REG_MAX_PAYLOAD_LENGTH      =   0x23,  /*!<  LoRa maximum payload length                           */
  SX1272_SX1273_REG_HOP_PERIOD              =   0x24,  /*!<  FHSS Hop period                                       */
  SX1272_SX1273_REG_FIFO_RX_BYTE_ADDR       =   0x25,  /*!<  Address of last byte written in FIFO                  */
  SX1272_SX1273_REG_FEI_MSB                 =   0x28,  /*!<  Estimated frequency error                             */
  SX1272_SX1273_REG_FEI_MIB                 =   0x29,  /*!<  Estimated frequency error                             */
  SX1272_SX1273_REG_FEI_LSB                 =   0x2A,  /*!<  Estimated frequency error                             */
  SX1272_SX1273_REG_RSSI_WIDE_BAND          =   0x2C,  /*!<  Wideband RSSI measurement                             */
  SX1272_SX1273_REG_DETECT_OPTIMIZE         =   0x31,  /*!<  LoRa detection Optimize for SF6                       */
  SX1272_SX1273_REG_INVERT_IQ               =   0x33,  /*!<  Invert LoRa I and Q signals                           */
  SX1272_SX1273_REG_DETECTION_THRESHOLD     =   0x37,  /*!<  Change the LoRa Detection threshold for SF6           */
  SX1272_SX1273_REG_SYNC_WORD               =   0x39,  /*!<  LoRa Sync Word                                        */
  SX1272_SX1273_REG_INVERT_IQ2              =   0x3B   /*!<  Optimize for inverted IQ                              */
} SX1272_SX1273_lora_registers_t;






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
