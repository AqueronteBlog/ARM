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


/**
  * @brief   FIFO_CONFIG_1. FIFO frame content configuration.
  */
/* FIFO_ACC_EN <6>
 *    NOTE: Store accelerometer data in FIFO (all 3 axes).
 */
typedef enum
{
    FIFO_CONFIG_1_FIFO_ACC_EN_MASK        =   ( 1U << 6U ),       /*!<  FIFO_ACC_EN mask                                  */
    FIFO_CONFIG_1_FIFO_ACC_EN_DISABLE     =   ( 0U << 6U ),       /*!<  No accelerometer data is stored       [ Default ] */
    FIFO_CONFIG_1_FIFO_ACC_EN_ENABLE      =   ( 1U << 6U )        /*!<  Accelerometer data is stored                      */
} BMA456_fifo_config_1_fifo_acc_en_t;


/* FIFO_AUX_EN <5>
 *    NOTE: Store auxiliary data in FIFO (all 3 axes).
 */
typedef enum
{
    FIFO_CONFIG_1_FIFO_AUX_EN_MASK        =   ( 1U << 5U ),       /*!<  FIFO_AUX_EN mask                                  */
    FIFO_CONFIG_1_FIFO_AUX_EN_DISABLE     =   ( 0U << 5U ),       /*!<  No auxiliary data is stored           [ Default ] */
    FIFO_CONFIG_1_FIFO_AUX_EN_ENABLE      =   ( 1U << 5U )        /*!<  Auxiliary data is stored                          */
} BMA456_fifo_config_1_fifo_aux_en_t;


/* FIFO_HEADER_EN <4>
 *    NOTE: FIFO frame header enable.
 */
typedef enum
{
    FIFO_CONFIG_1_FIFO_HEADER_EN_MASK     =   ( 1U << 4U ),       /*!<  FIFO_HEADER_EN mask                               */
    FIFO_CONFIG_1_FIFO_HEADER_EN_DISABLE  =   ( 0U << 4U ),       /*!<  No header is stored                               */
    FIFO_CONFIG_1_FIFO_HEADER_EN_ENABLE   =   ( 1U << 4U )        /*!<  Header is stored                      [ Default ] */
} BMA456_fifo_config_1_fifo_header_en_t;


/* FIFO_TAG_INT1_EN <3>
 *    NOTE: FIFO interrupt 1 tag enable.
 */
typedef enum
{
    FIFO_CONFIG_1_FIFO_TAG_INT1_EN_MASK     =   ( 1U << 3U ),     /*!<  FIFO_TAG_INT1_EN mask                             */
    FIFO_CONFIG_1_FIFO_TAG_INT1_EN_DISABLE  =   ( 0U << 3U ),     /*!<  Disable tag                           [ Default ] */
    FIFO_CONFIG_1_FIFO_TAG_INT1_EN_ENABLE   =   ( 1U << 3U )      /*!<  Enable tag                                        */
} BMA456_fifo_config_1_fifo_tag_int1_en_t;


/* FIFO_TAG_INT2_EN <2>
 *    NOTE: FIFO interrupt 2 tag enable.
 */
typedef enum
{
    FIFO_CONFIG_1_FIFO_TAG_INT2_EN_MASK     =   ( 1U << 2U ),     /*!<  FIFO_TAG_INT2_EN mask                             */
    FIFO_CONFIG_1_FIFO_TAG_INT2_EN_DISABLE  =   ( 0U << 2U ),     /*!<  Disable tag                           [ Default ] */
    FIFO_CONFIG_1_FIFO_TAG_INT2_EN_ENABLE   =   ( 1U << 2U )      /*!<  Enable tag                                        */
} BMA456_fifo_config_1_fifo_tag_int2_en_t;


/**
  * @brief   AUX_DEV_ID. Auxiliary interface slave device ID.
  */
/* I2C_DEVICE_ADDR <7:1>
 *    NOTE: I2C device address of auxiliary slave.
 */
typedef enum
{
    AUX_DEV_ID_I2C_DEVICE_ADDR_MASK        =   ( 0b1111111 << 1U )  /*!<  I2C_DEVICE_ADDR mask                              */
} BMA456_aux_dev_id_i2c_device_addr_t;


/**
  * @brief   AUX_IF_CONF. Auxiliary interface configuration.
  */
/* AUX_MANUAL_EN <7>
 *    NOTE: Enable auxiliary interface manual mode.
 */
typedef enum
{
    AUX_IF_CONF_AUX_MANUAL_EN_MASK      =   ( 1U << 7U ),       /*!<  AUX_MANUAL_EN mask                                */
    AUX_IF_CONF_AUX_MANUAL_EN_DISABLE   =   ( 0U << 7U ),       /*!<  Data mode                                         */
    AUX_IF_CONF_AUX_MANUAL_EN_ENABLE    =   ( 1U << 7U )        /*!<  Setup mode                            [ Default ] */
} BMA456_aux_if_conf_aux_manual_en_t;


/* AUX_RD_BURST <1:0>
 *    NOTE: Burst data length (1, 2, 6, 8 byte).
 */
typedef enum
{
    AUX_IF_CONF_AUX_RD_BURST_MASK       =   ( 0b11 << 0U ),     /*!<  AUX_RD_BURST mask                                 */
    AUX_IF_CONF_AUX_RD_BURST_BL1        =   ( 0b00 << 0U ),     /*!<  Burst length 1                                    */
    AUX_IF_CONF_AUX_RD_BURST_BL2        =   ( 0b01 << 0U ),     /*!<  Burst length 2                                    */
    AUX_IF_CONF_AUX_RD_BURST_BL6        =   ( 0b10 << 0U ),     /*!<  Burst length 6                                    */
    AUX_IF_CONF_AUX_RD_BURST_BL8        =   ( 0b11 << 0U )      /*!<  Burst length 8                        [ Default ] */
} BMA456_aux_if_conf_aux_rd_burst_t;


/**
  * @brief   INT1_IO_CTRL. Configure the electrical behaviour of the interrupt pins.
  */
/* INPUT_EN <4>
 *    NOTE: Input enable for INT1 pin.
 */
typedef enum
{
    INT1_IO_CTRL_INPUT_EN_MASK      =   ( 1U << 4U ),       /*!<  INPUT_EN mask                                     */
    INT1_IO_CTRL_INPUT_EN_OFF       =   ( 0U << 4U ),       /*!<  Input disabled                        [ Default ] */
    INT1_IO_CTRL_INPUT_EN_ON        =   ( 1U << 4U )        /*!<  Input enabled                                     */
} BMA456_int1_io_ctrl_input_en_t;


/* OUTPUT_EN <3>
 *    NOTE: Output enable for INT1 pin.
 */
typedef enum
{
    INT1_IO_CTRL_OUTPUT_EN_MASK     =   ( 1U << 3U ),       /*!<  OUTPUT_EN mask                                    */
    INT1_IO_CTRL_OUTPUT_EN_OFF      =   ( 0U << 3U ),       /*!<  Output disabled                       [ Default ] */
    INT1_IO_CTRL_OUTPUT_EN_ON       =   ( 1U << 3U )        /*!<  Output enabled                                    */
} BMA456_int1_io_ctrl_output_en_t;


/* OD <2>
 *    NOTE: Configure behaviour of INT1 pin to open drain.
 */
typedef enum
{   
    INT1_IO_CTRL_OD_MASK            =   ( 1U << 2U ),       /*!<  OD mask                                           */
    INT1_IO_CTRL_OD_PUSH_PULL       =   ( 0U << 2U ),       /*!<  Push-pull                             [ Default ] */
    INT1_IO_CTRL_OD_OPEN_DRAIN      =   ( 1U << 2U )        /*!<  Open drain                                        */
} BMA456_int1_io_ctrl_od_t;


/* LVL <1>
 *    NOTE: Configure level of INT1 pin.
 */
typedef enum
{   
    INT1_IO_CTRL_LVL_MASK           =   ( 1U << 1U ),       /*!<  LVL mask                                          */
    INT1_IO_CTRL_LVL_ACTIVE_LOW     =   ( 0U << 1U ),       /*!<  Active low                            [ Default ] */
    INT1_IO_CTRL_LVL_ACTIVE_HIGH    =   ( 1U << 1U )        /*!<  Active high                                       */
} BMA456_int1_io_ctrl_lvl_t;


/* EDGE_CTRL <0>
 *    NOTE: Configure trigger condition of INT1 pin (input).
 */
typedef enum
{   
    INT1_IO_CTRL_EDGE_CTRL_MASK     =   ( 1U << 0U ),       /*!<  EDGE_CTRL mask                                    */
    INT1_IO_CTRL_EDGE_CTRL_LEVEL_TR =   ( 0U << 0U ),       /*!<  Level                                 [ Default ] */
    INT1_IO_CTRL_EDGE_CTRL_EDGE_TR  =   ( 1U << 0U )        /*!<  Edge                                              */
} BMA456_int1_io_ctrl_edge_ctrl_t;


/**
  * @brief   INT2_IO_CTRL. Configure the electrical behaviour of the interrupt pins.
  */
/* INPUT_EN <4>
 *    NOTE: Input enable for INT2 pin.
 */
typedef enum
{
    INT2_IO_CTRL_INPUT_EN_MASK      =   ( 1U << 4U ),       /*!<  INPUT_EN mask                                     */
    INT2_IO_CTRL_INPUT_EN_OFF       =   ( 0U << 4U ),       /*!<  Input disabled                        [ Default ] */
    INT2_IO_CTRL_INPUT_EN_ON        =   ( 1U << 4U )        /*!<  Input enabled                                     */
} BMA456_int2_io_ctrl_input_en_t;


/* OUTPUT_EN <3>
 *    NOTE: Output enable for INT2 pin.
 */
typedef enum
{
    INT2_IO_CTRL_OUTPUT_EN_MASK     =   ( 1U << 3U ),       /*!<  OUTPUT_EN mask                                    */
    INT2_IO_CTRL_OUTPUT_EN_OFF      =   ( 0U << 3U ),       /*!<  Output disabled                       [ Default ] */
    INT2_IO_CTRL_OUTPUT_EN_ON       =   ( 1U << 3U )        /*!<  Output enabled                                    */
} BMA456_int2_io_ctrl_output_en_t;


/* OD <2>
 *    NOTE: Configure behaviour of INT2 pin to open drain.
 */
typedef enum
{   
    INT2_IO_CTRL_OD_MASK            =   ( 1U << 2U ),       /*!<  OD mask                                           */
    INT2_IO_CTRL_OD_PUSH_PULL       =   ( 0U << 2U ),       /*!<  Push-pull                             [ Default ] */
    INT2_IO_CTRL_OD_OPEN_DRAIN      =   ( 1U << 2U )        /*!<  Open drain                                        */
} BMA456_int2_io_ctrl_od_t;


/* LVL <1>
 *    NOTE: Configure level of INT2 pin.
 */
typedef enum
{   
    INT2_IO_CTRL_LVL_MASK           =   ( 1U << 1U ),       /*!<  LVL mask                                          */
    INT2_IO_CTRL_LVL_ACTIVE_LOW     =   ( 0U << 1U ),       /*!<  Active low                            [ Default ] */
    INT2_IO_CTRL_LVL_ACTIVE_HIGH    =   ( 1U << 1U )        /*!<  Active high                                       */
} BMA456_int2_io_ctrl_lvl_t;


/* EDGE_CTRL <0>
 *    NOTE: Configure trigger condition of INT2 pin (input).
 */
typedef enum
{   
    INT2_IO_CTRL_EDGE_CTRL_MASK     =   ( 1U << 0U ),       /*!<  EDGE_CTRL mask                                    */
    INT2_IO_CTRL_EDGE_CTRL_LEVEL_TR =   ( 0U << 0U ),       /*!<  Level                                 [ Default ] */
    INT2_IO_CTRL_EDGE_CTRL_EDGE_TR  =   ( 1U << 0U )        /*!<  Edge                                              */
} BMA456_int2_io_ctrl_edge_ctrl_t;


/**
  * @brief   INT_LATCH. Configure interrupt modes.
  */
/* INT_LATCH <0>
 *    NOTE: Latched/non-latched/temporary interrupt modes.
 */
typedef enum
{
    INT_LATCH_INT_LATCH_MASK      =   ( 1U << 0U ),         /*!<  INT_LATCH mask                                    */
    INT_LATCH_INT_LATCH_NONE      =   ( 0U << 0U ),         /*!<  Non latched                           [ Default ] */
    INT_LATCH_INT_LATCH_PERMANENT =   ( 1U << 0U )          /*!<  Latched                                           */
} BMA456_int_latch_int_latch_t;


/**
  * @brief   INT1_MAP. Interrupt/Feature mapping on INT1.
  */
/* ERROR_INT_OUT <7>
 *    NOTE: Error interrupt output.
 */
typedef enum
{
    INT1_MAP_ERROR_INT_OUT_MASK     =   ( 1U << 7U ),       /*!<  ERROR_INT_OUT mask                                */
    INT1_MAP_ERROR_INT_OUT_DISABLED =   ( 0U << 7U ),       /*!<  Non enabled                           [ Default ] */
    INT1_MAP_ERROR_INT_OUT_ENABLED  =   ( 1U << 7U )        /*!<  Enabled                                           */
} BMA456_int1_map_error_int_out_t;


/* ANY_NO_MOTION_OUT <6>
 *    NOTE: Error interrupt output.
 */
typedef enum
{
    INT1_MAP_ERROR_ANY_NO_MOTION_OUT_MASK     =   ( 1U << 6U ),       /*!<  ERROR_INT_OUT mask                                */
    INT1_MAP_ERROR_ANY_NO_MOTION_OUT_DISABLED =   ( 0U << 6U ),       /*!<  Non enabled                           [ Default ] */
    INT1_MAP_ERROR_ANY_NO_MOTION_OUT_ENABLED  =   ( 1U << 6U )        /*!<  Enabled                                           */
} BMA456_int1_map_error_any_no_motion_out_t;


/* WAKEUP_OUT <5>
 *    NOTE: Wakeup output.
 */
typedef enum
{
    INT1_MAP_ERROR_WAKEUP_OUT_MASK     =   ( 1U << 5U ),    /*!<  WAKEUP_OUT mask                                   */
    INT1_MAP_ERROR_WAKEUP_OUT_DISABLED =   ( 0U << 5U ),    /*!<  Non enabled                           [ Default ] */
    INT1_MAP_ERROR_WAKEUP_OUT_ENABLED  =   ( 1U << 5U )     /*!<  Enabled                                           */
} BMA456_int1_map_error_wakeup_out_t;


/* WRIST_TILT_OUT <3>
 *    NOTE: Wrist tilt output.
 */
typedef enum
{
    INT1_MAP_ERROR_WRIST_TILT_OUT_MASK     =   ( 1U << 3U ),  /*!<  WRIST_TILT_OUT mask                               */
    INT1_MAP_ERROR_WRIST_TILT_OUT_DISABLED =   ( 0U << 3U ),  /*!<  Non enabled                           [ Default ] */
    INT1_MAP_ERROR_WRIST_TILT_OUT_ENABLED  =   ( 1U << 3U )   /*!<  Enabled                                           */
} BMA456_int1_map_error_wrist_tilt_out_t;


/* ACTIVITY_TYPE_OUT <2>
 *    NOTE: Step counter activity output (running, walking, still).
 */
typedef enum
{
    INT1_MAP_ERROR_ACTIVITY_TYPE_OUT_MASK     =   ( 1U << 2U ),  /*!<  ACTIVITY_TYPE_OUT mask                            */
    INT1_MAP_ERROR_ACTIVITY_TYPE_OUT_DISABLED =   ( 0U << 2U ),  /*!<  Non enabled                           [ Default ] */
    INT1_MAP_ERROR_ACTIVITY_TYPE_OUT_ENABLED  =   ( 1U << 2U )   /*!<  Enabled                                           */
} BMA456_int1_map_error_activity_type_out_t;


/* STEP_COUNTER_OUT <1>
 *    NOTE: Step-counter watermark or step-detector output.
 */
typedef enum
{
    INT1_MAP_ERROR_STEP_COUNTER_OUT_MASK     =   ( 1U << 1U ),  /*!<  STEP_COUNTER_OUT mask                             */
    INT1_MAP_ERROR_STEP_COUNTER_OUT_DISABLED =   ( 0U << 1U ),  /*!<  Non enabled                           [ Default ] */
    INT1_MAP_ERROR_STEP_COUNTER_OUT_ENABLED  =   ( 1U << 1U )   /*!<  Enabled                                           */
} BMA456_int1_map_error_step_counter_out_t;


/**
  * @brief   INT2_MAP. Interrupt/Feature mapping on INT2.
  */
/* ERROR_INT_OUT <7>
 *    NOTE: Error interrupt output.
 */
typedef enum
{
    INT2_MAP_ERROR_INT_OUT_MASK     =   ( 1U << 7U ),       /*!<  ERROR_INT_OUT mask                                */
    INT2_MAP_ERROR_INT_OUT_DISABLED =   ( 0U << 7U ),       /*!<  Non enabled                           [ Default ] */
    INT2_MAP_ERROR_INT_OUT_ENABLED  =   ( 1U << 7U )        /*!<  Enabled                                           */
} BMA456_int2_map_error_int_out_t;


/* ANY_NO_MOTION_OUT <6>
 *    NOTE: Error interrupt output.
 */
typedef enum
{
    INT2_MAP_ERROR_ANY_NO_MOTION_OUT_MASK     =   ( 1U << 6U ),       /*!<  ERROR_INT_OUT mask                                */
    INT2_MAP_ERROR_ANY_NO_MOTION_OUT_DISABLED =   ( 0U << 6U ),       /*!<  Non enabled                           [ Default ] */
    INT2_MAP_ERROR_ANY_NO_MOTION_OUT_ENABLED  =   ( 1U << 6U )        /*!<  Enabled                                           */
} BMA456_int2_map_error_any_no_motion_out_t;


/* WAKEUP_OUT <5>
 *    NOTE: Wakeup output.
 */
typedef enum
{
    INT2_MAP_ERROR_WAKEUP_OUT_MASK     =   ( 1U << 5U ),    /*!<  WAKEUP_OUT mask                                   */
    INT2_MAP_ERROR_WAKEUP_OUT_DISABLED =   ( 0U << 5U ),    /*!<  Non enabled                           [ Default ] */
    INT2_MAP_ERROR_WAKEUP_OUT_ENABLED  =   ( 1U << 5U )     /*!<  Enabled                                           */
} BMA456_int2_map_error_wakeup_out_t;


/* WRIST_TILT_OUT <3>
 *    NOTE: Wrist tilt output.
 */
typedef enum
{
    INT2_MAP_ERROR_WRIST_TILT_OUT_MASK     =   ( 1U << 3U ),  /*!<  WRIST_TILT_OUT mask                               */
    INT2_MAP_ERROR_WRIST_TILT_OUT_DISABLED =   ( 0U << 3U ),  /*!<  Non enabled                           [ Default ] */
    INT2_MAP_ERROR_WRIST_TILT_OUT_ENABLED  =   ( 1U << 3U )   /*!<  Enabled                                           */
} BMA456_int2_map_error_wrist_tilt_out_t;


/* ACTIVITY_TYPE_OUT <2>
 *    NOTE: Step counter activity output (running, walking, still).
 */
typedef enum
{
    INT2_MAP_ERROR_ACTIVITY_TYPE_OUT_MASK     =   ( 1U << 2U ),  /*!<  ACTIVITY_TYPE_OUT mask                            */
    INT2_MAP_ERROR_ACTIVITY_TYPE_OUT_DISABLED =   ( 0U << 2U ),  /*!<  Non enabled                           [ Default ] */
    INT2_MAP_ERROR_ACTIVITY_TYPE_OUT_ENABLED  =   ( 1U << 2U )   /*!<  Enabled                                           */
} BMA456_int2_map_error_activity_type_out_t;


/* STEP_COUNTER_OUT <1>
 *    NOTE: Step-counter watermark or step-detector output.
 */
typedef enum
{
    INT2_MAP_ERROR_STEP_COUNTER_OUT_MASK     =   ( 1U << 1U ),  /*!<  STEP_COUNTER_OUT mask                             */
    INT2_MAP_ERROR_STEP_COUNTER_OUT_DISABLED =   ( 0U << 1U ),  /*!<  Non enabled                           [ Default ] */
    INT2_MAP_ERROR_STEP_COUNTER_OUT_ENABLED  =   ( 1U << 1U )   /*!<  Enabled                                           */
} BMA456_int2_map_error_step_counter_out_t;


/**
  * @brief   INT_MAP_DATA. Interrupt mappeing hardware interrupts.
  */
/* INT2_DRDY <6>
 *    NOTE: Data ready interrupt mapped to INT2.
 */
typedef enum
{
    INT_MAP_DATA_INT2_DRDY_MASK       =   ( 1U << 6U ),           /*!<  INT2_DRDY mask                                    */
    INT_MAP_DATA_INT2_DRDY_NOT_MAPPED =   ( 0U << 6U ),           /*!<  Interrupt not mapped                  [ Default ] */
    INT_MAP_DATA_INT2_DRDY_MAPPED     =   ( 1U << 6U )            /*!<  Interrupt mapped                                  */
} BMA456_int_map_data_int2_drdy_t;


/* INT2_FWM <5>
 *    NOTE: FIFO watermark interrupt mapped to INT2.
 */
typedef enum
{
    INT_MAP_DATA_INT2_FWM_MASK        =   ( 1U << 5U ),           /*!<  INT2_FWM mask                                     */
    INT_MAP_DATA_INT2_FWM_NOT_MAPPED  =   ( 0U << 5U ),           /*!<  Interrupt not mapped                  [ Default ] */
    INT_MAP_DATA_INT2_FWM_MAPPED      =   ( 1U << 5U )            /*!<  Interrupt mapped                                  */
} BMA456_int_map_data_int2_fwm_t;


/* INT2_FFULL <4>
 *    NOTE: FIFO full interrupt mapped to INT2.
 */
typedef enum
{
    INT_MAP_DATA_INT2_FFULL_MASK        =   ( 1U << 4U ),         /*!<  INT2_FFULL mask                                   */
    INT_MAP_DATA_INT2_FFULL_NOT_MAPPED  =   ( 0U << 4U ),         /*!<  Interrupt not mapped                  [ Default ] */
    INT_MAP_DATA_INT2_FFULL_MAPPED      =   ( 1U << 4U )          /*!<  Interrupt mapped                                  */
} BMA456_int_map_data_int2_ffull_t;


/* INT1_DRDY <2>
 *    NOTE: Data ready interrupt mapped to INT1.
 */
typedef enum
{
    INT_MAP_DATA_INT1_DRDY_MASK        =   ( 1U << 2U ),         /*!<  INT1_DRDY mask                                    */
    INT_MAP_DATA_INT1_DRDY_NOT_MAPPED  =   ( 0U << 2U ),         /*!<  Interrupt not mapped                  [ Default ] */
    INT_MAP_DATA_INT1_DRDY_MAPPED      =   ( 1U << 2U )          /*!<  Interrupt mapped                                  */
} BMA456_int_map_data_int1_drdy_t;


/* INT1_FWM <1>
 *    NOTE: FIFO watermark interrupt mapped to INT1.
 */
typedef enum
{
    INT_MAP_DATA_INT1_FWM_MASK        =   ( 1U << 1U ),           /*!<  INT1_FWM mask                                     */
    INT_MAP_DATA_INT1_FWM_NOT_MAPPED  =   ( 0U << 1U ),           /*!<  Interrupt not mapped                  [ Default ] */
    INT_MAP_DATA_INT1_FWM_MAPPED      =   ( 1U << 1U )            /*!<  Interrupt mapped                                  */
} BMA456_int_map_data_int1_fwm_t;


/* INT1_FFULL <0>
 *    NOTE: FIFO full interrupt mapped to INT1.
 */
typedef enum
{
    INT_MAP_DATA_INT1_FFULL_MASK        =   ( 1U << 0U ),         /*!<  INT1_FFULL mask                                   */
    INT_MAP_DATA_INT1_FFULL_NOT_MAPPED  =   ( 0U << 0U ),         /*!<  Interrupt not mapped                  [ Default ] */
    INT_MAP_DATA_INT1_FFULL_MAPPED      =   ( 1U << 0U )          /*!<  Interrupt mapped                                  */
} BMA456_int_map_data_int1_ffull_t;


/**
  * @brief   INIT_CTRL. Start initialization.
  */
/* INIT_CTRL <7:0>
 *    NOTE: N/A.
 */
typedef enum
{
    INIT_CTRL_INIT_CTRL_MASK      =   0xFF,                       /*!<  INIT_CTRL mask                                    */
    INIT_CTRL_INIT_CTRL_DISABLE   =   0x00,                       /*!<  Disable                                           */
    INIT_CTRL_INIT_CTRL_ENABLE    =   0x01,                       /*!<  Enable                                            */
    INIT_CTRL_INIT_CTRL           =   0x90                        /*!<  Reset value                           [ Default ] */
} BMA456_int_ctrl_init_ctrl_t;



/* features_in  HOLAHOLAHOLAHOLAHOLAHOLAHOLAHOLAOLAHOLAHOLAHOLAHOLAHOLAHOLAHOLA 
                HOLAHOLAHOLAHOLAHOLAHOLAHOLAHOLAOLAHOLAHOLAHOLAHOLAHOLAHOLAHOLA 
                HOLAHOLAHOLAHOLAHOLAHOLAHOLAHOLAOLAHOLAHOLAHOLAHOLAHOLAHOLAHOLA 
*/





/**
  * @brief   INTERNAL_ERROR. Internal error flags.
  */
/* INT_ERR_2 <2>
 *    NOTE: Internal error flag: fatal error, processing halted.
 */
typedef enum
{
    INTERNAL_ERROR_INT_ERR_2_MASK       =   ( 1U << 2U ),         /*!<  INT_ERR_2 mask                                    */
    INTERNAL_ERROR_INT_ERR_2_NO_ERROR   =   ( 0U << 2U ),         /*!<  No errors                             [ Default ] */
    INTERNAL_ERROR_INT_ERR_2_ERROR      =   ( 1U << 2U )          /*!<  Errors                                            */
} BMA456_internal_error_int_err_2_t;


/* INT_ERR_1 <1>
 *    NOTE: Internal error flag: long processing time, processing halted.
 */
typedef enum
{
    INTERNAL_ERROR_INT_ERR_1_MASK       =   ( 1U << 1U ),         /*!<  INT_ERR_1 mask                                    */
    INTERNAL_ERROR_INT_ERR_1_NO_ERROR   =   ( 0U << 1U ),         /*!<  No errors                             [ Default ] */
    INTERNAL_ERROR_INT_ERR_1_ERROR      =   ( 1U << 1U )          /*!<  Errors                                            */
} BMA456_internal_error_int_err_1_t;


/**
  * @brief   NVM_CONF. NVM controller mode (prog/erase or read only).
  */
/* NVM_PROG_EN <1>
 *    NOTE: Enable NVM programming.
 */
typedef enum
{
    NVM_CONF_NVM_PROG_EN_MASK       =   ( 1U << 1U ),             /*!<  NVM_PROG_EN mask                                  */
    NVM_CONF_NVM_PROG_EN_DISABLE    =   ( 0U << 1U ),             /*!<  Disable                               [ Default ] */
    NVM_CONF_NVM_PROG_EN_ENABLE     =   ( 1U << 1U )              /*!<  Enable                                            */
} BMA456_nvm_conf_nvm_prog_en_t;


/**
  * @brief   IF_CONF. Serial interface settings.
  */
/* IF_MODE <4>
 *    NOTE: Auxiliary interface configuration.
 */
typedef enum
{
    IF_CONF_IF_MODE_MASK          =   ( 1U << 4U ),               /*!<  IF_MODE mask                                      */
    IF_CONF_IF_MODE_P_AUTO_S_OFF  =   ( 0U << 4U ),               /*!<  Auxiliary interface: off              [ Default ] */
    IF_CONF_IF_MODE_P_AUTO_S_MAG  =   ( 1U << 4U )                /*!<  Auxiliary interface: Magnetometer                 */
} BMA456_if_conf_if_mode_t;


/* SPI3 <0>
 *    NOTE: Configure SPI interface mode for primary interface.
 */
typedef enum
{
    IF_CONF_SPI3_MASK           =   ( 1U << 0U ),                 /*!<  SPI3 mask                                         */
    IF_CONF_SPI3_SPI4           =   ( 0U << 0U ),                 /*!<  SPI 4-wire mode                       [ Default ] */
    IF_CONF_SPI3_SPI3           =   ( 1U << 0U )                  /*!<  SPI 3-wire mode                                   */
} BMA456_if_conf_spi3_t;


/**
  * @brief   ACC_SELF_TEST. Settings for the sensor self-test configuration and trigger.
  */
/* ACC_SELF_TEST_AMP <3>
 *    NOTE: Select amplitud of the selftest deflection.
 */
typedef enum
{
    ACC_SELF_TEST_ACC_SELF_TEST_AMP_MASK  =   ( 1U << 3U ),       /*!<  ACC_SELF_TEST_AMP mask                            */
    ACC_SELF_TEST_ACC_SELF_TEST_AMP_LOW   =   ( 0U << 3U ),       /*!<  low                                   [ Default ] */
    ACC_SELF_TEST_ACC_SELF_TEST_AMP_HIGH  =   ( 1U << 3U )        /*!<  high                                              */
} BMA456_acc_self_test_acc_self_test_amp_t;


/* ACC_SELF_TEST_SIGN <2>
 *    NOTE: Select sign of self-test exication.
 */
typedef enum
{
    ACC_SELF_TEST_ACC_SELF_TEST_SIGN_MASK     =   ( 1U << 2U ),     /*!<  ACC_SELF_TEST_SIGN mask                            */
    ACC_SELF_TEST_ACC_SELF_TEST_SIGN_NEGATIVE =   ( 0U << 2U ),     /*!<  negative                               [ Default ] */
    ACC_SELF_TEST_ACC_SELF_TEST_SIGN_POSITIVE =   ( 1U << 2U )      /*!<  positive                                           */
} BMA456_acc_self_test_acc_self_test_sign_t;


/* ACC_SELF_TEST_EN <0>
 *    NOTE: Enable accelerometer self-test.
 */
typedef enum
{
    ACC_SELF_TEST_ACC_SELF_TEST_EN_MASK    =   ( 1U << 0U ),        /*!<  ACC_SELF_TEST_EN mask                              */
    ACC_SELF_TEST_ACC_SELF_TEST_EN_DISABLE =   ( 0U << 0U ),        /*!<  disable                                [ Default ] */
    ACC_SELF_TEST_ACC_SELF_TEST_EN_ENABLE  =   ( 1U << 0U )         /*!<  enable                                             */
} BMA456_acc_self_test_acc_self_test_en_t;


/**
  * @brief   NV_CONF. NVM backed configuration bits.
  */
/* ACC_OFF_EN <3>
 *    NOTE: Add the offset defined in the off_acc_[xyz] OFFSET register to filtered and unfiltered accelerometer data.
 */
typedef enum
{
    NV_CONF_ACC_OFF_EN_MASK     =   ( 1U << 3U ),                   /*!<  ACC_OFF_EN mask                                   */
    NV_CONF_ACC_OFF_EN_DISABLE  =   ( 0U << 3U ),                   /*!<  disable                               [ Default ] */
    NV_CONF_ACC_OFF_EN_ENABLE   =   ( 1U << 3U )                    /*!<  enable                                            */
} BMA456_nv_conf_acc_off_en_t;


/* I2C_WDT_EN <2>
 *    NOTE: I2C watchdog at the SDI pin in I2C interface mode.
 */
typedef enum
{
    NV_CONF_I2C_WDT_EN_MASK     =   ( 1U << 2U ),                   /*!<  I2C_WDT_EN mask                                   */
    NV_CONF_I2C_WDT_EN_DISABLE  =   ( 0U << 2U ),                   /*!<  disable I2C watchdog                  [ Default ] */
    NV_CONF_I2C_WDT_EN_ENABLE   =   ( 1U << 2U )                    /*!<  enable I2C watchdog                               */
} BMA456_nv_conf_i2c_wdt_en_t;


/* I2C_WDT_SEL <1>
 *    NOTE: Select timer period for I2C watchdog.
 */
typedef enum
{
    NV_CONF_I2C_WDT_SEL_MASK      =   ( 1U << 1U ),                 /*!<  I2C_WDT_SEL mask                                  */
    NV_CONF_I2C_WDT_SEL_WDT_SHORT =   ( 0U << 1U ),                 /*!<  I2C watchdog timeout after 1.25ms     [ Default ] */
    NV_CONF_I2C_WDT_SEL_WDT_LONG  =   ( 1U << 1U )                  /*!<  I2C watchdog timeout after 40ms                   */
} BMA456_nv_conf_i2c_wdt_sel_t;


/* SPI_EN <0>
 *    NOTE: Disable the I2C and enable SPI for the primary interface, when it is in autoconfig mode.
 */
typedef enum
{
    NV_CONF_SPI_EN_MASK      =   ( 1U << 0U ),                      /*!<  SPI_EN mask                                       */
    NV_CONF_SPI_EN_DISABLE   =   ( 0U << 0U ),                      /*!<  I2C enabled                           [ Default ] */
    NV_CONF_SPI_EN_ENABLE    =   ( 1U << 0U )                       /*!<  I2C disabled                                      */
} BMA456_nv_conf_spi_en_t;


/**
  * @brief   PWR_CONF. Power mode configuration register.
  */
/* FIFO_SELF_WAKEUP <1>
 *    NOTE: N/A.
 */
typedef enum
{
    PWR_CONF_FIFO_SELF_WAKEUP_MASK     =   ( 1U << 1U ),            /*!<  FIFO_SELF_WAKEUP mask                                                       */
    PWR_CONF_FIFO_SELF_WAKEUP_FSW_OFF  =   ( 0U << 1U ),            /*!<  FIFO read disabled in advanced power saving mode                            */
    PWR_CONF_FIFO_SELF_WAKEUP_FSW_ON   =   ( 1U << 1U )             /*!<  FIFO read enabled after interrupt in advanced power saving mode [ Default ] */
} BMA456_pwr_conf_fifo_self_wakeup_t;


/* ADV_POWER_SAVE <0>
 *    NOTE: N/A.
 */
typedef enum
{
    PWR_CONF_ADV_POWER_SAVE_MASK        =   ( 1U << 0U ),            /*!<  ADV_POWER_SAVE mask                                                                          */
    PWR_CONF_ADV_POWER_SAVE_APS_OFF     =   ( 0U << 0U ),            /*!<  Advanced power save disabled (fast clk always enabled)                                       */
    PWR_CONF_ADV_POWER_SAVE_APS_ON      =   ( 1U << 0U )             /*!<  Advanced power mode enabled (slow clk is active when no measurement is ongoing)  [ Default ] */
} BMA456_pwr_conf_adv_power_save_t;


/**
  * @brief   PWR_CTRL. Sensor enable register.
  */
/* ACC_EN <2>
 *    NOTE: N/A.
 */
typedef enum
{
    PWR_CTRL_ACC_EN_MASK     =   ( 1U << 2U ),                   /*!<  ACC_EN mask                                       */
    PWR_CTRL_ACC_EN_ACC_OFF  =   ( 0U << 2U ),                   /*!<  Disables the accelerometer            [ Default ] */
    PWR_CTRL_ACC_EN_ACC_ON   =   ( 1U << 2U )                    /*!<  Enables the accelerometer                         */
} BMA456_pwr_ctrl_acc_en_t;


/* AUX_EN <0>
 *    NOTE: N/A.
 */
typedef enum
{
    PWR_CTRL_AUX_EN_MASK     =   ( 1U << 0U ),                   /*!<  AUX_EN mask                                       */
    PWR_CTRL_AUX_EN_MAG_OFF  =   ( 0U << 0U ),                   /*!<  Disables the auxiliary sensor         [ Default ] */
    PWR_CTRL_AUX_EN_MAG_ON   =   ( 1U << 0U )                    /*!<  Enables the auxiliary sensor                      */
} BMA456_pwr_ctrl_aux_en_t;


/**
  * @brief   CMD. Command register.
  */
/* CMD <7:0>
 *    NOTE: Register will always read as 0x00.
 */
typedef enum
{
    CMD_CMD_MASK        =   0xFF,               /*!<  CMD mask                                                                                    */
    CMD_CMD_NV_PROG     =   0xA0,               /*!<  Writes the NVM backed registers into NVM                                                    */
    CMD_CMD_FIFO_FLUSH  =   0xB0,               /*!<  Clears all data in the FIFO, does not change FIFO_CONFIG and FIFO_DOWNS registers           */
    CMD_CMD_SOFTRESET   =   0xB6                /*!<  Triggers a reset, all user configuration settings are overwritten with their default state  */
} BMA456_cmd_cmd_t;










#ifndef BMA456_VECTOR_STRUCT_H
#define BMA456_VECTOR_STRUCT_H
typedef struct
{
  /* Output: Raw data  */
  uint16_t  aux_raw_x;                        /*!<  Auxiliary: Raw Aux_X              */
  uint16_t  aux_raw_y;                        /*!<  Auxiliary: Raw Aux_Y              */
  uint16_t  aux_raw_z;                        /*!<  Auxiliary: Raw Aux_Z              */
  uint16_t  aux_raw_r;                        /*!<  Auxiliary: Raw Aux_R              */

  uint16_t  acc_raw_x;                        /*!<  Accelerometer: Raw Acc_X          */
  uint16_t  acc_raw_y;                        /*!<  Accelerometer: Raw Acc_Y          */
  uint16_t  acc_raw_z;                        /*!<  Accelerometer: Raw Acc_Z          */
  
  uint32_t  sensor_time;                      /*!<  Sensor time                       */
  uint32_t  step_counter;                     /*!<  Step counting value               */
  
  uint8_t   rawTemperature;                   /*!<  Temperature raw value             */
  
  /* Offset  */
  int8_t    off_acc_x;                        /*!<  Offset for Accelerometer X-axis   */
  int8_t    off_acc_y;                        /*!<  Offset for Accelerometer Y-axis   */
  int8_t    off_acc_z;                        /*!<  Offset for Accelerometer Z-axis   */
  
  /* Sensor status flags   */
  BMA456_status_drdy_acc_t    drdy_acc;       /*!<  Data ready for accelerometer      */
  BMA456_status_drdy_aux_t    drdy_aux;       /*!<  Data ready for auxiliary sensor   */
  BMA456_status_cmd_rdy_t     cmd_rdy;        /*!<  CMD decoder status                */
  BMA456_status_aux_man_op_t  aux_man_op;     /*!<  Auxiliary interface operation     */

  BMA456_event_por_detected_t por_detected;   /*!<  Power-up or softreset             */
  
  /* Internal status   */
  BMA456_internal_status_odr_high_error_t   odr_high_error;     /*!<  Minimum Bandwidth conditions for Wakeup detection                 */
  BMA456_internal_status_odr_50hz_error_t   odr_50hz_error;     /*!<  Minimum Bandwidth conditions for features that require 50Hz data  */
  BMA456_internal_status_axes_remap_error_t axes_remap_error;   /*!<  Axes remapped error                                               */
  BMA456_internal_status_message_t          message;            /*!<  Internal status message                                           */

  /* Sensor error conditions  */
  BMA456_err_reg_aux_err_t    aux_err;        /*!<  Error in I2C-Master detected      */
  BMA456_err_reg_fifo_err_t   fifo_err;       /*!<  Error in FIFO detected            */
  BMA456_err_reg_error_code_t error_code;     /*!<  Error codes for persistent errors */
  BMA456_err_reg_cmd_err_t    cmd_err;        /*!<  Command execution failed          */
  BMA456_err_reg_fatal_err_t  fatal_err;      /*!<  Fatal error                       */

  /* FIFO  */
  uint16_t                                  fifo_byte_counter;  /*!<  FIFO byte count register            */
  uint8_t                                   fifo_data;          /*!<  FIFO read data                      */

  uint8_t                                   acc_fifo_downs;     /*!<  FIFO downsampling for Acc.          */
  BMA456_fifo_downs_acc_fifo_filt_data_t    acc_fifo_filt_data; /*!<  Filtered/Unfiltered for Acc.        */
  
  uint16_t                                  fifo_water_mark;    /*!<  FIFO watermark level                */
  
  BMA456_fifo_config_0_fifo_time_en_t       fifo_time_en;       /*!<  Sensortime frame                    */
  BMA456_fifo_config_0_fifo_stop_on_full_t  fifo_stop_on_full;  /*!<  Writing samples into FIFO when full */
  BMA456_fifo_config_1_fifo_acc_en_t        fifo_acc_en;        /*!<  Store Acc. data in FIFO             */
  BMA456_fifo_config_1_fifo_aux_en_t        fifo_aux_en;        /*!<  Store Aux. data in FIFO             */
  BMA456_fifo_config_1_fifo_header_en_t     fifo_header_en;     /*!<  FIFO frame header enable            */
  BMA456_fifo_config_1_fifo_tag_int1_en_t   fifo_tag_int1_en;   /*!<  FIFO interrupt 1 tag enable         */
  BMA456_fifo_config_1_fifo_tag_int2_en_t   fifo_tag_int2_en;   /*!<  FIFO interrupt 2 tag enable         */

  /* Power mode configuration  */
  BMA456_pwr_conf_fifo_self_wakeup_t  fifo_self_wakeup; /*!<  FIFO self wakeup                    */
  BMA456_pwr_conf_adv_power_save_t    adv_power_save;   /*!<  Advanced power save                 */
  
  BMA456_pwr_ctrl_acc_en_t            acc_en;           /*!<  Enable/Disable Accelerometer        */
  BMA456_pwr_ctrl_aux_en_t            aux_en;           /*!<  Enable/Disable Auxiliary sensor     */


  /* Activity  */
  BMA456_activity_type_activity_type_out_t activity_type_out; /*!<  Step counter activity output  */

  /* Accelerometer configuration   */
  BMA456_acc_conf_acc_perf_mode_t  acc_perf_mode;   /*!<  Acc. Filter performance           */
  BMA456_acc_conf_acc_bwp_t        acc_bwp;         /*!<  Acc. Bandwidth parameter          */
  BMA456_acc_conf_acc_odr_t        acc_odr;         /*!<  Acc. ODR in Hz                    */

  BMA456_acc_range_acc_acc_range_t acc_range;       /*!<  Acc. Range                        */

  /* Auxiliary interface configuration   */
  uint8_t                             aux_offset;       /*!<  Trigger-readout offset in units of 2.5ms  */
  BMA456_aux_conf_aux_odr_t           aux_odr;          /*!<  Auxiliary ODR in Hz                       */
  
  uint8_t                             i2c_device_addr;  /*!<  Auxiliary interface slave device ID       */
  
  BMA456_aux_if_conf_aux_manual_en_t  aux_manual_en;    /*!<  Auxiliary interface manual mode           */
  BMA456_aux_if_conf_aux_rd_burst_t   aux_rd_burst;     /*!<  Auxiliary interface burst data length     */

  uint8_t                             read_addr;        /*!<  Auxiliary interface, address to read      */
  uint8_t                             write_addr;       /*!<  Auxiliary interface, address to write     */

  uint8_t                             write_data;       /*!<  Auxiliary interface, write data           */

  
  /* Interrupt pins  */
  BMA456_int1_io_ctrl_input_en_t            int1_input_en;          /*!<  Input enable for INT1 pin                       */
  BMA456_int1_io_ctrl_output_en_t           int1_output_en;         /*!<  Output enable for INT1 pin                      */
  BMA456_int1_io_ctrl_od_t                  int1_od;                /*!<  Open-drain for INT1 pin                         */
  BMA456_int1_io_ctrl_lvl_t                 int1_lvl;               /*!<  Configure level for INT1 pin                    */
  BMA456_int1_io_ctrl_edge_ctrl_t           int1_edge_ctrl;         /*!<  Trigger condition of INT1 pin                   */

  BMA456_int2_io_ctrl_input_en_t            int2_input_en;          /*!<  Input enable for INT2 pin                       */
  BMA456_int2_io_ctrl_output_en_t           int2_output_en;         /*!<  Output enable for INT2 pin                      */
  BMA456_int2_io_ctrl_od_t                  int2_od;                /*!<  Open-drain for INT2 pin                         */
  BMA456_int2_io_ctrl_lvl_t                 int2_lvl;               /*!<  Configure level for INT2 pin                    */
  BMA456_int2_io_ctrl_edge_ctrl_t           int2_edge_ctrl;         /*!<  Trigger condition of INT2 pin                   */

  BMA456_int_latch_int_latch_t              int_latch;              /*!<  Latched/non-latched/temporary interrupt modes   */

  BMA456_int1_map_error_int_out_t           int1_error_int_out;     /*!<  Error interrupt output                          */
  BMA456_int1_map_error_any_no_motion_out_t int1_any_no_motion_out; /*!<  Any-motion/No-motion detection output           */
  BMA456_int1_map_error_wakeup_out_t        int1_wakeup_out;        /*!<  Wakeup output                                   */
  BMA456_int1_map_error_wrist_tilt_out_t    int1_wrist_tilt_out;    /*!<  Wrist tilt output                               */
  BMA456_int1_map_error_activity_type_out_t int1_activity_type_out; /*!<  Step counter activity output                    */
  BMA456_int1_map_error_activity_type_out_t int1_step_counter_out;  /*!<  Step-counter watermark or Step-detector output  */

  BMA456_int2_map_error_int_out_t           int2_error_int_out;     /*!<  Error interrupt output                          */
  BMA456_int2_map_error_any_no_motion_out_t int2_any_no_motion_out; /*!<  Any-motion/No-motion detection output           */
  BMA456_int2_map_error_wakeup_out_t        int2_wakeup_out;        /*!<  Wakeup output                                   */
  BMA456_int2_map_error_wrist_tilt_out_t    int2_wrist_tilt_out;    /*!<  Wrist tilt output                               */
  BMA456_int2_map_error_activity_type_out_t int2_activity_type_out; /*!<  Step counter activity output                    */
  BMA456_int2_map_error_activity_type_out_t int2_step_counter_out;  /*!<  Step-counter watermark or Step-detector output  */

  BMA456_int_map_data_int2_drdy_t           int2_drdy;              /*!<  Data ready interrupt mapped to INT2             */
  BMA456_int_map_data_int2_fwm_t            int2_fwm;               /*!<  FIFO watermark interrupt mapped to INT2         */
  BMA456_int_map_data_int2_ffull_t          int2_ffull;             /*!<  FIFO full interrupt mapped to INT2              */
  BMA456_int_map_data_int1_drdy_t           int1_drdy;              /*!<  Data ready interrupt mapped to INT1             */
  BMA456_int_map_data_int1_fwm_t            int1_fwm;               /*!<  FIFO watermark interrupt mapped to INT1         */
  BMA456_int_map_data_int1_ffull_t          int1_ffull;             /*!<  FIFO full interrupt mapped to INT1              */

  /* Internal error flags  */
  BMA456_internal_error_int_err_2_t int_err_2;  /*!<  Internal error flag - fatal error, processing halted          */
  BMA456_internal_error_int_err_1_t int_err_1;  /*!<  Internal error flag - long processing time, processing halted */
  
  /* NVM controller mode   */
  BMA456_nvm_conf_nvm_prog_en_t nvm_prog_en;    /*!<  Enable/Disable NVM programming    */

  BMA456_nv_conf_acc_off_en_t   acc_off_en;     /*!<  Enable/Disable offset             */
  BMA456_nv_conf_i2c_wdt_en_t   i2c_wdt_en;     /*!<  I2C watchdog at the SDI pin       */
  BMA456_nv_conf_i2c_wdt_sel_t  i2c_wdt_sel;    /*!<  I2C watchdog period               */
  BMA456_nv_conf_spi_en_t       spi_en;         /*!<  Enable/Disable SPI                */


  /* Auxiliary interface configuration   */
  BMA456_if_conf_if_mode_t      if_mode;        /*!<  Auxiliary interface configuration */

  /* Self-test configuration and trigger   */
  BMA456_acc_self_test_acc_self_test_amp_t  acc_self_test_amp;        /*!<  Amplitude of the sleftest deflection    */
  BMA456_acc_self_test_acc_self_test_sign_t acc_self_test_sign;       /*!<  Sign of the selftest excitation         */
  BMA456_acc_self_test_acc_self_test_en_t   acc_self_test_en;         /*!<  Enable accelerometer self-test          */
  
  /* Command   */
  BMA456_cmd_cmd_t              cmd;            /*!<  Available commands                */


  /* Device identification   */
  uint8_t   chip_id;                            /*!<  Device ID                         */
} BMA456_data_t;


typedef struct
{
  /* Interrupt/Feature status  */
  BMA456_int_status_0_error_int_out_t     error_int_out;      /*!<  Error interrupt output                      */
  BMA456_int_status_0_any_no_motion_out_t any_no_motion_out;  /*!<  Any-motion/No-motion detection output       */
  BMA456_int_status_0_wakeup_out_t        wakeup_out;         /*!<  Wakeup output                               */
  BMA456_int_status_0_wrist_tilt_out_t    wrist_tilt_out;     /*!<  Wrist tilt output                           */
  BMA456_int_status_0_activity_type_out_t activity_type_out;  /*!<  Step counter activity output                */
  BMA456_int_status_0_step_counter_out_t  step_counter_out;   /*!<  Step-counter watermark/Step-detector output */
  BMA456_int_status_1_acc_drdy_int_t      acc_drdy_int;       /*!<  Accelerometer data ready interrupt          */
  BMA456_int_status_1_aux_drdy_int_t      aux_drdy_int;       /*!<  Auxiliary sensor data ready interrupt       */
  BMA456_int_status_1_fwm_int_t           fwm_int;            /*!<  FIFO watermark interrupt                    */
  BMA456_int_status_1_ffull_int_t         ffull_int;          /*!<  FIFO full interrupt                         */
} BMA456_int_status_t;
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

/** It gets the device ID.
  */
BMA456_status_t BMA456_GetID                    ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myID                   );

/** It reports sensor error conditions.
  */
BMA456_status_t BMA456_GetSensorErrorConditions ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myErrors               );

/** It reports sensor status flags.
  */
BMA456_status_t BMA456_GetSensorStatusFlags     ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myStatusFlags          );

/** It gets aux raw data ( X, Y, Z and R ).
  */
BMA456_status_t BMA456_GetAuxRawData            ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxRawData           );

/** It gets acceleration raw data ( X, Y and Z ).
  */
BMA456_status_t BMA456_GetAccRawData            ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccRawData           );

/** It gets sensor time ( raw value ).
  */
BMA456_status_t BMA456_GetSensorTime            ( I2C_parameters_t myI2Cparameters, BMA456_data_t* mySensorTime           );

/** It gets sensor status flag ( POR event ).
  */
BMA456_status_t BMA456_GetEvent                 ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myEvent                );

/** It gets interrupt/feature status.
  */
BMA456_status_t BMA456_GetIntStatus             ( I2C_parameters_t myI2Cparameters, BMA456_int_status_t* myIntStatus      );

/** It gets step counter value.
  */
BMA456_status_t BMA456_GetStepCounter           ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myStepCounter          );

/** It gets the temperature raw value of the sensor.
  */
BMA456_status_t BMA456_GetRawTemperature        ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myRawTemperature       );

/** It gets the FIFO length.
  */
BMA456_status_t BMA456_GetFIFO_Length           ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOlen              );

/** It gets the FIFO data output.
  */
BMA456_status_t BMA456_GetFIFO_Data             ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOdata             );

/** It gets the activity type ( Running, walking or still ).
  */
BMA456_status_t BMA456_GetActivityType          ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myActivityType         );

/** It gets the internal status.
  */
BMA456_status_t BMA456_GetInternalStatus        ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInternalStatus       );

/** It gets the accelerometer configuration of the acceleration sensor.
  */
BMA456_status_t BMA456_GetAccConf               ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccConf              );

/** It sets the accelerometer configuration of the acceleration sensor.
  */
BMA456_status_t BMA456_SetAccConf               ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAccConf               );

/** It gets the accelerometer range: ±2g/±4g/±8g/±16g.
  */
BMA456_status_t BMA456_GetAccRange              ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccRange             );

/** It sets the accelerometer range: ±2g/±4g/±8g/±16g.
  */
BMA456_status_t BMA456_SetAccRange              ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAccRange              );

/** It gets the auxiliary configuration of the auxiliary interface.
  */
BMA456_status_t BMA456_GetAuxConf               ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxConf              );

/** It sets the auxiliary configuration of the auxiliary interface.
  */
BMA456_status_t BMA456_SetAuxConf               ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxConf               );

/** It gets the sensor configuration downsampling rates for FIFO.
  */
BMA456_status_t BMA456_GetFIFO_Downs            ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOdowns            );

/** It sets the sensor configuration downsampling rates for FIFO.
  */
BMA456_status_t BMA456_SetFIFO_Downs            ( I2C_parameters_t myI2Cparameters, BMA456_data_t myFIFOdowns             );

/** It gets the FIFO watermark level.
  */
BMA456_status_t BMA456_GetFIFO_Watermark        ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOwtm              );

/** It sets the FIFO watermark level.
  */
BMA456_status_t BMA456_SetFIFO_Watermark        ( I2C_parameters_t myI2Cparameters, BMA456_data_t myFIFOwtm               );

/** It gets the FIFO frame content configuration.
  */
BMA456_status_t BMA456_GetFIFO_Config           ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOconfig           );

/** It sets the FIFO frame content configuration.
  */
BMA456_status_t BMA456_SetFIFO_Config           ( I2C_parameters_t myI2Cparameters, BMA456_data_t myFIFOconfig            );

/** It gets the auxiliary interface slave ID.
  */
BMA456_status_t BMA456_GetAuxDevID              ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxDevID             );

/** It sets the auxiliary interface slave ID.
  */
BMA456_status_t BMA456_SetAuxDevID              ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxDevID              );

/** It gets the auxiliary interface configuration.
  */
BMA456_status_t BMA456_GetAuxIfConf             ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxIfConf            );

/** It sets the auxiliary interface configuration.
  */
BMA456_status_t BMA456_SetAuxIfConf             ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxIfConf             );

/** It gets the auxiliary interface read register address.
  */
BMA456_status_t BMA456_GetAuxRdAddr             ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxRdAddr            );

/** It sets the auxiliary interface read register address.
  */
BMA456_status_t BMA456_SetAuxRdAddr             ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxRdAddr             );

/** It gets the auxiliary interface write register address.
  */
BMA456_status_t BMA456_GetAuxWdAddr             ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxWdAddr            );

/** It sets the auxiliary interface write register address.
  */
BMA456_status_t BMA456_SetAuxWdAddr             ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxWdAddr             );

/** It gets the auxiliary interface write data.
  */
BMA456_status_t BMA456_GetAuxWrData             ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxWrData            );

/** It sets the auxiliary interface write data.
  */
BMA456_status_t BMA456_SetAuxWrData             ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxWrData             );

/** It gets the configuration for the electrical behaviour of the interrupt pins ( INT1 ).
  */
BMA456_status_t BMA456_GetInt1_IO_Ctrl          ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt1_IO_Ctrl         );

/** It sets the configuration for the electrical behaviour of the interrupt pins ( INT1 ).
  */
BMA456_status_t BMA456_SetInt1_IO_Ctrl          ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt1_IO_Ctrl          );

/** It gets the configuration for the electrical behaviour of the interrupt pins ( INT2 ).
  */
BMA456_status_t BMA456_GetInt2_IO_Ctrl          ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt2_IO_Ctrl         );

/** It sets the configuration for the electrical behaviour of the interrupt pins ( INT2 ).
  */
BMA456_status_t BMA456_SetInt2_IO_Ctrl          ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt2_IO_Ctrl          );

/** It gets the configuration for interrupt modes.
  */
BMA456_status_t BMA456_GetIntLatch              ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myIntLatch             );

/** It sets the configuration for interrupt modes.
  */
BMA456_status_t BMA456_SetIntLatch              ( I2C_parameters_t myI2Cparameters, BMA456_data_t myIntLatch              );

/** It gets the interrupt/feature mapping on INT1.
  */
BMA456_status_t BMA456_GetInt1Map               ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt1Map              );

/** It sets the interrupt/feature mapping on INT1.
  */
BMA456_status_t BMA456_SetInt1Map               ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt1Map               );

/** It gets the interrupt/feature mapping on INT2.
  */
BMA456_status_t BMA456_GetInt2Map               ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt2Map              );

/** It sets the interrupt/feature mapping on INT2.
  */
BMA456_status_t BMA456_SetInt2Map               ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt2Map               );

/** It gets the interrupt mapping hardware interrupts.
  */
BMA456_status_t BMA456_GetIntMapData            ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myIntMapData           );

/** It sets the interrupt mapping hardware interrupts.
  */
BMA456_status_t BMA456_SetIntMapData            ( I2C_parameters_t myI2Cparameters, BMA456_data_t myIntMapData            );

/* INIT_CTRL nad FEATURES **********************************************************************/


/** It gets the internal error flags.
  */
BMA456_status_t BMA456_GetInternalError         ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInternalError        );

/** It gets the NVM controller mode (Prog/rase or Read only).
  */
BMA456_status_t BMA456_GetNVM_Conf              ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myNVM_Conf             );

/** It sets the NVM controller mode (Prog/rase or Read only).
  */
BMA456_status_t BMA456_SetNVM_Conf              ( I2C_parameters_t myI2Cparameters, BMA456_data_t myNVM_Conf              );

/** It gets the auxiliary interface configuration.
  */
BMA456_status_t BMA456_GetAuxiliaryInterfaceConf  ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxIntConf           );

/** It sets the auxiliary interface configuration.
  */
BMA456_status_t BMA456_SetAuxiliaryInterfaceConf  ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxIntConf            );

/** It gets the settings for the sensor self-test configuration and trigger.
  */
BMA456_status_t BMA456_GetAccSelfTest           ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccSelfTest          );

/** It sets the settings for the sensor self-test configuration and trigger.
  */
BMA456_status_t BMA456_SetAccSelfTest           ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAccSelfTest           );

/** It gets the NVM backed configuration bits.
  */
BMA456_status_t BMA456_GetNV_Conf               ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myNV_Conf              );

/** It sets the NVM backed configuration bits.
  */
BMA456_status_t BMA456_SetNV_Conf               ( I2C_parameters_t myI2Cparameters, BMA456_data_t myNV_Conf               );

/** It gets the offset compensation for accelerometer X/Y/Z-axis.
  */
BMA456_status_t BMA456_GetOffset                ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myOffset               );

/** It sets the offset compensation for accelerometer X/Y/Z-axis.
  */
BMA456_status_t BMA456_SetOffset                ( I2C_parameters_t myI2Cparameters, BMA456_data_t myOffset                );

/** It gets the power mode configuration register.
  */
BMA456_status_t BMA456_GetPWR_Conf              ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myPWR_Conf             );

/** It sets the power mode configuration register.
  */
BMA456_status_t BMA456_SetPWR_Conf              ( I2C_parameters_t myI2Cparameters, BMA456_data_t myPWR_Conf              );

/** It gets the sensor enable register.
  */
BMA456_status_t BMA456_GetPWR_Ctrl              ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myPWR_Ctrl             );

/** It sets the sensor enable register.
  */
BMA456_status_t BMA456_SetPWR_Ctrl              ( I2C_parameters_t myI2Cparameters, BMA456_data_t myPWR_Ctrl              );

/** It sets the command register.
  */
BMA456_status_t BMA456_SetCMD                   ( I2C_parameters_t myI2Cparameters, BMA456_data_t myCMD                   );