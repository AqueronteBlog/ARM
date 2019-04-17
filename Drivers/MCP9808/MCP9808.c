/**
 * @brief       MCP9808.c
 * @details     ±0.5°C Maximum Accuracy Digital Temperature Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "MCP9808.h"


/**
 * @brief       MCP9808_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   MCP9808_SUCCESS;
  }
  else
  {
    return   MCP9808_FAILURE;
  }
}



/**
 * @brief       MCP9808_SetT_HYST ( I2C_parameters_t , MCP9808_config_thyst_t )
 *
 * @details     It sets T_UPPER and T_LOWER Limit Hysteresis.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myT_HYST:        Limit hysteresis.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetT_HYST.
 *
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_SetT_HYST ( I2C_parameters_t myI2Cparameters, MCP9808_config_thyst_t myT_HYST )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* T_HYSTT can NOT be altered when either of the Lock bits are set ( bit 6 and bit 7 )   */
  if ( ( ( cmd[1] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[1] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONFIG_T_HYST_MASK ) | myT_HYST );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   MCP9808_SUCCESS;
  }
  else
  {
    return   MCP9808_FAILURE;
  }
}



/**
 * @brief       MCP9808_SetPowerMode ( I2C_parameters_t , MCP9808_config_shdn_t )
 *
 * @details     It sets device power mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySHDN:          Power mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_SetPowerMode ( I2C_parameters_t myI2Cparameters, MCP9808_config_shdn_t mySHDN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* SHDN This bit cannot be set to '1' when either of the Lock bits is set ( bit 6 and bit 7 ). However, it can be
   * cleared to '0' for continuous conversion while locked   
   */
  if ( ( ( ( cmd[1] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[1] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) ) && ( mySHDN == CONFIG_SHDN_SHUTDOWN ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONFIG_SHDN_MASK ) | mySHDN );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   MCP9808_SUCCESS;
  }
  else
  {
    return   MCP9808_FAILURE;
  }
}



/**
 * @brief       MCP9808_SetT_CRIT_Lock ( I2C_parameters_t , MCP9808_config_crit_lock_t )
 *
 * @details     It sets T_CRIT lock bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myT_CRIT_Lock    Power mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetT_CRIT_Lock.
 *
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_SetT_CRIT_Lock ( I2C_parameters_t myI2Cparameters, MCP9808_config_crit_lock_t myT_CRIT_Lock )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* When enabled, this bit remains set to ‘1’ or locked until cleared by an internal Reset  */
  if ( ( cmd[1] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONFIG_CRIT_LOCK_MASK ) | myT_CRIT_Lock );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   MCP9808_SUCCESS;
  }
  else
  {
    return   MCP9808_FAILURE;
  }
}
