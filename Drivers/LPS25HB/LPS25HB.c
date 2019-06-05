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
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG1_PD_MASK ) | myPowerMode );
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
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG1_BDU_MASK ) | myBDU.bdu );
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
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG1_ODR_MASK ) | myODR.odr );
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
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG2_BOOT_MASK ) | CTRL_REG2_BOOT_REBOOT_MEMORY_CONTENT );
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
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG2_HEATER_MASK ) | myHeater.heater );
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
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG2_ONE_SHOT_MASK ) | CTRL_REG2_ONE_SHOT_START );
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



/**
 * @brief       HTS221_SetDataReadyOuput ( I2C_parameters_t , HTS221_ctrl_reg3_drdy_h_l_t )
 *
 * @details     It sets data ready output signal active high/low.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDRDY_H_L:      Data ready output signal high/low.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetDataReadyOuput.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetDataReadyOuput ( I2C_parameters_t myI2Cparameters, HTS221_ctrl_reg3_drdy_h_l_t myDRDY_H_L )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG3_DRDY_H_L_MASK ) | myDRDY_H_L );
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
 * @brief       HTS221_SetSelectionOnPin3 ( I2C_parameters_t , HTS221_ctrl_reg3_pp_od_t )
 *
 * @details     It sets Push-pull/Open Drain selection on pin 3 ( DRDY ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDRDY:          Push-pull/Open Drain selection on pin 3 (DRDY).
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetDataReadyOuput.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetSelectionOnPin3 ( I2C_parameters_t myI2Cparameters, HTS221_ctrl_reg3_pp_od_t myDRDY )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG3_PP_OD_MASK ) | myDRDY );
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
 * @brief       HTS221_SetDataReadyEnable ( I2C_parameters_t , HTS221_ctrl_reg3_drdy_en_t )
 *
 * @details     It sets data ready enable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDRDY_EN:       Data Ready enable.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HTS221_SetDataReadyEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HTS221_status_t HTS221_SetDataReadyEnable ( I2C_parameters_t myI2Cparameters, HTS221_ctrl_reg3_drdy_en_t myDRDY_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   HTS221_CTRL_REG3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Update the register   */
  cmd[1]   =   ( ( cmd[1] & ~CTRL_REG3_DRDY_EN_MASK ) | myDRDY_EN );
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
 * @brief       HTS221_GetHumidityDataAvailable ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets humidity data available flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHumidityFlag:  Humidity data available flag
 *
 *
 * @return       Status of HTS221_GetHumidityDataAvailable.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetHumidityDataAvailable ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myHumidityFlag )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_STATUS_REG;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myHumidityFlag->h_da   =   (HTS221_status_reg_h_da_t)( cmd & STATUS_REGISTER_H_DA_MASK );
  



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
 * @brief       HTS221_GetTemperatureDataAvailable ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets temperature data available flag.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperatureFlag: Temperature data available flag
 *
 *
 * @return       Status of HTS221_GetTemperatureDataAvailable.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetTemperatureDataAvailable ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myTemperatureFlag )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   HTS221_STATUS_REG;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myTemperatureFlag->t_da   =   (HTS221_status_reg_t_da_t)( cmd & STATUS_REGISTER_T_DA_MASK );
  



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
 * @brief       HTS221_GetRawHumidity ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets raw humidity.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawHumidity:     Raw humidity
 *
 *
 * @return       Status of HTS221_GetRawHumidity.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         This function uses autoincrementing for reading the registers.
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetRawHumidity ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myRawHumidity )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   ( HTS221_HUMIDITY_OUT_L | 0x80 );                                        // Autoincrementing
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myRawHumidity->rawHumidity   =   cmd[1];
  myRawHumidity->rawHumidity <<=   8U;
  myRawHumidity->rawHumidity  |=   cmd[0];
  



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
 * @brief       HTS221_GetRawTemperature ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature
 *
 *
 * @return       Status of HTS221_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     24/May/2019     The ORIGIN
 * @pre         This function uses autoincrementing for reading the registers.
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetRawTemperature ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myRawTemperature )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   ( HTS221_TEMP_OUT_L | 0x80 );                                             // Autoincrementing
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


  /* Parse the data   */
  myRawTemperature->rawTemperature   =   cmd[1];
  myRawTemperature->rawTemperature <<=   8U;
  myRawTemperature->rawTemperature  |=   cmd[0];
  



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
 * @brief       HTS221_GetCalibrationCoefficients ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets calibration coefficients.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCoeff:           Calibration coefficients
 *
 *
 * @return       Status of HTS221_GetCalibrationCoefficients.
 *
 *
 * @author      Manuel Caballero
 * @date        24/May/2019
 * @version     30/May/2019     Coefficients calibration is calculated here.
 *              24/May/2019     The ORIGIN
 * @pre         This function uses autoincrementing for reading the registers.
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetCalibrationCoefficients ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myCoeff )
{
  uint8_t      cmd[16]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   ( HTS221_CALIB_0 | 0x80 );                                             // Autoincrementing 
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myCoeff->h0_rH_x2    =   cmd[0];
  myCoeff->h1_rH_x2    =   cmd[1];
  myCoeff->t0_degC_x8  =   cmd[2];
  myCoeff->t1_degC_x8  =   cmd[3];
  myCoeff->t1_T0_msb   =   ( cmd[5] & 0x0F );
  myCoeff->h0_T0_OUT   =   cmd[7];
  myCoeff->h0_T0_OUT <<=   8U;
  myCoeff->h0_T0_OUT  |=   cmd[6];
  myCoeff->h1_T0_OUT   =   cmd[11];
  myCoeff->h1_T0_OUT <<=   8U;
  myCoeff->h1_T0_OUT  |=   cmd[10];
  myCoeff->t0_OUT      =   cmd[13];
  myCoeff->t0_OUT    <<=   8U;
  myCoeff->t0_OUT     |=   cmd[12];
  myCoeff->t1_OUT      =   cmd[15];
  myCoeff->t1_OUT    <<=   8U;
  myCoeff->t1_OUT     |=   cmd[14];
  
  /* Coefficient result for temperature & humidity  */
  myCoeff->t0_degC   =  ( myCoeff->t1_T0_msb & 0x03 );
  myCoeff->t0_degC <<=  8U;
  myCoeff->t0_degC  |=  myCoeff->t0_degC_x8;
  myCoeff->t0_degC >>=  3U;

  myCoeff->t1_degC   =   ( myCoeff->t1_T0_msb & 0x0C );
  myCoeff->t1_degC <<=   6U;
  myCoeff->t1_degC  |=   myCoeff->t1_degC_x8;
  myCoeff->t1_degC >>=  3U;

  myCoeff->h0_RH     =   myCoeff->h0_rH_x2;
  myCoeff->h0_RH   >>=  1U;

  myCoeff->h1_RH     =   myCoeff->h1_rH_x2;
  myCoeff->h1_RH   >>=  1U;
  



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
 * @brief       HTS221_GetTemperature ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets the current temperature in Celsius degrees.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Current temperature in Celsius degress
 *
 *
 * @return       Status of HTS221_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        26/May/2019
 * @version     30/May/2019     Temperature calculation was improved
 *              26/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetTemperature ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myTemperature )
{
  HTS221_status_t aux;

  /* Get temperature  */
  aux  =   HTS221_GetRawTemperature ( myI2Cparameters, &(*myTemperature) );

  /* Parse the data   */
  myTemperature->temperature   =   (int32_t)( 10.0*( myTemperature->rawTemperature - myTemperature->t0_OUT )*( myTemperature->t1_degC - myTemperature->t0_degC )/( myTemperature->t1_OUT - myTemperature->t0_OUT ) );
  myTemperature->temperature  +=   10.0*myTemperature->t0_degC;
  myTemperature->temperature  /=   10.0;
  
  

  if ( aux == HTS221_SUCCESS )
  {
    return   HTS221_SUCCESS;
  }
  else
  {
    return   HTS221_FAILURE;
  }
}


/**
 * @brief       HTS221_GetHumidity ( I2C_parameters_t , HTS221_data_t* )
 *
 * @details     It gets the current humidity value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHumidity:        Current humidity value
 *
 *
 * @return       Status of HTS221_GetHumidity.
 *
 *
 * @author      Manuel Caballero
 * @date        26/May/2019
 * @version     30/May/2019     Humidity calculation was improved
 *              26/May/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HTS221_status_t HTS221_GetHumidity ( I2C_parameters_t myI2Cparameters, HTS221_data_t* myHumidity )
{
  HTS221_status_t aux;

  /* Get humidity  */
  aux  =   HTS221_GetRawHumidity ( myI2Cparameters, &(*myHumidity) );

  /* Parse the data   */ 
  myHumidity->humidity   =   (int32_t)( 10.0*( myHumidity->rawHumidity - myHumidity->h0_T0_OUT )*( myHumidity->h1_RH - myHumidity->h0_RH )/( myHumidity->h1_T0_OUT - myHumidity->h0_T0_OUT ) );
  myHumidity->humidity  +=   10.0*myHumidity->h0_RH;
  myHumidity->humidity  /=   10.0;

  /* Check if it is saturated  */
  if ( myHumidity->humidity > 100 )
  {
    myHumidity->humidity   =   100;
  }
  
  

  if ( aux == HTS221_SUCCESS )
  {
    return   HTS221_SUCCESS;
  }
  else
  {
    return   HTS221_FAILURE;
  }
}