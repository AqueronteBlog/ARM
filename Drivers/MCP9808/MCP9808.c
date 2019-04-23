/**
 * @brief       MCP9808.c
 * @details     �0.5캜 Maximum Accuracy Digital Temperature Sensor.
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
 * @brief       MCP9808_GetCONFIG ( I2C_parameters_t , MCP9808_config_reg_t* )
 *
 * @details     It gets CONFIG register value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myCONFIG:        CONFIG register value.
 *
 *
 * @return       Status of MCP9808_GetCONFIG.
 *
 *
 * @author      Manuel Caballero
 * @date        23/April/2019
 * @version     23/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetCONFIG ( I2C_parameters_t myI2Cparameters, MCP9808_config_reg_t* myCONFIG )
{
  uint8_t      cmd[2]       = { 0U };
  uint16_t     myConfigAux  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Mask it and update it with the new value  */
  myConfigAux   =   cmd[0];
  myConfigAux <<=   8U;
  myConfigAux  |=   cmd[1];

  myCONFIG->t_hyst       =   (MCP9808_config_thyst_t)( myConfigAux & CONFIG_T_HYST_MASK );
  myCONFIG->shdn         =   (MCP9808_config_shdn_t)( myConfigAux & CONFIG_SHDN_MASK );
  myCONFIG->t_crit       =   (MCP9808_config_crit_lock_t)( myConfigAux & CONFIG_CRIT_LOCK_MASK );
  myCONFIG->t_win_lock   =   (MCP9808_config_win_lock_t)( myConfigAux & CONFIG_WIN_LOCK_MASK );
  myCONFIG->int_clear    =   (MCP9808_conf_int_clear_t)( myConfigAux & CONFIG_INT_CLEAR_MASK );
  myCONFIG->alert_stat   =   (MCP9808_config_alert_stat_t)( myConfigAux & CONFIG_ALERT_STAT_MASK );
  myCONFIG->alert_cnt    =   (MCP9808_config_alert_cnt_t)( myConfigAux & CONFIG_ALERT_CNT_MASK );
  myCONFIG->alert_sel    =   (MCP9808_config_alert_sel_t)( myConfigAux & CONFIG_ALERT_SEL_MASK );
  myCONFIG->alert_pol    =   (MCP9808_config_alert_pol_t)( myConfigAux & CONFIG_ALERT_POL_MASK );
  myCONFIG->alert_mod    =   (MCP9808_config_alert_mod_t)( myConfigAux & CONFIG_ALERT_MOD_MASK );



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
 * @brief       MCP9808_SetCONFIG ( I2C_parameters_t , MCP9808_config_reg_t )
 *
 * @details     It sets CONFIG register value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCONFIG:        CONFIG register value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MCP9808_SetCONFIG.
 *
 *
 * @author      Manuel Caballero
 * @date        23/April/2019
 * @version     23/April/2019     The ORIGIN
 * @pre         MCP9808_GetCONFIG function should be called first to mask the bits.
 * @warning     Be aware that some commands can NOT be written depending on Crit.Lock and/or Win.Lock values.
 */
MCP9808_status_t MCP9808_SetCONFIG ( I2C_parameters_t myI2Cparameters, MCP9808_config_reg_t myCONFIG )
{
  uint8_t      cmd[3]       = { 0U };
  uint16_t     myConfigAux  = 0U;
  i2c_status_t aux;

  /* Update CONFI register  */
  myConfigAux   =   ( myCONFIG.t_hyst | myCONFIG.shdn | myCONFIG.t_crit | myCONFIG.t_win_lock | myCONFIG.int_clear |
                      myCONFIG.alert_stat | myCONFIG.alert_cnt | myCONFIG.alert_sel | myCONFIG.alert_pol | myCONFIG.alert_mod );
  
  cmd[0]   =   MCP9808_CONFIG;
  cmd[1]   =   (uint8_t)( myConfigAux >> 8U );
  cmd[2]   =   (uint8_t)( myConfigAux & 0xFF );
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



/**
 * @brief       MCP9808_GetRawTA ( I2C_parameters_t , MCP9808_data_t* )
 *
 * @details     It gets ambient temperature register ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawTA:         Raw T_A data.
 *
 *
 * @return       Status of MCP9808_GetRawTA.
 *
 *
 * @author      Manuel Caballero
 * @date        17/April/2019
 * @version     17/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetRawTA ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myRawTA )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_TA;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Mask it and update it with the new value  */
  myRawTA->t_a_raw   =   cmd[0];
  myRawTA->t_a_raw <<=   8U;
  myRawTA->t_a_raw  |=   cmd[1];




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
 * @brief       MCP9808_GetTA ( I2C_parameters_t , MCP9808_data_t* )
 *
 * @details     It gets ambient temperature register ( Celsius degrees ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myTA:            T_A value and flags.
 *
 *
 * @return       Status of MCP9808_GetTA.
 *
 *
 * @author      Manuel Caballero
 * @date        17/April/2019
 * @version     17/April/2019     The ORIGIN
 * @pre         This function also updates the comparison flags.
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetTA ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myTA )
{
  uint8_t          myUpperByte   =   0U;
  uint8_t          myLowerByte   =   0U;
  MCP9808_status_t aux;

  /* Read the register   */
  aux  =   MCP9808_GetRawTA ( myI2Cparameters, &(*myTA) );
  
  /* Mask it and update it with the new value  */
  /* Mask the flags  */
  myTA->ta_vs_tcrit  =   (MCP9808_t_a_ta_vs_tcrit_t)( myTA->t_a_raw & T_A_TA_VS_TCRIT_MASK );
  myTA->ta_vs_tupper =   (MCP9808_t_a_ta_vs_tupper_t)( myTA->t_a_raw & T_A_TA_VS_TUPPER_MASK );
  myTA->t_lower      =   (MCP9808_t_a_ta_vs_tlower_t)( myTA->t_a_raw & T_A_TA_VS_TLOWER_MASK );
  myTA->t_a_sign     =   (MCP9808_t_a_sign_t)( myTA->t_a_raw & T_A_TA_SIGN_MASK );

  /* Mask the ambient temperature value  */
  myUpperByte  =   (uint8_t)( myTA->t_a_raw >> 8U );
  myLowerByte  =   (uint8_t)( myTA->t_a_raw & 0xFF );

  /* Clean the flags   */
  myUpperByte &=  ~(uint8_t)( ( T_A_TA_VS_TCRIT_MASK | T_A_TA_VS_TUPPER_MASK | T_A_TA_VS_TLOWER_MASK ) >> 8U );
  
  /* Check if T_A is negative/positive   */
  if ( myTA->t_a_sign == T_A_TA_SIGN_NEGATIVE )
  {
    /* Ambient temperature is NEGATIVE   */
    myUpperByte &=  ~(uint8_t)( T_A_TA_SIGN_MASK >> 8U );                                     // Clear the SIGN flag
    myTA->t_a    =   256.0f - (float)( ( myUpperByte * 16.0f ) + ( myLowerByte / 16.0f ) );   // Ambient temperature value
  }
  else
  {
    /* Ambient temperature is POSITIVE   */
    myTA->t_a    =   (float)( ( myUpperByte * 16.0f ) + ( myLowerByte / 16.0f ) );            // Ambient temperature value
  }


  return aux;
}



/**
 * @brief       MCP9808_GetManufacturerID ( I2C_parameters_t , MCP9808_data_t* )
 *
 * @details     It gets manufacturer ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myManufacturerID:  Manufacturer ID code
 *
 *
 * @return       Status of MCP9808_GetManufacturerID.
 *
 *
 * @author      Manuel Caballero
 * @date        17/April/2019
 * @version     17/April/2019     The ORIGIN
 * @pre         It should be 0x0054 ( hexadecimal ).
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetManufacturerID ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myManufacturerID )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_MANUFACTURER_ID;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Mask it and update it with the new value  */
  myManufacturerID->manufacturerID   =   cmd[0];
  myManufacturerID->manufacturerID <<=   8U;
  myManufacturerID->manufacturerID  |=   cmd[1];



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
 * @brief       MCP9808_GetDeviceID ( I2C_parameters_t , MCP9808_data_t* )
 *
 * @details     It gets device ID and device revision.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Both device ID and device revision 
 *
 *
 * @return       Status of MCP9808_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        17/April/2019
 * @version     17/April/2019     The ORIGIN
 * @pre         Device ID should be 0x04 ( hexadecimal ).
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetDeviceID ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myDeviceID )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_DEVICE_ID;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Mask it and update it with the new value  */
  myDeviceID->deviceID         =   cmd[0];
  myDeviceID->deviceRevision   =   cmd[1];



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
 * @brief       MCP9808_SetResolution ( I2C_parameters_t , MCP9808_data_t )
 *
 * @details     It sets the sensor resolution.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myResolution:    Device resolution.
 *
 * @param[out]   N/A 
 *
 *
 * @return       Status of MCP9808_SetResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        17/April/2019
 * @version     17/April/2019     The ORIGIN
 * @pre         Resolution vs timing conversion:
 *                � Resolution: +0.5캜    ( t_CONV = 30ms typical )
 *                � Resolution: +0.25캜   ( t_CONV = 65ms typical )
 *                � Resolution: +0.125캜  ( t_CONV = 130ms typical )
 *                � Resolution: +0.0625캜 ( power-up default, t_CONV = 250ms typical )
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetResolution ( I2C_parameters_t myI2Cparameters, MCP9808_data_t myResolution )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_RESOLUTION;
  cmd[1]   =   myResolution.resolution;
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
 * @brief       MCP9808_GetResolution ( I2C_parameters_t , MCP9808_data_t* )
 *
 * @details     It gets the sensor resolution.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myResolution:    Device resolution. 
 *
 *
 * @return       Status of MCP9808_GetResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        17/April/2019
 * @version     17/April/2019     The ORIGIN
 * @pre         Resolution vs timing conversion:
 *                � Resolution: +0.5캜    ( t_CONV = 30ms typical )
 *                � Resolution: +0.25캜   ( t_CONV = 65ms typical )
 *                � Resolution: +0.125캜  ( t_CONV = 130ms typical )
 *                � Resolution: +0.0625캜 ( power-up default, t_CONV = 250ms typical )
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetResolution ( I2C_parameters_t myI2Cparameters, MCP9808_data_t* myResolution )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   MCP9808_RESOLUTION;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Mask it and update it with the new value  */
  myResolution->resolution     =   (MCP9808_resolution_t)cmd;



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
 * @brief       MCP9808_SetT_Limit ( I2C_parameters_t , MCP9808_registers_t, MCP9808_data_t )
 *
 * @details     It sets temperature limit for: T_UPPER, T_LOWER or T_CRIT.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTLimit:        Temperature limit register: T_UPPER, T_LOWER or T_CRIT.
 * @param[in]    myTValue_Limit:  Temperature limit value.
 *
 * @param[out]   N/A. 
 *
 *
 * @return       Status of MCP9808_SetT_Limit.
 *
 *
 * @author      Manuel Caballero
 * @date        20/April/2019
 * @version     20/April/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_SetT_Limit ( I2C_parameters_t myI2Cparameters, MCP9808_registers_t myTLimit, MCP9808_data_t myTValue_Limit )
{
  uint8_t      cmd[2]     = { 0U };
  int8_t       myDecimal  = 0U;
  uint8_t      myIntegral = 0U;
  i2c_status_t aux;
  
  /* Only temperature limit registers can keep going   */
  if ( ( myTLimit != MCP9808_TUPPER ) || ( myTLimit != MCP9808_TLOWER ) || ( myTLimit != MCP9808_TCRIT ) )
  {
    return  MCP9808_FAILURE;
  }
  else
  {
    /* Parse the data  */
    myIntegral =   (int8_t)myTValue_Limit.t_upper;
    myDecimal  =   (uint8_t)( ( myTValue_Limit.t_upper - myIntegral ) * 100.0f );
  
    /* Check the decimal part is correct; Valid decimal values: 0.00, 0.25, 0.50 or 0.75   */
    myIntegral <<=  4U;
    myDecimal  <<=  2U;
    if( ( myDecimal != TEMPERATURE_LIMIT_DECIMAL_PART_0_00C ) || ( myDecimal != TEMPERATURE_LIMIT_DECIMAL_PART_0_25C ) || 
        ( myDecimal != TEMPERATURE_LIMIT_DECIMAL_PART_0_50C ) || ( myDecimal != TEMPERATURE_LIMIT_DECIMAL_PART_0_50C ) )
    {
      return  MCP9808_FAILURE;
    }
    else
    {
      /* Update the register with the new value  */
      cmd[0]  =   myTLimit;
      cmd[1]  =   ( myIntegral | myDecimal );
      aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  

      if ( aux == I2C_SUCCESS )
      {
        return   MCP9808_SUCCESS;
      }
      else
      {
        return   MCP9808_FAILURE;
      }
    }
  }
}



/**
 * @brief       MCP9808_GetT_Limit ( I2C_parameters_t , MCP9808_registers_t, MCP9808_data_t* )
 *
 * @details     It gets temperature limit for: T_UPPER, T_LOWER or T_CRIT.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTLimit:        Temperature limit register: T_UPPER, T_LOWER or T_CRIT.
 *
 * @param[out]   myTValue_Limit:  Temperature limit value for the chosen register. 
 *
 *
 * @return       Status of MCP9808_GetT_Limit.
 *
 *
 * @author      Manuel Caballero
 * @date        20/April/2019
 * @version     20/April/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MCP9808_status_t MCP9808_GetT_Limit ( I2C_parameters_t myI2Cparameters, MCP9808_registers_t myTLimit, MCP9808_data_t* myTValue_Limit )
{
  uint8_t      cmd        = 0U;
  uint8_t      myDecimal  = 0U;
  float        myAuxValue = 0U;
  i2c_status_t aux;
  
  /* Only temperature limit registers can keep going   */
  if ( ( myTLimit != MCP9808_TUPPER ) || ( myTLimit != MCP9808_TLOWER ) || ( myTLimit != MCP9808_TCRIT ) )
  {
    return  MCP9808_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd  =   myTLimit;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
    
    /* Process the data  */
    myAuxValue =   (float)( ( cmd & TEMPERATURE_LIMIT_INTEGRAL_PART_MASK ) >> 4U );
    myDecimal  =   ( ( cmd & TEMPERATURE_LIMIT_DECIMAL_PART_MASK ) >> 2U );
    
    /* Process the decimal part  */
    for( cmd = ( TEMPERATURE_LIMIT_DECIMAL_PART_0_00C >> 2U ); cmd < myDecimal; cmd++ )
    {
      myAuxValue  +=   0.25f;
    }

    /* Parse the data   */
    switch( myTLimit )
    {
      case MCP9808_TUPPER:
        myTValue_Limit->t_upper  =   (float)myAuxValue;
        break;
      
      case MCP9808_TLOWER:
        myTValue_Limit->t_lower  =   (float)myAuxValue;
        break;

      case MCP9808_TCRIT:
        myTValue_Limit->t_crit  =   (float)myAuxValue;
        break;

      default:
        return  MCP9808_FAILURE;
        break;
    }

  

    if ( aux == I2C_SUCCESS )
    {
      return   MCP9808_SUCCESS;
    }
    else
    {
      return   MCP9808_FAILURE;
    }
  }
}
