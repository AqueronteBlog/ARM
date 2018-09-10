/**
 * @brief       BMP180.h
 * @details     Digital Pressure Sensor
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/September/2018
 * @version     6/September/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "i2c.h"


#ifndef BMP180_H_
#define BMP180_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    BMP180_ADDRESS     =   0b1110111            /*!<   BMP180 I2C Address           */
} BMP180_address_t;



/**
  * @brief   CALIBRATION COEFFICIENTS
  */
typedef enum
{
    BMP180_AC1_MSB      =   0xAA,               /*!<  MSB AC1 coefficient           */
    BMP180_AC1_LSB      =   0xAB,               /*!<  LSB AC1 coefficient           */
    BMP180_AC2_MSB      =   0xAC,               /*!<  MSB AC2 coefficient           */
    BMP180_AC2_LSB      =   0xAD,               /*!<  LSB AC2 coefficient           */
    BMP180_AC3_MSB      =   0xAE,               /*!<  MSB AC3 coefficient           */
    BMP180_AC3_LSB      =   0xAF,               /*!<  LSB AC3 coefficient           */
    BMP180_AC4_MSB      =   0xB0,               /*!<  MSB AC4 coefficient           */
    BMP180_AC4_LSB      =   0xB1,               /*!<  LSB AC4 coefficient           */
    BMP180_AC5_MSB      =   0xB2,               /*!<  MSB AC5 coefficient           */
    BMP180_AC5_LSB      =   0xB3,               /*!<  LSB AC5 coefficient           */
    BMP180_AC6_MSB      =   0xB4,               /*!<  MSB AC6 coefficient           */
    BMP180_AC6_LSB      =   0xB5,               /*!<  LSB AC6 coefficient           */
    BMP180_B1_MSB       =   0xB6,               /*!<  MSB B1 coefficient            */
    BMP180_B1_LSB       =   0xB7,               /*!<  LSB B1 coefficient            */
    BMP180_B2_MSB       =   0xB8,               /*!<  MSB B2 coefficient            */
    BMP180_B2_LSB       =   0xB9,               /*!<  LSB B2 coefficient            */
    BMP180_MB_MSB       =   0xBA,               /*!<  MSB MB coefficient            */
    BMP180_MB_LSB       =   0xBB,               /*!<  LSB MB coefficient            */
    BMP180_MC_MSB       =   0xBC,               /*!<  MSB MC coefficient            */
    BMP180_MC_LSB       =   0xBD,               /*!<  LSB MC coefficient            */
    BMP180_MD_MSB       =   0xBE,               /*!<  MSB MD coefficient            */
    BMP180_MD_LSB       =   0xBF                /*!<  LSB MD coefficient            */
} BMP180_calibration_coefficients_t;



/**
  * @brief   REGISTERS MAP
  */
typedef enum
{
    BMP180_OUT_XLSB     =   0xF8,               /*!<  ADC OUT XLSB                              | Reset: 0x00   */
    BMP180_OUT_LSB      =   0xF7,               /*!<  ADC OUT MSB                               | Reset: 0x00   */
    BMP180_OUT_MSB      =   0xF6,               /*!<  ADC OUT LSB                               | Reset: 0x80   */
    BMP180_CTRL_MEAS    =   0xF4,               /*!<  Measurement control ( Control register )  | Reset: 0x00   */
    BMP180_SOFT         =   0xE0,               /*!<  Software reset                            | Reset: 0x00   */
    BMP180_ID           =   0xD0                /*!<  Chip-ID                                   | Reset: 0x55   */
} BMP180_registers map_t;



/* MEASUREMENT CONTROL  */
/**
  * @brief   START OF CONVERSION ( SCO, BIT<5> )
  */
/*
    NOTE: The value of this bit stays '1' during conversion and is reset to '0' after conversion is complete ( data registers
          are filled ).
*/
typedef enum
{
    CTRL_MEAS_SCO_MASK                      =   ( 1U << 5U ),       /*!<  SCO Mask                         */
    CTRL_MEAS_SCO_CONVERSION_IN_PROGRESS    =   ( 1U << 5U ),       /*!<  SCO conversion in progress       */
    CTRL_MEAS_SCO_CONVERSION_COMPLETED      =   ( 0U << 5U )        /*!<  SCO conversion is complete       */
} BMP180_sco_t;



/**
  * @brief   CONTROLS THE OVERSAMPLING RATIO OF THE PRESSURE MEASUREMENT ( OSS, BIT<7:6> )
  */
typedef enum
{
    CTRL_MEAS_OSS_MASK                      =   ( 0b11 << 6U ),       /*!<  OSS Mask                         */
    CTRL_MEAS_OSS_OVERSAMPLING_SINGLE       =   ( 0b00 << 6U ),       /*!<  OSS oversampling ratio: single   */
    CTRL_MEAS_OSS_OVERSAMPLING_2_TIMES      =   ( 0b01 << 6U ),       /*!<  OSS oversampling ratio: 2 times  */
    CTRL_MEAS_OSS_OVERSAMPLING_4_TIMES      =   ( 0b10 << 6U ),       /*!<  OSS oversampling ratio: 4 times  */
    CTRL_MEAS_OSS_OVERSAMPLING_8_TIMES      =   ( 0b11 << 6U )        /*!<  OSS oversampling ratio: 8 times  */
} BMP180_oss_t;



/* SOFT RESET   */
/**
  * @brief   SOFT RESET
  */
typedef enum
{
    SOFT_SOFT_RESET         =   0xB6                  /*!<  It will perform the same sequence as power on reset   */
} BMP180_soft_reset_t;



/* ID   */
/**
  * @brief   CHIP-ID
  */
typedef enum
{
    ID_CHIP_ID              =   0x55                  /*!<  Fixed value                         */
} BMP180_chip_id_t;



/*
    AUXILIAR REGISTERS

    NOTE: These definitions are for better understanding in order to use the driver
*/
/**
  * @brief   COMMANDS
  */
typedef enum
{
    BMP180_TRIGGER_TEMPERATURE      =   0x2E,           /*!<  It triggers a new temperature measurement  */
    BMP180_TRIGGER_PRESSURE         =   0x34            /*!<  It triggers a new pressure measurement     */
} BMP180_commands_t;



/**
  * @brief   PRESSURE
  */
typedef enum
{
    PRESSURE_ULTRA_LOW_POWER_MODE   =   CTRL_MEAS_OSS_OVERSAMPLING_SINGLE,      /*!<  OSS oversampling ratio: single   */
    PRESSURE_STANDARD_MODE          =   CTRL_MEAS_OSS_OVERSAMPLING_2_TIMES,     /*!<  OSS oversampling ratio: 2 times  */
    PRESSURE_HIGH_RESOLUTION_MODE   =   CTRL_MEAS_OSS_OVERSAMPLING_4_TIMES,     /*!<  OSS oversampling ratio: 4 times  */
    PRESSURE_ULTRA_HIGH_RES_MODE    =   CTRL_MEAS_OSS_OVERSAMPLING_8_TIMES      /*!<  OSS oversampling ratio: 8 times  */
} BMP180_pressure_resolution_t;





#ifndef BMP180_VECTOR_STRUCT_H
#define BMP180_VECTOR_STRUCT_H
/* Calibration data  */
typedef struct
{
    int16_t  ac1;
    int16_t  ac2;
    int16_t  ac3;
    uint16_t ac4;
    uint16_t ac5;
    uint16_t ac6;

    int16_t  b1;
    int16_t  b2;

    int16_t  mb;
    int16_t  mc;
    int16_t  md;
} BMP180_calibration_data_t;


/* Uncompensated data  */
typedef struct
{
    int32_t  ut;
    int32_t  up;
} BMP180_uncompensated_data_t;


/* Data  */
typedef struct
{
    uint8_t  id;
    int32_t  b5;

    float    temp;
    float    press;
} BMP180_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    BMP180_SUCCESS     =       0,
    BMP180_FAILURE     =       1
} BMP180_status_t;






/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
BMP180_status_t  BMP180_Init                ( I2C_parameters_t myI2Cparameters                                                                                                                                                              );

/** It performs a soft reset.
  */
BMP180_status_t  BMP180_SoftReset           ( I2C_parameters_t myI2Cparameters                                                                                                                                                              );

/** It gets the chip-ID.
  */
BMP180_status_t  BMP180_GetID               ( I2C_parameters_t myI2Cparameters, BMP180_data_t* myID                                                                                                                                         );

/** It reads the calibration data.
  */
BMP180_status_t  BMP180_Get_Cal_Param       ( I2C_parameters_t myI2Cparameters, BMP180_calibration_data_t* myCalibrationData                                                                                                                );

/** It reads uncompensated temperature value.
  */
BMP180_status_t  BMP180_Get_UT              ( I2C_parameters_t myI2Cparameters, BMP180_uncompensated_data_t* myUT                                                                                                                           );

/** It reads uncompensated pressure value.
  */
BMP180_status_t  BMP180_Get_UP              ( I2C_parameters_t myI2Cparameters, BMP180_pressure_resolution_t myPressureResolutionMode, BMP180_uncompensated_data_t* myUP                                                                    );

/** It calculates true temperature.
  */
BMP180_data_t    BMP180_Get_Temperature     ( I2C_parameters_t myI2Cparameters, BMP180_calibration_data_t myCalibrationData, BMP180_uncompensated_data_t myUT                                                                               );

/** It calculates true pressure.
  */
BMP180_data_t    BMP180_Get_CalPressure     ( I2C_parameters_t myI2Cparameters, BMP180_calibration_data_t myCalibrationData, BMP180_data_t myB5, BMP180_pressure_resolution_t myPressureResolutionMode, BMP180_uncompensated_data_t myUP    );


#ifdef __cplusplus
}
#endif

#endif /* BMP180_H */
