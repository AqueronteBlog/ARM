/**
 * @brief       BME680.h
 * @details     Low power gas, pressure, temperature and humidity sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018   The ORIGIN
 * @pre         Although the BME680 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C.
 * @pre         This files makes Bosh's driver compatible with our I2C driver.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "bme680.h"
#include "i2c.h"

#ifndef BME680_H_
#define BME680_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    BME680_SUCCESS     =       0,
    BME680_FAILURE     =       1
} BME680_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
        */
BME680_status_t  BME680_Init                          ( I2C_parameters_t myI2Cparameters                                                                                            );





#ifdef __cplusplus
}
#endif

#endif /* BME680_H_ */
