/**
 * @brief       SCD30.h
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

#ifndef SCD30_H_
#define SCD30_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "i2c.h"



/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  SCD30_ADDRESS     =   0x61               /*!<   SCD30 ADDR              */
} SCD30_address_t;



/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
  SCD30_TRIGGERS_CONTINUOUS_MEASUREMENT       =   0x0010,   /*!<  Triggers continuous measurement. Ambient pressure is optional   */
  SCD30_STOP_CONTINUOUS_MEASUREMENT           =   0x0104,   /*!<  Stop continuous measurement                                     */
  SCD30_SET_MEASUREMENT_INTERVAL              =   0x4600,   /*!<  Set measurement interval for continuous measurement mode        */
  SCD30_GET_DATA_READY_STATUS                 =   0x0202,   /*!<  Data ready status                                               */
  SCD30_READ_MEASUREMENT                      =   0x0300,   /*!<  Reads a single measurement of C02 concentration                 */
  SCD30_CONTINUOUS_AUTOMATIC_SELF_CALIBRATION =   0x5306,   /*!<  Continuous automatic self-calibration can be (de-)activated     */
  SCD30_SET_FORCED_RECALIBRATION              =   0x5204,   /*!<  Forced recalibration (FRC)                                      */
  SCD30_SET_TEMPERATURE_OFFSET                =   0x5403,   /*!<  Temperature offset                                              */
  SCD30_SET_ALTITUDE_COMPENSATION             =   0x5102,   /*!<  Altitude compensation                                           */
  SCD30_FIRMWARE_VERSION                      =   0xD100,   /*!<  Firmware version                                                */
  SCD30_SOFTRESET                             =   0xD304    /*!<  Software reset: Restart the sensor                              */
} SCD30_command_registers_t;



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
} SCD30_get_ready_status_bit_t;


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
} SCD30_continuous_auto_selfcal_t;





#ifndef SCD30_VECTOR_STRUCT_H
#define SCD30_VECTOR_STRUCT_H
/* Firmware version  */
typedef struct
{
  uint8_t  version_major;  
  uint8_t  version_minor;  
} SCD30_fw_version_t;


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
} SCD30_raw_output_data_t;


/* Measurement data  */
typedef struct
{
  float  co2;  
  float  temperature; 
  float  humidity;  
} SCD30_output_data_t;




/* USER: User's variables  */
typedef struct
{
  /* Raw output data   */
  SCD30_raw_output_data_t         raw_data;               /*< Raw data                                                                  */

  /* Output data   */
  SCD30_output_data_t             data;                   /*< Data: CO2, Temperature and Humidity                                       */

  /* Pressure compensation   */
  uint16_t                        pressure_compensation;  /*< 0 (desactivates pressure compensation) or [700 - 1400]. Pressure in mBar  */
  
  /* Set measurement interval  */
  uint16_t                        measurement_interval;   /*< [2 - 1800]. Interval in seconds                                           */
  
  /* Status  */
  SCD30_get_ready_status_bit_t    status;                 /*< Measurement is ready to be read from the sensor                           */
  
  /* (De-)Activate automatic self-calibration  */
  SCD30_continuous_auto_selfcal_t asc;                    /*< Measurement is ready to be read from the sensor                           */
  
  /* Forced recalibration  */
  uint16_t                        frc;                    /*< Value of C02 concentration in ppm                                         */
  
  /* Set temperature offset  */
  uint16_t                        temperature_offset;     /*< Value of Temperature offset. [°C x 100]. One tick corresponds to 0.01 C   */
  
  /* Altitude compensation  */
  uint16_t                        altitude_compensation;  /*< Altitude compensation value. Height over sea level in [m] above 0         */
  
  /* Firmware version  */
  SCD30_fw_version_t              firmware;               /*< Firmware version                                                          */
} SCD30_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SCD30_SUCCESS     =       0,
    SCD30_FAILURE     =       1
} SCD30_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SCD30_status_t  SCD30_Init                          ( I2C_parameters_t myI2Cparameters                                  );

/** It triggers continuous measurement with or without ambient pressure compensation.
  */
SCD30_status_t  SCD30_TriggerContinuousMeasurement  ( I2C_parameters_t myI2Cparameters, uint16_t pressure_compensation  );

/** It stops the continuous measurement.
  */
SCD30_status_t  SCD30_StopContinuousMeasurement     ( I2C_parameters_t myI2Cparameters                                  );

/** It sets the measurement interval.
  */
SCD30_status_t  SCD30_SetMeasurementInterval        ( I2C_parameters_t myI2Cparameters, uint16_t measurement_interval   );

/** It sets the measurement interval.
  */
SCD30_status_t  SCD30_SetMeasurementInterval        ( I2C_parameters_t myI2Cparameters, uint16_t measurement_interval   );

/** It gets the measurement interval.
  */
SCD30_status_t  SCD30_GetMeasurementInterval        ( I2C_parameters_t myI2Cparameters, uint16_t* measurement_interval  );



#ifdef __cplusplus
}
#endif

#endif /* SCD30_H */
