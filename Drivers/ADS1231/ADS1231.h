/**
 * @brief       ADS1231.h
 * @details     24-Bit Analog-to-Digital Converter for Bridge Sensors.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/September/2017
 * @version     18/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "nrf.h"
#include "nrf_delay.h"


/**
  * @brief   CHANNELS & GAIN
  */
typedef enum
{
    CHANNEL_A_GAIN_128      =   0,              /*!<  Channel A 128 Gain.                                               */
    CHANNEL_B_GAIN_32       =   1,              /*!<  Channel B 32 Gain.                                                */
    CHANNEL_A_GAIN_64       =   2               /*!<  Channel A 64 Gain.                                                */
} ADS1231_channel_gain_t;


/**
      * @brief   READY/BUSY DATA
      */
typedef enum
{
    ADS1231_DATA_BUSY         =   0,              /*!<  ADS1231 data is NOT ready to be read.                                */
    ADS1231_DATA_READY        =   1               /*!<  ADS1231 data is ready to be read.                                    */
} ADS1231_data_output_status_t;



/**
  * @brief   SCALE
  */
typedef enum
{
    ADS1231_SCALE_kg          =   0,              /*!<  ADS1231 Scale in kg.                                                 */
    ADS1231_SCALE_g           =   1,              /*!<  ADS1231 Scale in  g.                                                 */
    ADS1231_SCALE_mg          =   2,              /*!<  ADS1231 Scale in mg.                                                 */
    ADS1231_SCALE_ug          =   3               /*!<  ADS1231 Scale in ug.                                                 */
} ADS1231_scale_t;




#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct
{
    float myRawValue_WithCalibratedMass;
    float myRawValue_WithoutCalibratedMass;
    float myRawValue_TareWeight;
    uint32_t myRawValue;
} Vector_count_t;

typedef struct
{
    float myMass;
} Vector_mass_t;

typedef struct
{
    float myVoltage;
} Vector_voltage_t;
#endif


/**
  * @brief   AVAILABLE PINS
  */
typedef struct
{
    uint32_t DOUT;
    uint32_t SCLK;
} ADS1231_pins_t;


/**
  * @brief   INTERNAL CONSTANTS
  */
#define ADS1231_PIN_HIGH           0x01               /*!<   Pin 'HIGH'                                                       */
#define ADS1231_PIN_LOW            0x00               /*!<   Pin 'LOW'                                                        */

typedef enum
{
    ADS1231_SUCCESS     =       0,
    ADS1231_FAILURE     =       1,
} ADS1231_status_t;


ADS1231_channel_gain_t    _ADS1231_CHANNEL_GAIN;
ADS1231_scale_t           _ADS1231_SCALE;
float                   _ADS1231_USER_CALIBATED_MASS;


/**
  * @brief   FUNCTION PROTOTYPES
  */

/** It configures the pins to use.
     */
ADS1231_pins_t    ADS1231_Init                          ( uint32_t myDOUT, uint32_t mySCLK );

/** It performs an internal reset.
     */
ADS1231_status_t  ADS1231_Reset                         ( ADS1231_pins_t myPins );

/** It puts the device into power-down mode.
 */
ADS1231_status_t  ADS1231_PowerDown                     ( ADS1231_pins_t myPins );

/** It reads raw data from the device.
 */
ADS1231_status_t  ADS1231_ReadRawData                   ( ADS1231_pins_t myPins, Vector_count_t* myNewRawData, uint32_t myAverage );

/** It reads raw data with an user-specified calibrated mass.
 */
ADS1231_status_t  ADS1231_ReadData_WithCalibratedMass   ( ADS1231_pins_t myPins, Vector_count_t* myNewRawData, uint32_t myAverage );

/** It reads raw data without any mass.
 */
ADS1231_status_t  ADS1231_ReadData_WithoutMass          ( ADS1231_pins_t myPins, Vector_count_t* myNewRawData, uint32_t myAverage );

/** It reads raw data without any mass after the system is calibrated.
 */
ADS1231_status_t  ADS1231_SetAutoTare                   ( ADS1231_pins_t myPins, float myCalibratedMass, ADS1231_scale_t myScaleCalibratedMass, Vector_count_t* myNewRawData, float myTime );

/** It sets a tare weight manually.
 */
Vector_count_t  ADS1231_SetManualTare                   ( float myTareWeight );

/** It calculates scaled data.
 */
Vector_mass_t  ADS1231_CalculateMass                    ( Vector_count_t* myNewRawData, float myCalibratedMass, ADS1231_scale_t myScaleCalibratedMass );

/** It calculates voltage data.
 */
Vector_voltage_t  ADS1231_CalculateVoltage              ( Vector_count_t* myNewRawData, float myVoltageReference );
