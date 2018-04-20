/**
 * @brief       MC3635.h
 * @details     3-Axis Accelerometer.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018   The ORIGIN
 * @pre         Although the MC3635 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C..
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef MC3635_H_
#define MC3635_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum{
    MC3635_ADDRESS_LOW     =   0x4C,     /*!<  DOUT_A1 = GND                                   */
    MC3635_ADDRESS_HIGH    =   0x6C      /*!<  DOUT_A1 = VDD                                   */
} MC3635_address_t;


/**
  * @brief   REGISTER SUMMARY
  */
typedef enum
{
    EXT_STAT_1      =   0x00,           /*!<  Extended Status 1                                 */
    EXT_STAT_2      =   0x01,           /*!<  Extended Status 2                                 */
    XOUT_LSB        =   0x02,           /*!<  XOUT_LSB                                          */
    XOUT_MSB        =   0x03,           /*!<  XOUT_MSB                                          */
    YOUT_LSB        =   0x04,           /*!<  YOUT_LSB                                          */
    YOUT_MSB        =   0x05,           /*!<  YOUT_MSB                                          */
    ZOUT_LSB        =   0x06,           /*!<  ZOUT_LSB                                          */
    ZOUT_MSB        =   0x07,           /*!<  ZOUT_MSB                                          */
    STATUS_1        =   0x08,           /*!<  Status 1                                          */
    STATUS_2        =   0x09,           /*!<  Status 2                                          */

    FREG_1          =   0x0D,           /*!<  Feature 1                                         */
    FREG_2          =   0x0E,           /*!<  Feature 2                                         */
    INIT_1          =   0x0F,           /*!<  Initialization 1                                  */
    MODE_C          =   0x10,           /*!<  Mode Control                                      */
    RATE_1          =   0x11,           /*!<  Rate 1                                            */
    SNIFF_C         =   0x12,           /*!<  Sniff Control                                     */
    SNIFFTH_C       =   0x13,           /*!<  Sniff Threshold Control                           */
    SNIFFCF_C       =   0x14,           /*!<  Sniff Configuration                               */
    RANGE_C         =   0x15,           /*!<  Range Resolution Control                          */
    FIFO_C          =   0x16,           /*!<  FIFO Control                                      */
    INTR_C          =   0x17,           /*!<  Interrupt Control                                 */

    INIT_3          =   0x1A,           /*!<  Initialization 3                                  */
    SCRATCH         =   0x1B,           /*!<  Scratchpad                                        */
    PMCR            =   0x1C,           /*!<  Power Mode Control                                */

    DMX             =   0x20,           /*!<  Drive Motion X                                    */
    DMY             =   0x21,           /*!<  Drive Motion Y                                    */
    DMZ             =   0x22,           /*!<  Drive Motion Z                                    */

    RESET           =   0x24,           /*!<  Reset                                             */

    INIT_2          =   0x28,           /*!<  Initialization Register 2                         */
    TRIGC           =   0x29,           /*!<  Trigger Count                                     */
    XOFFL           =   0x2A,           /*!<  X-Offset LSB                                      */
    XOFFH           =   0x2B,           /*!<  X-Offset MSB                                      */
    YOFFL           =   0x2C,           /*!<  Y-Offset LSB                                      */
    YOFFH           =   0x2D,           /*!<  Y-Offset MSB                                      */
    ZOFFL           =   0x2E,           /*!<  Z-Offset LSB                                      */
    ZOFFH           =   0x2F,           /*!<  Z-Offset MSB                                      */
    XGAIN           =   0x30,           /*!<  X Gain                                            */
    YGAIN           =   0x31,           /*!<  Y Gain                                            */
    ZGAIN           =   0x32            /*!<  Z Gain                                            */
} MC3635_register_summary_t;



/* Commands Registers */
/**
  * @brief   EXTENDED STATUS REGISTER 1
  */
/* Bit 3 : This register contains status for the I2C address of the device.  */
typedef enum{
    EXT_STAT_1_I2C_AD0_BIT_MASK =   ( 1 << 3 ),         /*!<  I2C_AD0_BIT Mask                                  */
    EXT_STAT_1_I2C_AD0_BIT_0X4C =   ( 0 << 3 ),         /*!<  I2C Address 0x4C ( DOUT_A1 = LOW )                */
    EXT_STAT_1_I2C_AD0_BIT_0X6C =   ( 1 << 3 )          /*!<  I2C Address 0x6C ( DOUT_A1 = HIGH )               */
} MC3635_ext_stat_1_i2c_ad0_bit_t;



/**
  * @brief   EXTENDED STATUS REGISTER 2
  *
  *             The device status register reports various conditions of the device data, clock and sniff
  *             circuitry.
  */
/* Bit 0 : OVR_DATA.  */
typedef enum{
    EXT_STAT_2_OVR_DATA_MASK                    =   ( 1 << 0 ),         /*!<  OVR_DATA Mask                                                                 */
    EXT_STAT_2_OVR_DATA_SAMPLE_OVERWRITTEN      =   ( 1 << 0 ),         /*!<  Previous acceleration sample was not read by host and has been overwritten    */
    EXT_STAT_2_OVR_DATA_SAMPLE_NOT_OVERWRITTEN  =   ( 0 << 0 )          /*!<  Previous acceleration sample has not been overwritten before read by host     */
} MC3635_ext_stat_2_ovr_data_t;


/* Bit 1 : PD_CLK_STAT.  */
typedef enum{
    EXT_STAT_2_PD_CLK_STAT_MASK                 =   ( 1 << 1 ),         /*!<  PD_CLK_STAT Mask                                                              */
    EXT_STAT_2_PD_CLK_STAT_CLOCKS_ENABLED       =   ( 0 << 1 ),         /*!<  Clocks are enabled                                                            */
    EXT_STAT_2_PD_CLK_STAT_CLOCKS_DISABLED      =   ( 1 << 1 )          /*!<  Clocks are disabled                                                           */
} MC3635_ext_stat_2_pd_clk_stat_t;


/* Bit 5 : OTP_BUSY.  */
typedef enum{
    EXT_STAT_2_OTP_BUSY_MASK                    =   ( 1 << 5 ),         /*!<  OTP_BUSY Mask                                                                 */
    EXT_STAT_2_OTP_BUSY_OTP_POWER_DOWN          =   ( 0 << 5 ),         /*!<  OTP_VDD supply is not enabled, OTP is powered down                            */
    EXT_STAT_2_OTP_BUSY_OTP_POWERED             =   ( 1 << 5 )          /*!<  OTP_VDD supply is enabled, OTP is powered                                     */
} MC3635_ext_stat_2_otp_busy_t;


/* Bit 6 : SNIFF_EN.  */
typedef enum{
    EXT_STAT_2_SNIFF_EN_MASK                    =   ( 1 << 6 ),         /*!<  SNIFF_EN Mask                                                                 */
    EXT_STAT_2_SNIFF_EN_DISABLED                =   ( 0 << 6 ),         /*!<  SNIFF mode is not active                                                      */
    EXT_STAT_2_SNIFF_EN_ENABLED                 =   ( 1 << 6 )          /*!<  SNIFF mode is active                                                          */
} MC3635_ext_stat_2_sniff_en_t;


/* Bit 7 : SNIFF_DETECT.  */
typedef enum{
    EXT_STAT_2_SNIFF_DETECT_MASK                =   ( 1 << 7 ),         /*!<  SNIFF_DETECT Mask                                                             */
    EXT_STAT_2_SNIFF_DETECT_NOT_EVENT           =   ( 0 << 7 ),         /*!<  No sniff event detected                                                       */
    EXT_STAT_2_SNIFF_DETECT_EVENT               =   ( 1 << 7 )          /*!<  Sniff event detected, move to CWAKE mode                                      */
} MC3635_ext_stat_2_sniff_detect_t;



/**
  * @brief   STATUS REGISTER 1
  *
  *             This register reports the operational mode of the device. Note that the lower 3-bits, the
  *             MODE[2:0] field, do not immediately change once a command is written to the MODE register,
  *             but may take up to 3 transitions of the heartbeat clock.
  */
/* Bits 2:0 : MODE.  */
typedef enum{
    STATUS_1_MODE_MASK                      =   ( 0b111 << 0 ),       /*!<  MODE Mask                                                                       */
    STATUS_1_MODE_SLEEP                     =   ( 0b000 << 0 ),       /*!<  Lowest power mode, regulators on, no clock activity, partial chip power-down    */
    STATUS_1_MODE_STANDBY                   =   ( 0b001 << 0 ),       /*!<  Low power mode, no sampling, clocks active                                      */
    STATUS_1_MODE_SNIFF                     =   ( 0b010 << 0 ),       /*!<  Sniff activity detection mode, sniff enabled, sniff sampling, no FIFO operations, automatically transition to CWAKE mode upon activity detection     */
    STATUS_1_MODE_CWAKE                     =   ( 0b101 << 0 ),       /*!<  Continuous wake. Active XYZ sampling. Sniff circuitry not active                */
    STATUS_1_MODE_SWAKE                     =   ( 0b110 << 0 ),       /*!<  Use Sniff logic, main XYZ pipeline and optional FIFO at the same time; highest power consumption                                                     */
    STATUS_1_MODE_TRIG                      =   ( 0b111 << 0 )        /*!<  Trigger mode, 1 to 254 samples or continuous, return to sleep upon completion                                                                        */
} MC3635_status_1_mode_t;


/* Bit 3 : NEW_DATA.  */
typedef enum{
    STATUS_1_NEW_DATA_MASK                  =   ( 1 << 3 ),         /*!<  NEW_DATA Mask                                                                     */
    STATUS_1_NEW_DATA_FALSE                 =   ( 0 << 3 ),         /*!<  No new sample data has arrived since last read                                    */
    STATUS_1_NEW_DATA_TRUE                  =   ( 1 << 3 )          /*!<  New sample data has arrived and has been written to FIFO/registers. This bit is always enabled and valid, regardless of the settings of any interrupt enable bits     */
} MC3635_status_1_new_data_t;


/* Bit 4 : FIFO_EMPTY.  */
typedef enum{
    STATUS_1_FIFO_EMPTY_MASK                =   ( 1 << 4 ),         /*!<  FIFO_EMPTY Mask                                                                     */
    STATUS_1_FIFO_EMPTY_FALSE               =   ( 0 << 4 ),         /*!<  FIFO has one or more samples in storage (level)                                     */
    STATUS_1_FIFO_EMPTY_TRUE                =   ( 1 << 4 )          /*!<  FIFO is empty (level) (default). This bit is set to 1 immediately after device power-up or device reset   */
} MC3635_status_1_fifo_empty_t;


/* Bit 5 : FIFO_FULL.  */
typedef enum{
    STATUS_1_FIFO_FULL_MASK                 =   ( 1 << 5 ),         /*!<  FIFO_FULL Mask                                                                      */
    STATUS_1_FIFO_FULL_FALSE                =   ( 0 << 5 ),         /*!<  FIFO has space or 1 or more samples (up to 32) (level)                              */
    STATUS_1_FIFO_FULL_TRUE                 =   ( 1 << 5 )          /*!<  FIFO is full, all 32 samples are used (level)                                       */
} MC3635_status_1_fifo_full_t;


/* Bit 6 : FIFO_THRESH.  */
typedef enum{
    STATUS_1_FIFO_THRESH_MASK               =   ( 1 << 6 ),         /*!<  FIFO_THRESH Mask                                                                    */
    STATUS_1_FIFO_THRESH_LESS               =   ( 0 << 6 ),         /*!<  Amount of data in FIFO is less than the threshold (level)                           */
    STATUS_1_FIFO_THRESH_EQUAL_GREATER      =   ( 1 << 6 )          /*!<  Amount of data in FIFO is equal to or greater than the threshold (level)            */
} MC3635_status_1_fifo_thresh_t;


/* Bit 7 : INT_PEND.  */
typedef enum{
    STATUS_1_INT_PEND_MASK                  =   ( 1 << 7 ),         /*!<  INT_PEND Mask                                                                      */
    STATUS_1_INT_PEND_FALSE                 =   ( 0 << 7 ),         /*!<  No interrupt flags are pending in register 0x09 (level)                            */
    STATUS_1_INT_PEND_TRUE                  =   ( 1 << 7 )          /*!<  One or more interrupt flags are pending in register 0x09 (logical OR) (level)      */
} MC3635_status_1_int_pend_t;



/**
  * @brief   STATUS REGISTER 2
  *
  *             This register reports the state of the interrupts ('0' means not pending; '1' means pending). A
  *             bit in this register will only be set if the corresponding interrupt enable is set to '1' in (0x17)
  *             Interrupt Control Register.
  */
/* Bit 2 : INT_WAKE.  */
typedef enum{
    STATUS_2_INT_WAKE_MASK                  =   ( 1 << 2 ),         /*!<  INT_WAKE Mask                                                                     */
    STATUS_2_INT_WAKE_FALSE                 =   ( 0 << 2 ),         /*!<  INT_WAKE not triggered                                                            */
    STATUS_2_INT_WAKE_TRUE                  =   ( 1 << 2 )          /*!<  INT_WAKE triggered                                                                */
} MC3635_status_2_int_wake_t;


/* Bit 3 : INT_ACQ.  */
typedef enum{
    STATUS_2_INT_ACQ_MASK                   =   ( 1 << 3 ),         /*!<  INT_ACQ Mask                                                                      */
    STATUS_2_INT_ACQ_FALSE                  =   ( 0 << 3 ),         /*!<  INT_ACQ not triggered                                                             */
    STATUS_2_INT_ACQ_TRUE                   =   ( 1 << 3 )          /*!<  INT_ACQ triggered                                                                 */
} MC3635_status_2_int_acq_t;


/* Bit 4 : INT_FIFO_EMPTY.  */
typedef enum{
    STATUS_2_INT_FIFO_EMPTY_MASK            =   ( 1 << 4 ),         /*!<  INT_FIFO_EMPTY Mask                                                               */
    STATUS_2_INT_FIFO_EMPTY_FALSE           =   ( 0 << 4 ),         /*!<  INT_FIFO_EMPTY not triggered                                                      */
    STATUS_2_INT_FIFO_EMPTY_TRUE            =   ( 1 << 4 )          /*!<  INT_FIFO_EMPTY triggered                                                          */
} MC3635_status_2_int_fifo_empty_t;


/* Bit 5 : INT_FIFO_FULL.  */
typedef enum{
    STATUS_2_INT_FIFO_FULL_MASK             =   ( 1 << 5 ),         /*!<  INT_FIFO_FULL Mask                                                                */
    STATUS_2_INT_FIFO_FULL_FALSE            =   ( 0 << 5 ),         /*!<  INT_FIFO_FULL not triggered                                                       */
    STATUS_2_INT_FIFO_FULL_TRUE             =   ( 1 << 5 )          /*!<  INT_FIFO_FULL triggered                                                           */
} MC3635_status_2_int_fifo_full_t;


/* Bit 6 : INT_FIFO_THRESH.  */
typedef enum{
    STATUS_2_INT_FIFO_THRESH_MASK           =   ( 1 << 6 ),         /*!<  INT_FIFO_THRESH Mask                                                              */
    STATUS_2_INT_FIFO_THRESH_FALSE          =   ( 0 << 6 ),         /*!<  INT_FIFO_THRESH not triggered                                                     */
    STATUS_2_INT_FIFO_THRESH_TRUE           =   ( 1 << 6 )          /*!<  INT_FIFO_THRESH triggered                                                         */
} MC3635_status_2_int_fifo_thresh_t;


/* Bit 7 : INT_SWAKE.  */
typedef enum{
    STATUS_2_INT_SWAKE_MASK                 =   ( 1 << 7 ),         /*!<  INT_SWAKE Mask                                                                    */
    STATUS_2_INT_SWAKE_FALSE                =   ( 0 << 7 ),         /*!<  INT_SWAKE not triggered                                                           */
    STATUS_2_INT_SWAKE_TRUE                 =   ( 1 << 7 )          /*!<  INT_SWAKE triggered                                                               */
} MC3635_status_2_int_swake_t;



/**
  * @brief   FEATURE REGISTER 1
  *
  *             This register is used to select the interface mode as well as the operation style of the FIFO and
  *             interrupt in SWAKE mode.
  */
/* Bit 3 : FREEZE.  */
typedef enum{
    FREG_1_FREEZE_MASK                   =   ( 1 << 3 ),         /*!<  FREEZE Mask                                                                                                   */
    FREG_1_FREEZE_FIFO_STANDARD_MODE     =   ( 0 << 3 ),         /*!<  FIFO operates in standard mode, does not stop capturing data in SWAKE interrupt (default)                     */
    FREG_1_FREEZE_FIFO_STOP_SWAKE        =   ( 1 << 3 )          /*!<  FIFO stops capturing on SWAKE interrupt, software can examine the conditions which generated the SWAKE event  */
} MC3635_freg_1_freeze_t;


/* Bit 4 : INTSC_EN.  */
typedef enum{
    FREG_1_INTSC_EN_MASK                 =   ( 1 << 4 ),         /*!<  INTSC_EN Mask                                                                                                                                                                                         */
    FREG_1_INTSC_EN_DISABLED             =   ( 0 << 4 ),         /*!<  Do not re-arm SNIFF block following a SWAKE event (requires the SNIFF block to be reset by exiting SWAKE mode). (default)                                                                             */
    FREG_1_INTSC_EN_ENABLED              =   ( 1 << 4 )          /*!<  Clearing the SWAKE interrupt clears and rearms the SNIFF block for subsequent detections (device may stay in SWAKE mode and continuing processing subsequent SWAKE events once interrupt is cleared)  */
} MC3635_freg_1_intsc_en_t;


/* Bit 5 : SPI3_EN.  */
typedef enum{
    FREG_1_SPI3_EN_MASK                  =   ( 1 << 5 ),         /*!<  SPI3_EN Mask                                                                          */
    FREG_1_SPI3_EN_DISABLED              =   ( 0 << 5 ),         /*!<  SPI interface is 4-wire                                                               */
    FREG_1_SPI3_EN_ENABLED               =   ( 1 << 5 )          /*!<  SPI interface is 3-wire (DOUT_A1 is the bidirectional pin)                            */
} MC3635_freg_1_spi3_en_t;


/* Bit 6 : I2C_EN.  */
typedef enum{
    FREG_1_I2C_EN_MASK                   =   ( 1 << 6 ),         /*!<  I2C_EN Mask                                                                           */
    FREG_1_I2C_EN_DISABLED               =   ( 0 << 6 ),         /*!<  Device interface is still defined as it was at power-up but no data will appear in XOUT, YOUT and ZOUT registers if both this bit and SPI_EN are set to 0 (default).  */
    FREG_1_I2C_EN_ENABLED                =   ( 1 << 6 )          /*!<  Disables any SPI communications                                                       */
} MC3635_freg_1_i2c_en_t;


/* Bit 7 : SPI_EN.  */
typedef enum{
    FREG_1_SPI_EN_MASK                   =   ( 1 << 7 ),         /*!<  SPI_EN Mask                                                                           */
    FREG_1_SPI_EN_DISABLED               =   ( 0 << 7 ),         /*!<  Device interface is still defined as it was at power-up but no data will appear in XOUT, YOUT and ZOUT registers if both this bit and I2C_EN are set to 0 (default).  */
    FREG_1_SPI_EN_ENABLED                =   ( 1 << 7 )          /*!<  Disables any I2C communications                                                       */
} MC3635_freg_1_spi_en_t;



/**
  * @brief   FEATURE REGISTER 2
  *
  *             This register allows selection of various features for the FIFO, external trigger input, method of interrupt clearing and burst address wrapping.
  */
/* Bit 0 : WRAPA.  */
typedef enum{
    FREG_2_WRAPA_MASK                    =   ( 1 << 0 ),         /*!<  WRAPA Mask                                                                                                    */
    FREG_2_WRAPA_ADDRESS_0X07            =   ( 0 << 0 ),         /*!<  Burst read cycle address wrap address is 0x07, counter automatically returns to 0x02. (default)               */
    FREG_2_WRAPA_ADDRESS_0X09            =   ( 1 << 0 )          /*!<  Burst read cycle address wrap address is 0x09, counter automatically returns to 0x02. This setting allows for status registers 0x08 and 0x09 to be included in the burst read  */
} MC3635_freg_2_wrapa_t;


/* Bit 1 : FIFO_BURST.  */
typedef enum{
    FREG_2_FIFO_BURST_MASK               =   ( 1 << 1 ),         /*!<  FIFO_BURST Mask                                                                                               */
    FREG_2_FIFO_BURST_DISABLED           =   ( 0 << 1 ),         /*!<  FIFO burst read cycles are 6-bytes in length, 0x02 to 0x07 per read cycle transaction (default)               */
    FREG_2_FIFO_BURST_ENABLED            =   ( 1 << 1 )          /*!<  FIFO burst read cycle can be any number of 6-byte reads, up to 32 x 6 bytes (i.e. the entire FIFO contents can be read). */
} MC3635_freg_2_fifo_burst_t;


/* Bit 2 : SPI_STAT_EN.  */
typedef enum{
    FREG_2_SPI_STAT_EN_MASK              =   ( 1 << 2 ),         /*!<  SPI_STAT_EN Mask                                                                                               */
    FREG_2_SPI_STAT_EN_SPI_FLAGS_DISABLED=   ( 0 << 2 ),         /*!<  No SPI status flags are shifted out (default)                                                                  */
    FREG_2_SPI_STAT_EN_SPI_FLAGS_ENABLED =   ( 1 << 2 )          /*!<  SPI status flags are shifted out on the first byte of all 4-wire SPI transactions (SPI 3-wire and I2C modes are not supported, so no effect will be seen in those modes).*/
} MC3635_freg_2_spi_stat_en_t;


/* Bit 3 : FIFO_STAT_EN.  */
typedef enum{
    FREG_2_FIFO_STAT_EN_MASK              =   ( 1 << 3 ),         /*!<  FIFO_STAT_EN Mask                                                                                                */
    FREG_2_FIFO_STAT_EN_DISABLED          =   ( 0 << 3 ),         /*!<  FIFO status feature is disabled, Z channel FIFO data is not overwritten with FIFO status information. (default)  */
    FREG_2_FIFO_STAT_EN_ENABLED           =   ( 1 << 3 )          /*!<  FIFO status feature is enabled. When the resolution is less than 14-bits, the top 4-bits of 16-bit Z channel FIFO data are replaced with FIFO status information */
} MC3635_freg_2_fifo_stat_en_t;


/* Bit 4 : I2CINT_WRCLRE.  */
typedef enum{
    FREG_2_I2CINT_WRCLRE_MASK             =   ( 1 << 4 ),         /*!<  I2CINT_WRCLRE Mask                                                                                                */
    FREG_2_I2CINT_WRCLRE_DISABLED         =   ( 0 << 4 ),         /*!<  In I2C mode, interrupts are cleared when reading register 0x09 (default)                                          */
    FREG_2_I2CINT_WRCLRE_ENABLED          =   ( 1 << 4 )          /*!<  if I2C_EN is '1', then interrupts are cleared when writing to register 0x09. Otherwise I2C reads to register 0x09 will still clear pending interrupts */
} MC3635_freg_2_i2cint_wrclre_t;


/* Bit 5 : FIFO_STREAM.  */
typedef enum{
    FREG_2_FIFO_STREAM_MASK               =   ( 1 << 5 ),         /*!<  FIFO_STREAM Mask                                                                                                   */
    FREG_2_FIFO_STREAM_DISABLED           =   ( 0 << 5 ),         /*!<  FIFO steam mode is disabled, FIFO stops accepting new data when FULL (default)                                     */
    FREG_2_FIFO_STREAM_ENABLED            =   ( 1 << 5 )          /*!<  FIFO stream mode is enabled, FIFO discards oldest samples once new data arrives                                    */
} MC3635_freg_2_fifo_stream_t;


/* Bit 6 : EXT_TRIG_POL.  */
typedef enum{
    FREG_2_EXT_TRIG_POL_MASK              =   ( 1 << 6 ),         /*!<  EXT_TRIG_POL Mask                                                                                                   */
    FREG_2_EXT_TRIG_POL_NEGATIVE_EDGE     =   ( 0 << 6 ),         /*!<  Trigger polarity is negative edge triggered (default)                                                               */
    FREG_2_EXT_TRIG_POL_POSITIVE_EDGE     =   ( 1 << 6 )          /*!<  Trigger polarity is positive edge triggered                                                                         */
} MC3635_freg_2_ext_trig_pol_t;


/* Bit 7 : EXT_TRIG_EN.  */
typedef enum{
    FREG_2_EXT_TRIG_EN_MASK              =   ( 1 << 7 ),         /*!<  EXT_TRIG_EN Mask                                                                                                    */
    FREG_2_EXT_TRIG_EN_DISABLED          =   ( 0 << 7 ),         /*!<  External trigger mode is not enabled (default)                                                                      */
    FREG_2_EXT_TRIG_EN_ENABLED           =   ( 1 << 7 )          /*!<  External trigger mode is enabled, use INTN pin as the external trigger input.                                       */
} MC3635_freg_2_ext_trig_en_t;



/**
  * @brief   INITIALIZATION REGISTER 1
  *
  *             Software must write a fixed value to this register immediately after power-up or reset. This register will not typically read-back the value which was written.
  */
/* Bits 7:0 : INIT_1.  */
typedef enum{
    INIT_1_INIT_1_FIXED_VALUE  =   0x42              /*!<  INIT_1 fix value                                                                                                   */
} MC3635_init_1_init_1_t;



/**
  * @brief   MODE CONTROL REGISTER
  *
  *             This register is the primary control register for the accelerometer. The operational mode of the device, X/Y/Z axis enables, and the TRIG one-shot
  *             mode can be written through this register. The mode transitions controlled by this register may take up to 3 transitions of the heartbeat clock.
  *             Depending on the operation, the lower 3-bits (MCTRL[2:0]) may be automatically set or cleared by hardware if auto-triggered events are executed.
  *             In general, when software sets an operational mode using the MCTRL [2:0] bits, there might be a delay time of 2 to 10 mSec before the operational mode
  *             is reflected by the MODE[2:0] bits in Status Register 1.
  */
/* Bits 2:0 : MCTRL.  */
typedef enum{
    MODE_C_MCTRL_MASK                 =   ( 0b111 << 0 ),     /*!<  MCTRL Mask                                                                                                    */
    MODE_C_MCTRL_SLEEP                =   ( 0b000 << 0 ),     /*!<  Lowest power mode, regulators on, no clock activity, partial chip power-down                                  */
    MODE_C_MCTRL_STANDBY              =   ( 0b001 << 0 ),     /*!<  Low power mode, no sampling, clocks active                                                                    */
    MODE_C_MCTRL_SNIFF                =   ( 0b010 << 0 ),     /*!<  Sniff activity detection mode, sniff enabled, no sampling, no FIFO operations, automatically transition to CWAKE mode upon activity detection  */
    MODE_C_MCTRL_CWAKE                =   ( 0b101 << 0 ),     /*!<  Continuous wake. Active XYZ sampling. Sniff circuitry not active                                              */
    MODE_C_MCTRL_SWAKE                =   ( 0b110 << 0 ),     /*!<  Use Sniff logic, main XYZ pipeline and optional FIFO at the same time; highest power consumption              */
    MODE_C_MCTRL_TRIG                 =   ( 0b111 << 0 )      /*!<  Trigger mode, 1 to 254 samples or continuous, return to sleep upon completion                                 */
} MC3635_mode_c_mctrl_t;


/* Bit 4 : X_AXIS_PD.  */
typedef enum{
    MODE_C_X_AXIS_PD_MASK             =   ( 1 << 4 ),         /*!<  X_AXIS_PD Mask                                                                                                */
    MODE_C_X_AXIS_PD_ENABLED          =   ( 0 << 4 ),         /*!<  X-axis is enabled                                                                                             */
    MODE_C_X_AXIS_PD_DISABLED         =   ( 1 << 4 )          /*!<  X-axis is disabled                                                                                            */
} MC3635_mode_c_x_axis_pd_t;


/* Bit 5 : Y_AXIS_PD.  */
typedef enum{
    MODE_C_Y_AXIS_PD_MASK             =   ( 1 << 5 ),         /*!<  Y_AXIS_PD Mask                                                                                                */
    MODE_C_Y_AXIS_PD_ENABLED          =   ( 0 << 5 ),         /*!<  Y-axis is enabled                                                                                             */
    MODE_C_Y_AXIS_PD_DISABLED         =   ( 1 << 5 )          /*!<  Y-axis is disabled                                                                                            */
} MC3635_mode_c_y_axis_pd_t;


/* Bit 6 : Z_AXIS_PD.  */
typedef enum{
    MODE_C_Z_AXIS_PD_MASK             =   ( 1 << 6 ),         /*!<  Z_AXIS_PD Mask                                                                                                */
    MODE_C_Z_AXIS_PD_ENABLED          =   ( 0 << 6 ),         /*!<  Z-axis is enabled                                                                                             */
    MODE_C_Z_AXIS_PD_DISABLED         =   ( 1 << 6 )          /*!<  Z-axis is disabled                                                                                            */
} MC3635_mode_c_z_axis_pd_t;


/* Bit 7 : TRIG_CMD.  */
typedef enum{
    MODE_C_TRIG_CMD_MASK              =   ( 1 << 7 ),         /*!<  TRIG_CMD Mask                                                                                                 */
    MODE_C_TRIG_CMD_DISABLED          =   ( 0 << 7 ),
    MODE_C_TRIG_CMD_ENABLED           =   ( 1 << 7 )
} MC3635_mode_c_trig_cmd_t;


/**
  * @brief   RATE REGISTER 1
  *
  *             This register configures the sample rates for wake modes. The rates also depend upon the value in register 0x1C.
  *             The device has several power modes which can be adjusted to achieve a desired power consumption at a certain ODR.
  *             The trade-off for lower power is either higher noise or lower ODR.
  */
/* Bits 3:0 : RR.  */
typedef enum{
    RATE_1_RR_MASK                     =   ( 0b1111 << 0 ),    /*!<  RR Mask                                                                                                    */
    RATE_1_RR_0X05                     =   ( 0x05 << 0 ),      /*!<  RR value: 0x05                                                                                             */
    RATE_1_RR_0X06                     =   ( 0x06 << 0 ),      /*!<  RR value: 0x06                                                                                             */
    RATE_1_RR_0X07                     =   ( 0x07 << 0 ),      /*!<  RR value: 0x07                                                                                             */
    RATE_1_RR_0X08                     =   ( 0x08 << 0 ),      /*!<  RR value: 0x08                                                                                             */
    RATE_1_RR_0X09                     =   ( 0x09 << 0 ),      /*!<  RR value: 0x09                                                                                             */
    RATE_1_RR_0X0A                     =   ( 0x0A << 0 ),      /*!<  RR value: 0x0A                                                                                             */
    RATE_1_RR_0X0B                     =   ( 0x0B << 0 ),      /*!<  RR value: 0x0B                                                                                             */
    RATE_1_RR_0X0C                     =   ( 0x0C << 0 ),      /*!<  RR value: 0x0C                                                                                             */
    RATE_1_RR_0X0F                     =   ( 0x0F << 0 )       /*!<  RR value: 0x0F                                                                                             */
} MC3635_rate_1_rr_t;


/**
  * @brief   SNIFF CONTROL REGISTER
  *
  *             This register selects the sample rate for SNIFF mode and the clock rate for STANDBY mode.
  */
/* Bits 3:0 : SNIFF_SR.  */
typedef enum{
    SNIFF_C_SNIFF_SR_MASK                       =   ( 0b1111 << 0 ),      /*!<  SNIFF_SR Mask                                                                                             */
    SNIFF_C_SNIFF_SR_0                          =   ( 0b0000 << 0 ),
    SNIFF_C_SNIFF_SR_1                          =   ( 0b0001 << 0 ),
    SNIFF_C_SNIFF_SR_2                          =   ( 0b0010 << 0 ),
    SNIFF_C_SNIFF_SR_3                          =   ( 0b0011 << 0 ),
    SNIFF_C_SNIFF_SR_4                          =   ( 0b0100 << 0 ),
    SNIFF_C_SNIFF_SR_5                          =   ( 0b0101 << 0 ),
    SNIFF_C_SNIFF_SR_6                          =   ( 0b0110 << 0 ),
    SNIFF_C_SNIFF_SR_7                          =   ( 0b0111 << 0 ),
    SNIFF_C_SNIFF_SR_8                          =   ( 0b1000 << 0 ),
    SNIFF_C_SNIFF_SR_9                          =   ( 0b1001 << 0 ),
    SNIFF_C_SNIFF_SR_10                         =   ( 0b1010 << 0 ),
    SNIFF_C_SNIFF_SR_11                         =   ( 0b1011 << 0 ),
    SNIFF_C_SNIFF_SR_12                         =   ( 0b1100 << 0 ),
    SNIFF_C_SNIFF_SR_13                         =   ( 0b1101 << 0 ),
    SNIFF_C_SNIFF_SR_14                         =   ( 0b1110 << 0 ),
    SNIFF_C_SNIFF_SR_15                         =   ( 0b1111 << 0 )
} MC3635_sniff_c_sniff_sr_t;


/* Bits 7:5 : STB_RATE.  */
typedef enum{
    SNIFF_C_STB_RATE_MASK                       =   ( 0b111 << 5 ),       /*!<  STB_RATE Mask                                                                                             */
    SNIFF_C_STB_RATE_0                          =   ( 0b000 << 5 ),
    SNIFF_C_STB_RATE_1                          =   ( 0b001 << 5 ),
    SNIFF_C_STB_RATE_2                          =   ( 0b010 << 5 ),
    SNIFF_C_STB_RATE_3                          =   ( 0b011 << 5 ),
    SNIFF_C_STB_RATE_4                          =   ( 0b100 << 5 ),
    SNIFF_C_STB_RATE_5                          =   ( 0b101 << 5 ),
    SNIFF_C_STB_RATE_6                          =   ( 0b110 << 5 ),
    SNIFF_C_STB_RATE_7                          =   ( 0b111 << 5 )
} MC3635_sniff_c_stb_rate_t;



/**
  * @brief   SNIFF THRESHOLD CONTROL REGISTER
  *
  *             This register sets the threshold values used by the SNIFF logic for activity detection. For each axis,
  *             a delta count is generated and compared to the threshold. When the delta count is greater than the threshold,
  *             a SNIFF wakeup event occurs. There is a unique sniff threshold for each axis, and an optional 'false detection count'
  *             which requires multiple sniff detection events to occur before a wakeup condition is declared. These features are set by
  *             six shadow registers accessed by register 0x13[5:0] and register 0x14 bits [2:0].
  */
/* Bits 5:0 : SNIFF_TH.  */
typedef enum{
    SNIFFTH_C_SNIFF_TH_MASK                       =   ( 0b111111 << 0 )     /*!<  SNIFF_TH Mask                                                                                             */
} MC3635_sniffth_c_sniff_th_t;


/* Bits 6 : SNIFF_AND_OR.  */
typedef enum{
    SNIFFTH_C_SNIFF_AND_OR_MASK                   =   ( 1 << 6 ),           /*!<  SNIFF_AND_OR Mask                                                                                                                         */
    SNIFFTH_C_SNIFF_AND_OR_OR_ENABLED             =   ( 0 << 6 ),           /*!<  OR - SNIFF wakeup/interrupt is triggered when any of the active channels have met detection threshold and count requirements (default)    */
    SNIFFTH_C_SNIFF_AND_OR_AND_ENABLED            =   ( 1 << 6 )            /*!<  AND - SNIFF wakeup/interrupt is triggered when all active channels have met detection threshold and count requirements                    */
} MC3635_sniffth_c_sniff_and_or_t;


/* Bits 7 : SNIFF_MODE.  */
typedef enum{
    SNIFFTH_C_SNIFF_MODE_MASK                     =   ( 1 << 7 ),           /*!<  SNIFF_MODE Mask                                                                                                                                                                                                   */
    SNIFFTH_C_SNIFF_MODE_C2P_ENABLED              =   ( 0 << 7 ),           /*!<  C2P Mode (Current to Previous): The delta count between current and previous samples is a moving window. The SNIFF logic uses the current sample and the immediate previous sample to compute a delta (default)   */
    SNIFFTH_C_SNIFF_MODE_C2B_ENABLED              =   ( 1 << 7 )            /*!<  C2B Mode (Current to Baseline): The delta count is generated from subtracting the current sample from the first sample stored when entering SNIFF mode                                                            */
} MC3635_sniffth_c_sniff_mode_t;



/**
  * @brief   SNIFF CONFIGURATION REGISTER
  *
  *             This register selects which of the six shadow registers is being accessed in register 0x13, and controls settings of the SNIFF hardware.
  */
/* Bits 2:0 : SNIFF_THADR.  */
typedef enum{
    SNIFFCF_C_SNIFF_THADR_MASK                      =   ( 0b111 << 0 ),     /*!<  SNIFF_THADR Mask                                                                                          */
    SNIFFCF_C_SNIFF_THADR_NONE                      =   ( 0b000 << 0 ),     /*!<  None                                                                                                      */
    SNIFFCF_C_SNIFF_THADR_SNIFF_THRESHOLD_X_AXIS    =   ( 0b001 << 0 ),     /*!<  SNIFF Threshold, X-axis                                                                                   */
    SNIFFCF_C_SNIFF_THADR_SNIFF_THRESHOLD_Y_AXIS    =   ( 0b010 << 0 ),     /*!<  SNIFF Threshold, X-axis                                                                                   */
    SNIFFCF_C_SNIFF_THADR_SNIFF_THRESHOLD_Z_AXIS    =   ( 0b011 << 0 ),     /*!<  SNIFF Threshold, X-axis                                                                                   */
    //SNIFFCF_C_SNIFF_THADR_NONE                      =   ( 0b100 << 0 ),     /*!<  None                                                                                                      */
    SNIFFCF_C_SNIFF_THADR_SNIFF_DETECTION_X_AXIS    =   ( 0b101 << 0 ),     /*!<  SNIFF Detection Count, X-axis                                                                             */
    SNIFFCF_C_SNIFF_THADR_SNIFF_DETECTION_Y_AXIS    =   ( 0b110 << 0 ),     /*!<  SNIFF Detection Count, X-axis                                                                             */
    SNIFFCF_C_SNIFF_THADR_SNIFF_DETECTION_Z_AXIS    =   ( 0b111 << 0 )      /*!<  SNIFF Detection Count, X-axis                                                                             */
} MC3635_sniffcf_c_sniff_thadr_t;


/* Bits 3 : SNIFF_CNTEN.  */
typedef enum{
    SNIFFCF_C_SNIFF_CNTEN_MASK                      =   ( 1 << 3 ),         /*!<  SNIFF_CNTEN Mask                                                                                          */
    SNIFFCF_C_SNIFF_CNTEN_DISABLED                  =   ( 0 << 3 ),         /*!<  Do not use SNIFF detection counters. (default)                                                            */
    SNIFFCF_C_SNIFF_CNTEN_ENABLED                   =   ( 1 << 3 )          /*!<  Enable SNIFF detection counts, required for valid SNIFF wakeup                                            */
} MC3635_sniffcf_c_sniff_cnten_t;


/* Bits 6:4 : SNIFF_MUX.  */
typedef enum{
    SNIFFCF_C_SNIFF_MUX_MASK                        =   ( 0b111 << 4 ),     /*!<  SNIFF_MUX Mask                                                                                            */
    SNIFFCF_C_SNIFF_MUX_DELTA_5_0                   =   ( 0b000 << 4 ),     /*!<  DELTA[5:0]                                                                                                */
    SNIFFCF_C_SNIFF_MUX_DELTA_6_1                   =   ( 0b001 << 4 ),     /*!<  DELTA[6:1]                                                                                                */
    SNIFFCF_C_SNIFF_MUX_DELTA_7_2                   =   ( 0b010 << 4 ),     /*!<  DELTA[7:2]                                                                                                */
    SNIFFCF_C_SNIFF_MUX_DELTA_8_3                   =   ( 0b011 << 4 ),     /*!<  DELTA[8:3]                                                                                                */
    SNIFFCF_C_SNIFF_MUX_DELTA_9_4                   =   ( 0b100 << 4 ),     /*!<  DELTA[9:4]                                                                                                */
    SNIFFCF_C_SNIFF_MUX_DELTA_10_5                  =   ( 0b101 << 4 )      /*!<  DELTA[10:5]                                                                                               */
} MC3635_sniffcf_c_sniff_mux_t;


/* Bits 7 : SNIFF_RESET.  */
typedef enum{
    SNIFFCF_C_SNIFF_RESET_MASK                      =   ( 1 << 7 ),         /*!<  SNIFF_RESET Mask                                                                                          */
    SNIFFCF_C_SNIFF_RESET_DISABLED                  =   ( 0 << 7 ),         /*!<  SNIFF block reset is not applied (default).                                                               */
    SNIFFCF_C_SNIFF_RESET_ENABLED                   =   ( 1 << 7 )          /*!<  SNIFF block reset is applied                                                                              */
} MC3635_sniffcf_c_sniff_reset_t;



/**
  * @brief   RANGE AND RESOLUTION CONTROL REGISTER
  *
  *             The RANGE register sets the resolution and range options for the accelerometer. All numbers are sign-extended, 2's complement format.
  *             All results are reported in registers 0x02 to 0x07. When the FIFO is enabled, only 6 to 12-bit resolutions are supported due to the
  *             12-bit width of the FIFO.
  */
/* Bits 2:0 : RES.  */
typedef enum{
    RANGE_C_RES_MASK                              =   ( 0b111 << 0 ),       /*!<  RES Mask                                                                                                  */
    RANGE_C_RES_6_BITS                            =   ( 0b000 << 0 ),       /*!<  6 bits                                                                                                    */
    RANGE_C_RES_7_BITS                            =   ( 0b001 << 0 ),       /*!<  7 bits                                                                                                    */
    RANGE_C_RES_8_BITS                            =   ( 0b010 << 0 ),       /*!<  8 bits                                                                                                    */
    RANGE_C_RES_10_BITS                           =   ( 0b011 << 0 ),       /*!<  10 bits                                                                                                   */
    RANGE_C_RES_12_BITS                           =   ( 0b100 << 0 ),       /*!<  12 bits                                                                                                   */
    RANGE_C_RES_14_BITS                           =   ( 0b101 << 0 )        /*!<  14 bits (only 12-bits if FIFO enabled)                                                                    */
} MC3635_range_c_res_t;


/* Bits 6:4 : RANGE.  */
typedef enum{
    RANGE_C_RANGE_MASK                            =   ( 0b111 << 4 ),       /*!<  RANGE Mask                                                                                                */
    RANGE_C_RANGE_2G                              =   ( 0b000 << 4 ),       /*!<  ±2g                                                                                                       */
    RANGE_C_RANGE_4G                              =   ( 0b001 << 4 ),       /*!<  ±4g                                                                                                       */
    RANGE_C_RANGE_8G                              =   ( 0b010 << 4 ),       /*!<  ±8g                                                                                                       */
    RANGE_C_RANGE_16G                             =   ( 0b011 << 4 ),       /*!<  ±16g                                                                                                      */
    RANGE_C_RANGE_12G                             =   ( 0b100 << 4 )        /*!<  ±12g                                                                                                      */
} MC3635_range_c_range_t;



/**
  * @brief   FIFO CONTROL REGISTER
  *
  *             This register selects the FIFO threshold level, operation mode, FIFO reset and enable. With the exception of FIFO_RESET,
  *             the FIFO_EN bit must be '1' for any FIFO interrupts, thresholds, or modes to be enabled. The FIFO flags in register 0x08 will
  *             continue to report FIFO defaults even if the FIFO_EN is '0'.
  */
/* Bits 4:0 : FIFO_TH.  */
typedef enum{
    FIFO_C_FIFO_TH_MASK                           =   ( 0b11111 << 0 )      /*!<  The FIFO threshold level selects the number of samples in the FIFO for different FIFO events. The threshold value may be 1 to 31 (00001 to 11111)        */
} MC3635_fifo_c_fifo_th_t;


/* Bit 5 : FIFO_MODE.  */
typedef enum{
    FIFO_C_FIFO_MODE_MASK                         =   ( 1 << 5 ),           /*!<  FIFO_MODE Mask                                                                                                                                                                */
    FIFO_C_FIFO_MODE_NORMAL                       =   ( 0 << 5 ),           /*!<  Normal operation, the FIFO continues to accept new sample data as long as there is space remaining (default)                                                                  */
    FIFO_C_FIFO_MODE_WATERMARK                    =   ( 1 << 5 )            /*!<  Watermark, once the amount of samples in the FIFO reaches or exceeds the threshold level, the FIFO stops accepting new sample data. Any additional sample data is 'dropped'   */
} MC3635_fifo_c_fifo_mode_t;


/* Bit 6 : FIFO_EN.  */
typedef enum{
    FIFO_C_FIFO_EN_MASK                           =   ( 1 << 6 ),           /*!<  FIFO_EN Mask                                                                                          */
    FIFO_C_FIFO_EN_DISABLED                       =   ( 0 << 6 ),           /*!<  No FIFO operation, sample data written directly to output registers                                   */
    FIFO_C_FIFO_EN_ENABLED                        =   ( 1 << 6 )            /*!<  FIFO enabled, all sample data written to FIFO write port if there is room. The FIFO write clock is controlled by this enable, resulting in higher dynamic power   */
} MC3635_fifo_c_fifo_en_t;


/* Bit 7 : FIFO_RESET.  */
typedef enum{
    FIFO_C_FIFO_RESET_MASK                        =   ( 1 << 7 ),           /*!<  FIFO_RESET Mask                                                                                       */
    FIFO_C_FIFO_RESET_DISABLED                    =   ( 0 << 7 ),           /*!<  FIFO reset is disabled, normal operation (default)                                                    */
    FIFO_C_FIFO_RESET_ENABLED                     =   ( 1 << 7 )            /*!<  FIFO read and write pointers are cleared, FIFO contents returned to 0                                 */
} MC3635_fifo_c_fifo_reset_t;



/**
  * @brief   INTERRUPT CONTROL REGISTER
  *
  */
/* Bit 0 : IPP.  */
typedef enum{
    INTR_C_IPP_MASK                               =   ( 1 << 0 ),           /*!<  IPP Mask                                                                                              */
    INTR_C_IPP_OPEN_DRAIN_MODE                    =   ( 0 << 0 ),           /*!<  INTN pin is configured for open-drain mode (external pull-up to VDDIO required) (default)             */
    INTR_C_IPP_PUSH_PULL_MODE                     =   ( 1 << 0 )            /*!<  INTN pin is configured for active drive or 'push-pull' mode. Drive level is to VDDIO                  */
} MC3635_intr_c_ipp_t;


/* Bit 1 : IAH.  */
typedef enum{
    INTR_C_IAH_MASK                               =   ( 1 << 1 ),           /*!<  IAH Mask                                                                                              */
    INTR_C_IAH_ACTIVE_LOW                         =   ( 0 << 1 ),           /*!<  Interrupt request is active low (default).                                                            */
    INTR_C_IAH_ACTIVE_HIGH                        =   ( 1 << 1 )            /*!<  Interrupt request is active high                                                                      */
} MC3635_intr_c_iah_t;


/* Bit 2 : INT_WAKE.  */
typedef enum{
    INTR_C_INT_WAKE_MASK                          =   ( 1 << 2 ),           /*!<  INT_WAKE Mask                                                                                                     */
    INTR_C_INT_WAKE_DISABLED                      =   ( 0 << 2 ),           /*!<  No interrupt is generated when SNIFF activity is detected and the device auto-transitions to CWAKE mode (default) */
    INTR_C_INT_WAKE_ENABLED                       =   ( 1 << 2 )            /*!<  Generate an interrupt when activity is detected in SNIFF mode and the device auto-transitions to CWAKE mode.      */
} MC3635_intr_c_int_wake_t;


/* Bit 3 : INT_ACQ.  */
typedef enum{
    INTR_C_INT_ACQ_MASK                           =   ( 1 << 3 ),           /*!<  INT_ACQ Mask                                                                                                      */
    INTR_C_INT_ACQ_DISABLED                       =   ( 0 << 3 ),           /*!<  No interrupt generated when new sample data is acquired (default)                                                 */
    INTR_C_INT_ACQ_ENABLED                        =   ( 1 << 3 )            /*!<  Generate an interrupt when new sample data is acquired (applies to new data written to output registers or FIFO). This enable is paired with the NEW_DATA flag in register 0x08   */
} MC3635_intr_c_int_acq_t;


/* Bit 4 : INT_FIFO_EMPTY.  */
typedef enum{
    INTR_C_INT_FIFO_EMPTY_MASK                    =   ( 1 << 4 ),           /*!<  INT_FIFO_EMPTY Mask                                                                                               */
    INTR_C_INT_FIFO_EMPTY_DISABLED                =   ( 0 << 4 ),           /*!<  No interrupt is generated when the FIFO is empty or completely drained of sample data (default)                   */
    INTR_C_INT_FIFO_EMPTY_ENABLED                 =   ( 1 << 4 )            /*!<  Generate an interrupt when the FIFO is empty. This interrupt is paired with the FIFO_EMPTY flag in register 0x08. Note that this interrupt is independent of the FIFO threshold level, and will only activate when the FIFO sample count has reached a value of 0   */
} MC3635_intr_c_int_fifo_empty_t;


/* Bit 5 : INT_FIFO_FULL.  */
typedef enum{
    INTR_C_INT_FIFO_FULL_MASK                     =   ( 1 << 5 ),           /*!<  INT_FIFO_FULL Mask                                                                                                */
    INTR_C_INT_FIFO_FULL_DISABLED                 =   ( 0 << 5 ),           /*!<  No interrupt is generated when the FIFO is empty or completely filled of sample data (default)                    */
    INTR_C_INT_FIFO_FULL_ENABLED                  =   ( 1 << 5 )            /*!<  Generate an interrupt when the FIFO is full. This interrupt is paired with the FIFO_FULL flag in register 0x08. Note that this interrupt is independent of the FIFO threshold level, and will only activate when the FIFO sample count has reached a value of 32  */
} MC3635_intr_c_int_fifo_full_t;


/* Bit 6 : INT_FIFO_THRESH.  */
typedef enum{
    INTR_C_INT_FIFO_THRESH_MASK                   =   ( 1 << 6 ),           /*!<  INT_FIFO_THRESH Mask                                                                                              */
    INTR_C_INT_FIFO_THRESH_DISABLED               =   ( 0 << 6 ),           /*!<  No interrupt is generated when the FIFO threshold level is reached (default)                                      */
    INTR_C_INT_FIFO_THRESH_ENABLED                =   ( 1 << 6 )            /*!<  Generate an interrupt when the FIFO threshold level is reached                                                    */
} MC3635_intr_c_int_fifo_thresh_t;


/* Bit 7 : INT_SWAKE.  */
typedef enum{
    INTR_C_INT_SWAKE_MASK                         =   ( 1 << 7 ),           /*!<  INT_SWAKE Mask                                                                                                    */
    INTR_C_INT_SWAKE_DISABLED                     =   ( 0 << 7 ),           /*!<  No interrupt generated when SNIFF activity is detected (default)                                                  */
    INTR_C_INT_SWAKE_ENABLED                      =   ( 1 << 7 )            /*!<  Generate an interrupt when SNIFF activity is detected                                                             */
} MC3635_intr_c_int_fifo_swake_t;



/**
  * @brief   INITIALIZATION REGISTER 3
  *
  *             Software must write a fixed value to this register immediately after power-up or reset
  */
/* Bits 7:0 : INIT_3.  */
typedef enum{
    INIT_3_INT_3_FIXED_VALUE                     =   0                      /*!<  INIT_3 fixed value                                                                                               */
} MC3635_init_3_int_3t;



/**
  * @brief   POWER MODE CONTROL REGISTER
  *
  *             This register selects the power setting for CWAKE, SWAKE and SNIFF modes.
  */
/* Bits 2:0 : CSPM.  */
typedef enum{
    PMCR_CSPM_MASK                                =   ( 0b111 << 0 ),       /*!<  CSPM Mask                                                                                                     */
    PMCR_CSPM_LOW_POWER_MODE                      =   ( 0b000 << 0 ),       /*!<  Low Power Mode (nominal noise levels) (default)                                                               */
    PMCR_CSPM_ULTRA_LOW_POWER_MODE                =   ( 0b011 << 0 ),       /*!<  Ultra-Low Power Mode (highest noise levels)                                                                   */
    PMCR_CSPM_PRECISION_MODE                      =   ( 0b100 << 0 )        /*!<  Precision Mode (lowest noise levels)                                                                          */
} MC3635_pmcr_cspm_t;


/* Bits 6:4 : SPM.  */
typedef enum{
    PMCR_SPM_MASK                                 =   ( 0b111 << 4 ),       /*!<  SPM Mask                                                                                                      */
    PMCR_SPM_LOW_POWER_MODE                       =   ( 0b000 << 4 ),       /*!<  Low Power Mode (nominal noise levels) (default)                                                               */
    PMCR_SPM_ULTRA_LOW_POWER_MODE                 =   ( 0b011 << 4 ),       /*!<  Ultra-Low Power Mode (highest noise levels)                                                                   */
    PMCR_SPM_PRECISION_MODE                       =   ( 0b100 << 4 )        /*!<  Precision Mode (lowest noise levels)                                                                          */
} MC3635_pmcr_spm_t;


/* Bit 7 : SPI_HS_EN.  */
typedef enum{
    PMCR_SPI_HS_EN_MASK                           =   ( 1 << 7 ),           /*!<  SPI_HS_EN Mask                                                                                                */
    PMCR_SPI_HS_EN_DISABLED                       =   ( 0 << 7 ),           /*!<  This bit will always return a '0' when read. Software must keep track of the state of this bit                */
    PMCR_SPI_HS_EN_ENABLED                        =   ( 1 << 7 )            /*!<  SPI High-Speed Enable                                                                                         */
} MC3635_pmcr_spi_hs_en_t;



/**
  * @brief   DRIVE MOTION X REGISTER
  *
  *             This register controls the test mode which moves the sensor in the X axis direction and initializes specific hardware bits.
  */
/* Bit 2 : DPX.  */
typedef enum{
    DMX_DPX_MASK                                  =   ( 1 << 2 ),           /*!<  DPX Mask                                                                                              */
    DMX_DPX_DISABLED                              =   ( 0 << 2 ),           /*!<  Disabled (default)                                                                                    */
    DMX_DPX_ENABLED                               =   ( 1 << 2 )            /*!<  Move the sensor in X Positive direction                                                               */
} MC3635_dmx_dpx_t;


/* Bit 3 : DNX.  */
typedef enum{
    DMX_DNX_MASK                                  =   ( 1 << 3 ),           /*!<  DNX Mask                                                                                              */
    DMX_DNX_DISABLED                              =   ( 0 << 3 ),           /*!<  Disabled (default)                                                                                    */
    DMX_DNX_ENABLED                               =   ( 1 << 3 )            /*!<  Move the sensor in X Negative direction                                                               */
} MC3635_dmx_dpnx_t;



/**
  * @brief   DRIVE MOTION Y REGISTER
  *
  *             This register controls the test mode which moves the sensor in the Y axis direction and initializes specific hardware bits.
  */
/* Bit 2 : DPY.  */
typedef enum{
    DMY_DPX_MASK                                  =   ( 1 << 2 ),           /*!<  DPY Mask                                                                                              */
    DMY_DPX_DISABLED                              =   ( 0 << 2 ),           /*!<  Disabled (default)                                                                                    */
    DMY_DPX_ENABLED                               =   ( 1 << 2 )            /*!<  Move the sensor in Y Positive direction                                                               */
} MC3635_dmy_dpy_t;


/* Bit 3 : DNY.  */
typedef enum{
    DMY_DNY_MASK                                  =   ( 1 << 3 ),           /*!<  DNY Mask                                                                                              */
    DMY_DNY_DISABLED                              =   ( 0 << 3 ),           /*!<  Disabled (default)                                                                                    */
    DMY_DNY_ENABLED                               =   ( 1 << 3 )            /*!<  Move the sensor in Y Negative direction                                                               */
} MC3635_dmy_dpny_t;



/**
  * @brief   DRIVE MOTION Z REGISTER
  *
  *             This register controls the test mode which moves the sensor in the Z axis direction.
  */
/* Bit 2 : DPZ.  */
typedef enum{
    DMZ_DPZ_MASK                                  =   ( 1 << 2 ),           /*!<  DPZ Mask                                                                                              */
    DMZ_DPZ_DISABLED                              =   ( 0 << 2 ),           /*!<  Disabled (default)                                                                                    */
    DMZ_DPZ_ENABLED                               =   ( 1 << 2 )            /*!<  Move the sensor in Z Positive direction                                                               */
} MC3635_dmz_dpz_t;


/* Bit 3 : DNZ.  */
typedef enum{
    DMZ_DNZ_MASK                                  =   ( 1 << 3 ),           /*!<  DNZ Mask                                                                                              */
    DMZ_DNZ_DISABLED                              =   ( 0 << 3 ),           /*!<  Disabled (default)                                                                                    */
    DMZ_DNZ_ENABLED                               =   ( 1 << 3 )            /*!<  Move the sensor in Z Negative direction                                                               */
} MC3635_dmz_dpnz_t;



/**
  * @brief   RESET REGISTER
  *
  *             This register can be used to reset the device. Anytime there is a reset to the device, a POR event, or a
  *             power cycle the SPI 3-wire configuration will reset to 4-wire mode.
  */
/* Bit 6 : RESET.  */
typedef enum{
    RESET_RESET_MASK                                =   ( 1 << 6 ),           /*!<  RESET Mask                                                                                            */
    RESET_RESET_NORMAL_OPERATION                    =   ( 0 << 6 ),           /*!<  Normal operation (default)                                                                            */
    RESET_RESET_FORCE_POWER_ON_RESET                =   ( 1 << 6 )            /*!<  Force a power-on-reset (POR) sequence                                                                 */
} MC3635_reset_reset_t;


/* Bit 7 : RELOAD.  */
typedef enum{
    RESET_RELOAD_MASK                               =   ( 1 << 7 ),           /*!<  RELOAD Mask                                                                                           */
    RESET_RELOAD_NORMAL_OPERATION                   =   ( 0 << 7 ),           /*!<  Normal operation (default)                                                                            */
    RESET_RELOAD_RELOAD_REGISTER_FROM_OTP           =   ( 1 << 7 )            /*!<  Reloads the registers from OTP                                                                        */
} MC3635_reset_reload_t;



/**
  * @brief   INITIALIZATION REGISTER 2
  *
  *             Software must write a fixed value to this register immediately after power-up or reset
  */
/* Bits 7:0 : INIT_2.  */
typedef enum{
    INIT_2_INT_2_FIXED_VALUE                      =   0                      /*!<  INIT_2 fixed value                                                                                       */
} MC3635_init_2_int_2_t;



/**
  * @brief   TRIGGER COUNT REGISTER
  *
  *             This register selects the number of samples to be taken after the one-shot trigger is started
  */
/* Bits 7:0 : TRIGC.  */
typedef enum{
    TRIGC_MASK                                    =   0xFF                   /*!<  TRIGC Mask                                                                                               */
} MC3635_trigc_t;




/**
  * @brief   X-AXIS OFFSET REGISTERS
  *
  *             This register contains a signed 2's complement 15-bit value applied as an offset adjustment to the output
  *             of the acceleration values, prior to being sent to the OUT_EX registers. The Power-On-Reset value for each
  *             chip is unique and is set as part of factory calibration. If necessary, this value can be overwritten by software.
  */
/* Bits 7:0 : XOFFL.  */
typedef enum{
    XOFFL_MASK                                    =   0xFF                   /*!<  XOFFL Mask                                                                                               */
} MC3635_x_axis_offset_xoffl_t;


/* Bits 7:0 : XOFFH.  */
typedef enum{
    XOFFH_MASK                                    =   ( 0b01111111 << 0 )    /*!<  XOFFH Mask                                                                                               */
} MC3635_x_axis_offset_xoffh_t;



/**
  * @brief   Y-AXIS OFFSET REGISTERS
  *
  *             This register contains a signed 2's complement 15-bit value applied as an offset adjustment to the output
  *             of the acceleration values, prior to being sent to the OUT_EX registers. The Power-On-Reset value for each
  *             chip is unique and is set as part of factory calibration. If necessary, this value can be overwritten by software.
  */
/* Bits 7:0 : YOFFL.  */
typedef enum{
    YOFFL_MASK                                    =   0xFF                   /*!<  YOFFL Mask                                                                                               */
} MC3635_y_axis_offset_yoffl_t;


/* Bits 7:0 : YOFFH.  */
typedef enum{
    YOFFH_MASK                                    =   ( 0b01111111 << 0 )    /*!<  YOFFH Mask                                                                                               */
} MC3635_y_axis_offset_yoffh_t;



/**
  * @brief   Z-AXIS OFFSET REGISTERS
  *
  *             This register contains a signed 2's complement 15-bit value applied as an offset adjustment to the output
  *             of the acceleration values, prior to being sent to the OUT_EX registers. The Power-On-Reset value for each
  *             chip is unique and is set as part of factory calibration. If necessary, this value can be overwritten by software.
  */
/* Bits 7:0 : ZOFFL.  */
typedef enum{
    ZOFFL_MASL                                    =   0xFF                   /*!<  ZOFFL Mask                                                                                               */
} MC3635_z_axis_offset_zoffl_t;


/* Bits 7:0 : ZOFFH.  */
typedef enum{
    ZOFFH_MASK                                    =   ( 0b01111111 << 0 )    /*!<  ZOFFH Mask                                                                                               */
} MC3635_z_axis_offset_zoffh_t;



/**
  * @brief   X-AXIS GAIN REGISTERS
  *
  *             The gain value is an unsigned 9-bit number.
  */
/* Bits 7:0 : GAIN LSB.  */
typedef enum{
    XGAINL_GAIN_MASK                                =   0xFF                   /*!<  XGAINL GAIN Mask                                                                                         */
} MC3635_x_axis_xgainl_t;


/* Bits 7:0 : GAIN HSB.  */
typedef enum{
    XGAINH_GAIN_MASK                                =   ( 1 << 7 )             /*!<  XGAINH GAIN Mask                                                                                         */
} MC3635_x_axis_xgainh_t;



/**
  * @brief   Y-AXIS GAIN REGISTERS
  *
  *             The gain value is an unsigned 9-bit number.
  */
/* Bits 7:0 : GAIN LSB.  */
typedef enum{
    YGAINL_GAIN_MASK                                =   0xFF                   /*!<  YGAINL GAIN Mask                                                                                         */
} MC3635_y_axis_ygainl_t;


/* Bits 7:0 : GAIN HSB.  */
typedef enum{
    YGAINH_GAIN_MASK                                =   ( 1 << 7 )             /*!<  YGAINH GAIN Mask                                                                                         */
} MC3635_y_axis_ygainh_t;



/**
  * @brief   Z-AXIS GAIN REGISTERS
  *
  *             The gain value is an unsigned 9-bit number.
  */
/* Bits 7:0 : GAIN LSB.  */
typedef enum{
    ZGAINL_GAIN_MASK                                =   0xFF                   /*!<  ZGAINL GAIN Mask                                                                                         */
} MC3635_z_axis_zgainl_t;


/* Bits 7:0 : GAIN HSB.  */
typedef enum{
    ZGAINH_GAIN_MASK                                =   ( 1 << 7 )             /*!<  ZGAINH GAIN Mask                                                                                         */
} MC3635_z_axis_zgainh_t;





/**
  * @brief   ODR ( Hz )
  *
  *             Sample rates for wake modes.
  */
typedef enum{
    ODR_14_HZ       =   0x00,                   /*!<  ODR 14 Hz    Mode: Low Power | Precision            */
    ODR_25_HZ       =   0x01,                   /*!<  ODR 25 Hz    Mode: Ultra-Low Power                  */
    ODR_28_HZ       =   0x02,                   /*!<  ODR 28 Hz    Mode: Low Power | Precision            */
    ODR_50_HZ       =   0x03,                   /*!<  ODR 50 Hz    Mode: Ultra-Low Power                  */
    ODR_54_HZ       =   0x04,                   /*!<  ODR 54 Hz    Mode: Low Power                        */
    ODR_55_HZ       =   0x05,                   /*!<  ODR 55 Hz    Mode: Precision                        */
    ODR_80_HZ       =   0x06,                   /*!<  ODR 80 Hz    Mode: Precision                        */
    ODR_100_HZ      =   0x07,                   /*!<  ODR 100 Hz   Mode: Ultra-Low Power | Precision      */
    ODR_105_HZ      =   0x08,                   /*!<  ODR 105 Hz   Mode: Low Power                        */
    ODR_190_HZ      =   0x09,                   /*!<  ODR 190 Hz   Mode: Ultra-Low Power                  */
    ODR_210_HZ      =   0x0A,                   /*!<  ODR 210 Hz   Mode: Low Power                        */
    ODR_380_HZ      =   0x0B,                   /*!<  ODR 380 Hz   Mode: Ultra-Low Power                  */
    ODR_400_HZ      =   0x0C,                   /*!<  ODR 400 Hz   Mode: Low Power                        */
    ODR_600_HZ      =   0x0D,                   /*!<  ODR 600 Hz   Mode: Low Power                        */
    ODR_750_HZ      =   0x0E,                   /*!<  ODR 750 Hz   Mode: Ultra-Low Power | Low Power      */
    ODR_1100_HZ     =   0x0F,                   /*!<  ODR 1100 Hz  Mode: Ultra-Low Power                  */
    ODR_1300_HZ     =   0x10                    /*!<  ODR 1300 Hz  Mode: Ultra-Low Power                  */
} MC3635_odr_t;










#ifndef MC3635_VECTOR_STRUCT_H
#define MC3635_VECTOR_STRUCT_H
typedef struct{
    int16_t XAxis;
    int16_t YAxis;
    int16_t ZAxis;

    uint8_t Xout_lsb;                       /*!<  XOUT LSB                                                                */
    uint8_t Xout_msb;                       /*!<  XOUT MSB                                                                */
    uint8_t Yout_lsb;                       /*!<  YOUT LSB                                                                */
    uint8_t Yout_msb;                       /*!<  YOUT MSB                                                                */
    uint8_t Zout_lsb;                       /*!<  ZOUT LSB                                                                */
    uint8_t Zout_msb;                       /*!<  ZOUT MSB                                                                */

    uint8_t scratch;                        /*!<  Any value can be written and read-back                                  */
    uint8_t ext_stat_2;                     /*!<  It contains the value for the Extended Status Register 2                */
    uint8_t status_1;                       /*!<  It contains the value for the Status Register 1                         */
    uint8_t status_2;                       /*!<  It contains the value for the Status Register 2                         */
    uint8_t myFeatureRegister1;             /*!<  It contains the value for the Feature Register 1                        */
    uint8_t myFeatureRegister2;             /*!<  It contains the value for the Feature Register 2                        */
} MC3635_data_t;
#endif


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MC3635_SUCCESS     =       0,
    MC3635_FAILURE     =       1
} MC3635_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
        */
MC3635_status_t  MC3635_Init                          ( I2C_parameters_t myI2Cparameters );

/** It starts an initialization sequence.
        */
MC3635_status_t  MC3635_InitializationSequence        ( I2C_parameters_t myI2Cparameters );

/** It writes into the scratch pad register.
        */
MC3635_status_t  MC3635_WriteScratchpadRegister       ( I2C_parameters_t myI2Cparameters, uint8_t myScratchpadRegister );

/** It reads the scratch pad register.
        */
MC3635_status_t  MC3635_ReadScratchpadRegister        ( I2C_parameters_t myI2Cparameters, uint8_t* myScratchpadRegister );

/** It performs a software reset.
        */
MC3635_status_t  MC3635_SetSoftwareReset              ( I2C_parameters_t myI2Cparameters );

/** It performs a reload.
        */
MC3635_status_t  MC3635_SetReload                     ( I2C_parameters_t myI2Cparameters );

///** It sets the operational mode.
//        */
//MC3635_status_t  MC3635_SetOperationalMode            ( I2C_parameters_t myI2Cparameters );
//
///** It reads the operational mode.
//        */
//MC3635_status_t  MC3635_GetOperationalMode            ( I2C_parameters_t myI2Cparameters );

/** It reads the Extended Status Register 2.
        */
MC3635_status_t  MC3635_ReadExtendedStatusRegister2     ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myExt_stat_2 );

/** It reads X, Y and Z raw data output.
        */
MC3635_status_t  MC3635_ReadRawData                     ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myRawData );

/** It reads the Status Register 1.
        */
MC3635_status_t  MC3635_ReadStatusRegister1             ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myStatus_1 );

/** It reads the Status Register 2.
        */
MC3635_status_t  MC3635_ReadStatusRegister2             ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myStatus_2 );

/** It reads the Feature Register 1.
        */
MC3635_status_t  MC3635_ReadFeatureRegister1            ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myFeatureRegister1 );

/** It reads the Feature Register 2.
        */
MC3635_status_t  MC3635_ReadFeatureRegister2            ( I2C_parameters_t myI2Cparameters, MC3635_data_t* myFeatureRegister2 );

/** It starts the Initialization Register 1.
        */
MC3635_status_t  MC3635_InitializationRegister1         ( I2C_parameters_t myI2Cparameters );

/** It sets mode control of the device and if the trigger bit is enabled, the number of samples to be acquired is given as well.
        */
MC3635_status_t  MC3635_SetModeControl                  ( I2C_parameters_t myI2Cparameters, MC3635_mode_c_mctrl_t myOperationalMode, MC3635_mode_c_x_axis_pd_t myXAxis, MC3635_mode_c_y_axis_pd_t myYAxis,
                                                          MC3635_mode_c_z_axis_pd_t myZAxis, MC3635_mode_c_trig_cmd_t myTriggerEnable, uint8_t myTriggerSamples );
/** It sets the operational mode.
        */
MC3635_status_t  MC3635_SetOperationalMode              ( I2C_parameters_t myI2Cparameters, MC3635_mode_c_mctrl_t myOperationalMode );

/** It sets the power mode and odr for wake modes.
        */
MC3635_status_t  MC3635_SetWakePowerModeODR             ( I2C_parameters_t myI2Cparameters, MC3635_pmcr_cspm_t myPowerMode, MC3635_odr_t myODR );



#ifdef __cplusplus
}
#endif

#endif /* MC3635_H_ */
