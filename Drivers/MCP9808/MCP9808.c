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
MCP9808_status_t MCP9808_Init ( I2C_parameters_t myI2Cparameters )
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
MCP9808_status_t MCP9808_SetT_HYST ( I2C_parameters_t myI2Cparameters, MCP9808_config_thyst_t myT_HYST )
{
  uint8_t      cmd[3]       = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

  /* T_HYSTT can NOT be altered when either of the Lock bits are set ( bit 6 and bit 7 )   */
  if ( ( ( cmd[2] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~(uint8_t)( CONFIG_T_HYST_MASK >> 8U ) ) | ( myT_HYST >> 8U ) );
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
MCP9808_status_t MCP9808_SetPowerMode ( I2C_parameters_t myI2Cparameters, MCP9808_config_shdn_t mySHDN )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* SHDN This bit cannot be set to '1' when either of the Lock bits is set ( bit 6 and bit 7 ). However, it can be
   * cleared to '0' for continuous conversion while locked   
   */
  if ( ( ( ( cmd[2] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) ) && ( mySHDN == CONFIG_SHDN_SHUTDOWN ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~(uint8_t)( CONFIG_SHDN_MASK >> 8U ) ) | ( mySHDN >> 8U ) );
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
 * @brief       MCP9808_SetCRITLock ( I2C_parameters_t , MCP9808_config_crit_lock_t )
 *
 * @details     It sets T_CRIT lock bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myT_CRIT_Lock    Power mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetCRITLock.
 *
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetCRITLock ( I2C_parameters_t myI2Cparameters, MCP9808_config_crit_lock_t myT_CRIT_Lock )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* When enabled, this bit remains set to '1' or locked until cleared by an internal Reset  */
  if ( ( cmd[2] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_CRIT_LOCK_MASK ) | myT_CRIT_Lock );
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
 * @brief       MCP9808_SetWinLock ( I2C_parameters_t , MCP9808_config_win_lock_t )
 *
 * @details     It sets T_UPPER and T_LOWER window lock bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myWinLock        Window lock mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetWinLock.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetWinLock ( I2C_parameters_t myI2Cparameters, MCP9808_config_win_lock_t myWinLock )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* When enabled, this bit remains set to '1' or locked until cleared by a power-on reset  */
  if ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_WIN_LOCK_MASK ) | myWinLock );
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
 * @brief       MCP9808_SetIntClear ( I2C_parameters_t , MCP9808_conf_int_clear_t )
 *
 * @details     It sets interrupt Clear bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myIntClear       Interrupt clear mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetIntClear.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetIntClear ( I2C_parameters_t myI2Cparameters, MCP9808_conf_int_clear_t myIntClear )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* This bit can not be set to '1' in Shutdown mode, but it can be cleared after the device enters Shutdown mode  */
  if ( ( ( cmd[1] & ( CONFIG_SHDN_MASK >> 8U ) ) == ( CONFIG_SHDN_SHUTDOWN >> 8U ) ) && ( myIntClear == CONFIG_INT_CLEAR_CLEAR_INT_OUTPUT ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_INT_CLEAR_MASK ) | myIntClear );
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
 * @brief       MCP9808_GetAlertStat ( I2C_parameters_t , MCP9808_data_t* )
 *
 * @details     It gets alert output status bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAlertStat      Alert output status bit.
 *
 *
 * @return       Status of MCP9808_GetAlertStat.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_GetAlertStat ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myAlertStat )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  
  /* Parse the data  */
  myAlertStat->alert_stat  =   (MCP9808_config_alert_stat_t)( cmd[1] & CONFIG_ALERT_STAT_MASK );



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
 * @brief       MCP9808_SetAlertCnt ( I2C_parameters_t , MCP9808_config_alert_cnt_t )
 *
 * @details     It sets alert output control bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAlertCnt:      Alert output control bit.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetAlertCnt.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_SetAlertCnt ( I2C_parameters_t myI2Cparameters, MCP9808_config_alert_cnt_t myAlertCnt )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* This bit can NOT be altered when either of the Lock bits are set ( bit 6 and bit 7 )   */
  if ( ( ( cmd[2] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_ALERT_CNT_MASK ) | myAlertCnt );
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
 * @brief       MCP9808_SetAlertSel ( I2C_parameters_t , MCP9808_config_alert_sel_t )
 *
 * @details     It sets alert output select bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAlertSel:      Alert output select bit.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetAlertSel.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t  MCP9808_SetAlertSel ( I2C_parameters_t myI2Cparameters, MCP9808_config_alert_sel_t myAlertSel )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* This bit can NOT be altered when Alarm Window Lock bit is set ( bit 6 )   */
  if ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_ALERT_SEL_MASK ) | myAlertSel );
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
 * @brief       MCP9808_SetAlertPol ( I2C_parameters_t , MCP9808_config_alert_pol_t )
 *
 * @details     It sets alert output polarity bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAlertPol:      Alert output polarity bit.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetAlertPol.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetAlertPol ( I2C_parameters_t myI2Cparameters, MCP9808_config_alert_pol_t myAlertPol )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* This bit can NOT be altered when either of the Lock bits are set ( bit 6 and bit 7 )   */
  if ( ( ( cmd[2] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_ALERT_POL_MASK ) | myAlertPol );
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
 * @brief       MCP9808_SetAlertMod ( I2C_parameters_t , MCP9808_config_alert_mod_t )
 *
 * @details     It sets alert output mode bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAlertMod:      Alert output mode bit.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetAlertMod.
 *
 *
 * @author      Manuel Caballero
 * @date        16/April/2019
 * @version     16/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetAlertMod ( I2C_parameters_t myI2Cparameters, MCP9808_config_alert_mod_t myAlertMod )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* This bit can NOT be altered when either of the Lock bits are set ( bit 6 and bit 7 )   */
  if ( ( ( cmd[2] & CONFIG_CRIT_LOCK_MASK ) == CONFIG_CRIT_LOCK_LOCKED ) || ( ( cmd[2] & CONFIG_WIN_LOCK_MASK ) == CONFIG_WIN_LOCK_LOCKED ) )
  {
    return   MCP9808_FAILURE;
  }

  /* Mask it and update it with the new value  */
  cmd[2]   =   ( ( cmd[2] & ~CONFIG_ALERT_MOD_MASK ) | myAlertMod );
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
