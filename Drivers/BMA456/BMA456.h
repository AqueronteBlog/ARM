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



  float     pressure;                         /*!<  Pressure in mbar                  */
  float     temperature;                      /*!<  Temperature in Celsius degree     */

  uint32_t  ref_p;                            /*!<  Reference pressure ( raw value )  */
  uint16_t  rpds;                             /*!<  Pressure offset                   */

  /* Configuration  */
  BMA456_ctrl_reg1_odr_t         odr;        /*!<  Output data rate selection        */
  BMA456_ctrl_reg1_bdu_t         bdu;        /*!<  Block data update                 */
  BMA456_ctrl_reg2_boot_t        boot;       /*!<  Reboot memory content flag        */
  BMA456_ctrl_reg2_fifo_en_t     fifo_en;    /*!<  FIFO enable                       */
  BMA456_ctrl_reg2_stop_on_fth_t stopOnFTH;  /*!<  FIFO watermark level use flag     */
  BMA456_ctrl_reg2_swreset_t     swreset;    /*!<  Software reset                    */
  BMA456_ctrl_reg2_one_shot_t    one_shot;   /*!<  One-shot                          */
  
  /* FIFO control  */
  BMA456_fifo_ctrl_f_mode_t      f_mode;     /*!<  FIFO mode selection               */  
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

