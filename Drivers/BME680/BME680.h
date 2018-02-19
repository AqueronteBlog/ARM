/**
 * @brief       BME680.h
 * @details     Low power gas, pressure, temperature & humidity sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/February/2018
 * @version     13/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef BME680_H_
#define BME680_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   DEFAULT ADDRESSES. NOTE: The SDO pin cannot be left floating, if left floating, the
  *                                   I2C address will be undefined.
  */
typedef enum
{
    BME680_ADDRESS_SDO_TO_GND     =   0x76,         /*!<   BME680 I2C Address: SDO connected to GND         */
    BME680_ADDRESS_SDO_TO_VDD     =   0x77          /*!<   BME680 I2C Address: SDO connected to VDD         */
} BME680_address_t;


// REGISTERS
/**
  * @brief   REGISTERS: MEMORY MAP
  */
typedef enum
{
    BME680_STATUS           =   0x73,               /*!<  Selects memory map page in SPI mode               */
    BME680_RESET            =   0xE0,               /*!<  Soft-reset register                               */
    BME680_ID               =   0xD0,               /*!<  Chip ID                                           */
    BME680_CONFIG           =   0x75,               /*!<  IIR filter control                                */
    BME680_CTRL_MEAS        =   0x74,               /*!<  Oversampling setting for temperature and pressure */
    BME680_CTRL_HUM         =   0x72,               /*!<  Humidity sensor over sampling control             */
    BME680_CTRL_GAS_1       =   0x71,               /*!<  Heater  profile selection                         */
    BME680_CTRL_GAS_0       =   0x70,               /*!<  Heater off                                        */
    BME680_GAS_WAIT_9       =   0x6D,               /*!<  Gas sensor wait time                              */
    BME680_GAS_WAIT_0       =   0x64,               /*!<  Gas sensor wait time                              */
    BME680_RES_HEAT_9       =   0x63,               /*!<  Target heater resistance                          */
    BME680_RES_HEAT_0       =   0x5A,               /*!<  Target heater resistance                          */
    BME680_IDAC_HEAT_9      =   0x59,               /*!<  Heater current                                    */
    BME680_IDAC_HEAT_0      =   0x50,               /*!<  Heater current                                    */
    BME680_GAS_R_LSB        =   0x2B,               /*!<  Gas resistance data                               */
    BME680_GAS_R_MSB        =   0x2A,               /*!<  Gas resistance data                               */
    BME680_HUM_LSB          =   0x26,               /*!<  Humidity data                                     */
    BME680_HUM_MSB          =   0x25,               /*!<  Humidity data                                     */
    BME680_TEMP_XLSB        =   0x24,               /*!<  Temperature data                                  */
    BME680_TEMP_LSB         =   0x23,               /*!<  Temperature data                                  */
    BME680_TEMP_MSB         =   0x22,               /*!<  Temperature data                                  */
    BME680_PRESS_XLSB       =   0x21,               /*!<  Pressure data                                     */
    BME680_PRESS_LSB        =   0x20,               /*!<  Pressure data                                     */
    BME680_PRESS_MSB        =   0x1F,               /*!<  Pressure data                                     */
    BME680_MEAS_STATUS_0    =   0x1D,               /*!<  New data status                                   */
} BME680_registers_t;



// GENERAL CONTROL REGISTERS
/**
  * @brief   MODE SELECTION
  */
typedef enum
{
    BME680_MODE_MASK        =   ( 0x03 << 0 ),      /*!<  BME680 Mode Selection Mask                        */
    BME680_MODE_SLEEP_MODE  =   ( 0x00 << 0 ),      /*!<  BME680 Sleep Mode                                 */
    BME680_MODE_FORCED_MODE =   ( 0x01 << 0 )       /*!<  BME680 Forced Mode                                */
} BME680_ctrl_meas_mode_selection_t;


/**
  * @brief   RESET
  */
typedef enum
{
    BME680_RESET_MASK   =   ( 0xFF << 0 ),          /*!<  BME680 Mode Selection Mask                        */
    BME680_RESET        =   ( 0xB6 << 0 )           /*!<  BME680 Command to initiate a soft-reset procedure */
} BME680_reset_t;


/**
  * @brief   ID
  */
typedef enum
{
    BME680_ID_MASK   =   ( 0xFF << 0 )              /*!<  BME680 ID Mask                                    */
} BME680_id_t;


// TEMPERATURE, PRESSURE AND RELATIVE HUMIDITY CONTRO, REGISTERS
/**
  * @brief   HUMIDITY SENSOR OVER SAMPLING CONTROL. Controls over sampling setting of humidity sensor.
  */
typedef enum
{
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_MASK    =   ( 0x07 << 0 ),          /*!<  BME680 Humidity Oversampling Mask                             */
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_SKIPPED =   ( 0x00 << 0 ),          /*!<  BME680 Humidity Oversampling skipped ( output set to 0x8000 ) */
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_X1      =   ( 0x01 << 0 ),          /*!<  BME680 Humidity Oversampling x1                               */
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_X2      =   ( 0x02 << 0 ),          /*!<  BME680 Humidity Oversampling x2                               */
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_X4      =   ( 0x03 << 0 ),          /*!<  BME680 Humidity Oversampling x4                               */
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_X8      =   ( 0x04 << 0 ),          /*!<  BME680 Humidity Oversampling x8                               */
    BME680_OSRS_H_HUMIDITY_OVERSAMPLING_X16     =   ( 0x05 << 0 )           /*!<  BME680 Humidity Oversampling x16                              */
} BME680_ctrl_hum_humidity_oversampling_t;


/**
  * @brief   OVER SAMPLING SETTING. TEMPERATURE DATA. Temperature oversampling settings.
  */
typedef enum
{
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_MASK    =   ( 0xE0 << 5 ),          /*!<  BME680 Temperature Oversampling Mask                             */
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_SKIPPED =   ( 0x00 << 5 ),          /*!<  BME680 Temperature Oversampling skipped ( output set to 0x8000 ) */
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_X1      =   ( 0x01 << 5 ),          /*!<  BME680 Temperature Oversampling x1                               */
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_X2      =   ( 0x02 << 5 ),          /*!<  BME680 Temperature Oversampling x2                               */
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_X4      =   ( 0x03 << 5 ),          /*!<  BME680 Temperature Oversampling x4                               */
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_X8      =   ( 0x04 << 5 ),          /*!<  BME680 Temperature Oversampling x8                               */
    BME680_OSRS_T_TEMPERATURE_OVERSAMPLING_X16     =   ( 0x05 << 5 )           /*!<  BME680 Temperature Oversampling x16                              */
} BME680_ctrl_meas_temperature_oversampling_t;


/**
  * @brief   OVER SAMPLING SETTING. PRESSURE DATA. Pressure oversampling settings.
  */
typedef enum
{
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_MASK    =   ( 0x1C << 2 ),          /*!<  BME680 Pressure Oversampling Mask                             */
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_SKIPPED =   ( 0x00 << 2 ),          /*!<  BME680 Pressure Oversampling skipped ( output set to 0x8000 ) */
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_X1      =   ( 0x01 << 2 ),          /*!<  BME680 Pressure Oversampling x1                               */
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_X2      =   ( 0x02 << 2 ),          /*!<  BME680 Pressure Oversampling x2                               */
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_X4      =   ( 0x03 << 2 ),          /*!<  BME680 Pressure Oversampling x4                               */
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_X8      =   ( 0x04 << 2 ),          /*!<  BME680 Pressure Oversampling x8                               */
    BME680_OSRS_P_PRESSURE_OVERSAMPLING_X16     =   ( 0x05 << 2 )           /*!<  BME680 Pressure Oversampling x16                              */
} BME680_ctrl_meas_pressure_oversampling_t;


// IIR FILTER CONTROL
/**
  * @brief   FILTER COEFFICIENT. IIR filter settings.
  */
typedef enum
{
    BME680_FILTER_COEFFICIENT_MASK              =   ( 0x07 << 2 ),          /*!<  BME680 Filter Coefficient Mask                                */
    BME680_FILTER_COEFFICIENT_0                 =   ( 0x00 << 2 ),          /*!<  BME680 Filter Coefficient 0                                   */
    BME680_FILTER_COEFFICIENT_1                 =   ( 0x01 << 2 ),          /*!<  BME680 Filter Coefficient 1                                   */
    BME680_FILTER_COEFFICIENT_3                 =   ( 0x02 << 2 ),          /*!<  BME680 Filter Coefficient 3                                   */
    BME680_FILTER_COEFFICIENT_7                 =   ( 0x03 << 2 ),          /*!<  BME680 Filter Coefficient 7                                   */
    BME680_FILTER_COEFFICIENT_15                =   ( 0x04 << 2 ),          /*!<  BME680 Filter Coefficient 15                                  */
    BME680_FILTER_COEFFICIENT_31                =   ( 0x05 << 2 ),          /*!<  BME680 Filter Coefficient 31                                  */
    BME680_FILTER_COEFFICIENT_63                =   ( 0x06 << 2 ),          /*!<  BME680 Filter Coefficient 63                                  */
    BME680_FILTER_COEFFICIENT_127               =   ( 0x07 << 2 )           /*!<  BME680 Filter Coefficient 127                                 */
} BME680_config_filter_t;


// GAS CONTROL REGISTERS
/**
  * @brief   GAS SENSOR WAIT TIME. Multiplication factor.
  */
typedef enum
{
    BME680_GAS_WAIT_MULTIPLICATION_FACTOR_MASK  =   ( 0x03 << 6 ),          /*!<  BME680 Gas wait Multiplication factor Mask                    */
    BME680_GAS_WAIT_MULTIPLICATION_FACTOR_1     =   ( 0x00 << 6 ),          /*!<  BME680 Gas wait Multiplication factor 1                       */
    BME680_GAS_WAIT_MULTIPLICATION_FACTOR_4     =   ( 0x01 << 6 ),          /*!<  BME680 Gas wait Multiplication factor 4                       */
    BME680_GAS_WAIT_MULTIPLICATION_FACTOR_16    =   ( 0x02 << 6 ),          /*!<  BME680 Gas wait Multiplication factor 16                      */
    BME680_GAS_WAIT_MULTIPLICATION_FACTOR_64    =   ( 0x03 << 6 )           /*!<  BME680 Gas wait Multiplication factor 64                      */
} BME680_gas_wait_multiplication_factor_t;



/**
  * @brief   HEATER OFF.
  */
typedef enum
{
    BME680_HEAT_OFF_MASK                        =   ( 0x01 << 3 ),          /*!<  BME680 Heat off Mask                                          */
    BME680_HEAT_OFF_ENABLED                     =   ( 0x00 << 3 ),          /*!<  BME680 Turn on current injected to heater                     */
    BME680_HEAT_OFF_DISABLED                    =   ( 0x01 << 3 ),          /*!<  BME680 Turn off current injected to heater                    */
} BME680_ctrl_gas_0_heater_off_t;



/**
  * @brief   HEATER PROFILE SELECTION. Indicates index of heater set point that will be used in forced mode.
  */
typedef enum
{
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_MASK =   ( 0x0F << 0 ),          /*!<  BME680 Heater profile set-point Mask                          */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_0    =   ( 0x00 << 0 ),          /*!<  BME680 Heater profile set-point 0                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_1    =   ( 0x01 << 0 ),          /*!<  BME680 Heater profile set-point 1                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_2    =   ( 0x02 << 0 ),          /*!<  BME680 Heater profile set-point 2                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_3    =   ( 0x03 << 0 ),          /*!<  BME680 Heater profile set-point 3                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_4    =   ( 0x04 << 0 ),          /*!<  BME680 Heater profile set-point 4                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_5    =   ( 0x05 << 0 ),          /*!<  BME680 Heater profile set-point 5                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_6    =   ( 0x06 << 0 ),          /*!<  BME680 Heater profile set-point 6                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_7    =   ( 0x07 << 0 ),          /*!<  BME680 Heater profile set-point 7                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_8    =   ( 0x08 << 0 ),          /*!<  BME680 Heater profile set-point 8                             */
    BME680_NB_CONV_HEATER_PROFILE_SETPOINT_9    =   ( 0x09 << 0 )           /*!<  BME680 Heater profile set-point 9                             */
} BME680_ctrl_gas_1_nb_conv_t;


/**
  * @brief   RUN GAS.
  */
typedef enum
{
    BME680_RUN_GAS_MASK                         =   ( 0x01 << 4 ),          /*!<  BME680 Run gas Mask                                           */
    BME680_RUN_GAS_ENABLED                      =   ( 0x01 << 4 ),          /*!<  BME680 Run gas ENABLED                                        */
    BME680_RUN_GAS_DISABLED                     =   ( 0x00 << 4 )           /*!<  BME680 Run gas DISABLED                                       */
} BME680_ctrl_gas_1_run_gas_t;


// STATUS REGISTERS
/**
  * @brief   NEW DATA STATUS. The measured data are stored into the output data register at the end of each TPHG conversion phase
  *                           along with status flags and index of measurement.
  */
typedef enum
{
    BME680_NEW_DATA_MASK                        =   ( 0x01 << 7 ),          /*!<  BME680 New data Mask                                          */
    BME680_NEW_DATA_NEW                         =   ( 0x01 << 7 ),          /*!<  BME680 New data conversion                                    */
    BME680_NEW_DATA_OLD                         =   ( 0x00 << 7 )           /*!<  BME680 No New data conversion                                 */
} BME680_meas_status_0_new_data_t;


/**
  * @brief   GAS MEASURING STATUS. Measuring bit is set to '1' only during gas measurements, goes to '0' as soon as the measurement is completed
  *                                and data transfered to data registers.
  */
typedef enum
{
    BME680_GAS_MEASURING_MASK                   =   ( 0x01 << 6 ),          /*!<  BME680 Gas measuring Mask                                     */
    BME680_GAS_MEASURING_MEASURING              =   ( 0x01 << 6 ),          /*!<  BME680 Gas measuring in process                               */
    BME680_GAS_MEASURING_COMPLETED              =   ( 0x00 << 6 )           /*!<  BME680 Gas measuring is completed                             */
} BME680_meas_status_0_gas_measuring_t;


/**
  * @brief   MEASURING STATUS. Measuring bit is set to '1' whenever a conversion TPHG is running and back to '0' when the results have been transfered
  *                            to data registers.
  */
typedef enum
{
    BME680_MEASURING_MASK                       =   ( 0x01 << 5 ),          /*!<  BME680 Measuring Mask                                         */
    BME680_MEASURING_MEASURING                  =   ( 0x01 << 5 ),          /*!<  BME680 Measuring in process                                   */
    BME680_MEASURING_COMPLETED                  =   ( 0x00 << 5 )           /*!<  BME680 Measuring is completed                                 */
} BME680_meas_status_0_measuring_t;


/**
  * @brief   GAS MEASUREMENT INDEX.
  */
typedef enum
{
    BME680_GAS_MEASUREMENT_INDEX_MASK               =   ( 0x07 << 0 ),      /*!<  BME680 Gas measurement index Mask                             */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_0 =   ( 0x00 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 0              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_1 =   ( 0x01 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 1              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_2 =   ( 0x02 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 2              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_3 =   ( 0x03 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 3              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_4 =   ( 0x04 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 4              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_5 =   ( 0x05 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 5              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_6 =   ( 0x06 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 6              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_7 =   ( 0x07 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 7              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_8 =   ( 0x08 << 0 ),      /*!<  BME680 Gas measurement index profile set-point 8              */
    BME680_GAS_MEASUREMENT_INDEX_PROFILE_SETPOINT_9 =   ( 0x09 << 0 )       /*!<  BME680 Gas measurement index profile set-point 9              */
} BME680_meas_status_0_gas_measurement_index_t;


/**
  * @brief   GAS VALID STATUS. In each TPHG sequence contains a gas measurement slot, either a real one which result is used or a dummy one to keep
  *                            a constant sampling rate and predictable device timing. A real gas conversion is indicated by the gas_valid_r status
  *                            register.
  */
typedef enum
{
    BME680_GAS_VALID_R_MASK                         =   ( 0x01 << 5 ),      /*!<  BME680 Gas valid Mask                                        */
    BME680_GAS_VALID_R_MEASURING                    =   ( 0x01 << 5 ),      /*!<  BME680 Gas valid in process                                  */
    BME680_GAS_VALID_R_COMPLETED                    =   ( 0x00 << 5 )       /*!<  BME680 Gas valid is completed                                */
} BME680_gas_r_lsb_gas_valid_r_t;



/**
  * @brief   HEATER STABILITY STATUS. Heater temperature stability for target heater resistance.
  */
typedef enum
{
    BME680_HEATER_STAB_R_MASK                       =   ( 0x01 << 4 ),      /*!<  BME680 Heater temperature stability Mask                     */
    BME680_HEATER_STAB_R_IN_PROGRESS                =   ( 0x01 << 4 ),      /*!<  BME680 Heater temperature stability in process               */
    BME680_HEATER_STAB_R_COMPLETED                  =   ( 0x00 << 4 )       /*!<  BME680 Heater temperature stability is completed             */
} BME680_gas_r_lsb_heater_stab_r_t;








#ifndef BME680_VECTOR_STRUCT_H
#define BME680_VECTOR_STRUCT_H
typedef struct
{
    // Pressure data
    uint8_t  press_msb;                 /*!<  Contains the MSB part  [ 19:12 ] of the raw pressure measurement output data     */
    uint8_t  press_lsb;                 /*!<  Contains the LSB part  [ 11:4  ] of the raw pressure measurement output data     */
    uint8_t  press_xlsb;                /*!<  Contains the XLSB part [  3:0  ] of the raw pressure measurement output data.
                                              Contents depend on pressure resolution controlled by oversampling setting.       */
    // Temperature data
    uint8_t  temp_msb;                  /*!<  Contains the MSB part  [ 19:12 ] of the raw temperature measurement output data  */
    uint8_t  temp_lsb;                  /*!<  Contains the LSB part  [ 11:4  ] of the raw temperature measurement output data  */
    uint8_t  temp_xlsb;                 /*!<  Contains the XLSB part [  3:0  ] of the raw temperature measurement output data.
                                              Contents depend on temperature resolution controlled by oversampling setting.    */
    // Humidity data
    uint8_t  hum_msb;                   /*!<  Contains the MSB part  [ 15:8 ] of the raw humidity measurement output data      */
    uint8_t  hum_lsb;                   /*!<  Contains the LSB part  [  7:0 ] of the raw humidity measurement output data      */

    // Gas resistance data
    uint8_t  gas_r_msb;                 /*!<  Contains the MSB part gas resistance [ 9:2 ] of the raw gas resistance           */
    uint8_t  gas_r_lsb;                 /*!<  Contains the LSB part gas resistance [ 1:0 ] of the raw gas resistance           */
    uint16_t gas_r;                     /*!<  Gas resistance data                                                              */

    // Gas resistance range
    uint8_t  gas_range_r;               /*!<  Contains ADC range of measured gas resistance                                    */


} BME680_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    BME680_SUCCESS     =       0,
    BME680_FAILURE     =       1
} BME680_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
BME680_status_t  BME680_Init                        ( I2C_parameters_t myI2Cparameters );

/** It configures the device: resolution and heater.
  */
BME680_status_t  BME680_Conf                        ( I2C_parameters_t myI2Cparameters, BME680_measurement_resolution_t myResolution, BME680_heater_t myHeater );

/** It performs a software reset.
  */
BME680_status_t  BME680_SoftReset                   ( I2C_parameters_t myI2Cparameters );

/** It gets the electronic serial number.
  */
BME680_status_t  BME680_GetElectronicSerialNumber   ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* mySerialNumber );

/** It gets the firmware revision.
  */
BME680_status_t  BME680_GetFirmwareRevision         ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myFirmwareRevision );

/** It sets the heater current.
*/
BME680_status_t  BME680_SetHeaterCurrent            ( I2C_parameters_t myI2Cparameters, uint8_t myHeaterCurrent );

/** It performs a new temperature measurement.
  */
BME680_status_t  BME680_TriggerTemperature          ( I2C_parameters_t myI2Cparameters, BME680_master_mode_t myMode );

/** It read the temperature.
  */
BME680_status_t  BME680_ReadTemperature             ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It reads the raw data from temperature.
  */
BME680_status_t  BME680_ReadRawTemperature          ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It reads the raw temperature data after a relative humidity measurement was done.
  */
BME680_status_t  BME680_ReadRawTemperatureFromRH    ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It reads the temperature after a relative humidity measurement was done.
  */
BME680_status_t  BME680_ReadTemperatureFromRH       ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myTemperature );

/** It performs a new relative humidity measurement.
  */
BME680_status_t  BME680_TriggerHumidity             ( I2C_parameters_t myI2Cparameters, BME680_master_mode_t myMode );

/** It reads the relative humidity.
  */
BME680_status_t  BME680_ReadHumidity                ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myHumidity );

/** It reads the raw data from relative humidity.
  */
BME680_status_t  BME680_ReadRawHumidity             ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myHumidity );

/** It gets the battery status.
  */
BME680_status_t  BME680_GetBatteryStatus            ( I2C_parameters_t myI2Cparameters, BME680_vector_data_t* myBatteryStatus );


#ifdef __cplusplus
}
#endif

#endif /* BME680_H */
