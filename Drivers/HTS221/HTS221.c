/**
 * @brief       HTS221.c
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
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include "HTS221.h"


/**
 * @brief       HTS221_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HTS221_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   HTS221_SUCCESS;
  }
  else
  {
    return   HTS221_FAILURE;
  }
}



/**
 * @brief       HTS221_GetCONFIG ( I2C_parameters_t , HTS221_config_reg_t* )
 *
 * @details     It gets CONFIG register value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myCONFIG:        CONFIG register value.
 *
 *
 * @return       Status of HTS221_GetCONFIG.
 *
 *
 * @author      Manuel Caballero
 * @date        23/April/2019
 * @version     23/April/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
//HTS221_status_t HTS221_GetCONFIG ( I2C_parameters_t myI2Cparameters, HTS221_config_reg_t* myCONFIG )
//{
//  uint8_t      cmd[2]       = { 0U };
//  uint16_t     myConfigAux  = 0U;
//  i2c_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   HTS221_CONFIG;
//  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
//
//  /* Mask it and update it with the new value  */
//  myConfigAux   =   cmd[0];
//  myConfigAux <<=   8U;
//  myConfigAux  |=   cmd[1];
//
//  myCONFIG->t_hyst       =   (HTS221_config_thyst_t)( myConfigAux & CONFIG_T_HYST_MASK );
//  myCONFIG->shdn         =   (HTS221_config_shdn_t)( myConfigAux & CONFIG_SHDN_MASK );
//  myCONFIG->t_crit       =   (HTS221_config_crit_lock_t)( myConfigAux & CONFIG_CRIT_LOCK_MASK );
//  myCONFIG->t_win_lock   =   (HTS221_config_win_lock_t)( myConfigAux & CONFIG_WIN_LOCK_MASK );
//  myCONFIG->int_clear    =   (HTS221_conf_int_clear_t)( myConfigAux & CONFIG_INT_CLEAR_MASK );
//  myCONFIG->alert_stat   =   (HTS221_config_alert_stat_t)( myConfigAux & CONFIG_ALERT_STAT_MASK );
//  myCONFIG->alert_cnt    =   (HTS221_config_alert_cnt_t)( myConfigAux & CONFIG_ALERT_CNT_MASK );
//  myCONFIG->alert_sel    =   (HTS221_config_alert_sel_t)( myConfigAux & CONFIG_ALERT_SEL_MASK );
//  myCONFIG->alert_pol    =   (HTS221_config_alert_pol_t)( myConfigAux & CONFIG_ALERT_POL_MASK );
//  myCONFIG->alert_mod    =   (HTS221_config_alert_mod_t)( myConfigAux & CONFIG_ALERT_MOD_MASK );
//
//
//
//  if ( aux == I2C_SUCCESS )
//  {
//    return   HTS221_SUCCESS;
//  }
//  else
//  {
//    return   HTS221_FAILURE;
//  }
//}
