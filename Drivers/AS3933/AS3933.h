/**
 * @brief       AS3933.h
 * @details     3D Low Frequency Wakeup Receiver.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/* SPI COMMAND STRUCTURE */
/**
  * @brief   MODE. ( B15:B14 )
  */
typedef enum
{
    AS3933_WRITE            =   0x00,           /*!<  WRITE                 */
    AS3933_READ             =   0x01,           /*!<  READ                  */
    AS3933_DIRECT_COMMAND   =   0x03            /*!<  DIRECT COMMAND        */
} AS3933_spi_command_structure_mode_t;


/**
  * @brief   READ/WRITE REGISTER ( B13:B8 )
  */
typedef enum
{
    AS3933_R0               =   0x00,           /*!<  R0  register          */
    AS3933_R1               =   0x01,           /*!<  R1  register          */
    AS3933_R2               =   0x02,           /*!<  R3  register          */
    AS3933_R3               =   0x03,           /*!<  R4  register          */
    AS3933_R4               =   0x04,           /*!<  R5  register          */
    AS3933_R5               =   0x05,           /*!<  R6  register          */
    AS3933_R6               =   0x06,           /*!<  R7  register          */
    AS3933_R7               =   0x07,           /*!<  R8  register          */
    AS3933_R8               =   0x08,           /*!<  R9  register          */
    AS3933_R9               =   0x09,           /*!<  R10 register          */
    AS3933_R10              =   0x0A,           /*!<  R11 register          */
    AS3933_R11              =   0x0B,           /*!<  R11 register          */
    AS3933_R12              =   0x0C,           /*!<  R12 register          */
    AS3933_R13              =   0x0D,           /*!<  R13 register          */
    AS3933_R14              =   0x0E,           /*!<  R14 register          */
    AS3933_R15              =   0x0F,           /*!<  R15 register          */
    AS3933_R16              =   0x10,           /*!<  R16 register          */
    AS3933_R17              =   0x11,           /*!<  R17 register          */
    AS3933_R18              =   0x12,           /*!<  R18 register          */
    AS3933_R19              =   0x13            /*!<  R19 register          */
} AS3933_spi_command_structure_registers_t;


/* SPI DIRECT COMMANDS */
/**
  * @brief   DIRECT COMMANDS. ( B13:B8 )
  */
typedef enum
{
    CLEAR_WAKE              =   0x00,           /*!<  Clears the wake state of the chip. In case the chip has woken up ( WAKE pin is high ) the chip is set back to listening mode  */
    RESET_RSSI              =   0x01,           /*!<  Resets the RSSI measurement                                                                                                   */
    CALIB_RC_OSC            =   0x02,           /*!<  Starts the trimming procedure of the internal RC oscillator                                                                   */
    CLEAR_FALSE             =   0x03,           /*!<  Resets the false wakeup register ( R13 = 00 )                                                                                 */
    PRESET_DEFAULT          =   0x04,           /*!<  Sets all register in the default mode                                                                                         */
    CALIB_RCO_LC            =   0x05            /*!<  Calibration of the RC-oscillator with the external LC tank                                                                    */
} AS3933_spi_direct_commands_t;


/* R0 REGISTER. COMMANDS */
/**
  * @brief   PATT32 ( R0<7> ). Pattern extended to 32 bits
  *
  *          NOTE: Default value: PATT32_16_BITS
  */
typedef enum
{
    PATT32_MASK             =   ( 1 << 7 ),     /*!<  PATT32 mask                                   */
    PATT32_16_BITS          =   ( 0 << 7 ),     /*!<  16-bits pattern extended                      */
    PATT32_32_BITS          =   ( 1 << 7 )      /*!<  32-bits pattern extended                      */
} AS3933_r0_patt32_value_t;


/**
  * @brief   DAT_MASK ( R0<6> ). Masks data on DAT pin before wakeup happens
  *
  *          NOTE: Default value: DAT_MASK_DISABLED
  */
typedef enum
{
    DAT_MASK_MASK           =   ( 1 << 6 ),     /*!<  DAT_MASK mask                                 */
    DAT_MASK_DISABLED       =   ( 0 << 6 ),     /*!<  Data is not masked on DAT pin                 */
    DAT_MASK_ENABLED        =   ( 1 << 6 )      /*!<  Data is masked on DAT pin                     */
} AS3933_r0_dat_mask_value_t;


/**
  * @brief   ON_OFF ( R0<5> ). On/Off operation mode. ( Duty-cycle defined in the register R4<7:6> )
  *
  *          NOTE: Default value: ON_OFF_DISABLED
  */
typedef enum
{
    ON_OFF_MASK             =   ( 1 << 5 ),     /*!<  ON_OFF mask                                   */
    ON_OFF_DISABLED         =   ( 0 << 5 ),     /*!<  ON_OFF is disabled                            */
    ON_OFF_ENABLED          =   ( 1 << 5 )      /*!<  ON_OFF is enabled                             */
} AS3933_r0_on_off_value_t;


/**
  * @brief   MUX_123 ( R0<4> ). Scan mode enable
  *
  *          NOTE: Default value: MUX_123_DISABLED
  */
typedef enum
{
    MUX_123_MASK             =   ( 1 << 4 ),     /*!<  MUX_123 mask                                 */
    MUX_123_DISABLED         =   ( 0 << 4 ),     /*!<  Scan mode enable is disabled                 */
    MUX_123_ENABLED          =   ( 1 << 4 )      /*!<  Scan mode enable is enabled                  */
} AS3933_r0_mux_123_value_t;


/**
  * @brief   EN_A2 ( R0<3> ). Channel 2 enable
  *
  *          NOTE: Default value: EN_A2_ENABLED
  */
typedef enum
{
    EN_A2_MASK              =   ( 1 << 3 ),     /*!<  EN_A2 mask                                    */
    EN_A2_DISABLED          =   ( 0 << 3 ),     /*!<  Channel 2 is disabled                         */
    EN_A2_ENABLED           =   ( 1 << 3 )      /*!<  Channel 2 is enabled                          */
} AS3933_r0_en_a2_value_t;


/**
  * @brief   EN_A3 ( R0<2> ). Channel 3 enable
  *
  *          NOTE: Default value: EN_A3_ENABLED
  */
typedef enum
{
    EN_A3_MASK              =   ( 1 << 2 ),     /*!<  EN_A3 mask                                    */
    EN_A3_DISABLED          =   ( 0 << 2 ),     /*!<  Channel 3 is disabled                         */
    EN_A3_ENABLED           =   ( 1 << 2 )      /*!<  Channel 3 is enabled                          */
} AS3933_r0_en_a3_value_t;


/**
  * @brief   EN_A1 ( R0<1> ). Channel 1 enable
  *
  *          NOTE: Default value: EN_A1_ENABLED
  */
typedef enum
{
    EN_A1_MASK              =   ( 1 << 1 ),     /*!<  EN_A1 mask                                    */
    EN_A1_DISABLED          =   ( 0 << 1 ),     /*!<  Channel 1 is disabled                         */
    EN_A1_ENABLED           =   ( 1 << 1 )      /*!<  Channel 1 is enabled                          */
} AS3933_r0_en_a1_value_t;


/* R1 REGISTER. COMMANDS */
/**
  * @brief   ABS_HY ( R1<7> ). Enable Data slicer absolute reference
  *
  *          NOTE: Default value: ABS_HY_DISABLED
  */
typedef enum
{
    ABS_HY_MASK             =   ( 1 << 7 ),     /*!<  ABS_HY mask                                   */
    ABS_HY_DISABLED         =   ( 0 << 7 ),     /*!<  Data slicer absolute reference is disabled    */
    ABS_HY_ENABLED          =   ( 1 << 7 )      /*!<  Data slicer absolute reference is enabled     */
} AS3933_r1_abs_hy_value_t;


/**
  * @brief   AGC_TLIM ( R1<6> ). AGC acting only on the first carrier burst
  *
  *          NOTE: Default value: AGC_TLIM_DISABLED
  */
typedef enum
{
    AGC_TLIM_MASK           =   ( 1 << 6 ),     /*!<  AGC_TLIM mask                                   */
    AGC_TLIM_DISABLED       =   ( 0 << 6 ),     /*!<  AGC is disabled                                 */
    AGC_TLIM_ENABLED        =   ( 1 << 6 )      /*!<  AGC is enabled                                  */
} AS3933_r1_agc_tlim_value_t;


/**
  * @brief   AGC_UD ( R1<5> ). AGC operating in both direction (up-down)
  *
  *          NOTE: Default value: AGC_UD_UP_DOWN_MODE
  */
typedef enum
{
    AGC_UD_MASK             =   ( 1 << 5 ),     /*!<  AGC_UD mask                                       */
    AGC_UD_DOWN_MODE        =   ( 0 << 5 ),     /*!<  AGC down mode only                                */
    AGC_UD_UP_DOWN_MODE     =   ( 1 << 5 )      /*!<  AGC up and down mode                              */
} AS3933_r1_agc_ud_value_t;


/**
  * @brief   ATT_ON ( R1<4> ). Antenna damper enable
  *
  *          NOTE: Default value: ATT_ON_DISABLED
  */
typedef enum
{
    ATT_ON_MASK             =   ( 1 << 4 ),     /*!<  ATT_ON mask                                       */
    ATT_ON_DISABLED         =   ( 0 << 4 ),     /*!<  Antenna damper disabled                           */
    ATT_ON_ENABLED          =   ( 1 << 4 )      /*!<  Antenna damper enabled                            */
} AS3933_r1_att_on_value_t;


/**
  * @brief   EN_MANCH ( R1<3> ). Manchester decoder enable
  *
  *          NOTE: Default value: EN_MANCH_DISABLED
  */
typedef enum
{
    EN_MANCH_MASK           =   ( 1 << 3 ),     /*!<  EN_MANCH mask                                         */
    EN_MANCH_DISABLED       =   ( 0 << 3 ),     /*!<  Manchester decoder disabled                           */
    EN_MANCH_ENABLED        =   ( 1 << 3 )      /*!<  Manchester decoder enabled                            */
} AS3933_r1_en_manch_value_t;


/**
  * @brief   EN_PAT2 ( R1<2> ). Double wakeup pattern correlation
  *
  *          NOTE: Default value: EN_PAT2_DISABLED
  */
typedef enum
{
    EN_PAT2_MASK            =   ( 1 << 2 ),     /*!<  EN_PAT2 mask                                          */
    EN_PAT2_DISABLED        =   ( 0 << 2 ),     /*!<  Double wakeup pattern correlation disabled            */
    EN_PAT2_ENABLED         =   ( 1 << 2 )      /*!<  Double wakeup pattern correlation enabled             */
} AS3933_r1_en_pat2_value_t;


/**
  * @brief   EN_WPAT ( R1<1> ). Correlator enable
  *
  *          NOTE: Default value: EN_WPAT_ENABLED
  */
typedef enum
{
    EN_WPAT_MASK            =   ( 1 << 1 ),     /*!<  EN_WPAT mask                                          */
    EN_WPAT_DISABLED        =   ( 0 << 1 ),     /*!<  Correlator disabled                                   */
    EN_WPAT_ENABLED         =   ( 1 << 1 )      /*!<  Correlator enabled                                    */
} AS3933_r1_en_wpat_value_t;


/**
  * @brief   EN_XTAL ( R1<0> ). Crystal oscillator enable
  *
  *          NOTE: Default value: EN_XTAL_ENABLED
  */
typedef enum
{
    EN_XTAL_MASK            =   ( 1 << 0 ),     /*!<  EN_XTAL mask                                          */
    EN_XTAL_DISABLED        =   ( 0 << 0 ),     /*!<  Crystal oscillator disabled                           */
    EN_XTAL_ENABLED         =   ( 1 << 0 )      /*!<  Crystal oscillator enabled                            */
} AS3933_r1_en_xtal_value_t;


/* R2 REGISTER. COMMANDS */
/**
  * @brief   S_ABSH ( R2<7> ). Data slicer absolute threshold reduction
  *
  *          NOTE: Default value: S_ABSH_DISABLED
  */
typedef enum
{
    S_ABSH_MASK             =   ( 1 << 7 ),     /*!<  S_ABSH mask                                           */
    S_ABSH_DISABLED         =   ( 0 << 7 ),     /*!<  Data slicer absolute threshold reduction is disabled  */
    S_ABSH_ENABLED          =   ( 1 << 7 )      /*!<  Data slicer absolute threshold reduction is enabled   */
} AS3933_r2_s_absh_value_t;


/**
  * @brief   EN_EXT_CLK ( R2<6> ). Enables external clock generator
  *
  *          NOTE: Default value: EN_EXT_CLK_DISABLED
  */
typedef enum
{
    EN_EXT_CLK_MASK         =   ( 1 << 6 ),     /*!<  EN_EXT_CLK mask                                   */
    EN_EXT_CLK_DISABLED     =   ( 0 << 6 ),     /*!<  Enables external clock generator is disabled      */
    EN_EXT_CLK_ENABLED      =   ( 1 << 6 )      /*!<  Enables external clock generator is enabled       */
} AS3933_r2_en_ext_clk_value_t;


/**
  * @brief   G_BOOST ( R2<5> ). +3dB Amplifier Gain Boost
  *
  *          NOTE: Default value: G_BOOST_DISABLED
  */
typedef enum
{
    G_BOOST_MASK            =   ( 1 << 5 ),     /*!<  G_BOOST mask                                      */
    G_BOOST_DISABLED        =   ( 0 << 5 ),     /*!<  Gain Boost is disabled                            */
    G_BOOST_ENABLED         =   ( 1 << 5 )      /*!<  Gain Boost is enabled                             */
} AS3933_r2_g_boost_value_t;


/**
  * @brief   S_WU1 ( R2<1:0> ). Tolerance setting for the stage wakeup ( 20 to 150 kHz )
  *
  *          NOTE: Default value: S_WU1_20_150_KHZ_TOLERANCE_16_3
  */
typedef enum
{
    S_WU1_20_150_KHZ_MASK               =   ( 0b11 << 0 ),  /*!<  S_WU1 mask ( 20 to 150 kHz )          */
    S_WU1_20_150_KHZ_TOLERANCE_16_3     =   ( 0b00 << 0 ),  /*!<  M = 8 +/- 3                           */
    S_WU1_20_150_KHZ_TOLERANCE_16_2     =   ( 0b01 << 0 ),  /*!<  M = 8 +/- 2                           */
    S_WU1_20_150_KHZ_TOLERANCE_16_1     =   ( 0b10 << 0 )   /*!<  M = 8 +/- 1                           */
} AS3933_r2_s_wu1_20_150_khz_value_t;



/**
  * @brief   S_WU1 ( R2<1:0> ). Tolerance setting for the stage wakeup ( 15 to 20 kHz )
  *
  *          NOTE: Default value: S_WU1_15_20_KHZ_TOLERANCE_8_3
  */
typedef enum
{
    S_WU1_15_20_KHZ_MASK            =   ( 0b11 << 0 ),  /*!<  S_WU1 mask ( 15 to 20 kHz )               */
    S_WU1_15_20_KHZ_TOLERANCE_8_3   =   ( 0b00 << 0 ),  /*!<  M = 8 +/- 3                               */
    S_WU1_15_20_KHZ_TOLERANCE_8_2   =   ( 0b01 << 0 ),  /*!<  M = 8 +/- 2                               */
    S_WU1_15_20_KHZ_TOLERANCE_8_1   =   ( 0b10 << 0 )   /*!<  M = 8 +/- 1                               */
} AS3933_r2_s_wu1_15_20_khz_value_t;


/* R3 REGISTER. COMMANDS */
/**
  * @brief   HY_20m ( R3<7> ). Data slicer hysteresis
  *
  *          NOTE: Default value: HY_20M_COMPARATOR_HYSTERESIS_40MV
  */
typedef enum
{
    HY_20M_MASK                         =   ( 1 << 7 ), /*!<  HY_20m mask                               */
    HY_20M_COMPARATOR_HYSTERESIS_40MV   =   ( 0 << 7 ), /*!<  Comparator hysteresis = 40mV              */
    HY_20M_COMPARATOR_HYSTERESIS_20MV   =   ( 1 << 7 )  /*!<  Comparator hysteresis = 20mV              */
} AS3933_r3_hy_20m_value_t;


/**
  * @brief   HY_POS ( R3<6> ). Data slicer hysteresis
  *
  *          NOTE: Default value: HY_POS_HYSTERESIS_POSITIVE_EDGES
  */
typedef enum
{
    HY_POS_MASK                         =   ( 1 << 6 ), /*!<  HY_POS mask                               */
    HY_POS_HYSTERESIS_POSITIVE_EDGES    =   ( 0 << 6 ), /*!<  Hysteresis only positive edges            */
    HY_POS_HYSTERESIS_BOTH_EDGES        =   ( 1 << 6 )  /*!<  Hysteresis positive and negative edges    */
} AS3933_r3_hy_pos_value_t;


/**
  * @brief   FS_SCL ( R3<3:5> ). Data slices time constant
  *
  *          NOTE: Default value: FS_SCL_PREAMBLE_LENGTH_2_3
  */
typedef enum
{
    FS_SCL_MASK                     =   ( 0b111 << 3 ),     /*!<  FS_SCL mask                           */
    FS_SCL_PREAMBLE_LENGTH_0_8      =   ( 0b000 << 3 ),     /*!<  Minimum Preamble Length: 0.8ms        */
    FS_SCL_PREAMBLE_LENGTH_1_15     =   ( 0b001 << 3 ),     /*!<  Minimum Preamble Length: 1.15ms       */
    FS_SCL_PREAMBLE_LENGTH_1_55     =   ( 0b010 << 3 ),     /*!<  Minimum Preamble Length: 1.55ms       */
    FS_SCL_PREAMBLE_LENGTH_1_9      =   ( 0b011 << 3 ),     /*!<  Minimum Preamble Length: 1.9ms        */
    FS_SCL_PREAMBLE_LENGTH_2_3      =   ( 0b100 << 3 ),     /*!<  Minimum Preamble Length: 2.3ms        */
    FS_SCL_PREAMBLE_LENGTH_2_65     =   ( 0b101 << 3 ),     /*!<  Minimum Preamble Length: 2.65ms       */
    FS_SCL_PREAMBLE_LENGTH_3        =   ( 0b110 << 3 ),     /*!<  Minimum Preamble Length: 3ms          */
    FS_SCL_PREAMBLE_LENGTH_3_5      =   ( 0b111 << 3 )      /*!<  Minimum Preamble Length: 3.5ms        */
} AS3933_r3_fs_scl_value_t;


/**
  * @brief   FS_ENV ( R3<2:0> ). Envelop detector time constant
  *
  *          NOTE: Default value: FS_ENV_SYMBOL_RATE_4096
  */
typedef enum
{
    FS_ENV_MASK                 =   ( 0b111 << 0 ),     /*!<  FS_ENV mask                               */
    FS_ENV_SYMBOL_RATE_4096     =   ( 0b000 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 4096   */
    FS_ENV_SYMBOL_RATE_2184     =   ( 0b001 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 2184   */
    FS_ENV_SYMBOL_RATE_1490     =   ( 0b010 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 1490   */
    FS_ENV_SYMBOL_RATE_1130     =   ( 0b011 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 1130   */
    FS_ENV_SYMBOL_RATE_910      =   ( 0b100 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 910    */
    FS_ENV_SYMBOL_RATE_762      =   ( 0b101 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 762    */
    FS_ENV_SYMBOL_RATE_655      =   ( 0b110 << 0 ),     /*!<  Symbol Rate [Manchester symbol/s]: 655    */
    FS_ENV_SYMBOL_RATE_512      =   ( 0b111 << 0 )      /*!<  Symbol Rate [Manchester symbol/s]: 512    */
} AS3933_r3_fs_env_value_t;


/* R4 REGISTER. COMMANDS */
/**
  * @brief   T_OFF ( R4<7:6> ). Off time in ON/OFF operation mode
  *
  *          NOTE: Default value: T_OFF_1_MS
  */
typedef enum
{
    T_OFF_MASK      =   ( 0b11 << 6 ),                 /*!<  T_OFF mask                                 */
    T_OFF_1_MS      =   ( 0b00 << 6 ),                 /*!<  Off time: 1ms                              */
    T_OFF_2_MS      =   ( 0b01 << 6 ),                 /*!<  Off time: 2ms                              */
    T_OFF_4_MS      =   ( 0b10 << 6 ),                 /*!<  Off time: 4ms                              */
    T_OFF_8_MS      =   ( 0b11 << 6 )                  /*!<  Off time: 8ms                              */
} AS3933_r4_t_off_value_t;


/**
  * @brief   D_RES ( R4<5:4> ). Antenna damping resistor ( Shunt Resistor ( parallel to the resonator at 125 kHz ) )
  *
  *          NOTE: Default value: D_RES_PARALLEL_SHUNT_RESISTOR_3_KOHM
  */
typedef enum
{
    D_RES_MASK                              =   ( 0b11 << 4 ),      /*!<  D_RES mask                    */
    D_RES_PARALLEL_SHUNT_RESISTOR_1_KOHM    =   ( 0b00 << 4 ),      /*!<  Shunt Resistor: 1kOhm         */
    D_RES_PARALLEL_SHUNT_RESISTOR_3_KOHM    =   ( 0b01 << 4 ),      /*!<  Shunt Resistor: 3kOhm         */
    D_RES_PARALLEL_SHUNT_RESISTOR_9_KOHM    =   ( 0b10 << 4 ),      /*!<  Shunt Resistor: 9kOhm         */
    D_RES_PARALLEL_SHUNT_RESISTOR_27_KOHM   =   ( 0b11 << 4 )       /*!<  Shunt Resistor: 27kOhm        */
} AS3933_r4_d_res_value_t;


/**
  * @brief   GR ( R4<3:0> ). Gain reduction
  *
  *          NOTE: Default value: GR_GAIN_REDUCTION_NO_GAIN_REDUCTION
  */
typedef enum
{
    GR_MASK                             =   ( 0b1111 << 0 ),        /*!<  GR mask                       */
    GR_GAIN_REDUCTION_NO_GAIN_REDUCTION =   ( 0b0000 << 0 ),        /*!<  No Gain Reduction             */
    GR_GAIN_REDUCTION_MINUS_4_DB        =   ( 0b0100 << 0 ),        /*!<  Gain Reduction: -4dB          */
    GR_GAIN_REDUCTION_MINUS_8_DB        =   ( 0b0110 << 0 ),        /*!<  Gain Reduction: -8dB          */
    GR_GAIN_REDUCTION_MINUS_12_DB       =   ( 0b1000 << 0 ),        /*!<  Gain Reduction: -12dB         */
    GR_GAIN_REDUCTION_MINUS_16_DB       =   ( 0b1010 << 0 ),        /*!<  Gain Reduction: -16dB         */
    GR_GAIN_REDUCTION_MINUS_20_DB       =   ( 0b1100 << 0 ),        /*!<  Gain Reduction: -20dB         */
    GR_GAIN_REDUCTION_MINUS_24_DB       =   ( 0b1110 << 0 )         /*!<  Gain Reduction: -24dB         */
} AS3933_r4_gr_value_t;


/* R5 REGISTER. COMMANDS */
/**
  * @brief   TS2 ( R5<7:0> ). 2nd Byte of wakeup pattern
  *
  *          NOTE: Default value: TS2_WAKEUP_PATTERN_MSB
  */
typedef enum
{
    TS2_PATT2B_MASK             =   ( 0xFF          << 0 ),     /*!<  TS2 mask                       */
    TS2_WAKEUP_PATTERN_PATT2B   =   ( 0b01101001    << 0 )      /*!<  Default value                  */
} AS3933_r5_ts2_value_t;


/* R6 REGISTER. COMMANDS */
/**
  * @brief   TS1 ( R6<7:0> ). 1st Byte of wakeup pattern
  *
  *          NOTE: Default value: TS1_WAKEUP_PATTERN_LSB
  */
typedef enum
{
    TS1_PATT1B_MASK             =   ( 0xFF          << 0 ),     /*!<  TS1 mask                       */
    TS1_WAKEUP_PATTERN_PATT1B   =   ( 0b10010110    << 0 )      /*!<  Default value                  */
} AS3933_r6_ts2_value_t;


/* R7 REGISTER. COMMANDS */
/**
  * @brief   T_OUT ( R7<7:5> ). Automatic time-out
  *
  *          NOTE: Default value: T_OUT_0_SEC
  */
typedef enum
{
    T_OUT_MASK          =   ( 0b111 << 5 ),                 /*!<  T_OUT mask                            */
    T_OUT_0_SEC         =   ( 0b000 << 5 ),                 /*!<  Timeout: 0sec                         */
    T_OUT_50_MSEC       =   ( 0b001 << 5 ),                 /*!<  Timeout: 50msec                       */
    T_OUT_100_MSEC      =   ( 0b010 << 5 ),                 /*!<  Timeout: 100mecs                      */
    T_OUT_150_MSEC      =   ( 0b011 << 5 ),                 /*!<  Timeout: 150msec                      */
    T_OUT_200_MSEC      =   ( 0b100 << 5 ),                 /*!<  Timeout: 200msec                      */
    T_OUT_250_MSEC      =   ( 0b101 << 5 ),                 /*!<  Timeout: 250msec                      */
    T_OUT_300_MSEC      =   ( 0b110 << 5 ),                 /*!<  Timeout: 300msec                      */
    T_OUT_350_MSEC      =   ( 0b111 << 5 )                  /*!<  Timeout: 350msec                      */
} AS3933_r7_t_out_value_t;


/**
  * @brief   T_HBIT ( R7<4:0> ). Bit rate definition
  *
  *          NOTE: Default value: T_HBIT_BIT_RATE_12
  */
typedef enum
{
    T_HBIT_MASK         =   ( 0b11111 << 0 ),                 /*!<  T_HBIT mask                                  */
    T_HBIT_BIT_RATE_4   =   ( 0b00011 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 4   */
    T_HBIT_BIT_RATE_5   =   ( 0b00100 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 5   */
    T_HBIT_BIT_RATE_6   =   ( 0b00101 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 6   */
    T_HBIT_BIT_RATE_7   =   ( 0b00110 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 7   */
    T_HBIT_BIT_RATE_8   =   ( 0b00111 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 8   */
    T_HBIT_BIT_RATE_9   =   ( 0b01000 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 9   */
    T_HBIT_BIT_RATE_10  =   ( 0b01001 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 10  */
    T_HBIT_BIT_RATE_11  =   ( 0b01010 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 11  */
    T_HBIT_BIT_RATE_12  =   ( 0b01011 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 12  */
    T_HBIT_BIT_RATE_13  =   ( 0b01100 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 13  */
    T_HBIT_BIT_RATE_14  =   ( 0b01101 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 14  */
    T_HBIT_BIT_RATE_15  =   ( 0b01110 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 15  */
    T_HBIT_BIT_RATE_16  =   ( 0b01111 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 16  */
    T_HBIT_BIT_RATE_17  =   ( 0b10000 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 17  */
    T_HBIT_BIT_RATE_18  =   ( 0b10001 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 18  */
    T_HBIT_BIT_RATE_19  =   ( 0b10010 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 19  */
    T_HBIT_BIT_RATE_20  =   ( 0b10011 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 20  */
    T_HBIT_BIT_RATE_21  =   ( 0b10100 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 21  */
    T_HBIT_BIT_RATE_22  =   ( 0b10101 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 22  */
    T_HBIT_BIT_RATE_23  =   ( 0b10110 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 23  */
    T_HBIT_BIT_RATE_24  =   ( 0b10111 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 24  */
    T_HBIT_BIT_RATE_25  =   ( 0b11000 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 25  */
    T_HBIT_BIT_RATE_26  =   ( 0b11001 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 26  */
    T_HBIT_BIT_RATE_27  =   ( 0b11010 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 27  */
    T_HBIT_BIT_RATE_28  =   ( 0b11011 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 28  */
    T_HBIT_BIT_RATE_29  =   ( 0b11100 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 29  */
    T_HBIT_BIT_RATE_30  =   ( 0b11101 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 30  */
    T_HBIT_BIT_RATE_31  =   ( 0b11110 << 0 ),                 /*!<  Bit Duration in Clock Generator Periods: 31  */
    T_HBIT_BIT_RATE_32  =   ( 0b11111 << 0 )                  /*!<  Bit Duration in Clock Generator Periods: 32  */
} AS3933_r7_t_hbit_value_t;


/* R8 REGISTER. COMMANDS */
/**
  * @brief   BAND_SEL ( R8<7:5> ). Band selection
  *
  *          NOTE: Default value: BAND_SEL_RANGE_95_150_KHZ
  */
typedef enum
{
    BAND_SEL_MASK               =   ( 0b111 << 5 ),             /*!<  BAND_SEL mask                                     */
    BAND_SEL_RANGE_95_150_KHZ   =   ( 0b000 << 5 ),             /*!<  N = 4,  Operating Frequency Range [kHz]: 95-150   */
    BAND_SEL_RANGE_65_95_KHZ    =   ( 0b000 << 5 ),             /*!<  N = 6,  Operating Frequency Range [kHz]: 65-95    */
    BAND_SEL_RANGE_40_65_KHZ    =   ( 0b000 << 5 ),             /*!<  N = 10, Operating Frequency Range [kHz]: 40-65    */
    BAND_SEL_RANGE_23_40_KHZ    =   ( 0b000 << 5 ),             /*!<  N = 18, Operating Frequency Range [kHz]: 23-40    */
    BAND_SEL_RANGE_15_23_KHZ    =   ( 0b000 << 5 )              /*!<  N = 14, Operating Frequency Range [kHz]: 15-23    */
} AS3933_r8_band_sel_value_t;


/**
  * @brief   T_AUTO ( R8<2:0> ). Artificial wake-up
  *
  *          NOTE: Default value: T_AUTO_NO_ARTIFICIAL_WAKEUP
  */
typedef enum
{
    T_AUTO_MASK                     =   ( 0b111 << 0 ),         /*!<  T_AUTO mask                                       */
    T_AUTO_NO_ARTIFICIAL_WAKEUP     =   ( 0b000 << 0 ),         /*!<  No artificial wake-up                             */
    T_AUTO_ARTIFICIAL_WAKEUP_1_SEC  =   ( 0b001 << 0 ),         /*!<  Artificial wake-up 1sec                           */
    T_AUTO_ARTIFICIAL_WAKEUP_5_SEC  =   ( 0b010 << 0 ),         /*!<  Artificial wake-up 5sec                           */
    T_AUTO_ARTIFICIAL_WAKEUP_20_SEC =   ( 0b011 << 0 ),         /*!<  Artificial wake-up 20sec                          */
    T_AUTO_ARTIFICIAL_WAKEUP_2_MIN  =   ( 0b100 << 0 ),         /*!<  Artificial wake-up 2min                           */
    T_AUTO_ARTIFICIAL_WAKEUP_15_MIN =   ( 0b101 << 0 ),         /*!<  Artificial wake-up 15min                          */
    T_AUTO_ARTIFICIAL_WAKEUP_1_HOUR =   ( 0b110 << 0 ),         /*!<  Artificial wake-up 1hour                          */
    T_AUTO_ARTIFICIAL_WAKEUP_2_HOUR =   ( 0b111 << 0 ),         /*!<  Artificial wake-up 2hour                          */
} AS3933_r8_t_auto_value_t;


/* R9 REGISTER. COMMANDS */
/**
  * @brief   BLOCK_AGC ( R9<7> ). Disables AGC
  *
  *          NOTE: Default value: BLOCK_AGC_ENABLED
  */
typedef enum
{
    BLOCK_AGC_MASK      =   ( 1 << 7 ),             /*!<  BLOCK_AGC mask                       */
    BLOCK_AGC_DISABLED  =   ( 1 << 7 ),             /*!<  AGC is disabled                      */
    BLOCK_AGC_ENABLED   =   ( 0 << 7 )              /*!<  AGC is enabled                       */
} AS3933_r9_block_agc_value_t;



/* R10 REGISTER. COMMANDS */
/**
  * @brief   RSSI1 ( R10<4:0> ). RSSI channel 1
  *
  */
typedef enum
{
    RSSI1_MASK      =   ( 0b11111 << 0 )              /*!<  RSSI1 mask                        */
} AS3933_r10_rssi1_value_t;


/* R11 REGISTER. COMMANDS */
/**
  * @brief   RSSI3 ( R11<4:0> ). RSSI channel 3
  *
  */
typedef enum
{
    RSSI3_MASK      =   ( 0b11111 << 0 )              /*!<  RSSI3 mask                        */
} AS3933_r11_rssi3_value_t;


/* R12 REGISTER. COMMANDS */
/**
  * @brief   RSSI2 ( R11<4:0> ). RSSI channel 2
  *
  */
typedef enum
{
    RSSI2_MASK      =   ( 0b11111 << 0 )              /*!<  RSSI2 mask                        */
} AS3933_r11_rssi2_value_t;


/* R14 REGISTER. COMMANDS */
/**
  * @brief   RC_CAL_KO ( R14<7> ). Unsuccessful RC calibration
  *
  */
typedef enum
{
    RC_CAL_KO_MASK  =   ( 1 << 7 ),                 /*!<  RC_CAL_KO mask                        */
    RC_CAL_KO_HIGH  =   ( 1 << 7 ),                 /*!<  RC_CAL_KO Unsuccessful RC calibration */
    RC_CAL_KO_LOW   =   ( 0 << 7 )                  /*!<  RC_CAL_KO Reset state                 */
} AS3933_r14_rc_cal_ko_value_t;


/**
  * @brief   RC_CAL_OK ( R14<6> ). Successful RC calibration
  *
  */
typedef enum
{
    RC_CAL_OK_MASK  =   ( 1 << 6 ),                 /*!<  RC_CAL_OK mask                        */
    RC_CAL_OK_HIGH  =   ( 1 << 6 ),                 /*!<  RC_CAL_OK Successful RC calibration   */
    RC_CAL_OK_LOW   =   ( 0 << 6 )                  /*!<  RC_CAL_OK Reset state                 */
} AS3933_r14_rc_cal_ok_value_t;


/**
  * @brief   RC_OSC_TAPS ( R14<5:0> ). RC-Oscillator taps setting
  *
  */
typedef enum
{
    RC_OSC_TAPS_MASK  =   ( 0b111111 << 0 )         /*!<  RC_OSC_TAPS mask                        */
} AS3933_r14_rc_osc_taps_value_t;


/* R15 REGISTER. COMMANDS */
/**
  * @brief   LC_OSC_KO ( R15<7> ). LC-Oscillator not working
  *
  */
typedef enum
{
    LC_OSC_KO_MASK  =   ( 1 << 7 ),                 /*!<  LC_OSC_KO mask                        */
    LC_OSC_KO_HIGH  =   ( 1 << 7 ),                 /*!<  LC-Oscillator not working             */
    LC_OSC_KO_LOW   =   ( 0 << 7 )                  /*!<  LC_OSC_KO Reset state                 */
} AS3933_r15_lc_osc_ko_value_t;


/**
  * @brief   LC_OSC_OK ( R15<6> ). LC-Oscillator working
  *
  */
typedef enum
{
    LC_OSC_OK_MASK  =   ( 1 << 6 ),                 /*!<  LC_OSC_OK mask                        */
    LC_OSC_OK_HIGH  =   ( 1 << 6 ),                 /*!<  LC_OSC_OK LC-Oscillator working       */
    LC_OSC_OK_LOW   =   ( 0 << 6 )                  /*!<  LC_OSC_OK Reset state                 */
} AS3933_r15_lc_osc_ok_value_t;


/* R16 REGISTER. COMMANDS */
/**
  * @brief   CLOCK_GEN_DIS ( R16<7> ). The Clock Generator output signal displayed on CL_DAT pin
  *
  *          NOTE: Default value: CLOCK_GEN_DIS_DISABLED
  */
typedef enum
{
    CLOCK_GEN_DIS_MASK      =   ( 1 << 7 ),         /*!<  CLOCK_GEN_DIS mask                    */
    CLOCK_GEN_DIS_ENABLED   =   ( 1 << 7 ),         /*!<  CLOCK on CL_DAT pin                   */
    CLOCK_GEN_DIS_DISABLED  =   ( 0 << 7 )          /*!<  NO CLOCK on CL_DAT pin                */
} AS3933_r16_clock_gen_dis_value_t;


/**
  * @brief   LC_OSC_DIS ( R16<6> ). The LC-oscillator output signal displayed on DAT pin
  *
  *          NOTE: Default value: LC_OSC_DIS_DISABLED
  */
typedef enum
{
    LC_OSC_DIS_MASK      =   ( 1 << 6 ),         /*!<  LC_OSC_DIS mask                          */
    LC_OSC_DIS_ENABLED   =   ( 1 << 6 ),         /*!<  LC-CLOCK on CL_DAT pin                   */
    LC_OSC_DIS_DISABLED  =   ( 0 << 6 )          /*!<  NO LC-CLOCK on CL_DAT pin                */
} AS3933_r16_lc_osc_dis_value_t;



/**
  * @brief   RC_OSC_MIN ( R16<5> ). Sets the RC-oscillator to minimum frequency
  *
  *          NOTE: Default value: RC_OSC_MIN_DISABLED
  */
typedef enum
{
    RC_OSC_MIN_MASK      =   ( 1 << 5 ),         /*!<  RC_OSC_MIN mask                                  */
    RC_OSC_MIN_ENABLED   =   ( 1 << 5 ),         /*!<  RC-oscillator to minimum frequency enabled       */
    RC_OSC_MIN_DISABLED  =   ( 0 << 5 )          /*!<  RC-oscillator to minimum frequency disabled      */
} AS3933_r16_rc_osc_min_value_t;


/**
  * @brief   RC_OSC_MIN ( R16<4> ). Sets the RC-oscillator to maximum frequency
  *
  *          NOTE: Default value: RC_OSC_MAX_DISABLED
  */
typedef enum
{
    RC_OSC_MAX_MASK      =   ( 1 << 4 ),         /*!<  RC_OSC_MAX mask                                  */
    RC_OSC_MAX_ENABLED   =   ( 1 << 4 ),         /*!<  RC-oscillator to maximum frequency enabled       */
    RC_OSC_MAX_DISABLED  =   ( 0 << 4 )          /*!<  RC-oscillator to maximum frequency disabled      */
} AS3933_r16_rc_osc_max_value_t;


/**
  * @brief   LC_OSC_MUX3 ( R16<2> ). Connects LF3P to the LCO
  *
  *          NOTE: Default value: LC_OSC_MUX3_LF3P_AND_LCO_DISCONNECTED
  */
typedef enum
{
    LC_OSC_MUX3_MASK                        =   ( 1 << 2 ),     /*!<  LC_OSC_MUX3 mask                  */
    LC_OSC_MUX3_LF3P_AND_LCO_CONNECTED      =   ( 1 << 2 ),     /*!<  LF3P and LCO connected            */
    LC_OSC_MUX3_LF3P_AND_LCO_DISCONNECTED   =   ( 0 << 2 )      /*!<  LF3P and LCO disconnected         */
} AS3933_r16_lc_osc_mux3_value_t;


/**
  * @brief   LC_OSC_MUX2 ( R16<1> ). Connects LF2P to the LCO
  *
  *          NOTE: Default value: LC_OSC_MUX2_LF2P_AND_LCO_DISCONNECTED
  */
typedef enum
{
    LC_OSC_MUX2_MASK                        =   ( 1 << 1 ),     /*!<  LC_OSC_MUX2 mask                  */
    LC_OSC_MUX2_LF2P_AND_LCO_CONNECTED      =   ( 1 << 1 ),     /*!<  LF2P and LCO connected            */
    LC_OSC_MUX2_LF2P_AND_LCO_DISCONNECTED   =   ( 0 << 1 )      /*!<  LF2P and LCO disconnected         */
} AS3933_r16_lc_osc_mux2_value_t;


/**
  * @brief   LC_OSC_MUX1 ( R16<0> ). Connects LF1P to the LCO
  *
  *          NOTE: Default value: LC_OSC_MUX1_LF1P_AND_LCO_DISCONNECTED
  */
typedef enum
{
    LC_OSC_MUX1_MASK                        =   ( 1 << 0 ),     /*!<  LC_OSC_MUX1 mask                  */
    LC_OSC_MUX1_LF1P_AND_LCO_CONNECTED      =   ( 1 << 0 ),     /*!<  LF1P and LCO connected            */
    LC_OSC_MUX1_LF1P_AND_LCO_DISCONNECTED   =   ( 0 << 0 )      /*!<  LF1P and LCO disconnected         */
} AS3933_r16_lc_osc_mux1_value_t;



/* R17 REGISTER. COMMANDS */
/**
  * @brief   CAPS_CH1 ( R17<4:0> ). Capacitor banks on the channel1
  *
  *          NOTE: Default value: CAPS_CH1_ADDS_NONE
  */
typedef enum
{
    CAPS_CH1_MASK       =   ( 0b11111 << 0 ),           /*!<  CAPS_CH1 mask                                 */
    CAPS_CH1_ADDS_NONE  =   ( 0b00000 << 0 ),           /*!<  None      to LF1P                             */
    CAPS_CH1_ADDS_1PF   =   ( 0b00001 << 0 ),           /*!<  Adds 1pF  to LF1P                             */
    CAPS_CH1_ADDS_2PF   =   ( 0b00010 << 0 ),           /*!<  Adds 2pF  to LF1P                             */
    CAPS_CH1_ADDS_4PF   =   ( 0b00100 << 0 ),           /*!<  Adds 4pF  to LF1P                             */
    CAPS_CH1_ADDS_8PF   =   ( 0b01000 << 0 ),           /*!<  Adds 8pF  to LF1P                             */
    CAPS_CH1_ADDS_16PF  =   ( 0b10000 << 0 )            /*!<  Adds 16pF to LF1P                             */
} AS3933_r17_caps_ch1_value_t;


/* R18 REGISTER. COMMANDS */
/**
  * @brief   CAPS_CH2 ( R18<4:0> ). Capacitor banks on the channel2
  *
  *          NOTE: Default value: CAPS_CH2_ADDS_NONE
  */
typedef enum
{
    CAPS_CH2_MASK       =   ( 0b11111 << 0 ),           /*!<  CAPS_CH2 mask                                 */
    CAPS_CH2_ADDS_NONE  =   ( 0b00000 << 0 ),           /*!<  None      to LF2P                             */
    CAPS_CH2_ADDS_1PF   =   ( 0b00001 << 0 ),           /*!<  Adds 1pF  to LF2P                             */
    CAPS_CH2_ADDS_2PF   =   ( 0b00010 << 0 ),           /*!<  Adds 2pF  to LF2P                             */
    CAPS_CH2_ADDS_4PF   =   ( 0b00100 << 0 ),           /*!<  Adds 4pF  to LF2P                             */
    CAPS_CH2_ADDS_8PF   =   ( 0b01000 << 0 ),           /*!<  Adds 8pF  to LF2P                             */
    CAPS_CH2_ADDS_16PF  =   ( 0b10000 << 0 )            /*!<  Adds 16pF to LF2P                             */
} AS3933_r18_caps_ch2_value_t;


/* R19 REGISTER. COMMANDS */
/**
  * @brief   CAPS_CH3 ( R19<4:0> ). Capacitor banks on the channel3
  *
  *          NOTE: Default value: CAPS_CH3_ADDS_NONE
  */
typedef enum
{
    CAPS_CH3_MASK       =   ( 0b11111 << 0 ),           /*!<  CAPS_CH3 mask                                 */
    CAPS_CH3_ADDS_NONE  =   ( 0b00000 << 0 ),           /*!<  None      to LF3P                             */
    CAPS_CH3_ADDS_1PF   =   ( 0b00001 << 0 ),           /*!<  Adds 1pF  to LF3P                             */
    CAPS_CH3_ADDS_2PF   =   ( 0b00010 << 0 ),           /*!<  Adds 2pF  to LF3P                             */
    CAPS_CH3_ADDS_4PF   =   ( 0b00100 << 0 ),           /*!<  Adds 4pF  to LF3P                             */
    CAPS_CH3_ADDS_8PF   =   ( 0b01000 << 0 ),           /*!<  Adds 8pF  to LF3P                             */
    CAPS_CH3_ADDS_16PF  =   ( 0b10000 << 0 )            /*!<  Adds 16pF to LF3P                             */
} AS3933_r19_caps_ch3_value_t;




/* DRIVER COMMANDS */
/**
  * @brief   CHANNEL ENABLED
  *
  *          NOTE: p.14 8.1.1 Listening Mode
  */
typedef enum
{
    AS3933_THREE_CHANNELS_ENABLED   =   0,              /*!<  All channels enabled                          */
    AS3933_TWO_CHANNELS_ENABLED     =   1,              /*!<  Channels 1 and 2 enabled                      */
    AS3933_ONE_CHANNELS_ENABLED     =   2,              /*!<  Channel 1 enabled                             */
    AS3933_ALL_CHANNELS_DISABLED    =   3               /*!<  All channels disabled                         */
} AS3933_channels_enable_t;


/**
  * @brief   LISTENING MODE ( LOW POWER MODE )
  *
  *          NOTE: p.14 8.1.1 Listening Mode
  */
typedef enum
{
    AS3933_STANDARD_LISTENING_MODE  =   0,              /*!<  All channels are active at the same time      */
    AS3933_SCANNING_MODE            =   1,              /*!<  Low Power mode 1                              */
    AS3933_ON_OFF_MODE              =   2               /*!<  Low Power mode 2                              */
} AS3933_scanning_mode_t;


/**
  * @brief   TOLERANCE SETTINGS
  *
  *          NOTE: p.23 8.3.1 Frequency Detector / RSSI / Channel Selector
  *                The tolerance depends on the frequency detection band.
  */
typedef enum
{
    AS3933_TOLERANCE_TIGHT  =   0,
    AS3933_TOLERANCE_MEDIUM =   1,
    AS3933_TOLERANCE_RELAX  =   2
} AS3933_tolerance_settings_t;


/**
  * @brief   CHANNELS ( Parallel Tuning Capacitance )
  *
  */
typedef enum
{
    AS3933_CHANNEL_LF1P  =   0,                 /*!<  Channel 1         */
    AS3933_CHANNEL_LF2P  =   1,                 /*!<  Channel 2         */
    AS3933_CHANNEL_LF3P  =   2                  /*!<  Channel 3         */
} AS3933_parallel_tuning_channels_t;


/**
  * @brief   CAPACITANCE ( Parallel Tuning Capacitance )
  *
  */
typedef enum
{
    AS3933_CAPACITANCE_ADD_1PF   =   0,         /*!<  Capacitance 1pF   */
    AS3933_CAPACITANCE_ADD_2PF   =   1,         /*!<  Capacitance 2pF   */
    AS3933_CAPACITANCE_ADD_4PF   =   2,         /*!<  Capacitance 4pF   */
    AS3933_CAPACITANCE_ADD_8PF   =   3,         /*!<  Capacitance 8pF   */
    AS3933_CAPACITANCE_ADD_16PF  =   4          /*!<  Capacitance 16pF  */
} AS3933_parallel_tuning_capacitance_t;








#ifndef AS3933_VECTOR_STRUCT_H
#define AS3933_VECTOR_STRUCT_H
/* AS3933 DATA */
typedef struct
{
    int8_t      f_wake;                  /*!<  False wakeup register                */
    uint8_t     patt2b;                  /*!<  Wakeup pattern PATT2B ( Manchester ) */
    uint8_t     patt1b;                  /*!<  Wakeup pattern PATT1B ( Manchester ) */

    uint32_t    data;                    /*!<  Data                                 */
} AS3933_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AS3933_SUCCESS     =       0,
    AS3933_FAILURE     =       1
} AS3933_status_t;





/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
AS3933_status_t  AS3933_Init                            ( SPI_parameters_t mySPI_parameters                                                                                                                         );

/** It configures the low power mode.
    */
AS3933_status_t  AS3933_SetLowPowerMode                 ( SPI_parameters_t mySPI_parameters, AS3933_channels_enable_t myEnabledChannels, AS3933_scanning_mode_t myLowPowerMode, AS3933_r4_t_off_value_t myT         );

/** It configures the artificial wakeup.
    */
AS3933_status_t  AS3933_SetArtificialWakeUp             ( SPI_parameters_t mySPI_parameters, AS3933_r8_t_auto_value_t myArtificialWakeUp                                                                            );

/** It gets feedback on the surrounding environment reading the false wakeup register.
    */
AS3933_status_t  AS3933_ReadFalseWakeUpRegister         ( SPI_parameters_t mySPI_parameters, AS3933_data_t* myF_WAKE                                                                                                );

/** It configures the clock generator.
    */
AS3933_status_t  AS3933_SetClockGenerator               ( SPI_parameters_t mySPI_parameters, AS3933_r1_en_xtal_value_t myClockGenerator, AS3933_r16_clock_gen_dis_value_t myClockGeneratorOutputMode                );

/** It calibrates RC oscillator ( Self Calibration only ).
    */
AS3933_status_t  AS3933_CalibrateRC_Oscillator          ( SPI_parameters_t mySPI_parameters                                                                                                                         );

/** It configures the antenna damper.
    */
AS3933_status_t  AS3933_SetAntennaDamper                ( SPI_parameters_t mySPI_parameters, AS3933_r1_att_on_value_t myAntennaDamperMode, AS3933_r4_d_res_value_t myShuntResistor                                  );

/** It configures the envelop detector for different symbol rates.
    */
AS3933_status_t  AS3933_SetEnvelopDetector              ( SPI_parameters_t mySPI_parameters, AS3933_r3_fs_env_value_t mySymbolRates                                                                                 );

/** It configures the data slicer for different preamble length.
    */
AS3933_status_t  AS3933_SetDataSlicer                   ( SPI_parameters_t mySPI_parameters, AS3933_r1_abs_hy_value_t myAbsoluteThresholdMode, AS3933_r3_fs_scl_value_t myMinimumPreableLength                      );

/** It configures the hysteresis on the data slicer comparator.
    */
AS3933_status_t  AS3933_SetComparatorHysteresis         ( SPI_parameters_t mySPI_parameters, AS3933_r3_hy_pos_value_t myHysteresisMode, AS3933_r3_hy_20m_value_t myHysteresisRange                                  );

/** It configures the gain reduction.
    */
AS3933_status_t  AS3933_SetGainReduction                ( SPI_parameters_t mySPI_parameters, AS3933_r4_gr_value_t myGainReductionValue                                                                              );

/** It configures the operating frequency range.
    */
AS3933_status_t  AS3933_SetOperatingFrequencyRange      ( SPI_parameters_t mySPI_parameters, AS3933_r8_band_sel_value_t myOperatingFrequencyRange                                                                   );

/** It configures the frequency detection tolerance.
    */
AS3933_status_t  AS3933_SetFrequencyDetectionTolerance  ( SPI_parameters_t mySPI_parameters, AS3933_tolerance_settings_t myTolerance                                                                                );

/** It configures the +3dB gain boost.
    */
AS3933_status_t  AS3933_SetGainBoost                    ( SPI_parameters_t mySPI_parameters, AS3933_r2_g_boost_value_t myGainBoostMode                                                                              );

/** It configures the Automatic Gain Control ( AGC ).
    */
AS3933_status_t  AS3933_SetAGC                          ( SPI_parameters_t mySPI_parameters, AS3933_r1_agc_tlim_value_t myAGC_CarrierBurstMode, AS3933_r1_agc_ud_value_t myAGC_OperatingDirection                   );

/** It configures the Automatic Gain Control ( AGC ).
    */
AS3933_status_t  AS3933_SetAGC                          ( SPI_parameters_t mySPI_parameters, AS3933_r1_agc_tlim_value_t myAGC_CarrierBurstMode, AS3933_r1_agc_ud_value_t myAGC_OperatingDirection                   );

/** It configures the mask data before wakeup.
    */
AS3933_status_t  AS3933_SetDataMask                     ( SPI_parameters_t mySPI_parameters, AS3933_r0_dat_mask_value_t myDataMaskMode                                                                              );

/** It configures the correlator and the Manchester Decoder.
    */
AS3933_status_t  AS3933_SetCorrelator                   ( SPI_parameters_t mySPI_parameters, AS3933_r1_en_wpat_value_t myCorrelatorMode, AS3933_r0_patt32_value_t mySymbolPattern, AS3933_r7_t_hbit_value_t myRate,
                                                          AS3933_r1_en_manch_value_t myManchesterDecoderMode                                                                                                        );

/** It sets the wakeup pattern ( Manchester ).
    */
AS3933_status_t  AS3933_SetWakeUpPattern                ( SPI_parameters_t mySPI_parameters, AS3933_data_t myWakeUpPattern                                                                                          );

/** It sets the automatic time-out setup.
    */
AS3933_status_t  AS3933_SetAutomaticTimeOut             ( SPI_parameters_t mySPI_parameters, AS3933_r7_t_out_value_t myAutomaticTimeOut                                                                             );

/** It sets the parallel tuning capacitance on the chosen channel.
    */
AS3933_status_t  AS3933_SetParallelTuningCapacitance    ( SPI_parameters_t mySPI_parameters, AS3933_parallel_tuning_channels_t myChannel, AS3933_parallel_tuning_capacitance_t myAddedCapacitance                   );
