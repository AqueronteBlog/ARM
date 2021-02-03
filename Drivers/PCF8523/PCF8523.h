/**
 * @brief       PCF8523.h
 * @details     Real-Time Clock (RTC) and calendar.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#ifndef PCF8523_H
#define PCF8523_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  PCF8523_ADDRESS     =   0b1101000                                  /*!<   I2C slave address byte                       */
} PCF8523_address_t;



/**
  * @brief   REGISTERS ORGANIZATION
  */
typedef enum
{
  /* CONTROL REGISTERS  */
  PCF8523_CONTROL_1         =   0x00,                  /*!<  Control register 1                 */
  PCF8523_CONTROL_2         =   0x01,                  /*!<  Control register 2                 */
  PCF8523_CONTROL_3         =   0x02,                  /*!<  Control register 3                 */

  /* TIME AND DATE REGISTERS  */
  PCF8523_SECONDS           =   0x03,                  /*!<  Seconds register                   */
  PCF8523_MINUTES           =   0x04,                  /*!<  Minutes register                   */
  PCF8523_HOURS             =   0x05,                  /*!<  Hours register                     */
  PCF8523_DAYS              =   0x06,                  /*!<  Days register                      */
  PCF8523_WEEKDAYS          =   0x07,                  /*!<  Weekdays register                  */
  PCF8523_MONTHS            =   0x08,                  /*!<  Months register                    */
  PCF8523_YEARS             =   0x09,                  /*!<  Years register                     */

  /* ALARM REGISTERS   */
  PCF8523_MINUTE_ALARM      =   0x0A,                  /*!<  Minute alarm register               */
  PCF8523_HOUR_ALARM        =   0x0B,                  /*!<  Hour alarm register                 */
  PCF8523_DAY_ALARM         =   0x0C,                  /*!<  Day alarm register                  */
  PCF8523_WEEKDAY_ALARM     =   0x0D,                  /*!<  Weekday alarm regist                */

  /* OFFSET REGISTER   */
  PCF8523_OFFSET            =   0x0E,                  /*!<  Offset register                     */

  /* CLOCKOUT AND TIMER REGISTERS   */
  PCF8523_TMR_CLOCKOUT_CTRL =   0x0F,                  /*!<  Tmr CLOCKOUT ctrl register          */
  PCF8523_TMR_A_FREQ_CTRL   =   0x10,                  /*!<  Tmr A freq ctrl register            */
  PCF8523_TMR_A_REG         =   0x11,                  /*!<  Tmr A reg register                  */
  PCF8523_TMR_B_FREQ_CTRL   =   0x12,                  /*!<  Tmr B freq ctrl register            */
  PCF8523_TMR_B_REG         =   0x13                   /*!<  Tmr B reg register                  */
} PCF8523_registers_t;



/**
  * @brief   Register Control_1
  */
/* CAP_SEL <7>: INTERNAL CAPACITOR SELECTION FOR QUARTZ CRYSTALS
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_CAP_SEL_MASK            =   ( 1U << 7U ),     /*!<  CAP_SEL mask                              */
  CONTROL_1_CAP_SEL_7_PF            =   ( 0U << 7U ),     /*!<  CAP_SEL: 7pF                  [ Default ] */
  CONTROL_1_CAP_SEL_12_5_PF         =   ( 1U << 7U )      /*!<  CAP_SEL: 12.5pF                           */
} PCF8523_control_1_cap_sel_t;



/* STOP <5>: STOP BIT
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_STOP_MASK               =   ( 1U << 5U ),     /*!<  STOP mask                                 */
  CONTROL_1_STOP_RTC_CLOCK_RUNS     =   ( 0U << 5U ),     /*!<  STOP: RTC clock runs          [ Default ] */
  CONTROL_1_STOP_RTC_CLOCK_STOPPED  =   ( 1U << 5U )      /*!<  STOP: RTC clock is stopped                */
} PCF8523_control_1_stop_t;



/* SR <4>: SOFTWARE RESET 
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_SR_MASK                 =   ( 1U << 4U ),     /*!<  SR mask                                   */
  CONTROL_1_SR_NO_SOFTWARE_RESET    =   ( 0U << 4U ),     /*!<  SR: no software reset         [ Default ] */
  CONTROL_1_SR_SOFTWARE_RESET       =   ( 1U << 4U )      /*!<  SR: initiate software reset               */
} PCF8523_control_1_sr_t;



/* 12_24 <3>: 24/12 MODE SELECTED 
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_12_24_MASK              =   ( 1U << 3U ),     /*!<  12_24 mask                                */
  CONTROL_1_12_24_MODE_24_HOUR      =   ( 0U << 3U ),     /*!<  24 hour mode                  [ Default ] */
  CONTROL_1_12_24_MODE_12_HOUR      =   ( 1U << 3U )      /*!<  12 hour mode                              */
} PCF8523_control_1_12_24_t;



/* SIE <2>: SECOND INTERRUPT ENABLE 
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_SIE_MASK                      =   ( 1U << 2U ), /*!<  SIE mask                                  */
  CONTROL_1_SIE_SECOND_INTERRUPT_DISABLED =   ( 0U << 2U ), /*!<  Second interrupt disabled     [ Default ] */
  CONTROL_1_SIE_SECOND_INTERRUPT_ENABLED  =   ( 1U << 2U )  /*!<  Second interrupt enabled                  */
} PCF8523_control_1_sie_t;



/* AIE <1>: ALARM INTERRUPT ENABLE 
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_AIE_MASK                      =   ( 1U << 1U ), /*!<  AIE mask                                  */
  CONTROL_1_AIE_ALARM_INTERRUPT_DISABLED  =   ( 0U << 1U ), /*!<  Alarm interrupt disabled      [ Default ] */
  CONTROL_1_AIE_ALARM_INTERRUPT_ENABLED   =   ( 1U << 1U )  /*!<  Alarm interrupt enabled                   */
} PCF8523_control_1_aie_t;



/* CIE <0>: CORRECTION INTERRUPT ENABLE 
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_1_CIE_MASK                              =   ( 1U << 0U ), /*!<  CIE mask                                                      */
  CONTROL_1_CIE_NO_CORRECTION_INTERRUPT_GENERATED =   ( 0U << 0U ), /*!<  CIE: no correction interrupt generated [ Default ]            */
  CONTROL_1_CIE_INTERRUPT_PULSES_GENERATED        =   ( 1U << 0U )  /*!<  CIE: interrupt pulses are generated at every correction cycle */
} PCF8523_control_1_cie_t;



/**
  * @brief   Register Control_2
  */
/* WTAF <7>: WATCHDOG TIMER A INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_WTAG_MASK                         =   ( 1U << 7U ),     /*!<  WTAF mask                                           */
  CONTROL_2_WTAF_NO_WDT_A_INTERRUPT_GENERATED =   ( 0U << 7U ),     /*!<  No watchdog timer A interrupt generated [ Default ] */
  CONTROL_2_WTAF_WDT_A_INTERRUPT_GENERATED    =   ( 1U << 7U )      /*!<  Flag set when watchdog timer A interrupt generated  */
} PCF8523_control_2_wtaf_t;



/* CTAF <6>: COUNTDOWN TIMER A INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_CTAF_MASK                                     =   ( 1U << 6U ),   /*!<  CTAF mask                                             */
  CONTROL_2_CTAF_NO_COUNTDOWN_TIMER_A_INTERRUPT_GENERATED =   ( 0U << 6U ),   /*!<  No countdown timer A interrupt generated  [ Default ] */
  CONTROL_2_CTAF_CONTDOWN_TIMER_A_INTERRUPT_GENERATED     =   ( 1U << 6U )    /*!<  Flag set when countdown timer A interrupt generated   */
} PCF8523_control_2_ctaf_t;



/* CTBF <5>: COUNTDOWN TIMER B INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_CTBF_MASK                                     =   ( 1U << 5U ),   /*!<  CTBF mask                                             */
  CONTROL_2_CTBF_NO_COUNTDOWN_TIMER_B_INTERRUPT_GENERATED =   ( 0U << 5U ),   /*!<  No countdown timer B interrupt generated  [ Default ] */
  CONTROL_2_CTBF_CONTDOWN_TIMER_B_INTERRUPT_GENERATED     =   ( 1U << 5U )    /*!<  Flag set when countdown timer B interrupt generated   */
} PCF8523_control_2_ctbf_t;



/* SF <4>: SECOND INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_SF_MASK                                       =   ( 1U << 4U ),   /*!<  SF mask                                               */
  CONTROL_2_SF_NO_SECOND_INTERRUPT_GENERATED              =   ( 0U << 4U ),   /*!<  No second interrupt generated             [ Default ] */
  CONTROL_2_SF_SECOND_INTERRUPT_GENERATED                 =   ( 1U << 4U )    /*!<  Second interrupt generated                            */
} PCF8523_control_2_sf_t;



/* AF <3>: ALARM INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_AF_MASK                                       =   ( 1U << 3U ),   /*!<  AF mask                                               */
  CONTROL_2_AF_NO_SECOND_INTERRUPT_GENERATED              =   ( 0U << 3U ),   /*!<  No alarm interrupt generated              [ Default ] */
  CONTROL_2_AF_SECOND_INTERRUPT_GENERATED                 =   ( 1U << 3U )    /*!<  Alarm interrupt generated                             */
} PCF8523_control_2_af_t;



/* WTAIE <2>: WATCHDOG TIMER A INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_WTAIE_MASK                                    =   ( 1U << 2U ),   /*!<  WTAIE mask                                            */
  CONTROL_2_WTAIE_WTD_TIMER_A_INTERRUPT_DISABLED          =   ( 0U << 2U ),   /*!<  Watchdog timer A interrupt is disabled    [ Default ] */
  CONTROL_2_WTAIE_WTD_TIMER_A_INTERRUPT_ENABLED           =   ( 1U << 2U )    /*!<  Watchdog timer A interrupt is enabled                 */
} PCF8523_control_2_wtaie_t;



/* CTAIE <1>: COUNTDOWN TIMER A INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_CTAIE_MASK                                    =   ( 1U << 1U ),   /*!<  CTAIE mask                                            */
  CONTROL_2_CTAIE_COUNTDOWN_TIMER_A_INTERRUPT_DISABLED    =   ( 0U << 1U ),   /*!<  Countdown timer A interrupt is disabled   [ Default ] */
  CONTROL_2_CTAIE_COUNTDOWN_TIMER_A_INTERRUPT_ENABLED     =   ( 1U << 1U )    /*!<  Countdown timer A interrupt is enabled                */
} PCF8523_control_2_ctaie_t;



/* CTBIE <0>: COUNTDOWN TIMER B INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_2_CTBIE_MASK                                    =   ( 1U << 0U ),   /*!<  CTBIE mask                                            */
  CONTROL_2_CTBIE_COUNTDOWN_TIMER_B_INTERRUPT_DISABLED    =   ( 0U << 0U ),   /*!<  Countdown timer B interrupt is disabled   [ Default ] */
  CONTROL_2_CTBIE_COUNTDOWN_TIMER_B_INTERRUPT_ENABLED     =   ( 1U << 0U )    /*!<  Countdown timer B interrupt is enabled                */
} PCF8523_control_2_ctbie_t;



/**
  * @brief   Register Control_3
  */
/* PM <7:5>: BATTERY SWITCH-OVER AND BATTERY LOW DETECTION CONTROL
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_3_PM_MASK               =   ( 0b111 << 5U ),  /*!<  PM mask                                                                                                                       */
  CONTROL_3_PM_POWER_MODE_0       =   ( 0b000 << 5U ),  /*!<  Battery switch-over function is enabled in standard mode; Battery low detection function is enabled                           */
  CONTROL_3_PM_POWER_MODE_1       =   ( 0b001 << 5U ),  /*!<  Battery switch-over function is enabled in direct switching mode; Battery low detection function is enabled                   */
  CONTROL_3_PM_POWER_MODE_2       =   ( 0b010 << 5U ),  /*!<  Battery switch-over function is disabled - only one power supply (VDD); Battery low detection function is enabled [ Default ] */
  CONTROL_3_PM_POWER_MODE_3       =   ( 0b100 << 5U ),  /*!<  Battery switch-over function is enabled in standard mode; Battery low detection function is disabled                          */
  CONTROL_3_PM_POWER_MODE_4       =   ( 0b101 << 5U ),  /*!<  Battery switch-over function is enabled in direct switching mode; Battery low detection function is disabled                  */
  CONTROL_3_PM_POWER_MODE_5       =   ( 0b111 << 5U ),  /*!<  Battery switch-over function is disabled - only one power supply (VDD); Battery low detection function is disabled            */
} PCF8523_control_3_pm_t;


/* BSF <3>: BATTERY SWITCH-OVER INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_3_BSF_MASK                                        =   ( 1U << 3U ),     /*!<  BSF mask                                                                            */
  CONTROL_3_BSF_NO_BATTERY_SWITCH_OVER_INTERRUPT_GENERATED  =   ( 0U << 3U ),     /*!<  No battery switch-over interrupt generated                              [ Default ] */
  CONTROL_3_BSF_BATTERY_SWITCH_OVER_INTERRUPT_GENERATED     =   ( 1U << 3U )      /*!<  Flag set when battery switch-over occurs                                            */
} PCF8523_control_3_bsf_t;


/* BLF <2>: BATTERY STATUS
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_3_BLF_MASK                                        =   ( 1U << 2U ),     /*!<  BLF mask                                                                           */
  CONTROL_3_BLF_BATTERY_STATUS_OK                           =   ( 0U << 2U ),     /*!<  Battery status ok                                                      [ Default ] */
  CONTROL_3_BLF_BATTERY_STATUS_LOW                          =   ( 1U << 2U )      /*!<  Battery status low                                                                 */
} PCF8523_control_3_blf_t;


/* BSIE <1>: BATTERY SWITCH-OVER INTERRUPT GENERATED
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_3_BSIE_MASK                                       =   ( 1U << 1U ),     /*!<  BSIE mask                                                                           */
  CONTROL_3_BSIE_DISABLE_INTERRUPT                          =   ( 0U << 1U ),     /*!<  No interrupt generated from battery switch-over flag                    [ Default ] */
  CONTROL_3_BSIE_ENABLE_INTERRUPT                           =   ( 1U << 1U )      /*!<  Interrupt generated when BSF is set                                                 */
} PCF8523_control_3_bsie_t;


/* BLIE <0>: BATTERY STATUS
 *    NOTE: N/A.
 */
typedef enum
{
  CONTROL_3_BLIE_MASK                                       =   ( 1U << 0U ),     /*!<  BLIE mask                                                                           */
  CONTROL_3_BLIE_NO_INTERRUPT_GENERATED                     =   ( 0U << 0U ),     /*!<  No interrupt generated from battery low flag                            [ Default ] */
  CONTROL_3_BLIE_INTERRUPT_GENERATED                        =   ( 1U << 0U )      /*!<  Interrupt generated when BLF is set                                                 */
} PCF8523_control_3_blie_t;


/**
  * @brief   Register Seconds
  */
/* OS <7>: OSCILLATOR STOP
 *    NOTE: N/A.
 */
typedef enum
{
  SECONDS_OS_MASK                           =   ( 1U << 7U ),     /*!<  OS mask                                                                                         */
  SECONDS_OS_CLOCK_INTEGRITY_IS_GUARANTEED  =   ( 0U << 7U ),     /*!<  Clock integrity is guaranteed                                                                   */
  SECONDS_OS_CLOCK_INTEGRITY_NOT_GUARANTEED =   ( 1U << 7U )      /*!<  Clock integrity is not guaranteed, oscillator has stopped or has been interrupted  [ Default ]  */
} PCF8523_seconds_os_t;



/* SECONDS, TEN'S PLACE <6:4>: ACTUAL SECONDS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  SECONDS_SECONDS_TEN_PLACE_MASK            =   ( 0b111 << 4U )   /*!<  SECONDS TEN'S PLACE mask                              */
} PCF8523_seconds_ten_place_t;



/* SECONDS, UNIT PLACE <3:0>: ACTUAL SECONDS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  SECONDS_SECONDS_UNIT_PLACE_MASK           =   ( 0b1111 << 0U )  /*!<  SECONDS UNIT PLACE mask                               */
} PCF8523_seconds_unit_place_t;



/**
  * @brief   Register Minutes
  */
/* MINUTES, TEN'S PLACE <6:4>: ACTUAL MINUTES, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  MINUTES_MINUTES_TEN_PLACE_MASK            =   ( 0b111 << 4U )   /*!<  MINUTES TEN'S PLACE mask                              */
} PCF8523_minutes_ten_place_t;



/* MINUTES, UNIT PLACE <3:0>: ACTUAL MINUTES, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  MINUTES_MINUTES_UNIT_PLACE_MASK           =   ( 0b1111 << 0U )  /*!<  MINUTES UNIT PLACE mask                               */
} PCF8523_minutes_unit_place_t;



/**
  * @brief   Register HOURS
  */
/* AMPM <5>: AM/PM INDICATOR
 *    NOTE: ONLY FOR 12-HOUR MODE.
 */
typedef enum
{
  HOURS_AMPM_MASK                           =   ( 1U << 5U ),     /*!<  AMPM mask                                             */
  HOURS_AMPM_AM                             =   ( 0U << 5U ),     /*!<  AMPM: AM mode                                         */
  HOURS_AMPM_PM                             =   ( 1U << 5U )      /*!<  AMPM: PM mode                                         */
} PCF8523_hours_ampm_t;



/* HOURS, TEN'S PLACE <4>: ACTUAL HOURS, TEN'S PLACE
 *    NOTE: ONLY FOR 12-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
  HOURS_12_HOUR_MODE_TEN_PLACE_MASK         =   ( 1U << 4U )      /*!<  Hours TEN'S PLACE mask                                */
} PCF8523_12_hour_mode_ten_place_t;



/* HOURS, TEN'S PLACE <5:4>: ACTUAL HOURS, TEN'S PLACE
 *    NOTE: ONLY FOR 24-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
  HOURS_24_HOUR_MODE_TEN_PLACE_MASK         =   ( 0b11 << 4U )    /*!<  Hours TEN'S PLACE mask                                */
} PCF8523_24_hour_mode_ten_place_t;



/* HOURS, UNIT PLACE <3:0>: ACTUAL HOURS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  HOURS_HOURS_UNIT_PLACE_MASK               =   ( 0b1111 << 0U )  /*!<  HOURS UNIT PLACE mask                                 */
} PCF8523_hours_unit_place_t;



/**
  * @brief   Register Days
  */
/* DAYS, TEN'S PLACE <5:4>: ACTUAL DAYS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  DAYS_DAYS_TEN_PLACE_MASK                  =   ( 0b11 << 4U )    /*!<  DAYS TEN'S PLACE mask                                 */
} PCF8523_days_ten_place_t;



/* DAYS, UNIT PLACE <3:0>: ACTUAL DAYS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  DAYS_DAYS_UNIT_PLACE_MASK                 =   ( 0b1111 << 0U )  /*!<  DAYS UNIT PLACE mask                                  */
} PCF8523_days_unit_place_t;



/**
  * @brief   Register Weekdays
  */
/* WEEKDAYS <2:0>: ACTUAL WEEKDAY
 *    NOTE: N/A.
 */
typedef enum
{
  WEEKDAYS_WEEKDAYS_MASK                    =   ( 0b111 << 0U ),  /*!<  WEEKDAYS mask                                          */
  WEEKDAYS_WEEKDAYS_SUNDAY                  =   ( 0b000 << 0U ),  /*!<  WEEKDAYS Sunday                                        */
  WEEKDAYS_WEEKDAYS_MONDAY                  =   ( 0b001 << 0U ),  /*!<  WEEKDAYS Monday                                        */
  WEEKDAYS_WEEKDAYS_TUESDAY                 =   ( 0b010 << 0U ),  /*!<  WEEKDAYS Tuesday                                       */
  WEEKDAYS_WEEKDAYS_WEDNESDAY               =   ( 0b011 << 0U ),  /*!<  WEEKDAYS Wednesday                                     */
  WEEKDAYS_WEEKDAYS_THURSDAY                =   ( 0b100 << 0U ),  /*!<  WEEKDAYS Thursday                                      */
  WEEKDAYS_WEEKDAYS_FRIDAY                  =   ( 0b101 << 0U ),  /*!<  WEEKDAYS Friday                                        */
  WEEKDAYS_WEEKDAYS_SATURDAY                =   ( 0b110 << 0U )   /*!<  WEEKDAYS Saturday                          [ Default ] */
} PCF8523_weekdays_weekdays_t;



/**
  * @brief   Register Months
  */
/* MONTHS <4:0>: ACTUAL MONTH
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  MONTHS_MONTHS_MASK                        =   ( 0b11111 << 0U ),  /*!<  MONTHS mask                                            */
  MONTHS_MONTHS_JANUARY                     =   ( 0b00001 << 0U ),  /*!<  MONTHS January                             [ Default ] */
  MONTHS_MONTHS_FEBRUARY                    =   ( 0b00010 << 0U ),  /*!<  MONTHS February                                        */
  MONTHS_MONTHS_MARCH                       =   ( 0b00011 << 0U ),  /*!<  MONTHS March                                           */
  MONTHS_MONTHS_APRIL                       =   ( 0b00100 << 0U ),  /*!<  MONTHS April                                           */
  MONTHS_MONTHS_MAY                         =   ( 0b00101 << 0U ),  /*!<  MONTHS May                                             */
  MONTHS_MONTHS_JUNE                        =   ( 0b00110 << 0U ),  /*!<  MONTHS June                                            */
  MONTHS_MONTHS_JULY                        =   ( 0b00111 << 0U ),  /*!<  MONTHS July                                            */
  MONTHS_MONTHS_AUGUST                      =   ( 0b01000 << 0U ),  /*!<  MONTHS August                                          */
  MONTHS_MONTHS_SEPTEMBER                   =   ( 0b01001 << 0U ),  /*!<  MONTHS September                                       */
  MONTHS_MONTHS_OCTOBER                     =   ( 0b10000 << 0U ),  /*!<  MONTHS October                                         */
  MONTHS_MONTHS_NOVEMBER                    =   ( 0b10001 << 0U ),  /*!<  MONTHS November                                        */
  MONTHS_MONTHS_DECEMBER                    =   ( 0b10010 << 0U )   /*!<  MONTHS December                                        */
} PCF8523_months_months_t;



/**
  * @brief   Register Years
  */
/* YEARS, TEN'S PLACE <7:4>: ACTUAL YEARS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  YEARS_YEARS_TEN_PLACE_MASK                =   ( 0b1111 << 4U )   /*!<  YEARS TEN'S PLACE mask                                 */
} PCF8523_years_ten_place_t;



/* YEARS, UNIT PLACE <3:0>: ACTUAL YEARS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  YEARS_YEARS_UNIT_PLACE_MASK               =   ( 0b1111 << 0U )   /*!<  YEARS UNIT PLACE mask                                  */
} PCF8523_years_unit_place_t;



/**
  * @brief   Minute alarm
  */
/* AEN_M <7>: MINUTE ALARM ENABLE/DISABLE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  MINUTE_ALARM_AEN_M_MASK                   =   ( 1U << 7U ),     /*!<  AEN_M mask                                    */
  MINUTE_ALARM_AEN_M_MINUTE_ALARM_ENABLE    =   ( 0U << 7U ),     /*!<  Minute alarm is enabled                       */
  MINUTE_ALARM_AEN_M_MINUTE_ALARM_DISABLE   =   ( 1U << 7U )      /*!<  Minute alarm is disabled          [ Default ] */
} PCF8523_minute_alarm_aen_m_t;


/* MINUTE_ALARM, TEN'S PLACE <6:4>: TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  MINUTE_ALARM_TEN_PLACE_MASK               =   ( 0b1111 << 4U )   /*!<  Minute alarm TEN'S PLACE mask                */
} PCF8523_minute_alarm_ten_place_t;


/* MINUTE_ALARM, UNIT PLACE <3:0>: UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  MINUTE_ALARM_UNIT_PLACE_MASK              =   ( 0b1111 << 0U )   /*!<  Minute alarm UNIT PLACE mask                   */
} PCF8523_minute_alarm_unit_place_t;



/**
  * @brief   Hour alarm
  */
/* AEN_H <7>: HOUR ALARM ENABLE/DISABLE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  HOUR_ALARM_AEN_H_MASK                   =   ( 1U << 7U ),     /*!<  AEN_H mask                                    */
  HOUR_ALARM_AEN_H_MINUTE_ALARM_ENABLE    =   ( 0U << 7U ),     /*!<  Hour alarm is enabled                         */
  HOUR_ALARM_AEN_H_MINUTE_ALARM_DISABLE   =   ( 1U << 7U )      /*!<  Hour alarm is disabled            [ Default ] */
} PCF8523_hour_alarm_aen_h_t;


/* AMPM <5>: INDICATES AM/PM
 *    NOTE: N/A.
 */
typedef enum
{
  HOUR_ALARM_AMPM_MASK                    =   ( 1U << 5U ),     /*!<  AMPM mask                                     */
  HOUR_ALARM_AMPM_AM_MODE                 =   ( 0U << 5U ),     /*!<  AM mode                                       */
  HOUR_ALARM_AMPM_PM_MODE                 =   ( 1U << 5U )      /*!<  PM mode                                       */
} PCF8523_hour_alarm_ampm_t;


/* HOUR_ALARM, TEN'S PLACE <4>: TEN'S PLACE
 *    NOTE: ONLY FOR 12-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
  HOUR_ALARM_12_HOUR_MODE_TEN_PLACE_MASK  =   ( 1U << 4U )      /*!<  HOUR_ALARM 12h TEN'S PLACE mask               */
} PCF8523_12_hour_alarm_mode_ten_place_t;


/* HOUR_ALARM, TEN'S PLACE <5:4>: TEN'S PLACE
 *    NOTE: ONLY FOR 24-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
  HOUR_ALARM_24_HOUR_MODE_TEN_PLACE_MASK  =   ( 0b11 << 4U )    /*!<  HOUR_ALARM 24h TEN'S PLACE mask               */
} PCF8523_24_hour_alarm_mode_ten_place_t;


/* HOUR_ALARM, UNIT PLACE <3:0>: UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  HOUR_ALARM_HOURS_UNIT_PLACE_MASK        =   ( 0b1111 << 0U )  /*!<  HOUR_ALARM UNIT PLACE mask                   */
} PCF8523_hour_alamr_unit_place_t;



/**
  * @brief   Day alarm
  */
/* AEN_D <7>: DAY ALARM ENABLE/DISABLE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  DAY_ALARM_AEN_D_MASK                    =   ( 1U << 7U ),     /*!<  AEN_D mask                                    */
  DAY_ALARM_AEN_D_DAY_ALARM_ENABLE        =   ( 0U << 7U ),     /*!<  Day alarm is enabled                          */
  DAY_ALARM_AEN_D_DAY_ALARM_DISABLE       =   ( 1U << 7U )      /*!<  Day alarm is disabled             [ Default ] */
} PCF8523_day_alarm_aen_d_t;



/**
  * @brief   Weekly alarm
  */
/* AEN_W <7>: WEEKLY ALARM ENABLE/DISABLE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
  WEEKLY_ALARM_AEN_W_MASK                 =   ( 1U << 7U ),     /*!<  AEN_W mask                                    */
  WEEKLY_ALARM_AEN_W_DAY_ALARM_ENABLE     =   ( 0U << 7U ),     /*!<  Weekly alarm is enabled                       */
  WEEKLY_ALARM_AEN_W_DAY_ALARM_DISABLE    =   ( 1U << 7U )      /*!<  Weekly alarm is disabled          [ Default ] */
} PCF8523_weekly_alarm_aen_w_t;



/**
  * @brief   Offset mode
  */
/* MODE <7>: OFFSET MODE
 *    NOTE: N/A.
 */
typedef enum
{
  OFFSET_MODE_MASK                      =   ( 1U << 7U ),     /*!<  MODE mask                                     */
  OFFSET_MODE_ONCE_EVERY_TWO_HOURS      =   ( 0U << 7U ),     /*!<  Offset is made once every two hours[ Default] */
  OFFSET_MODE_ONCE_EVERY_MINUTE         =   ( 1U << 7U )      /*!<  Offset is made once every minute              */
} PCF8523_offset_mode_t;






#ifndef PCF8523_VECTOR_STRUCT_H
#define PCF8523_VECTOR_STRUCT_H
/* Interrupt flags status  */
typedef struct
{
  PCF8523_control_2_wtaf_t  wtaf;                     /*!<  Watchdog timer A interrupt flag                       */
  PCF8523_control_2_ctaf_t  ctaf;                     /*!<  Countdown timer A interrupt flag                      */
  PCF8523_control_2_ctbf_t  ctbf;                     /*!<  Countdown timer B interrupt flag                      */
  PCF8523_control_2_sf_t    sf;                       /*!<  Second interrupt flag                                 */
  PCF8523_control_2_af_t    af;                       /*!<  Alarm interrupt flag                                  */

  PCF8523_control_3_bsf_t   bsf;                      /*!<  Battery switch-over interrupt flag                    */
  PCF8523_control_3_blf_t   blf;                      /*!<  Battery status interrupt flag                         */
} PCF8523_interrupt_flags_status_t;


/* Time ( BCD )  */
typedef struct
{
  uint32_t                  bcd;                      /*!<  Time in BCD format                                    */
  PCF8523_control_1_12_24_t hourMode;                 /*!<  Time mode: 12-hour or 24-hour mode                    */
  PCF8523_hours_ampm_t      timeMode;                 /*!<  AM/PM mode ( only for 12-hour mode )                  */
} PCF8523_time_t;


/* Date  */
typedef struct
{
  uint8_t                      day;                    /*!<  Day in BCD format                                     */
  PCF8523_weekdays_weekdays_t  weekday;                /*!<  Weekday                                               */
  PCF8523_months_months_t      month;                  /*!<  Month  in BCD format                                  */
  uint8_t                      year;                   /*!<  Year in BCD format                                    */
} PCF8523_date_t;


/* Offset  */
typedef struct
{
  PCF8523_offset_mode_t        mode;                   /*!<  Offset mode                                           */
  int8_t                       value;                  /*!<  Offset value: from +63 to -64                         */
} PCF8523_offset_t;



/* USER'S PARAMETERS   */
typedef struct
{
  /* Interrupt flag status   */
  PCF8523_interrupt_flags_status_t  status;           /*!<  Interrupt flag status                                 */
  
  /* Outputs   */
  PCF8523_time_t    time;                             /*!<  Time ( HHMMSS ) in BCD format                         */
  PCF8523_date_t    date;                             /*!<  Date: Day/Weekday/Month/Year                          */
  
  /* Offset  */
  PCF8523_offset_t  offset;                           /*!<  Offset                                                */
  


  PCF8523_seconds_os_t         os;                                 /*!<  Oscillator flag                                       */
} PCF8523_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCF8523_SUCCESS     =       0,
    PCF8523_FAILURE     =       1
} PCF8523_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
PCF8523_status_t  PCF8523_Init                              ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the internal oscillator capacitor selection for quartz crystals with a corresponding load capacitance.
  */
PCF8523_status_t  PCF8523_SetInternallOscilatorCapacitor    ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_cap_sel_t myCAP_SEL                         );

/** It sets the RTC clock mode.
  */
PCF8523_status_t  PCF8523_SetRTCMode                        ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_stop_t mySTOP                               );

/** It performs a software reset.
  */
PCF8523_status_t  PCF8523_SoftwareReset                     ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets 24h/12h mode.
  */
PCF8523_status_t  PCF8523_SetHourMode                       ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_12_24_t my12_24                             );

/** It enables/disables the second interrupt.
  */
PCF8523_status_t  PCF8523_SetSecondInterrupt                ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_sie_t mySIE                                 );

/** It enables/disables the alarm interrupt.
  */
PCF8523_status_t  PCF8523_SetAlarmInterrupt                 ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_aie_t myAIE             );

/** It sets the correction interrupt mode.
  */
PCF8523_status_t  PCF8523_SetCorrectionInterruptMode        ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_cie_t myCIE             );

/** It gets the satus interrupt flags.
  */
PCF8523_status_t  PCF8523_GetStatusInterruptFlags           ( I2C_parameters_t myI2Cparameters, PCF8523_interrupt_flags_status_t* myFlags );

/** It enables/disables the watchdog timer A interrupt.
  */
PCF8523_status_t  PCF8523_SetWatchdogTimerA_Interrupt       ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_wtaie_t myWTAIE         );

/** It enables/disables the countdown timer A interrupt.
  */
PCF8523_status_t  PCF8523_SetCountdownTimerA_Interrupt      ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_ctaie_t myCTAIE         );

/** It enables/disables the countdown timer B interrupt.
  */
PCF8523_status_t  PCF8523_SetCountdownTimerB_Interrupt     ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_ctbie_t myCTBIE          );

/** It enables/disables the battery switch-over interrupt.
  */
PCF8523_status_t  PCF8523_SetBatterySwitchOverInterrupt     ( I2C_parameters_t myI2Cparameters, PCF8523_control_3_bsie_t myBSIE           );

/** It enables/disables the battery low interrupt.
  */
PCF8523_status_t  PCF8523_SetBatteryLowInterrupt            ( I2C_parameters_t myI2Cparameters, PCF8523_control_3_blie_t myBLIE           );

/** It sets the power mode: battery switch-over and battery low detection control.
  */
PCF8523_status_t  PCF8523_SetBatteryPowerModeControl        ( I2C_parameters_t myI2Cparameters, PCF8523_control_3_pm_t myPM               );

/** It gets the time ( BCD format ).
  */
PCF8523_status_t  PCF8523_GetTime                           ( I2C_parameters_t myI2Cparameters, PCF8523_time_t* myActualTime              );

/** It sets the time ( BCD format ).
  */
PCF8523_status_t  PCF8523_SetTime                           ( I2C_parameters_t myI2Cparameters, PCF8523_time_t myNewTime                  );

/** It sets the AM/PM indicator ( only for 12-hour mode ).
  */
PCF8523_status_t  PCF8523_SetAM_PM_Indicator                ( I2C_parameters_t myI2Cparameters, PCF8523_time_t myAM_PM_Indicator          );

/** It gets the AM/PM indicator ( only for 12-hour mode ).
  */
PCF8523_status_t  PCF8523_GetAM_PM_Indicator                ( I2C_parameters_t myI2Cparameters, PCF8523_time_t* myAM_PM_Indicator         );

/** It gets the day ( BCD format ).
  */
PCF8523_status_t  PCF8523_GetDay                            ( I2C_parameters_t myI2Cparameters, uint8_t* myActualDay                      );

/** It sets the day ( BCD format ).
  */
PCF8523_status_t  PCF8523_SetDay                            ( I2C_parameters_t myI2Cparameters, uint8_t myNewDay                          );

/** It gets the weekday.
  */
PCF8523_status_t  PCF8523_GetWeekday                        ( I2C_parameters_t myI2Cparameters, PCF8523_weekdays_weekdays_t* myActualWeekday  );

/** It sets the weekday.
  */
PCF8523_status_t  PCF8523_SetWeekday                        ( I2C_parameters_t myI2Cparameters, PCF8523_weekdays_weekdays_t myNewWeekday      );

/** It gets the month ( BCD format ).
  */
PCF8523_status_t  PCF8523_GetMonth                          ( I2C_parameters_t myI2Cparameters, PCF8523_months_months_t* myActualMonth        );

/** It sets the month ( BCD format ).
  */
PCF8523_status_t  PCF8523_SetMonth                          ( I2C_parameters_t myI2Cparameters, PCF8523_months_months_t myNewMonth            );

/** It gets the year ( BCD format ).
  */
PCF8523_status_t  PCF8523_GetYear                           ( I2C_parameters_t myI2Cparameters, uint8_t* myActualYear                        );

/** It sets the year ( BCD format ).
  */
PCF8523_status_t  PCF8523_SetYear                           ( I2C_parameters_t myI2Cparameters, uint8_t myNewYear                            );

/** It sets the offset.
  */
PCF8523_status_t  PCF8523_SetOffset                         ( I2C_parameters_t myI2Cparameters, PCF8523_offset_t myOFFSET                                   );



///** It enables/disables minute/half minute interrupt.
//  */
//PCF8523_status_t  PCF8523_SetMinuteInterrupts               ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_mi_t myMI, PCF8523_control_2_hmi_t myHMI  );

///** It gets the status of the timer flag.
//  */
//PCF8523_status_t  PCF8523_GetTimerFlag                      ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_tf_t* myTF                                 );

///** It resets the status of the timer flag.
//  */
//PCF8523_status_t  PCF8523_ClearTimerFlag                    ( I2C_parameters_t myI2Cparameters                                                                );



#ifdef __cplusplus
}
#endif

#endif /* PCF8523_H_ */