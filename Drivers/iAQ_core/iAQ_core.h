/**
 * @brief       iAQ_Core.h
 * @details     Indoor air quality module, I2C interface.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/May/2018
 * @version     31/May/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef iAQ_Core_H_
#define iAQ_Core_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   DEFAULT ADDRESSES.
  */
typedef enum
{
    iAQ_Core_ADDRESS     =   0x5A               /*!<   Address for iAQ_Core                                             */
} iAQ_Core_address_t;


// iAQ_Core DATA. NOTE: The I2C master can request up to 9 bytes.
/**
  * @brief   STATUS FLAG. NOTE: If status is OK the data is valid. If the status is BUSY, the data integrity is not guaranteed for
  *                             variables of size > 8 bits, because the module may be updating a part of the variable. If the status
  *                             is ERROR constantly (or very frequently) this indicates that the module is reading non-realistic values,
  *                             and the sensor element is probably defective.
  */
typedef enum
{
    iAQ_Core_STATUS_OK        =   0x00,         /*!<  Status Flag: OK      ( data valid )                               */
    iAQ_Core_STATUS_BUSY      =   0x01,         /*!<  Status Flag: BUSY    ( re-read multi byte data! )                 */
    iAQ_Core_STATUS_RUNIN     =   0x10,         /*!<  Status Flag: RUNIN   ( module in warm up phase )                  */
    iAQ_Core_STATUS_ERROR     =   0x80          /*!<  Status Flag: ERROR   ( if constant: replace sensor )              */
} iAQ_Core_status_flag_t;






#ifndef iAQ_Core_VECTOR_STRUCT_H
#define iAQ_Core_VECTOR_STRUCT_H
typedef struct
{
    uint16_t                pred;               /*!<  Prediction (CO2 eq. ppm),  Typical Value: 450                     */
    iAQ_Core_status_flag_t  status;             /*!<  Status,                    Typical Value: 0                       */
    int32_t                 resistance;         /*!<  Sensor resistance [Ohm],   Typical Value: 256431                  */
    uint16_t                Tvoc;               /*!<  Prediction (TVOC eq. ppb), Typical Value: 125                     */
} iAQ_Core_vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    iAQ_Core_SUCCESS     =   0,
    iAQ_Core_FAILURE     =   1
} iAQ_Core_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
iAQ_Core_status_t iAQ_Core_Init              ( I2C_parameters_t myI2Cparameters                                 );

/** It performs a new parameters reading from the sensor.
      */
iAQ_Core_status_t iAQ_Core_GetNewReading     ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myData );




#ifdef __cplusplus
}
#endif

#endif /* iAQ_Core_H */
