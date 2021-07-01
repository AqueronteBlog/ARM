/**
 * @brief       MicroForce_FMA.h
 * @details     MicroForce Sensors, Compensated/Amplified.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021    The ORIGIN
 * @pre         N/A.
 * @warning     This driver only supports SPI communication: FMAMSDXX005WCSC3,FMAMSDXX015WCSC3 and FMAMSDXX025WCSC3.
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */
#ifndef MicroForce_FMA_H_
#define MicroForce_FMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/**
  * @brief   STATUS BITS
  */
typedef enum{
    MicroForce_FMA_STATUS_BITS_MASK                   =   ( 0b11 << 6 ),      /*!<   STATUS BITS mask                 */
    MicroForce_FMA_STATUS_BITS_NORMAL_OPERATION       =   ( 0b00 << 6 ),      /*!<   Normal operation, valid data     */
    MicroForce_FMA_STATUS_BITS_DEVICE_IN_COMMAND_MODE =   ( 0b01 << 6 ),      /*!<   Device in command mode           */
    MicroForce_FMA_STATUS_BITS_STALE_DATA             =   ( 0b10 << 6 ),      /*!<   Stale data                       */
    MicroForce_FMA_STATUS_BITS_DIAGNOSTIC_CONDITION   =   ( 0b11 << 6 )       /*!<   Diagnostic condition             */
} MicroForce_FMA_status_bits_t;


/**
  * @brief   TRANSFER FUCNTION
  */
typedef enum{
    MicroForce_FMA_TRANSFER_FUNCTION_10_TO_90         =   0U,                 /*!<   Tranfer function A: 10% to 90%   */
    MicroForce_FMA_TRANSFER_FUNCTION_20_TO_80         =   1U                  /*!<   Tranfer function C: 20% to 80%   */
} MicroForce_FMA_transfer_function_t;


/**
  * @brief   FORCE RANGE
  */

#define FMA_FORCE_RANGE_5_N     5U                 /*!<   Force range:  5N                 */
#define FMA_FORCE_RANGE_15_N   15U                 /*!<   Force range: 15N                 */
#define FMA_FORCE_RANGE_25_N   25U                 /*!<   Force range: 25N                 */





#ifndef MicroForce_FMA_STRUCT_H
#define MicroForce_FMA_STRUCT_H
typedef struct{
    MicroForce_FMA_status_bits_t status_bits;
} MicroForce_FMA_status_bits_data_t;


typedef struct{
    uint16_t  raw_bridge_data;
    float     bridge_data;                                              /*!<   Force data in Newton (N)           */
} MicroForce_FMA_bridge_data_t;


typedef struct{
    uint8_t   raw_8bit_temperature;
    uint16_t  raw_11bit_temperature;
    float     temperature_data;                                         /*!<   Temperature data in Celsius degree */
} MicroForce_FMA_temperature_data_t;


/* User's data   */
typedef struct{
    MicroForce_FMA_transfer_function_t  transfer_function;              /*!<   Transfer function. Calibration     */
    uint8_t                             force_range;                    /*!<   Force Range                        */

    MicroForce_FMA_status_bits_data_t   status;                         /*!<   Status bits. Device condition      */

    MicroForce_FMA_bridge_data_t        force;                          /*!<   Force data                         */
    MicroForce_FMA_temperature_data_t   temperature;                    /*!<   Temperature data                   */  
} MicroForce_FMA_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MicroForce_FMA_SUCCESS     =       0,
    MicroForce_FMA_FAILURE     =       1
} MicroForce_FMA_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
MicroForce_FMA_status_t  MicroForce_FMA_Init                      ( SPI_parameters_t mySPIparameters                                                                                                    );

/** It gets the raw force data.
    */
MicroForce_FMA_status_t  MicroForce_FMA_GetRawForce               ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint16_t* myRawBridgeData                            );

/** It calculates the force data in Newton (N).
    */
float                    MicroForce_FMA_CalculateForce            ( MicroForce_FMA_transfer_function_t myCalibration, uint8_t myForceRange, uint16_t myRawBridgeData                                    );

/** It gets the raw 8-bit temperature.
    */
MicroForce_FMA_status_t  MicroForce_FMA_GetRaw8bitTemperature     ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint8_t* myRaw8bitTemp                               );

/** It gets the raw 11-bit temperature.
    */
MicroForce_FMA_status_t  MicroForce_FMA_GetRaw11bitTemperature    ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint16_t* myRaw11bitTemp                             );

/** It calculates the 8-bit temperature in Celsius degree.
    */
float                    MicroForce_FMA_Calculate8bitTemperature  ( uint8_t myRawTemperature                                                                                                            );

/** It calculates the 11-bit temperature in Celsius degree.
    */
float                    MicroForce_FMA_Calculate11bitTemperature ( uint16_t myRawTemperature                                                                                                           );

/** It gets the all raw data ( bridge data and 11-bit temperature ).
    */
MicroForce_FMA_status_t  MicroForce_FMA_GetAllRawData             ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint16_t* myRawBridgeData, uint16_t* myRaw11bitTemp  );


#ifdef __cplusplus
}
#endif

#endif /* MicroForce_FMA_H_ */
