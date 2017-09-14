/**
 * @brief       HX711.h
 * @details     24-Bit Analog-to-Digital Converter (ADC) for Weigh Scales.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017    The ORIGIN
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
} HX711_channel_gain_t;


/**
      * @brief   READY/BUSY DATA
      */
typedef enum
{
    HX711_DATA_BUSY         =   0,              /*!<  HX711 data is NOT ready to be read.                                */
    HX711_DATA_READY        =   1               /*!<  HX711 data is ready to be read.                                    */
} HX711_data_output_status_t;



/**
  * @brief   SCALE
  */
typedef enum
{
    HX711_SCALE_kg          =   0,              /*!<  HX711 Scale in kg.                                                 */
    HX711_SCALE_g           =   1,              /*!<  HX711 Scale in  g.                                                 */
    HX711_SCALE_mg          =   2,              /*!<  HX711 Scale in mg.                                                 */
    HX711_SCALE_ug          =   3               /*!<  HX711 Scale in ug.                                                 */
} HX711_scale_t;




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
    uint32_t PD_SCK;
} HX711_pins_t;


/**
  * @brief   INTERNAL CONSTANTS
  */
#define HX711_PIN_HIGH           0x01               /*!<   Pin 'HIGH'                                                       */
#define HX711_PIN_LOW            0x00               /*!<   Pin 'LOW'                                                        */

typedef enum
{
    HX711_SUCCESS     =       0,
    HX711_FAILURE     =       1,
} HX711_status_t;


HX711_channel_gain_t    _HX711_CHANNEL_GAIN;
HX711_scale_t           _HX711_SCALE;
float                   _HX711_USER_CALIBATED_MASS;


/**
  * @brief   FUNCTION PROTOTYPES
  */

/** It configures the pins to use.
     */
HX711_pins_t    HX711_Init                          ( uint32_t myDOUT, uint32_t myPD_SCK );

/** It performs an internal reset.
     */
HX711_status_t  HX711_Reset                         ( HX711_pins_t myPins );

/** It puts the device into power-down mode.
 */
HX711_status_t  HX711_PowerDown                     ( HX711_pins_t myPins );

/** It sets both the channel and the gain for the next measurement.
 */
HX711_status_t  HX711_SetChannelAndGain             ( HX711_pins_t myPins, HX711_channel_gain_t myChannel_Gain );

/** It gets both the channel and the gain for the current measurement.
 */
HX711_channel_gain_t  HX711_GetChannelAndGain       ( void );

/** It reads raw data from the device.
 */
HX711_status_t  HX711_ReadRawData                   ( HX711_pins_t myPins, HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage );

/** It reads raw data with an user-specified calibrated mass.
 */
HX711_status_t  HX711_ReadData_WithCalibratedMass   ( HX711_pins_t myPins, HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage );

/** It reads raw data without any mass.
 */
HX711_status_t  HX711_ReadData_WithoutMass          ( HX711_pins_t myPins, HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage );

/** It reads raw data without any mass after the system is calibrated.
 */
HX711_status_t  HX711_SetAutoTare                   ( HX711_pins_t myPins, HX711_channel_gain_t myChannel_Gain, float myCalibratedMass, HX711_scale_t myScaleCalibratedMass, Vector_count_t* myNewRawData, float myTime );

/** It sets a tare weight manually.
 */
Vector_count_t  HX711_SetManualTare                 ( float myTareWeight );

/** It calculates scaled data.
 */
Vector_mass_t  HX711_CalculateMass                  ( Vector_count_t* myNewRawData, float myCalibratedMass, HX711_scale_t myScaleCalibratedMass );

/** It calculates voltage data.
 */
Vector_voltage_t  HX711_CalculateVoltage            ( Vector_count_t* myNewRawData, float myVoltageReference );
