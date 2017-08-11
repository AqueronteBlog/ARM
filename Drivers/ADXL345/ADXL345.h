/**
 * @brief       ADXL345.h
 * @details     3-Axis, ±2 g/±4 g/±8 g/±16 g Digital Accelerometer.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/August/2017
 * @version     11/August/2017    The ORIGIN
 * @pre         Although the ADXL345 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
#define ADXL345_ALT_ADDRESS_LOW                 0x53
#define ADXL345_ALT_ADDRESS_HIGH                0x1D

/**
  * @brief   REGISTERS MAP
  */
#define ADXL345_DEVID                           0x00        /*!<   Device ID                                                    */
#define ADXL345_THRESH_TAP                      0x1D        /*!<   Tap threshold                                                */
#define ADXL345_OFSX                            0x1E        /*!<   X-axis offset                                                */
#define ADXL345_OFSY                            0x1F        /*!<   Y-axis offset                                                */
#define ADXL345_OFSZ                            0x20        /*!<   Z-axis offset                                                */
#define ADXL345_DUR                             0x21        /*!<   Tap duration                                                 */
#define ADXL345_LATENT                          0x22        /*!<   Tap latency                                                  */
#define ADXL345_WINDOW                          0x23        /*!<   Tap window                                                   */
#define ADXL345_THRESH_ACT                      0x24        /*!<   Activity threshold                                           */
#define ADXL345_THRESH_INACT                    0x25        /*!<   Inactivity threshold                                         */
#define ADXL345_TIME_INACT                      0x26        /*!<   Inactivity time                                              */
#define ADXL345_ACT_INACT_CTL                   0x27        /*!<   Axis enable control for activity and inactivity detection    */
#define ADXL345_THRESH_FF                       0x28        /*!<   Free-fall threshold                                          */
#define ADXL345_TIME_FF                         0x29        /*!<   Free-fall time                                               */
#define ADXL345_TAP_AXES                        0x2A        /*!<   Axis control for single tap/double tap                       */
#define ADXL345_ACT_TAP_STATUS                  0x2B        /*!<   Source of single tap/double tap                              */
#define ADXL345_BW_RATE                         0x2C        /*!<   Data rate and power mode control                             */
#define ADXL345_POWER_CTL                       0x2D        /*!<   Power-saving features control                                */
#define ADXL345_INT_ENABLE                      0x2E        /*!<   Interrupt enable control                                     */
#define ADXL345_INT_MAP                         0x2F        /*!<   Interrupt mapping control                                    */
#define ADXL345_INT_SOURCE                      0x30        /*!<   Source of interrupts                                         */
#define ADXL345_DATA_FORMAT                     0x31        /*!<   Data format control                                          */
#define ADXL345_DATAX0                          0x32        /*!<   X-Axis Data 0                                                */
#define ADXL345_DATAX1                          0x33        /*!<   X-Axis Data 1                                                */
#define ADXL345_DATAY0                          0x34        /*!<   Y-Axis Data 0                                                */
#define ADXL345_DATAY1                          0x35        /*!<   Y-Axis Data 1                                                */
#define ADXL345_DATAZ0                          0x36        /*!<   Z-Axis Data 0                                                */
#define ADXL345_DATAZ1                          0x37        /*!<   Z-Axis Data 1                                                */
#define ADXL345_FIFO_CTL                        0x38        /*!<   FIFO control                                                 */
#define ADXL345_FIFO_STATUS                     0x39        /*!<   FIFO status                                                  */


/* Commands Registers */
/**
  * @brief   DEVID
  */
#define DEVID_ID                                0xE5        /*!<   A fixed device ID code                                       */


/**
  * @brief   ACT_INACT_CTL
  */
/* Bit 7 : ACT ac/dc ( D7 ). */
#define ACT_INACT_CTL_ACT_DC_Pos                0x07        /*!<  Position of ACT_DC field.                                      */
#define ACT_INACT_CTL_ACT_DC_Mask               0x80        /*!<  Bit mask of ACT_DC field.                                      */
#define ACT_INACT_CTL_ACT_DC_Enabled            0x01        /*!<  ACT_DC Enabled.                                                */
#define ACT_INACT_CTL_ACT_DC_Disabled           0x00        /*!<  ACT_DC Disabled.                                               */

#define ACT_INACT_CTL_ACT_AC_Pos                0x07        /*!<  Position of INACT_AC field.                                    */
#define ACT_INACT_CTL_ACT_AC_Mask               0x80        /*!<  Bit mask of INACT_AC field.                                    */
#define ACT_INACT_CTL_ACT_AC_Enabled            0x00        /*!<  INACT_AC Enabled.                                              */
#define ACT_INACT_CTL_ACT_AC_Disabled           0x01        /*!<  INACT_AC Disabled.                                             */

/* Bit 6 : ACT_X enable ( D6 ). */
#define ACT_INACT_CTL_ACT_X_Pos                 0x06        /*!<  Position of ACT_X field.                                       */
#define ACT_INACT_CTL_ACT_X_Mask                0x40        /*!<  Bit mask of ACT_X field.                                       */
#define ACT_INACT_CTL_ACT_X_Enabled             0x01        /*!<  ACT_X Enabled.                                                 */
#define ACT_INACT_CTL_ACT_X_Disabled            0x00        /*!<  ACT_X Disabled.                                                */

/* Bit 5 : ACT_Y enable  ( D5 ). */
#define ACT_INACT_CTL_ACT_Y_Pos                 0x05        /*!<  Position of ACT_Y field.                                       */
#define ACT_INACT_CTL_ACT_Y_Mask                0x20        /*!<  Bit mask of ACT_Y field.                                       */
#define ACT_INACT_CTL_ACT_Y_Enabled             0x01        /*!<  ACT_Y Enabled.                                                 */
#define ACT_INACT_CTL_ACT_Y_Disabled            0x00        /*!<  ACT_Y Disabled.                                                */

/* Bit 4 : ACT_Z enable ( D4 ). */
#define ACT_INACT_CTL_ACT_Z_Pos                 0x04        /*!<  Position of ACT_Z field.                                       */
#define ACT_INACT_CTL_ACT_Z_Mask                0x10        /*!<  Bit mask of ACT_Z field.                                       */
#define ACT_INACT_CTL_ACT_Z_Enabled             0x01        /*!<  ACT_Z Enabled.                                                 */
#define ACT_INACT_CTL_ACT_Z_Disabled            0x00        /*!<  ACT_Z Disabled.                                                */

/* Bit 3 : INACT ac/dc ( D3 ). */
#define ACT_INACT_CTL_INACT_DC_Pos              0x03        /*!<  Position of INACT_DC field.                                    */
#define ACT_INACT_CTL_INACT_DC_Mask             0x08        /*!<  Bit mask of INACT_DC field.                                    */
#define ACT_INACT_CTL_INACT_DC_Enabled          0x01        /*!<  INACT_DC Enabled.                                              */
#define ACT_INACT_CTL_INACT_DC_Disabled         0x00        /*!<  INACT_DC Disabled.                                             */

#define ACT_INACT_CTL_INACT_AC_Pos              0x03        /*!<  Position of INACT_AC field.                                    */
#define ACT_INACT_CTL_INACT_AC_Mask             0x08        /*!<  Bit mask of INACT_AC field.                                    */
#define ACT_INACT_CTL_INACT_AC_Enabled          0x00        /*!<  INACT_AC Enabled.                                              */
#define ACT_INACT_CTL_INACT_AC_Disabled         0x01        /*!<  INACT_AC Disabled.                                             */

/* Bit 2 : INACT_X enable ( D2 ). */
#define ACT_INACT_CTL_INACT_X_Pos               0x02        /*!<  Position of INACT_X field.                                     */
#define ACT_INACT_CTL_INACT_X_Mask              0x04        /*!<  Bit mask of INACT_X field.                                     */
#define ACT_INACT_CTL_INACT_X_Enabled           0x01        /*!<  INACT_X Enabled.                                               */
#define ACT_INACT_CTL_INACT_X_Disabled          0x00        /*!<  INACT_X Disabled.                                              */

/* Bit 1 : INACT_Y enable ( D1 ). */
#define ACT_INACT_CTL_INACT_Y_Pos               0x01        /*!<  Position of INACT_Y field.                                     */
#define ACT_INACT_CTL_INACT_Y_Mask              0x02        /*!<  Bit mask of INACT_Y field.                                     */
#define ACT_INACT_CTL_INACT_Y_Enabled           0x01        /*!<  INACT_Y Enabled.                                               */
#define ACT_INACT_CTL_INACT_Y_Disabled          0x00        /*!<  INACT_Y Disabled.                                              */

/* Bit 0 : INACT_Z enable ( D0 ). */
#define ACT_INACT_CTL_INACT_Z_Pos               0x00        /*!<  Position of INACT_Z field.                                     */
#define ACT_INACT_CTL_INACT_Z_Mask              0x01        /*!<  Bit mask of INACT_Z field.                                     */
#define ACT_INACT_CTL_INACT_Z_Enabled           0x01        /*!<  INACT_Z Enabled.                                               */
#define ACT_INACT_CTL_INACT_Z_Disabled          0x00        /*!<  INACT_Z Disabled.                                              */



/**
  * @brief   TAP_AXES
  */
/* Bit 3 : SUPPRESS ( D3 ). */
#define TAP_AXES_SUPPRESS_Pos                   0x03        /*!<  Position of SUPPRESS field.                                    */
#define TAP_AXES_SUPPRESS_Mask                  0x08        /*!<  Bit mask of SUPPRESS field.                                    */
#define TAP_AXES_SUPPRESS_Enabled               0x01        /*!<  SUPPRESS Enabled.                                              */
#define TAP_AXES_SUPPRESS_Disabled              0x00        /*!<  SUPPRESS Disabled.                                             */

/* Bit 2 : TAP_X enable ( D2 ). */
#define TAP_AXES_TAP_X_Pos                      0x02        /*!<  Position of TAP_X field.                                       */
#define TAP_AXES_TAP_X_Mask                     0x04        /*!<  Bit mask of TAP_X field.                                       */
#define TAP_AXES_TAP_X_Enabled                  0x01        /*!<  TAP_X Enabled.                                                 */
#define TAP_AXES_TAP_X_Disabled                 0x00        /*!<  TAP_X Disabled.                                                */

/* Bit 1 : TAP_Y enable  ( D1 ). */
#define TAP_AXES_TAP_Y_Pos                      0x01        /*!<  Position of TAP_Y field.                                       */
#define TAP_AXES_TAP_Y_Mask                     0x02        /*!<  Bit mask of TAP_Y field.                                       */
#define TAP_AXES_TAP_Y_Enabled                  0x01        /*!<  TAP_Y Enabled.                                                 */
#define TAP_AXES_TAP_Y_Disabled                 0x00        /*!<  TAP_Y Disabled.                                                */

/* Bit 0 : TAP_Z enable  ( D0 ). */
#define TAP_AXES_TAP_Z_Pos                      0x00        /*!<  Position of TAP_Z field.                                       */
#define TAP_AXES_TAP_Z_Mask                     0x01        /*!<  Bit mask of TAP_Z field.                                       */
#define TAP_AXES_TAP_Z_Enabled                  0x01        /*!<  TAP_Z Enabled.                                                 */
#define TAP_AXES_TAP_Z_Disabled                 0x00        /*!<  TAP_Z Disabled.                                                */



/**
  * @brief   ACT_TAP_STATUS
  */
/* Bit 6 : ACT_X source ( D6 ). */
#define ACT_TAP_STATUS_ACT_X_Pos                0x06        /*!<  Position of ACT_X field.                                       */
#define ACT_TAP_STATUS_ACT_X_Mask               0x40        /*!<  Bit mask of ACT_X field.                                       */
#define ACT_TAP_STATUS_ACT_X_Enabled            0x01        /*!<  ACT_X Enabled.                                                 */
#define ACT_TAP_STATUS_ACT_X_Disabled           0x00        /*!<  ACT_X Disabled.                                                */

/* Bit 5 : ACT_Y source ( D5 ). */
#define ACT_TAP_STATUS_ACT_Y_Pos                0x05        /*!<  Position of ACT_Y field.                                       */
#define ACT_TAP_STATUS_ACT_Y_Mask               0x20        /*!<  Bit mask of ACT_Y field.                                       */
#define ACT_TAP_STATUS_ACT_Y_Enabled            0x01        /*!<  ACT_Y Enabled.                                                 */
#define ACT_TAP_STATUS_ACT_Y_Disabled           0x00        /*!<  ACT_Y Disabled.                                                */

/* Bit 4 : ACT_Z source ( D4 ). */
#define ACT_TAP_STATUS_ACT_Z_Pos                0x04        /*!<  Position of ACT_Z field.                                       */
#define ACT_TAP_STATUS_ACT_Z_Mask               0x10        /*!<  Bit mask of ACT_Z field.                                       */
#define ACT_TAP_STATUS_ACT_Z_Enabled            0x01        /*!<  ACT_Z Enabled.                                                 */
#define ACT_TAP_STATUS_ACT_Z_Disabled           0x00        /*!<  ACT_Z Disabled.                                                */

/* Bit 3 : Asleep ( D3 ). */
#define ACT_TAP_STATUS_ASLEEP_Pos               0x03        /*!<  Position of ASLEEP field.                                      */
#define ACT_TAP_STATUS_ASLEEP_Mask              0x08        /*!<  Bit mask of ASLEEP field.                                      */
#define ACT_TAP_STATUS_ASLEEP_Enabled           0x01        /*!<  ASLEEP Enabled.                                                */
#define ACT_TAP_STATUS_ASLEEP_Disabled          0x00        /*!<  ASLEEP Disabled.                                               */

/* Bit 2 : TAP_X source  ( D2 ). */
#define ACT_TAP_STATUS_TAP_X_Pos                0x02        /*!<  Position of TAP_X field.                                       */
#define ACT_TAP_STATUS_TAP_X_Mask               0x04        /*!<  Bit mask of TAP_X field.                                       */
#define ACT_TAP_STATUS_TAP_X_Enabled            0x01        /*!<  TAP_X Enabled.                                                 */
#define ACT_TAP_STATUS_TAP_X_Disabled           0x00        /*!<  TAP_X Disabled.                                                */

/* Bit 1 : TAP_Y source  ( D1 ). */
#define ACT_TAP_STATUS_TAP_Y_Pos                0x01        /*!<  Position of TAP_Y field.                                       */
#define ACT_TAP_STATUS_TAP_Y_Mask               0x02        /*!<  Bit mask of TAP_Y field.                                       */
#define ACT_TAP_STATUS_TAP_Y_Enabled            0x01        /*!<  TAP_Y Enabled.                                                 */
#define ACT_TAP_STATUS_TAP_Y_Disabled           0x00        /*!<  TAP_Y Disabled.                                                */

/* Bit 0 : TAP_Z source  ( D0 ). */
#define ACT_TAP_STATUS_TAP_Z_Pos                0x00        /*!<  Position of TAP_Z field.                                       */
#define ACT_TAP_STATUS_TAP_Z_Mask               0x02        /*!<  Bit mask of TAP_Z field.                                       */
#define ACT_TAP_STATUS_TAP_Z_Enabled            0x01        /*!<  TAP_Z Enabled.                                                 */
#define ACT_TAP_STATUS_TAP_Z_Disabled           0x00        /*!<  TAP_Z Disabled.                                                */


/**
  * @brief   BW_RATE
  */
/* Bit 4 : LOW_POWER ( D4 ). */
#define BW_RATE_LOW_POWER_Pos                   0x04        /*!<  Position of LOW_POWER field.                                    */
#define BW_RATE_LOW_POWER_Mask                  0x10        /*!<  Bit mask of LOW_POWER field.                                    */
#define BW_RATE_LOW_POWER_Enabled               0x01        /*!<  LOW_POWER Enabled.                                              */
#define BW_RATE_LOW_POWER_Disabled              0x00        /*!<  LOW_POWER Disabled.                                             */

/* Bit 3 - 0 : RATE ( D3 - D0 ). */
/* Normal operation */
#define BW_RATE_RATE_Pos                        0x00        /*!<  Position of RATE field.                                         */
#define BW_RATE_RATE_Mask                       0x0F        /*!<  Bit mask of RATE field.                                         */
#define BW_RATE_RATE_3200HZ                     0x0F        /*!<  RATE 3200 Hz.                                                   */
#define BW_RATE_RATE_1600HZ                     0x0E        /*!<  RATE 1600 Hz.                                                   */
#define BW_RATE_RATE_800HZ                      0x0D        /*!<  RATE 800 Hz.                                                    */
#define BW_RATE_RATE_400HZ                      0x0C        /*!<  RATE 400 Hz.                                                    */
#define BW_RATE_RATE_200HZ                      0x0B        /*!<  RATE 200 Hz.                                                    */
#define BW_RATE_RATE_100HZ                      0x0A        /*!<  RATE 100 Hz. ( DEFAULT )                                        */
#define BW_RATE_RATE_50HZ                       0x09        /*!<  RATE 50 Hz.                                                     */
#define BW_RATE_RATE_25HZ                       0x08        /*!<  RATE 25 Hz.                                                     */
#define BW_RATE_RATE_12_5HZ                     0x07        /*!<  RATE 12.5 Hz.                                                   */
#define BW_RATE_RATE_6_25HZ                     0x06        /*!<  RATE 6.25 Hz.                                                   */
#define BW_RATE_RATE_3_13HZ                     0x05        /*!<  RATE 3.13 Hz.                                                   */
#define BW_RATE_RATE_1_56HZ                     0x04        /*!<  RATE 1.56 Hz.                                                   */
#define BW_RATE_RATE_0_78HZ                     0x03        /*!<  RATE 0.78 Hz.                                                   */
#define BW_RATE_RATE_0_39HZ                     0x02        /*!<  RATE 0.39 Hz.                                                   */
#define BW_RATE_RATE_0_20HZ                     0x01        /*!<  RATE 0.20 Hz.                                                   */
#define BW_RATE_RATE_0_10HZ                     0x00        /*!<  RATE 0.10 Hz.                                                   */

/* Low Power operation */
#define BW_RATE_RATE_LOW_POWER_400HZ            0x0C        /*!<  RATE 400 Hz.                                                    */
#define BW_RATE_RATE_LOW_POWER_200HZ            0x0B        /*!<  RATE 200 Hz.                                                    */
#define BW_RATE_RATE_LOW_POWER_100HZ            0x0A        /*!<  RATE 100 Hz. ( DEFAULT )                                        */
#define BW_RATE_RATE_LOW_POWER_50HZ             0x09        /*!<  RATE 50 Hz.                                                     */
#define BW_RATE_RATE_LOW_POWER_25HZ             0x08        /*!<  RATE 25 Hz.                                                     */
#define BW_RATE_RATE_LOW_POWER_12_5HZ           0x07        /*!<  RATE 12.5 Hz.                                                   */


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
#define POWER_CTL_MEASURE_Pos                   0x03        /*!<  Position of MEASURE field.                                        */
#define POWER_CTL_MEASURE_Mask                  0x08        /*!<  Bit mask of MEASURE field.                                        */
#define POWER_CTL_MEASURE_Enabled               0x01        /*!<  MEASURE Enabled.                                                  */
#define POWER_CTL_MEASURE_Disabled              0x00        /*!<  MEASURE Disabled.                                                 */

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
  * @brief   INT_ENABLE
  */
/* Bit 7 : DATA_READY ( D7 ). */
#define INT_ENABLE_DATA_READY_Pos                0x07        /*!<  Position of DATA_READY field.                                     */
#define INT_ENABLE_DATA_READY_Mask               0x80        /*!<  Bit mask of DATA_READY field.                                     */
#define INT_ENABLE_DATA_READY_Enabled            0x01        /*!<  DATA_READY Enabled.                                               */
#define INT_ENABLE_DATA_READY_Disabled           0x00        /*!<  DATA_READY Disabled.                                              */

/* Bit 6 : SINGLE_TAP ( D6 ). */
#define INT_ENABLE_SINGLE_TAP_Pos                0x06        /*!<  Position of SINGLE_TAP field.                                     */
#define INT_ENABLE_SINGLE_TAP_Mask               0x40        /*!<  Bit mask of SINGLE_TAP field.                                     */
#define INT_ENABLE_SINGLE_TAP_Enabled            0x01        /*!<  SINGLE_TAP Enabled.                                               */
#define INT_ENABLE_SINGLE_TAP_Disabled           0x00        /*!<  SINGLE_TAP Disabled.                                              */

/* Bit 5 : DOUBLE_TAP ( D5 ). */
#define INT_ENABLE_DOUBLE_TAP_Pos                0x06        /*!<  Position of DOUBLE_TAP field.                                     */
#define INT_ENABLE_DOUBLE_TAP_Mask               0x20        /*!<  Bit mask of DOUBLE_TAP field.                                     */
#define INT_ENABLE_DOUBLE_TAP_Enabled            0x01        /*!<  DOUBLE_TAP Enabled.                                               */
#define INT_ENABLE_DOUBLE_TAP_Disabled           0x00        /*!<  DOUBLE_TAP Disabled.                                              */

/* Bit 4 : ACTIVITY ( D4 ). */
#define INT_ENABLE_ACTIVITY_Pos                  0x04        /*!<  Position of ACTIVITY field.                                       */
#define INT_ENABLE_ACTIVITY_Mask                 0x10        /*!<  Bit mask of ACTIVITY field.                                       */
#define INT_ENABLE_ACTIVITY_Enabled              0x01        /*!<  ACTIVITY Enabled.                                                 */
#define INT_ENABLE_ACTIVITY_Disabled             0x00        /*!<  ACTIVITY Disabled.                                                */

/* Bit 3 : ACTIVITY ( D3 ). */
#define INT_ENABLE_INACTIVITY_Pos                0x03        /*!<  Position of INACTIVITY field.                                     */
#define INT_ENABLE_INACTIVITY_Mask               0x08        /*!<  Bit mask of INACTIVITY field.                                     */
#define INT_ENABLE_INACTIVITY_Enabled            0x01        /*!<  INACTIVITY Enabled.                                               */
#define INT_ENABLE_INACTIVITY_Disabled           0x00        /*!<  INACTIVITY Disabled.                                              */

/* Bit 2 : FREE_FALL ( D2 ). */
#define INT_ENABLE_FREE_FALL_Pos                 0x02        /*!<  Position of FREE_FALL field.                                      */
#define INT_ENABLE_FREE_FALL_Mask                0x04        /*!<  Bit mask of FREE_FALL field.                                      */
#define INT_ENABLE_FREE_FALL_Enabled             0x01        /*!<  FREE_FALL Enabled.                                                */
#define INT_ENABLE_FREE_FALL_Disabled            0x00        /*!<  FREE_FALL Disabled.                                               */

/* Bit 1 : WATERMARK ( D1 ). */
#define INT_ENABLE_WATERMARK_Pos                 0x01        /*!<  Position of WATERMARK field.                                      */
#define INT_ENABLE_WATERMARK_Mask                0x02        /*!<  Bit mask of WATERMARK field.                                      */
#define INT_ENABLE_WATERMARK_Enabled             0x01        /*!<  WATERMARK Enabled.                                                */
#define INT_ENABLE_WATERMARK_Disabled            0x00        /*!<  WATERMARK Disabled.                                               */

/* Bit 0 : OVERRUN ( D0 ). */
#define INT_ENABLE_OVERRUN_Pos                   0x00        /*!<  Position of OVERRUN field.                                        */
#define INT_ENABLE_OVERRUN_Mask                  0x01        /*!<  Bit mask of OVERRUN field.                                        */
#define INT_ENABLE_OVERRUN_Enabled               0x01        /*!<  OVERRUN Enabled.                                                  */
#define INT_ENABLE_OVERRUN_Disabled              0x00        /*!<  OVERRUN Disabled.                                                 */


/**
  * @brief   INT_SOURCE
  */
/* Bit 7 : DATA_READY ( D7 ). */
#define INT_SOURCE_DATA_READY_Pos                0x07        /*!<  Position of DATA_READY field.                                     */
#define INT_SOURCE_DATA_READY_Mask               0x80        /*!<  Bit mask of DATA_READY field.                                     */
#define INT_SOURCE_DATA_READY_Enabled            0x01        /*!<  DATA_READY Enabled.                                               */
#define INT_SOURCE_DATA_READY_Disabled           0x00        /*!<  DATA_READY Disabled.                                              */

/* Bit 6 : SINGLE_TAP ( D6 ). */
#define INT_SOURCE_SINGLE_TAP_Pos                0x06        /*!<  Position of SINGLE_TAP field.                                     */
#define INT_SOURCE_SINGLE_TAP_Mask               0x40        /*!<  Bit mask of SINGLE_TAP field.                                     */
#define INT_SOURCE_SINGLE_TAP_Enabled            0x01        /*!<  SINGLE_TAP Enabled.                                               */
#define INT_SOURCE_SINGLE_TAP_Disabled           0x00        /*!<  SINGLE_TAP Disabled.                                              */

/* Bit 5 : DOUBLE_TAP ( D5 ). */
#define INT_SOURCE_DOUBLE_TAP_Pos                0x06        /*!<  Position of DOUBLE_TAP field.                                     */
#define INT_SOURCE_DOUBLE_TAP_Mask               0x20        /*!<  Bit mask of DOUBLE_TAP field.                                     */
#define INT_SOURCE_DOUBLE_TAP_Enabled            0x01        /*!<  DOUBLE_TAP Enabled.                                               */
#define INT_SOURCE_DOUBLE_TAP_Disabled           0x00        /*!<  DOUBLE_TAP Disabled.                                              */

/* Bit 4 : ACTIVITY ( D4 ). */
#define INT_SOURCE_ACTIVITY_Pos                  0x04        /*!<  Position of ACTIVITY field.                                       */
#define INT_SOURCE_ACTIVITY_Mask                 0x10        /*!<  Bit mask of ACTIVITY field.                                       */
#define INT_SOURCE_ACTIVITY_Enabled              0x01        /*!<  ACTIVITY Enabled.                                                 */
#define INT_SOURCE_ACTIVITY_Disabled             0x00        /*!<  ACTIVITY Disabled.                                                */

/* Bit 3 : ACTIVITY ( D3 ). */
#define INT_SOURCE_INACTIVITY_Pos                0x03        /*!<  Position of INACTIVITY field.                                     */
#define INT_SOURCE_INACTIVITY_Mask               0x08        /*!<  Bit mask of INACTIVITY field.                                     */
#define INT_SOURCE_INACTIVITY_Enabled            0x01        /*!<  INACTIVITY Enabled.                                               */
#define INT_SOURCE_INACTIVITY_Disabled           0x00        /*!<  INACTIVITY Disabled.                                              */

/* Bit 2 : FREE_FALL ( D2 ). */
#define INT_SOURCE_FREE_FALL_Pos                 0x02        /*!<  Position of FREE_FALL field.                                      */
#define INT_SOURCE_FREE_FALL_Mask                0x04        /*!<  Bit mask of FREE_FALL field.                                      */
#define INT_SOURCE_FREE_FALL_Enabled             0x01        /*!<  FREE_FALL Enabled.                                                */
#define INT_SOURCE_FREE_FALL_Disabled            0x00        /*!<  FREE_FALL Disabled.                                               */

/* Bit 1 : WATERMARK ( D1 ). */
#define INT_SOURCE_WATERMARK_Pos                 0x01        /*!<  Position of WATERMARK field.                                      */
#define INT_SOURCE_WATERMARK_Mask                0x02        /*!<  Bit mask of WATERMARK field.                                      */
#define INT_SOURCE_WATERMARK_Enabled             0x01        /*!<  WATERMARK Enabled.                                                */
#define INT_SOURCE_WATERMARK_Disabled            0x00        /*!<  WATERMARK Disabled.                                               */

/* Bit 0 : OVERRUN ( D0 ). */
#define INT_SOURCE_OVERRUN_Pos                   0x00        /*!<  Position of OVERRUN field.                                        */
#define INT_SOURCE_OVERRUN_Mask                  0x01        /*!<  Bit mask of OVERRUN field.                                        */
#define INT_SOURCE_OVERRUN_Enabled               0x01        /*!<  OVERRUN Enabled.                                                  */
#define INT_SOURCE_OVERRUN_Disabled              0x00        /*!<  OVERRUN Disabled.                                                 */


/**
  * @brief   DATA_FORMAT
  */
/* Bit 7 : SELF_TEST ( D7 ). */
#define DATA_FORMAT_SELF_TEST_Pos                0x07        /*!<  Position of SELF_TEST field.                                      */
#define DATA_FORMAT_SELF_TEST_Mask               0x80        /*!<  Bit mask of SELF_TEST field.                                      */
#define DATA_FORMAT_SELF_TEST_Enabled            0x01        /*!<  SELF_TEST Enabled.                                                */
#define DATA_FORMAT_SELF_TEST_Disabled           0x00        /*!<  SELF_TEST Disabled.                                               */

/* Bit 6 : SPI ( D6 ). */
#define DATA_FORMAT_SPI_Pos                      0x06        /*!<  Position of SPI field.                                            */
#define DATA_FORMAT_SPI_Mask                     0x40        /*!<  Bit mask of SPI field.                                            */
#define DATA_FORMAT_SPI_Enabled                  0x01        /*!<  SPI Enabled.                                                      */
#define DATA_FORMAT_SPI_Disabled                 0x00        /*!<  SPI Disabled.                                                     */

/* Bit 5 : INT_INVERT ( D5 ). */
#define DATA_FORMAT_INT_INVERT_Pos               0x05        /*!<  Position of INT_INVERT field.                                      */
#define DATA_FORMAT_INT_INVERT_Mask              0x20        /*!<  Bit mask of INT_INVERT field.                                      */
#define DATA_FORMAT_INT_INVERT_Enabled           0x01        /*!<  INT_INVERT Enabled.                                                */
#define DATA_FORMAT_INT_INVERT_Disabled          0x00        /*!<  INT_INVERT Disabled.                                               */

/* Bit 3 : FULL_RES ( D3 ). */
#define DATA_FORMAT_FULL_RES_Pos                 0x03        /*!<  Position of FULL_RES field.                                        */
#define DATA_FORMAT_FULL_RES_Mask                0x08        /*!<  Bit mask of FULL_RES field.                                        */
#define DATA_FORMAT_FULL_RES_Enabled             0x01        /*!<  FULL_RES Enabled.                                                  */
#define DATA_FORMAT_FULL_RES_Disabled            0x00        /*!<  FULL_RES Disabled.                                                 */

/* Bit 2 : JUSTIFY ( D2 ). */
#define DATA_FORMAT_JUSTIFY_Pos                  0x02        /*!<  Position of JUSTIFY field.                                         */
#define DATA_FORMAT_JUSTIFY_Mask                 0x04        /*!<  Bit mask of JUSTIFY field.                                         */
#define DATA_FORMAT_JUSTIFY_Enabled              0x01        /*!<  JUSTIFY Enabled.                                                   */
#define DATA_FORMAT_JUSTIFY_Disabled             0x00        /*!<  JUSTIFY Disabled.                                                  */

/* Bit 1 - 0 : RANGE ( D1 - D0 ). */
#define DATA_FORMAT_RANGE_Pos                    0x00        /*!<  Position of RANGE field.                                           */
#define DATA_FORMAT_RANGE_Mask                   0x03        /*!<  Bit mask of RANGE field.                                           */
#define DATA_FORMAT_RANGE_2_G                    0x00        /*!<  RANGE ±2g.                                                         */
#define DATA_FORMAT_RANGE_4_G                    0x01        /*!<  RANGE ±4g.                                                         */
#define DATA_FORMAT_RANGE_8_G                    0x02        /*!<  RANGE ±8g.                                                         */
#define DATA_FORMAT_RANGE_16_G                   0x03        /*!<  RANGE ±16g.                                                        */


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





/**
  * @brief   INTERNAL CONSTANTS
  */
#define ADXL345_SUCCESS                                              0x00
#define ADXL345_FAILURE                                              0x01



/**
  * @brief   INTERNAL VARIABLES
  */
uint32_t    ADXL345_Mode;



/**
  * @brief   FUNCTION PROTOTYPES
  */
uint32_t  ADXL345_GetID          ( NRF_TWI_Type* myinstance, uint32_t ADDR, uint8_t* myID );

