/**
 * @brief       BMA456.c
 * @details     MEMS nano pressure sensor: 260-1260 hPa absolute digital output barometer.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/June/2019
 * @version     15/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "BMA456.h"


/**
 * @brief       BMA456_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BMA456_status_t BMA456_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetInterruptMode ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the Interrupt CFG register, raw value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInterruptCFG:  InterruptCFG register, raw value.
 *
 *
 * @return       Status of BMA456_GetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetInterruptMode ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInterruptCFG )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

//  /* Read the register   */
//  cmd  =   BMA456_INTERRUPT_CFG;
//  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
//  
//  /* Parse the data   */
//  myInterruptCFG->interruptCFG   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}


