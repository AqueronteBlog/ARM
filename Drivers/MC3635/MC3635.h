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
} MC3635_act_inact_ctl_activity_dc_coupled_t;



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
    STATUS_REG_1_MODE_MASK                      =   ( 0b111 << 0 ),       /*!<  MODE Mask                                                                       */
    STATUS_REG_1_MODE_SLEEP                     =   ( 0b000 << 0 ),       /*!<  Lowest power mode, regulators on, no clock activity, partial chip power-down    */
    STATUS_REG_1_MODE_STANDBY                   =   ( 0b001 << 0 ),       /*!<  Low power mode, no sampling, clocks active                                      */
    STATUS_REG_1_MODE_SNIFF                     =   ( 0b010 << 0 ),       /*!<  Sniff activity detection mode, sniff enabled, sniff sampling, no FIFO operations, automatically transition to CWAKE mode upon activity detection     */
    STATUS_REG_1_MODE_CWAKE                     =   ( 0b101 << 0 ),       /*!<  Continuous wake. Active XYZ sampling. Sniff circuitry not active                */
    STATUS_REG_1_MODE_SWAKE                     =   ( 0b110 << 0 ),       /*!<  Use Sniff logic, main XYZ pipeline and optional FIFO at the same time; highest power consumption                                                     */
    STATUS_REG_1_MODE_TRIG                      =   ( 0b111 << 0 )        /*!<  Trigger mode, 1 to 254 samples or continuous, return to sleep upon completion                                                                        */
} MC3635_status_reg1_mode_t;


/* Bit 3 : NEW_DATA.  */
typedef enum{
    STATUS_REG_1_NEW_DATA_MASK                  =   ( 1 << 3 ),         /*!<  NEW_DATA Mask                                                                     */
    STATUS_REG_1_NEW_DATA_FALSE                 =   ( 0 << 3 ),         /*!<  No new sample data has arrived since last read                                    */
    STATUS_REG_1_NEW_DATA_TRUE                  =   ( 1 << 3 )          /*!<  New sample data has arrived and has been written to FIFO/registers. This bit is always enabled and valid, regardless of the settings of any interrupt enable bits     */
} MC3635_status_reg1_new_data_t;


/* Bit 4 : FIFO_EMPTY.  */
typedef enum{
    STATUS_REG_1_FIFO_EMPTY_MASK                =   ( 1 << 4 ),         /*!<  FIFO_EMPTY Mask                                                                     */
    STATUS_REG_1_FIFO_EMPTY_FALSE               =   ( 0 << 4 ),         /*!<  FIFO has one or more samples in storage (level)                                     */
    STATUS_REG_1_FIFO_EMPTY_TRUE                =   ( 1 << 4 )          /*!<  FIFO is empty (level) (default). This bit is set to 1 immediately after device power-up or device reset   */
} MC3635_status_reg1_fifo_empty_t;


/* Bit 5 : FIFO_FULL.  */
typedef enum{
    STATUS_REG_1_FIFO_FULL_MASK                 =   ( 1 << 5 ),         /*!<  FIFO_FULL Mask                                                                      */
    STATUS_REG_1_FIFO_FULL_FALSE                =   ( 0 << 5 ),         /*!<  FIFO has space or 1 or more samples (up to 32) (level)                              */
    STATUS_REG_1_FIFO_FULL_TRUE                 =   ( 1 << 5 )          /*!<  FIFO is full, all 32 samples are used (level)                                       */
} MC3635_status_reg1_fifo_full_t;


/* Bit 6 : FIFO_THRESH.  */
typedef enum{
    STATUS_REG_1_FIFO_THRESH_MASK               =   ( 1 << 6 ),         /*!<  FIFO_THRESH Mask                                                                    */
    STATUS_REG_1_FIFO_THRESH_LESS               =   ( 0 << 6 ),         /*!<  Amount of data in FIFO is less than the threshold (level)                           */
    STATUS_REG_1_FIFO_THRESH_EQUAL_GREATER      =   ( 1 << 6 )          /*!<  Amount of data in FIFO is equal to or greater than the threshold (level)            */
} MC3635_status_reg1_fifo_thresh_t;


/* Bit 7 : INT_PEND.  */
typedef enum{
    STATUS_REG_1_INT_PEND_MASK                  =   ( 1 << 7 ),         /*!<  INT_PEND Mask                                                                      */
    STATUS_REG_1_INT_PEND_FALSE                 =   ( 0 << 7 ),         /*!<  No interrupt flags are pending in register 0x09 (level)                            */
    STATUS_REG_1_INT_PEND_TRUE                  =   ( 1 << 7 )          /*!<  One or more interrupt flags are pending in register 0x09 (logical OR) (level)      */
} MC3635_status_reg1_int_pend_t;



/**
  * @brief   STATUS REGISTER 2
  *
  *             This register reports the state of the interrupts ('0' means not pending; '1' means pending). A
  *             bit in this register will only be set if the corresponding interrupt enable is set to '1' in (0x17)
  *             Interrupt Control Register.
  */
/* Bit 2 : INT_WAKE.  */
typedef enum{
    STATUS_REG_2_INT_WAKE_MASK                  =   ( 1 << 2 ),         /*!<  INT_WAKE Mask                                                                     */
    STATUS_REG_2_INT_WAKE_FALSE                 =   ( 0 << 2 ),         /*!<  INT_WAKE not triggered                                                            */
    STATUS_REG_2_INT_WAKE_TRUE                  =   ( 1 << 2 )          /*!<  INT_WAKE triggered                                                                */
} MC3635_status_reg2_int_wake_t;


/* Bit 3 : INT_ACQ.  */
typedef enum{
    STATUS_REG_2_INT_ACQ_MASK                   =   ( 1 << 3 ),         /*!<  INT_ACQ Mask                                                                      */
    STATUS_REG_2_INT_ACQ_FALSE                  =   ( 0 << 3 ),         /*!<  INT_ACQ not triggered                                                             */
    STATUS_REG_2_INT_ACQ_TRUE                   =   ( 1 << 3 )          /*!<  INT_ACQ triggered                                                                 */
} MC3635_status_reg2_int_acq_t;


/* Bit 4 : INT_FIFO_EMPTY.  */
typedef enum{
    STATUS_REG_2_INT_FIFO_EMPTY_MASK            =   ( 1 << 4 ),         /*!<  INT_FIFO_EMPTY Mask                                                               */
    STATUS_REG_2_INT_FIFO_EMPTY_FALSE           =   ( 0 << 4 ),         /*!<  INT_FIFO_EMPTY not triggered                                                      */
    STATUS_REG_2_INT_FIFO_EMPTY_TRUE            =   ( 1 << 4 )          /*!<  INT_FIFO_EMPTY triggered                                                          */
} MC3635_status_reg2_int_fifo_empty_t;


/* Bit 5 : INT_FIFO_FULL.  */
typedef enum{
    STATUS_REG_2_INT_FIFO_FULL_MASK             =   ( 1 << 5 ),         /*!<  INT_FIFO_FULL Mask                                                                */
    STATUS_REG_2_INT_FIFO_FULL_FALSE            =   ( 0 << 5 ),         /*!<  INT_FIFO_FULL not triggered                                                       */
    STATUS_REG_2_INT_FIFO_FULL_TRUE             =   ( 1 << 5 )          /*!<  INT_FIFO_FULL triggered                                                           */
} MC3635_status_reg2_int_fifo_full_t;


/* Bit 6 : INT_FIFO_THRESH.  */
typedef enum{
    STATUS_REG_2_INT_FIFO_THRESH_MASK           =   ( 1 << 6 ),         /*!<  INT_FIFO_THRESH Mask                                                              */
    STATUS_REG_2_INT_FIFO_THRESH_FALSE          =   ( 0 << 6 ),         /*!<  INT_FIFO_THRESH not triggered                                                     */
    STATUS_REG_2_INT_FIFO_THRESH_TRUE           =   ( 1 << 6 )          /*!<  INT_FIFO_THRESH triggered                                                         */
} MC3635_status_reg2_int_fifo_thresh_t;


/* Bit 7 : INT_SWAKE.  */
typedef enum{
    STATUS_REG_2_INT_SWAKE_MASK                 =   ( 1 << 7 ),         /*!<  INT_SWAKE Mask                                                                    */
    STATUS_REG_2_INT_SWAKE_FALSE                =   ( 0 << 7 ),         /*!<  INT_SWAKE not triggered                                                           */
    STATUS_REG_2_INT_SWAKE_TRUE                 =   ( 1 << 7 )          /*!<  INT_SWAKE triggered                                                               */
} MC3635_status_reg2_int_swake_t;



/**
  * @brief   FEATURE REGISTER 1
  *
  *             This register is used to select the interface mode as well as the operation style of the FIFO and
  *             interrupt in SWAKE mode.
  */
/* Bit 3 : FREEZE.  */
typedef enum{
    FEATURE_REG_1_FREEZE_MASK                   =   ( 1 << 3 ),         /*!<  FREEZE Mask                                                                                                   */
    FEATURE_REG_1_FREEZE_FIFO_STANDARD_MODE     =   ( 0 << 3 ),         /*!<  FIFO operates in standard mode, does not stop capturing data in SWAKE interrupt (default)                     */
    FEATURE_REG_1_FREEZE_FIFO_STOP_SWAKE        =   ( 1 << 3 )          /*!<  FIFO stops capturing on SWAKE interrupt, software can examine the conditions which generated the SWAKE event  */
} MC3635_feature_reg1_freeze_t;


/* Bit 4 : INTSC_EN.  */
typedef enum{
    FEATURE_REG_1_INTSC_EN_MASK                 =   ( 1 << 4 ),         /*!<  INTSC_EN Mask                                                                                                                                                                                         */
    FEATURE_REG_1_INTSC_EN_DISABLED             =   ( 0 << 4 ),         /*!<  Do not re-arm SNIFF block following a SWAKE event (requires the SNIFF block to be reset by exiting SWAKE mode). (default)                                                                             */
    FEATURE_REG_1_INTSC_EN_ENABLED              =   ( 1 << 4 )          /*!<  Clearing the SWAKE interrupt clears and rearms the SNIFF block for subsequent detections (device may stay in SWAKE mode and continuing processing subsequent SWAKE events once interrupt is cleared)  */
} MC3635_feature_reg1_intsc_en_t;


/* Bit 5 : SPI3_EN.  */
typedef enum{
    FEATURE_REG_1_SPI3_EN_MASK                  =   ( 1 << 5 ),         /*!<  SPI3_EN Mask                                                                          */
    FEATURE_REG_1_SPI3_EN_DISABLED              =   ( 0 << 5 ),         /*!<  SPI interface is 4-wire                                                               */
    FEATURE_REG_1_SPI3_EN_ENABLED               =   ( 1 << 5 )          /*!<  SPI interface is 3-wire (DOUT_A1 is the bidirectional pin)                            */
} MC3635_feature_reg1_spi3_en_t;


/* Bit 6 : I2C_EN.  */
typedef enum{
    FEATURE_REG_1_I2C_EN_MASK                   =   ( 1 << 6 ),         /*!<  I2C_EN Mask                                                                           */
    FEATURE_REG_1_I2C_EN_DISABLED               =   ( 0 << 6 ),         /*!<  Device interface is still defined as it was at power-up but no data will appear in XOUT, YOUT and ZOUT registers if both this bit and SPI_EN are set to 0 (default).  */
    FEATURE_REG_1_I2C_EN_ENABLED                =   ( 1 << 6 )          /*!<  Disables any SPI communications                                                       */
} MC3635_feature_reg1_i2c_en_t;


/* Bit 7 : SPI_EN.  */
typedef enum{
    FEATURE_REG_1_SPI_EN_MASK                   =   ( 1 << 7 ),         /*!<  SPI_EN Mask                                                                           */
    FEATURE_REG_1_SPI_EN_DISABLED               =   ( 0 << 7 ),         /*!<  Device interface is still defined as it was at power-up but no data will appear in XOUT, YOUT and ZOUT registers if both this bit and I2C_EN are set to 0 (default).  */
    FEATURE_REG_1_SPI_EN_ENABLED                =   ( 1 << 7 )          /*!<  Disables any I2C communications                                                       */
} MC3635_feature_reg1_spi_en_t;









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
} MC3635_vector_t;


typedef struct{
    float Xmg_Axis;
    float Ymg_Axis;
    float Zmg_Axis;
} Vector_f;
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
MC3635_status_t  MC3635_Init                          ( I2C_parameters_t myI2Cparameters );
MC3635_status_t  MC3635_Conf                          ( I2C_parameters_t myI2Cparameters, AXDL345_bw_rate_low_power_t LOWPOWER, AXDL345_bw_rate_rate_t RATE,
                                                          MC3635_data_format_int_invert_t INT_INVERT, MC3635_data_format_full_res_t FULLRESOLUTION, MC3635_data_format_justify_t JUSTIFY,
                                                          MC3635_data_format_range_t RANGE );




#ifdef __cplusplus
}
#endif

#endif /* MC3635_H_ */
