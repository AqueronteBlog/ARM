/**
 * @brief       BMA456.h
 * @details     Digital, triaxial acceleration sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/July/2019
 * @version     15/July/2019   The ORIGIN
 * @pre         Although the BMA456 can be handled by SPI or I2C, this library is only adapted to be used by I2C.
 * @pre         This files makes Bosh's driver compatible with our I2C driver.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "bma456.h" 
#include "i2c.h"
#include "nrf_delay.h"

#ifndef BMA456_port_H_
#define BMA456_port_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief VARIABLES.
 */
extern volatile I2C_parameters_t    myBMA456_I2C_parameters;



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    BMA456_SUCCESS     =       0,
    BMA456_FAILURE     =       1
} BMA456_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
        */
BMA456_status_t  BMA456_Init_I2C ( I2C_parameters_t myI2Cparameters                                  );

/** Return control or wait, for a period amount of milliseconds.
        */
void             user_delay_ms   ( uint32_t period                                                   );

/** It reads data through the I2C bus.
        */
uint16_t         user_i2c_read   ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );

/** It writes data through the I2C bus.
        */
uint16_t         user_i2c_write  ( uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len );



#ifdef __cplusplus
}
#endif

#endif /* BMA456_port_H_ */
