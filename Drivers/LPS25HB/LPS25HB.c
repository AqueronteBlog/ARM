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