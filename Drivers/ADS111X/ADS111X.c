/**
 * @brief       ADS111X.c
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 860-SPS, 16-Bit ADCs With Internal Reference, Oscillator, and Programmable Comparator.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "ADS111X.h"


/**
 * @brief       ADS111X_Init ( I2C_parameters_t, ADS111X_data_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myADS111X:       Device to use.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_Init ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myADS111X  )
{
  i2c_status_t aux =  I2C_SUCCESS;;

  aux  |=   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_StartSingleConversion ( I2C_parameters_t );
 *
 * @details     It starts a new single conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_StartSingleConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         This function can only be used when in power-down state and has no effect 
 *              when a conversion is ongoing.
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_StartSingleConversion ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;
  
  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
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
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetOS ( I2C_parameters_t, ADS111X_config_t* );
 *
 * @details     It checks if the device is not currently performing a conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myADS111X:       Operational status flag.
 *
 *
 * @return       Status of ADS111X_GetOS.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetOS ( I2C_parameters_t myI2Cparameters, ADS111X_config_t* myADS111X )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse it   */
  myConfig       =   cmd[0];
  myConfig     <<=   8U;
  myConfig      |=   cmd[1];
  myADS111X->os  =   (ADS111X_config_os_t)( myConfig & CONFIG_OS_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetMux ( I2C_parameters_t, ADS111X_data_t );
 *
 * @details     It sets input multiplexer configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myADS111X:       Input multiplexer configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetMux.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1015 only.
 */
ADS111X_status_t ADS111X_SetMux ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myADS111X )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015 supports this functionality    */
  if ( myADS111X.device == DEVICE_ADS1115 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS111X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );

    /* Mask it and update the register   */
    myConfig    =   cmd[1];
    myConfig  <<=   8U;
    myConfig   |=   cmd[2];

    myConfig   &=  ~CONFIG_MUX_MASK;
    myConfig   |=   myADS111X.config.mux;
    cmd[1]      =   (uint8_t)( myConfig >> 8U );
    cmd[2]      =   (uint8_t)( myConfig );
    aux        |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  ADS111X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetMux ( I2C_parameters_t, ADS111X_data_t* );
 *
 * @details     It gets input multiplexer configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myADS111X:       Input multiplexer configuration..
 *
 *
 * @return       Status of ADS111X_GetMux.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1015 only.
 */
ADS111X_status_t ADS111X_GetMux ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myADS111X )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015 supports this functionality    */
  if ( myADS111X->device == DEVICE_ADS1115 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS111X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myConfig         =   cmd[0];
    myConfig       <<=   8U;
    myConfig        |=   cmd[1];
    myADS111X->config.mux   =   (ADS111X_config_mux_t)( myConfig & CONFIG_MUX_MASK );
  }
  else
  {
    return  ADS111X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetGain ( I2C_parameters_t, ADS111X_data_t );
 *
 * @details     It sets programmable gain amplifier.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPGA:           Programmable gain.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     Not ADS1013.
 */
ADS111X_status_t ADS111X_SetGain ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myPGA )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myPGA.device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS111X_CONFIG;
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
    return  ADS111X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetGain ( I2C_parameters_t, ADS111X_data_t* );
 *
 * @details     It gets programmable gain amplifier.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myPGA:           Programmable gain.
 *
 *
 * @return       Status of ADS111X_GetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     Not ADS1013.
 */
ADS111X_status_t ADS111X_GetGain ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myPGA )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myPGA->device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS111X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myConfig     =   cmd[0];
    myConfig   <<=   8U;
    myConfig    |=   cmd[1];
    myPGA->config.pga   =   (ADS111X_config_pga_t)( myConfig & CONFIG_PGA_MASK );
  }
  else
  {
    return  ADS111X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetMode ( I2C_parameters_t, ADS111X_config_t );
 *
 * @details     It sets the device operating mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myMode:          Continuous/Single-shot mode conversion.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_SetMode ( I2C_parameters_t myI2Cparameters, ADS111X_config_t myMode )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
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
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetMode ( I2C_parameters_t, ADS111X_config_t* );
 *
 * @details     It gets the device operating mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myMode:          Continuous/Single-shot mode conversion..
 *
 *
 * @return       Status of ADS111X_GetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetMode ( I2C_parameters_t myI2Cparameters, ADS111X_config_t* myMode )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myConfig       =   cmd[0];
  myConfig     <<=   8U;
  myConfig      |=   cmd[1];
  myMode->mode   =   (ADS111X_config_mode_t)( myConfig & CONFIG_MODE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetDataRate ( I2C_parameters_t, ADS111X_config_t );
 *
 * @details     It sets the data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDR:            Data rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_SetDataRate ( I2C_parameters_t myI2Cparameters, ADS111X_config_t myDR )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
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
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetDataRate ( I2C_parameters_t, ADS111X_config_t* );
 *
 * @details     It gets the data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDR:            Data rate.
 *
 *
 * @return       Status of ADS111X_GetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetDataRate ( I2C_parameters_t myI2Cparameters, ADS111X_config_t* myDR )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myConfig   =   cmd[0];
  myConfig <<=   8U;
  myConfig  |=   cmd[1];
  myDR->dr   =   (ADS111X_config_dr_t)( myConfig & CONFIG_DR_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetComparator ( I2C_parameters_t, ADS111X_data_t );
 *
 * @details     It sets the comparator configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCOMP:          Comparator Mode/Polarity/Latching/Queue and disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetComparator.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1014 and ADS1015 only.
 */
ADS111X_status_t ADS111X_SetComparator ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myCOMP )
{
  uint8_t      cmd[3]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myCOMP.device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS111X_CONFIG;
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
    return  ADS111X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetComparator ( I2C_parameters_t, ADS111X_data_t* );
 *
 * @details     It gets the comparator configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myCOMP:          Comparator Mode/Polarity/Latching/Queue and disable.
 *
 *
 * @return       Status of ADS111X_GetComparator.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     ADS1014 and ADS1015 only.
 */
ADS111X_status_t ADS111X_GetComparator ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myCOMP )
{
  uint8_t      cmd[2]   =  { 0U };
  uint16_t     myConfig =  0U;
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myCOMP->device != DEVICE_ADS1113 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS111X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data   */
    myConfig           =   cmd[0];
    myConfig         <<=   8U;
    myConfig          |=   cmd[1];

    myCOMP->config.comp_mode  =   (ADS111X_config_comp_mode_t)( myConfig & CONFIG_COMP_MODE_MASK );
    myCOMP->config.comp_pol   =   (ADS111X_config_comp_pol_t)( myConfig & CONFIG_COMP_POL_MASK );
    myCOMP->config.comp_lat   =   (ADS111X_config_comp_lat_t)( myConfig & CONFIG_COMP_LAT_MASK );
    myCOMP->config.comp_que   =   (ADS111X_config_comp_que_t)( myConfig & CONFIG_COMP_QUE_MASK );
  }
  else
  {
    return  ADS111X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetLowThresholdValue ( I2C_parameters_t, ADS111X_thresh_t );
 *
 * @details     It sets the low threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myLoThres:       low threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetLowThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_SetLowThresholdValue ( I2C_parameters_t myI2Cparameters, ADS111X_thresh_t myLoThres )
{
  uint8_t      cmd[3]  =  { 0U };
  i2c_status_t aux     =  I2C_SUCCESS;

  /* Update the register   */
   myLoThres.lo_thresh <<= 4U;

   cmd[0]   =   ADS111X_LO_THRESH;
   cmd[1]   =   (uint8_t)( myLoThres.lo_thresh >> 8U );
   cmd[2]   =   (uint8_t)( myLoThres.lo_thresh );
   aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetLowThresholdValue ( I2C_parameters_t, ADS111X_thresh_t );
 *
 * @details     It gets the low threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myLoThres:       low threshold value.
 *
 *
 * @return       Status of ADS111X_GetLowThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetLowThresholdValue ( I2C_parameters_t myI2Cparameters, ADS111X_thresh_t* myLoThres )
{
  uint8_t      cmd[2]   =  { 0U };
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_LO_THRESH;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myLoThres->lo_thresh    =   cmd[0];
  myLoThres->lo_thresh  <<=   8U;
  myLoThres->lo_thresh   |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_SetHighThresholdValue ( I2C_parameters_t, ADS111X_thresh_t );
 *
 * @details     It sets the high threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHiThres:       High threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SetHighThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_SetHighThresholdValue ( I2C_parameters_t myI2Cparameters, ADS111X_thresh_t myHiThres )
{
  uint8_t      cmd[3]  =  { 0U };
  i2c_status_t aux     =  I2C_SUCCESS;

  /* Update the register   */
  myHiThres.hi_thresh <<= 4U;

  cmd[0]   =   ADS111X_HI_THRESH;
  cmd[1]   =   (uint8_t)( myHiThres.hi_thresh >> 8U );
  cmd[2]   =   (uint8_t)( myHiThres.hi_thresh );
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetHighThresholdValue ( I2C_parameters_t, ADS111X_thresh_t );
 *
 * @details     It gets the high threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHiThres:       High threshold value.
 *
 *
 * @return       Status of ADS111X_GetHighThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetHighThresholdValue ( I2C_parameters_t myI2Cparameters, ADS111X_thresh_t* myHiThres )
{
  uint8_t      cmd[2]   =  { 0U };
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_HI_THRESH;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myHiThres->hi_thresh    =   cmd[0];
  myHiThres->hi_thresh  <<=   8U;
  myHiThres->hi_thresh   |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetRawConversion ( I2C_parameters_t, ADS111X_conversion_t* );
 *
 * @details     It gets the raw conversion value
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawD:          Raw conversion value.
 *
 *
 * @return       Status of ADS111X_GetRawConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetRawConversion ( I2C_parameters_t myI2Cparameters, ADS111X_conversion_t* myRawD )
{
  uint8_t      cmd[2]   =  { 0U };
  i2c_status_t aux      =  I2C_SUCCESS;

  /* Read the register to mask it  */
  cmd[0]   =   ADS111X_CONVERSION;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawD->raw_conversion    =   cmd[0];
  myRawD->raw_conversion  <<=   8U;
  myRawD->raw_conversion   |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}



/**
 * @brief       ADS111X_GetConversion ( I2C_parameters_t, ADS111X_data_t* );
 *
 * @details     It gets the conversion value
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myD:             Conversion value.
 *
 *
 * @return       Status of ADS111X_GetConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_GetConversion ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myD )
{
  float             myGain    =  0.0;
  float             myFactor  =  0.0;
  ADS111X_status_t  aux       =  ADS111X_SUCCESS;

  /* Get the raw conversion value   */
  aux  =   ADS111X_GetRawConversion ( myI2Cparameters, &(myD->conversion) );

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
 * @brief       ADS111X_SoftReset ( I2C_parameters_t );
 *
 * @details     It triggers a softreset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS111X_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2020
 * @version     14/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS111X_status_t ADS111X_SoftReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;

  /* General address: 0x00   */
  myI2Cparameters.addr   =   0x00;

  /* Update the register   */
  cmd  =   ADS111X_RESET_COMMAND;
  aux |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS111X_SUCCESS;
  }
  else
  {
    return   ADS111X_FAILURE;
  }
}

