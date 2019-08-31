/**
 * @brief       BME280.h
 * @details     Combined humidity and pressure sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/August/2019
 * @version     30/August/2019   The ORIGIN
 * @pre         Although the BME280 can be handled by SPI or I2C, this library is only
 *              adapted to be used by I2C.
 * @pre         This files makes Bosh's driver compatible with our I2C driver.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "bme280.h"
#include "i2c.h"
#include "nrf_delay.h"

#ifndef BME280_port_H_
#define BME280_port_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief VARIABLES.
 */
extern volatile I2C_parameters_t    myBME280_I2C_parameters;



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    BME280_SUCCESS     =       0,
    BME280_FAILURE     =       1
} BME280_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
        */
BME280_status_t  BME280_Init_I2C ( I2C_parameters_t myI2Cparameters                                  );

/** Return control or wait, for a period amount of milliseconds.
        */
void             user_delay_ms   ( uint32_t period                                                   );

/** It reads data through the I2C bus.
        */
int8_t           user_i2c_read   ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

/** It writes data through the I2C bus.
        */
int8_t           user_i2c_write  ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );



#ifdef __cplusplus
}
#endif

#endif /* BME280_port_H_ */
