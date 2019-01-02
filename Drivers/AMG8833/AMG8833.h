/**
 * @brief       AMG8833.h
 * @details     Infrared Array Sensor "Grid-EYE".
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/December/2018
 * @version     19/December/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef AMG8833_H_
#define AMG8833_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    AMG8833_ADDRESS_AD_SELECT_VDD   =   0b1101001,    /*!<   AMG8833 I2C Address: AD_SELECT to VDD                */
    AMG8833_ADDRESS_AD_SELECT_GND   =   0b1101000     /*!<   AMG8833 I2C Address: AD_SELECT to GND                */
} AMG8833_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
    AMG8833_PCTL  =   0x00,                           /*!<  Power Control Register              ( Read/Write )      */
    AMG8833_RST   =   0x01,                           /*!<  Reset Register                      ( Write Only )      */
    AMG8833_FPSC  =   0x02,                           /*!<  Frame Rate Register                 ( Read/Write )      */
    AMG8833_INTC  =   0x03,                           /*!<  Interrupt Control Register          ( Read/Write )      */
    AMG8833_STAT  =   0x04,                           /*!<  Status Register                     ( Read Only  )      */
    AMG8833_SCLR  =   0x05,                           /*!<  Status Clear Register               ( Write Only )      */
    AMG8833_AVE   =   0x07,                           /*!<  Average Register                    ( Read/Write )      */
    AMG8833_INTHL =   0x08,                           /*!<  Interrupt Level upper limit [7:0]   ( Read/Write )      */
    AMG8833_INTHH =   0x09,                           /*!<  Interrupt Level upper limit [11:8]  ( Read/Write )      */
    AMG8833_INTLL =   0x0A,                           /*!<  Interrupt Level lower limit [7:0]   ( Read/Write )      */
    AMG8833_INTLH =   0x0B,                           /*!<  Interrupt Level lower limit [11:8]  ( Read/Write )      */
    AMG8833_IHYSL =   0x0C,                           /*!<  Interrupt Hysteresis Level  [7:0]   ( Read/Write )      */
    AMG8833_IHYSH =   0x0D,                           /*!<  Interrupt Hysteresis Level  [11:8]  ( Read/Write )      */
    AMG8833_TTHL  =   0x0E,                           /*!<  Thermistor Register lower  [7:0]    ( Read Only  )      */
    AMG8833_TTHH  =   0x0F,                           /*!<  Thermistor Register upper  [11:8]   ( Read Only  )      */
    AMG8833_INT0  =   0x10,                           /*!<  Interrupt Table Register 0          ( Read Only  )      */
    AMG8833_INT1  =   0x11,                           /*!<  Interrupt Table Register 1          ( Read Only  )      */
    AMG8833_INT2  =   0x12,                           /*!<  Interrupt Table Register 2          ( Read Only  )      */
    AMG8833_INT3  =   0x13,                           /*!<  Interrupt Table Register 3          ( Read Only  )      */
    AMG8833_INT4  =   0x14,                           /*!<  Interrupt Table Register 4          ( Read Only  )      */
    AMG8833_INT5  =   0x15,                           /*!<  Interrupt Table Register 5          ( Read Only  )      */
    AMG8833_INT6  =   0x16,                           /*!<  Interrupt Table Register 6          ( Read Only  )      */
    AMG8833_INT7  =   0x17,                           /*!<  Interrupt Table Register 7          ( Read Only  )      */
    AMG8833_T01L  =   0x80,                           /*!<  Pixel 1 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T01H  =   0x81,                           /*!<  Pixel 1 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T02L  =   0x82,                           /*!<  Pixel 2 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T02H  =   0x83,                           /*!<  Pixel 2 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T03L  =   0x84,                           /*!<  Pixel 3 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T03H  =   0x85,                           /*!<  Pixel 3 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T04L  =   0x86,                           /*!<  Pixel 4 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T04H  =   0x87,                           /*!<  Pixel 4 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T05L  =   0x88,                           /*!<  Pixel 5 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T05H  =   0x89,                           /*!<  Pixel 5 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T06L  =   0x8A,                           /*!<  Pixel 6 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T06H  =   0x8B,                           /*!<  Pixel 6 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T07L  =   0x8C,                           /*!<  Pixel 7 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T07H  =   0x8D,                           /*!<  Pixel 7 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T08L  =   0x8E,                           /*!<  Pixel 8 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T08H  =   0x8F,                           /*!<  Pixel 8 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T09L  =   0x90,                           /*!<  Pixel 9 Output Value (Lower Level)  ( Read Only  )      */
    AMG8833_T09H  =   0x91,                           /*!<  Pixel 9 Output Value (Upper Level)  ( Read Only  )      */
    AMG8833_T10L  =   0x92,                           /*!<  Pixel 10 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T10H  =   0x93,                           /*!<  Pixel 10 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T11L  =   0x94,                           /*!<  Pixel 11 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T11H  =   0x95,                           /*!<  Pixel 11 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T12L  =   0x96,                           /*!<  Pixel 12 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T12H  =   0x97,                           /*!<  Pixel 12 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T13L  =   0x98,                           /*!<  Pixel 13 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T13H  =   0x99,                           /*!<  Pixel 13 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T14L  =   0x9A,                           /*!<  Pixel 14 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T14H  =   0x9B,                           /*!<  Pixel 14 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T15L  =   0x9C,                           /*!<  Pixel 15 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T15H  =   0x9D,                           /*!<  Pixel 15 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T16L  =   0x9E,                           /*!<  Pixel 16 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T16H  =   0x9F,                           /*!<  Pixel 16 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T17L  =   0xA0,                           /*!<  Pixel 17 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T17H  =   0xA1,                           /*!<  Pixel 17 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T18L  =   0xA2,                           /*!<  Pixel 18 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T18H  =   0xA3,                           /*!<  Pixel 18 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T19L  =   0xA4,                           /*!<  Pixel 19 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T19H  =   0xA5,                           /*!<  Pixel 19 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T20L  =   0xA6,                           /*!<  Pixel 20 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T20H  =   0xA7,                           /*!<  Pixel 20 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T21L  =   0xA8,                           /*!<  Pixel 21 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T21H  =   0xA9,                           /*!<  Pixel 21 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T22L  =   0xAA,                           /*!<  Pixel 22 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T22H  =   0xAB,                           /*!<  Pixel 22 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T23L  =   0xAC,                           /*!<  Pixel 23 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T23H  =   0xAD,                           /*!<  Pixel 23 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T24L  =   0xAE,                           /*!<  Pixel 24 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T24H  =   0xAF,                           /*!<  Pixel 24 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T25L  =   0xB0,                           /*!<  Pixel 25 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T25H  =   0xB1,                           /*!<  Pixel 25 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T26L  =   0xB2,                           /*!<  Pixel 26 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T26H  =   0xB3,                           /*!<  Pixel 26 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T27L  =   0xB4,                           /*!<  Pixel 27 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T27H  =   0xB5,                           /*!<  Pixel 27 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T28L  =   0xB6,                           /*!<  Pixel 28 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T28H  =   0xB7,                           /*!<  Pixel 28 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T29L  =   0xB8,                           /*!<  Pixel 29 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T29H  =   0xB9,                           /*!<  Pixel 29 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T30L  =   0xBA,                           /*!<  Pixel 30 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T30H  =   0xBB,                           /*!<  Pixel 30 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T31L  =   0xBC,                           /*!<  Pixel 31 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T31H  =   0xBD,                           /*!<  Pixel 31 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T32L  =   0xBE,                           /*!<  Pixel 32 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T32H  =   0xBF,                           /*!<  Pixel 32 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T33L  =   0xC0,                           /*!<  Pixel 33 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T33H  =   0xC1,                           /*!<  Pixel 33 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T34L  =   0xC2,                           /*!<  Pixel 34 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T34H  =   0xC3,                           /*!<  Pixel 34 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T35L  =   0xC4,                           /*!<  Pixel 35 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T35H  =   0xC5,                           /*!<  Pixel 35 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T36L  =   0xC6,                           /*!<  Pixel 36 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T36H  =   0xC7,                           /*!<  Pixel 36 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T37L  =   0xC8,                           /*!<  Pixel 37 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T37H  =   0xC9,                           /*!<  Pixel 37 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T38L  =   0xCA,                           /*!<  Pixel 38 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T38H  =   0xCB,                           /*!<  Pixel 38 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T39L  =   0xCC,                           /*!<  Pixel 39 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T39H  =   0xCD,                           /*!<  Pixel 39 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T40L  =   0xCE,                           /*!<  Pixel 40 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T40H  =   0xCF,                           /*!<  Pixel 40 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T41L  =   0xD0,                           /*!<  Pixel 41 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T41H  =   0xD1,                           /*!<  Pixel 41 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T42L  =   0xD2,                           /*!<  Pixel 42 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T42H  =   0xD3,                           /*!<  Pixel 42 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T43L  =   0xD4,                           /*!<  Pixel 43 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T43H  =   0xD5,                           /*!<  Pixel 43 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T44L  =   0xD6,                           /*!<  Pixel 44 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T44H  =   0xD7,                           /*!<  Pixel 44 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T45L  =   0xD8,                           /*!<  Pixel 45 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T45H  =   0xD9,                           /*!<  Pixel 45 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T46L  =   0xDA,                           /*!<  Pixel 46 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T46H  =   0xDB,                           /*!<  Pixel 46 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T47L  =   0xDC,                           /*!<  Pixel 47 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T47H  =   0xDD,                           /*!<  Pixel 47 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T48L  =   0xDE,                           /*!<  Pixel 48 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T48H  =   0xDF,                           /*!<  Pixel 48 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T49L  =   0xE0,                           /*!<  Pixel 49 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T49H  =   0xE1,                           /*!<  Pixel 49 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T50L  =   0xE2,                           /*!<  Pixel 50 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T50H  =   0xE3,                           /*!<  Pixel 50 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T51L  =   0xE4,                           /*!<  Pixel 51 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T51H  =   0xE5,                           /*!<  Pixel 51 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T52L  =   0xE6,                           /*!<  Pixel 52 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T52H  =   0xE7,                           /*!<  Pixel 52 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T53L  =   0xE8,                           /*!<  Pixel 53 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T53H  =   0xE9,                           /*!<  Pixel 53 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T54L  =   0xEA,                           /*!<  Pixel 54 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T54H  =   0xEB,                           /*!<  Pixel 54 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T55L  =   0xEC,                           /*!<  Pixel 55 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T55H  =   0xED,                           /*!<  Pixel 55 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T56L  =   0xEE,                           /*!<  Pixel 56 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T56H  =   0xEF,                           /*!<  Pixel 56 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T57L  =   0xF0,                           /*!<  Pixel 57 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T57H  =   0xF1,                           /*!<  Pixel 57 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T58L  =   0xF2,                           /*!<  Pixel 58 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T58H  =   0xF3,                           /*!<  Pixel 58 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T59L  =   0xF4,                           /*!<  Pixel 59 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T59H  =   0xF5,                           /*!<  Pixel 59 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T60L  =   0xF6,                           /*!<  Pixel 60 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T60H  =   0xF7,                           /*!<  Pixel 60 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T61L  =   0xF8,                           /*!<  Pixel 61 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T61H  =   0xF9,                           /*!<  Pixel 61 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T62L  =   0xFA,                           /*!<  Pixel 62 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T62H  =   0xFB,                           /*!<  Pixel 62 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T63L  =   0xFC,                           /*!<  Pixel 63 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T63H  =   0xFD,                           /*!<  Pixel 63 Output Value (Upper Level)  ( Read Only  )     */
    AMG8833_T64L  =   0xFE,                           /*!<  Pixel 64 Output Value (Lower Level)  ( Read Only  )     */
    AMG8833_T64H  =   0xFF                            /*!<  Pixel 64 Output Value (Upper Level)  ( Read Only  )     */
} AMG8833_register_map_t;



/**
  * @brief   POWER CONTROL REGISTER
  */
/* PCTL: OPERATING MODE
 *    NOTE: Writing operation in Sleep mode is only active in return to Normal mode. Reading operation in Sleep mode is invalid.
*/
typedef enum
{
    PCTL_MASK                 =   0xFF,         /*!<  PCTL bit mask                                                 */
    PCTL_NORMAL_MODE          =   0x00,         /*!<  PCTL: Normal mode                                   ( RESET ) */
    PCTL_SLEEP_MODE           =   0x10,         /*!<  PCTL: Sleep mode                                              */
    PCTL_STANDBY_60SEC_MODE   =   0x20,         /*!<  PCTL: Stand-by mode ( 60sec intermittence )                   */
    PCTL_STANDBY_10SEC_MODE   =   0x21          /*!<  PCTL: Stand-by mode ( 10sec intermittence )                   */
} AMG8833_pctl_t;


/**
  * @brief   RESET REGISTER
  */
typedef enum
{
    RST_MASK                  =   0xFF,         /*!<  RST mask                                                      */
    RST_FLAG_RESET            =   0x30,         /*!<  Flag reset                                                    */
    RST_INITIAL_RESET         =   0x3F,         /*!<  Initial reset reset                                           */
    RST_RESUME_FROM_RESET     =   0x00          /*!<  Resume from reset                                             */
} AMG8833_rst_t;



/**
  * @brief   FRAME RATE REGISTER ( SETTING FRAME MODE )
  */
typedef enum
{
    FPSC_MASK                 =   ( 1U << 0U ), /*!<  FPSC mask                                                     */
    FPSC_1FPS                 =   ( 1U << 0U ), /*!<  FPSC: 1 FPSC                                                  */
    FPSC_10FPS                =   ( 0U << 0U )  /*!<  FPSC: 10 FPSC                                       ( RESET ) */
} AMG8833_fpsc_t;



/**
  * @brief   INTERRUPT CONTROL REGISTER
  */
/**
  * INTMOD ( INTERRUPT MODE ) <1>
  */
typedef enum
{
    INTMOD_MASK                       =   ( 1U << 1U ), /*!<  INTMOD mask                                           */
    INTMOD_ABSOLUTE_INTERRUPT_MODE    =   ( 1U << 1U ), /*!<  Absolute interrupt mode                               */
    INTMOD_DIFFERENCE_INTERRUPT_MODE  =   ( 0U << 1U )  /*!<  Difference Interrupt Mode                   ( RESET ) */
} AMG8833_intmod_t;



/**
  * INTEN ( INTERRUPT MODE ) <0>
  */
typedef enum
{
    INTEN_MASK                        =   ( 1U << 0U ), /*!<  INTEN mask                                            */
    INTEN_INT_OUTPUT_ACTIVE           =   ( 1U << 0U ), /*!<  INT Output active                                     */
    INTEN_INT_OUTPUT_REACTIVE         =   ( 0U << 0U )  /*!<  INT Output reactive ( Hi-Z )                ( RESET ) */
} AMG8833_inten_t;



/**
  * @brief   STATUS REGISTER
  */
/**
  * OVF_THS ( THERMISTOR TEMPERATURE OUTPUT OVERFLOW ) <3>
  */
typedef enum
{
    OVF_THS_MASK                                =   ( 1U << 3U ), /*!<  OVF_THS mask                                          */
    OVF_THS_THERMISTOR_TEMPERATURE_OVERFLOW     =   ( 1U << 3U ), /*!<  Thermistor Temperature Output Overflow                */
    OVF_THS_THERMISTOR_TEMPERATURE_NO_OVERFLOW  =   ( 0U << 3U )  /*!<  Thermistor Temperature Output NO Overflow             */
} AMG8833_ovf_ths_t;


/**
  * OVF_IRS ( TEMPERATURE OUTPUT OVERFLOW ) <2>
  */
typedef enum
{
    OVF_IRS_MASK                      =   ( 1U << 2U ),   /*!<  OVF_IRS mask                                          */
    OVF_IRS_TEMPERATURE_OVERFLOW      =   ( 1U << 2U ),   /*!<  Temperature Output Overflow                           */
    OVF_IRS_TEMPERATURE_NO_OVERFLOW   =   ( 0U << 2U )    /*!<  Temperature Output NO Overflow                        */
} AMG8833_ovf_irs_t;


/**
  * INTF ( INTERRUPT OUTBREAK ) <1>
  */
typedef enum
{
    INTF_MASK                         =   ( 1U << 1U ),   /*!<  INTF mask                                             */
    INTF_INTERRUPT_OUTBREAK           =   ( 1U << 1U ),   /*!<  Interrupt Outbreak                                    */
    INTF_INTERRUPT_NO_OUTBREAK        =   ( 0U << 1U )    /*!<  Interrupt NO Outbreak                                 */
} AMG8833_intf_t;



/**
  * @brief   STATUS CLEAR REGISTER
  */
/**
  * OVT_CLR ( THERMISTOR TEMPERATURE OUTPUT OVERFLOW FLAG CLEAR  ) <3>
  */
typedef enum
{
    OVT_CLR_THERMISTOR_TEMPERATURE_OVERFLOW_CLEAR_FLAG  =   ( 1U << 3U )  /*!<  Thermistor Temperature Output Overflow Clear Flag     */
} AMG8833_ovf_clr_t;


/**
  * OVS_CLR ( TEMPERATURE OUTPUT OVERFLOW FLAG CLEAR ) <2>
  */
typedef enum
{
    OVS_CLR_TEMPERATURE_OVERFLOW_CLEAR_FLAG =   ( 1U << 2U )    /*!<  Temperature Output Overflow Flag Clear                */
} AMG8833_ovs_clr_t;


/**
  * INTCLR ( INTERRUPT OUTBREAK FLAG CLEAR ) <1>
  */
typedef enum
{
    INTCLR_INTERRUPT_OUTBREAK_CLEAR_FLAG   =   ( 1U << 1U )    /*!<  Interrupt Outbreak Clear Flag                           */
} AMG8833_intclr_t;



/**
  * @brief   AVERAGE REGISTER
  */
/**
  * MAMOD ( TWICE MOVING AVERAGE OUTPUT MODE ) <5> 
  */
typedef enum
{
    MAMOD_MASK                                  =   ( 1U << 5U ), /*!<  MAMOD mask                                            */
    MAMOD_WICE_MOVING_AVERAGE_OUTPUT_MODE_ON    =   ( 1U << 5U ), /*!<  Twice moving average Output Mode ON                   */
    MAMOD_WICE_MOVING_AVERAGE_OUTPUT_MODE_OFF   =   ( 0U << 5U )  /*!<  Twice moving average Output Mode OFF        ( RESET ) */
} AMG8833_mamod_t;



/**
  * @brief   INTERRUPT LEVEL REGISTER
  */
/**
  * SETTING UPPER/LOWER LIMIT HYSTERESIS ON INTERRUPT LEVEL 
  */
typedef enum
{
    LIMIT_HYSTERESIS_INTHH_MASK    =   0b00001111,                /*!<  INTHH mask                                            */
    LIMIT_HYSTERESIS_INTLH_MASK    =   0b00001111,                /*!<  INTLH mask                                            */
    LIMIT_HYSTERESIS_IHYSH_MASK    =   0b00001111                 /*!<  IHYSH mask                                            */
} AMG8833_limit_hysteresis_interrupt_level_t;



/**
  * @brief   THERMISTOR REGISTER
  */
typedef enum
{
    TTHH_MASK    =   0b00001111                 /*!<  TTHH mask                                            */
} AMG8833_thermistor_register_t;



/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    TXXH_MASK    =   0b00001111                 /*!<  TXXH mask                                            */
} AMG8833_temperature_register_t;





#ifndef AMG8833_VECTOR_STRUCT_H
#define AMG8833_VECTOR_STRUCT_H

#define THERMISTOR_RESOLUTION   0.0625      /*!<  Thermistor Temperature Data 1 LSB has 12 bit resolution at 0.0625C  */
#define TEMPERATURE_RESOLUTION  0.25        /*!<  Pixel Temperature Data 1 LSB has 12 bit resolution at 0.25C         */

typedef struct
{
    float    termistorOutputValue;          /*!<  Termistor output value in Celsius degrees */
    float    pixelOutputValues[64U];        /*!<  Pixel output values in Celsius degrees    */
    
    uint16_t termistorOutputRawValue;       /*!<  Termistor output raw value                */
    uint16_t pixelOutputRawValues[64U];     /*!<  Pixel output raw values                   */

    AMG8833_pctl_t operationMode;           /*!<  AMG8833 operation mode                    */
    uint8_t pixelInterruptTable[64U];       /*!<  Pixel interrupt table                     */
} AMG8833_data_t;
#endif

 



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AMG8833_SUCCESS     =       0,
    AMG8833_FAILURE     =       1
} AMG8833_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
AMG8833_status_t  AMG8833_Init                      ( I2C_parameters_t myI2Cparameters                                                                      );

/** It reads the operation mode ( power control register ).
  */
AMG8833_status_t  AMG8833_GetOperationMode          ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myOperationMode                                     );

/** It sets the operation mode ( power control register ).
  */
AMG8833_status_t  AMG8833_SetOperationMode          ( I2C_parameters_t myI2Cparameters, AMG8833_data_t myOperationMode                                      );

/** It sets the reset mode.
  */
AMG8833_status_t  AMG8833_SoftwareReset             ( I2C_parameters_t myI2Cparameters, AMG8833_rst_t mySoftwareReset                                       );

/** It sets frame mode.
  */
AMG8833_status_t  AMG8833_SetFrameMode              ( I2C_parameters_t myI2Cparameters, AMG8833_fpsc_t myFrameMode                                          );

/** It sets interrupt function mode.
  */
AMG8833_status_t  AMG8833_SetInterruptFunctionMode  ( I2C_parameters_t myI2Cparameters, AMG8833_intmod_t myInterruptMode, AMG8833_inten_t myInterruptOutput );

/** It gets the status register value.
  */
AMG8833_status_t  AMG8833_GetStatusRegisterValue    ( I2C_parameters_t myI2Cparameters, uint8_t* myStatusRegisterValue                                      );

/** It clears overflow and/or interrupt flags.
  */
AMG8833_status_t  AMG8833_ClearFlags                ( I2C_parameters_t myI2Cparameters, uint8_t myFlagsToBeCleared                                          );

/** It sets twice moving average output mode.
  */
AMG8833_status_t  AMG8833_SetAverageOutputMode      ( I2C_parameters_t myI2Cparameters, AMG8833_mamod_t myAverageOutputMode                                 );

/** It sets interrupt level upper/lower limit.
  */
AMG8833_status_t  AMG8833_SetInterruptLevel         ( I2C_parameters_t myI2Cparameters, int16_t myUpperLimit, int16_t myLowerLimit                          );

/** It sets interrupt hysteresis level when interrupt is generated.
  */
AMG8833_status_t  AMG8833_SetHysteresisLevel        ( I2C_parameters_t myI2Cparameters, int16_t myHysteresisLimit                                           );

/** It gets thermistor raw temperature data.
  */
AMG8833_status_t  AMG8833_GetThermistorRawData      ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myThermistorRawData                                 );

/** It gets thermistor temperature data.
  */
AMG8833_status_t  AMG8833_GetThermistorValue        ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myThermistorValue                                   );

/** It gets pixel interrupt table.
  */
AMG8833_status_t  AMG8833_GetPixelInterruptTable    ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myPixelInterruptTable                               );

/** It gets pixel raw temperature data.
  */
AMG8833_status_t  AMG8833_GetPixelRawTemperatures   ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myPixelRawTemperatureData                           );

/** It gets pixel temperature value in Celsius degrees.
  */
AMG8833_status_t  AMG8833_GetPixelTemperatures      ( I2C_parameters_t myI2Cparameters, AMG8833_data_t* myPixelTemperatureData                              );




#ifdef __cplusplus
}
#endif

#endif /* AMG8833_H */
