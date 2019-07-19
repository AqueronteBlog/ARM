/**
 * @brief       ADS101X.c
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 3.3-kSPS, 12-Bit ADCs. With Internal Reference, Oscillator, and Programmable Comparator.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "ADS101X.h"


/**
 * @brief       ADS101X_Init ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myADS101X:       Device to use.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     19/July/2019   The device to use was added ( this is redundant ).
 *              17/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_Init ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myADS101X  )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_StartSingleConversion ( I2C_parameters_t );
 *
 * @details     It starts a new single conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_StartSingleConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        19/July/2019
 * @version     19/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_StartSingleConversion ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd[0]   =   ADS101X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update the register   */
  cmd[1]  |=   CONFIG_OS_BUSY;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetOS ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It checks if the device is not currently performing a conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myADS101X:       Operational status flag.
 *
 *
 * @return       Status of ADS101X_GetOS.
 *
 *
 * @author      Manuel Caballero
 * @date        19/July/2019
 * @version     19/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetOS ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myADS101X )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_CONFIG;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse it   */
  myADS101X->os  =   (ADS101X_config_os_t)( cmd & CONFIG_OS_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



