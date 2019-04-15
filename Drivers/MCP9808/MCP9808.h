/**
 * @brief       MCP9808.h
 * @details     Tiny Real-Time Clock/calendar.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  MCP9808_ADDRESS_0     =   0b0011000,        /*!<   I2C slave address byte: A2A1A0: 000          */
  MCP9808_ADDRESS_1     =   0b0011001,        /*!<   I2C slave address byte: A2A1A0: 001          */
  MCP9808_ADDRESS_2     =   0b0011010,        /*!<   I2C slave address byte: A2A1A0: 010          */
  MCP9808_ADDRESS_3     =   0b0011011,        /*!<   I2C slave address byte: A2A1A0: 011          */
  MCP9808_ADDRESS_4     =   0b0011100,        /*!<   I2C slave address byte: A2A1A0: 100          */
  MCP9808_ADDRESS_5     =   0b0011101,        /*!<   I2C slave address byte: A2A1A0: 101          */
  MCP9808_ADDRESS_6     =   0b0011110,        /*!<   I2C slave address byte: A2A1A0: 110          */
  MCP9808_ADDRESS_7     =   0b0011111         /*!<   I2C slave address byte: A2A1A0: 111          */
} MCP9808_addresses_t;



/**
  * @brief   REGISTERS
  */
typedef enum
{
  MCP9808_CONFIG          =   0x00,           /*!<  CONFIG register                               */
  MCP9808_TUPPER          =   0x02,           /*!<  T_UPPER register                              */
  MCP9808_TLOWER          =   0x03,           /*!<  T_LOWER register                              */
  MCP9808_TCRIT           =   0x04,           /*!<  T_CRIT register                               */
  MCP9808_TA              =   0x05,           /*!<  T_A register                                  */
  MCP9808_MANUFACTURER_ID =   0x06,           /*!<  Manufacturer ID register                      */
  MCP9808_DEVICE_ID       =   0x07,           /*!<  Device ID/Revision register                   */
  MCP9808_RESOLUTION      =   0x08            /*!<  Resolution register                           */
} MCP9808_registers_t;



/**
  * @brief   CONFIG Register
  */
/* T_HYST <9:10>: TUPPER AND TLOWER LIMIT HYSTERESIS BITS
 *    NOTE:
 *      � This bit can not be altered when either of the Lock bits are set ( bit 6 and bit 7 )
 *      � This bit can be programmed in Shutdown mode
 */
typedef enum
{
    CONFIG_T_HYST_MASK                =   ( 0b11 << 9U ),   /*!<  T_HYST mask                                     */
    CONFIG_T_HYST_0_C                 =   ( 0b00 << 9U ),   /*!<  T_HYST: 0C                          [ Default ] */
    CONFIG_T_HYST_1_5_C               =   ( 0b01 << 9U ),   /*!<  T_HYST: +1.5C                                   */
    CONFIG_T_HYST_3_0_C               =   ( 0b10 << 9U ),   /*!<  T_HYST: +3.0C                                   */
    CONFIG_T_HYST_6_0_C               =   ( 0b11 << 9U ),   /*!<  T_HYST: +6.0C                                   */
} MCP9808_config_thyst_t;



/* SHDN <8>: SHUTDOWN MODE BIT
 *    NOTE: 
 *      � This bit can not be set to '1' when either of the Lock bits are set ( bit 6 and bit 7 ), however,
 *        it can be cleared to '0' for continuous conversion while locked.
 */
typedef enum
{
    CONFIG_SHDN_MASK                  =   ( 1U << 8U ),     /*!<  SHDN mask                                       */
    CONFIG_SHDN_CONTINUOUS_CONVERSION =   ( 0U << 8U ),     /*!<  SHDN: Continuous conversion         [ Default ] */
    CONFIG_SHDN_SHUTDOWN              =   ( 1U << 8U )      /*!<  SHDN: Shutdown ( Low-power mode )               */
} MCP9808_config_shdn_t;



/* CRIT_LOCK <7>: T_CRIT LOCKED BIT
 *    NOTE: N/A.
 */
typedef enum
{
    CONFIG_CRIT_LOCK_MASK             =   ( 1U << 7U ),     /*!<  CRIT_LOCK mask                                  */
    CONFIG_CRIT_LOCK_UNLOCKED         =   ( 0U << 7U ),     /*!<  T_CRIT register can be written      [ Default ] */
    CONFIG_CRIT_LOCK_LOCKED           =   ( 1U << 7U )      /*!<  T_CRIT register can not be written              */
} MCP9808_config_crit_lock_t;



/* WIN_LOCK <6>: CORRECTION INTERRUPT ENABLE 
 *    NOTE: N/A.
 */
typedef enum
{
    CONFIG_WIN_LOCK_MASK              =   ( 1U << 6U ),     /*!<  WIN_LOCK mask                                   */
    CONFIG_WIN_LOCK_UNLOCKED          =   ( 0U << 6U ),     /*!<  TUPPER and TLOWER can be written    [ Default ] */
    CONFIG_WIN_LOCK_LOCKED            =   ( 1U << 6U )      /*!<  TUPPER and TLOWER can not be written            */
} MCP9808_config_win_lock_t;



/* INT_CLEAR <5>: INTERRUPT CLEAR BIT 
 *    NOTE: 
 *      � This bit can not be set to '1' in Shutdown mode, but it can be cleared after the device enters Shutdown mode
 */
typedef enum
{
    CONFIG_INT_CLEAR_MASK              =   ( 1U << 5U ),     /*!<  INT_CLEAR mask                                 */
    CONFIG_INT_CLEAR_NO_EFFECT         =   ( 0U << 5U ),     /*!<  No effect                          [ Default ] */
    CONFIG_INT_CLEAR_CLEAR_INT_OUTPUT  =   ( 1U << 5U )      /*!<  Clear interrupt output, when read, returns '0' */
} MCP9808_conf_int_clear_t;



/* HOLAHOLAHOLAHOLAHOLACAP_SEL <0>: INTERNAL OSCILLATOR CAPACITOR SELECTION 
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_1_CAP_SEL_MASK                      =   ( 1U << 0U ),     /*!<  CAP_SEL mask                                    */
    CONTROL_1_CAP_SEL_7_PF                      =   ( 0U << 0U ),     /*!<  CAP_SEL: 7 pF                       [ Default ] */
    CONTROL_1_CAP_SEL_12_5_PF                   =   ( 1U << 0U )      /*!<  CAP_SEL: 12.5 pF                                */
} MCP9808_control_1_cap_sel_t;



/**
  * @brief   Register Control_2
  */
/* MI <5>: MINUTE INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_MI_MASK                           =   ( 1U << 5U ),     /*!<  MI mask                                         */
    CONTROL_2_MI_MINUTE_INTERRUPT_DISABLED      =   ( 0U << 5U ),     /*!<  Minute interrupt disabled           [ Default ] */
    CONTROL_2_MI_MINUTE_INTERRUPT_ENABLED       =   ( 1U << 5U )      /*!<  Minute interrupt enabled                        */
} MCP9808_control_2_mi_t;



/* HMI <4>: HALF MINUTE INTERRUPT
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_HMI_MASK                            =   ( 1U << 4U ),   /*!<  HMI mask                                        */
    CONTROL_2_HMI_HALF_MINUTE_INTERRUPT_DISABLED  =   ( 0U << 4U ),   /*!<  Half Minute interrupt disabled      [ Default ] */
    CONTROL_2_HMI_HALF_MINUTE_INTERRUPT_ENABLED   =   ( 1U << 4U )    /*!<  Half Minute interrupt enabled                   */
} MCP9808_control_2_hmi_t;



/* TF <3>: TIMER FLAG
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_TF_MASK                           =   ( 1U << 3U ),     /*!<  TF mask                                         */
    CONTROL_2_TF_TIMER_INTERRUPT_NOT_GENERATED  =   ( 0U << 3U ),     /*!<  No Timer interrupt generated        [ Default ] */
    CONTROL_2_TF_TIMER_INTERRUPT_GENERATED      =   ( 1U << 3U )      /*!<  Timer interrupt generated                       */
} MCP9808_control_2_tf_t;



/* COF <2:0>: CLKOUT CONTROL
 *    NOTE: N/A.
 */
typedef enum
{
    CONTROL_2_COF_MASK                          =   ( 0b111 << 0U ),  /*!<  COF mask                                        */
    CONTROL_2_COF_CLKOUT_32768_HZ               =   ( 0b000 << 0U ),  /*!<  CLKOUT: 32768 Hz                    [ Default ] */
    CONTROL_2_COF_CLKOUT_16384_HZ               =   ( 0b001 << 0U ),  /*!<  CLKOUT: 16384 Hz                                */
    CONTROL_2_COF_CLKOUT_8192_HZ                =   ( 0b010 << 0U ),  /*!<  CLKOUT: 8192  Hz                                */
    CONTROL_2_COF_CLKOUT_4096_HZ                =   ( 0b011 << 0U ),  /*!<  CLKOUT: 4096  Hz                                */
    CONTROL_2_COF_CLKOUT_2048_HZ                =   ( 0b100 << 0U ),  /*!<  CLKOUT: 2048  Hz                                */
    CONTROL_2_COF_CLKOUT_1024_HZ                =   ( 0b101 << 0U ),  /*!<  CLKOUT: 1024  Hz                                */
    CONTROL_2_COF_CLKOUT_1_HZ                   =   ( 0b110 << 0U ),  /*!<  CLKOUT: 1     Hz                                */
    CONTROL_2_COF_CLKOUT_LOW                    =   ( 0b111 << 0U )   /*!<  CLKOUT: LOW                                     */
} MCP9808_control_2_cof_t;



/**
  * @brief   Register Offset
  */
/* MODE <7>: OFFSET MODE
 *    NOTE: N/A.
 */
typedef enum
{
    OFFSET_MODE_MASK                            =   ( 1U << 7U ),     /*!<  MODE mask                                                   */
    OFFSET_MODE_NORMAL_MODE                     =   ( 0U << 7U ),     /*!<  Normal mode: offset is made once every two hours[ Default ] */
    OFFSET_MODE_COURSE_MODE                     =   ( 1U << 7U )      /*!<  Course mode: offset is made every 4 minutes                 */
} MCP9808_offset_mode_t;



/**
  * @brief   Register RAM_byte
  */
/* B <7:0>: RAM CONTENT
 *    NOTE: N/A.
 */
typedef enum
{
    RAM_BYTE_B_MASK                             =   0xFF              /*!<  RAM_byte mask                                     */
} MCP9808_ram_byte_b_t;



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
} MCP9808_seconds_os_t;



/* SECONDS, TEN'S PLACE <6:4>: ACTUAL SECONDS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    SECONDS_SECONDS_TEN_PLACE_MASK            =   ( 0b111 << 4U )   /*!<  SECONDS TEN'S PLACE mask                              */
} MCP9808_seconds_ten_place_t;



/* SECONDS, UNIT PLACE <3:0>: ACTUAL SECONDS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    SECONDS_SECONDS_UNIT_PLACE_MASK           =   ( 0b1111 << 0U )  /*!<  SECONDS UNIT PLACE mask                               */
} MCP9808_seconds_unit_place_t;



/**
  * @brief   Register Minutes
  */
/* MINUTES, TEN'S PLACE <6:4>: ACTUAL MINUTES, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    MINUTES_MINUTES_TEN_PLACE_MASK            =   ( 0b111 << 4U )   /*!<  MINUTES TEN'S PLACE mask                              */
} MCP9808_minutes_ten_place_t;



/* MINUTES, UNIT PLACE <3:0>: ACTUAL MINUTES, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    MINUTES_MINUTES_UNIT_PLACE_MASK           =   ( 0b1111 << 0U )  /*!<  MINUTES UNIT PLACE mask                               */
} MCP9808_minutes_unit_place_t;



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
} MCP9808_hours_ampm_t;



/* HOURS, TEN'S PLACE <4>: ACTUAL HOURS, TEN'S PLACE
 *    NOTE: ONLY FOR 12-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
    HOURS_12_HOUR_MODE_TEN_PLACE_MASK         =   ( 1U << 4U )      /*!<  Hours TEN'S PLACE mask                                */
} MCP9808_12_hour_mode_ten_place_t;



/* HOURS, TEN'S PLACE <5:4>: ACTUAL HOURS, TEN'S PLACE
 *    NOTE: ONLY FOR 24-HOUR MODE, CODED IN BCD FORMAT.
 */
typedef enum
{
    HOURS_24_HOUR_MODE_TEN_PLACE_MASK         =   ( 0b11 << 4U )    /*!<  Hours TEN'S PLACE mask                                */
} MCP9808_24_hour_mode_ten_place_t;



/* HOURS, UNIT PLACE <3:0>: ACTUAL HOURS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    HOURS_HOURS_UNIT_PLACE_MASK               =   ( 0b1111 << 0U )  /*!<  HOURS UNIT PLACE mask                                 */
} MCP9808_hours_unit_place_t;



/**
  * @brief   Register Days
  */
/* DAYS, TEN'S PLACE <5:4>: ACTUAL DAYS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    DAYS_DAYS_TEN_PLACE_MASK                  =   ( 0b11 << 4U )    /*!<  DAYS TEN'S PLACE mask                                 */
} MCP9808_days_ten_place_t;



/* DAYS, UNIT PLACE <3:0>: ACTUAL DAYS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    DAYS_DAYS_UNIT_PLACE_MASK                 =   ( 0b1111 << 0U )  /*!<  DAYS UNIT PLACE mask                                  */
} MCP9808_days_unit_place_t;



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
    WEEKDAYS_WEEKDAYS_SATURDAY                =   ( 0b111 << 0U )   /*!<  WEEKDAYS Saturday                          [ Default ] */
} MCP9808_weekdays_weekdays_t;



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
} MCP9808_months_months_t;



/**
  * @brief   Register Years
  */
/* YEARS, TEN'S PLACE <7:4>: ACTUAL YEARS, TEN'S PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    YEARS_YEARS_TEN_PLACE_MASK                =   ( 0b1111 << 4U )   /*!<  YEARS TEN'S PLACE mask                                 */
} MCP9808_years_ten_place_t;



/* YEARS, UNIT PLACE <3:0>: ACTUAL YEARS, UNIT PLACE
 *    NOTE: CODED IN BCD FORMAT.
 */
typedef enum
{
    YEARS_YEARS_UNIT_PLACE_MASK               =   ( 0b1111 << 0U )   /*!<  YEARS UNIT PLACE mask                                  */
} MCP9808_years_unit_place_t;





#ifndef MCP9808_VECTOR_STRUCT_H
#define MCP9808_VECTOR_STRUCT_H
typedef struct
{
    MCP9808_control_1_12_24_t    Time12H_24HMode;                    /*!<  Time mode: 12-hour or 24-hour mode                    */
    MCP9808_hours_ampm_t         TimeAM_PM_Mode;                     /*!<  AM/PM mode ( only for 12-hour mode )                  */

    uint32_t                      BCDtime;                            /*!<  Time ( HHMMSS ) in BCD format                         */
    uint8_t                       BCDday;                             /*!<  Day number in BCD format                              */
    MCP9808_weekdays_weekdays_t  weekday;                            /*!<  Weekday                                               */
    MCP9808_months_months_t      BCDmonth;                           /*!<  Month  in BCD format                                  */
    uint8_t                       BCDyear;                            /*!<  Year in BCD format                                    */

    int8_t                        ramByte;                            /*!<  RAM byte                                              */
    MCP9808_seconds_os_t         os;                                 /*!<  Oscillator flag                                       */
} MCP9808_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    MCP9808_SUCCESS     =       0,
    MCP9808_FAILURE     =       1
} MCP9808_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
MCP9808_status_t  MCP9808_Init                              ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the external clock test mode.
  */
MCP9808_status_t  MCP9808_SetTestMode                       ( I2C_parameters_t myI2Cparameters, MCP9808_control_1_ext_test_t myEXT_TEST                      );

/** It sets the RTC clock mode.
  */
MCP9808_status_t  MCP9808_SetRTCMode                        ( I2C_parameters_t myI2Cparameters, MCP9808_control_1_stop_t mySTOP                              );

/** It performs a software reset.
  */
MCP9808_status_t  MCP9808_SoftwareReset                     ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the correction interrupt mode.
  */
MCP9808_status_t  MCP9808_SetCorrectionInterruptMode        ( I2C_parameters_t myI2Cparameters, MCP9808_control_1_cie_t myCIE                                );

/** It sets 12 or 24 hour mode.
  */
MCP9808_status_t  MCP9808_Set12_24_HourMode                 ( I2C_parameters_t myI2Cparameters, MCP9808_data_t my12_24                                       );

/** It sets the internal oscillator capacitor.
  */
MCP9808_status_t  MCP9808_SetInternalOscillatorCapacitor    ( I2C_parameters_t myI2Cparameters, MCP9808_control_1_cap_sel_t myCAP_SEL                        );

/** It enables/disables minute/half minute interrupt.
  */
MCP9808_status_t  MCP9808_SetMinuteInterrupts               ( I2C_parameters_t myI2Cparameters, MCP9808_control_2_mi_t myMI, MCP9808_control_2_hmi_t myHMI  );

/** It gets the status of the timer flag.
  */
MCP9808_status_t  MCP9808_GetTimerFlag                      ( I2C_parameters_t myI2Cparameters, MCP9808_control_2_tf_t* myTF                                 );

/** It resets the status of the timer flag.
  */
MCP9808_status_t  MCP9808_ClearTimerFlag                    ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the clock output frequency.
  */
MCP9808_status_t  MCP9808_SetClockOutputFrequency           ( I2C_parameters_t myI2Cparameters, MCP9808_control_2_cof_t myCOF                                );

/** It sets the offset.
  */
MCP9808_status_t  MCP9808_SetOffset                         ( I2C_parameters_t myI2Cparameters, MCP9808_offset_mode_t myMODE, int8_t myOFFSET                );

/** It writes into the RAM byte register.
  */
MCP9808_status_t  MCP9808_WriteByteRAM                      ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myData                                        );

/** It reads the RAM byte register.
  */
MCP9808_status_t  MCP9808_ReadByteRAM                       ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myData                                       );

/** It checks oscillator clock integrity flag.
  */
MCP9808_status_t  MCP9808_CheckOscillatorClockIntegrityFlag ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myOS                                         );

/** It clears oscillator clock integrity flag.
  */
MCP9808_status_t  MCP9808_ClearOscillatorClockIntegrityFlag ( I2C_parameters_t myI2Cparameters                                                                );

/** It sets the AM/PM indicator ( only for 12-hour mode ).
  */
MCP9808_status_t  MCP9808_SetAM_PM_Indicator                ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myAM_PM_Indicator                             );

/** It gets the AM/PM indicator ( only for 12-hour mode ).
  */
MCP9808_status_t  MCP9808_GetAM_PM_Indicator                ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myAM_PM_Indicator                            );

/** It gets the day ( BCD format ).
  */
MCP9808_status_t  MCP9808_GetDay                            ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myActualDay                                  );

/** It sets the day ( BCD format ).
  */
MCP9808_status_t  MCP9808_SetDay                            ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myNewDay                                      );

/** It gets the weekday.
  */
MCP9808_status_t  MCP9808_GetWeekday                        ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myActualWeekday                              );

/** It sets the weekday.
  */
MCP9808_status_t  MCP9808_SetWeekday                        ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myNewWeekday                                  );

/** It gets the month ( BCD format ).
  */
MCP9808_status_t  MCP9808_GetMonth                          ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myActualMonth                                );

/** It sets the month ( BCD format ).
  */
MCP9808_status_t  MCP9808_SetMonth                          ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myNewMonth                                    );

/** It gets the time ( BCD format ).
  */
MCP9808_status_t  MCP9808_GetTime                           ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myActualTime                                 );

/** It sets the time ( BCD format ).
  */
MCP9808_status_t  MCP9808_SetTime                           ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myNewTime                                     );

/** It gets the year ( BCD format ).
  */
MCP9808_status_t  MCP9808_GetYear                           ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myActualYear                                 );

/** It sets the year ( BCD format ).
  */
MCP9808_status_t  MCP9808_SetYear                           ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myNewYear                                     );
