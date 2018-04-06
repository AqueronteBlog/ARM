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
    MC3635_ALT_ADDRESS_LOW     =   0x53,
    MC3635_ALT_ADDRESS_HIGH    =   0x1D
} MC3635_address_t;


/**
  * @brief   REGISTERS MAP
  */
#define MC3635_DEVID                           0x00        /*!<   Device ID                                                    */
#define MC3635_THRESH_TAP                      0x1D        /*!<   Tap threshold                                                */
#define MC3635_OFSX                            0x1E        /*!<   X-axis offset                                                */
#define MC3635_OFSY                            0x1F        /*!<   Y-axis offset                                                */
#define MC3635_OFSZ                            0x20        /*!<   Z-axis offset                                                */
#define MC3635_DUR                             0x21        /*!<   Tap duration                                                 */
#define MC3635_LATENT                          0x22        /*!<   Tap latency                                                  */
#define MC3635_WINDOW                          0x23        /*!<   Tap window                                                   */
#define MC3635_THRESH_ACT                      0x24        /*!<   Activity threshold                                           */
#define MC3635_THRESH_INACT                    0x25        /*!<   Inactivity threshold                                         */
#define MC3635_TIME_INACT                      0x26        /*!<   Inactivity time                                              */
#define MC3635_ACT_INACT_CTL                   0x27        /*!<   Axis enable control for activity and inactivity detection    */
#define MC3635_THRESH_FF                       0x28        /*!<   Free-fall threshold                                          */
#define MC3635_TIME_FF                         0x29        /*!<   Free-fall time                                               */
#define MC3635_TAP_AXES                        0x2A        /*!<   Axis control for single tap/double tap                       */
#define MC3635_ACT_TAP_STATUS                  0x2B        /*!<   Source of single tap/double tap                              */
#define MC3635_BW_RATE                         0x2C        /*!<   Data rate and power mode control                             */
#define MC3635_POWER_CTL                       0x2D        /*!<   Power-saving features control                                */
#define MC3635_INT_ENABLE                      0x2E        /*!<   Interrupt enable control                                     */
#define MC3635_INT_MAP                         0x2F        /*!<   Interrupt mapping control                                    */
#define MC3635_INT_SOURCE                      0x30        /*!<   Source of interrupts                                         */
#define MC3635_DATA_FORMAT                     0x31        /*!<   Data format control                                          */
#define MC3635_DATAX0                          0x32        /*!<   X-Axis Data 0                                                */
#define MC3635_DATAX1                          0x33        /*!<   X-Axis Data 1                                                */
#define MC3635_DATAY0                          0x34        /*!<   Y-Axis Data 0                                                */
#define MC3635_DATAY1                          0x35        /*!<   Y-Axis Data 1                                                */
#define MC3635_DATAZ0                          0x36        /*!<   Z-Axis Data 0                                                */
#define MC3635_DATAZ1                          0x37        /*!<   Z-Axis Data 1                                                */
#define MC3635_FIFO_CTL                        0x38        /*!<   FIFO control                                                 */
#define MC3635_FIFO_STATUS                     0x39        /*!<   FIFO status                                                  */


/* Commands Registers */
/**
  * @brief   DEVID
  */
#define DEVID_ID                                0xE5        /*!<   A fixed device ID code                                       */


/**
  * @brief   ACT_INACT_CTL
  */
/* Bit 7 : ACT ac/dc ( D7 ). */
typedef enum{
    ACTIVITY_DC_Enabled     =   1,                          /*!<  Activity DC-Coupled Enabled.                                   */
    ACTIVITY_AC_Enabled     =   2                           /*!<  Activity AC-Coupled Enabled.                                   */
} MC3635_act_inact_ctl_activity_dc_coupled_t;


/* Bit 6 - 4 : ACT_X ( D6 ), ACT_Y ( D5 ) y ACT_Z enable ( D4 ). */
typedef enum{
    ACT_X_Enabled     =   1,                                /*!<  X-axis Enabled.                                                */
    ACT_Y_Enabled     =   2,                                /*!<  Y-axis Enabled.                                                */
    ACT_Z_Enabled     =   3,                                /*!<  Z-axis Enabled.                                                */
    ACT_YZ_Enabled    =   4,                                /*!<  YZ-axis Enabled.                                               */
    ACT_XZ_Enabled    =   5,                                /*!<  XZ-axis Enabled.                                               */
    ACT_XY_Enabled    =   6,                                /*!<  XY-axis Enabled.                                               */
    ACT_XYZ_Enabled   =   7,                                /*!<  XYZ-axis Enabled.                                              */
    ACT_XYZ_Disabled  =   8                                 /*!<  XYZ-axis Disabled.                                             */
} MC3635_act_inact_ctl_activity_axis_t;


/* Bit 3 : INACT ac/dc ( D3 ). */
typedef enum{
    INACTIVITY_DC_Enabled     =   1,                        /*!<  Inactivity DC-Coupled Enabled.                                 */
    INACTIVITY_AC_Enabled     =   2                         /*!<  Inactivity AC-Coupled Enabled.                                 */
} MC3635_act_inact_ctl_inactivity_dc_coupled_t;


/* Bit 2 - 0 : INACT_X ( D2 ), INACT_X ( D1 ) y INACT_X enable ( D0 ). */
typedef enum{
    INACT_X_Enabled     =   1,                              /*!<  X-axis Enabled.                                                */
    INACT_Y_Enabled     =   2,                              /*!<  Y-axis Enabled.                                                */
    INACT_Z_Enabled     =   3,                              /*!<  Z-axis Enabled.                                                */
    INACT_YZ_Enabled    =   4,                              /*!<  YZ-axis Enabled.                                               */
    INACT_XZ_Enabled    =   5,                              /*!<  XZ-axis Enabled.                                               */
    INACT_XY_Enabled    =   6,                              /*!<  XY-axis Enabled.                                               */
    INACT_XYZ_Enabled   =   7,                              /*!<  XYZ-axis Enabled.                                              */
    INACT_XYZ_Disabled  =   8                               /*!<  XYZ-axis Disabled.                                             */
} MC3635_act_inact_ctl_inactivity_axis_t;



/**
  * @brief   TAP_AXES
  */
/* Bit 3 : SUPPRESS ( D3 ). */
typedef enum{
    SUPPRESS_Enabled     =   1,                             /*!<  SUPPRESS Enabled.                                             */
    SUPPRESS_Disabled    =   2                              /*!<  SUPPRESS Disabled.                                            */
} MC3635_tap_axes_suppress_t;

/* Bit 2 - 0 : TAP_X ( D2 ), TAP_Y ( D1 ) y TAP_Z enable ( D0 ). */
typedef enum{
    TAP_X_Enabled     =   1,                                /*!<  X-axis Enabled.                                                */
    TAP_Y_Enabled     =   2,                                /*!<  Y-axis Enabled.                                                */
    TAP_Z_Enabled     =   3,                                /*!<  Z-axis Enabled.                                                */
    TAP_YZ_Enabled    =   4,                                /*!<  YZ-axis Enabled.                                               */
    TAP_XZ_Enabled    =   5,                                /*!<  XZ-axis Enabled.                                               */
    TAP_XY_Enabled    =   6,                                /*!<  XY-axis Enabled.                                               */
    TAP_XYZ_Enabled   =   7,                                /*!<  XYZ-axis Enabled.                                              */
    TAP_XYZ_Disabled  =   8                                 /*!<  XYZ-axis Disabled.                                             */
} MC3635_tap_axes_axis_t;



/**
  * @brief   BW_RATE
  */
/* Bit 4 : LOW_POWER ( D4 ). */
typedef enum{
    BW_RATE_LOW_POWER_Enabled       =       true,        /*!<  LOW_POWER Enabled.                                              */
    BW_RATE_LOW_POWER_Disabled      =       false        /*!<  LOW_POWER Disabled.                                             */
} AXDL345_bw_rate_low_power_t;


/* Bit 3 - 0 : RATE ( D3 - D0 ). */
/* Normal operation */
typedef enum{
    BW_RATE_RATE_3200HZ         =       0x0F,        /*!<  RATE 3200 Hz.                                                   */
    BW_RATE_RATE_1600HZ         =       0x0E,        /*!<  RATE 1600 Hz.                                                   */
    BW_RATE_RATE_800HZ          =       0x0D,        /*!<  RATE 800 Hz.                                                    */
    BW_RATE_RATE_400HZ          =       0x0C,        /*!<  RATE 400 Hz.                                                    */
    BW_RATE_RATE_200HZ          =       0x0B,        /*!<  RATE 200 Hz.                                                    */
    BW_RATE_RATE_100HZ          =       0x0A,        /*!<  RATE 100 Hz. ( DEFAULT )                                        */
    BW_RATE_RATE_50HZ           =       0x09,        /*!<  RATE 50 Hz.                                                     */
    BW_RATE_RATE_25HZ           =       0x08,        /*!<  RATE 25 Hz.                                                     */
    BW_RATE_RATE_12_5HZ         =       0x07,        /*!<  RATE 12.5 Hz.                                                   */
    BW_RATE_RATE_6_25HZ         =       0x06,        /*!<  RATE 6.25 Hz.                                                   */
    BW_RATE_RATE_3_13HZ         =       0x05,        /*!<  RATE 3.13 Hz.                                                   */
    BW_RATE_RATE_1_56HZ         =       0x04,        /*!<  RATE 1.56 Hz.                                                   */
    BW_RATE_RATE_0_78HZ         =       0x03,        /*!<  RATE 0.78 Hz.                                                   */
    BW_RATE_RATE_0_39HZ         =       0x02,        /*!<  RATE 0.39 Hz.                                                   */
    BW_RATE_RATE_0_20HZ         =       0x01,        /*!<  RATE 0.20 Hz.                                                   */
    BW_RATE_RATE_0_10HZ         =       0x00         /*!<  RATE 0.10 Hz.                                                   */
} AXDL345_bw_rate_rate_t;



/**
  * @brief   POWER_CTL
  */
/* Bit 5 : LINK ( D5 ). */
#define POWER_CTL_LINK_Pos                      0x05        /*!<  Position of LINK field.                                         */
#define POWER_CTL_LINK_Mask                     0x20        /*!<  Bit mask of LINK field.                                         */
#define POWER_CTL_LINK_Enabled                  0x01        /*!<  LINK Enabled.                                                   */
#define POWER_CTL_LINK_Disabled                 0x00        /*!<  LINK Disabled.                                                  */

/* Bit 4 : AUTO_SLEEP ( D4 ). */
#define POWER_CTL_AUTO_SLEEP_Pos                0x04        /*!<  Position of AUTO_SLEEP field.                                    */
#define POWER_CTL_AUTO_SLEEP_Mask               0x10        /*!<  Bit mask of AUTO_SLEEP field.                                    */
#define POWER_CTL_AUTO_SLEEP_Enabled            0x01        /*!<  AUTO_SLEEP Enabled.                                              */
#define POWER_CTL_AUTO_SLEEP_Disabled           0x00        /*!<  AUTO_SLEEP Disabled.                                             */

/* Bit 3 : MEASURE ( D3 ). */
typedef enum{
    MEASURE_MODE        =       true,        /*!<  MEASURE Enabled.                                                  */
    STANDBY_MODE        =       false        /*!<  MEASURE Disabled, Standby mode.                                   */
} AXDL345_power_ctl_measure_t;



/* Bit 2 : SLEEP ( D2 ). */
#define POWER_CTL_SLEEP_Pos                     0x02        /*!<  Position of SLEEP field.                                          */
#define POWER_CTL_SLEEP_Mask                    0x04        /*!<  Bit mask of SLEEP field.                                          */
#define POWER_CTL_SLEEP_Enabled                 0x01        /*!<  SLEEP Enabled.                                                    */
#define POWER_CTL_SLEEP_Disabled                0x00        /*!<  SLEEP Disabled.                                                   */

/* Bit 1 - 0 : WAKEUP ( D1 - D0 ). */
#define POWER_CTL_WAKEUP_Pos                    0x00        /*!<  Position of WAKEUP field.                                          */
#define POWER_CTL_WAKEUP_Mask                   0x03        /*!<  Bit mask of WAKEUP field.                                          */
#define POWER_CTL_WAKEUP_FREQ_8HZ               0x00        /*!<  WAKEUP frequency 8Hz.                                              */
#define POWER_CTL_WAKEUP_FREQ_4HZ               0x01        /*!<  WAKEUP frequency 4Hz.                                              */
#define POWER_CTL_WAKEUP_FREQ_2HZ               0x02        /*!<  WAKEUP frequency 3Hz.                                              */
#define POWER_CTL_WAKEUP_FREQ_1HZ               0x03        /*!<  WAKEUP frequency 1Hz.                                              */



/**
  * @brief   INT_MAP
  */
/* Bit 7 - 0 : */
typedef enum{
    INT_DATA_READY          =       0x80,                   /*!<  Data ready.                                                       */
    INT_SINGLE_TAP          =       0x40,                   /*!<  single tap.                                                       */
    INT_DOUBLE_TAP          =       0x20,                   /*!<  double tap.                                                       */
    INT_ACTIVITY            =       0x10,                   /*!<  activity.                                                         */
    INT_INACTIVITY          =       0x08,                   /*!<  inactivity.                                                       */
    INT_FREE_FALL           =       0x04,                   /*!<  Free fall.                                                        */
    INT_WATERMARK           =       0x02,                   /*!<  Watermark.                                                        */
    INT_OVERRUN             =       0x01                    /*!<  Overrun.                                                          */
} AXDL345_int_map_t;

typedef enum{
    INT1_PIN                =       0x01,                   /*!<  PIN 1                                                             */
    INT2_PIN                =       0x02                    /*!<  PIN 2                                                             */
} AXDL345_int_pin_t;


/**
  * @brief   DATA_FORMAT
  */
/* Bit 7 : SELF_TEST ( D7 ). */
typedef enum{
    DATA_FORMAT_SELF_TEST_Enabled       =       true,        /*!<  SELF_TEST Enabled.                                                */
    DATA_FORMAT_SELF_TEST_Disabled      =       false        /*!<  SELF_TEST Disabled.                                               */
} MC3635_data_format_self_test_t;


/* Bit 6 : SPI ( D6 ). */
typedef enum{
    DATA_FORMAT_SPI_Enabled             =       true,        /*!<  3-wire SPI Enabled.                                               */
    DATA_FORMAT_SPI_Disabled            =       false        /*!<  4-wire SPI Enabled.                                               */
} MC3635_data_format_spi_t;


/* Bit 5 : INT_INVERT ( D5 ). */
typedef enum{
    DATA_FORMAT_INT_INVERT_Enabled             =       true,        /*!<  INT_INVERT Enabled.                                                */
    DATA_FORMAT_INT_INVERT_Disabled            =       false        /*!<  INT_INVERT Disabled.                                               */
} MC3635_data_format_int_invert_t;


/* Bit 3 : FULL_RES ( D3 ). */
typedef enum{
    DATA_FORMAT_FULL_RES_Enabled             =       true,        /*!<  FULL_RES Enabled.                                                */
    DATA_FORMAT_FULL_RES_Disabled            =       false        /*!<  FULL_RES Disabled.                                               */
} MC3635_data_format_full_res_t;


/* Bit 2 : JUSTIFY ( D2 ). */
typedef enum{
    DATA_FORMAT_JUSTIFY_Enabled             =       true,        /*!<  JUSTIFY Enabled.                                                */
    DATA_FORMAT_JUSTIFY_Disabled            =       false        /*!<  JUSTIFY Disabled.                                               */
} MC3635_data_format_justify_t;


/* Bit 1 - 0 : RANGE ( D1 - D0 ). */
typedef enum{
    DATA_FORMAT_RANGE_2_G       =       0x00,        /*!<  RANGE ±2g.                                                         */
    DATA_FORMAT_RANGE_4_G       =       0x01,        /*!<  RANGE ±4g.                                                         */
    DATA_FORMAT_RANGE_8_G       =       0x02,        /*!<  RANGE ±8g.                                                         */
    DATA_FORMAT_RANGE_16_G      =       0x03         /*!<  RANGE ±16g.                                                        */
} MC3635_data_format_range_t;



/**
  * @brief   FIFO_CTL
  */
/* Bit 7 - 6 : FIFO_MODE ( D7 - D6 ). */
#define FIFO_CTL_FIFO_MODE_Pos                    0x07        /*!<  Position of FIFO_MODE field.                                      */
#define FIFO_CTL_FIFO_MODE_Mask                   0xC0        /*!<  Bit mask of FIFO_MODE field.                                      */
#define FIFO_CTL_FIFO_MODE_BYPASS                 0x00        /*!<  FIFO_MODE BYPASS mode.                                            */
#define FIFO_CTL_FIFO_MODE_FIFO                   0x01        /*!<  FIFO_MODE FIFO mode.                                              */
#define FIFO_CTL_FIFO_MODE_STREAM                 0x02        /*!<  FIFO_MODE STREAM mode.                                            */
#define FIFO_CTL_FIFO_MODE_TRIGGER                0x03        /*!<  FIFO_MODE TRIGGER mode.                                           */

/* Bit 5 : TRIGGER ( D5 ). */
#define TRIGGER_FIFO_MODE_Pos                     0x05        /*!<  Position of TRIGGER field.                                        */
#define TRIGGER_FIFO_MODE_Mask                    0x20        /*!<  Bit mask of TRIGGER field.                                        */
#define TRIGGER_FIFO_MODE_Enabled                 0x01        /*!<  TRIGGER Enabled.                                                  */
#define TRIGGER_FIFO_MODE_Disabled                0x00        /*!<  TRIGGER Disabled.                                                 */


/**
  * @brief   FIFO_STATUS
  */
/* Bit 7 : FIFO_TRIG ( D7 ). */
#define FIFO_STATUS_FIFO_TRIG_Pos                  0x07        /*!<  Position of FIFO_TRIG field.                                     */
#define FIFO_STATUS_FIFO_TRIG_Mask                 0x80        /*!<  Bit mask of FIFO_TRIG field.                                     */
#define FIFO_STATUS_FIFO_TRIG_Enabled              0x01        /*!<  FIFO_TRIG Enabled.                                               */
#define FIFO_STATUS_FIFO_TRIG_Disabled             0x00        /*!<  FIFO_TRIG Disabled.                                              */




#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct{
    int16_t XAxis;
    int16_t YAxis;
    int16_t ZAxis;
} Vector_t;


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
