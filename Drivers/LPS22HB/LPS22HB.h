/**
 * @brief       LPS22HB.h
 * @details     MEMS nano pressure sensor: 260-1260 hPa absolute digital output barometer.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/June/2019
 * @version     15/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  LPS22HB_ADDRESS_0     =   0b1011100,       /*!<   I2C slave address byte, SDO/SA0 = GND        */
  LPS22HB_ADDRESS_1     =   0b1011101        /*!<   I2C slave address byte, SDO/SA0 = VDD        */
} LPS22HB_addresses_t;



/**
  * @brief   REGISTERS
  */
typedef enum
{
  LPS22HB_REF_P_XL        =   0x08,           /*!<  Reference pressure registers                  */
  LPS22HB_REF_P_L         =   0x09,           /*!<  Reference pressure registers                  */
  LPS22HB_REF_P_H         =   0x0A,           /*!<  Reference pressure registers                  */
  LPS22HB_WHO_AM_I        =   0x0F,           /*!<  Who am I register                             */
  LPS22HB_RES_CONF        =   0x10,           /*!<  Resolution register                           */
  LPS22HB_CTRL_REG1       =   0x20,           /*!<  Control registers                             */
  LPS22HB_CTRL_REG2       =   0x21,           /*!<  Control registers                             */
  LPS22HB_CTRL_REG3       =   0x22,           /*!<  Control registers                             */
  LPS22HB_CTRL_REG4       =   0x23,           /*!<  Control registers                             */
  LPS22HB_INTERRUPT_CFG   =   0x24,           /*!<  Interrupt registers                           */
  LPS22HB_INT_SOURCE      =   0x25,           /*!<  Interrupt registers                           */
  LPS22HB_STATUS_REG      =   0x27,           /*!<  Status register                               */
  LPS22HB_PRESS_OUT_XL    =   0x28,           /*!<  Pressure output register                      */
  LPS22HB_PRESS_OUT_L     =   0x29,           /*!<  Pressure output register                      */
  LPS22HB_PRESS_OUT_H     =   0x2A,           /*!<  Pressure output register                      */
  LPS22HB_TEMP_OUT_L      =   0x2B,           /*!<  Temperature output registers                  */
  LPS22HB_TEMP_OUT_H      =   0x2C,           /*!<  Temperature output registers                  */
  LPS22HB_FIFO_CTRL       =   0x2E,           /*!<  FIFO configure registers                      */
  LPS22HB_FIFO_STATUS     =   0x2F,           /*!<  FIFO configure registers                      */
  LPS22HB_THS_P_L         =   0x30,           /*!<  Pressure threshold registers                  */
  LPS22HB_THS_P_H         =   0x31,           /*!<  Pressure threshold registers                  */
  LPS22HB_RPDS_L          =   0x39,           /*!<  Pressure offset registers                     */
  LPS22HB_RPDS_H          =   0x3A            /*!<  Pressure offset registers                     */
} LPS22HB_registers_t;



/**
  * @brief   REF_P_XL REGISTER. Reference pressure (LSB data) ( Default: 0x00 )
  */
typedef enum
{
    REF_P_XL_MASK         =   0xFF            /*!<  REF_P_XL mask                                 */
} LPS22HB_rep_p_xl_t;


/**
  * @brief   REF_P_L REGISTER. Reference pressure (middle part) ( Default: 0x00 )
  */
typedef enum
{
    REF_P_L_MASK          =   0xFF            /*!<  REF_P_L mask                                  */
} LPS22HB_rep_p_l_t;


/**
  * @brief   REF_P_H REGISTER. Reference pressure (MSB data) ( Default: 0x00 )
  */
typedef enum
{
    REF_P_H_MASK          =   0xFF            /*!<  REF_P_H mask                                  */
} LPS22HB_rep_p_h_t;


/**
  * @brief   WHO_AM_I REGISTER.
  */
typedef enum
{
    WHO_AM_I_MASK         =   0xFF,           /*!<  WHO_AM_I mask                                */
    WHO_AM_I_VALUE        =   0xBD            /*!<  WHO_AM_I: 0xBD                               */
} LPS22HB_who_am_i_t;


/**
  * @brief   RES_CONF REGISTER.
  */
/* AVGT <3:2>
 *    NOTE: Temperature internal average configuration.
 */
typedef enum
{
    RES_CONF_AVGT_MASK    =   ( 0b11 << 2U ),   /*!<  AVGT mask                                    */
    RES_CONF_AVGT_8       =   ( 0b00 << 2U ),   /*!<  AVGT Nr. internal average  8                 */
    RES_CONF_AVGT_16      =   ( 0b01 << 2U ),   /*!<  AVGT Nr. internal average 16                 */
    RES_CONF_AVGT_32      =   ( 0b10 << 2U ),   /*!<  AVGT Nr. internal average 32                 */
    RES_CONF_AVGT_64      =   ( 0b11 << 2U )    /*!<  AVGT Nr. internal average 64     [ Default ] */
} LPS22HB_res_conf_avgt_t;


/* AVGP <1:0>
 *    NOTE: Pressure internal average configuration.
 */
typedef enum
{
    RES_CONF_AVGP_MASK    =   ( 0b11 << 0U ),   /*!<  AVGP mask                                    */
    RES_CONF_AVGP_8       =   ( 0b00 << 0U ),   /*!<  AVGP Nr. internal average   8                */
    RES_CONF_AVGP_32      =   ( 0b01 << 0U ),   /*!<  AVGP Nr. internal average  32                */
    RES_CONF_AVGP_128     =   ( 0b10 << 0U ),   /*!<  AVGP Nr. internal average 128                */
    RES_CONF_AVGP_512     =   ( 0b11 << 0U )    /*!<  AVGP Nr. internal average 512    [ Default ] */
} LPS22HB_res_conf_avgp_t;


/**
  * @brief   CTRL_REG1 REGISTER.
  */
/* PD <7>
 *    NOTE: Power-down control.
 */
typedef enum
{
    CTRL_REG1_PD_MASK             =   ( 1U << 7U ),     /*!<  PD mask                                       */
    CTRL_REG1_PD_POWER_DOWN_MODE  =   ( 0U << 7U ),     /*!<  Power-down mode                   [ Default ] */
    CTRL_REG1_PD_ACTIVE_MODE      =   ( 1U << 7U )      /*!<  Active mode                                   */
} LPS22HB_ctrl_reg1_pd_t;


/* ODR <6:4>
 *    NOTE: Output data rate selection.
 */
typedef enum
{
    CTRL_REG1_ODR_MASK            =   ( 0b111 << 4U ),  /*!<  ODR mask                                      */
    CTRL_REG1_ODR_ONE_SHOT_MODE   =   ( 0b000 << 4U ),  /*!<  One- shot mode enabled            [ Default ] */
    CTRL_REG1_ODR_1_HZ            =   ( 0b001 << 4U ),  /*!<  ODR:  1 HZ                                    */
    CTRL_REG1_ODR_7_HZ            =   ( 0b010 << 4U ),  /*!<  ODR:  7 HZ                                    */
    CTRL_REG1_ODR_12_5_HZ         =   ( 0b011 << 4U ),  /*!<  ODR: 12.5 HZ                                  */
    CTRL_REG1_ODR_25_HZ           =   ( 0b100 << 4U )   /*!<  ODR: 25 HZ                                    */
} LPS22HB_ctrl_reg1_odr_t;


/* DIFF_EN <3>
 *    NOTE: Interrupt generation enable.
 */
typedef enum
{
    CTRL_REG1_DIFF_EN_MASK        =   ( 1U << 3U ),     /*!<  DIFF_EN mask                                  */
    CTRL_REG1_DIFF_EN_DISABLED    =   ( 0U << 3U ),     /*!<  Interrupt generation disabled     [ Default ] */
    CTRL_REG1_DIFF_EN_ENABLED     =   ( 1U << 3U )      /*!<  Interrupt generation enabled                  */
} LPS22HB_ctrl_reg1_diff_en_t;


/* BDU <2>
 *    NOTE: Block data update.
 */
typedef enum
{
    CTRL_REG1_BDU_MASK            =   ( 1U << 2U ),     /*!<  BDU mask                                      */
    CTRL_REG1_BDU_0               =   ( 0U << 2U ),     /*!<  Continuous update                 [ Default ] */
    CTRL_REG1_BDU_1               =   ( 1U << 2U )      /*!<  Not updated until MSB and LSB have been read  */
} LPS22HB_ctrl_reg1_bdu_t;


/* RESET_AZ <1>
 *    NOTE: Reset Autozero function.
 */
typedef enum
{
    CTRL_REG1_RESET_AZ_MASK                     =   ( 1U << 1U ), /*!<  RESET_AZ mask                                 */
    CTRL_REG1_RESET_AZ_NORMAL_MODE              =   ( 0U << 1U ), /*!<  Normal mode                       [ Default ] */
    CTRL_REG1_RESET_AZ_RESET_AUTOZERO_FUNCTION  =   ( 1U << 1U )  /*!<  Reset Autozero function                       */
} LPS22HB_ctrl_reg1_reset_az_t;


/* SIM <0>
 *    NOTE: SPI Serial Interface Mode selection.
 */
typedef enum
{
    CTRL_REG1_SIM_MASK              =   ( 1U << 0U ),   /*!<  SIM mask                                      */
    CTRL_REG1_SIM_4_WIRE_INTERFACE  =   ( 0U << 0U ),   /*!<  4-wire interface                  [ Default ] */
    CTRL_REG1_SIM_3_WIRE_INTERFACE  =   ( 1U << 0U )    /*!<  3-wire interface                              */
} LPS22HB_ctrl_reg1_sim_t;


/**
  * @brief   CTRL_REG2 REGISTER.
  */
/* BOOT <7>
 *    NOTE: Reboot memory content. The bit is self-cleared when the BOOT is completed
 */
typedef enum
{
    CTRL_REG2_BOOT_MASK           =   ( 1U << 7U ),     /*!<  BOOT mask                                     */
    CTRL_REG2_BOOT_NORMAL_MODE    =   ( 0U << 7U ),     /*!<  Normal mode                       [ Default ] */
    CTRL_REG2_BOOT_REBOOT_MODE    =   ( 1U << 7U )      /*!<  Reboot memory content                         */
} LPS22HB_ctrl_reg2_boot_t;


/* FIFO_EN <6>
 *    NOTE: FIFO enable
 */
typedef enum
{
    CTRL_REG2_FIFO_EN_MASK        =   ( 1U << 6U ),     /*!<  FIFO_EN mask                                  */
    CTRL_REG2_FIFO_EN_DISABLED    =   ( 0U << 6U ),     /*!<  Disable                           [ Default ] */
    CTRL_REG2_FIFO_EN_ENABLED     =   ( 1U << 6U )      /*!<  Enabled                                       */
} LPS22HB_ctrl_reg2_fifo_en_t;


/* STOP_ON_FTH <5>
 *    NOTE: Enable the FTH_FIFO bit in FIFO_STATUS (2Fh) for monitoring of FIFO level.
 */
typedef enum
{
    CTRL_REG2_STOP_ON_FTH_MASK      =   ( 1U << 5U ),   /*!<  STOP_ON_FTH mask                              */
    CTRL_REG2_STOP_ON_FTH_DISABLED  =   ( 0U << 5U ),   /*!<  Disable                           [ Default ] */
    CTRL_REG2_STOP_ON_FTH_ENABLED   =   ( 1U << 5U )    /*!<  Enabled                                       */
} LPS22HB_ctrl_reg2_stop_on_fth_t;


/* FIFO_MEAN_DEC <4>
 *    NOTE: Enable to decimate the output pressure to 1Hz with FIFO Mean mode.
 */
typedef enum
{
    CTRL_REG2_FIFO_MEAN_DEC_MASK      =   ( 1U << 4U ),   /*!<  FIFO_MEAN_DEC mask                            */
    CTRL_REG2_FIFO_MEAN_DEC_DISABLED  =   ( 0U << 4U ),   /*!<  Disable                           [ Default ] */
    CTRL_REG2_FIFO_MEAN_DEC_ENABLED   =   ( 1U << 4U )    /*!<  Enabled                                       */
} LPS22HB_ctrl_reg2_fifo_mean_dec_t;


/* I2C_DIS <3>
 *    NOTE: I2C interface enabled
 */
typedef enum
{
    CTRL_REG2_I2C_DIS_MASK        =   ( 1U << 3U ),     /*!<  I2C_DIS mask                                  */
    CTRL_REG2_I2C_DIS_ENABLED     =   ( 0U << 3U ),     /*!<  Enabled                           [ Default ] */
    CTRL_REG2_I2C_DIS_DISABLED    =   ( 1U << 3U )      /*!<  Disabled                                      */
} LPS22HB_ctrl_reg2_i2c_dis_t;


/* SWRESET <2>
 *    NOTE: Software reset. The bit is self-cleared when the reset is completed.
 */
typedef enum
{
    CTRL_REG2_SWRESET_MASK        =   ( 1U << 2U ),     /*!<  SWRESET mask                                  */
    CTRL_REG2_SWRESET_NORMAL_MODE =   ( 0U << 2U ),     /*!<  Normal mode                       [ Default ] */
    CTRL_REG2_SWRESET_SW_RESET    =   ( 1U << 2U )      /*!<  Software reset                                */
} LPS22HB_ctrl_reg2_swreset_t;


/* AUTOZERO <1>
 *    NOTE: Autozero enable.
 */
typedef enum
{
    CTRL_REG2_AUTOZERO_MASK             =   ( 1U << 1U ),     /*!<  AUTOZERO mask                                 */
    CTRL_REG2_AUTOZERO_NORMAL_MODE      =   ( 0U << 1U ),     /*!<  Normal mode                       [ Default ] */
    CTRL_REG2_AUTOZERO_AUTOZERO_ENABLED =   ( 1U << 1U )      /*!<  Autozero enabled                              */
} LPS22HB_ctrl_reg2_autozero_t;


/* ONE_SHOT <0>
 *    NOTE: One shot mode enable.
 */
typedef enum
{
    CTRL_REG2_ONE_SHOT_MASK         =   ( 1U << 0U ),   /*!<  ONE_SHOT mask                                 */
    CTRL_REG2_ONE_SHOTL_IDLE_MODE   =   ( 0U << 0U ),   /*!<  Idle mode                         [ Default ] */
    CTRL_REG2_ONE_SHOT_NEW_DATASET  =   ( 1U << 0U )    /*!<  A new dataset is acquired                     */
} LPS22HB_ctrl_reg2_one_shot_t;


/**
  * @brief   CTRL_REG3 REGISTER
  */
/* INT_H_L <7>
 *    NOTE: Interrupt active high
 */
typedef enum
{
    CTRL_REG3_INT_H_L_MASK          =   ( 1U << 7U ),   /*!<  INT_H_L mask                                 */
    CTRL_REG3_INT_H_L_ACTIVE_HIGH   =   ( 0U << 7U ),   /*!<  active high                      [ Default ] */
    CTRL_REG3_INT_H_L_ACTIVE_LOW    =   ( 1U << 7U )    /*!<  active low                                   */
} LPS22HB_ctrl_reg3_int_h_l_t;


/* PP_OD <6>
 *    NOTE: Push-pull/open drain selection on interrupt pads.
 */
typedef enum
{
    CTRL_REG3_PP_OD_MASK                  =   ( 1U << 6U ), /*!<  PP_OD mask                                  */
    CTRL_REG3_PP_OD_PUSH_PULL             =   ( 0U << 6U ), /*!<  push-pull                       [ Default ] */
    CTRL_REG3_PP_OD_OPEN_DRAIN            =   ( 1U << 6U )  /*!<  open drain                                  */
} LPS22HB_ctrl_reg3_pp_od_t;


/* INT_S2 <1:0>
 *    NOTE: Data signal on INT_DRDY pin control bits.
 */
typedef enum
{
    CTRL_REG3_INT_S2_MASK                 =   ( 0b11 << 0U ), /*!<  INT_S2 mask                                 */
    CTRL_REG3_INT_S2_DATA_SIGNAL          =   ( 0b00 << 0U ), /*!<  Data signal                     [ Default ] */
    CTRL_REG3_INT_S2_PRESSURE_HIGH        =   ( 0b01 << 0U ), /*!<  Pressure high (P_high)                      */
    CTRL_REG3_INT_S2_PRESSURE_LOW         =   ( 0b10 << 0U ), /*!<  Pressure low (P_low)                        */
    CTRL_REG3_INT_S2_PRESSURE_LOW_OR_HIGH =   ( 0b11 << 0U )  /*!<  Pressure low OR high                        */
} LPS22HB_ctrl_reg3_int_s2_t;


/**
  * @brief   CTRL_REG4 REGISTER
  */
/* F_EMPTY <3>
 *    NOTE: FIFO empty flag on INT_DRDY pin
 */
typedef enum
{
    CTRL_REG4_F_EMPTY_MASK          =   ( 1U << 3U ),   /*!<  F_EMPTY mask                                  */
    CTRL_REG4_F_EMPTY_DISABLED      =   ( 0U << 3U ),   /*!<  Disabled                          [ Default ] */
    CTRL_REG4_F_EMPTY_ENABLED       =   ( 1U << 3U )    /*!<  Enabled                                       */
} LPS22HB_ctrl_reg4_f_empty_t;


/* F_FTH <2>
 *    NOTE: FIFO threshold (watermark) status on INT_DRDY pin to indicate that FIFO is filled up to the threshold level
 */
typedef enum
{
    CTRL_REG4_F_FTH_MASK            =   ( 1U << 2U ),   /*!<  F_FTH mask                                    */
    CTRL_REG4_F_FTH_DISABLED        =   ( 0U << 2U ),   /*!<  Disabled                          [ Default ] */
    CTRL_REG4_F_FTH_ENABLED         =   ( 1U << 2U )    /*!<  Enabled                                       */
} LPS22HB_ctrl_reg4_f_fth_t;


/* F_OVR <1>
 *    NOTE: FIFO overrun interrupt on INT_DRDY pin to indicate that FIFO is full in FIFO mode or that an overrun occurred in Stream mode
 */
typedef enum
{
    CTRL_REG4_F_OVR_MASK            =   ( 1U << 1U ),   /*!<  F_OVR mask                                    */
    CTRL_REG4_F_OVR_DISABLED        =   ( 0U << 1U ),   /*!<  Disabled                          [ Default ] */
    CTRL_REG4_F_OVR_ENABLED         =   ( 1U << 1U )    /*!<  Enabled                                       */
} LPS22HB_ctrl_reg4_f_ovr_t;


/* DRDY <0>
 *    NOTE: Data-ready signal on INT_DRDY pin
 */
typedef enum
{
    CTRL_REG4_DRDY_MASK             =   ( 1U << 0U ),   /*!<  DRDY mask                                     */
    CTRL_REG4_DRDY_DISABLED         =   ( 0U << 0U ),   /*!<  Disabled                          [ Default ] */
    CTRL_REG4_DRDY_ENABLED          =   ( 1U << 0U )    /*!<  Enabled                                       */
} LPS22HB_ctrl_reg4_drdy_t;


/**
  * @brief   INTERRUPT_CFG REGISTER
  */
/* LIR <2>
 *    NOTE: Latch interrupt request to the INT_SOURCE (25h) register
 */
typedef enum
{
    INTERRUPT_CFG_LIR_MASK          =   ( 1U << 2U ),   /*!<  LIR mask                                      */
    INTERRUPT_CFG_LIR_NOT_LATCHED   =   ( 0U << 2U ),   /*!<  Interrupt request not latched     [ Default ] */
    INTERRUPT_CFG_LIR_LATCHED       =   ( 1U << 2U )    /*!<  Interrupt request latched                     */
} LPS22HB_interrupt_cfg_lir_t;


/* PL_E <1>
 *    NOTE: Enable interrupt generation on differential pressure low event
 */
typedef enum
{
    INTERRUPT_CFG_PL_E_MASK         =   ( 1U << 1U ),   /*!<  PL_E mask                                     */
    INTERRUPT_CFG_PL_E_DISABLED     =   ( 0U << 1U ),   /*!<  Disable interrupt request         [ Default ] */
    INTERRUPT_CFG_PL_E_ENABLED      =   ( 1U << 1U )    /*!<  Enable interrupt request on measured differential pressure value lower than preset threshold      */
} LPS22HB_interrupt_cfg_pl_e_t;


/* PH_E <0>
 *    NOTE: Enable interrupt generation on differential pressure high event
 */
typedef enum
{
    INTERRUPT_CFG_PH_E_MASK         =   ( 1U << 0U ),   /*!<  PH_E mask                                     */
    INTERRUPT_CFG_PH_E_DISABLED     =   ( 0U << 0U ),   /*!<  Disable interrupt request         [ Default ] */
    INTERRUPT_CFG_PH_E_ENABLED      =   ( 1U << 0U )    /*!<  enable interrupt request on measured differential pressure value higher than preset threshold      */
} LPS22HB_interrupt_cfg_ph_e_t;


/**
  * @brief   INT_SOURCE REGISTER ( INT_SOURCE register is cleared by reading it )
  */
/* IA <2>
 *    NOTE: Interrupt active
 */
typedef enum
{
    INT_SOURCE_IA_MASK                    =   ( 1U << 2U ),   /*!<  IA mask                                       */
    INT_SOURCE_IA_NO_INTERRUPT_GENERATED  =   ( 0U << 2U ),   /*!<  No interrupt has been generated               */
    INT_SOURCE_IA_INTERRUPT_GENERATED     =   ( 1U << 2U )    /*!<  One/more interrupt events have been generated */
} LPS22HB_int_source_ia_t;


/* PL <1>
 *    NOTE: Differential pressure Low
 */
typedef enum
{ 
    INT_SOURCE_PL_MASK                    =   ( 1U << 1U ),   /*!<  PL mask                                       */
    INT_SOURCE_PL_NO_INTERRUPT_GENERATED  =   ( 0U << 1U ),   /*!<  No interrupt has been generated               */
    INT_SOURCE_PL_EVENT_OCCURRED          =   ( 1U << 1U )    /*!<  Low differential pressure event has occurred  */
} LPS22HB_int_source_pl_t;


/* PH <0>
 *    NOTE: Differential pressure High
 */
typedef enum
{ 
    INT_SOURCE_PH_MASK                    =   ( 1U << 0U ),   /*!<  PH mask                                       */
    INT_SOURCE_PH_NO_INTERRUPT_GENERATED  =   ( 0U << 0U ),   /*!<  No interrupt has been generated               */
    INT_SOURCE_PH_EVENT_OCCURRED          =   ( 1U << 0U )    /*!<  High differential pressure event has occurred */
} LPS22HB_int_source_ph_t;


/**
  * @brief   STATUS_REG REGISTER
  */
/* P_OR <5>
 *    NOTE: Pressure data overrun
 */
typedef enum
{
    STATUS_REG_P_OR_MASK            =   ( 1U << 5U ),   /*!<  P_OR mask                                               */
    STATUS_REG_P_OR_NO_DATA         =   ( 0U << 5U ),   /*!<  no overrun has occurred                                 */
    STATUS_REG_P_OR_NEW_DATA        =   ( 1U << 5U )    /*!<  new data for pressure has overwritten the previous one  */
} LPS22HB_status_reg_p_or_t;


/* T_OR <4>
 *    NOTE: Temperature data overrun
 */
typedef enum
{
    STATUS_REG_T_OR_MASK            =   ( 1U << 4U ),   /*!<  T_OR mask                                                 */
    STATUS_REG_T_OR_NO_DATA         =   ( 0U << 4U ),   /*!<  no overrun has occurred                                   */
    STATUS_REG_T_OR_NEW_DATA        =   ( 1U << 4U )    /*!<  new data for temperature has overwritten the previous one */
} LPS22HB_status_reg_t_or_t;


/* P_DA <1>
 *    NOTE: Pressure data available
 */
typedef enum
{
    STATUS_REG_P_DA_MASK            =   ( 1U << 1U ),   /*!<  P_DA mask                                               */
    STATUS_REG_P_DA_NO_AVAILABLE    =   ( 0U << 1U ),   /*!<  new data for pressure is not yet available              */
    STATUS_REG_P_DA_NEW_DATA        =   ( 1U << 1U )    /*!<  new data for pressure is available                      */
} LPS22HB_status_reg_p_da_t;


/* T_DA <0>
 *    NOTE: Temperature data available
 */
typedef enum
{
    STATUS_REG_T_DA_MASK            =   ( 1U << 0U ),   /*!<  T_DA mask                                               */
    STATUS_REG_T_DA_NO_AVAILABLE    =   ( 0U << 0U ),   /*!<  new data for temperature is not yet available           */
    STATUS_REG_T_DA_NEW_DATA        =   ( 1U << 0U )    /*!<  new data for temperature is available                   */
} LPS22HB_status_reg_t_da_t;


/**
  * @brief   FIFO_CTRL REGISTER
  */
/* F_MODE <7:5>
 *    NOTE: FIFO mode selection
 */
typedef enum
{
    FIFO_CTRL_F_MODE_MASK                   =   ( 0b111 << 5U ),  /*!<  F_MODE mask                                           */
    FIFO_CTRL_F_MODE_BYPASS_MODE            =   ( 0b000 << 5U ),  /*!<  Bypass mode                               [ Default ] */
    FIFO_CTRL_F_MODE_FIFO_MODE              =   ( 0b001 << 5U ),  /*!<  FIDO mode                                             */
    FIFO_CTRL_F_MODE_STREAM_MOD             =   ( 0b010 << 5U ),  /*!<  Stream mode                                           */
    FIFO_CTRL_F_MODE_STREAM_TO_FIFO_MODE    =   ( 0b011 << 5U ),  /*!<  Stream-to-FIDO mode                                   */
    FIFO_CTRL_F_MODE_BYPASS_TO_STREAM_MODE  =   ( 0b100 << 5U ),  /*!<  Bypass-to-Stream mode                                 */
    FIFO_CTRL_F_MODE_FIFO_MEAN_MODE         =   ( 0b110 << 5U ),  /*!<  FIDO mean mode                                        */
    FIFO_CTRL_F_MODE_BYPASS_TO_FIFO_MODE    =   ( 0b111 << 5U )   /*!<  Bypass-to-FIDO mode                                   */
} LPS22HB_fifo_ctrl_f_mode_t;


/* WTM_POINT <4:0>
 *    NOTE: FIFO threshold (watermark) level selection
 */
typedef enum
{
    FIFO_CTRL_WTM_POINT_MASK                =   ( 0b11111 << 0U ),  /*!<  WTM_POINT mask                                        */
    FIFO_CTRL_WTM_POINT_2_SAMPLE_MOV_AVG    =   ( 0b00001 << 0U ),  /*!<  2-sample moving average                   [ Default ] */
    FIFO_CTRL_WTM_POINT_4_SAMPLE_MOV_AVG    =   ( 0b00011 << 0U ),  /*!<  4-sample moving average                               */
    FIFO_CTRL_WTM_POINT_8_SAMPLE_MOV_AVG    =   ( 0b00111 << 0U ),  /*!<  8-sample moving average                               */
    FIFO_CTRL_WTM_POINT_16_SAMPLE_MOV_AVG   =   ( 0b01111 << 0U ),  /*!<  16-sample moving average                              */
    FIFO_CTRL_WTM_POINT_32_SAMPLE_MOV_AVG   =   ( 0b11111 << 0U )   /*!<  32-sample moving average                              */
} LPS22HB_fifo_ctrl_wtm_point_t;


/**
  * @brief   FIFO_STATUS REGISTER
  */
/* FTH_FIFO <7>
 *    NOTE: FIFO threshold status
 */
typedef enum
{
    FIFO_STATUS_FTH_FIFO_MASK       =   ( 1U << 7U ),   /*!<  FTH_FIFO mask                                           */
    FIFO_STATUS_FTH_FIFO_0          =   ( 0U << 7U ),   /*!<  FIFO filling is lower than FTH level                    */
    FIFO_STATUS_FTH_FIFO_1          =   ( 1U << 7U )    /*!<  FIFO filling is equal or higher than FTH level          */
} LPS22HB_fifo_status_fth_fifo_t;


/* OVR <6>
 *    NOTE: Overrun bit status
 */
typedef enum
{
    FIFO_STATUS_OVR_MASK            =   ( 1U << 6U ),   /*!<  OVR mask                                                */
    FIFO_STATUS_OVR_FIFO_NOT_FULL   =   ( 0U << 6U ),   /*!<  FIFO not full                                           */
    FIFO_STATUS_OVR_FIFO_FULL       =   ( 1U << 6U )    /*!<  FIFO is full and at least one sample in the FIFO has been overwritten */
} LPS22HB_fifo_status_ovr_t;


/* EMPTY_FIFO <5>
 *    NOTE: Empty FIFO bit status
 */
typedef enum
{
    FIFO_STATUS_EMPTY_FIFO_MASK       =   ( 1U << 5U ),   /*!<  EMPTY_FIFO mask                                       */
    FIFO_STATUS_EMPTY_FIFO_NOT_EMPTY  =   ( 0U << 5U ),   /*!<  FIFO not empty                                        */
    FIFO_STATUS_EMPTY_FIFO_EMPTY      =   ( 1U << 5U )    /*!<  FIFO empty                                            */
} LPS22HB_fifo_status_empty_fifo_t;


/* FSS <4:0>
 *    NOTE: FIFO stored data level
 */
typedef enum
{
    FIFO_STATUS_FSS_MASK              =   ( 0b11111 << 0U ) /*!<  FSS mask                                              */
} LPS22HB_fifo_status_fss_t;




#ifndef LPS22HB_VECTOR_STRUCT_H
#define LPS22HB_VECTOR_STRUCT_H
typedef struct
{
    /* Output registers  */
    int32_t   rawReferencePressure;         /*!<  Raw reference pressure        */
    int32_t   rawPressure;                  /*!<  Raw pressure                  */
    int16_t   rawTemperature;               /*!<  Raw temperature               */

    float     pressure;                     /*!<  Pressure in mbar              */
    float     temperature;                  /*!<  Temperature in Celsius degree */
    
    /* Resolution  */
    LPS22HB_res_conf_avgt_t avgt;           /*!<  Temperature resolution        */
    LPS22HB_res_conf_avgp_t avgp;           /*!<  Pressure resolution           */
    
    /* Configuration  */
    LPS22HB_ctrl_reg1_odr_t      odr;       /*!<  Output data rate selection    */
    LPS22HB_ctrl_reg1_reset_az_t reset_az;  /*!<  Reset autozero function       */
    LPS22HB_ctrl_reg2_boot_t     boot;      /*!<  Reboot memory content         */
    LPS22HB_ctrl_reg2_fifo_en_t  fifo_en;   /*!<  FIFO enable                   */
    LPS22HB_ctrl_reg2_swreset_t  swreset;   /*!<  Software reset                */
    LPS22HB_ctrl_reg2_autozero_t autozero;  /*!<  Autozero enable               */
    LPS22HB_ctrl_reg2_one_shot_t one_shot;  /*!<  One-shot                      */
    
    /* INT_DRDY behaviour   */
    LPS22HB_ctrl_reg4_f_empty_t  f_empty;   /*!<  FIFO empty flag on INT_DRDY pin                   */
    LPS22HB_ctrl_reg4_f_fth_t    f_fth;     /*!<  FIFO threshold (watermark) status on INT_DRDY pin */
    LPS22HB_ctrl_reg4_f_ovr_t    f_ovr;     /*!<  FIFO overrun interrupt on INT_DRDY pin            */
    LPS22HB_ctrl_reg4_drdy_t     drdy;      /*!<  Data-ready signal on INT_DRDY pin                 */

    /* Interrupt configuration   */
    LPS22HB_interrupt_cfg_lir_t  lir;       /*!<  Latch interrupt request                                         */
    LPS22HB_interrupt_cfg_pl_e_t pl_e;      /*!<  Enable interrupt generation on differential pressure low event  */
    LPS22HB_interrupt_cfg_ph_e_t ph_e;      /*!<  Enable interrupt generation on differential pressure high event */
    
    /* Interrupt source  */
    uint8_t                      int_source;  /*!<  Interrupt source            */
    
    /* Status register  */
    uint8_t                      status_reg;  /*!<  Status register             */

    /* FIFO control  */
    LPS22HB_fifo_ctrl_f_mode_t    f_mode;     /*!<  FIFO mode selection                         */
    LPS22HB_fifo_ctrl_wtm_point_t wtm_point;  /*!<  FIFO threshold (watermark) level selection  */

    /* FIFO status   */
    uint8_t                       FIFOstatus; /*!<  FIFO status register        */
    
    /* Pressure threshold  */
    uint16_t                      ths_p;      /*!<  Threshold value for pressure interrupt generation */

    /* Pressure offset  */
    uint16_t                      rpds;       /*!<  Pressure offset             */

    /* Device identification   */
    uint8_t                       deviceID;   /*!<  Device ID                   */
} LPS22HB_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    LPS22HB_SUCCESS     =       0,
    LPS22HB_FAILURE     =       1
} LPS22HB_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
LPS22HB_status_t LPS22HB_Init                     ( I2C_parameters_t myI2Cparameters                                        );

/** It gets raw reference pressure.
  */
LPS22HB_status_t LPS22HB_GetReferencePressure     ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myREFL                );

/** It sets raw reference pressure.
  */
LPS22HB_status_t LPS22HB_SetReferencePressure     ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myREFL                 );

/** It gets the device ID.
  */
LPS22HB_status_t LPS22HB_GetDeviceID              ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myID                  );

/** It sets temperature resolution.
  */
LPS22HB_status_t LPS22HB_SetTemperatureResolution ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myAVGT                 );

/** It gets temperature resolution.
  */
LPS22HB_status_t LPS22HB_GetTemperatureResolution ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myAVGT                );

/** It sets pressure resolution.
  */
LPS22HB_status_t LPS22HB_SetPressureResolution    ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myAVGP                 );

/** It gets pressure resolution.
  */
LPS22HB_status_t LPS22HB_GetPressureResolution    ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myAVGP                );

/** It sets the power mode.
  */
LPS22HB_status_t LPS22HB_SetPowerMode             ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_pd_t myPD           );

/** It sets the output data rate.
  */
LPS22HB_status_t LPS22HB_SetOutputDataRate        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myODR                  );

/** It gets the output data rate.
  */
LPS22HB_status_t LPS22HB_GetOutputDataRate        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myODR                 );

/** It sets the interrupt generation enable.
  */
LPS22HB_status_t LPS22HB_SetInterruptGeneration   ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_diff_en_t myDIFF_EN );

/** It sets the block data update.
  */
LPS22HB_status_t LPS22HB_SetBlockDataUpdate       ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_bdu_t myBDU         );

/** It sets the reset autozero function.
  */
LPS22HB_status_t LPS22HB_SetResetAutozero         ( I2C_parameters_t myI2Cparameters                                        );

/** It gets the reset autozero function.
  */
LPS22HB_status_t LPS22HB_GetResetAutozero         ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRESET_AZ            );

/** It sets the reboot memory content.
  */
LPS22HB_status_t LPS22HB_SetRebootMemoryContent   ( I2C_parameters_t myI2Cparameters                                        );

/** It gets the reboot memory content.
  */
LPS22HB_status_t LPS22HB_GetRebootMemoryContent   ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myBOOT                );

/** It sets the FIFO enable/disable.
  */
LPS22HB_status_t LPS22HB_SetFIFOEnable            ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFO_EN              );

/** It gets the FIFO enable/disable.
  */
LPS22HB_status_t LPS22HB_GetFIFOEnable            ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFO_EN             );

/** It enables/disables the decimate the output pressure to 1Hz with FIFO Mean mode.
  */
LPS22HB_status_t LPS22HB_SetFIFOMeanDec           ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg2_fifo_mean_dec_t myFIFO_MEAN_DEC );

/** It sets the software reset.
  */
LPS22HB_status_t LPS22HB_SetSoftwareReset         ( I2C_parameters_t myI2Cparameters                                        );

/** It gets the software reset flag value.
  */
LPS22HB_status_t LPS22HB_GetSoftwareReset         ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* mySWRESET             );

/** It sets the autozero enable.
  */
LPS22HB_status_t LPS22HB_SetAutozero              ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myAUTOZERO             );

/** It gets the autozero enable value.
  */
LPS22HB_status_t LPS22HB_GetAutozero              ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myAUTOZERO            );

/** It sets the one-shot mode.
  */
LPS22HB_status_t LPS22HB_SetOneShot               ( I2C_parameters_t myI2Cparameters                                        );

/** It gets the one-shot mode flag.
  */
LPS22HB_status_t LPS22HB_GetOneShot               ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myONE_SHOT            );

/** It sets the interrupt active mode.
  */
LPS22HB_status_t LPS22HB_SetInterruptActiveMode   ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg3_int_h_l_t myINT_H_L );

/** It sets the Push-pull/open drain selection on interrupt pads.
  */
LPS22HB_status_t LPS22HB_SetDrainSelectionMode    ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg3_pp_od_t myPP_OD     );

/** It sets the Data signal on INT_DRDY pin control bits.
  */
LPS22HB_status_t LPS22HB_SetDataSignalOnPin       ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg3_int_s2_t myINT_S    );

/** It sets the INT_DRDY behaviour.
  */
LPS22HB_status_t LPS22HB_SetINT_DRDY_Behaviour    ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myIntConfig            );

/** It gets the INT_DRDY behaviour.
  */
LPS22HB_status_t LPS22HB_GetINT_DRDY_Behaviour    ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myIntConfig           );

/** It sets the interrupt configuration register.
  */
LPS22HB_status_t LPS22HB_SetInterruptConfiguration ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myIntConfig           );

/** It gets the interrupt configuration register.
  */
LPS22HB_status_t LPS22HB_GetInterruptConfiguration ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myIntConfig          );
 
/** It reads the interrupt source register.
  */
LPS22HB_status_t LPS22HB_GetInterruptSource       ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myIntSource           );

/** It reads the status register.
  */
LPS22HB_status_t LPS22HB_GetStatusRegister        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myStatusRegister      );

/** It gets the raw pressure value.
  */
LPS22HB_status_t LPS22HB_GetRawPressure           ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRawPressure         );

/** It gets the raw temperature value.
  */
LPS22HB_status_t LPS22HB_GetRawTemperature        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRawTemperature      );

/** It gets the FIFO mode selection.
  */
LPS22HB_status_t LPS22HB_GetFIFO_Mode             ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOmode            );

/** It sets the FIFO mode selection.
  */
LPS22HB_status_t LPS22HB_SetFIFO_Mode             ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFOmode             );

/** It gets the FIFO threshold (watermark) level selection.
  */
LPS22HB_status_t LPS22HB_GetFIFO_Threshold        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOthreshold       );

/** It sets the FIFO threshold (watermark) level selection.
  */
LPS22HB_status_t LPS22HB_SetFIFO_Threshold        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFOthreshold        );

/** It reads the FIFO status register.
  */
LPS22HB_status_t LPS22HB_GetFIFO_Status           ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOstatus          );

/** It sets the FIFO threshold value.
  */
LPS22HB_status_t LPS22HB_SetFIFO_ThresholdValue   ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFOthresholdValue   );

/** It gets the FIFO threshold value.
  */
LPS22HB_status_t LPS22HB_GetFIFO_ThresholdValue   ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOthresholdValue  );

/** It sets the Pressure offset value.
  */
LPS22HB_status_t LPS22HB_SetPressureOffset        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myPressureOffset       );

/** It gets the Pressure offset value.
  */
LPS22HB_status_t LPS22HB_GetPressureOffset        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myPressureOffset      );

/** It gets the current pressure in mbar.
  */
LPS22HB_status_t LPS22HB_GetPressure              ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myPressure            );

/** It gets the current temperature in Celsius degrees.
  */
LPS22HB_status_t LPS22HB_GetTemperature           ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myTemperature         );
