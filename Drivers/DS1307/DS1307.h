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
    SECONDS_10SECONDS_MASK         =   ( 0b111 << 4 )       /*!<  10 Seconds mask                            */
} DS1307_10seconds_t;


/**
  * @brief   10 SECONDS
  */
typedef enum
{
    SECONDS_10SECONDS_MASK         =   ( 0b111 << 4 )       /*!<  10 Seconds mask                            */
} DS1307_10seconds_t;


/**
  * @brief   POLARITY
  */
typedef enum
{
    DS1307_CONFIGURATION_POL_MASK                   =   ( 1U << 10 ),    /*!<  Polarity Mask                                                                      */
    DS1307_CONFIGURATION_POL_ALERT_PIN_ACTIVE_LOW   =   ( 0U << 10 ),    /*!<  Polarity: ALERT pin becomes active low ( default )                                 */
    DS1307_CONFIGURATION_POL_ALERT_PIN_ACTIVE_HIGH  =   ( 1U << 10 )     /*!<  Polarity: ALERT pin becomes active high and the state of the ALERT pin is inverted */
} DS1307_configuration_polarity_t;


/**
  * @brief   FAULT QUEUE
  */
typedef enum
{
    DS1307_CONFIGURATION_F1F0_MASK                   =   ( 0b11 << 11 ),    /*!<  Fault Queue Mask                                                               */
    DS1307_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_1   =   ( 0b00 << 11 ),    /*!<  Fault Queue: consecutive faults: 1                                             */
    DS1307_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_2   =   ( 0b01 << 11 ),    /*!<  Fault Queue: consecutive faults: 2                                             */
    DS1307_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_4   =   ( 0b10 << 11 ),    /*!<  Fault Queue: consecutive faults: 4                                             */
    DS1307_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_6   =   ( 0b11 << 11 )     /*!<  Fault Queue: consecutive faults: 6                                             */
} DS1307_configuration_fault_queue_t;


/**
  * @brief   CONVERTER RESOLUTION
  */
typedef enum
{
    DS1307_CONFIGURATION_R1R0_MASK                   =   ( 0b11 << 13 )     /*!<  Converter resolution bits Mask                                                 */
} DS1307_configuration_converter_resolution_t;


/**
  * @brief   ONE-SHOT
  */
typedef enum
{
    DS1307_CONFIGURATION_OS_MASK                                =   ( 1U << 15 ),      /*!<  One-Shot Mask                                                       */
    DS1307_CONFIGURATION_OS_START_SINGLE_TEMPERATURE_CONVERSION =   ( 1U << 15 ),      /*!<  One-Shot It starts a single temperature conversion                  */
    DS1307_CONFIGURATION_OS_BUSY                                =   ( 0U << 15 )       /*!<  One-Shot During the conversion, the OS bit reads '0'                */
} DS1307_configuration_one_shot_t;



/**
  * @brief   EXTENDED-MODE BIT
  */
typedef enum
{
    DS1307_CONFIGURATION_EM_MASK                                =   ( 1U << 4 ),      /*!<  Extended-Mode Mask                                                  */
    DS1307_CONFIGURATION_EM_NORMAL_MODE_OPERATION               =   ( 0U << 4 ),      /*!<  Extended-Mode: Normal Mode operation                                */
    DS1307_CONFIGURATION_EM_EXTENDED_MODE_OPERATION             =   ( 1U << 4 )       /*!<  Extended-Mode: Extended Mode operation                              */
} DS1307_configuration_extended_mode_bit_t;


/**
  * @brief   ALERT BIT
  */
typedef enum
{
    DS1307_CONFIGURATION_AL_MASK                                =   ( 1U << 5 )       /*!<  Alert Mask                                                          */
} DS1307_configuration_alert_bit_t;


/**
  * @brief   CONVERSION RATE
  */
typedef enum
{
    DS1307_CONFIGURATION_CR_MASK                                =   ( 0b11 << 6 ),    /*!<  Conversion Rate Mask                                                */
    DS1307_CONFIGURATION_CR_0_25_HZ                             =   ( 0b00 << 6 ),    /*!<  Conversion Rate: 0.25Hz                                             */
    DS1307_CONFIGURATION_CR_1_HZ                                =   ( 0b01 << 6 ),    /*!<  Conversion Rate: 1Hz                                                */
    DS1307_CONFIGURATION_CR_4_HZ                                =   ( 0b10 << 6 ),    /*!<  Conversion Rate: 4Hz ( default )                                    */
    DS1307_CONFIGURATION_CR_8_HZ                                =   ( 0b11 << 6 )     /*!<  Conversion Rate: 8Hz                                                */
} DS1307_configuration_conversion_rate_t;



// HIGH-TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    DS1307_THIGH_RESOLUTION_12_BITS_MASK    =   0xFFF0,                             /*!<  THIGH configured as a 12-bit                         */
    DS1307_THIGH_RESOLUTION_13_BITS_MASK    =   0xFFF8                              /*!<  THIGH configured as a 13-bit                         */
} DS1307_high_temperature_register_t;



// LOW-TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    DS1307_TLOW_RESOLUTION_12_BITS_MASK    =   0xFFF0,                             /*!<  TLOW configured as a 12-bit                            */
    DS1307_TLOW_RESOLUTION_13_BITS_MASK    =   0xFFF8                              /*!<  TLOW configured as a 13-bit                            */
} DS1307_low_temperature_register_t;




#ifndef DS1307_VECTOR_STRUCT_H
#define DS1307_VECTOR_STRUCT_H
typedef struct
{
    float    Temperature;

    int16_t  TemperatureRegister;
    uint16_t ConfigurationRegister;
    int16_t  TLOW_Register;
    int16_t  THIGH_Register;
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
DS1307_status_t  DS1307_Init                                ( I2C_parameters_t myI2Cparameters                                                      );

/** It gets the temperature register value ( raw temperature ).
  */
DS1307_status_t  DS1307_ReadTemperatureRegister             ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTemperatureRegister         );

/** It gets the temperature value.
  */
DS1307_status_t  DS1307_GetTemperature                      ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTemperature                 );

/** It gets the low temperature register value.
  */
DS1307_status_t  DS1307_Read_T_LOW_Register                 ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTLOW_Register               );

/** It updates the low temperature register value.
  */
DS1307_status_t  DS1307_Write_T_LOW_Register                ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myTLOW_Register                );

/** It gets the high temperature register value.
  */
DS1307_status_t  DS1307_Read_T_HIGH_Register                ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myTHIGH_Register              );

/** It updates the high temperature register value.
  */
DS1307_status_t  DS1307_Write_T_HIGH_Register               ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t myTHIGH_Register               );

/** It gets the configuration register value.
  */
DS1307_status_t  DS1307_ReadConfigurationRegister           ( I2C_parameters_t myI2Cparameters, DS1307_vector_data_t* myConfigurationRegister       );

/** It enables shutdown/continuous mode operation.
  */
DS1307_status_t  DS1307_SetShutdownMode                     ( I2C_parameters_t myI2Cparameters, DS1307_configuration_shutdown_mode_t mySDMode       );

/** It enables comparator/interrupt mode operation.
  */
DS1307_status_t  DS1307_SetThermostatMode                   ( I2C_parameters_t myI2Cparameters, DS1307_configuration_thermostat_mode_t myTMMode     );

/** The polarity bit allows the user to adjust the polarity of the ALERT pin output.
  */
DS1307_status_t  DS1307_SetPolarityAlertPinOutput           ( I2C_parameters_t myI2Cparameters, DS1307_configuration_polarity_t myPOLMode           );

/** The number of fault conditions required to generate an alert may be programmed using the fault queue.
  */
DS1307_status_t  DS1307_SetConsecutiveFaultsQueue           ( I2C_parameters_t myI2Cparameters, DS1307_configuration_fault_queue_t myF1F0Mode       );

/** When the device is in Shutdown Mode, writing a 1 to the OS bit starts a single temperature conversion.
  */
DS1307_status_t  DS1307_TriggerSingleTemperatureConversion  ( I2C_parameters_t myI2Cparameters                                                      );

/** It sets the device into Normal/Extended mode operation.
  */
DS1307_status_t  DS1307_SetModeOperation                    ( I2C_parameters_t myI2Cparameters, DS1307_configuration_extended_mode_bit_t myEMMode   );

/** It sets the conversion rate for the device.
  */
DS1307_status_t  DS1307_SetConversionRate                   ( I2C_parameters_t myI2Cparameters, DS1307_configuration_conversion_rate_t myCR         );




#ifdef __cplusplus
}
#endif

#endif /* DS1307_H */
