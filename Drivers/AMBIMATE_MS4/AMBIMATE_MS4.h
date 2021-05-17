/**
 * @brief       AMBIMATE_MS4.h
 * @details     CO2, humidity and temperature sensor.
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
  AMBIMATE_MS4_ADDRESS     =   0x61               /*!<   AMBIMATE_MS4 ADDR              */
} AMBIMATE_MS4_address_t;



/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
  AMBIMATE_MS4_TRIGGERS_CONTINUOUS_MEASUREMENT       =   0x0010,   /*!<  Triggers continuous measurement. Ambient pressure is optional   */
  AMBIMATE_MS4_STOP_CONTINUOUS_MEASUREMENT           =   0x0104,   /*!<  Stop continuous measurement                                     */
  AMBIMATE_MS4_SET_MEASUREMENT_INTERVAL              =   0x4600,   /*!<  Set measurement interval for continuous measurement mode        */
  AMBIMATE_MS4_GET_DATA_READY_STATUS                 =   0x0202,   /*!<  Data ready status                                               */
  AMBIMATE_MS4_READ_MEASUREMENT                      =   0x0300,   /*!<  Reads a single measurement of C02 concentration                 */
  AMBIMATE_MS4_CONTINUOUS_AUTOMATIC_SELF_CALIBRATION =   0x5306,   /*!<  Continuous automatic self-calibration can be (de-)activated     */
  AMBIMATE_MS4_SET_FORCED_RECALIBRATION              =   0x5204,   /*!<  Forced recalibration (FRC)                                      */
  AMBIMATE_MS4_SET_TEMPERATURE_OFFSET                =   0x5403,   /*!<  Temperature offset                                              */
  AMBIMATE_MS4_SET_ALTITUDE_COMPENSATION             =   0x5102,   /*!<  Altitude compensation                                           */
  AMBIMATE_MS4_FIRMWARE_VERSION                      =   0xD100,   /*!<  Firmware version                                                */
  AMBIMATE_MS4_SOFTRESET                             =   0xD304    /*!<  Software reset: Restart the sensor                              */
} AMBIMATE_MS4_command_registers_t;



/**
  * @brief   GET DATA READY STATUS.
  *           NOTE: N/A.
  */
/* BIT <0>
 *    NOTE: N/A.
 */
typedef enum
{
    GET_READY_STATUS_BIT_MASK           =   ( 1U << 0U ),   /*!<  BIT mask                                                        */
    GET_READY_STATUS_BIT_DATA_NO_READY  =   ( 0U << 0U ),   /*!<  Measurement is not ready to be read from the sensor             */
    GET_READY_STATUS_BIT_DATA_READY     =   ( 1U << 0U )    /*!<  Measurement is ready to be read from the sensor                 */
} AMBIMATE_MS4_get_ready_status_bit_t;


/**
  * @brief   CONTINUOUS AUTOMATIC SELF CALIBRATION.
  *           NOTE: N/A.
  */
/* ASC <0>
 *    NOTE: N/A.
 */
typedef enum
{
    CONTINUOUS_AUTOMATIC_SELF_CALIBRATION_ASC_MASK        =   ( 1U << 0U ),   /*!<  ASC mask                                                        */
    CONTINUOUS_AUTOMATIC_SELF_CALIBRATION_ASC_DEACTIVATE  =   ( 0U << 0U ),   /*!<  Deactivate continuous ASC                                       */
    CONTINUOUS_AUTOMATIC_SELF_CALIBRATION_ASC_ACTIVATE    =   ( 1U << 0U )    /*!<  Activate continuous ASC                                         */
} AMBIMATE_MS4_continuous_auto_selfcal_t;


/**
  * @brief   CRC-8.
  *           NOTE: Polynomial:     0x31 (x^8 + x^5 + x^4 + 1)
  *                 Initialization: 0xFF
  *                 Final XOR:      0x00.
  */
#define AMBIMATE_MS4_CRC8_POLYNOMIAL       0x31                                      /*!<  AMBIMATE_MS4 CRC-8: Polynomial                                         */
#define AMBIMATE_MS4_CRC8_INITIALIZATION   0xFF                                      /*!<  AMBIMATE_MS4 CRC-8: Initialization                                     */
#define AMBIMATE_MS4_CRC8_FINAL_XOR        0x00                                      /*!<  AMBIMATE_MS4 CRC-8: Final XOR                                          */






#ifndef AMBIMATE_MS4_VECTOR_STRUCT_H
#define AMBIMATE_MS4_VECTOR_STRUCT_H
/* Firmware version  */
typedef struct
{
  uint8_t  version_major;  
  uint8_t  version_minor;  
} AMBIMATE_MS4_fw_version_t;


/* Raw measurement data  */
typedef struct
{
  uint8_t  co2_mmsb;  
  uint8_t  co2_mlsb;  
  uint8_t  co2_mmsb_mlsb_crc;

  uint8_t  co2_lmsb;  
  uint8_t  co2_llsb;  
  uint8_t  co2_lmsb_llsb_crc;

  uint8_t  temperature_mmsb;  
  uint8_t  temperature_mlsb;  
  uint8_t  temperature_mmsb_mlsb_crc;

  uint8_t  temperature_lmsb;  
  uint8_t  temperature_llsb;  
  uint8_t  temperature_lmsb_llsb_crc;

  uint8_t  humidity_mmsb;  
  uint8_t  humidity_mlsb;  
  uint8_t  humidity_mmsb_mlsb_crc;

  uint8_t  humidity_lmsb;  
  uint8_t  humidity_llsb;  
  uint8_t  humidity_lmsb_llsb_crc;
} AMBIMATE_MS4_raw_output_data_t;


/* Measurement processed data  */
typedef struct
{
  float  co2;  
  float  temperature; 
  float  humidity;  
} AMBIMATE_MS4_processed_data_t;


/* Measurement data: Raw and processed data  */
typedef struct
{
  AMBIMATE_MS4_raw_output_data_t raw;  
  AMBIMATE_MS4_processed_data_t  processed;  
} AMBIMATE_MS4_output_data_t;




/* USER: User's variables  */
typedef struct
{
  /* Output data   */
  AMBIMATE_MS4_output_data_t             data;                   /*< Data (processed and raw): CO2, Temperature and Humidity                   */

  /* Pressure compensation   */
  uint16_t                        pressure_compensation;  /*< 0 (desactivates pressure compensation) or [700 - 1400]. Pressure in mBar  */
  
  /* Set measurement interval  */
  uint16_t                        measurement_interval;   /*< [2 - 1800]. Interval in seconds                                           */
  
  /* Status  */
  AMBIMATE_MS4_get_ready_status_bit_t    status;                 /*< Measurement is ready to be read from the sensor                           */
  
  /* (De-)Activate automatic self-calibration  */
  AMBIMATE_MS4_continuous_auto_selfcal_t asc;                    /*< Continuos automatic self-calibration                                      */
  
  /* Forced recalibration  */
  uint16_t                        frc;                    /*< Value of C02 concentration in ppm                                         */
  
  /* Set temperature offset  */
  uint16_t                        temperature_offset;     /*< Value of Temperature offset. [°C x 100]. One tick corresponds to 0.01 C   */
  
  /* Altitude compensation  */
  uint16_t                        altitude_compensation;  /*< Altitude compensation value. Height over sea level in [m] above 0         */
  
  /* Firmware version  */
  AMBIMATE_MS4_fw_version_t              firmware;               /*< Firmware version                                                          */
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
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Init                          ( I2C_parameters_t myI2Cparameters                                        );

/** It triggers continuous measurement with or without ambient pressure compensation.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_TriggerContinuousMeasurement  ( I2C_parameters_t myI2Cparameters, uint16_t pressure_compensation        );

/** It stops the continuous measurement.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_StopContinuousMeasurement     ( I2C_parameters_t myI2Cparameters                                        );

/** It sets the measurement interval.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_SetMeasurementInterval        ( I2C_parameters_t myI2Cparameters, uint16_t measurement_interval         );

/** It gets the measurement interval.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetMeasurementInterval        ( I2C_parameters_t myI2Cparameters, uint16_t* measurement_interval        );

/** It gets the status when the data is ready to be read.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetDataReadyStatus            ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_get_ready_status_bit_t* status  );

/** It gets all the raw data.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_ReadRawMeasurement            ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_raw_output_data_t* raw_data     );

/** It gets all the data.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_ReadMeasurement               ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_output_data_t* data             );

/** It enables/disables the continuous automatic self-calibration.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_SetContinuousASC              ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_continuous_auto_selfcal_t asc   );

/** It gets the continuous automatic self-calibration bit.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetContinuousASC              ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_continuous_auto_selfcal_t* asc  );

/** It sets the forced recalibration value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_SetForcedRecalibrationValue   ( I2C_parameters_t myI2Cparameters, uint16_t frc                          );

/** It gets the forced recalibration value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetForcedRecalibrationValue   ( I2C_parameters_t myI2Cparameters, uint16_t* frc                         );

/** It sets the temperature offset value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_SetTemperatureOffsetValue     ( I2C_parameters_t myI2Cparameters, uint16_t temp_offset                  );

/** It gets the temperature offset value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetTemperatureOffsetValue     ( I2C_parameters_t myI2Cparameters, uint16_t* temp_offset                 );

/** It sets the altitude compensation value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_SetAltitudeCompensationValue  ( I2C_parameters_t myI2Cparameters, uint16_t alt_comp                     );

/** It gets the altitude compensation value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetAltitudeCompensationValue  ( I2C_parameters_t myI2Cparameters, uint16_t* alt_comp                    );

/** It gets the firmware version value.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetFirmwareVersion            ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_fw_version_t* fw                );

/** It performs a software reset.
  */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_SoftReset                     ( I2C_parameters_t myI2Cparameters                                        );

/** It calculates the I2C checksum calculation (CRC-8).
  */
uint8_t         AMBIMATE_MS4_CalculateI2C_CRC8             ( uint16_t seed                                                           );



#ifdef __cplusplus
}
#endif

#endif /* AMBIMATE_MS4_H */
