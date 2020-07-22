/**
 * @brief       SFM4100.c
 * @details     Low-cost Digital Mass Flow Meter for Gases.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "SFM4100.h"


/**
 * @brief       SFM4100_Init ( I2C_parameters_t, SFM4100_data_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySFM4100:       Device to use.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_Init ( I2C_parameters_t myI2Cparameters, SFM4100_data_t mySFM4100  )
{
  i2c_status_t aux =  I2C_SUCCESS;;

  aux  |=   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_StartSingleConversion ( I2C_parameters_t );
 *
 * @details     It starts a new single conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_StartSingleConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         This function can only be used when in power-down state and has no effect 
 *              when a conversion is ongoing.
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_StartSingleConversion ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;
  
  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );
  
  /* Mask it and update the register   */
  myConfig   =   cmd[1];
  myConfig <<=   8U;
  myConfig  |=   cmd[2];

  myConfig  |=   CONFIG_OS_BUSY;
  cmd[1]     =   (uint8_t)( myConfig >> 8U );
  cmd[2]     =   (uint8_t)( myConfig );
  aux       |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetOS ( I2C_parameters_t, SFM4100_config_t* );
 *
 * @details     It checks if the device is not currently performing a conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySFM4100:       Operational status flag.
 *
 *
 * @return       Status of SFM4100_GetOS.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetOS ( I2C_parameters_t myI2Cparameters, SFM4100_config_t* mySFM4100 )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse it   */
  myConfig       =   cmd[0];
  myConfig     <<=   8U;
  myConfig      |=   cmd[1];
  mySFM4100->os  =   (SFM4100_config_os_t)( myConfig & CONFIG_OS_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetMux ( I2C_parameters_t, SFM4100_data_t );
 *
 * @details     It sets input multiplexer configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySFM4100:       Input multiplexer configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetMux.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1015 only.
 */
SFM4100_status_t SFM4100_SetMux ( I2C_parameters_t myI2Cparameters, SFM4100_data_t mySFM4100 )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015 supports this functionality    */
  if ( mySFM4100.device == DEVICE_ADS1115 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   SFM4100_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

    /* Mask it and update the register   */
    myConfig    =   cmd[1];
    myConfig  <<=   8U;
    myConfig   |=   cmd[2];

    myConfig   &=  ~CONFIG_MUX_MASK;
    myConfig   |=   mySFM4100.config.mux;
    cmd[1]      =   (uint8_t)( myConfig >> 8U );
    cmd[2]      =   (uint8_t)( myConfig );
    aux        |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  SFM4100_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetMux ( I2C_parameters_t, SFM4100_data_t* );
 *
 * @details     It gets input multiplexer configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySFM4100:       Input multiplexer configuration..
 *
 *
 * @return       Status of SFM4100_GetMux.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1015 only.
 */
SFM4100_status_t SFM4100_GetMux ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* mySFM4100 )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015 supports this functionality    */
  if ( mySFM4100->device == DEVICE_ADS1115 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   SFM4100_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myConfig         =   cmd[0];
    myConfig       <<=   8U;
    myConfig        |=   cmd[1];
    mySFM4100->config.mux   =   (SFM4100_config_mux_t)( myConfig & CONFIG_MUX_MASK );
  }
  else
  {
    return  SFM4100_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetGain ( I2C_parameters_t, SFM4100_data_t );
 *
 * @details     It sets programmable gain amplifier.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPGA:           Programmable gain.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     Not ADS1013.
 */
SFM4100_status_t SFM4100_SetGain ( I2C_parameters_t myI2Cparameters, SFM4100_data_t myPGA )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myPGA.device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   SFM4100_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

    /* Mask it and update the register   */
    myConfig    =   cmd[1];
    myConfig  <<=   8U;
    myConfig   |=   cmd[2];

    myConfig   &=  ~CONFIG_PGA_MASK;
    myConfig   |=   myPGA.config.pga;
    cmd[1]      =   (uint8_t)( myConfig >> 8U );
    cmd[2]      =   (uint8_t)( myConfig );
    aux        |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  SFM4100_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetGain ( I2C_parameters_t, SFM4100_data_t* );
 *
 * @details     It gets programmable gain amplifier.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myPGA:           Programmable gain.
 *
 *
 * @return       Status of SFM4100_GetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     Not ADS1013.
 */
SFM4100_status_t SFM4100_GetGain ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myPGA )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myPGA->device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   SFM4100_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myConfig     =   cmd[0];
    myConfig   <<=   8U;
    myConfig    |=   cmd[1];
    myPGA->config.pga   =   (SFM4100_config_pga_t)( myConfig & CONFIG_PGA_MASK );
  }
  else
  {
    return  SFM4100_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetMode ( I2C_parameters_t, SFM4100_config_t );
 *
 * @details     It sets the device operating mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myMode:          Continuous/Single-shot mode conversion.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_SetMode ( I2C_parameters_t myI2Cparameters, SFM4100_config_t myMode )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

  /* Mask it and update the register   */
  myConfig    =   cmd[1];
  myConfig  <<=   8U;
  myConfig   |=   cmd[2];

  myConfig   &=  ~CONFIG_MODE_MASK;
  myConfig   |=   myMode.mode;
  cmd[1]      =   (uint8_t)( myConfig >> 8U );
  cmd[2]      =   (uint8_t)( myConfig );
  aux        |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetMode ( I2C_parameters_t, SFM4100_config_t* );
 *
 * @details     It gets the device operating mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myMode:          Continuous/Single-shot mode conversion..
 *
 *
 * @return       Status of SFM4100_GetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetMode ( I2C_parameters_t myI2Cparameters, SFM4100_config_t* myMode )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myConfig       =   cmd[0];
  myConfig     <<=   8U;
  myConfig      |=   cmd[1];
  myMode->mode   =   (SFM4100_config_mode_t)( myConfig & CONFIG_MODE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetDataRate ( I2C_parameters_t, SFM4100_config_t );
 *
 * @details     It sets the data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDR:            Data rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_SetDataRate ( I2C_parameters_t myI2Cparameters, SFM4100_config_t myDR )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

  /* Mask it and update the register   */
  myConfig    =   cmd[1];
  myConfig  <<=   8U;
  myConfig   |=   cmd[2];

  myConfig   &=  ~CONFIG_DR_MASK;
  myConfig   |=   myDR.dr;
  cmd[1]      =   (uint8_t)( myConfig >> 8U );
  cmd[2]      =   (uint8_t)( myConfig );
  aux        |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetDataRate ( I2C_parameters_t, SFM4100_config_t* );
 *
 * @details     It gets the data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDR:            Data rate.
 *
 *
 * @return       Status of SFM4100_GetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetDataRate ( I2C_parameters_t myI2Cparameters, SFM4100_config_t* myDR )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myConfig   =   cmd[0];
  myConfig <<=   8U;
  myConfig  |=   cmd[1];
  myDR->dr   =   (SFM4100_config_dr_t)( myConfig & CONFIG_DR_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetComparator ( I2C_parameters_t, SFM4100_data_t );
 *
 * @details     It sets the comparator configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCOMP:          Comparator Mode/Polarity/Latching/Queue and disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetComparator.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1014 and ADS1015 only.
 */
SFM4100_status_t SFM4100_SetComparator ( I2C_parameters_t myI2Cparameters, SFM4100_data_t myCOMP )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myCOMP.device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   SFM4100_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

    /* Mask it and update the register   */
    myConfig    =   cmd[1];
    myConfig  <<=   8U;
    myConfig   |=   cmd[2];

    myConfig   &=  ~( CONFIG_COMP_MODE_MASK | CONFIG_COMP_POL_MASK | CONFIG_COMP_LAT_MASK | CONFIG_COMP_QUE_MASK );
    myConfig   |=   ( myCOMP.config.comp_mode | myCOMP.config.comp_pol | myCOMP.config.comp_lat | myCOMP.config.comp_que );
    cmd[1]      =   (uint8_t)( myConfig >> 8U );
    cmd[2]      =   (uint8_t)( myConfig );
    aux        |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  SFM4100_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetComparator ( I2C_parameters_t, SFM4100_data_t* );
 *
 * @details     It gets the comparator configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myCOMP:          Comparator Mode/Polarity/Latching/Queue and disable.
 *
 *
 * @return       Status of SFM4100_GetComparator.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1014 and ADS1015 only.
 */
SFM4100_status_t SFM4100_GetComparator ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myCOMP )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myCOMP->device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   SFM4100_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myConfig           =   cmd[0];
    myConfig         <<=   8U;
    myConfig          |=   cmd[1];

    myCOMP->config.comp_mode  =   (SFM4100_config_comp_mode_t)( myConfig & CONFIG_COMP_MODE_MASK );
    myCOMP->config.comp_pol   =   (SFM4100_config_comp_pol_t)( myConfig & CONFIG_COMP_POL_MASK );
    myCOMP->config.comp_lat   =   (SFM4100_config_comp_lat_t)( myConfig & CONFIG_COMP_LAT_MASK );
    myCOMP->config.comp_que   =   (SFM4100_config_comp_que_t)( myConfig & CONFIG_COMP_QUE_MASK );
  }
  else
  {
    return  SFM4100_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetLowThresholdValue ( I2C_parameters_t, SFM4100_thresh_t );
 *
 * @details     It sets the low threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myLoThres:       low threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetLowThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_SetLowThresholdValue ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t myLoThres )
{
  uint8_t      cmd[3]  =  { 0U };
  i2c_status_t aux     =  I2C_SUCCESS;

  /* Update the register   */
   myLoThres.lo_thresh <<= 4U;

   cmd[0]   =   SFM4100_LO_THRESH;
   cmd[1]   =   (uint8_t)( myLoThres.lo_thresh >> 8U );
   cmd[2]   =   (uint8_t)( myLoThres.lo_thresh );
   aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetLowThresholdValue ( I2C_parameters_t, SFM4100_thresh_t );
 *
 * @details     It gets the low threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myLoThres:       low threshold value.
 *
 *
 * @return       Status of SFM4100_GetLowThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetLowThresholdValue ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t* myLoThres )
{
  uint8_t      cmd[2]   =  { 0U };
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_LO_THRESH;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myLoThres->lo_thresh    =   cmd[0];
  myLoThres->lo_thresh  <<=   8U;
  myLoThres->lo_thresh   |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SetHighThresholdValue ( I2C_parameters_t, SFM4100_thresh_t );
 *
 * @details     It sets the high threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHiThres:       High threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SetHighThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_SetHighThresholdValue ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t myHiThres )
{
  uint8_t      cmd[3]  =  { 0U };
  i2c_status_t aux     =  I2C_SUCCESS;

  /* Update the register   */
  myHiThres.hi_thresh <<= 4U;

  cmd[0]   =   SFM4100_HI_THRESH;
  cmd[1]   =   (uint8_t)( myHiThres.hi_thresh >> 8U );
  cmd[2]   =   (uint8_t)( myHiThres.hi_thresh );
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetHighThresholdValue ( I2C_parameters_t, SFM4100_thresh_t );
 *
 * @details     It gets the high threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHiThres:       High threshold value.
 *
 *
 * @return       Status of SFM4100_GetHighThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetHighThresholdValue ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t* myHiThres )
{
  uint8_t      cmd[2]   =  { 0U };
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_HI_THRESH;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myHiThres->hi_thresh    =   cmd[0];
  myHiThres->hi_thresh  <<=   8U;
  myHiThres->hi_thresh   |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetRawConversion ( I2C_parameters_t, SFM4100_conversion_t* );
 *
 * @details     It gets the raw conversion value
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawD:          Raw conversion value.
 *
 *
 * @return       Status of SFM4100_GetRawConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetRawConversion ( I2C_parameters_t myI2Cparameters, SFM4100_conversion_t* myRawD )
{
  uint8_t      cmd[2]   =  { 0U };
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   SFM4100_CONVERSION;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawD->raw_conversion    =   cmd[0];
  myRawD->raw_conversion  <<=   8U;
  myRawD->raw_conversion   |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetConversion ( I2C_parameters_t, SFM4100_data_t* );
 *
 * @details     It gets the conversion value
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myD:             Conversion value.
 *
 *
 * @return       Status of SFM4100_GetConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_GetConversion ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myD )
{
  float             myGain    =  0.0;
  float             myFactor  =  0.0;
  SFM4100_status_t  aux       =  SFM4100_SUCCESS;

  /* Get the raw conversion value   */
  aux  =   SFM4100_GetRawConversion ( myI2Cparameters, &(myD->conversion) );

  /* Set up the gain accordingly   */
  switch ( myD->device )
  {
    case DEVICE_ADS1113:
      myGain   =   2.048;
      break;

    default:
    case DEVICE_ADS1114:
    case DEVICE_ADS1115:
      switch ( myD->config.pga )
      {
        case CONFIG_PGA_FSR_6_144_V:
          myGain   =   6.144;
          break;

        case CONFIG_PGA_FSR_4_096_V:
          myGain   =   4.096;
          break;

        default:
        case CONFIG_PGA_FSR_2_048_V:
          myGain   =   2.048;
          break;

        case CONFIG_PGA_FSR_1_024_V:
          myGain   =   1.024;
          break;

        case CONFIG_PGA_FSR_0_512_V:
          myGain   =   0.512;
          break;

        case CONFIG_PGA_FSR_0_256_V:
          myGain   =   0.256;
          break;
      }
      break;
  }


  /* Check the scale	 */
  if ( myD->conversion.raw_conversion == 0x8000 )
  {
	  myFactor  =   myGain;
  }
  else if ( myD->conversion.raw_conversion == 0x7FFF )
  {
	  myFactor  =   ( myGain * ( 32768.0 - 1.0 ) ) / 32768.0;
  }
  else
  {
	  myFactor  =   myGain / 32768.0;
  }


  /* Result  */
  myD->conversion.conversion  =   (float)( myFactor * myD->conversion.raw_conversion );


  return   aux;
}



/**
 * @brief       SFM4100_SoftReset ( I2C_parameters_t );
 *
 * @details     It triggers a softreset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_SoftReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;

  /* General address: 0x00   */
  myI2Cparameters.addr   =   0x00;

  /* Update the register   */
  cmd  =   SFM4100_RESET_COMMAND;
  aux |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}

