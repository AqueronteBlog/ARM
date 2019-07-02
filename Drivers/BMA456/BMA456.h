/**
 * @brief       BMA456.h
 * @details     Digital, triaxial acceleration sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/June/2019
 * @version     29/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  BMA456_ADDRESS_SDO_GND     =   0x18,       /*!<   I2C slave address byte, SDO = GND        */
  BMA456_ADDRESS_SDO_VDDIO   =   0x19        /*!<   I2C slave address byte, SDO = VDDIO      */
} BMA456_addresses_t;



/**
  * @brief   REGISTERS
  */
typedef enum
{
  BMA456_CHIP_ID          =   0x00,           /*!<  Chip ID                           */
  BMA456_ERR_REG          =   0x02,           /*!<  ERR_REG                           */
  BMA456_STATUS           =   0x03,           /*!<  Status                            */
  BMA456_DATA_0           =   0x0A,           /*!<  DATA0                             */
  BMA456_DATA_1           =   0x0B,           /*!<  DATA1                             */
  BMA456_DATA_2           =   0x0C,           /*!<  DATA2                             */
  BMA456_DATA_3           =   0x0D,           /*!<  DATA3                             */
  BMA456_DATA_4           =   0x0E,           /*!<  DATA4                             */
  BMA456_DATA_5           =   0x0F,           /*!<  DATA5                             */
  BMA456_DATA_6           =   0x10,           /*!<  DATA6                             */
  BMA456_DATA_7           =   0x11,           /*!<  DATA7                             */
  BMA456_DATA_8           =   0x12,           /*!<  DATA8                             */
  BMA456_DATA_9           =   0x13,           /*!<  DATA9                             */
  BMA456_DATA_10          =   0x14,           /*!<  DATA10                            */
  BMA456_DATA_11          =   0x15,           /*!<  DATA11                            */
  BMA456_DATA_12          =   0x16,           /*!<  DATA12                            */
  BMA456_DATA_13          =   0x17,           /*!<  DATA13                            */
  BMA456_SENSOR_TIME_0    =   0x18,           /*!<  SENSOR TIME 0                     */
  BMA456_SENSOR_TIME_1    =   0x19,           /*!<  SENSOR TIME 1                     */
  BMA456_SENSOR_TIME_2    =   0x1A,           /*!<  SENSOR TIME 2                     */
  BMA456_EVENT            =   0x1B,           /*!<  EVENT                             */
  BMA456_INT_STATUS_0     =   0x1C,           /*!<  INT STATUS 0                      */
  BMA456_INT_STATUS_1     =   0x1D,           /*!<  INT STATUS 1                      */
  BMA456_STEP_COUNTER_0   =   0x1E,           /*!<  STEP COUNTER 0                    */
  BMA456_STEP_COUNTER_1   =   0x1F,           /*!<  STEP COUNTER 1                    */
  BMA456_STEP_COUNTER_2   =   0x20,           /*!<  STEP COUNTER 2                    */
  BMA456_STEP_COUNTER_3   =   0x21,           /*!<  STEP COUNTER 3                    */
  BMA456_TEMPERATURE      =   0x22,           /*!<  TEMPERATURE                       */
  BMA456_FIFO_LENGTH_0    =   0x24,           /*!<  FIFO LENGHT 0                     */
  BMA456_FIFO_LENGTH_1    =   0x25,           /*!<  FIFO LENGHT 1                     */
  BMA456_FIFO_DATA        =   0x26,           /*!<  FIFO DATA                         */
  BMA456_ACTIVITY_TYPE    =   0x27,           /*!<  ACTIVITY TYPE                     */
  BMA456_INTERNAL_STATUS  =   0x2A,           /*!<  INTERNAL STATUS                   */
  BMA456_ACC_CONF         =   0x40,           /*!<  ACC CONF                          */
  BMA456_ACC_RANGE        =   0x41,           /*!<  ACC RANGE                         */
  BMA456_AUX_CONF         =   0x44,           /*!<  AUX CONF                          */
  BMA456_FIFO_DOWNS       =   0x45,           /*!<  FIFO DOWNS                        */
  BMA456_FIFO_WTM_0       =   0x46,           /*!<  FIFO WTM 0                        */
  BMA456_FIFO_WTM_1       =   0x47,           /*!<  FIFO WTM 1                        */
  BMA456_FIFO_CONFIG_0    =   0x48,           /*!<  FIFO CONFIG 0                     */
  BMA456_FIFO_CONFIG_1    =   0x49,           /*!<  FIFO CONFIG 1                     */
  BMA456_AUX_DEV_ID       =   0x4B,           /*!<  AUX DEV ID                        */
  BMA456_AUX_IF_CONF      =   0x4C,           /*!<  AUX IF CONF                       */
  BMA456_AUX_RD_ADDR      =   0x4D,           /*!<  AUX RD ADDR                       */
  BMA456_AUX_WR_ADDR      =   0x4E,           /*!<  AUX WR ADDR                       */
  BMA456_AUX_WR_DATA      =   0x4F,           /*!<  AUX WR DATA                       */
  BMA456_INT1_IO_CTRL     =   0x53,           /*!<  INT1 IO CTRL                      */
  BMA456_INT2_IO_CTRL     =   0x54,           /*!<  INT2 IO CTRL                      */
  BMA456_INT_LATCH        =   0x55,           /*!<  INT LATCH                         */
  BMA456_INT1_MAP         =   0x56,           /*!<  INT1 MAP                          */
  BMA456_INT2_MAP         =   0x57,           /*!<  INT2 MAP                          */
  BMA456_INT_MAP_DATA     =   0x58,           /*!<  INT MAP DATA                      */
  BMA456_INIT_CTRL        =   0x59,           /*!<  INIT CTRL                         */
  BMA456_FEATURES_IN      =   0x5E,           /*!<  FEATURES IN                       */
  BMA456_INTERNAL_ERROR   =   0x5F,           /*!<  INTERNAL ERROR                    */
  BMA456_NVM_CONF         =   0x6A,           /*!<  NVM CONF                          */
  BMA456_IF_CONF          =   0x6B,           /*!<  IF CONF                           */
  BMA456_ACC_SELF_TEST    =   0x6D,           /*!<  ACC SELF TEST                     */
  BMA456_NV_CONF          =   0x70,           /*!<  NV CONF                           */
  BMA456_OFFSET_0         =   0x71,           /*!<  OFFSET 0                          */
  BMA456_OFFSET_1         =   0x72,           /*!<  OFFSET 1                          */
  BMA456_OFFSET_2         =   0x73,           /*!<  OFFSET 2                          */
  BMA456_PWR_CONF         =   0x7C,           /*!<  PWR CONF                          */
  BMA456_PWR_CTRL         =   0x7D,           /*!<  PWR CTRL                          */
  BMA456_CMD              =   0x7E            /*!<  CMD                               */
} BMA456_registers_t;



/**
  * @brief   CHIP_ID. Chip identification code.
  */
typedef enum
{
    CHIP_ID_MASK         =   0x16             /*!<  Chip ID value                                 */
} BMA456_chip_id_t;


/**
  * @brief   ERR_REG. Reports sensor error conditions.
  */
/* AUX_ERR <7>
 *    NOTE: This flag will be reset when read.
 */
typedef enum
{
    ERR_REG_AUX_ERR_MASK      =   ( 1U << 7U ),   /*!<  AUX_ERR mask                                  */
    ERR_REG_AUX_ERR_ERROR     =   ( 1U << 7U ),   /*!<  Error in I2C-Master detected                  */
    ERR_REG_AUX_ERR_NO_ERROR  =   ( 0U << 7U )    /*!<  No Error in I2C-Master detected   [ Default ] */
} BMA456_err_reg_aux_err_t;


/* FIFO_ERR <6>
 *    NOTE: This flag will be reset when read.
 */
typedef enum
{
    ERR_REG_FIFO_ERR_MASK     =   ( 1U << 6U ),     /*!<  FIFO_ERR mask                                                   */
    ERR_REG_FIFO_ERR_ERROR    =   ( 1U << 6U ),     /*!<  Error in FIFO detected. Input data was discarded in stream mode */
    ERR_REG_FIFO_ERR_NO_ERROR =   ( 0U << 6U )      /*!<  No Error in FIFO detected                           [ Default ] */
} BMA456_err_reg_fifo_err_t;


/* ERROR_CODE <4:2>
 *    NOTE: Error codes for persistent errors.
 */
typedef enum
{
    ERR_REG_ERROR_CODE_MASK     =   ( 0b111 << 2U ), /*!<  ERROR_ERR mask                                                  */
    ERR_REG_ERROR_CODE_ACC_ERR  =   ( 0b001 << 2U ), /*!<  Error in register ACC_CONF                                      */
    ERR_REG_ERROR_CODE_NO_ERROR =   ( 0b000 << 2U )  /*!<  No error is reported                                [ Default ] */
} BMA456_err_reg_error_code_t;


/* CMD_ERR <1>
 *    NOTE: N/A
 */
typedef enum
{
    ERR_REG_CMD_ERR_MASK      =   ( 1U << 1U ),     /*!<  CMD_ERR mask                                                    */
    ERR_REG_CMD_ERR_ERROR     =   ( 1U << 1U ),     /*!<  Command execution failed                                        */
    ERR_REG_CMD_ERR_NO_ERROR  =   ( 0U << 1U )      /*!<  No error is reported                                [ Default ] */
} BMA456_err_reg_cmd_err_t;


/* FATAL_ERR <0>
 *    NOTE: This bit will be reset only by power-on-reset or softreset.
 */
typedef enum
{
    ERR_REG_FATAL_ERR_MASK      =   ( 1U << 0U ),    /*!<  FATAL_ERR mask                                                  */
    ERR_REG_FATAL_ERR_ERROR     =   ( 1U << 0U ),    /*!<  Chip is not in operation stable ( Boot, power system )          */
    ERR_REG_FATAL_ERR_NO_ERROR  =   ( 0U << 0U )     /*!<  No error is reported                                [ Default ] */
} BMA456_err_reg_fatal_err_t;


/**
  * @brief   STATUS. Sensor status flags.
  */
/* DRDY_ACC <7>
 *    NOTE: This flag will be reset when one accelerometer DATA register is read out.
 */
typedef enum
{
    STATUS_DRDY_ACC_MASK          =   ( 1U << 7U ),   /*!<  DRDY_ACC mask                                 */
    STATUS_DRDY_ACC_DATA_READY    =   ( 1U << 7U ),   /*!<  Data ready for accelerometer                  */
    STATUS_DRDY_ACC_DATA_NO_READY =   ( 0U << 7U )    /*!<  Data no ready for accelerometer   [ Default ] */
} BMA456_status_drdy_acc_t;


/* DRDY_AUX <5>
 *    NOTE: This flag will be reset when one auxiliary DATA register is read out.
 */
typedef enum
{
    STATUS_DRDY_AUX_MASK          =   ( 1U << 5U ),   /*!<  DRDY_AUX mask                                     */
    STATUS_DRDY_AUX_DATA_READY    =   ( 1U << 5U ),   /*!<  Data ready for auxiliary sensor                   */
    STATUS_DRDY_AUX_DATA_NO_READY =   ( 0U << 5U )    /*!<  Data no ready for auxiliary sensor    [ Default ] */
} BMA456_status_drdy_aux_t;


/* CMD_RDY <4>
 *    NOTE: N/A.
 */
typedef enum
{
    STATUS_CMD_RDY_MASK                 =   ( 1U << 4U ),   /*!<  CMD_RDY mask                                      */
    STATUS_CMD_RDY_COMMAND_READY        =   ( 1U << 4U ),   /*!<  Command ready to accept a new command [ Default ] */
    STATUS_CMD_RDY_COMMAND_IN_PROGRESS  =   ( 0U << 4U )    /*!<  Command in progress                               */
} BMA456_status_cmd_rdy_t;


/* AUX_MAN_OP <2>
 *    NOTE: N/A.
 */
typedef enum
{
    STATUS_AUX_MAN_OP_MASK                =   ( 1U << 2U ), /*!<  AUX_MAN_OP mask                                                */
    STATUS_AUX_MAN_OP_MANUAL_INTERFACE    =   ( 1U << 2U ), /*!<  Manual auxiliary interface operation is ongoing                */
    STATUS_AUX_MAN_OP_NO_MANUAL_INTERFACE =   ( 0U << 2U )  /*!<  No Manual auxiliary interface operation is ongoing [ Default ] */
} BMA456_status_aux_man_op_t;


/**
  * @brief   EVENT. Sensor status flags.
  */
/* POR_DETECTED <0>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    EVENT_POR_DETECTED_MASK       =   ( 1U << 0U ),   /*!<  POR_DETECTED mask                             */
    EVENT_POR_DETECTED_HIGH       =   ( 1U << 0U ),   /*!<  After device power up or softreset[ Default ] */
    EVENT_POR_DETECTED_LOW        =   ( 0U << 0U )    /*!<  Low value                                     */
} BMA456_event_por_detected_t;


/**
  * @brief   INT_STATUS_0. Interrupt/Feature status.
  */
/* ERROR_INT_OUT <7>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_0_ERROR_INT_OUT_MASK =   ( 1U << 7U ),   /*!<  ERROR_INT_OUT mask                            */
    INT_STATUS_0_ERROR_INT_OUT_HIGH =   ( 1U << 7U ),   /*!<  Error interrupt out detected                  */
    INT_STATUS_0_ERROR_INT_OUT_LOW  =   ( 0U << 7U )    /*!<  Error interrupt out not detected  [ Default ] */
} BMA456_int_status_0_error_int_out_t;


/* ANY_NO_MOTION_OUT <6>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_0_ANY_NO_MOTION_OUT_MASK =   ( 1U << 6U ), /*!<  ANY_NO_MOTION_OUT mask                          */
    INT_STATUS_0_ANY_NO_MOTION_OUT_HIGH =   ( 1U << 6U ), /*!<  Any-motion detection output detected            */
    INT_STATUS_0_ANY_NO_MOTION_OUT_LOW  =   ( 0U << 6U )  /*!<  No-motion detection output detected [ Default ] */
} BMA456_int_status_0_any_no_motion_out_t;


/* WAKEUP_OUT <5>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_0_WAKEUP_OUT_MASK    =   ( 1U << 5U ),     /*!<  WAKEUP_OUT mask                                 */
    INT_STATUS_0_WAKEUP_OUT_HIGH    =   ( 1U << 5U ),     /*!<  Wakeup output detected                          */
    INT_STATUS_0_WAKEUP_OUT_LOW     =   ( 0U << 5U )      /*!<  Wakeup output no detected           [ Default ] */
} BMA456_int_status_0_wakeup_out_t;


/* WRIST_TILT_OUT <3>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_0_WRIST_TILT_OUT_MASK    =   ( 1U << 3U ),   /*!<  WRIST_TILT_OUT mask                             */
    INT_STATUS_0_WRIST_TILT_OUT_HIGH    =   ( 1U << 3U ),   /*!<  Wrist tilt output detected                      */
    INT_STATUS_0_WRIST_TILT_OUT_LOW     =   ( 0U << 3U )    /*!<  Wrist tilt output no detected       [ Default ] */
} BMA456_int_status_0_wrist_tilt_out_t;


/* ACTIVITY_TYPE_OUT <2>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_0_ACTIVITY_TYPE_OUT_MASK    =   ( 1U << 2U ),  /*!<  ACTIVITY_TYPE_OUT mask                                */
    INT_STATUS_0_ACTIVITY_TYPE_OUT_HIGH    =   ( 1U << 2U ),  /*!<  Step counter activity output detected                 */
    INT_STATUS_0_ACTIVITY_TYPE_OUT_LOW     =   ( 0U << 2U )   /*!<  Step counter activity output no detected  [ Default ] */
} BMA456_int_status_0_activity_type_out_t;


/* STEP_COUNTER_OUT <1>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_0_STEP_COUNTER_OUT_MASK    =   ( 1U << 1U ),   /*!<  STEP_COUNTER_OUT mask                                                   */
    INT_STATUS_0_STEP_COUNTER_OUT_HIGH    =   ( 1U << 1U ),   /*!<  Step-counter watermark or step-detector output detected                 */
    INT_STATUS_0_STEP_COUNTER_OUT_LOW     =   ( 0U << 1U )    /*!<  Step-counter watermark or step-detector output no detected  [ Default ] */
} BMA456_int_status_0_step_counter_out_t;


/**
  * @brief   INT_STATUS_1. Interrupt status.
  */
/* ACC_DRDY_INT <7>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_1_ACC_DRDY_INT_MASK =   ( 1U << 7U ),   /*!<  ACC_DRDY_INT mask                                  */
    INT_STATUS_1_ACC_DRDY_INT_HIGH =   ( 1U << 7U ),   /*!<  Accelerometer data ready interrupt                 */
    INT_STATUS_1_ACC_DRDY_INT_LOW  =   ( 0U << 7U )    /*!<  Accelerometer data not ready interrupt [ Default ] */
} BMA456_int_status_1_acc_drdy_int_t;


/* AUX_DRDY_INT <5>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_1_AUX_DRDY_INT_MASK =   ( 1U << 5U ),   /*!<  AUX_DRDY_INT mask                                      */
    INT_STATUS_1_AUX_DRDY_INT_HIGH =   ( 1U << 5U ),   /*!<  Auxiliary sensor data ready interrupt                  */
    INT_STATUS_1_AUX_DRDY_INT_LOW  =   ( 0U << 5U )    /*!<  Auxiliary sensor data not ready interrupt  [ Default ] */
} BMA456_int_status_1_aux_drdy_int_t;


/* FWM_INT <1>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_1_FWM_INT_MASK =   ( 1U << 1U ),   /*!<  FWM_INT mask                                       */
    INT_STATUS_1_FWM_INT_HIGH =   ( 1U << 1U ),   /*!<  FIFO watermark interrupt detected                  */
    INT_STATUS_1_FWM_INT_LOW  =   ( 0U << 1U )    /*!<  FIFO watermark interrupt not detected  [ Default ] */
} BMA456_int_status_1_fwm_int_t;


/* FFULL_INT <0>
 *    NOTE: Clear-on-read.
 */
typedef enum
{
    INT_STATUS_1_FFULL_INT_MASK =   ( 1U << 0U ),   /*!<  FFULL_INT mask                                    */
    INT_STATUS_1_FFULL_INT_HIGH =   ( 1U << 0U ),   /*!<  FIFO full interrupt detected                      */
    INT_STATUS_1_FFULL_INT_LOW  =   ( 0U << 0U )    /*!<  FIFO full interrupt not detected      [ Default ] */
} BMA456_int_status_1_ffull_int_t;


/**
  * @brief   ACTIVITY_TYPE. Step couter activity output ( Running, walking, still ).
  */
/* ACTIVITY_TYPE_OUT <1:0>
 *    NOTE: N/A.
 */
typedef enum
{
    ACTIVITY_TYPE_ACTIVITY_TYPE_OUT_MASK    =   ( 0b11 << 0U ), /*!<  ACTIVITY_TYPE_OUT mask                              */
    ACTIVITY_TYPE_ACTIVITY_TYPE_OUT_STILL   =   ( 0b00 << 0U ), /*!<  User not moving                         [ Default ] */
    ACTIVITY_TYPE_ACTIVITY_TYPE_OUT_WALKING =   ( 0b01 << 0U ), /*!<  User walking                                        */
    ACTIVITY_TYPE_ACTIVITY_TYPE_OUT_RUNNING =   ( 0b10 << 0U ), /*!<  User running                                        */
    ACTIVITY_TYPE_ACTIVITY_TYPE_OUT_UNKNOWN =   ( 0b11 << 0U )  /*!<  Unknown state                                       */
} BMA456_activity_type_activity_type_out_t;


/**
  * @brief   INTERNAL_STATUS. Error bits and message indicating internal status.
  */
/* ODR_HIGH_ERROR <7>
 *    NOTE: The minimum bandwidth conditions are not respected for the wakeup detection.
 */
typedef enum
{
    INTERNAL_STATUS_ODR_HIGH_ERROR_MASK   =   ( 1U << 7U ),     /*!<  ODR_HIGH_ERROR mask                              */
    INTERNAL_STATUS_ODR_HIGH_ERROR_LOW    =   ( 0U << 7U ),     /*!<  The conditions are respected         [ Default ] */
    INTERNAL_STATUS_ODR_HIGH_ERROR_HIGH   =   ( 1U << 7U )      /*!<  The conditions are not respected                 */
} BMA456_internal_status_odr_high_error_t;


/* ODR_50HZ_ERROR <6>
 *    NOTE: The minimum bandwidth conditions are not respected for the features which require 50 Hz data.
 */
typedef enum
{
    INTERNAL_STATUS_ODR_50HZ_ERROR_MASK   =   ( 1U << 6U ),     /*!<  ODR_50HZ_ERROR mask                              */
    INTERNAL_STATUS_ODR_50HZ_ERROR_LOW    =   ( 0U << 6U ),     /*!<  The conditions are respected         [ Default ] */
    INTERNAL_STATUS_ODR_50HZ_ERROR_HIGH   =   ( 1U << 6U )      /*!<  The conditions are not respected                 */
} BMA456_internal_status_odr_50hz_error_t;


/* AXES_REMAP_ERROR <5>
 *    NOTE: Axes remapped wrongly because a source axis is not assigned to more than one target axis.
 */
typedef enum
{
    INTERNAL_STATUS_AXES_REMAP_ERROR_MASK =   ( 1U << 5U ),     /*!<  AXES_REMAP_ERROR mask                            */
    INTERNAL_STATUS_AXES_REMAP_ERROR_LOW  =   ( 0U << 5U ),     /*!<  Axes mapped correctly                [ Default ] */
    INTERNAL_STATUS_AXES_REMAP_ERROR_HIGH =   ( 1U << 5U )      /*!<  Axes mapped wrongly                              */
} BMA456_internal_status_axes_remap_error_t;


/* MESSAGE <4:0>
 *    NOTE: Axes remapped wrongly because a source axis is not assigned to more than one target axis.
 */
typedef enum
{
    INTERNAL_STATUS_MESSAGE_MASK      =   ( 0b11111 << 0U ),     /*!<  MESSAGE mask                                     */
    INTERNAL_STATUS_MESSAGE_NOT_INIT  =   ( 0b00000 << 0U ),     /*!<  ASIC is not initializef              [ Default ] */
    INTERNAL_STATUS_MESSAGE_INIT_OK   =   ( 0b00001 << 0U ),     /*!<  ASIC initialized                                 */
    INTERNAL_STATUS_MESSAGE_INIT_ERR  =   ( 0b00010 << 0U ),     /*!<  Initialization error                             */
    INTERNAL_STATUS_MESSAGE_DRV_ERR   =   ( 0b00011 << 0U ),     /*!<  Invalid driver                                   */
    INTERNAL_STATUS_MESSAGE_SNS_STOP  =   ( 0b00100 << 0U )      /*!<  Sensor stopped                                   */
} BMA456_internal_status_message_t;


/**
  * @brief   ACC_CONF. Sets the output data rate, the bandwidth, and the read mode of the acceleration sensor.
  */
/* ACC_PERF_MODE <7>
 *    NOTE: Select accelerometer filter performance mode.
 */
typedef enum
{
    ACC_CONF_ACC_PERF_MODE_MASK     =   ( 1U << 7U ),     /*!<  ACC_PERF_MODE mask                              */
    ACC_CONF_ACC_PERF_MODE_CIC_AVG  =   ( 0U << 7U ),     /*!<  Averaging mode                                  */
    ACC_CONF_ACC_PERF_MODE_CONT     =   ( 1U << 7U )      /*!<  Continuous filter function          [ Default ] */
} BMA456_acc_conf_acc_perf_mode_t;


/* ACC_BWP <6:4>
 *    NOTE: Bandwidth parameters, determines filter configuration (acc_perf_mode = 1) and averaging for undersampling mode (acc_perf_mode = 0).
 */
typedef enum
{
    ACC_CONF_ACC_BWP_MASK       =   ( 0b111 << 4U ),     /*!<  ACC_BWP mask                                                                   */
    ACC_CONF_ACC_BWP_OSR4_AVG1  =   ( 0b000 << 4U ),     /*!<  acc_perf_mode=1 : OSR4 mode; acc_perf_mode=0 : no averaging                    */
    ACC_CONF_ACC_BWP_OSR2_AVG2  =   ( 0b001 << 4U ),     /*!<  acc_perf_mode=1 : OSR2 mode; acc_perf_mode=0 : average 2 samples               */
    ACC_CONF_ACC_BWP_NORM_AVG4  =   ( 0b010 << 4U ),     /*!<  acc_perf_mode=1 : normal mode; acc_perf_mode=0 : average 4 samples [ Default ] */
    ACC_CONF_ACC_BWP_CIC_AVG8   =   ( 0b011 << 4U ),     /*!<  acc_perf_mode=1 : reserved; acc_perf_mode=0 : average 8 samples                */
    ACC_CONF_ACC_BWP_RES_AVG16  =   ( 0b100 << 4U ),     /*!<  acc_perf_mode=1 : reserved; acc_perf_mode=0 : average 16 samples               */
    ACC_CONF_ACC_BWP_RES_AVG32  =   ( 0b101 << 4U ),     /*!<  acc_perf_mode=1 : reserved; acc_perf_mode=0 : average 32 samples               */
    ACC_CONF_ACC_BWP_RES_AVG64  =   ( 0b110 << 4U ),     /*!<  acc_perf_mode=1 : reserved; acc_perf_mode=0 : average 64 samples               */
    ACC_CONF_ACC_BWP_RES_AVG128 =   ( 0b111 << 4U )      /*!<  acc_perf_mode=1 : reserved; acc_perf_mode=0 : average 128 samples              */
} BMA456_acc_conf_acc_bwp_t;


/* ACC_ODR <3:0>
 *    NOTE: ODR in Hz. The output data rate is independent of the power ode setting for the sensor, but not all settings are supported in all power modes.
 */
typedef enum
{
    ACC_CONF_ACC_ODR_MASK       =   ( 0b1111 << 0U ),     /*!<  ACC_ODR mask                                                                  */
    ACC_CONF_ACC_ODR_ODR_0P78   =   ( 0b0001 << 0U ),     /*!<  ACC ODR: 25/32                                                                */
    ACC_CONF_ACC_ODR_ODR_1P5    =   ( 0b0010 << 0U ),     /*!<  ACC ODR: 25/16                                                                */
    ACC_CONF_ACC_ODR_ODR_3P1    =   ( 0b0011 << 0U ),     /*!<  ACC ODR: 25/8                                                                 */
    ACC_CONF_ACC_ODR_ODR_6P25   =   ( 0b0100 << 0U ),     /*!<  ACC ODR: 25/4                                                                 */
    ACC_CONF_ACC_ODR_ODR_12P5   =   ( 0b0101 << 0U ),     /*!<  ACC ODR: 25/2                                                                 */
    ACC_CONF_ACC_ODR_ODR_25     =   ( 0b0110 << 0U ),     /*!<  ACC ODR: 25                                                                   */
    ACC_CONF_ACC_ODR_ODR_50     =   ( 0b0111 << 0U ),     /*!<  ACC ODR: 50                                                                   */
    ACC_CONF_ACC_ODR_ODR_100    =   ( 0b1000 << 0U ),     /*!<  ACC ODR: 100                                                      [ Default ] */
    ACC_CONF_ACC_ODR_ODR_200    =   ( 0b1001 << 0U ),     /*!<  ACC ODR: 200                                                                  */
    ACC_CONF_ACC_ODR_ODR_400    =   ( 0b1010 << 0U ),     /*!<  ACC ODR: 400                                                                  */
    ACC_CONF_ACC_ODR_ODR_800    =   ( 0b1011 << 0U ),     /*!<  ACC ODR: 800                                                                  */
    ACC_CONF_ACC_ODR_ODR_1K6    =   ( 0b1100 << 0U )      /*!<  ACC ODR: 1600                                                                 */
} BMA456_acc_conf_acc_odr_t;


/**
  * @brief   ACC_RANGE. Selection of the accelerometer g-range.
  */
/* ACC_RANGE <1:0>
 *    NOTE: Accelerometer g-range.
 */
typedef enum
{
    ACC_RANGE_ACC_RANGE_MASK      =   ( 0b11 << 0U ),   /*!<  ACC_RANGE mask                                    */
    ACC_RANGE_ACC_RANGE_RANGE_2G  =   ( 0b00 << 0U ),   /*!<  +/- 2g                                            */
    ACC_RANGE_ACC_RANGE_RANGE_4G  =   ( 0b01 << 0U ),   /*!<  +/- 4g                                [ Default ] */
    ACC_RANGE_ACC_RANGE_RANGE_8G  =   ( 0b10 << 0U ),   /*!<  +/- 8g                                            */
    ACC_RANGE_ACC_RANGE_RANGE_16G =   ( 0b11 << 0U )    /*!<  +/- 16g                                           */
} BMA456_acc_range_acc_acc_range_t;


/**
  * @brief   AUX_CONF. Sets the output data rate of the auxiliary interface.
  */
/* AUX_OFFSET <7:4>
 *    NOTE: Trigger-readout offset in units of 2.5ms. If set to zero, the offset is maximum (i.e. after readout a trigger is issued inmediately)
 */
typedef enum
{
    AUX_CONF_AUX_OFFSET_MASK      =   ( 0b1111 << 4U )  /*!<  AUX_OFFSET mask                                  */
} BMA456_aux_conf_aux_offset_t;


/* AUX_ODR <3:0>
 *    NOTE: Select the poll rate for the sensor attached to the auxiliary interface.
 */
typedef enum
{
    AUX_CONF_AUX_ODR_MASK       =   ( 0b1111 << 0U ),   /*!<  AUX_ODR mask                                                                  */
    AUX_CONF_AUX_ODR_ODR_0P78   =   ( 0b0001 << 0U ),   /*!<  AUX ODR: 25/32                                                                */
    AUX_CONF_AUX_ODR_ODR_1P5    =   ( 0b0010 << 0U ),   /*!<  AUX ODR: 25/16                                                                */
    AUX_CONF_AUX_ODR_ODR_3P1    =   ( 0b0011 << 0U ),   /*!<  AUX ODR: 25/8                                                                 */
    AUX_CONF_AUX_ODR_ODR_6P25   =   ( 0b0100 << 0U ),   /*!<  AUX ODR: 25/4                                                                 */
    AUX_CONF_AUX_ODR_ODR_12P5   =   ( 0b0101 << 0U ),   /*!<  AUX ODR: 25/2                                                                 */
    AUX_CONF_AUX_ODR_ODR_25     =   ( 0b0110 << 0U ),   /*!<  AUX ODR: 25                                                       [ Default ] */
    AUX_CONF_AUX_ODR_ODR_50     =   ( 0b0111 << 0U ),   /*!<  AUX ODR: 50                                                                   */
    AUX_CONF_AUX_ODR_ODR_100    =   ( 0b1000 << 0U ),   /*!<  AUX ODR: 100                                                                  */
    AUX_CONF_AUX_ODR_ODR_200    =   ( 0b1001 << 0U ),   /*!<  AUX ODR: 200                                                                  */
    AUX_CONF_AUX_ODR_ODR_400    =   ( 0b1010 << 0U ),   /*!<  AUX ODR: 400                                                                  */
    AUX_CONF_AUX_ODR_ODR_800    =   ( 0b1011 << 0U )    /*!<  AUX ODR: 800                                                                  */
} BMA456_aux_conf_aux_odr_t;


/**
  * @brief   FIFO_DOWNS. Configure accelerometer downsampling rates for FIFO.
  */
/* ACC_FIFO_FILT_DATA <7>
 *    NOTE: Selects filtered or unfiltered accelerometer data for FIFO.
 */
typedef enum
{
    FIFO_DOWNS_ACC_FIFO_FILT_DATA_MASK        =   ( 1U << 7U ),  /*!<  ACC_FIFO_FILT_DATA mask                  */
    FIFO_DOWNS_ACC_FIFO_FILT_DATA_UNFILTERED  =   ( 0U << 7U ),  /*!<  Unfiltered data                          */
    FIFO_DOWNS_ACC_FIFO_FILT_DATA_FILTERED    =   ( 1U << 7U )   /*!<  Filtered data                [ Default ] */
} BMA456_fifo_downs_acc_fifo_filt_data_t;


/* ACC_FIFO_DOWNS <6:4>
 *    NOTE: Downsampling for accelerometer data (2^acc_fifo_downs).
 */
typedef enum
{
    FIFO_DOWNS_ACC_FIFO_DOWNS_MASK        =   ( 0b111 << 4U )     /*!<  ACC_FIFO_FILT_DATA mask                  */
} BMA456_fifo_downs_acc_fifo_downs_t;


/**
  * @brief   FIFO_CONFIG_0. FIFO frame content configuration.
  */
/* FIFO_TIME_EN <1>
 *    NOTE: Return sensortime frame after the last valid data frame.
 */
typedef enum
{
    FIFO_CONFIG_0_FIFO_TIME_EN_MASK       =   ( 1U << 1U ),       /*!<  FIFO_TIME_EN mask                                */
    FIFO_CONFIG_0_FIFO_TIME_EN_DISABLE    =   ( 0U << 1U ),       /*!<  Do not return sensortime frame                   */
    FIFO_CONFIG_0_FIFO_TIME_EN_ENABLE     =   ( 1U << 1U )        /*!<  Return sensortime frane              [ Default ] */
} BMA456_fifo_config_0_fifo_time_en_t;


/* FIFO_STOP_ON_FULL <0>
 *    NOTE: Stop writing samples into FIFO when FIFO is full.
 */
typedef enum
{
    FIFO_CONFIG_0_FIFO_STOP_ON_FULL_MASK       =   ( 1U << 0U ),  /*!<  FIFO_STOP_ON_FULL mask                            */
    FIFO_CONFIG_0_FIFO_STOP_ON_FULL_DISABLE    =   ( 0U << 0U ),  /*!<  Do not stop writing to FIFO when full [ Default ] */
    FIFO_CONFIG_0_FIFO_STOP_ON_FULL_ENABLE     =   ( 1U << 0U )   /*!<  Stop writing into FIFO when full                  */
} BMA456_fifo_config_0_fifo_stop_on_full_t;












#ifndef BMA456_VECTOR_STRUCT_H
#define BMA456_VECTOR_STRUCT_H
typedef struct
{
  /* Output registers  */
  uint16_t  aux_x;                            /*!<  Accelerometer: Aux_X              */
  uint16_t  aux_y;                            /*!<  Accelerometer: Aux_Y              */
  uint16_t  aux_z;                            /*!<  Accelerometer: Aux_Z              */
  uint16_t  aux_r;                            /*!<  Accelerometer: Aux_R              */

  uint16_t  acc_x;                            /*!<  Accelerometer: Acc_X              */
  uint16_t  acc_y;                            /*!<  Accelerometer: Acc_Y              */
  uint16_t  acc_z;                            /*!<  Accelerometer: Acc_Z              */
  
  uint16_t  sensor_time;                      /*!<  Sensor time                       */
  uint32_t  step_counter;                     /*!<  Step counting value               */
  
  int8_t    temperature;                      /*!<  Temperature value of the sensor   */
  
  uint16_t  fifo_byte_counter;                /*!<  FIFO counter                      */
  uint8_t   fifo_data;                        /*!<  FIFO read data                    */



  /* Device identification   */
  uint8_t                       deviceID;     /*!<  Device ID                                         */
} BMA456_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    BMA456_SUCCESS     =       0,
    BMA456_FAILURE     =       1
} BMA456_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
BMA456_status_t BMA456_Init                     ( I2C_parameters_t myI2Cparameters                                        );

