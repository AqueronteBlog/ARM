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
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include "SX1272_SX1273.h"


/**
 * @brief       MCP9808_Init ( SPI_parameters_t )
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
MCP9808_status_t MCP9808_Init ( SPI_parameters_t myI2Cparameters )
{
  spi_status_t aux;

  aux  =   spi_init ( myI2Cparameters );



  if ( aux == SPI_SUCCESS )
  {
    return   MCP9808_SUCCESS;
  }
  else
  {
    return   MCP9808_FAILURE;
  }
}



/**
 * @brief       MCP9808_GetCONFIG ( SPI_parameters_t , MCP9808_config_reg_t* )
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
MCP9808_status_t MCP9808_GetCONFIG ( SPI_parameters_t myI2Cparameters, MCP9808_config_reg_t* myCONFIG )
{
  uint8_t      cmd[2]       = { 0U };
  uint16_t     myConfigAux  = 0U;
  spi_status_t aux;

  /* Read the register   */
  cmd[0]   =   MCP9808_CONFIG;
  //aux      =   spi_transfer ( SPI_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length );

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



  if ( aux == SPI_SUCCESS )
  {
    return   MCP9808_SUCCESS;
  }
  else
  {
    return   MCP9808_FAILURE;
  }
}
