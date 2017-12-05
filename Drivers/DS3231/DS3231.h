/**
 * @brief       DS3231.h
 * @details     Extremely Accurate I2C-Integrated RTC/TCXO/Crystal.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017    The ORIGIN
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
    DS3231_ADDRESS     =   0x68                   /*!<   Address                                            */
} DS3231_address_t;


// REGISTERS
/**
  * @brief   TIMEKEEPING REGISTERS
  */
typedef enum
{
    DS3231_SECONDS          =   0x00,               /*!<  Seconds. RANGE 00-59                                  */
    DS3231_MINUTES          =   0x01,               /*!<  Minutes. RANGE 00-59                                  */
    DS3231_HOURS            =   0x02,               /*!<  Hours. 1-12 + AM/PM 00-23                             */
    DS3231_DAY              =   0x03,               /*!<  Day. 1-7                                              */
    DS3231_DATE             =   0x04,               /*!<  Date. 01-31                                           */
    DS3231_MONTH_CENTURY    =   0x05,               /*!<  Month/Century. 01-12 + Century                        */
    DS3231_YEAR             =   0x06,               /*!<  Year. 00-99                                           */
    DS3231_ALARM_1_SEONDS   =   0x07,               /*!<  Alarm 1 seconds. 00-59                                */
    DS3231_ALARM_1_MINUTES  =   0x08,               /*!<  Alarm 1 minutes. 00-59                                */
    DS3231_ALARM_1_HOURS    =   0x09,               /*!<  Alarm 1 hours. 1-12 + AM/PM 00-23                     */
    DS3231_ALARM_1_DAY_DATE =   0x0A,               /*!<  Alarm 1 day/date. 1-7/1-31                            */
    DS3231_ALARM_2_MINUTES  =   0x0B,               /*!<  Alarm 2 minutes. 00-59                                */
    DS3231_ALARM_2_HOURS    =   0x0C,               /*!<  Alarm 2 hours. 1-12 + AM/PM 00-23                     */
    DS3231_ALARM_2_DAY_DATE =   0x0D,               /*!<  Alarm 2 day/date. 1-7/1-31                            */
    DS3231_CONTROL          =   0x0E,               /*!<  Control                                               */
    DS3231_CONTROL_STATUS   =   0x0F,               /*!<  Control/Status                                        */
    DS3231_AGING_OFFSET     =   0x10,               /*!<  Aging offset                                          */
    DS3231_MSB_TEMPERATURE  =   0x11,               /*!<  MSB of Temp                                           */
    DS3231_LSB_TEMPERATURE  =   0x12                /*!<  LSB of Temp                                           */
} DS3231_registers_t;



// CONTROL REGISTER
/**
  * @brief   Enable Oscillator ( #EOSC )
  */
typedef enum
{
    CONTROL_STATUS_ENABLE_OSCILLATOR_MASK       =   ( 1 << 7 ),     /*!<  #EOSC Mask                            */
    CONTROL_STATUS_ENABLE_OSCILLATOR_ENABLED    =   ( 1 << 7 ),     /*!<  Enable oscillator                     */
    CONTROL_STATUS_ENABLE_OSCILLATOR_DISABLED   =   ( 0 << 7 )      /*!<  Disable oscillator                    */
} DS3231_control_status_enable_oscillator_t;


/**
  * @brief   Battery-Backed Square-Wave Enable ( BBSQW )
  */
typedef enum
{
    CONTROL_STATUS_BBSQW_MASK       =   ( 1 << 6 ),                 /*!<  BBSQW Mask                            */
    CONTROL_STATUS_BBSQW_ENABLED    =   ( 1 << 6 ),                 /*!<  Enable BBSQW                          */
    CONTROL_STATUS_BBSQW_DISABLED   =   ( 0 << 6 )                  /*!<  Disable BBSQW                         */
} DS3231_control_status_bbsqw_t;


/**
  * @brief   Convert Temperature ( CONV )
  */
typedef enum
{
    CONTROL_STATUS_CONVERT_TEMPERATURE_MASK       =   ( 1 << 5 ),   /*!<  CONVERT TEMPERATURE Mask              */
    CONTROL_STATUS_CONVERT_TEMPERATURE_ENABLED    =   ( 1 << 5 ),   /*!<  Enable CONVERT_TEMPERATURE            */
    CONTROL_STATUS_CONVERT_TEMPERATURE_DISABLED   =   ( 0 << 5 )    /*!<  Disable CONVERT_TEMPERATURE           */
} DS3231_control_status_convert_temperature_t;


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
} DS3231_control_status_rate_select_t;


/**
  * @brief   Interrupt Control ( INTCN )
  */
typedef enum
{
    CONTROL_STATUS_INTERRUPT_CONTROL_MASK       =   ( 1 << 2 ),     /*!<  Interrupt control Mask              */
    CONTROL_STATUS_INTERRUPT_CONTROL_SQW        =   ( 0 << 2 ),     /*!<  Square wave is output               */
    CONTROL_STATUS_INTERRUPT_CONTROL_INT        =   ( 1 << 2 )      /*!<  Alarm activates the output          */
} DS3231_control_status_interrupt_control_t;


/**
  * @brief   Alarm 2 Interrupt Enable ( A2IE )
  */
typedef enum
{
    CONTROL_STATUS_ALARM2_MASK       =   ( 1 << 1 ),                /*!<  Alarm 2 Mask                        */
    CONTROL_STATUS_ALARM2_ENABLED    =   ( 1 << 1 ),                /*!<  Alarm 2 enabled                     */
    CONTROL_STATUS_ALARM2_DISABLED   =   ( 0 << 1 )                 /*!<  Alarm 2 disabled                    */
} DS3231_control_status_alarm2_t;


/**
  * @brief   Alarm 1 Interrupt Enable ( A1IE )
  */
typedef enum
{
    CONTROL_STATUS_ALARM1_MASK       =   ( 1 << 0 ),                /*!<  Alarm 1 Mask                        */
    CONTROL_STATUS_ALARM1_ENABLED    =   ( 1 << 0 ),                /*!<  Alarm 1 enabled                     */
    CONTROL_STATUS_ALARM1_DISABLED   =   ( 0 << 0 )                 /*!<  Alarm 1 disabled                    */
} DS3231_control_status_alarm1_t;



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
} DS3231_status_oscillator_stop_flag_t;


/**
  * @brief   Enable 32kHz Output ( EN32kHz )
  */
typedef enum
{
    STATUS_ENABLE_32KHZ_OUTPUT_MASK       =   ( 1 << 3 ),          /*!<  32kHz output mask                     */
    STATUS_ENABLE_32KHZ_OUTPUT_ENABLED    =   ( 1 << 3 ),          /*!<  32kHz output on 32kHz pin             */
    STATUS_ENABLE_32KHZ_OUTPUT_DISABLED   =   ( 0 << 3 )           /*!<  32kHz output disabled                 */
} DS3231_status_enable_32khz_output_t;


/**
  * @brief   Busy ( BSY )
  */
typedef enum
{
    STATUS_BUSY_MASK        =   ( 1 << 2 ),                         /*!<  BSY mask                              */
    STATUS_BUSY_BUSY        =   ( 1 << 2 ),                         /*!<  device busy executing TCXO functions  */
    STATUS_BUSY_NOBUSY      =   ( 0 << 2 )                          /*!<  device IS NOT busy                    */
} DS3231_status_busy_t;


/**
  * @brief   Alarm 2 Flag ( A2F )
  */
typedef enum
{
    STATUS_ALARM2_FLAG_MASK        =   ( 1 << 1 ),                  /*!<  Alarm 2 flag mask                     */
    STATUS_ALARM2_FLAG_ENABLED     =   ( 1 << 1 ),                  /*!<  Alarm 2 flag enabled                  */
    STATUS_ALARM2_FLAG_DISABLED    =   ( 0 << 1 ),                  /*!<  Alarm 2 flag disabled                 */
    STATUS_ALARM2_FLAG_RESET       =   ( 0 << 1 ),                  /*!<  Alarm 2 flag reset flag               */
} DS3231_status_alarm2_flag_t;



/**
  * @brief   Alarm 1 Flag ( A1F )
  */
typedef enum
{
    STATUS_ALARM1_FLAG_MASK        =   ( 1 << 0 ),                  /*!<  Alarm 1 flag mask                     */
    STATUS_ALARM1_FLAG_ENABLED     =   ( 1 << 0 ),                  /*!<  Alarm 1 flag enabled                  */
    STATUS_ALARM1_FLAG_DISABLED    =   ( 0 << 0 ),                  /*!<  Alarm 1 flag disabled                 */
    STATUS_ALARM1_FLAG_RESET       =   ( 0 << 0 ),                  /*!<  Alarm 1 flag reset flag               */
} DS3231_status_alarm1_flag_t;





#ifndef DS3231_VECTOR_STRUCT_H
#define DS3231_VECTOR_STRUCT_H
typedef struct
{
    uint8_t myAgingOffset;
    uint8_t myMSBTemperature;
    uint8_t myLSBTemperature;

    int16_t myTemperature;
} DS3231_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    DS3231_SUCCESS     =       0,
    DS3231_FAILURE     =       1
} DS3231_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
DS3231_status_t  DS3231_Init      ( I2C_parameters_t myI2Cparameters );
DS3231_status_t  DS3231_SetPins   ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t  myConfDATA );
DS3231_status_t  DS3231_ReadPins  ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t* myReadDATA );
