/**
 * @brief       LPS25HB.c
 * @details     MEMS pressure sensor: 260-1260 hPa absolute digital output baromete.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include "LPS25HB.h"


/**
 * @brief       LPS25HB_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetReferencePressure ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets raw reference pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myREFL:          Raw reference pressure.
 *
 *
 * @return       Status of LPS25HB_GetReferencePressure.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         This function uses auto-increment to read more than one register in a raw.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetReferencePressure ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myREFL )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( LPS25HB_REF_P_XL | 0x80 );                                              // Auto-increment enabled
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Mask it and update it with the new value  */
  myREFL->rawReferencePressure   =   cmd[2];
  myREFL->rawReferencePressure <<=   8UL;
  myREFL->rawReferencePressure  |=   cmd[1];
  myREFL->rawReferencePressure <<=   8UL;
  myREFL->rawReferencePressure  |=   cmd[0];



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetReferencePressure ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets raw reference pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myREFL:          Raw reference pressure.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetReferencePressure.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         This function uses auto-increment to write more than one register in a raw.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetReferencePressure ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myREFL )
{
  uint8_t      cmd[4]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( LPS25HB_REF_P_XL | 0x80 );                                      // Auto-increment enabled
  cmd[1]  =   (uint8_t)( myREFL.rawReferencePressure );                         // REF_P_XL
  cmd[2]  =   (uint8_t)( myREFL.rawReferencePressure >> 8UL );                  // REF_P_L
  cmd[3]  =   (uint8_t)( myREFL.rawReferencePressure >> 16UL );                 // REF_P_H
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetDeviceID ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myID:            Device ID.
 *
 *
 * @return       Status of LPS25HB_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetDeviceID ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Write the register   */
  cmd   =  LPS25HB_WHO_AM_I;                                              
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse data  */
  myID->deviceID   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetTemperatureResolution ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets temperature resolution.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAVGT:          Temperature resolution.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetTemperatureResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetTemperatureResolution ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myAVGT )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_RES_CONF;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( RES_CONF_AVGT_MASK );
  cmd[1] |=  myAVGT.avgt;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetTemperatureResolution ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets temperature resolution.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAVGT:          Temperature resolution.
 *
 *
 * @return       Status of LPS25HB_GetTemperatureResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetTemperatureResolution ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myAVGT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_RES_CONF;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myAVGT->avgt   =   (LPS25HB_res_conf_avgt_t)( cmd & RES_CONF_AVGT_MASK );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetPressureResolution ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets pressure resolution.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAVGP:          Pressure resolution.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetPressureResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetPressureResolution ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myAVGP )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_RES_CONF;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( RES_CONF_AVGP_MASK );
  cmd[1] |=  myAVGP.avgp;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetPressureResolution ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets pressure resolution.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAVGP:          Pressure resolution.
 *
 *
 * @return       Status of LPS25HB_GetPressureResolution.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetPressureResolution ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myAVGP )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_RES_CONF;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myAVGP->avgp   =   (LPS25HB_res_conf_avgp_t)( cmd & RES_CONF_AVGP_MASK );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetPowerMode ( I2C_parameters_t , LPS25HB_ctrl_reg1_pd_t )
 *
 * @details     It sets power mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPD:            Power mode: Power-down/Active mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetPowerMode ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg1_pd_t myPD )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_PD_MASK );
  cmd[1] |=   myPD;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetOutputDataRate ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the output data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myODR:           Output data rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetOutputDataRate ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myODR )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_ODR_MASK );
  cmd[1] |=   myODR.odr;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetOutputDataRate ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the output data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myODR:           Output data rate.
 *
 *
 * @return       Status of LPS25HB_GetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetOutputDataRate ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myODR )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG1;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myODR->odr   =   (LPS25HB_ctrl_reg1_odr_t)( cmd & CTRL_REG1_ODR_MASK );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetInterruptGeneration ( I2C_parameters_t , LPS25HB_ctrl_reg1_diff_en_t )
 *
 * @details     It sets the interrupt generation enable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDIFF_EN:       Interrupt generation enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetInterruptGeneration.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetInterruptGeneration ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg1_diff_en_t myDIFF_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_DIFF_EN_MASK );
  cmd[1] |=   myDIFF_EN;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetBlockDataUpdate ( I2C_parameters_t , LPS25HB_ctrl_reg1_bdu_t )
 *
 * @details     It sets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBDU:           Block data update.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg1_bdu_t myBDU )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_BDU_MASK );
  cmd[1] |=   myBDU;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetResetAutozero ( I2C_parameters_t )
 *
 * @details     It sets the reset autozero function.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetResetAutozero.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetResetAutozero ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_RESET_AZ_MASK );
  cmd[1] |=   CTRL_REG1_RESET_AZ_RESET_AUTOZERO_FUNCTION;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetResetAutozero ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the reset autozero function.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRESET_AZ:      Reset autozero function value.
 *
 *
 * @return       Status of LPS25HB_GetResetAutozero.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetResetAutozero ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRESET_AZ )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG1;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myRESET_AZ->reset_az   =  (LPS25HB_ctrl_reg1_reset_az_t)( CTRL_REG1_RESET_AZ_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetRebootMemoryContent ( I2C_parameters_t )
 *
 * @details     It sets the reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetRebootMemoryContent ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_BOOT_MASK );
  cmd[1] |=   CTRL_REG2_BOOT_REBOOT_MODE;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetRebootMemoryContent ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBOOT:          Reboot memory content value.
 *
 *
 * @return       Status of LPS25HB_GetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetRebootMemoryContent ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myBOOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myBOOT->boot   =  (LPS25HB_ctrl_reg2_boot_t)( CTRL_REG2_BOOT_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetFIFOEnable ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFO_EN:       FIFO enable/disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetFIFOEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetFIFOEnable ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myFIFO_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_FIFO_EN_MASK );
  cmd[1] |=   myFIFO_EN.fifo_en;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetFIFOEnable ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFO_EN:       FIFO enable/disable.
 *
 *
 * @return       Status of LPS25HB_GetFIFOEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetFIFOEnable ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myFIFO_EN )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFO_EN->fifo_en   =  (LPS25HB_ctrl_reg2_fifo_en_t)( CTRL_REG2_FIFO_EN_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetFIFOMeanDec ( I2C_parameters_t , LPS25HB_ctrl_reg2_fifo_mean_dec_t )
 *
 * @details     It enables/disables the decimate the output pressure to 1Hz with FIFO Mean mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFO_MEAN_DEC: It enables/disables the decimate the output pressure to 1Hz with FIFO Mean mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetFIFOMeanDec.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetFIFOMeanDec ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg2_fifo_mean_dec_t myFIFO_MEAN_DEC )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_FIFO_MEAN_DEC_MASK );
  cmd[1] |=   myFIFO_MEAN_DEC;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetSoftwareReset ( I2C_parameters_t )
 *
 * @details     It sets the software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetSoftwareReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_SWRESET_MASK );
  cmd[1] |=   CTRL_REG2_SWRESET_SW_RESET;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetSoftwareReset ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the software reset flag value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySWRESET:       Software reset flag value.
 *
 *
 * @return       Status of LPS25HB_GetSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetSoftwareReset ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* mySWRESET )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  mySWRESET->swreset   =  (LPS25HB_ctrl_reg2_swreset_t)( CTRL_REG2_SWRESET_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetAutozero ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the autozero enable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAUTOZERO:      Enable/disable autozero.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetAutozero.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetAutozero ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myAUTOZERO )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_AUTOZERO_MASK );
  cmd[1] |=   myAUTOZERO.autozero;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetAutozero ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the software reset flag value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAUTOZERO:      Autozero enable value.
 *
 *
 * @return       Status of LPS25HB_GetAutozero.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetAutozero ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myAUTOZERO )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myAUTOZERO->autozero   =  (LPS25HB_ctrl_reg2_autozero_t)( CTRL_REG2_AUTOZERO_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetOneShot ( I2C_parameters_t )
 *
 * @details     It sets the one-shot mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetOneShot ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_ONE_SHOT_MASK );
  cmd[1] |=   CTRL_REG2_ONE_SHOT_NEW_DATASET;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetOneShot ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the one-shot mode flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myONE_SHOT:      One-shot flag value.
 *
 *
 * @return       Status of LPS25HB_GetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetOneShot ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myONE_SHOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myONE_SHOT->one_shot   =  (LPS25HB_ctrl_reg2_one_shot_t)( CTRL_REG2_ONE_SHOT_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetInterruptActiveMode ( I2C_parameters_t , LPS25HB_ctrl_reg3_int_h_l_t )
 *
 * @details     It sets the interrupt active mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myINT_H_L:       Interrupt active high/low.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetInterruptActiveMode.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetInterruptActiveMode ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_int_h_l_t myINT_H_L )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG3;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG3_INT_H_L_MASK );
  cmd[1] |=   myINT_H_L;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetDrainSelectionMode ( I2C_parameters_t , LPS25HB_ctrl_reg3_pp_od_t )
 *
 * @details     It sets the Push-pull/open drain selection on interrupt pads.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPP_OD:         Push-pull/open drain
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetDrainSelectionMode.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetDrainSelectionMode ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_pp_od_t myPP_OD )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG3;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG3_PP_OD_MASK );
  cmd[1] |=   myPP_OD;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetDataSignalOnPin ( I2C_parameters_t , LPS25HB_ctrl_reg3_int_s2_t )
 *
 * @details     It sets the Data signal on INT_DRDY pin control bits.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myINT_S:         Data signal on INT_DRDY pin control bits
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetDataSignalOnPin.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetDataSignalOnPin ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_int_s2_t myINT_S )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG3;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG3_INT_S2_MASK );
  cmd[1] |=   myINT_S;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetINT_DRDY_Behaviour ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the INT_DRDY behaviour.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myIntConfig:     Interrupt configuration parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetINT_DRDY_Behaviour.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetINT_DRDY_Behaviour ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myIntConfig )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_CTRL_REG4;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG4_F_EMPTY_MASK | CTRL_REG4_F_FTH_MASK | CTRL_REG4_F_OVR_MASK | CTRL_REG4_DRDY_MASK );
  cmd[1] |=   ( myIntConfig.f_empty | myIntConfig.f_fth | myIntConfig.f_ovr | myIntConfig.drdy );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetINT_DRDY_Behaviour ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets INT_DRDY behaviour.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntConfig:     Interrupt configuration parameters.
 *
 *
 * @return       Status of LPS25HB_GetINT_DRDY_Behaviour.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetINT_DRDY_Behaviour ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myIntConfig )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_CTRL_REG4;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myIntConfig->f_empty   =  (LPS25HB_ctrl_reg4_f_empty_t)( CTRL_REG4_F_EMPTY_MASK & cmd );
  myIntConfig->f_fth     =  (LPS25HB_ctrl_reg4_f_fth_t)( CTRL_REG4_F_FTH_MASK & cmd );
  myIntConfig->f_ovr     =  (LPS25HB_ctrl_reg4_f_ovr_t)( CTRL_REG4_F_OVR_MASK & cmd );
  myIntConfig->drdy      =  (LPS25HB_ctrl_reg4_drdy_t)( CTRL_REG4_DRDY_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_SetInterruptConfiguration ( I2C_parameters_t , LPS25HB_data_t )
 *
 * @details     It sets the interrupt configuration parameters.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myIntConfig:     Interrupt configuration parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS25HB_SetInterruptConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_SetInterruptConfiguration ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myIntConfig )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS25HB_INTERRUPT_CFG;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( INTERRUPT_CFG_LIR_MASK | INTERRUPT_CFG_PL_E_MASK | INTERRUPT_CFG_PH_E_MASK );
  cmd[1] |=   ( myIntConfig.lir | myIntConfig.pl_e | myIntConfig.ph_e );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetInterruptConfiguration ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets interrupt configuration parameters.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntConfig:     Interrupt configuration parameters.
 *
 *
 * @return       Status of LPS25HB_GetInterruptConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetInterruptConfiguration ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myIntConfig )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_INTERRUPT_CFG;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myIntConfig->lir   =  (LPS25HB_interrupt_cfg_lir_t)( INTERRUPT_CFG_LIR_MASK & cmd );
  myIntConfig->pl_e  =  (LPS25HB_interrupt_cfg_pl_e_t)( INTERRUPT_CFG_PL_E_MASK & cmd );
  myIntConfig->ph_e  =  (LPS25HB_interrupt_cfg_ph_e_t)( INTERRUPT_CFG_PH_E_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetInterruptSource ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It reads the interrupt source register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntSource:     Interrupt source.
 *
 *
 * @return       Status of LPS25HB_GetInterruptSource.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetInterruptSource ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myIntSource )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_INT_SOURCE;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myIntSource->int_source  =  (uint8_t)( 0b00000111 & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetStatusRegister ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It reads the status register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStatusRegister:  Status register.
 *
 *
 * @return       Status of LPS25HB_GetStatusRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetStatusRegister ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myStatusRegister )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS25HB_STATUS_REG;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myStatusRegister->status_reg  =  (uint8_t)( 0b11110011 & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetRawPressure ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the raw pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawPressure:   Raw pressure.
 *
 *
 * @return       Status of LPS25HB_GetRawPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetRawPressure ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRawPressure )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( LPS25HB_PRESS_OUT_XL | 0x80 );                                         // Force auto-increment
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myRawPressure->rawPressure   =   cmd[2];
  myRawPressure->rawPressure <<=   8UL;
  myRawPressure->rawPressure  |=   cmd[1];
  myRawPressure->rawPressure <<=   8UL;
  myRawPressure->rawPressure  |=   cmd[0];
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}



/**
 * @brief       LPS25HB_GetRawTemperature ( I2C_parameters_t , LPS25HB_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature.
 *
 *
 * @return       Status of LPS25HB_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        09/June/2019
 * @version     09/June/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
LPS25HB_status_t LPS25HB_GetRawTemperature ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRawTemperature )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( LPS25HB_TEMP_OUT_L | 0x80 );                                         // Force auto-increment
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myRawTemperature->rawTemperature   =   cmd[1];
  myRawTemperature->rawTemperature <<=   8UL;
  myRawTemperature->rawTemperature  |=   cmd[0];
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS25HB_SUCCESS;
  }
  else
  {
    return   LPS25HB_FAILURE;
  }
}