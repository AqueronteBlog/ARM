/**
 * @brief       ADS111X.c
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 860-SPS, 16-Bit ADCs With Internal Reference, Oscillator, and Programmable Comparator.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "ADS111X.h"


/**
 * @brief       ADS111X_Init ( I2C_parameters_t, ADS111X_data_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myADS111X:       Device to use.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_Init ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myADS111X  )
{
  i2c_status_t aux =  I2C_SUCCESS;;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_StartSingleConversion ( I2C_parameters_t );
 *
 * @details     It starts a new single conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_StartSingleConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020   The ORIGIN
 * @pre         This function can only be used when in power-down state and has no effect 
 *              when a conversion is ongoing.
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_StartSingleConversion ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;
  
  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* Mask it and update the register   */
  myConfig   =   cmd[1];
  myConfig <<=   8U;
  myConfig  |=   cmd[2];

  myConfig  |=   CONFIG_OS_BUSY;
  cmd[1]     =   (uint8_t)( myConfig >> 8U );
  cmd[2]     =   (uint8_t)( myConfig );
  aux       |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



