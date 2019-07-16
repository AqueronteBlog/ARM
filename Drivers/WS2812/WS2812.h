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
  LPS22HB_INTERRUPT_CFG   =   0x0B,           /*!<  Interrupt registers                           */
  LPS22HB_THS_P_L         =   0x0C,           /*!<  Pressure threshold registers                  */
  LPS22HB_THS_P_H         =   0x0D,           /*!<  Pressure threshold registers                  */
  LPS22HB_WHO_AM_I        =   0x0F,           /*!<  Who am I register                             */
  LPS22HB_CTRL_REG1       =   0x10,           /*!<  Control registers                             */
  LPS22HB_CTRL_REG2       =   0x11,           /*!<  Control registers                             */
  LPS22HB_CTRL_REG3       =   0x12,           /*!<  Control registers                             */
  LPS22HB_FIFO_CTRL       =   0x14,           /*!<  FIFO configure registers                      */
  LPS22HB_REF_P_XL        =   0x15,           /*!<  Reference pressure registers                  */
  LPS22HB_REF_P_L         =   0x16,           /*!<  Reference pressure registers                  */
  LPS22HB_REF_P_H         =   0x17,           /*!<  Reference pressure registers                  */
  LPS22HB_RPDS_L          =   0x18,           /*!<  Pressure offset registers                     */
  LPS22HB_RPDS_H          =   0x18,           /*!<  Pressure offset registers                     */
  LPS22HB_RES_CONF        =   0x1A,           /*!<  Resolution register                           */
  LPS22HB_INT_SOURCE      =   0x25,           /*!<  Interrupt registers                           */
  LPS22HB_FIFO_STATUS     =   0x26,           /*!<  FIFO configure registers                      */
  LPS22HB_STATUS          =   0x27,           /*!<  Status register                               */
  LPS22HB_PRESS_OUT_XL    =   0x28,           /*!<  Pressure output register                      */
  LPS22HB_PRESS_OUT_L     =   0x29,           /*!<  Pressure output register                      */
  LPS22HB_PRESS_OUT_H     =   0x2A,           /*!<  Pressure output register                      */
  LPS22HB_TEMP_OUT_L      =   0x2B,           /*!<  Temperature output registers                  */
  LPS22HB_TEMP_OUT_H      =   0x2C,           /*!<  Temperature output registers                  */
  LPS22HB_LPFP_RES        =   0x33            /*!<  Filter reset register                         */
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
    WHO_AM_I_VALUE        =   0xB1            /*!<  WHO_AM_I: 0xB1                               */
} LPS22HB_who_am_i_t;


/**
  * @brief   RES_CONF REGISTER.
  */
/* LC_EN <0>
 *    NOTE: Low current mode enable.
 */
typedef enum
{
    RES_CONF_LC_EN_MASK             =   ( 1U << 0U ),   /*!<  LC_EN mask                                   */
    RES_CONF_LC_EN_NORMAL_MODE      =   ( 0U << 0U ),   /*!<  Normal mode (low-noise mode)     [ Default ] */
    RES_CONF_LC_EN_LOW_CURRENT_MODE =   ( 1U << 0U )    /*!<  Low-current mode                             */
} LPS22HB_res_conf_lc_en_t;


/**
  * @brief   CTRL_REG1 REGISTER.
  */
/* ODR <6:4>
 *    NOTE: Output data rate selection.
 */
typedef enum
{
    CTRL_REG1_ODR_MASK            =   ( 0b111 << 4U ),  /*!<  ODR mask                                      */
    CTRL_REG1_ODR_ONE_SHOT_MODE   =   ( 0b000 << 4U ),  /*!<  One- shot mode enabled            [ Default ] */
    CTRL_REG1_ODR_1_HZ            =   ( 0b001 << 4U ),  /*!<  ODR:  1 HZ                                    */
    CTRL_REG1_ODR_10_HZ           =   ( 0b010 << 4U ),  /*!<  ODR: 10 HZ                                    */
    CTRL_REG1_ODR_25_HZ           =   ( 0b011 << 4U ),  /*!<  ODR: 25 HZ                                    */
    CTRL_REG1_ODR_50_HZ           =   ( 0b100 << 4U ),  /*!<  ODR: 50 HZ                                    */
    CTRL_REG1_ODR_75_HZ           =   ( 0b101 << 4U )   /*!<  ODR: 75 HZ                                    */
} LPS22HB_ctrl_reg1_odr_t;


/* EN_LPFP <3>
 *    NOTE: Enable low-pass filter on pressure data when Continuous mode is used.
 */
typedef enum
{
    CTRL_REG1_EN_LPFP_MASK        =   ( 1U << 3U ),     /*!<  EN_LPFP mask                                  */
    CTRL_REG1_EN_LPFP_DISABLED    =   ( 0U << 3U ),     /*!<  Low-pass filter disabled          [ Default ] */
    CTRL_REG1_EN_LPFP_ENABLED     =   ( 1U << 3U )      /*!<  Low-pass filter enabled                       */
} LPS22HB_ctrl_reg1_en_lpfp_t;


/* LPFP_CFG <2>
 *    NOTE: Low-pass configuration register.
 */
typedef enum
{
    CTRL_REG1_LPFP_CFG_MASK       =   ( 1U << 2U ),     /*!<  LPFP_CFG mask                                 */
    CTRL_REG1_LPFP_CFG_ODR_DIV_9  =   ( 0U << 2U ),     /*!<  ODR/9                             [ Default ] */
    CTRL_REG1_LPFP_CFG_ODR_DIV_20 =   ( 1U << 2U )      /*!<  ODR/20                                        */
} LPS22HB_ctrl_reg1_lpfp_cfg_t;


/* BDU <1>
 *    NOTE: Block data update.
 */
typedef enum
{
    CTRL_REG1_BDU_MASK            =   ( 1U << 1U ),     /*!<  BDU mask                                      */
    CTRL_REG1_BDU_0               =   ( 0U << 1U ),     /*!<  Continuous update                 [ Default ] */
    CTRL_REG1_BDU_1               =   ( 1U << 1U )      /*!<  Not updated until MSB and LSB have been read  */
} LPS22HB_ctrl_reg1_bdu_t;


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


/* IF_ADD_INC <4>
 *    NOTE: Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI).
 */
typedef enum
{
    CTRL_REG2_IF_ADD_INC_MASK         =   ( 1U << 4U ),   /*!<  IF_ADD_INC mask                               */
    CTRL_REG2_IF_ADD_INC_DISABLED     =   ( 0U << 4U ),   /*!<  Disable                                       */
    CTRL_REG2_IF_ADD_INC_ENABLED      =   ( 1U << 4U )    /*!<  Enabled                           [ Default ] */
} LPS22HB_ctrl_reg2_if_add_inc_t;


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


/* F_FSS5 <5>
 *    NOTE: FIFO full flag on INT_DRDY pin.
 */
typedef enum
{
    CTRL_REG3_F_FSS5_MASK                 =   ( 1U << 5U ), /*!<  F_FSS5 mask                                 */
    CTRL_REG3_F_FSS5_DISABLE              =   ( 0U << 5U ), /*!<  Disable                         [ Default ] */
    CTRL_REG3_F_FSS5_ENABLE               =   ( 1U << 5U )  /*!<  Enable                                      */
} LPS22HB_ctrl_reg3_f_fss5_t;


/* F_FTH <4>
 *    NOTE: FIFO watermark status on INT_DRDY pin.
 */
typedef enum
{
    CTRL_REG3_F_FTH_MASK                  =   ( 1U << 4U ), /*!<  F_FTH mask                                  */
    CTRL_REG3_F_FTH_DISABLE               =   ( 0U << 4U ), /*!<  Disable                         [ Default ] */
    CTRL_REG3_F_FTH_ENABLE                =   ( 1U << 4U )  /*!<  Enable                                      */
} LPS22HB_ctrl_reg3_f_fth_t;


/* F_OVR <3>
 *    NOTE: FIFO overrun interrupt on INT_DRDY pin.
 */
typedef enum
{
    CTRL_REG3_F_OVR_MASK                  =   ( 1U << 3U ), /*!<  F_OVR mask                                  */
    CTRL_REG3_F_OVR_DISABLE               =   ( 0U << 3U ), /*!<  Disable                         [ Default ] */
    CTRL_REG3_F_OVR_ENABLE                =   ( 1U << 3U )  /*!<  Enable                                      */
} LPS22HB_ctrl_reg3_f_ovr_t;


/* DRDY <2>
 *    NOTE: Data-ready signal on INT_DRDY pin.
 */
typedef enum
{
    CTRL_REG3_DRDY_MASK                   =   ( 1U << 2U ), /*!<  DRDY mask                                   */
    CTRL_REG3_DRDY_DISABLE                =   ( 0U << 2U ), /*!<  Disable                         [ Default ] */
    CTRL_REG3_DRDY_ENABLE                 =   ( 1U << 2U )  /*!<  Enable                                      */
} LPS22HB_ctrl_reg3_drdy_t;


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
  * @brief   INTERRUPT_CFG REGISTER
  */
/* AUTORIFP <7>
 *    NOTE: Enable AUTORIFP: function
 */
typedef enum
{
    INTERRUPT_CFG_AUTORIFP_MASK     =   ( 1U << 7U ),   /*!<  AUTORIFP mask                                 */
    INTERRUPT_CFG_AUTORIFP_NORMAL   =   ( 0U << 7U ),   /*!<  normal mode                       [ Default ] */
    INTERRUPT_CFG_AUTORIFP_ENABLED  =   ( 1U << 7U )    /*!<  AutoRifP enabled                              */
} LPS22HB_interrupt_cfg_autorifp_t;


/* RESET_ARP <6>
 *    NOTE: Enable Autozero function
 */
typedef enum
{
    INTERRUPT_CFG_RESET_ARP_MASK    =   ( 1U << 6U ),   /*!<  RESET_ARP mask                                */
    INTERRUPT_CFG_RESET_ARP_NORMAL  =   ( 0U << 6U ),   /*!<  normal mode                       [ Default ] */
    INTERRUPT_CFG_RESET_ARP_ENABLED =   ( 1U << 6U )    /*!<  reset AutoRifP function                       */
} LPS22HB_interrupt_cfg_reset_arp_t;


/* AUTOZERO <5>
 *    NOTE: Enable Autozero function
 */
typedef enum
{
    INTERRUPT_CFG_AUTOZERO_MASK     =   ( 1U << 5U ),   /*!<  AUTOZERO mask                                 */
    INTERRUPT_CFG_AUTOZERO_NORMAL   =   ( 0U << 5U ),   /*!<  normal mode                       [ Default ] */
    INTERRUPT_CFG_AUTOZERO_ENABLED  =   ( 1U << 5U )    /*!<  Autozero enabled                              */
} LPS22HB_interrupt_cfg_autozero_t;


/* RESET_AZ <4>
 *    NOTE: Reset Autozero function
 */
typedef enum
{
    INTERRUPT_CFG_RESET_AZ_MASK     =   ( 1U << 4U ),   /*!<  RESET_AZ mask                                 */
    INTERRUPT_CFG_RESET_AZ_NORMAL   =   ( 0U << 4U ),   /*!<  normal mode                       [ Default ] */
    INTERRUPT_CFG_RESET_AZ_ENABLED  =   ( 1U << 4U )    /*!<  reset Autozero function                       */
} LPS22HB_interrupt_cfg_reset_az_t;


/* DIFF_EN <3>
 *    NOTE: Enable interrupt generation
 */
typedef enum
{
    INTERRUPT_CFG_DIFF_EN_MASK      =   ( 1U << 3U ),   /*!<  DIFF_EN mask                                 */
    INTERRUPT_CFG_DIFF_EN_DISABLED  =   ( 0U << 3U ),   /*!<  interrupt generation disabled    [ Default ] */
    INTERRUPT_CFG_DIFF_EN_ENABLED   =   ( 1U << 3U )    /*!<  interrupt generation enabled                 */
} LPS22HB_interrupt_cfg_diff_en_t;


/* LIR <2>
 *    NOTE: Latch interrupt request to the INT_SOURCE (25h) register.
 */
typedef enum
{
    INTERRUPT_CFG_LIR_MASK          =   ( 1U << 2U ),   /*!<  LIR mask                                      */
    INTERRUPT_CFG_LIR_NOT_LATCHED   =   ( 0U << 2U ),   /*!<  Interrupt request not latched     [ Default ] */
    INTERRUPT_CFG_LIR_LATCHED       =   ( 1U << 2U )    /*!<  Interrupt request latched                     */
} LPS22HB_interrupt_cfg_lir_t;


/* PLE <1>
 *    NOTE: Enable interrupt generation on differential pressure low event
 */
typedef enum
{
    INTERRUPT_CFG_PLE_MASK          =   ( 1U << 1U ),   /*!<  PLE mask                                      */
    INTERRUPT_CFG_PLE_DISABLED      =   ( 0U << 1U ),   /*!<  Disable interrupt request         [ Default ] */
    INTERRUPT_CFG_PLE_ENABLED       =   ( 1U << 1U )    /*!<  Enable interrupt request on measured differential pressure value lower than preset threshold      */
} LPS22HB_interrupt_cfg_ple_t;


/* PHE <0>
 *    NOTE: Enable interrupt generation on differential pressure high event
 */
typedef enum
{
    INTERRUPT_CFG_PHE_MASK          =   ( 1U << 0U ),   /*!<  PHE mask                                      */
    INTERRUPT_CFG_PHE_DISABLED      =   ( 0U << 0U ),   /*!<  Disable interrupt request         [ Default ] */
    INTERRUPT_CFG_PHE_ENABLED       =   ( 1U << 0U )    /*!<  enable interrupt request on measured differential pressure value higher than preset threshold      */
} LPS22HB_interrupt_cfg_phe_t;


/**
  * @brief   INT_SOURCE REGISTER
  */
/* BOOT_STATUS <7>
 *    NOTE: Interrupt active
 */
typedef enum
{
    INT_SOURCE_BOOT_STATUS_MASK           =   ( 1U << 7U ),   /*!<  BOOT_STATUS mask                              */
    INT_SOURCE_BOOT_STATUS_RUNNING        =   ( 1U << 7U ),   /*!<  It indicates that the Boot phase is running   */
    INT_SOURCE_BOOT_STATUS_NOT_RUNNING    =   ( 0U << 7U )    /*!<  Boot is not running               [ Default ] */
} LPS22HB_int_source_boot_status_t;


/* IA <2>
 *    NOTE: Interrupt active
 */
typedef enum
{ 
    INT_SOURCE_IA_MASK                    =   ( 1U << 2U ),   /*!<  IA mask                                       */
    INT_SOURCE_IA_NO_INTERRUPT_GENERATED  =   ( 0U << 2U ),   /*!<  No interrupt has been generated               */
    INT_SOURCE_IA_INTERRUPT_GENERATED     =   ( 1U << 2U )    /*!<  one or more interrupt have been generated     */
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
  * @brief   STATUS REGISTER
  */
/* T_OR <5>
 *    NOTE: Temperature data overrun
 */
typedef enum
{
    STATUS_REG_T_OR_MASK            =   ( 1U << 5U ),   /*!<  T_OR mask                                                 */
    STATUS_REG_T_OR_NO_DATA         =   ( 0U << 5U ),   /*!<  no overrun has occurred                                   */
    STATUS_REG_T_OR_NEW_DATA        =   ( 1U << 5U )    /*!<  new data for temperature has overwritten the previous one */
} LPS22HB_status_t_or_t;


/* P_OR <4>
 *    NOTE: Pressure data overrun
 */
typedef enum
{
    STATUS_REG_P_OR_MASK            =   ( 1U << 4U ),   /*!<  P_OR mask                                               */
    STATUS_REG_P_OR_NO_DATA         =   ( 0U << 4U ),   /*!<  no overrun has occurred                                 */
    STATUS_REG_P_OR_NEW_DATA        =   ( 1U << 4U )    /*!<  new data for pressure has overwritten the previous one  */
} LPS22HB_status_p_or_t;


/* T_DA <1>
 *    NOTE: Temperature data available
 */
typedef enum
{
    STATUS_REG_T_DA_MASK            =   ( 1U << 1U ),   /*!<  T_DA mask                                               */
    STATUS_REG_T_DA_NO_AVAILABLE    =   ( 0U << 1U ),   /*!<  new data for temperature is not yet available           */
    STATUS_REG_T_DA_NEW_DATA        =   ( 1U << 1U )    /*!<  new data for temperature is available                   */
} LPS22HB_status_t_da_t;


/* P_DA <0>
 *    NOTE: Pressure data available
 */
typedef enum
{
    STATUS_REG_P_DA_MASK            =   ( 1U << 0U ),   /*!<  P_DA mask                                               */
    STATUS_REG_P_DA_NO_AVAILABLE    =   ( 0U << 0U ),   /*!<  new data for pressure is not yet available              */
    STATUS_REG_P_DA_NEW_DATA        =   ( 1U << 0U )    /*!<  new data for pressure is available                      */
} LPS22HB_status_p_da_t;


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
    FIFO_CTRL_F_MODE_DYNAMIC_STREAM_MODE    =   ( 0b110 << 5U ),  /*!<  Dynamic-Stream mode                                   */
    FIFO_CTRL_F_MODE_BYPASS_TO_FIFO_MODE    =   ( 0b111 << 5U )   /*!<  Bypass-to-FIDO mode                                   */
} LPS22HB_fifo_ctrl_f_mode_t;


/**
  * @brief   FIFO_STATUS REGISTER
  */
/* FTH_FIFO <7>
 *    NOTE: FIFO watermark status
 */
typedef enum
{
    FIFO_STATUS_FTH_FIFO_MASK       =   ( 1U << 7U ),   /*!<  FTH_FIFO mask                                           */
    FIFO_STATUS_FTH_FIFO_0          =   ( 0U << 7U ),   /*!<  FIFO filling is lower than FTH level                    */
    FIFO_STATUS_FTH_FIFO_1          =   ( 1U << 7U )    /*!<  FIFO filling is equal or higher than FTH level          */
} LPS22HB_fifo_status_fth_fifo_t;


/* OVR <6>
 *    NOTE: FIFO overrun status
 */
typedef enum
{
    FIFO_STATUS_OVR_MASK            =   ( 1U << 6U ),   /*!<  OVR mask                                                */
    FIFO_STATUS_OVR_FIFO_NOT_FULL   =   ( 0U << 6U ),   /*!<  FIFO not full                                           */
    FIFO_STATUS_OVR_FIFO_FULL       =   ( 1U << 6U )    /*!<  FIFO is full and at least one sample in the FIFO has been overwritten */
} LPS22HB_fifo_status_ovr_t;


/* FSS <5:0>
 *    NOTE: FIFO stored data level
 */
typedef enum
{
    FIFO_STATUS_FSS_MASK              =   ( 0b111111 << 0U ) /*!<  FSS mask                                              */
} LPS22HB_fifo_status_fss_t;




#ifndef LPS22HB_VECTOR_STRUCT_H
#define LPS22HB_VECTOR_STRUCT_H
typedef struct
{
  /* Output registers  */
  int32_t   rawPressure;                      /*!<  Raw pressure                      */
  int16_t   rawTemperature;                   /*!<  Raw temperature                   */

  float     pressure;                         /*!<  Pressure in mbar                  */
  float     temperature;                      /*!<  Temperature in Celsius degree     */

  uint32_t  ref_p;                            /*!<  Reference pressure ( raw value )  */
  uint16_t  rpds;                             /*!<  Pressure offset                   */

  /* Configuration  */
  LPS22HB_ctrl_reg1_odr_t         odr;        /*!<  Output data rate selection        */
  LPS22HB_ctrl_reg1_bdu_t         bdu;        /*!<  Block data update                 */
  LPS22HB_ctrl_reg2_boot_t        boot;       /*!<  Reboot memory content flag        */
  LPS22HB_ctrl_reg2_fifo_en_t     fifo_en;    /*!<  FIFO enable                       */
  LPS22HB_ctrl_reg2_stop_on_fth_t stopOnFTH;  /*!<  FIFO watermark level use flag     */
  LPS22HB_ctrl_reg2_swreset_t     swreset;    /*!<  Software reset                    */
  LPS22HB_ctrl_reg2_one_shot_t    one_shot;   /*!<  One-shot                          */
  
  /* FIFO control  */
  LPS22HB_fifo_ctrl_f_mode_t      f_mode;     /*!<  FIFO mode selection               */  
  uint8_t                         wtm;        /*!<  FIFO watermark level              */  

  /* Interrupt mode for pressure acquisition configuration   */
  uint8_t                       interruptCFG; /*!<  Interrupt_CFG register raw value  */

  /* Interrupt source  */
  uint8_t                       int_source;   /*!<  Interrupt source                  */ 

  /* FIFO status  */
  uint8_t                       fifo_status;  /*!<  FIFO status                       */ 
  
  /* Status register value  */
  uint8_t                       status;       /*!<  Status register value             */ 

  /* Pressure threshold  */
  uint16_t                      ths_p;        /*!<  Threshold value for pressure interrupt generation */

  /* Device identification   */
  uint8_t                       deviceID;     /*!<  Device ID                                         */
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

/** It sets the Interrupt mode for pressure acquisition configuration.
  */
LPS22HB_status_t LPS22HB_SetInterruptMode         ( I2C_parameters_t myI2Cparameters, LPS22HB_interrupt_cfg_autorifp_t myAUTORIFP, LPS22HB_interrupt_cfg_reset_arp_t myResetARP, LPS22HB_interrupt_cfg_autozero_t myAutoZero,
                                                    LPS22HB_interrupt_cfg_reset_az_t myResetAZ, LPS22HB_interrupt_cfg_diff_en_t myDiffEN, LPS22HB_interrupt_cfg_lir_t myLIR, LPS22HB_interrupt_cfg_ple_t myPLE, LPS22HB_interrupt_cfg_phe_t myPHE  );

/** It gets the InterruptCFG register: raw value.
  */
LPS22HB_status_t LPS22HB_GetInterruptMode         ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myInterruptCFG        );

/** It sets the threshold value for pressure interrupt event.
  */
LPS22HB_status_t LPS22HB_SetPressureThreshold     ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myThs_P                );

/** It gets the threshold value for pressure interrupt event.
  */
LPS22HB_status_t LPS22HB_GetPressureThreshold     ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myThs_P               );

/** It gets the device ID.
  */
LPS22HB_status_t LPS22HB_GetDeviceID              ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myID                  );

/** It sets the output data rate.
  */
LPS22HB_status_t LPS22HB_SetOutputDataRate        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myODR                  );

/** It gets the output data rate.
  */
LPS22HB_status_t LPS22HB_GetOutputDataRate        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myODR                 );

/** It configures the low-pass filter.
  */
LPS22HB_status_t LPS22HB_ConfLowPassFilter        ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_en_lpfp_t myEN_LPFP, LPS22HB_ctrl_reg1_lpfp_cfg_t myLPFP_CFG  );

/** It sets the block data update.
  */
LPS22HB_status_t LPS22HB_SetBlockDataUpdate       ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_bdu_t myBDU         );

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

/** It sets the FIFO watermark level use.
  */
LPS22HB_status_t LPS22HB_SetFIFOWatermarkLevel    ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t mySTOP_ON_FTH          );

/** It gets the FIFO watermark level use.
  */
LPS22HB_status_t LPS22HB_GetFIFOWatermarkLevel    ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* mySTOP_ON_FTH         );

/** It sets the software reset.
  */
LPS22HB_status_t LPS22HB_SetSoftwareReset         ( I2C_parameters_t myI2Cparameters                                        );

/** It gets the software reset flag value.
  */
LPS22HB_status_t LPS22HB_GetSoftwareReset         ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* mySWRESET             );

/** It triggers the one-shot mode.
  */
LPS22HB_status_t LPS22HB_TriggerOneShot           ( I2C_parameters_t myI2Cparameters                                        );

/** It gets the one-shot mode flag.
  */
LPS22HB_status_t LPS22HB_GetOneShot               ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myONE_SHOT            );

/** It sets the interrupt generation enable: INT_DRDY pin control.
  */
LPS22HB_status_t LPS22HB_SetInterruptGeneration   ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg3_int_h_l_t myINT_H_L, LPS22HB_ctrl_reg3_pp_od_t myPP_OD, LPS22HB_ctrl_reg3_f_fss5_t myF_FSS5,
                                                    LPS22HB_ctrl_reg3_f_fth_t myF_FTH, LPS22HB_ctrl_reg3_f_ovr_t myF_OVR, LPS22HB_ctrl_reg3_drdy_t myDRDY, LPS22HB_ctrl_reg3_int_s2_t myINT_S         );

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

/** It gets raw reference pressure.
  */
LPS22HB_status_t LPS22HB_GetReferencePressure     ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myREF_P               );

/** It sets raw reference pressure.
  */
LPS22HB_status_t LPS22HB_SetReferencePressure     ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myREF_P                );

/** It sets the Pressure offset value.
  */
LPS22HB_status_t LPS22HB_SetPressureOffset        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myPressureOffset       );

/** It gets the Pressure offset value.
  */
LPS22HB_status_t LPS22HB_GetPressureOffset        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myPressureOffset      );

/** It sets the power mode.
  */
LPS22HB_status_t LPS22HB_SetPowerMode             ( I2C_parameters_t myI2Cparameters, LPS22HB_res_conf_lc_en_t myLC_EN      );

/** It reads the interrupt source register.
  */
LPS22HB_status_t LPS22HB_GetInterruptSource       ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myIntSource           );

/** It reads the FIFO status register.
  */
LPS22HB_status_t LPS22HB_GetFIFO_Status           ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOstatus          );

/** It reads the status register.
  */
LPS22HB_status_t LPS22HB_GetStatusRegister        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myStatusRegister      );

/** It gets the raw pressure value.
  */
LPS22HB_status_t LPS22HB_GetRawPressure           ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRawPressure         );

/** It gets the raw temperature value.
  */
LPS22HB_status_t LPS22HB_GetRawTemperature        ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRawTemperature      );

/** It gets the current pressure in mbar.
  */
LPS22HB_status_t LPS22HB_GetPressure              ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myPressure            );

/** It gets the current temperature in Celsius degrees.
  */
LPS22HB_status_t LPS22HB_GetTemperature           ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myTemperature         );
