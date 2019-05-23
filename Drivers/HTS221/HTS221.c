/**
 * @brief       HTS221.c
 * @details     Capacitive digital sensor for relative humidity and temperature.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/May/2019
 * @version     22/May/2019    The ORIGIN
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
 * @date        22/May/2019
 * @version     22/May/2019   The ORIGIN
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
 * @brief       HTS221_GetDeviceID ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID.
 *
 *
 * @return       Status of HTS221_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetDeviceID ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myDeviceID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_WHO_AM_I;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Mask it and update it with the new value  */
  myDeviceID->deviceID   =   cmd;



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
 * @brief       HTS221_SetResolution ( I2C_parameters_t , HTS221_data_t )
 *
 * @details     It set humidity and temperature resolution mode.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 * @param[in]    myTempHumResolution: Humidity and Temperature resolution mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HTS221_SetResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetResolution ( I2C_parameters_t myI2Cparameters, HTS221_data_t myTempHumResolution )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_AV_CONF;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Mask it and update it with the new value  */
  cmd[1]  &=  ~( AV_CONF_AVGT_MASK | AV_CONF_AVGH_MASK );
  cmd[1]  |=   ( myTempHumResolution.temperatureResolution | myTempHumResolution.humidityResolution );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




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
 * @brief       HTS221_GetResolution ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It get humidity and temperature resolution mode.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 *
 * @param[out]   myTempHumResolution: Humidity and Temperature resolution mode
 *
 *
 * @return       Status of HTS221_GetResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetResolution ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myTempHumResolution )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_AV_CONF;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data  */
  myTempHumResolution->temperatureResolution   =   (HTS221_av_config_avgt_t)( cmd & AV_CONF_AVGT_MASK );
  myTempHumResolution->humidityResolution      =   (HTS221_av_config_avgh_t)( cmd & AV_CONF_AVGH_MASK );




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
 * @brief       HTS221_SetPowerDown ( I2C_parameters_t , HTS221_ctrl_reg1_pd_t )
 *
 * @details     It sets the device into power-down ( low-power mode ) or active mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPowerMode:     Power-Down/Active mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetPowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetPowerDown ( I2C_parameters_t myI2Cparameters, HTS221_ctrl_reg1_pd_t myPowerMode )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & CTRL_REG1_PD_MASK ) | myPowerMode );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



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
 * @brief       HTS221_SetBlockDataUpdate ( I2C_parameters_t , HTS221_data_t )
 *
 * @details     It sets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBDU:           Block data update mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, HTS221_data_t myBDU )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & CTRL_REG1_BDU_MASK ) | myBDU.bdu );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



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
 * @brief       HTS221_GetBlockDataUpdate ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBDU:           Block data update mode
 *
 *
 * @return       Status of HTS221_GetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myBDU )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_CTRL_REG1;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data  */
  myBDU->bdu   =   (HTS221_ctrl_reg1_bdu_t)( cmd & CTRL_REG1_BDU_MASK );
  



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
 * @brief       HTS221_SetOutputDataRate ( I2C_parameters_t , HTS221_data_t )
 *
 * @details     It sets the output data rate ( ODR ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myODR:           Output data rate.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetOutputDataRate  ( I2C_parameters_t myI2Cparameters, HTS221_data_t myODR )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & CTRL_REG1_ODR_MASK ) | myODR.odr );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



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
 * @brief       HTS221_GetOutputDataRate ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets the output data rate ( ODR ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myODR:           Output data rate
 *
 *
 * @return       Status of HTS221_GetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetOutputDataRate  ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myODR )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_CTRL_REG1;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myODR->odr   =   (HTS221_ctrl_reg1_odr_t)( cmd & CTRL_REG1_ODR_MASK );
  



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
 * @brief       HTS221_SetBoot ( I2C_parameters_t )
 *
 * @details     It sets reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetBoot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         At the end of the boot process, the BOOT bit is set again to '0'.
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetBoot  ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & CTRL_REG2_BOOT_MASK ) | CTRL_REG2_BOOT_REBOOT_MEMORY_CONTENT );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



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
 * @brief       HTS221_GetBoot ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBOOT:          Reboot memory content flag
 *
 *
 * @return       Status of HTS221_GetBoot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetBoot ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myBOOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_CTRL_REG2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myBOOT->boot   =   (HTS221_ctrl_reg2_boot_t)( cmd & CTRL_REG2_BOOT_MASK );
  



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
 * @brief       HTS221_SetHeater ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It sets heater mode: Enabled/Disabled.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHeater:        Heater mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetHeater.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetHeater ( I2C_parameters_t myI2Cparameters, HTS221_data_t myHeater )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & CTRL_REG2_HEATER_MASK ) | myHeater.heater );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



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
 * @brief       HTS221_GetHeater ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets heater mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHeater         Heater mode
 *
 *
 * @return       Status of HTS221_GetHeater.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetHeater ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myHeater )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_CTRL_REG2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myHeater->heater   =   (HTS221_ctrl_reg2_heater_t)( cmd & CTRL_REG2_HEATER_MASK );
  



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
 * @brief       HTS221_SetOneShot ( I2C_parameters_t )
 *
 * @details     It sets one-shot, new data set.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         ONE_SHOT bit comes back to '0' by hardware
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetOneShot ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & CTRL_REG2_ONE_SHOT_MASK ) | CTRL_REG2_ONE_SHOT_START );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  



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
 * @brief       HTS221_GetOneShot ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets one-shot flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myOneShot:       One-shot flag
 *
 *
 * @return       Status of HTS221_GetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/May/2019
 * @version     23/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetOneShot ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myOneShot )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_CTRL_REG2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myOneShot->one_shot   =   (HTS221_ctrl_reg2_one_shot_t)( cmd & CTRL_REG2_ONE_SHOT_MASK );
  



  if ( aux == I2C_SUCCESS )
  {
    return   HTS221_SUCCESS;
  }
  else
  {
    return   HTS221_FAILURE;
  }
}
