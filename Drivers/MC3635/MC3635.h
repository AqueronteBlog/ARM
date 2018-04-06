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
