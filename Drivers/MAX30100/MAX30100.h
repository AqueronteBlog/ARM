/**
 * @brief       MAX30100.h
 * @details     Pulse Oximeter and Heart-Rate Sensor IC for Wearable Health.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/July/2018
 * @version     9/July/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef MAX30100_H_
#define MAX30100_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    MAX30100_ADDRESS     =   0b1010111                      /*!<   MAX30100 I2C Address                                     */
} MAX30100_address_t;


// REGISTER MAPS
/**
  * @brief   REGISTERS BYTE
  */
typedef enum
{
    MAX30100_INTERRUPT_STATUS       =   0x00,               /*!<  Interrupt Status          ( Read Only  ) ( Default 0x00 ) */
    MAX30100_INTERRUPT_ENABLE       =   0x01,               /*!<  Interrupt Enable          ( Read/Write ) ( Default 0x00 ) */
    MAX30100_FIFO_WRITE_POINTER     =   0x02,               /*!<  FIFO Write Pointer        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_OVER_FLOW_COUNTER      =   0x03,               /*!<  Over Flow Counter         ( Read/Write ) ( Default 0x00 ) */
    MAX30100_FIFO_READ_POINTER      =   0x04,               /*!<  FIFO Read Pointer         ( Read/Write ) ( Default 0x00 ) */
    MAX30100_FIFO_DATA_REGISTER     =   0x05,               /*!<  FIFO Data Register        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_MODE_CONFIGURATION     =   0x06,               /*!<  Mode Configuration        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_SPO2_CONFIGURATION     =   0x07,               /*!<  SpO2 Configuration        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_LED_CONFIGURATION      =   0x09,               /*!<  LED Configuration         ( Read/Write ) ( Default 0x00 ) */
    MAX30100_TEMP_INTEGER           =   0x16,               /*!<  Temperature Integer       ( Read/Write ) ( Default 0x00 ) */
    MAX30100_TEMP_FRACTION          =   0x17,               /*!<  Temperature Fraction      ( Read/Write ) ( Default 0x00 ) */
    MAX30100_REVISION_ID            =   0xFE,               /*!<  T HIGH Register           ( Read Only  ) ( Default ??   ) */
    MAX30100_PART_ID                =   0xFF                /*!<  T HIGH Register           ( Read/Write ) ( Default 0x11 ) */
} MAX30100_register_maps_t;



// HOLAHOLAHOLAHOLAHOLA TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    MAX30100_RESOLUTION_12_BITS_MASK    =   0xFFF0,           /*!<  MAX30100 configured as a 12-bit                         */
    MAX30100_RESOLUTION_13_BITS_MASK    =   0xFFF8            /*!<  MAX30100 configured as a 13-bit                         */
} MAX30100_temperature_register_t;



// CONFIGURATION REGISTER
/**
  * @brief   SHUTDOWN MODE
  */
typedef enum
{
    MAX30100_CONFIGURATION_SD_MASK        =   ( 1U << 8 ),    /*!<  Shutdown Mode Mask                                    */
    MAX30100_CONFIGURATION_SD_ENABLED     =   ( 1U << 8 ),    /*!<  Shutdown Mode Enabled                                 */
    MAX30100_CONFIGURATION_SD_DISABLED    =   ( 0U << 8 )     /*!<  Shutdown Mode Disabled                                */
} MAX30100_configuration_shutdown_mode_t;


/**
  * @brief   THERMOSTAT MODE
  */
typedef enum
{
    MAX30100_CONFIGURATION_TM_MASK            =   ( 1U << 9 ),    /*!<  Thermostat Mode Mask                           */
    MAX30100_CONFIGURATION_TM_COMPARATOR_MODE =   ( 0U << 9 ),    /*!<  Thermostat Mode: Comparator mode               */
    MAX30100_CONFIGURATION_TM_INTERRUPT_MODE  =   ( 1U << 9 )     /*!<  Thermostat Mode: Interrupt mode                */
} MAX30100_configuration_thermostat_mode_t;


/**
  * @brief   POLARITY
  */
typedef enum
{
    MAX30100_CONFIGURATION_POL_MASK                   =   ( 1U << 10 ),    /*!<  Polarity Mask                                                                      */
    MAX30100_CONFIGURATION_POL_ALERT_PIN_ACTIVE_LOW   =   ( 0U << 10 ),    /*!<  Polarity: ALERT pin becomes active low ( default )                                 */
    MAX30100_CONFIGURATION_POL_ALERT_PIN_ACTIVE_HIGH  =   ( 1U << 10 )     /*!<  Polarity: ALERT pin becomes active high and the state of the ALERT pin is inverted */
} MAX30100_configuration_polarity_t;


/**
  * @brief   FAULT QUEUE
  */
typedef enum
{
    MAX30100_CONFIGURATION_F1F0_MASK                   =   ( 0b11 << 11 ),    /*!<  Fault Queue Mask                                                               */
    MAX30100_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_1   =   ( 0b00 << 11 ),    /*!<  Fault Queue: consecutive faults: 1                                             */
    MAX30100_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_2   =   ( 0b01 << 11 ),    /*!<  Fault Queue: consecutive faults: 2                                             */
    MAX30100_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_4   =   ( 0b10 << 11 ),    /*!<  Fault Queue: consecutive faults: 4                                             */
    MAX30100_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_6   =   ( 0b11 << 11 )     /*!<  Fault Queue: consecutive faults: 6                                             */
} MAX30100_configuration_fault_queue_t;


/**
  * @brief   CONVERTER RESOLUTION
  */
typedef enum
{
    MAX30100_CONFIGURATION_R1R0_MASK                   =   ( 0b11 << 13 )     /*!<  Converter resolution bits Mask                                                 */
} MAX30100_configuration_converter_resolution_t;


/**
  * @brief   ONE-SHOT
  */
typedef enum
{
    MAX30100_CONFIGURATION_OS_MASK                                =   ( 1U << 15 ),      /*!<  One-Shot Mask                                                       */
    MAX30100_CONFIGURATION_OS_START_SINGLE_TEMPERATURE_CONVERSION =   ( 1U << 15 ),      /*!<  One-Shot It starts a single temperature conversion                  */
    MAX30100_CONFIGURATION_OS_BUSY                                =   ( 0U << 15 )       /*!<  One-Shot During the conversion, the OS bit reads '0'                */
} MAX30100_configuration_one_shot_t;



/**
  * @brief   EXTENDED-MODE BIT
  */
typedef enum
{
    MAX30100_CONFIGURATION_EM_MASK                                =   ( 1U << 4 ),      /*!<  Extended-Mode Mask                                                  */
    MAX30100_CONFIGURATION_EM_NORMAL_MODE_OPERATION               =   ( 0U << 4 ),      /*!<  Extended-Mode: Normal Mode operation                                */
    MAX30100_CONFIGURATION_EM_EXTENDED_MODE_OPERATION             =   ( 1U << 4 )       /*!<  Extended-Mode: Extended Mode operation                              */
} MAX30100_configuration_extended_mode_bit_t;


/**
  * @brief   ALERT BIT
  */
typedef enum
{
    MAX30100_CONFIGURATION_AL_MASK                                =   ( 1U << 5 )       /*!<  Alert Mask                                                          */
} MAX30100_configuration_alert_bit_t;


/**
  * @brief   CONVERSION RATE
  */
typedef enum
{
    MAX30100_CONFIGURATION_CR_MASK                                =   ( 0b11 << 6 ),    /*!<  Conversion Rate Mask                                                */
    MAX30100_CONFIGURATION_CR_0_25_HZ                             =   ( 0b00 << 6 ),    /*!<  Conversion Rate: 0.25Hz                                             */
    MAX30100_CONFIGURATION_CR_1_HZ                                =   ( 0b01 << 6 ),    /*!<  Conversion Rate: 1Hz                                                */
    MAX30100_CONFIGURATION_CR_4_HZ                                =   ( 0b10 << 6 ),    /*!<  Conversion Rate: 4Hz ( default )                                    */
    MAX30100_CONFIGURATION_CR_8_HZ                                =   ( 0b11 << 6 )     /*!<  Conversion Rate: 8Hz                                                */
} MAX30100_configuration_conversion_rate_t;



// HIGH-TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    MAX30100_THIGH_RESOLUTION_12_BITS_MASK    =   0xFFF0,                             /*!<  THIGH configured as a 12-bit                         */
    MAX30100_THIGH_RESOLUTION_13_BITS_MASK    =   0xFFF8                              /*!<  THIGH configured as a 13-bit                         */
} MAX30100_high_temperature_register_t;



// LOW-TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    MAX30100_TLOW_RESOLUTION_12_BITS_MASK    =   0xFFF0,                             /*!<  TLOW configured as a 12-bit                            */
    MAX30100_TLOW_RESOLUTION_13_BITS_MASK    =   0xFFF8                              /*!<  TLOW configured as a 13-bit                            */
} MAX30100_low_temperature_register_t;




#ifndef MAX30100_VECTOR_STRUCT_H
#define MAX30100_VECTOR_STRUCT_H
typedef struct
{
    float    Temperature;

    int16_t  TemperatureRegister;
    uint16_t ConfigurationRegister;
    int16_t  TLOW_Register;
    int16_t  THIGH_Register;
} MAX30100_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    MAX30100_SUCCESS     =       0,
    MAX30100_FAILURE     =       1
} MAX30100_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
MAX30100_status_t  MAX30100_Init                                ( I2C_parameters_t myI2Cparameters                                                      );

/** It gets the temperature register value ( raw temperature ).
  */
MAX30100_status_t  MAX30100_ReadTemperatureRegister             ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTemperatureRegister         );

/** It gets the temperature value.
  */
MAX30100_status_t  MAX30100_GetTemperature                      ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTemperature                 );

/** It gets the low temperature register value.
  */
MAX30100_status_t  MAX30100_Read_T_LOW_Register                 ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTLOW_Register               );

/** It updates the low temperature register value.
  */
MAX30100_status_t  MAX30100_Write_T_LOW_Register                ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t myTLOW_Register                );

/** It gets the high temperature register value.
  */
MAX30100_status_t  MAX30100_Read_T_HIGH_Register                ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTHIGH_Register              );

/** It updates the high temperature register value.
  */
MAX30100_status_t  MAX30100_Write_T_HIGH_Register               ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t myTHIGH_Register               );

/** It gets the configuration register value.
  */
MAX30100_status_t  MAX30100_ReadConfigurationRegister           ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myConfigurationRegister       );

/** It enables shutdown/continuous mode operation.
  */
MAX30100_status_t  MAX30100_SetShutdownMode                     ( I2C_parameters_t myI2Cparameters, MAX30100_configuration_shutdown_mode_t mySDMode       );

/** It enables comparator/interrupt mode operation.
  */
MAX30100_status_t  MAX30100_SetThermostatMode                   ( I2C_parameters_t myI2Cparameters, MAX30100_configuration_thermostat_mode_t myTMMode     );

/** The polarity bit allows the user to adjust the polarity of the ALERT pin output.
  */
MAX30100_status_t  MAX30100_SetPolarityAlertPinOutput           ( I2C_parameters_t myI2Cparameters, MAX30100_configuration_polarity_t myPOLMode           );

/** The number of fault conditions required to generate an alert may be programmed using the fault queue.
  */
MAX30100_status_t  MAX30100_SetConsecutiveFaultsQueue           ( I2C_parameters_t myI2Cparameters, MAX30100_configuration_fault_queue_t myF1F0Mode       );

/** When the device is in Shutdown Mode, writing a 1 to the OS bit starts a single temperature conversion.
  */
MAX30100_status_t  MAX30100_TriggerSingleTemperatureConversion  ( I2C_parameters_t myI2Cparameters                                                      );

/** It sets the device into Normal/Extended mode operation.
  */
MAX30100_status_t  MAX30100_SetModeOperation                    ( I2C_parameters_t myI2Cparameters, MAX30100_configuration_extended_mode_bit_t myEMMode   );

/** It sets the conversion rate for the device.
  */
MAX30100_status_t  MAX30100_SetConversionRate                   ( I2C_parameters_t myI2Cparameters, MAX30100_configuration_conversion_rate_t myCR         );




#ifdef __cplusplus
}
#endif

#endif /* MAX30100_H */
