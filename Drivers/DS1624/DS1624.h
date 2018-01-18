/**
 * @brief       DS1624.h
 * @details     Digital Thermometer and Memory.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/January/2018
 * @version     18/January/2018    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES.
  */
typedef enum
{
    DS1624_ADDRESS     =   0x68                   /*!<   Address                                            */
} DS1624_address_t;


// REGISTERS
/**
  * @brief   TIMEKEEPING REGISTERS
  */
typedef enum
{
    DS1624_SECONDS          =   0x00,               /*!<  Seconds. RANGE 00-59                                  */
    DS1624_MINUTES          =   0x01,               /*!<  Minutes. RANGE 00-59                                  */
    DS1624_HOURS            =   0x02,               /*!<  Hours. 1-12 + AM/PM 00-23                             */
    DS1624_DAY              =   0x03,               /*!<  Day. 1-7                                              */
    DS1624_DATE             =   0x04,               /*!<  Date. 01-31                                           */
    DS1624_MONTH_CENTURY    =   0x05,               /*!<  Month/Century. 01-12 + Century                        */
    DS1624_YEAR             =   0x06,               /*!<  Year. 00-99                                           */
    DS1624_ALARM_1_SECONDS  =   0x07,               /*!<  Alarm 1 seconds. 00-59                                */
    DS1624_ALARM_1_MINUTES  =   0x08,               /*!<  Alarm 1 minutes. 00-59                                */
    DS1624_ALARM_1_HOURS    =   0x09,               /*!<  Alarm 1 hours. 1-12 + AM/PM 00-23                     */
    DS1624_ALARM_1_DAY_DATE =   0x0A,               /*!<  Alarm 1 day/date. 1-7/1-31                            */
    DS1624_ALARM_2_MINUTES  =   0x0B,               /*!<  Alarm 2 minutes. 00-59                                */
    DS1624_ALARM_2_HOURS    =   0x0C,               /*!<  Alarm 2 hours. 1-12 + AM/PM 00-23                     */
    DS1624_ALARM_2_DAY_DATE =   0x0D,               /*!<  Alarm 2 day/date. 1-7/1-31                            */
    DS1624_CONTROL          =   0x0E,               /*!<  Control                                               */
    DS1624_CONTROL_STATUS   =   0x0F,               /*!<  Control/Status                                        */
    DS1624_AGING_OFFSET     =   0x10,               /*!<  Aging offset                                          */
    DS1624_MSB_TEMPERATURE  =   0x11,               /*!<  MSB of Temp                                           */
    DS1624_LSB_TEMPERATURE  =   0x12                /*!<  LSB of Temp                                           */
} DS1624_registers_t;



// CONTROL REGISTER
/**
  * @brief   Enable Oscillator ( #EOSC )
  */
typedef enum
{
    CONTROL_STATUS_ENABLE_OSCILLATOR_MASK       =   ( 1 << 7 ),     /*!<  #EOSC Mask                            */
    CONTROL_STATUS_ENABLE_OSCILLATOR_ENABLED    =   ( 1 << 7 ),     /*!<  Enable oscillator                     */
    CONTROL_STATUS_ENABLE_OSCILLATOR_DISABLED   =   ( 0 << 7 )      /*!<  Disable oscillator                    */
} DS1624_control_status_enable_oscillator_t;


/**
  * @brief   Battery-Backed Square-Wave Enable ( BBSQW )
  */
typedef enum
{
    CONTROL_STATUS_BBSQW_MASK       =   ( 1 << 6 ),                 /*!<  BBSQW Mask                            */
    CONTROL_STATUS_BBSQW_ENABLED    =   ( 1 << 6 ),                 /*!<  Enable BBSQW                          */
    CONTROL_STATUS_BBSQW_DISABLED   =   ( 0 << 6 )                  /*!<  Disable BBSQW                         */
} DS1624_control_status_bbsqw_t;


/**
  * @brief   Convert Temperature ( CONV )
  */
typedef enum
{
    CONTROL_STATUS_CONVERT_TEMPERATURE_MASK       =   ( 1 << 5 ),   /*!<  CONVERT TEMPERATURE Mask              */
    CONTROL_STATUS_CONVERT_TEMPERATURE_ENABLED    =   ( 1 << 5 ),   /*!<  Enable CONVERT_TEMPERATURE            */
    CONTROL_STATUS_CONVERT_TEMPERATURE_DISABLED   =   ( 0 << 5 )    /*!<  Disable CONVERT_TEMPERATURE           */
} DS1624_control_status_convert_temperature_t;


/**
  * @brief   Rate Select ( RS2 and RS1 )
  */
typedef enum
{
    CONTROL_STATUS_RATE_SELECT_MASK         =   ( 3 << 3 ),         /*!<  Rate select Mask                      */
    CONTROL_STATUS_RATE_SELECT_1_HZ         =   ( 0 << 3 ),         /*!<  Rate select 1 Hz                      */
    CONTROL_STATUS_RATE_SELECT_1_024_KHZ    =   ( 1 << 3 ),         /*!<  Rate select 1.024 kHz                 */
    CONTROL_STATUS_RATE_SELECT_4_096_KHZ    =   ( 2 << 3 ),         /*!<  Rate select 4.096 kHz                 */
    CONTROL_STATUS_RATE_SELECT_8_192_KHZ    =   ( 3 << 3 )          /*!<  Rate select 8.192 kHz                 */
} DS1624_control_status_rate_select_t;


/**
  * @brief   Interrupt Control ( INTCN )
  */
typedef enum
{
    CONTROL_STATUS_INTERRUPT_CONTROL_MASK       =   ( 1 << 2 ),     /*!<  Interrupt control Mask              */
    CONTROL_STATUS_INTERRUPT_CONTROL_SQW        =   ( 0 << 2 ),     /*!<  Square wave is output               */
    CONTROL_STATUS_INTERRUPT_CONTROL_INT        =   ( 1 << 2 )      /*!<  Alarm activates the output          */
} DS1624_control_status_interrupt_control_t;


/**
  * @brief   Alarm 2 Interrupt Enable ( A2IE )
  */
typedef enum
{
    CONTROL_STATUS_ALARM2_MASK       =   ( 1 << 1 ),                /*!<  Alarm 2 Mask                        */
    CONTROL_STATUS_ALARM2_ENABLED    =   ( 1 << 1 ),                /*!<  Alarm 2 enabled                     */
    CONTROL_STATUS_ALARM2_DISABLED   =   ( 0 << 1 )                 /*!<  Alarm 2 disabled                    */
} DS1624_control_status_alarm2_t;


/**
  * @brief   Alarm 1 Interrupt Enable ( A1IE )
  */
typedef enum
{
    CONTROL_STATUS_ALARM1_MASK       =   ( 1 << 0 ),                /*!<  Alarm 1 Mask                        */
    CONTROL_STATUS_ALARM1_ENABLED    =   ( 1 << 0 ),                /*!<  Alarm 1 enabled                     */
    CONTROL_STATUS_ALARM1_DISABLED   =   ( 0 << 0 )                 /*!<  Alarm 1 disabled                    */
} DS1624_control_status_alarm1_t;



// STATUS REGISTER
/**
  * @brief   Oscillator Stop Flag ( OSF )
  */
typedef enum
{
    STATUS_OSCILLATOR_STOP_FLAG_MASK       =   ( 1 << 7 ),          /*!<  OSF Mask                              */
    STATUS_OSCILLATOR_STOP_FLAG_ENABLED    =   ( 1 << 7 ),          /*!<  Flag ON                               */
    STATUS_OSCILLATOR_STOP_FLAG_DISABLED   =   ( 0 << 7 ),          /*!<  Flag OFF                              */
    STATUS_OSCILLATOR_STOP_FLAG_RESET      =   ( 0 << 7 )           /*!<  Reset flag                            */
} DS1624_status_oscillator_stop_flag_t;


/**
  * @brief   Enable 32kHz Output ( EN32kHz )
  */
typedef enum
{
    STATUS_ENABLE_32KHZ_OUTPUT_MASK       =   ( 1 << 3 ),          /*!<  32kHz output mask                     */
    STATUS_ENABLE_32KHZ_OUTPUT_ENABLED    =   ( 1 << 3 ),          /*!<  32kHz output on 32kHz pin             */
    STATUS_ENABLE_32KHZ_OUTPUT_DISABLED   =   ( 0 << 3 )           /*!<  32kHz output disabled                 */
} DS1624_status_enable_32khz_output_t;


/**
  * @brief   Busy ( BSY )
  */
typedef enum
{
    STATUS_BUSY_MASK        =   ( 1 << 2 ),                         /*!<  BSY mask                              */
    STATUS_BUSY_BUSY        =   ( 1 << 2 ),                         /*!<  device busy executing TCXO functions  */
    STATUS_BUSY_NOBUSY      =   ( 0 << 2 )                          /*!<  device IS NOT busy                    */
} DS1624_status_busy_t;


/**
  * @brief   Alarm 2 Flag ( A2F )
  */
typedef enum
{
    STATUS_ALARM2_FLAG_MASK        =   ( 1 << 1 ),                  /*!<  Alarm 2 flag mask                     */
    STATUS_ALARM2_FLAG_ENABLED     =   ( 1 << 1 ),                  /*!<  Alarm 2 flag enabled                  */
    STATUS_ALARM2_FLAG_DISABLED    =   ( 0 << 1 ),                  /*!<  Alarm 2 flag disabled                 */
    STATUS_ALARM2_FLAG_RESET       =   ( 0 << 1 ),                  /*!<  Alarm 2 flag reset flag               */
} DS1624_status_alarm2_flag_t;



/**
  * @brief   Alarm 1 Flag ( A1F )
  */
typedef enum
{
    STATUS_ALARM1_FLAG_MASK        =   ( 1 << 0 ),                  /*!<  Alarm 1 flag mask                     */
    STATUS_ALARM1_FLAG_ENABLED     =   ( 1 << 0 ),                  /*!<  Alarm 1 flag enabled                  */
    STATUS_ALARM1_FLAG_DISABLED    =   ( 0 << 0 ),                  /*!<  Alarm 1 flag disabled                 */
    STATUS_ALARM1_FLAG_RESET       =   ( 0 << 0 ),                  /*!<  Alarm 1 flag reset flag               */
} DS1624_status_alarm1_flag_t;



// ALARMS
/**
  * @brief   Alarm 1 Mask Bits
  */
typedef enum
{
    ALARM1_ALARM_ONCE_PER_SECOND                        =   1,      /*!<  Alarm 1 once per second                               */
    ALARM1_WHEN_SECONDS_MATCH                           =   2,      /*!<  Alarm 1 when seconds match                            */
    ALARM1_WHEN_MINUTES_AND_SECONDS_MATCH               =   3,      /*!<  Alarm 1 when minutes and seconds match                */
    ALARM1_WHEN_HOURS_MINUTES_AND_SECONDS_MATCH         =   4,      /*!<  Alarm 1 when hours, minutes, and seconds match        */
    ALARM1_WHEN_DATE_HOURS_MINUTES_AND_SECONDS_MATCH    =   5,      /*!<  Alarm 1 when date, hours, minutes, and seconds match  */
    ALARM1_WHEN_DAY_HOURS_MINUTES_AND_SECONDS_MATCH     =   6       /*!<  Alarm 1 when day, hours, minutes, and seconds match   */
} DS1624_alarm1_register_t;


/**
  * @brief   Alarm 2 Mask Bits
  */
typedef enum
{
    ALARM2_ALARM_ONCE_PER_MINUTE                        =   1,      /*!<  Alarm 2 once per minute                               */
    ALARM2_WHEN_MINUTES_MATCH                           =   2,      /*!<  Alarm 2 when minutes match                            */
    ALARM2_WHEN_HOURS_MINUTES_MATCH                     =   3,      /*!<  Alarm 2 when hours and minutes match                  */
    ALARM2_WHEN_DATE_HOURS_AND_MINUTES_MATCH            =   4,      /*!<  Alarm 2 when date, hours and minutes match            */
    ALARM2_WHEN_DAY_HOURS_AND_MINUTES_MATCH             =   5       /*!<  Alarm 2 when day, hours and minutes match             */
} DS1624_alarm2_register_t;


// TIMEKEEPING REGISTERS
// SECONDS
typedef enum
{
    SECONDS_SECONDS_MASK                                =   0x0F,   /*!<  Seconds Seconds mask                                  */
    SECONDS_10SECONDS_MASK                              =   0x70    /*!<  Seconds 10Seconds mask                                */
} DS1624_seconds_t;


// MINUTES
typedef enum
{
    MINUTES_MINUTES_MASK                                =   0x0F,   /*!<  Minutes Minutes mask                                  */
    MINUTES_10MINUTES_MASK                              =   0x70    /*!<  Minutes 10Minutes mask                                */
} DS1624_minutes_t;


// HOURS
typedef enum
{
    HOURS_HOUR_MASK                                     =   0x0F,       /*!<  Hour Hour mask                                        */
    HOURS_10HOUR_MASK                                   =   0x10,       /*!<  Hour 10Hour mask                                      */

    HOURS_nAM_PM_MASK                                   =   0x20,       /*!<  Hour #AM/PM mask                                      */
    HOURS_AM_ENABLED                                    =   ( 0 << 5 ), /*!<  Hour AM ENABLED                                       */
    HOURS_PM_ENABLED                                    =   ( 1 << 5 ), /*!<  Hour PM ENABLED                                       */

    HOURS_12_n24_MASK                                   =   0x40,       /*!<  Hour 12/#24 mask                                      */
    HOURS_12_ENABLED                                    =   ( 1 << 6 ), /*!<  Hour 12 ENABLED                                       */
    HOURS_24_ENABLED                                    =   ( 0 << 6 ), /*!<  Hour 24 ENABLED                                       */
} DS1624_hours_t;


// DAY
typedef enum
{
    DAY_DAY_MASK                                        =   0x07    /*!<  Day Day mask                                          */
} DS1624_day_t;


// DATE
typedef enum
{
    DATE_DATE_MASK                                       =   0x0F,   /*!<  Date Date mask                                       */
    DATE_10DATE_MASK                                     =   0x30    /*!<  Date 10Date mask                                     */
} DS1624_date_t;


// MONTH/CENTURY
typedef enum
{
    MONTH_MONTH_MASK                                      =   0x0F,  /*!<  Month Month mask                                     */
    MONTH_10MONTH_MASK                                    =   0x10,  /*!<  Month 10Month mask                                   */
    MONTH_CENTURY_MASK                                    =   0x80   /*!<  Month Century mask                                   */
} DS1624_month_t;


// YEAR
typedef enum
{
    YEAR_YEAR_MASK                                        =   0x0F,   /*!<  Year Year mask                                       */
    YEAR_10YEAR_MASK                                      =   0xF0    /*!<  Year 10Year mask                                     */
} DS1624_year_t;


// ALARM 1 SECONDS
typedef enum
{
    ALARM1_A1M1_MASK                                       =   0x80,   /*!<  Alarm1 A1M1 mask                                    */
    ALARM1_10SECONDS_MASK                                  =   0x70,   /*!<  Alarm1 10Seconds mask                               */
    ALARM1_SECONDS_MASK                                    =   0x0F    /*!<  Alarm1 Seconds mask                                 */
} DS1624_alarm1_seconds_t;


// ALARM 1 MINUTES
typedef enum
{
    ALARM1_A1M2_MASK                                       =   0x80,   /*!<  Alarm1 A1M2 mask                                    */
    ALARM1_10MINUTES_MASK                                  =   0x70,   /*!<  Alarm1 10Minutes mask                               */
    ALARM1_MINUTES_MASK                                    =   0x0F    /*!<  Alarm1 Minutes mask                                 */
} DS1624_alarm1_minutes_t;


// ALARM 1 HOURS
typedef enum
{
    ALARM1_A1M3_MASK                                       =   0x80,   /*!<  Alarm1 A1M3 mask                                    */
    ALARM1_10HOUR_MASK                                     =   0x10,   /*!<  Alarm1 10Hour mask                                  */
    ALARM1_HOUR_MASK                                       =   0x0F    /*!<  Alarm1 Hour mask                                    */
} DS1624_alarm1_hours_t;


// ALARM 1 DAY/DATE
typedef enum
{
    ALARM1_A1M4_MASK                                       =   0x80,   /*!<  Alarm1 A1M4 mask                                    */
    ALARM1_DYDT_MASK                                       =   0x40,   /*!<  Alarm1 DY/DT mask                                   */
    ALARM1_10DATE_MASK                                     =   0x30,   /*!<  Alarm1 10Date mask                                  */
    ALARM1_DATE_DAY_MASK                                   =   0x0F    /*!<  Alarm1 Day/Date mask                                */
} DS1624_alarm1_day_date_t;


// ALARM 2 MINUTES
typedef enum
{
    ALARM2_A2M2_MASK                                       =   0x80,   /*!<  Alarm2 A2M2 mask                                    */
    ALARM2_10MINUTES_MASK                                  =   0x70,   /*!<  Alarm2 10Minutes mask                               */
    ALARM2_MINUTES_MASK                                    =   0x0F    /*!<  Alarm2 Minutes mask                                 */
} DS1624_alarm2_minutes_t;


// ALARM 2 HOURS
typedef enum
{
    ALARM2_A2M3_MASK                                       =   0x80,   /*!<  Alarm2 A1M3 mask                                    */
    ALARM2_10HOUR_MASK                                     =   0x10,   /*!<  Alarm2 10Hour mask                                  */
    ALARM2_HOUR_MASK                                       =   0x0F    /*!<  Alarm2 Hour mask                                    */
} DS1624_alarm2_hours_t;


// ALARM 2 DAY/DATE
typedef enum
{
    ALARM2_A2M4_MASK                                       =   0x80,   /*!<  Alarm2 A2M4 mask                                    */
    ALARM2_DYDT_MASK                                       =   0x40,   /*!<  Alarm2 DY/DT mask                                   */
    ALARM2_10DATE_MASK                                     =   0x30,   /*!<  Alarm2 10Date mask                                  */
    ALARM2_DATE_DAY_MASK                                   =   0x0F    /*!<  Alarm2 Day/Date mask                                */
} DS1624_alarm2_day_date_t;



// MACRO: It turns BCD into decimal
#define _MYBCD_TO_DECIMAL( x ) ({                           \
        ( ( x & 0x0F ) + ( ( ( x & 0xF0 ) >> 4) * 10) );    \
        })

// MACRO: It turns decimal into BCD
#define _MYDECIMAL_TO_BCD( x ) ({                               \
        ( ( ( x / 10) << 4 ) & 0xF0 ) | ( ( x % 10 ) & 0x0F );  \
        })



#ifndef DS1624_VECTOR_STRUCT_H
#define DS1624_VECTOR_STRUCT_H
typedef struct
{
    uint8_t MSBTemperature;
    uint8_t LSBTemperature;
    uint8_t RawAging;
    uint8_t Control_Status_Register;

    float   Temperature;
} DS1624_vector_data_t;

typedef struct
{
    uint8_t Date;
    uint8_t Month;
    uint8_t Year;
    uint8_t DayOfWeek;
    uint8_t Century;

    uint8_t Hours;
    uint8_t Minutes;
    uint8_t Seconds;
    uint8_t Mode_nAM_PM;                        /*!<  Mode_nAM_PM = 0    -> AM | Mode_nAM_PM = 0x20 -> PM     */
    uint8_t Mode_12_n24;                        /*!<  Mode_12_n24 = 0x40 -> 12 | Mode_12_n24 = 0    -> 24     */
} DS1624_vector_date_time_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    DS1624_SUCCESS     =       0,
    DS1624_FAILURE     =       1,

    DS1624_TIMEOUT     =       1000
} DS1624_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
DS1624_status_t  DS1624_Init                        ( I2C_parameters_t myI2Cparameters );

/** It reads the temperature data.
      */
DS1624_status_t  DS1624_ReadTemperature             ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t*  myTemperature );

/** It reads the raw temperature data.
      */
DS1624_status_t  DS1624_ReadRawTemperature          ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t*  myRawTemperature );

/** It triggers a new temperature measurement.
      */
DS1624_status_t  DS1624_StartNewConvertTemperature  ( I2C_parameters_t myI2Cparameters );

/** It reads the raw aging data.
      */
DS1624_status_t  DS1624_ReadRawAging                ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t*  myRawAging );

/** It sets the 32kHz pin output: Enabled/Disabled.
      */
DS1624_status_t  DS1624_Status32kHzPin              ( I2C_parameters_t myI2Cparameters, DS1624_status_enable_32khz_output_t  my32kHzPin );

/** It clears alarm flags.
      */
DS1624_status_t  DS1624_ClearAlarmFlag              ( I2C_parameters_t myI2Cparameters, DS1624_status_alarm1_flag_t  myA1F, DS1624_status_alarm2_flag_t myA2F );

/** It sets the alarm1.
      */
DS1624_status_t  DS1624_SetAlarm1                   ( I2C_parameters_t myI2Cparameters, DS1624_alarm1_register_t myAlarm1 );

/** It sets the alarm2.
      */
DS1624_status_t  DS1624_SetAlarm2                   ( I2C_parameters_t myI2Cparameters, DS1624_alarm2_register_t myAlarm2 );

/** It enables/disables Alarm ( 1 and 2 ) interrupts.
      */
DS1624_status_t  DS1624_SetAlarmsInterrupt          ( I2C_parameters_t myI2Cparameters, DS1624_control_status_alarm1_t myAlarm1, DS1624_control_status_alarm2_t myAlarm2 );

/** It sets square-wave output frequency.
      */
DS1624_status_t  DS1624_SetSquareWaveOutput         ( I2C_parameters_t myI2Cparameters, DS1624_control_status_rate_select_t myRate );

/** It gets the date.
      */
DS1624_status_t  DS1624_GetDate                     ( I2C_parameters_t myI2Cparameters, DS1624_vector_date_time_t* myDate );

/** It sets the date.
      */
DS1624_status_t  DS1624_SetDate                     ( I2C_parameters_t myI2Cparameters, DS1624_vector_date_time_t myDate );

/** It gets the time.
      */
DS1624_status_t  DS1624_GetTime                     ( I2C_parameters_t myI2Cparameters, DS1624_vector_date_time_t* myTime );

/** It sets the time.
      */
DS1624_status_t  DS1624_SetTime                     ( I2C_parameters_t myI2Cparameters, DS1624_vector_date_time_t myTime );

/** It gets the CONTROL/STATUS register.
      */
DS1624_status_t  DS1624_GetControlStatusRegister    ( I2C_parameters_t myI2Cparameters, DS1624_vector_data_t* myControlStatusReg );
