/**
 * @brief       ADS101X.c
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 3.3-kSPS, 12-Bit ADCs. With Internal Reference, Oscillator, and Programmable Comparator.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "ADS101X.h"


/**
 * @brief       ADS101X_Init ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myADS101X:       Device to use.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     19/July/2019   The device to use was added ( this is redundant ).
 *              17/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_Init ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myADS101X  )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_StartSingleConversion ( I2C_parameters_t );
 *
 * @details     It starts a new single conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_StartSingleConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        19/July/2019
 * @version     20/July/2019   Some comments were improved.
 *              19/July/2019   The ORIGIN
 * @pre         This function can only be used when in power-down state and has no effect 
 *              when a conversion is ongoing.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_StartSingleConversion ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd[0]   =   ADS101X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update the register   */
  cmd[1]  |=   CONFIG_OS_BUSY;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetOS ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It checks if the device is not currently performing a conversion.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myADS101X:       Operational status flag.
 *
 *
 * @return       Status of ADS101X_GetOS.
 *
 *
 * @author      Manuel Caballero
 * @date        19/July/2019
 * @version     19/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetOS ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myADS101X )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_CONFIG;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse it   */
  myADS101X->os  =   (ADS101X_config_os_t)( cmd & CONFIG_OS_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetMux ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets input multiplexer configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myADS101X:       Input multiplexer configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetMux.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     ADS1015 only.
 */
ADS101X_status_t ADS101X_SetMux ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myADS101X )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Only ADS1015 supports this functionality    */
  if ( myADS101X.device == DEVICE_ADS1015 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS101X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update the register   */
    cmd[1]  &=  ~CONFIG_MUX_MASK;
    cmd[1]  |=   myADS101X.mux;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  ADS101X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetMux ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It gets input multiplexer configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myADS101X:       Input multiplexer configuration..
 *
 *
 * @return       Status of ADS101X_GetMux.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     ADS1015 only.
 */
ADS101X_status_t ADS101X_GetMux ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myADS101X )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Only ADS1015 supports this functionality    */
  if ( myADS101X->device == DEVICE_ADS1015 )
  {
    /* Read the register to mask it  */
    cmd   =   ADS101X_CONFIG;
    aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
    /* Parse the data   */
    myADS101X->mux   =   (ADS101X_config_mux_t)( cmd & CONFIG_MUX_MASK );
  }
  else
  {
    return  ADS101X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetGain ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets programmable gain amplifier.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPGA:           Programmable gain.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     Not ADS1013.
 */
ADS101X_status_t ADS101X_SetGain ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myPGA )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myPGA.device != DEVICE_ADS1013 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS101X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update the register   */
    cmd[1]  &=  ~CONFIG_PGA_MASK;
    cmd[1]  |=   myPGA.pga;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  ADS101X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetGain ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It gets programmable gain amplifier.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myPGA:           Programmable gain.
 *
 *
 * @return       Status of ADS101X_GetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     Not ADS1013.
 */
ADS101X_status_t ADS101X_GetGain ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myPGA )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myPGA->device != DEVICE_ADS1013 )
  {
    /* Read the register to mask it  */
    cmd   =   ADS101X_CONFIG;
    aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
    /* Parse the data   */
    myPGA->pga   =   (ADS101X_config_pga_t)( cmd & CONFIG_PGA_MASK );
  }
  else
  {
    return  ADS101X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetMode ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets the device operating mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myMode:          Continuous/Single-shot mode conversion.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetMode ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myMode )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd[0]   =   ADS101X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update the register   */
  cmd[1]  &=  ~CONFIG_MODE_MASK;
  cmd[1]  |=   myMode.mode;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetMode ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It gets the device operating mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myMode:          Continuous/Single-shot mode conversion..
 *
 *
 * @return       Status of ADS101X_GetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetMode ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myMode )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_CONFIG;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myMode->mode   =   (ADS101X_config_mode_t)( cmd & CONFIG_MODE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetDataRate ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets the data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDR:            Data rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetDataRate ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myDR )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd[0]   =   ADS101X_CONFIG;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update the register   */
  cmd[1]  &=  ~CONFIG_DR_MASK;
  cmd[1]  |=   myDR.dr;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetDataRate ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It gets the data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDR:            Data rate.
 *
 *
 * @return       Status of ADS101X_GetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetDataRate ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myDR )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_CONFIG;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myDR->dr   =   (ADS101X_config_dr_t)( cmd & CONFIG_DR_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetComparator ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets the comparator configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCOMP:          Comparator Mode/Polarity/Latching/Queue and disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetComparator.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     ADS1014 and ADS1015 only.
 */
ADS101X_status_t ADS101X_SetComparator ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myCOMP )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myCOMP.device != DEVICE_ADS1013 )
  {
    /* Read the register to mask it  */
    cmd[0]   =   ADS101X_CONFIG;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update the register   */
    cmd[1]  &=  ~( CONFIG_COMP_MODE_MASK | CONFIG_COMP_POL_MASK | CONFIG_COMP_LAT_MASK | CONFIG_COMP_QUE_MASK );
    cmd[1]  |=   ( myCOMP.comp_mode | myCOMP.comp_pol | myCOMP.comp_lat | myCOMP.comp_que );
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }
  else
  {
    return  ADS101X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetComparator ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It gets the comparator configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myCOMP:          Comparator Mode/Polarity/Latching/Queue and disable.
 *
 *
 * @return       Status of ADS101X_GetComparator.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     ADS1014 and ADS1015 only.
 */
ADS101X_status_t ADS101X_GetComparator ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myCOMP )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Only ADS1015/ADS1014 supports this functionality    */
  if ( myCOMP->device != DEVICE_ADS1013 )
  {
    /* Read the register to mask it  */
    cmd   =   ADS101X_CONFIG;
    aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
    /* Parse the data   */
    myCOMP->comp_mode  =   (ADS101X_config_comp_mode_t)( cmd & CONFIG_COMP_MODE_MASK );
    myCOMP->comp_pol   =   (ADS101X_config_comp_pol_t)( cmd & CONFIG_COMP_POL_MASK );
    myCOMP->comp_lat   =   (ADS101X_config_comp_lat_t)( cmd & CONFIG_COMP_LAT_MASK );
    myCOMP->comp_que   =   (ADS101X_config_comp_que_t)( cmd & CONFIG_COMP_QUE_MASK );
  }
  else
  {
    return  ADS101X_DEVICE_NOT_SUPPORTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetLowThresholdValue ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets the low threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myLoThres:       low threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetLowThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetLowThresholdValue ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myLoThres )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* lo-threshold cannot be greather than 4095  */
  if ( (uint16_t)myLoThres.lo_thresh > 4095U )
  {
    return  ADS101X_VALUE_OUT_OF_RANGE;
  }
  else
  {
    /* Update the register   */ 
    cmd[0]   =   ADS101X_LO_THRESH;
    cmd[1]   =   ( myLoThres.lo_thresh << 4U );
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetLowThresholdValue ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It gets the low threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myLoThres:       low threshold value.
 *
 *
 * @return       Status of ADS101X_GetLowThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetLowThresholdValue ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myLoThres )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_LO_THRESH;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Check if the reading is correct   */
  if ( ( cmd & ~LO_THRESH_MASK ) == 0x0000 )
  {
    /* Parse the data   */
    myLoThres->lo_thresh   =   cmd;
    myLoThres->lo_thresh >>=   4U;
  }
  else
  {
    return   ADS101X_DATA_CORRUPTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SetHighThresholdValue ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It sets the high threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHiThres:       High threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetHighThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetHighThresholdValue ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myHiThres )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* Hi_threshold cannot be greather than 4095  */
  if ( (uint16_t)myHiThres.hi_thresh > 4095U )
  {
    return  ADS101X_VALUE_OUT_OF_RANGE;
  }
  else
  {
    /* Update the register   */ 
    cmd[0]   =   ADS101X_HI_THRESH;
    cmd[1]   =   ( myHiThres.hi_thresh << 4U );
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetHighThresholdValue ( I2C_parameters_t, ADS101X_data_t );
 *
 * @details     It gets the high threshold value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHiThres:       High threshold value.
 *
 *
 * @return       Status of ADS101X_GetHighThresholdValue.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetHighThresholdValue ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myHiThres )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_HI_THRESH;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Check if the reading is correct   */
  if ( ( cmd & ~HI_THRESH_MASK ) == 0x000F )
  {
    /* Parse the data   */
    myHiThres->hi_thresh   =   cmd;
    myHiThres->hi_thresh >>=   4U;
  }
  else
  {
    return   ADS101X_DATA_CORRUPTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetRawConversion ( I2C_parameters_t, ADS101X_data_t* );
 *
 * @details     It gets the raw conversion value
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myD:             Raw conversion value.
 *
 *
 * @return       Status of ADS101X_GetRawConversion.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetRawConversion ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myD )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* Read the register to mask it  */
  cmd   =   ADS101X_CONVERSION;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Check if the reading is correct   */
  if ( ( cmd & ~CONVERSION_D_MASK ) == 0x0000 )
  {
    /* Parse the data   */
    myD->raw_conversion   =   cmd;
    myD->raw_conversion >>=   4U;
  }
  else
  {
    return   ADS101X_DATA_CORRUPTED;
  }


  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_SoftReset ( I2C_parameters_t );
 *
 * @details     It triggers a softreset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        20/July/2019
 * @version     20/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SoftReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t           cmd  =  0U;
  i2c_status_t      aux;
  
  /* General address: 0x00   */
  myI2Cparameters.ADDR   =   0x00;

  /* Update the register   */
  cmd  =   ADS101X_RESET_COMMAND;
  aux |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



