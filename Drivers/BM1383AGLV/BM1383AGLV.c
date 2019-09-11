/**
 * @brief       BM1383AGLV.c
 * @details     Pressure Sensor IC.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include "BM1383AGLV.h"


/**
 * @brief       BM1383AGLV_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BM1383AGLV_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetDeviceID ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID.
 *
 *
 * @return       Status of BM1383AGLV_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
//BM1383AGLV_status_t BM1383AGLV_GetDeviceID ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myDeviceID )
//{
//  uint8_t      cmd  = 0U;
//  i2c_status_t aux;
//
//  /* Read the register   */
//  cmd   =   BM1383AGLV_WHO_AM_I;
//  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );
//
//  /* Mask it and update it with the new value  */
//  myDeviceID->deviceID   =   cmd;
//
//
//
//  if ( aux == I2C_SUCCESS )
//  {
//    return   BM1383AGLV_SUCCESS;
//  }
//  else
//  {
//    return   BM1383AGLV_FAILURE;
//  }
//}
