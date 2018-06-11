/**
 * @brief       TMP102.h
 * @details     Low-Power Digital Temperature Sensor With SMBus and Two-Wire Serial.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/June/2018
 * @version     9/June/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef TMP102_H_
#define TMP102_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    TMP102_ADDRESS_A0_GROUND     =   0b1001000,             /*!<   TMP102 I2C Address: A0 connected to Ground           */
    TMP102_ADDRESS_A0_VPOS       =   0b1001001,             /*!<   TMP102 I2C Address: A0 connected to V+               */
    TMP102_ADDRESS_A0_SDA        =   0b1001010,             /*!<   TMP102 I2C Address: A0 connected to SDA              */
    TMP102_ADDRESS_A0_SCL        =   0b1001011              /*!<   TMP102 I2C Address: A0 connected to SCL              */
} TMP102_addresses_t;


// REGISTERS
/**
  * @brief   REGISTERS BYTE
  */
typedef enum
{
    TMP102_TEMPERATURE_REGISTER     =   0x00,               /*!<  Temperature Register      ( Read Only  )              */
    TMP102_CONFIGURATION_REGISTER   =   0x01,               /*!<  Configuration Register    ( Read/Write )              */
    TMP102_T_LOW_REGISTER           =   0x02,               /*!<  T LOW Register            ( Read/Write )              */
    TMP102_T_HIGH_REGISTER          =   0x03                /*!<  T HIGH Register           ( Read/Write )              */
} TMP102_registers_byte_t;



// TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    TMP102_RESOLUTION_12_BITS_MASK    =   0xFFF0,           /*!<  TMP102 configured as a 12-bit                         */
    TMP102_RESOLUTION_13_BITS_MASK    =   0xFFF8            /*!<  TMP102 configured as a 13-bit                         */
} TMP102_temperature_register_t;



// CONFIGURATION REGISTER
/**
  * @brief   SHUTDOWN MODE
  */
typedef enum
{
    TMP102_CONFIGURATION_SD_MASK        =   ( 1U << 8 ),    /*!<  Shutdown Mode Mask                                    */
    TMP102_CONFIGURATION_SD_ENABLED     =   ( 1U << 8 ),    /*!<  Shutdown Mode Enabled                                 */
    TMP102_CONFIGURATION_SD_DISABLED    =   ( 0U << 8 )     /*!<  Shutdown Mode Disabled                                */
} TMP102_configuration_shutdown_mode_t;


/**
  * @brief   THERMOSTAT MODE
  */
typedef enum
{
    TMP102_CONFIGURATION_TM_MASK            =   ( 1U << 9 ),    /*!<  Thermostat Mode Mask                           */
    TMP102_CONFIGURATION_TM_COMPARATOR_MODE =   ( 0U << 9 ),    /*!<  Thermostat Mode: Comparator mode               */
    TMP102_CONFIGURATION_TM_INTERRUPT_MODE  =   ( 1U << 9 )     /*!<  Thermostat Mode: Interrupt mode                */
} TMP102_configuration_thermostat_mode_t;


/**
  * @brief   POLARITY
  */
typedef enum
{
    TMP102_CONFIGURATION_POL_MASK                   =   ( 1U << 10 ),    /*!<  Polarity Mask                                                                      */
    TMP102_CONFIGURATION_POL_ALERT_PIN_ACTIVE_LOW   =   ( 0U << 10 ),    /*!<  Polarity: ALERT pin becomes active low ( default )                                 */
    TMP102_CONFIGURATION_POL_ALERT_PIN_ACTIVE_LOW   =   ( 1U << 10 )     /*!<  Polarity: ALERT pin becomes active high and the state of the ALERT pin is inverted */
} TMP102_configuration_polarity_t;


/**
  * @brief   FAULT QUEUE
  */
typedef enum
{
    TMP102_CONFIGURATION_F1F0_MASK                   =   ( 0b11 << 11 ),    /*!<  Fault Queue Mask                                                               */
    TMP102_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_1   =   ( 0b00 << 11 ),    /*!<  Fault Queue: consecutive faults: 1                                             */
    TMP102_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_2   =   ( 0b01 << 11 ),    /*!<  Fault Queue: consecutive faults: 2                                             */
    TMP102_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_4   =   ( 0b10 << 11 ),    /*!<  Fault Queue: consecutive faults: 4                                             */
    TMP102_CONFIGURATION_F1F0_CONSECUTIVE_FAULTS_6   =   ( 0b11 << 11 )     /*!<  Fault Queue: consecutive faults: 6                                             */
} TMP102_configuration_fault_queue_t;


/**
  * @brief   CONVERTER RESOLUTION
  */
typedef enum
{
    TMP102_CONFIGURATION_R1R0_MASK                   =   ( 0b11 << 13 )     /*!<  Converter resolution bits Mask                                                 */
} TMP102_configuration_converter_resolution_t;


/**
  * @brief   ONE-SHOT
  */
typedef enum
{
    TMP102_CONFIGURATION_OS_MASK                                =   ( 1U << 15 ),      /*!<  One-Shot Mask                                                       */
    TMP102_CONFIGURATION_OS_START_SINGLE_TEMPERATURE_CONVERSION =   ( 1U << 15 ),      /*!<  One-Shot It starts a single temperature conversion                  */
    TMP102_CONFIGURATION_OS_BUSY                                =   ( 0U << 15 )       /*!<  One-Shot During the conversion, the OS bit reads '0'                */
} TMP102_configuration_one_shot_t;



/**
  * @brief   EXTENDED-MODE BIT
  */
typedef enum
{
    TMP102_CONFIGURATION_EM_MASK                                =   ( 1U << 4 ),      /*!<  Extended-Mode Mask                                                  */
    TMP102_CONFIGURATION_EM_NORMAL_MODE_OPERATION               =   ( 0U << 4 ),      /*!<  Extended-Mode: Normal Mode operation                                */
    TMP102_CONFIGURATION_EM_EXTENDED_MODE_OPERATION             =   ( 1U << 4 )       /*!<  Extended-Mode: Extended Mode operation                              */
} TMP102_configuration_extended_mode_bit_t;


/**
  * @brief   ALERT BIT
  */
typedef enum
{
    TMP102_CONFIGURATION_AL_MASK                                =   ( 1U << 5 )       /*!<  Alert Mask                                                          */
} TMP102_configuration_alert_bit_t;


/**
  * @brief   CONVERSION RATE
  */
typedef enum
{
    TMP102_CONFIGURATION_CR_MASK                                =   ( 0b11 << 6 ),    /*!<  Conversion Rate Mask                                                */
    TMP102_CONFIGURATION_CR_0_25_HZ                             =   ( 0b00 << 6 ),    /*!<  Conversion Rate: 0.25Hz                                             */
    TMP102_CONFIGURATION_CR_1_HZ                                =   ( 0b01 << 6 ),    /*!<  Conversion Rate: 1Hz                                                */
    TMP102_CONFIGURATION_CR_4_HZ                                =   ( 0b10 << 6 ),    /*!<  Conversion Rate: 4Hz ( default )                                    */
    TMP102_CONFIGURATION_CR_8_HZ                                =   ( 0b11 << 6 )     /*!<  Conversion Rate: 8Hz                                                */
} TMP102_configuration_conversion_rate_t;



// HIGH-TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    TMP102_THIGH_RESOLUTION_12_BITS_MASK    =   0xFFF0,                             /*!<  THIGH configured as a 12-bit                         */
    TMP102_THIGH_RESOLUTION_13_BITS_MASK    =   0xFFF8                              /*!<  THIGH configured as a 13-bit                         */
} TMP102_high_temperature_register_t;



// LOW-TEMPERATURE REGISTER
/**
  * @brief   TEMPERATURE REGISTER
  */
typedef enum
{
    TMP102_TLOW_RESOLUTION_12_BITS_MASK    =   0xFFF0,                             /*!<  TLOW configured as a 12-bit                            */
    TMP102_TLOW_RESOLUTION_13_BITS_MASK    =   0xFFF8                              /*!<  TLOW configured as a 13-bit                            */
} TMP102_low_temperature_register_t;




#ifndef TMP102_VECTOR_STRUCT_H
#define TMP102_VECTOR_STRUCT_H
typedef struct
{
    float    Temperature;

    int16_t  TemperatureRegister;
    uint16_t ConfigurationRegister;
    int16_t  TLOW_Register;
    int16_t  THIGH_Register;
} TMP102_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    TMP102_SUCCESS     =       0,
    TMP102_FAILURE     =       1
} TMP102_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
TMP102_status_t  TMP102_Init                                ( I2C_parameters_t myI2Cparameters                                                      );

/** It gets the temperature register value ( raw temperature ).
  */
TMP102_status_t  TMP102_ReadTemperatureRegister             ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperatureRegister         );

/** It gets the temperature value.
  */
TMP102_status_t  TMP102_GetTemperature                      ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTemperature                 );

/** It gets the low temperature register value.
  */
TMP102_status_t  TMP102_Read_T_LOW_Register                 ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTLOW_Register               );

/** It updates the low temperature register value.
  */
TMP102_status_t  TMP102_Write_T_LOW_Register                ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t myTLOW_Register                );

/** It gets the high temperature register value.
  */
TMP102_status_t  TMP102_Read_T_HIGH_Register                ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myTHIGH_Register              );

/** It updates the high temperature register value.
  */
TMP102_status_t  TMP102_Write_T_HIGH_Register               ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t myTHIGH_Register               );

/** It gets the configuration register value.
  */
TMP102_status_t  TMP102_ReadConfigurationRegister           ( I2C_parameters_t myI2Cparameters, TMP102_vector_data_t* myConfigurationRegister       );

/** It enables shutdown/continuous mode operation.
  */
TMP102_status_t  TMP102_SetShutdownMode                     ( I2C_parameters_t myI2Cparameters, TMP102_configuration_shutdown_mode_t mySDMode       );

/** It enables comparator/interrupt mode operation.
  */
TMP102_status_t  TMP102_SetThermostatMode                   ( I2C_parameters_t myI2Cparameters, TMP102_configuration_thermostat_mode_t myTMMode     );

/** The polarity bit allows the user to adjust the polarity of the ALERT pin output.
  */
TMP102_status_t  TMP102_SetPolarityAlertPinOutput           ( I2C_parameters_t myI2Cparameters, TMP102_configuration_polarity_t myPOLMode           );

/** The number of fault conditions required to generate an alert may be programmed using the fault queue.
  */
TMP102_status_t  TMP102_SetConsecutiveFaultsQueue           ( I2C_parameters_t myI2Cparameters, TMP102_configuration_fault_queue_t myF1F0Mode       );

/** When the device is in Shutdown Mode, writing a 1 to the OS bit starts a single temperature conversion.
  */
TMP102_status_t  TMP102_TriggerSingleTemperatureConversion  ( I2C_parameters_t myI2Cparameters                                                      );

/** It sets the device into Normal/Extended mode operation.
  */
TMP102_status_t  TMP102_SetModeOperation                    ( I2C_parameters_t myI2Cparameters, TMP102_configuration_extended_mode_bit_t myEMMode   );

/** It sets the conversion rate for the device.
  */
TMP102_status_t  TMP102_SetConversionRate                   ( I2C_parameters_t myI2Cparameters, TMP102_configuration_conversion_rate_t myCR         );




#ifdef __cplusplus
}
#endif

#endif /* TMP102_H */
