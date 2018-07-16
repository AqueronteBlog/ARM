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
#include "nrf_delay.h"

#ifndef BME680_port_H_
#define BME680_port_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief VARIABLES.
 */
extern volatile I2C_parameters_t    myBME680_I2C_parameters;



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
BME680_status_t  BME680_Init    ( I2C_parameters_t myI2Cparameters                                  );

/** Return control or wait, for a period amount of milliseconds.
        */
void             user_delay_ms  ( uint32_t period                                                   );

/** It reads data through the I2C bus.
        */
int8_t           user_i2c_read  ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

/** It writes data through the I2C bus.
        */
int8_t           user_i2c_write ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );



#ifdef __cplusplus
}
#endif

#endif /* BME680_port_H_ */
