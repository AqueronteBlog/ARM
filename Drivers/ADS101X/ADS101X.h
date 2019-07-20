/**
 * @brief       ADS101X.h
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 3.3-kSPS, 12-Bit ADCs. With Internal Reference, Oscillator, and Programmable Comparator.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019    The ORIGIN
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
  ADS101X_ADDRESS_GND   =   0b1001000,       /*!<   I2C slave address byte, ADDR = GND        */
  ADS101X_ADDRESS_VDD   =   0b1001001,       /*!<   I2C slave address byte, ADDR = VDD        */
  ADS101X_ADDRESS_SDA   =   0b1001010,       /*!<   I2C slave address byte, ADDR = SDA        */
  ADS101X_ADDRESS_SCL   =   0b1001011        /*!<   I2C slave address byte, ADDR = SCL        */
} ADS101X_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  ADS101X_CONVERSION  =   0x00,             /*!<  Conversion register                           */
  ADS101X_CONFIG      =   0x01,             /*!<  Config register                               */
  ADS101X_LO_THRESH   =   0x02,             /*!<  Lo threshold register                         */
  ADS101X_HI_THRESH   =   0x03              /*!<  Hi threshold register                         */
} ADS101X_register_map_t;



/**
  * @brief   DEVICE.
  *           NOTE: The user MUST define which device to use: ADS1013, ADS1014 or ADS1015.
  */
typedef enum
{
    DEVICE_ADS1013    =   0x00,             /*!<  Device: ADS1013                                */
    DEVICE_ADS1014    =   0x01,             /*!<  Device: ADS1014                                */
    DEVICE_ADS1015    =   0x02              /*!<  Device: ADS1015                                */
} ADS101X_device_t;



/**
  * @brief   CONVERSION REGISTER. ( Default: 0x0000 )
  *           NOTE: The 16-bit Conversion register contains the result of the last conversion in binary two's complement format.
  *                 Following power-up, the Conversion register is cleared to 0, and remains 0 until the first conversion is completed.
  */
/* D <15:4>
 *    NOTE: 12-bit conversion result.
 */
typedef enum
{
    CONVERSION_D_MASK   =   ( 0b111111111111 << 4U )  /*!<  D mask                                                    */
} ADS101X_conversion_t;



/**
  * @brief   CONFIG REGISTER. ( Default: 0x8583 )
  *           NOTE: The 16-bit Config register is used to control the operating mode, input selection, data rate, full-scale range, and
  *                 comparator modes.
  */
/* OS <15>
 *    NOTE: Operational status or single-shot conversion start.
 */
typedef enum
{
    CONFIG_OS_MASK      =   ( 1U << 15U ),            /*!<  OS mask                                                     */
    CONFIG_OS_BUSY      =   ( 1U << 15U ),            /*!<  Device is currently performing a conversion                 */
    CONFIG_OS_NOT_BUSY  =   ( 0U << 15U )             /*!<  Device is not currently performing a conversion [ Default ] */
} ADS101X_config_os_t;


/* MUX <14:12>
 *    NOTE: Input multiplexer configuration ( ADS1015 only ).
 */
typedef enum
{ 
    CONFIG_MUX_MASK                     =   ( 0b111 << 12U ),   /*!<  MUX mask                                                     */
    CONFIG_MUX_AINP_AIN0_AND_AINN_AIN1  =   ( 0b000 << 12U ),   /*!<  AINP = AIN0 and AINN = AIN1                      [ Default ] */
    CONFIG_MUX_AINP_AIN0_AND_AINN_AIN3  =   ( 0b001 << 12U ),   /*!<  AINP = AIN0 and AINN = AIN3                                  */
    CONFIG_MUX_AINP_AIN1_AND_AINN_AIN3  =   ( 0b010 << 12U ),   /*!<  AINP = AIN1 and AINN = AIN3                                  */
    CONFIG_MUX_AINP_AIN2_AND_AINN_AIN3  =   ( 0b011 << 12U ),   /*!<  AINP = AIN2 and AINN = AIN3                                  */
    CONFIG_MUX_AINP_AIN0_AND_AINN_GND   =   ( 0b100 << 12U ),   /*!<  AINP = AIN0 and AINN = GND                                   */
    CONFIG_MUX_AINP_AIN1_AND_AINN_GND   =   ( 0b101 << 12U ),   /*!<  AINP = AIN1 and AINN = GND                                   */
    CONFIG_MUX_AINP_AIN2_AND_AINN_GND   =   ( 0b110 << 12U ),   /*!<  AINP = AIN2 and AINN = GND                                   */
    CONFIG_MUX_AINP_AIN3_AND_AINN_GND   =   ( 0b111 << 12U )    /*!<  AINP = AIN3 and AINN = GND                                   */
} ADS101X_config_mux_t;


/* PGA <11:9>
 *    NOTE: Programmable gain amplifier configuration ( These bits serve NO function on the ADS1013 ).
 */
typedef enum
{ 
    CONFIG_PGA_MASK                     =   ( 0b111 << 9U ),   /*!<  PGA mask                                                     */
    CONFIG_PGA_FSR_6_144_V              =   ( 0b000 << 9U ),   /*!<  FSR = ±6.144 V                                               */
    CONFIG_PGA_FSR_4_096_V              =   ( 0b001 << 9U ),   /*!<  FSR = ±4.096 V                                               */
    CONFIG_PGA_FSR_2_048_V              =   ( 0b010 << 9U ),   /*!<  FSR = ±2.048 V                                   [ Default ] */
    CONFIG_PGA_FSR_1_024_V              =   ( 0b011 << 9U ),   /*!<  FSR = ±1.024 V                                               */
    CONFIG_PGA_FSR_0_512_V              =   ( 0b100 << 9U ),   /*!<  FSR = ±0.512 V                                               */
    CONFIG_PGA_FSR_0_256_V              =   ( 0b101 << 9U )    /*!<  FSR = ±0.256 V                                               */
} ADS101X_config_pga_t;


/* MODE <8>
 *    NOTE: Device operating mode.
 */
typedef enum
{ 
    CONFIG_MODE_MASK                    =   ( 1U << 8U ),       /*!<  MODE mask                                                    */
    CONFIG_MODE_CONTINUOUS_CONVERSION   =   ( 0U << 8U ),       /*!<  Continuous-conversion mode                                   */
    CONFIG_MODE_SINGLE_SHOT             =   ( 1U << 8U )        /*!<  Single-shot mode or power-down state             [ Default ] */
} ADS101X_config_mode_t;


/* DR <7:5>
 *    NOTE: Data rate.
 */
typedef enum
{ 
    CONFIG_DR_MASK                      =   ( 0b111 << 5U ),    /*!<  DR mask                                                       */
    CONFIG_DR_128_SPS                   =   ( 0b000 << 5U ),    /*!<  128 SPS                                                       */
    CONFIG_DR_250_SPS                   =   ( 0b001 << 5U ),    /*!<  250 SPS                                                       */
    CONFIG_DR_490_SPS                   =   ( 0b010 << 5U ),    /*!<  490 SPS                                                       */
    CONFIG_DR_920_SPS                   =   ( 0b011 << 5U ),    /*!<  920 SPS                                                       */
    CONFIG_DR_1600_SPS                  =   ( 0b100 << 5U ),    /*!<  1600 SPS                                          [ Default ] */
    CONFIG_DR_2400_SPS                  =   ( 0b101 << 5U ),    /*!<  2400 SPS                                                      */
    CONFIG_DR_3300_SPS                  =   ( 0b110 << 5U )     /*!<  3300 SPS                                                      */
} ADS101X_config_dr_t;


/* COMP_MODE <4>
 *    NOTE: Comparator mode ( ADS1014 and ADS1015 only )
 */
typedef enum
{ 
    CONFIG_COMP_MODE_MASK                   =   ( 1U << 4U ),   /*!<  COMP_MODE mask                                                */
    CONFIG_COMP_MODE_TRADITIONAL_COMPARATOR =   ( 0U << 4U ),   /*!<  Traditional comparator                            [ Default ] */
    CONFIG_COMP_MODE_WINDOW_COMPARATOR      =   ( 1U << 4U )    /*!<  Window comparator                                             */
} ADS101X_config_comp_mode_t;


/* COMP_POL <3>
 *    NOTE: Comparator polarity ( ADS1014 and ADS1015 only )
 */
typedef enum
{ 
    CONFIG_COMP_POL_MASK                    =   ( 1U << 3U ),   /*!<  COMP_POL mask                                                 */
    CONFIG_COMP_POL_ACTIVE_LOW              =   ( 0U << 3U ),   /*!<  Active low                                        [ Default ] */
    CONFIG_COMP_POL_ACTIVE_HIGH             =   ( 1U << 3U )    /*!<  Active high                                                   */
} ADS101X_config_comp_pol_t;


/* COMP_LAT <2>
 *    NOTE: Latching comparator ( ADS1014 and ADS1015 only )
 */
typedef enum
{ 
    CONFIG_COMP_LAT_MASK                    =   ( 1U << 2U ),   /*!<  COMP_LAT mask                                                 */
    CONFIG_COMP_LAT_NONLATCHING_COMPARATOR  =   ( 0U << 2U ),   /*!<  Nonlatching comparator                            [ Default ] */
    CONFIG_COMP_LAT_LATCHING_COMPARATOR     =   ( 1U << 2U )    /*!<  Latching comparator                                           */
} ADS101X_config_comp_lat_t;


/* COMP_QUE <1:0>
 *    NOTE: Latching comparator ( ADS1014 and ADS1015 only )
 */
typedef enum
{ 
    CONFIG_COMP_QUE_MASK                          =   ( 0b11 << 0U ), /*!<  COMP_QUE mask                                                           */
    CONFIG_COMP_QUE_ASSERT_AFTER_ONE_CONVERSION   =   ( 0b00 << 0U ), /*!<  Assert after one conversion                                             */
    CONFIG_COMP_QUE_ASSERT_AFTER_TWO_CONVERSION   =   ( 0b01 << 0U ), /*!<  Assert after two conversions                                            */
    CONFIG_COMP_QUE_ASSERT_AFTER_FOUR_CONVERSION  =   ( 0b10 << 0U ), /*!<  Assert after four conversions                                           */
    CONFIG_COMP_QUE_DISABLED                      =   ( 0b11 << 0U )  /*!<  Disable comparator and set ALERT/RDY pin to high-impedance  [ Default ] */
} ADS101X_config_comp_que_t;



/**
  * @brief   LO_THRESH REGISTER. ( Default: 0x8000 )
  */
/* LO_THRESH <15:4>
 *    NOTE: N/A.
 */
typedef enum
{
    LO_THRESH_MASK      =   ( 0b111111111111 << 4U )            /*!<  LO_THRESH mask                                                */
} ADS101X_lo_thresh_t;



/**
  * @brief   HI_THRESH REGISTER. ( Default: 0x7FFF )
  */
/* HI_THRESH <15:4>
 *    NOTE: N/A.
 */
typedef enum
{
    HI_THRESH_MASK      =   ( 0b111111111111 << 4U )            /*!<  HI_THRESH mask                                                */
} ADS101X_hi_thresh_t;







#ifndef ADS101X_VECTOR_STRUCT_H
#define ADS101X_VECTOR_STRUCT_H
typedef struct
{
  /* Output registers  */
  int32_t   rawPressure;                      /*!<  Raw pressure                      */
  int16_t   rawTemperature;                   /*!<  Raw temperature                   */

  /* Configuration  */
  ADS101X_config_os_t os;                     /*!<  Operational status                */
  

  /* Device identification   */
  ADS101X_device_t  device;                   /*!<  Device                            */
} ADS101X_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    ADS101X_SUCCESS     =       0,
    ADS101X_FAILURE     =       1
} ADS101X_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
ADS101X_status_t ADS101X_Init                   ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myADS101X  );

/** It starts a new single conversion.
  */
ADS101X_status_t ADS101X_StartSingleConversion  ( I2C_parameters_t myI2Cparameters                            );

/** It checks if the device is not currently performing a conversion.
  */
ADS101X_status_t ADS101X_GetOS                  ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myADS101X );


