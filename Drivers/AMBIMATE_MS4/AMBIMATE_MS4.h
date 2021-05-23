/**
 * @brief       AMBIMATE_MS4.h
 * @details     AmbiMate Sensor Module.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#ifndef AMBIMATE_MS4_H_
#define AMBIMATE_MS4_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "i2c.h"



/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  AMBIMATE_MS4_ADDRESS     =   0x2A                 /*!<   AMBIMATE_MS4 ADDR                    */
} AMBIMATE_MS4_address_t;



/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
  AMBIMATE_MS4_STATUS_HIGH_BYTE             =   0x00,   /*!<  Status register                       */
  AMBIMATE_MS4_TEMPERATURE_HIGH_BYTE        =   0x01,   /*!<  Temperature register. High byte       */
  AMBIMATE_MS4_TEMPERATURE_LOW_BYTE         =   0x02,   /*!<  Temperature register. Low byte        */
  AMBIMATE_MS4_HUMIDITY_HIGH_BYTE           =   0x03,   /*!<  Humidity register. High byte          */
  AMBIMATE_MS4_HUMIDITY_LOW_BYTE            =   0x04,   /*!<  Humidity register. Low byte           */
  AMBIMATE_MS4_LIGHT_HIGH_BYTE              =   0x05,   /*!<  Light register. High byte             */
  AMBIMATE_MS4_LIGHT_LOW_BYTE               =   0x06,   /*!<  Light register. Low byte              */
  AMBIMATE_MS4_AUDIO_HIGH_BYTE              =   0x07,   /*!<  Audio register. High byte             */
  AMBIMATE_MS4_AUDIO_LOW_BYTE               =   0x08,   /*!<  Audio register. Low byte              */
  AMBIMATE_MS4_BATTERY_VOLTS_HIGH_BYTE      =   0x09,   /*!<  Battery voltage register. High byte   */
  AMBIMATE_MS4_BATTERY_VOLTS_LOW_BYTE       =   0x0A,   /*!<  Battery voltage register. Low byte    */
  AMBIMATE_MS4_ECO2_HIGH_BYTE               =   0x0B,   /*!<  eCO2 register. High byte              */
  AMBIMATE_MS4_ECO2_LOW_BYTE                =   0x0C,   /*!<  eCO2 register. Low byte               */
  AMBIMATE_MS4_VOC_HIGH_BYTE                =   0x0D,   /*!<  VOC register. High byte               */
  AMBIMATE_MS4_VOC_LOW_BYTE                 =   0x0E    /*!<  VOC register. Low byte                */
} AMBIMATE_MS4_sensor_data_registers_t;


typedef enum
{
  AMBIMATE_MS4_8BIT_STATUS_HIGH_BYTE        =   0x40,   /*!<  Status register                       */
  AMBIMATE_MS4_8BIT_TEMPERATURE_HIGH_BYTE   =   0x41,   /*!<  Temperature register. High byte       */
  AMBIMATE_MS4_8BIT_HUMIDITY_HIGH_BYTE      =   0x42,   /*!<  Humidity register. High byte          */
  AMBIMATE_MS4_8BIT_LIGHT_HIGH_BYTE         =   0x43,   /*!<  Light register. High byte             */
  AMBIMATE_MS4_8BIT_AUDIO_HIGH_BYTE         =   0x44,   /*!<  Audio register. High byte             */
  AMBIMATE_MS4_8BIT_BATTERY_VOLTS_HIGH_BYTE =   0x45,   /*!<  Battery voltage register. High byte   */
  AMBIMATE_MS4_8BIT_ECO2_HIGH_BYTE          =   0x46,   /*!<  eCO2 register. High byte              */
  AMBIMATE_MS4_8BIT_VOC_HIGH_BYTE           =   0x47    /*!<  VOC register. High byte               */
} AMBIMATE_MS4_8bit_sensor_data_registers_t;


typedef enum
{
  AMBIMATE_MS4_FIRMWARE_VERSION             =   0x80,   /*!<  Firmware version                      */
  AMBIMATE_MS4_FIRMWARE_SUB_VERSION         =   0x81,   /*!<  Firmware sub-version                  */
  AMBIMATE_MS4_OPTIONAL_SENSORS             =   0x82    /*!<  Optional sensors                      */
} AMBIMATE_MS4_other_registers_t;


typedef enum
{
  AMBIMATE_MS4_SCAN_START_BYTE              =   0xC0,   /*!<  Scan start byte                       */
  AMBIMATE_MS4_AUDIO_EVENT_LEVEL            =   0xC1,   /*!<  Audio level event                     */
  AMBIMATE_MS4_PROCESSOR_RESET              =   0xF0    /*!<  Initiates a processor reset           */
} AMBIMATE_MS4_writable_registers_t;




/**
  * @brief   OPTIONAL SENSORS BYTE REGISTER.
  *           NOTE: N/A.
  */
/* CO2 <0>
 *    NOTE: N/A.
 */
typedef enum
{
    OPTIONAL_SENSORS_BYTE_CO2_MASK                  =   ( 1U << 0U ),   /*!<  CO2 mask                                                        */
    OPTIONAL_SENSORS_BYTE_CO2_SENSOR_NOT_INSTALLED  =   ( 0U << 0U ),   /*!<  CO2 sensor is not installed                                     */
    OPTIONAL_SENSORS_BYTE_CO2_SENSOR_INSTALLED      =   ( 1U << 0U )    /*!<  CO2 sensor is installed                                         */
} AMBIMATE_MS4_optional_sensors_byte_co2_t;


/* MIC <2>
 *    NOTE: N/A.
 */
typedef enum
{
    OPTIONAL_SENSORS_BYTE_MIC_MASK                  =   ( 1U << 2U ),   /*!<  MIC mask                                                        */
    OPTIONAL_SENSORS_BYTE_MIC_SENSOR_NOT_INSTALLED  =   ( 0U << 2U ),   /*!<  MIC sensor is not installed                                     */
    OPTIONAL_SENSORS_BYTE_MIC_SENSOR_INSTALLED      =   ( 1U << 2U )    /*!<  MIC sensor is installed                                         */
} AMBIMATE_MS4_optional_sensors_byte_mic_t;



/**
  * @brief   WRITEABLE REGISTERS.
  *           NOTE: N/A.
  */
/* GAS <6>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_GAS_MASK                        =   ( 1U << 6U ),   /*!<  GAS mask                                                        */
    WRITEABLE_REGISTERS_GAS_MEASUREMENT_COMPLETED       =   ( 0U << 6U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_GAS_INITIATE_NEW_MEASUREMENT    =   ( 1U << 6U )    /*!<  Initiates a measurement of the VOC sensor if installed          */
} AMBIMATE_MS4_writeable_reg_gas_t;


/* BATT <5>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_BATT_MASK                       =   ( 1U << 5U ),   /*!<  BATT mask                                                       */
    WRITEABLE_REGISTERS_BATT_MEASUREMENT_COMPLETED      =   ( 0U << 5U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_BATT_INITIATE_NEW_MEASUREMENT   =   ( 1U << 5U )    /*!<  Initiates a measurement of the BATTERY voltage                  */
} AMBIMATE_MS4_writeable_reg_batt_t;


/* AUD <4>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_AUD_MASK                        =   ( 1U << 4U ),   /*!<  AUD mask                                                        */
    WRITEABLE_REGISTERS_AUD_MEASUREMENT_COMPLETED       =   ( 0U << 4U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_AUD_INITIATE_NEW_MEASUREMENT    =   ( 1U << 4U )    /*!<  Initiates a measurement of the AUDIO sensor if installed        */
} AMBIMATE_MS4_writeable_reg_aud_t;


/* LIGHT <3>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_LIGHT_MASK                      =   ( 1U << 3U ),   /*!<  LIGHT mask                                                      */
    WRITEABLE_REGISTERS_LIGHT_MEASUREMENT_COMPLETED     =   ( 0U << 3U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_LIGHT_INITIATE_NEW_MEASUREMENT  =   ( 1U << 3U )    /*!<  Initiates a measurement of the LIGHT sensor                     */
} AMBIMATE_MS4_writeable_reg_light_t;


/* HUM <2>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_HUM_MASK                        =   ( 1U << 2U ),   /*!<  HUM mask                                                        */
    WRITEABLE_REGISTERS_HUM_MEASUREMENT_COMPLETED       =   ( 0U << 2U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_HUM_INITIATE_NEW_MEASUREMENT    =   ( 1U << 2U )    /*!<  Initiates a measurement of the HUMIDITY sensor                  */
} AMBIMATE_MS4_writeable_reg_hum_t;


/* TEMP <1>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_TEMP_MASK                       =   ( 1U << 1U ),   /*!<  TEMP mask                                                       */
    WRITEABLE_REGISTERS_TEMP_MEASUREMENT_COMPLETED      =   ( 0U << 1U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_TEMP_INITIATE_NEW_MEASUREMENT   =   ( 1U << 1U )    /*!<  Initiates a measurement of the TEMPERATURE sensor               */
} AMBIMATE_MS4_writeable_reg_temp_t;


/* STATUS <0>
 *    NOTE: N/A.
 */
typedef enum
{
    WRITEABLE_REGISTERS_STATUS_MASK                     =   ( 1U << 0U ),   /*!<  STATUS mask                                                     */
    WRITEABLE_REGISTERS_STATUS_MEASUREMENT_COMPLETED    =   ( 0U << 0U ),   /*!<  Measurement is completed                                        */
    WRITEABLE_REGISTERS_STATUS_INITIATE_NEW_MEASUREMENT =   ( 1U << 0U )    /*!<  Initiates a measurement of the STATUS                           */
} AMBIMATE_MS4_writeable_reg_status_t;




/**
  * @brief   RESET REGISTER.
  *           NOTE: N/A.
  */
/* PROCESSOR_RESET <7:0>
 *    NOTE: N/A.
 */
typedef enum
{
    RESET_REGISTER_PROCESSOR_RESET                      =   0xA5            /*!<  It initiates an AmbiMate processor reset                        */
} AMBIMATE_MS4_reset_t;




/**
  * @brief   OPTIONAL SENSORS BYTE.
  *           NOTE: N/A.
  */
typedef enum
{
    OPTIONAL_SENSORS_NONE                               =   0,            /*!<  No optional sensors on board                                      */
    OPTIONAL_SENSORS_CO2                                =   1,            /*!<  Optional sensors: C02 only                                        */
    OPTIONAL_SENSORS_MIC                                =   3,            /*!<  Optional sensors: MIC only                                        */
    OPTIONAL_SENSORS_CO2_AND_MIC                        =   4             /*!<  Optional sensors: CO2 and MIC                                     */
} AMBIMATE_MS4_op_sensors_byte_t;






#ifndef AMBIMATE_MS4_VECTOR_STRUCT_H
#define AMBIMATE_MS4_VECTOR_STRUCT_H
/* OTHER REGISTERS  */
typedef struct
{
  uint8_t                         firmware_version;                 /*< Firmware version                                                */
  uint8_t                         firmware_sub_version;             /*< Firmware sub-version                                            */
  AMBIMATE_MS4_op_sensors_byte_t  optional_sensors;                 /*< Optional sensors                                                */
} AMBIMATE_MS4_other_reg_param_t;


/* RAW DATA VALUES: 16-bit  */
typedef struct
{
  uint16_t  raw_temperature;                                        /*< Raw temperature value                                           */
  uint16_t  raw_humidity;                                           /*< Raw humidity value                                              */
  uint16_t  raw_light;                                              /*< Raw light value                                                 */
  uint16_t  raw_audio;                                              /*< Raw audio value                                                 */
  uint16_t  raw_battery_volts;                                      /*< Raw battery volts value                                         */
  uint16_t  raw_eco2;                                               /*< Raw eCO2 value                                                  */
  uint16_t  raw_voc;                                                /*< Raw VOC value                                                   */
} AMBIMATE_MS4_raw_data_values_t;


/* RAW DATA VALUES: 8-bit  */
typedef struct
{
  uint16_t  raw_8bit_temperature;                                   /*< Raw temperature value                                           */
  uint16_t  raw_8bit_humidity;                                      /*< Raw humidity value                                              */
  uint16_t  raw_8bit_light;                                         /*< Raw light value                                                 */
  uint16_t  raw_8bit_audio;                                         /*< Raw audio value                                                 */
  uint16_t  raw_8bit_battery_volts;                                 /*< Raw battery volts value                                         */
  uint16_t  raw_8bit_eco2;                                          /*< Raw eCO2 value                                                  */
  uint16_t  raw_8bit_voc;                                           /*< Raw VOC value                                                   */
} AMBIMATE_MS4_raw_8bit_data_values_t;


/* DATA VALUES: 16-bit resolution  */
typedef struct
{
  double    temperature;                                            /*< Temperature value                                               */
  double    humidity;                                               /*< Humidity value                                                  */
  uint16_t  light;                                                  /*< Light value                                                     */
  uint16_t  audio;                                                  /*< Audio value                                                     */
  double    battery_volts;                                          /*< Battery volts value                                             */
  uint16_t  eco2;                                                   /*< eCO2 value                                                      */
  uint16_t  voc;                                                    /*< VOC value                                                       */
} AMBIMATE_MS4_data_values_t;




/* USER: User's variables  */
typedef struct
{
  uint8_t  status;                                                  /*< Status register                                                 */
  
  AMBIMATE_MS4_raw_data_values_t      raw_data;                     /*< Raw data values                                                 */
  AMBIMATE_MS4_raw_8bit_data_values_t raw_data8bit;                 /*< 8-bit Raw data values                                           */
  
  AMBIMATE_MS4_data_values_t          data;                         /*< Data values                                                     */


  AMBIMATE_MS4_other_reg_param_t      info;                         /*< Other registers: Info regarding the device                      */
} AMBIMATE_MS4_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AMBIMATE_MS4_SUCCESS         =       0,
    AMBIMATE_MS4_FAILURE         =       1,
    AMBIMATE_MS4_DATA_CORRUPTED  =       2
} AMBIMATE_MS4_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Init                    ( I2C_parameters_t myI2Cparameters                                        );

/** It initiates a new measurements of the chosen sensors.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_ScanStartByte           ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_writeable_reg_gas_t gas, AMBIMATE_MS4_writeable_reg_batt_t batt, AMBIMATE_MS4_writeable_reg_aud_t aud, AMBIMATE_MS4_writeable_reg_light_t light, AMBIMATE_MS4_writeable_reg_hum_t hum, AMBIMATE_MS4_writeable_reg_temp_t temp, AMBIMATE_MS4_writeable_reg_status_t status );

/** It gets the firmware version.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetFirmwareVersion      ( I2C_parameters_t myI2Cparameters, uint8_t* fw_version );

/** It gets the firmware sub-version.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetFirmwareSubVersion   ( I2C_parameters_t myI2Cparameters, uint8_t* fw_subversion );

/** It gets the optional sensors on board.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetOptionalSensorsByte  ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_op_sensors_byte_t* op_sensors );

/** It performs a processor reset.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_ProcessorReset          ( I2C_parameters_t myI2Cparameters );

/** It gets the Status value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetStatus               ( I2C_parameters_t myI2Cparameters, uint8_t* status );

/** It gets the raw value for temperature.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawTemperature       ( I2C_parameters_t myI2Cparameters, uint16_t* raw_temp );

/** It gets the raw value for humidity.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawHumidity       ( I2C_parameters_t myI2Cparameters, uint16_t* raw_hum );

/** It gets the raw value for light.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawLight       ( I2C_parameters_t myI2Cparameters, uint16_t* raw_light );

/** It gets the raw value for audio.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawAudio       ( I2C_parameters_t myI2Cparameters, uint16_t* raw_audio );

/** It gets the raw value for battery volts.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawBatteryVolts       ( I2C_parameters_t myI2Cparameters, uint16_t* raw_batt );

/** It gets the raw value for eCO2.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawECO2         ( I2C_parameters_t myI2Cparameters, uint16_t* raw_eco2 );

/** It gets the raw value for VOC.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawVOC         ( I2C_parameters_t myI2Cparameters, uint16_t* raw_voc );

/** It gets the raw value for all the sensors.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawAllSensors         ( I2C_parameters_t myI2Cparameters, uint8_t* status, AMBIMATE_MS4_raw_data_values_t* raw_all );

/** It gets the 8bit raw value for temperature.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawTemperature       ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_temp );

/** It gets the 8bit raw value for humidity.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawHumidity       ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_hum );

/** It gets the 8bit raw value for light.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawLight       ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_light );

/** It gets the 8bit raw value for audio.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawAudio       ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_audio );

/** It gets the 8bit raw value for battery volts.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawBatteryVolts       ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_batt );

/** It gets the 8bit raw value for eCO2.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawECO2         ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_eco2 );

/** It gets the 8bit raw value for VOC.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawVOC         ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_voc );

/** It gets the 8bit raw value for all the sensors.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRaw8bitAllSensors         ( I2C_parameters_t myI2Cparameters, uint8_t* status, AMBIMATE_MS4_raw_8bit_data_values_t* raw_8bit_all );

/** It process all the data to human readable values for all the sensors.
  */
AMBIMATE_MS4_data_values_t  AMBIMATE_MS4_ProcessAllData         ( AMBIMATE_MS4_raw_data_values_t raw_all );


#ifdef __cplusplus
}
#endif

#endif /* AMBIMATE_MS4_H */
