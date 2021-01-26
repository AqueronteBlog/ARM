/**
 * @brief       SHT3X.h
 * @details     Humidity and Temperature Sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "i2c.h"


#ifndef SHT3X_H_
#define SHT3X_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  SHT3X_ADDRESS_A     =   0x44,             /*!<   SHT3X ADDR pin connected to logic low   */
  SHT3X_ADDRESS_B     =   0x45              /*!<   SHT3X ADDR pin connected to logic high  */
} SHT3X_address_t;



/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
  SHT3X_CLOCK_STRETCHING_ENABLED_REPEATABILITY_HIGH     = 0x2C06,   /*!<  High repeatability measurement with clock stretching enabled    */
  SHT3X_CLOCK_STRETCHING_ENABLED_REPEATABILITY_MEDIUM   = 0x2C0D,   /*!<  Medium repeatability measurement with clock stretching enabled  */
  SHT3X_CLOCK_STRETCHING_ENABLED_REPEATABILITY_LOW      = 0x2C10,   /*!<  Low repeatability measurement with clock stretching enabled     */
    
  SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_HIGH    = 0x2400,   /*!<  High repeatability measurement with clock stretching disabled   */
  SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_MEDIUM  = 0x240B,   /*!<  Medium repeatability measurement with clock stretching disabled */
  SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_LOW     = 0x2416,   /*!<  Low repeatability measurement with clock stretching disabled    */

  SHT3X_MPS_0_5_REPEATABILITY_HIGH                      = 0x2032,   /*!<  High repeatability 0.5 measurement per second                   */
  SHT3X_MPS_0_5_REPEATABILITY_MEDIUM                    = 0x2024,   /*!<  Medium repeatability 0.5 measurement per second                 */
  SHT3X_MPS_0_5_REPEATABILITY_LOW                       = 0x202F,   /*!<  Low repeatability 0.5 measurement per second                    */
    
  SHT3X_MPS_1_REPEATABILITY_HIGH                        = 0x2130,   /*!<  High repeatability 1 measurement per second                     */
  SHT3X_MPS_1_REPEATABILITY_MEDIUM                      = 0x2126,   /*!<  Medium repeatability 1 measurement per second                   */
  SHT3X_MPS_1_REPEATABILITY_LOW                         = 0x212D,   /*!<  Low repeatability 1 measurement per second                      */
    
  SHT3X_MPS_2_REPEATABILITY_HIGH                        = 0x2236,   /*!<  High repeatability 2 measurement per second                     */
  SHT3X_MPS_2_REPEATABILITY_MEDIUM                      = 0x2220,   /*!<  Medium repeatability 2 measurement per second                   */
  SHT3X_MPS_2_REPEATABILITY_LOW                         = 0x222B,   /*!<  Low repeatability 2 measurement per second                      */
    
  SHT3X_MPS_4_REPEATABILITY_HIGH                        = 0x2334,   /*!<  High repeatability 4 measurement per second                     */
  SHT3X_MPS_4_REPEATABILITY_MEDIUM                      = 0x2322,   /*!<  Medium repeatability 4 measurement per second                   */
  SHT3X_MPS_4_REPEATABILITY_LOW                         = 0x2329,   /*!<  Low repeatability 4 measurement per second                      */
    
  SHT3X_MPS_10_REPEATABILITY_HIGH                       = 0x2737,   /*!<  High repeatability 10 measurement per second                    */
  SHT3X_MPS_10_REPEATABILITY_MEDIUM                     = 0x2721,   /*!<  Medium repeatability 10 measurement per second                  */
  SHT3X_MPS_10_REPEATABILITY_LOW                        = 0x272A,   /*!<  Low repeatability 10 measurement per second                     */

  SHT3X_FETCH_DATA                                      = 0xE000,   /*!<  Fetch data command                                              */
  SHT3X_PERIODIC_MESUREMENT_WITH_ART                    = 0x2B32,   /*!<  ART command                                                     */
  SHT3X_BREAK                                           = 0x3093,   /*!<  Break command                                                   */
  SHT3X_SOFT_RESET                                      = 0x30A2,   /*!<  Software reset command                                          */
  SHT3X_HEATER_ENABLE                                   = 0x306D,   /*!<  Heater enable command                                           */
  SHT3X_HEATER_DISABLE                                  = 0x3066,   /*!<  Heater disable command                                          */
  SHT3X_STATUS_REGISTER                                 = 0xF32D,   /*!<  Status command                                                  */
  SHT3X_CLEAR_STATUS_REGISTER                           = 0x3041    /*!<  Clear Status register command                                   */
} SHT3X_command_registers_t;



// GENERAL CALL
/**
  * @brief   RESET
  */
typedef enum
{
  SHT3X_GENERAL_CALL_RESET_ADDRESS_BYTE = 0x00,     /*!<  Reset. Address byte                                   */
  SHT3X_GENERAL_CALL_RESET_SECOND_BYTE  = 0x06      /*!<  Reset. Second byte                                    */
} SHT3X_general_call_t;



/**
 * @brief   STATUS REGISTER. 
 *           NOTE: N/A.
 */
/* ALERT_PENDING_STATUS <15>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_ALERT_PENDING_STATUS_MASK                        =   ( 1U << 15U ),    /*!<  ALERT_PENDING_STATUS mask                            */
  STATUS_ALERT_PENDING_STATUS_NO_PENDING_ALERTS           =   ( 0U << 15U ),    /*!<  No pending alerts                                    */
  STATUS_ALERT_PENDING_STATUS_AT_LEAST_ONE_PENDING_ALERT  =   ( 1U << 15U )     /*!<  At least one pending alert                 [Default] */
} SHT3X_status_alert_pending_status_t;


/* HEATER_STATUS <13>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_HEATER_STATUS_MASK                               =   ( 1U << 13U ),    /*!<  HEATER_STATUS mask                                   */
  STATUS_HEATER_OFF                                       =   ( 0U << 13U ),    /*!<  Heater off                                 [Default] */
  STATUS_HEATER_ON                                        =   ( 1U << 13U )     /*!<  Heater on                                            */
} SHT3X_status_heater_status_t;


/* RH_TRACKING_ALERT <11>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_RH_TRACKING_ALERT_MASK                           =   ( 1U << 11U ),    /*!<  RH_TRACKING_ALERT mask                               */
  STATUS_RH_TRACKING_ALERT_NO_ALERT                       =   ( 0U << 11U ),    /*!<  No alert                                   [Default] */
  STATUS_RH_TRACKING_ALERT_ALERT                          =   ( 1U << 11U )     /*!<  Alert                                                */
} SHT3X_status_rh_tracking_alert_t;


/* T_TRACKING_ALERT <10>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_T_TRACKING_ALERT_MASK                            =   ( 1U << 10U ),    /*!<  T_TRACKING_ALERT mask                                */
  STATUS_T_TRACKING_ALERT_NO_ALERT                        =   ( 0U << 10U ),    /*!<  No alert                                   [Default] */
  STATUS_T_TRACKING_ALERT_ALERT                           =   ( 1U << 10U )     /*!<  Alert                                                */
} SHT3X_status_t_tracking_alert_t;


/* SYSTEM_RESET_DETECTED <4>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_SYSTEM_RESET_DETECTED_MASK                       =   ( 1U << 4U ),     /*!<  SYSTEM_RESET_DETECTED mask                                              */
  STATUS_SYSTEM_RESET_DETECTED_NO_RESET_DETECTED          =   ( 0U << 4U ),     /*!<  No reset detected since last 'clear status register' command            */
  STATUS_SYSTEM_RESET_DETECTED_RESET_DETECTED             =   ( 1U << 4U )      /*!<  Reset detected (hard reset, soft reset command or supply fail)[Default] */
} SHT3X_status_system_reset_detected_t;


/* COMMAND_STATUS <1>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_COMMAND_STATUS_MASK                              =   ( 1U << 10U ),    /*!<  COMMAND_STATUS mask                                  */
  STATUS_COMMAND_STATUS_COMMAND_EXECUTED_SUCCESSFULLY     =   ( 0U << 10U ),    /*!<  Last command executed successfully         [Default] */
  STATUS_COMMAND_STATUS_LAST_COMMAND_NOT_PROCESSED        =   ( 1U << 10U )     /*!<  Last command not processed                           */
} SHT3X_status_command_status_t;


/* WRITE_DATA_CHECKSUM_STATUS <0>
 *    NOTE: N/A.
 */
typedef enum
{
  STATUS_WRITE_DATA_CHECKSUM_STATUS_MASK                  =   ( 1U << 0U ),     /*!<  COMMAND_STATUS mask                                  */
  STATUS_WRITE_DATA_CHECKSUM_STATUS_CHECKSUM_CORRECT      =   ( 0U << 0U ),     /*!<  Checksum of last write transfer was correct[Default] */
  STATUS_WRITE_DATA_CHECKSUM_STATUS_CHECKSUM_FAILED       =   ( 1U << 0U )      /*!<  Checksum of last write transfer failed               */
} SHT3X_status_write_data_checksum_status_t;





#ifndef SHT3X_VECTOR_STRUCT_H
#define SHT3X_VECTOR_STRUCT_H
typedef struct
{
    float    RelativeHumidity;
    float    Temperature;

    uint16_t RawRelativeHumidity;
    uint16_t RawTemperature;

    uint8_t  BatteryStatus;
    uint64_t SerialNumber;
} SHT3X_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SHT3X_SUCCESS     =       0,
    SHT3X_FAILURE     =       1
} SHT3X_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SHT3X_status_t  SHT3X_Init               ( I2C_parameters_t myI2Cparameters                                                                                 );



#ifdef __cplusplus
}
#endif

#endif /* SHT3X_H */
