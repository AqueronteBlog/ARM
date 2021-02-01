/**
 * @brief       MICS_VZ_89TE.h
 * @details     Integrated VOC Sensor Module with CO2 equivalent.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     26/January/2021    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#ifndef MICS_VZ_89TE_H
#define MICS_VZ_89TE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  MICS_VZ_89TE_ADDRESS   =   0x70               /*!<   I2C slave address byte, Default              */
} MICS_VZ_89TE_address_t;



/**
  * @brief   COMMAND LIST
  */
typedef enum
{
  MICS_VZ_89TE_SET_PPM_CO2  =   0b00001000,       /*!<  To send the ppmCO2 value given by an external analyser to the VZ89TE in order to recalibrate its outputs  */
  MICS_VZ_89TE_GET_STATUS   =   0b00001100,       /*!<  This command is used to read the VZ89TE status coded on 6x bytes + 1 CRC byte                             */
  MICS_VZ_89TE_GET_REVISION =   0b00001101,       /*!<  This command will return the revision code of the module                                                  */
  MICS_VZ_89TE_GET_R0       =   0b00010000        /*!<  This command is used to read the R0 (calibration) value in [kOhms]                                        */
} MICS_VZ_89TE_command_list_t;






#ifndef MICS_VZ_89TE_VECTOR_STRUCT_H
#define MICS_VZ_89TE_VECTOR_STRUCT_H
/* Status command  */
typedef struct
{
  uint8_t d1;                   /*!<  Raw tVOC                                                */
  uint8_t d2;                   /*!<  Raw CO2_equ                                             */
  uint8_t d3;                   /*!<  RS first byte(MSB)                                      */
  uint8_t d4;                   /*!<  RS second byte                                          */
  uint8_t d5;                   /*!<  RS third byte(LSB)                                      */
  uint8_t d6;                   /*!<  Status                                                  */
  uint8_t d7;                   /*!<  CRC                                                     */
} MICS_VZ_89TE_get_status_t;


/* Output values  */
typedef struct
{
  float     tvoc;               /*!<  tVOC [13...242] in ppb                                  */
  float     co2_equ;            /*!<  CO2 equivalent [13...242] in ppm                        */
  uint32_t  resistor;           /*!<  Resistor value in Ohms                                  */
} MICS_VZ_89TE_output_values_t;


/* Revision  */
typedef struct
{
  uint8_t year;                  /*!<  Year                                                   */
  uint8_t month;                 /*!<  Month                                                  */
  uint8_t day;                   /*!<  Day                                                    */
  uint8_t ascii_code;            /*!<  ASCII code for a charter                               */
  uint8_t crc;                   /*!<  CRC                                                    */
} MICS_VZ_89TE_revision_t;


/* R0: Raw data  */
typedef struct
{
  uint8_t r0_lsb;                 /*!<  R0 LSB                                                 */
  uint8_t r0_msb;                 /*!<  R0 MSB                                                 */
  uint8_t crc;                    /*!<  CRC                                                    */
} MICS_VZ_89TE_r0_t;



/* USER: User's global variables	 */
typedef struct
{
  /* Output  */
  MICS_VZ_89TE_get_status_t     status;   /*!<  Raw values: tVOC, CO2_equ and Resistor                  */
  MICS_VZ_89TE_output_values_t  values;   /*!<  Output values: tVOC, CO2_equ and Resistor               */
  

  /* Calibration   */
  MICS_VZ_89TE_r0_t             r0_raw;   /*!<  R0 calibration raw value                                */
  uint16_t                      r0;       /*!<  R0 calibration value in kOhms                           */


  /* Device identification   */
  MICS_VZ_89TE_revision_t       device;   /*!<  Device. The revision code of the module                 */
} MICS_VZ_89TE_data_t;
#endif




/**
  * @brief   ERROR STATUS. INTERNAL CONSTANTS
  */
typedef enum
{
    MICS_VZ_89TE_SUCCESS               =   0U,          /*!<  I2C communication success                        */
    MICS_VZ_89TE_FAILURE               =   1U,          /*!<  I2C communication failure                        */
    MICS_VZ_89TE_DATA_CORRUPTED        =   2U           /*!<  Error status byte                                */
} MICS_VZ_89TE_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_Init           ( I2C_parameters_t myI2Cparameters                                                                            );

/** It triggers the STATUS command.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_TriggersStatus   ( I2C_parameters_t myI2Cparameters                                                                          );

/** It gets all the raw values.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetStatus        ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_get_status_t* status                                       );

/** It gets all the values: tVOC, CO2_equ and Resistor.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetUpdateValues  ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_get_status_t* status, MICS_VZ_89TE_output_values_t* values );

/** It triggers the Revsion command.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_TriggersRevision ( I2C_parameters_t myI2Cparameters                                                                          );

/** It gets Revision values.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetRevision      ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_revision_t* revision                                       );

/** It triggers the R0 command.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_TriggersR0       ( I2C_parameters_t myI2Cparameters                                          );

/** It gets R0 value.
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetRawR0         ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_r0_t* rawR0                );

/** It gets R0 value (in kOhms).
  */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetR0            ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_r0_t* rawR0, uint16_t* r0  );

/** It gets the CRC byte.
  */
uint8_t               MICS_VZ_89TE_GetCRC           ( uint8_t* buffer, uint8_t size                                             );


#ifdef __cplusplus
}
#endif

#endif /* MICS_VZ_89TE_H_ */