/**
 * @brief       DS1307.h
 * @details     64 x 8, Serial, I2C Real-Time Clock.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/July/2018
 * @version     28/July/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef DS1307_H_
#define DS1307_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    DS1307_ADDRESS     =   0b1101000            /*!<   DS1307 I2C Address                                  */
} DS1307_addresses_t;


// REGISTER MAP
/**
  * @brief   TIMEKEEPER REGISTERS
  */
typedef enum
{
    DS1307_SECONDS  =   0x00,                   /*!<  Seconds                   ( Read/Write )              */
    DS1307_MINUTES  =   0x01,                   /*!<  Minutes                   ( Read/Write )              */
    DS1307_HOURS    =   0x02,                   /*!<  Hours                     ( Read/Write )              */
    DS1307_DAY      =   0x03,                   /*!<  Day                       ( Read/Write )              */
    DS1307_DATE     =   0x04,                   /*!<  Date                      ( Read/Write )              */
    DS1307_MONTH    =   0x05,                   /*!<  Month                     ( Read/Write )              */
    DS1307_YEAR     =   0x06,                   /*!<  Year                      ( Read/Write )              */
    DS1307_CONTROL  =   0x07                    /*!<  Control                   ( Read/Write )              */
} DS1307_timekeeper_registers_t;



// SECONDS
/**
  * @brief   CLOCK HALT
  */
typedef enum
{
    SECONDS_CH_MASK                 =   ( 1 << 7 ),         /*!<  CH mask                                    */
    SECONDS_CH_OSCILLATOR_ENABLED   =   ( 0 << 7 ),         /*!<  CH Oscillator is enabled                   */
    SECONDS_CH_OSCILLATOR_DISABLED  =   ( 1 << 7 )          /*!<  CH Oscillator is disabled                  */
} DS1307_seconds_ch_t;


/**
  * @brief   10 SECONDS
  */
typedef enum
{
    SECONDS_10SECONDS_MASK          =   ( 0b111 << 4 )       /*!<  10 Seconds mask                            */
} DS1307_seconds_10seconds_t;


/**
  * @brief   SECONDS
  */
typedef enum
{
    SECONDS_SECONDS_MASK            =   ( 0b1111 << 0 )       /*!<  Seconds mask                            */
} DS1307_seconds_seconds_t;



// MINUTES
/**
  * @brief   10 MINUTES
  */
typedef enum
{
    MINUTES_10MINUTES_MASK          =   ( 0b111 << 4 )       /*!<  10 Minutes mask                         */
} DS1307_minutes_10minutes_t;


/**
  * @brief   MINUTES
  */
typedef enum
{
    MINUTES_MINUTES_MASK            =   ( 0b1111 << 0 )       /*!<  Minutes mask                            */
} DS1307_minutes_minutes_t;



// HOURS
/**
  * @brief   12-HOUR OR 24-HOUR MODE
  */
typedef enum
{
    HOURS_MODE_MASK                 =   ( 1 << 6 ),          /*!<  Hours 12/24 mode mask                   */
    HOURS_MODE_12H                  =   ( 1 << 6 ),          /*!<  Hours 12-hour mode enabled              */
    HOURS_MODE_24H                  =   ( 0 << 6 )           /*!<  Hours 24-hour mode enabled              */
} DS1307_hours_mode_t;


/**
  * @brief   AM OR PM MODE
  */
typedef enum
{
    HOURS_MODE_AM_PM_MASK           =   ( 1 << 5 ),          /*!<  Hours am/pm mode mask                   */
    HOURS_MODE_AM                   =   ( 1 << 5 ),          /*!<  Hours AM mode enabled                   */
    HOURS_MODE_PM                   =   ( 0 << 5 )           /*!<  Hours PM mode enabled                   */
} DS1307_hours_am_pm_mode_t;


/**
  * @brief   10 HOUR
  */
typedef enum
{
    HOUR_10HOUR_MASK                =   ( 0b11 << 4 )        /*!<  10 Hour mask                             */
} DS1307_hours_10hour_t;


/**
  * @brief   HOURS
  */
typedef enum
{
    HOUR_HOURS_MASK                 =   ( 0b1111 << 0 )      /*!<  Hours mask                               */
} DS1307_hours_hours_t;



// DAY
/**
  * @brief   DAY
  */
typedef enum
{
    DAY_MASK                        =   ( 0b111 << 0 ),     /*!<  Day mask                               */
    DAY_SUNDAY                      =   ( 1 << 0 ),         /*!<  Day Sunday                             */
    DAY_MONDAY                      =   ( 2 << 0 ),         /*!<  Day Monday                             */
    DAY_TUESDAY                     =   ( 3 << 0 ),         /*!<  Day Tuesday                            */
    DAY_WEDNESDAY                   =   ( 4 << 0 ),         /*!<  Day Wednesday                          */
    DAY_THURSDAY                    =   ( 5 << 0 ),         /*!<  Day Thursday                           */
    DAY_FRIDAY                      =   ( 6 << 0 ),         /*!<  Day Friday                             */
    DAY_SATURDAY                    =   ( 7 << 0 )          /*!<  Day Saturday                           */
} DS1307_day_t;



// DATE
/**
  * @brief   10 DATE
  */
typedef enum
{
    DATE_10DATE_MASK                =   ( 0b11 << 4 )        /*!<  10 Date mask                         */
} DS1307_date_10date_t;


/**
  * @brief   DATE
  */
typedef enum
{
    DATE_DATE_MASK                  =   ( 0b1111 << 0 )       /*!<  Date mask                            */
} DS1307_date_date_t;



// MONTH
/**
  * @brief   10 MONTH
  */
typedef enum
{
    MONTH_10MONTH_MASK              =   ( 0b1 << 4 )         /*!<  10 Month mask                         */
} DS1307_month_10month_t;


/**
  * @brief   MONTH
  */
typedef enum
{
    MONTH_MONTH_MASK                =   ( 0b1111 << 0 )       /*!<  Month mask                            */
} DS1307_month_month_t;



// YEAR
/**
  * @brief   10 YEAR
  */
typedef enum
{
    YEAR_10YEAR_MASK                =   ( 0b1111 << 4 )       /*!<  10 Year mask                           */
} DS1307_year_10month_t;


/**
  * @brief   YEAR
  */
typedef enum
{
    YEAR_YEAR_MASK                  =   ( 0b1111 << 0 )       /*!<  Year mask                              */
} DS1307_year_year_t;



// CONTROL
/**
  * @brief   OUTPUT CONTROL (OUT)
  */
typedef enum
{
    CONTROL_OUT_MASK                =   ( 1 << 7 ),         /*!<  OUT mask                                */
    CONTROL_OUT_HIGH                =   ( 1 << 7 ),         /*!<  SQW/OUT high                            */
    CONTROL_OUT_LOW                 =   ( 0 << 7 )          /*!<  SQW/OUT low                             */
} DS1307_control_out_t;


/**
  * @brief   SQUARE-WAVE ENABLE (SQWE)
  */
typedef enum
{
    CONTROL_SQWE_MASK               =   ( 1 << 4 ),         /*!<  SQWE mask                               */
    CONTROL_SQWE_ENABLED            =   ( 1 << 4 ),         /*!<  SQWE enabled                            */
    CONTROL_SQWE_DISABLED           =   ( 0 << 4 )          /*!<  SQWE disabled                           */
} DS1307_control_sqwe_t;


/**
  * @brief   RATE SELECT
  */
typedef enum
{
    CONTROL_RS_MASK                 =   ( 0b11 << 0 ),      /*!<  RS mask                                   */
    CONTROL_RS_1_HZ                 =   ( 0b00 << 0 ),      /*!<  RS 1Hz                                    */
    CONTROL_RS_4_096_KHZ            =   ( 0b01 << 0 ),      /*!<  RS 4.096kHz                               */
    CONTROL_RS_8_192_KHZ            =   ( 0b10 << 0 ),      /*!<  RS 8.192kHz                               */
    CONTROL_RS_32_768_KHZ           =   ( 0b11 << 0 )       /*!<  RS 32.768kHz                              */
} DS1307_control_rate_select_t;



// ALTERNATIVES
/**
  * @brief   MONTH
  */
typedef enum
{
    MONTH_JANUARY                   =   0x01,               /*!<  January                                   */
    MONTH_FEBRUARY                  =   0x02,               /*!<  February                                  */
    MONTH_MARCH                     =   0x03,               /*!<  March                                     */
    MONTH_APRIL                     =   0x04,               /*!<  April                                     */
    MONTH_MAY                       =   0x05,               /*!<  May                                       */
    MONTH_JUNE                      =   0x06,               /*!<  June                                      */
    MONTH_JULY                      =   0x07,               /*!<  July                                      */
    MONTH_AUGUST                    =   0x08,               /*!<  August                                    */
    MONTH_SEPTEMBER                 =   0x09,               /*!<  September                                 */
    MONTH_OCTOBER                   =   0x10,               /*!<  October                                   */
    MONTH_NOVEMBER                  =   0x11,               /*!<  November                                  */
    MONTH_DECEMBER                  =   0x12                /*!<  December                                  */
} DS1307_month_t;





#ifndef DS1307_VECTOR_STRUCT_H
#define DS1307_VECTOR_STRUCT_H
typedef struct
{
    uint32_t                    BCDTime;
    DS1307_hours_mode_t         Time12H_24HMode;
    DS1307_hours_am_pm_mode_t   TimeAM_PM_Mode;

    DS1307_day_t                DayOfTheWeek;

    uint8_t                     BCDDate;

    DS1307_month_t              BCDMonth;

    uint8_t                     BCDYear;
} DS1307_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    DS1307_SUCCESS     =       0,
    DS1307_FAILURE     =       1
} DS1307_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
DS1307_status_t  DS1307_Init                ( I2C_parameters_t myI2Cparameters                                                                                              );

/** It configures the square-wave output.
  */
DS1307_status_t  DS1307_SquareWaveOutput    ( I2C_parameters_t myI2Cparameters, DS1307_control_sqwe_t mySQWE, DS1307_control_rate_select_t myRateSelect                     );

/** It configures the output pin ( OUT ).
  */
DS1307_status_t  DS1307_ConfOutput          ( I2C_parameters_t myI2Cparameters, DS1307_control_out_t myOUT                                                                  );

/** It sets the time ( BCD mode ).
  */
DS1307_status_t  DS1307_SetTime             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myTime                                                                 );

/** It gets the time ( BCD mode ).
  */
DS1307_status_t  DS1307_GetTime             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTime                                                                );

/** It sets the day of the week.
  */
DS1307_status_t  DS1307_SetDayOfTheWeek     ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myDayOfTheWeek                                                         );

/** It gets the day of the week.
  */
DS1307_status_t  DS1307_GetDayOfTheWeek     ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myDayOfTheWeek                                                        );

/** It sets the date ( BCD mode ).
  */
DS1307_status_t  DS1307_SetDate             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myDate                                                                 );

/** It gets the date ( BCD mode ).
  */
DS1307_status_t  DS1307_GetDate             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myDate                                                                );

/** It sets the month ( BCD mode ).
  */
DS1307_status_t  DS1307_SetMonth            ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myMonth                                                                );

/** It gets the month ( BCD mode ).
  */
DS1307_status_t  DS1307_GetMonth            ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myMonth                                                               );

/** It sets the year ( BCD mode ).
  */
DS1307_status_t  DS1307_SetYear             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myYear                                                                 );

/** It gets the year ( BCD mode ).
  */
DS1307_status_t  DS1307_GetYear             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myYear                                                                );




#ifdef __cplusplus
}
#endif

#endif /* DS1307_H */
