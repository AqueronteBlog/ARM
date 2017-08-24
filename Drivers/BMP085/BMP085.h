/**
 * @brief       BMP085.h
 * @details     Digital pressure sensor.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum{
    BMP085_ADDRESS     =   0x77
} BMP085_address_t;


/**
  * @brief   CALIBRATION COEFFICIENTS
  */
#define BMP085_AC1_MSB                  0xAA        /*!<   MSB AC1 coefficient                                          */
#define BMP085_AC1_LSB                  0xAB        /*!<   LSB AC1 coefficient                                          */
#define BMP085_AC2_MSB                  0xAC        /*!<   MSB AC2 coefficient                                          */
#define BMP085_AC2_LSB                  0xAD        /*!<   LSB AC2 coefficient                                          */
#define BMP085_AC3_MSB                  0xAE        /*!<   MSB AC3 coefficient                                          */
#define BMP085_AC3_LSB                  0xAF        /*!<   LSB AC3 coefficient                                          */
#define BMP085_AC4_MSB                  0xB0        /*!<   MSB AC4 coefficient                                          */
#define BMP085_AC4_LSB                  0xB1        /*!<   LSB AC4 coefficient                                          */
#define BMP085_AC5_MSB                  0xB2        /*!<   MSB AC5 coefficient                                          */
#define BMP085_AC5_LSB                  0xB3        /*!<   LSB AC5 coefficient                                          */
#define BMP085_AC6_MSB                  0xB4        /*!<   MSB AC6 coefficient                                          */
#define BMP085_AC6_LSB                  0xB5        /*!<   LSB AC6 coefficient                                          */
#define BMP085_B1_MSB                   0xB6        /*!<   MSB B1 coefficient                                           */
#define BMP085_B1_LSB                   0xB7        /*!<   LSB B1 coefficient                                           */
#define BMP085_B2_MSB                   0xB8        /*!<   MSB B2 coefficient                                           */
#define BMP085_B2_LSB                   0xB9        /*!<   LSB B2 coefficient                                           */
#define BMP085_MB_MSB                   0xBA        /*!<   MSB MB coefficient                                           */
#define BMP085_MB_LSB                   0xBB        /*!<   LSB MB coefficient                                           */
#define BMP085_MC_MSB                   0xBC        /*!<   MSB MC coefficient                                           */
#define BMP085_MC_LSB                   0xBD        /*!<   LSB MC coefficient                                           */
#define BMP085_MD_MSB                   0xBE        /*!<   MSB MD coefficient                                           */
#define BMP085_MD_LSB                   0xBF        /*!<   LSB MD coefficient                                           */


/**
  * @brief   REGISTERS MAP
  */
#define BMP085_CONTROL                  0xF4        /*!<   Control register                                             */



/* Commands Registers */
/**
  * @brief   TEMPERATURE
  */
#define BMP085_TRIGGER_TEMPERATURE      0x2E        /*!<   Trigger a new Temperature measurement                        */
#define BMP085_READ_TEMPERATURE         0xF6        /*!<   Read Temperature                                             */

/* Commands Registers */
/**
  * @brief   PRESSURE
  */
#define BMP085_TRIGGER_PRESSURE         0x34        /*!<   Trigger a new Pressure measurement                           */
#define BMP085_READ_PRESSURE            0xF6        /*!<   Read Pressure                                                */

typedef enum{
    PRESSURE_ULTRA_LOW_POWER_MODE     =   0,        /*!<  Pressure: Ultra low power mode.                                */
    PRESSURE_STANDARD_MODE            =   1,        /*!<  Pressure: Standard mode.                                       */
    PRESSURE_HIGH_RESOLUTION_MODE     =   2,        /*!<  Pressure: High resolution mode.                                */
    PRESSURE_ULTRA_HIGH_RES_MODE      =   3         /*!<  Pressure: Ultra high resolution mode.                          */
} BMP085_pressure_osrs_t;




#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct{
    int16_t  AC1;
    int16_t  AC2;
    int16_t  AC3;
    uint16_t AC4;
    uint16_t AC5;
    uint16_t AC6;
    int16_t  B1;
    int16_t  B2;
    int16_t  MB;
    int16_t  MC;
    int16_t  MD;
} Vector_cal_coeff_t;


typedef struct{
    int16_t Temperature;
} Vector_temp_f;

typedef struct{
    int32_t Pressure;
} Vector_pressure_f;
#endif


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    BMP085_SUCCESS     =       0,
    BMP085_FAILURE     =       1
} BMP085_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
BMP085_status_t  BMP085_GetCalibrationCoefficients    ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_cal_coeff_t* myCalCoeff );
BMP085_status_t  BMP085_TriggerTemperature            ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR );
BMP085_status_t  BMP085_ReadRawTemperature            ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_temp_f* myRawTemperature );
BMP085_status_t  BMP085_ReadCompensatedTemperature    ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_temp_f* myTrueTemperature );
BMP085_status_t  BMP085_TriggerPressure               ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, BMP085_pressure_osrs_t myResolution );
BMP085_status_t  BMP085_ReadRawPressure               ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_pressure_f* myRawPressure );
BMP085_status_t  BMP085_ReadCompensatedPressure       ( NRF_TWI_Type* myinstance, BMP085_address_t ADDR, Vector_pressure_f* myTruePressure );
