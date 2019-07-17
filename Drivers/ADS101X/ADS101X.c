/**
 * @brief       ADS101X.c
 * @details     MEMS nano pressure sensor: 260-1260 hPa absolute digital output barometer.
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
 * @brief       ADS101X_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_Init ( I2C_parameters_t myI2Cparameters )
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
 * @brief       ADS101X_SetInterruptMode ( I2C_parameters_t , ADS101X_interrupt_cfg_autorifp_t , ADS101X_interrupt_cfg_reset_arp_t , ADS101X_interrupt_cfg_autozero_t ,
 *                                         ADS101X_interrupt_cfg_reset_az_t , ADS101X_interrupt_cfg_diff_en_t , ADS101X_interrupt_cfg_lir_t , ADS101X_interrupt_cfg_ple_t , ADS101X_interrupt_cfg_phe_t )
 *
 * @details     It sets the Interrupt mode for pressure acquisition configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAUTORIFP:      Enable/Disable AUTORIFP function.
 * @param[in]    myResetARP:      Enable/Disable RESET_ARP function.
 * @param[in]    myAutoZero:      Enable/Disable myAutoZero function.
 * @param[in]    myResetAZ:       Enable/Disable myResetAZ function.
 * @param[in]    myDiffEN:        Enable/Disable DIFF_EN function.
 * @param[in]    myLIR:           Enable/Disable LIR function.
 * @param[in]    myPLE:           Enable/Disable PLE function.
 * @param[in]    myPHE:           Enable/Disable PHE function.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetInterruptMode ( I2C_parameters_t myI2Cparameters, ADS101X_interrupt_cfg_autorifp_t myAUTORIFP, ADS101X_interrupt_cfg_reset_arp_t myResetARP, ADS101X_interrupt_cfg_autozero_t myAutoZero,
                                            ADS101X_interrupt_cfg_reset_az_t myResetAZ, ADS101X_interrupt_cfg_diff_en_t myDiffEN, ADS101X_interrupt_cfg_lir_t myLIR, ADS101X_interrupt_cfg_ple_t myPLE, ADS101X_interrupt_cfg_phe_t myPHE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =    ADS101X_INTERRUPT_CFG;
  cmd[1]   =   ( myAUTORIFP | myResetARP | myAutoZero | myResetAZ | myDiffEN | myLIR | myPLE | myPHE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       ADS101X_GetInterruptMode ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the Interrupt CFG register, raw value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInterruptCFG:  InterruptCFG register, raw value.
 *
 *
 * @return       Status of ADS101X_GetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetInterruptMode ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myInterruptCFG )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_INTERRUPT_CFG;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myInterruptCFG->interruptCFG   =   cmd;



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
 * @brief       ADS101X_SetPressureThreshold ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets the threshold value for pressure interrupt event.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myThs_P:         Pressure threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetPressureThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This functions uses auto-increment.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetPressureThreshold ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myThs_P )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( ADS101X_THS_P_L | 0x80 );    // Auto-increment
  cmd[1]  =   (uint8_t)( myThs_P.ths_p & 0xFF );
  cmd[2]  =   (uint8_t)( myThs_P.ths_p >> 8U );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




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
 * @brief       ADS101X_GetPressureThreshold ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the threshold value for pressure interrupt event.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myThs_P:         Pressure threshold value.
 *
 *
 * @return       Status of ADS101X_GetPressureThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetPressureThreshold ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myThs_P )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( ADS101X_THS_P_L | 0x80 );    // Auto-increment
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myThs_P->ths_p   =   cmd[0];
  myThs_P->ths_p <<=   8U;
  myThs_P->ths_p  |=   cmd[1];



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
 * @brief       ADS101X_GetDeviceID ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myID:            Device ID.
 *
 *
 * @return       Status of ADS101X_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetDeviceID ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Write the register   */
  cmd   =  ADS101X_WHO_AM_I;                                              
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse data  */
  myID->deviceID   =   cmd;



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
 * @brief       ADS101X_SetOutputDataRate ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets the output data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myODR:           Output data rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetOutputDataRate ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myODR )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_ODR_MASK );
  cmd[1] |=   myODR.odr;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetOutputDataRate ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the output data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myODR:           Output data rate.
 *
 *
 * @return       Status of ADS101X_GetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetOutputDataRate ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myODR )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_CTRL_REG1;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myODR->odr   =   (ADS101X_ctrl_reg1_odr_t)( cmd & CTRL_REG1_ODR_MASK );
 


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
 * @brief       ADS101X_ConfLowPassFilter ( I2C_parameters_t , ADS101X_ctrl_reg1_en_lpfp_t , ADS101X_ctrl_reg1_lpfp_cfg_t )
 *
 * @details     It configures the low-pass filter.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myEN_LPFP:       Enable/Disable Low-pass filter.
 * @param[in]    myLPFP_CFG:      Low-pass configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_ConfLowPassFilter.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_ConfLowPassFilter ( I2C_parameters_t myI2Cparameters, ADS101X_ctrl_reg1_en_lpfp_t myEN_LPFP, ADS101X_ctrl_reg1_lpfp_cfg_t myLPFP_CFG )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  /* Update the register   */  
  cmd[1] &=  ~( CTRL_REG1_EN_LPFP_MASK | CTRL_REG1_LPFP_CFG_MASK );
  cmd[1] |=   ( myEN_LPFP | myLPFP_CFG );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_SetBlockDataUpdate ( I2C_parameters_t , ADS101X_ctrl_reg1_bdu_t )
 *
 * @details     It sets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBDU:           Block data update.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, ADS101X_ctrl_reg1_bdu_t myBDU )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_BDU_MASK );
  cmd[1] |=   myBDU;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_SetRebootMemoryContent ( I2C_parameters_t )
 *
 * @details     It sets the reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetRebootMemoryContent ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_BOOT_MASK );
  cmd[1] |=   CTRL_REG2_BOOT_REBOOT_MODE;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetRebootMemoryContent ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBOOT:          Reboot memory content value.
 *
 *
 * @return       Status of ADS101X_GetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetRebootMemoryContent ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myBOOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myBOOT->boot   =  (ADS101X_ctrl_reg2_boot_t)( CTRL_REG2_BOOT_MASK & cmd );
 


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
 * @brief       ADS101X_SetFIFOEnable ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFO_EN:       FIFO enable/disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetFIFOEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetFIFOEnable ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myFIFO_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_FIFO_EN_MASK );
  cmd[1] |=   myFIFO_EN.fifo_en;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetFIFOEnable ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFO_EN:       FIFO enable/disable.
 *
 *
 * @return       Status of ADS101X_GetFIFOEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetFIFOEnable ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myFIFO_EN )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFO_EN->fifo_en   =  (ADS101X_ctrl_reg2_fifo_en_t)( CTRL_REG2_FIFO_EN_MASK & cmd );
 


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
 * @brief       ADS101X_SetFIFOWatermarkLevel ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets the FIFO watermark level use.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySTOP_ON_FTH:   FIFO watermark level use flag.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetFIFOWatermarkLevel.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetFIFOWatermarkLevel ( I2C_parameters_t myI2Cparameters, ADS101X_data_t mySTOP_ON_FTH )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_STOP_ON_FTH_MASK );
  cmd[1] |=   mySTOP_ON_FTH.stopOnFTH;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetFIFOWatermarkLevel ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySTOP_ON_FTH:   FIFO watermark level use flag.
 *
 *
 * @return       Status of ADS101X_GetFIFOWatermarkLevel.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetFIFOWatermarkLevel ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* mySTOP_ON_FTH )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  mySTOP_ON_FTH->stopOnFTH   =  (ADS101X_ctrl_reg2_stop_on_fth_t)( CTRL_REG2_STOP_ON_FTH_MASK & cmd );
 


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
 * @brief       ADS101X_SetSoftwareReset ( I2C_parameters_t )
 *
 * @details     It sets the software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetSoftwareReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_SWRESET_MASK );
  cmd[1] |=   CTRL_REG2_SWRESET_SW_RESET;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetSoftwareReset ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the software reset flag value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySWRESET:       Software reset flag value.
 *
 *
 * @return       Status of ADS101X_GetSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetSoftwareReset ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* mySWRESET )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  mySWRESET->swreset   =  (ADS101X_ctrl_reg2_swreset_t)( CTRL_REG2_SWRESET_MASK & cmd );
 


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
 * @brief       ADS101X_TriggerOneShot ( I2C_parameters_t )
 *
 * @details     It triggers the one-shot mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_TriggerOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_TriggerOneShot ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_ONE_SHOT_MASK );
  cmd[1] |=   CTRL_REG2_ONE_SHOT_NEW_DATASET;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetOneShot ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the one-shot mode flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myONE_SHOT:      One-shot flag value.
 *
 *
 * @return       Status of ADS101X_GetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetOneShot ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myONE_SHOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myONE_SHOT->one_shot   =  (ADS101X_ctrl_reg2_one_shot_t)( CTRL_REG2_ONE_SHOT_MASK & cmd );
 


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
 * @brief       ADS101X_SetInterruptGeneration ( I2C_parameters_t , ADS101X_ctrl_reg3_int_h_l_t , ADS101X_ctrl_reg3_pp_od_t , ADS101X_ctrl_reg3_f_fss5_t ,
 *                                               ADS101X_ctrl_reg3_f_fth_t , ADS101X_ctrl_reg3_f_ovr_t , ADS101X_ctrl_reg3_drdy_t , ADS101X_ctrl_reg3_int_s2_t )
 *
 * @details     It sets the interrupt generation enable: INT_DRDY pin control.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myINT_H_L:       Interrupt active-high/low.
 * @param[in]    myPP_OD:         Push-pull/open drain selection on interrupt pads.
 * @param[in]    myF_FSS5:        FIFO full flag on INT_DRDY pin.
 * @param[in]    myF_FTH:         FIFO watermark status on INT_DRDY pin.
 * @param[in]    myF_OVR:         FIFO overrun interrupt on INT_DRDY pin.
 * @param[in]    myDRDY:          Data-ready signal on INT_DRDY pin.
 * @param[in]    myINT_S:         Data signal on INT_DRDY pin control bits.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetInterruptGeneration.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetInterruptGeneration   ( I2C_parameters_t myI2Cparameters, ADS101X_ctrl_reg3_int_h_l_t myINT_H_L, ADS101X_ctrl_reg3_pp_od_t myPP_OD, ADS101X_ctrl_reg3_f_fss5_t myF_FSS5,
                                                    ADS101X_ctrl_reg3_f_fth_t myF_FTH, ADS101X_ctrl_reg3_f_ovr_t myF_OVR, ADS101X_ctrl_reg3_drdy_t myDRDY, ADS101X_ctrl_reg3_int_s2_t myINT_S )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_CTRL_REG3;                                                     
  cmd[1]  =   ( myINT_H_L | myPP_OD | myF_FSS5 | myF_FTH | myF_OVR | myDRDY | myINT_S );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_SetFIFO_Mode ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets the FIFO mode selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOmode:      FIFO mode selection.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetFIFO_Mode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetFIFO_Mode ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myFIFOmode )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_FIFO_CTRL;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( FIFO_CTRL_F_MODE_MASK );
  cmd[1] |=   myFIFOmode.f_mode;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetFIFO_Mode ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the FIFO mode selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOmode:      FIFO mode selection.
 *
 *
 * @return       Status of ADS101X_GetFIFO_Mode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetFIFO_Mode ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myFIFOmode )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_FIFO_CTRL;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFOmode->f_mode   =  (ADS101X_fifo_ctrl_f_mode_t)( FIFO_CTRL_F_MODE_MASK & cmd );
 


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
 * @brief       ADS101X_SetFIFO_Threshold ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets the FIFO threshold (watermark) level selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOthreshold: FIFO threshold (watermark) level selection ( 31 max. ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetFIFO_Threshold.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetFIFO_Threshold ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myFIFOthreshold )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* It cannot be greater than 31 level  */
  if ( myFIFOthreshold.wtm > 31U )
  {
    return   ADS101X_FAILURE;
  }
  else
  {
    /* Update the register   */
    cmd[0]  =   ADS101X_FIFO_CTRL;                                                     
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
    cmd[1] &=  ~( 0b11111 );
    cmd[1] |=   myFIFOthreshold.wtm;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
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
 * @brief       ADS101X_GetFIFO_Threshold ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the FIFO threshold (watermark) level selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOthreshold: FIFO threshold (watermark) level selection.
 *
 *
 * @return       Status of ADS101X_GetFIFO_Threshold.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetFIFO_Threshold ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myFIFOthreshold )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_FIFO_CTRL;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFOthreshold->wtm   =  (uint8_t)( 0x1F & cmd );
 


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
 * @brief       ADS101X_GetReferencePressure ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets raw reference pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myREFL:          Raw reference pressure.
 *
 *
 * @return       Status of ADS101X_GetReferencePressure.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function uses auto-increment to read more than one register in a raw.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetReferencePressure ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myREFL )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_REF_P_XL;                                             
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Mask it and update it with the new value  */
  myREFL->ref_p   =   cmd[2];
  myREFL->ref_p <<=   8UL;
  myREFL->ref_p  |=   cmd[1];
  myREFL->ref_p <<=   8UL;
  myREFL->ref_p  |=   cmd[0];



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
 * @brief       ADS101X_SetReferencePressure ( I2C_parameters_t , ADS101X_data_t )
 *
 * @details     It sets raw reference pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myREFL:          Raw reference pressure.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetReferencePressure.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function uses auto-increment to write more than one register in a raw.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetReferencePressure ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myREFL )
{
  uint8_t      cmd[4]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_REF_P_XL;                            
  cmd[1]  =   (uint8_t)( myREFL.ref_p );                         // REF_P_XL
  cmd[2]  =   (uint8_t)( myREFL.ref_p >> 8UL );                  // REF_P_L
  cmd[3]  =   (uint8_t)( myREFL.ref_p >> 16UL );                 // REF_P_H
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




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
 * @brief       ADS101X_GetPressureOffset ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the Pressure offset value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPressureOffset:  Pressure offset.
 *
 *
 * @return       Status of ADS101X_GetPressureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function implemets auto-increment.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetPressureOffset ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myPressureOffset )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_RPDS_L;                                   
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myPressureOffset->rpds   =   cmd[1];
  myPressureOffset->rpds <<=   8U;
  myPressureOffset->rpds  |=   cmd[0];
 


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
 * @brief       ADS101X_SetPressureOffset ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It sets the Pressure offset value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPressureOffset:  Pressure offset.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetPressureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function implements auto-increment.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetPressureOffset ( I2C_parameters_t myI2Cparameters, ADS101X_data_t myPressureOffset )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_RPDS_L;                                   
  cmd[1]  =   (uint8_t)( myPressureOffset.rpds & 0xFF );
  cmd[2]  =   (uint8_t)( ( myPressureOffset.rpds >> 8U ) & 0xFF );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

  

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
 * @brief       ADS101X_SetPowerMode ( I2C_parameters_t , ADS101X_ctrl_reg1_pd_t )
 *
 * @details     It sets power mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPD:            Power mode: Normal mode (low-noise mode)/Low-current mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of ADS101X_SetPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_SetPowerMode ( I2C_parameters_t myI2Cparameters, ADS101X_res_conf_lc_en_t myLC_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   ADS101X_RES_CONF;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( RES_CONF_LC_EN_MASK );
  cmd[1] |=   myLC_EN;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


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
 * @brief       ADS101X_GetInterruptSource ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It reads the interrupt source register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntSource:     Interrupt source.
 *
 *
 * @return       Status of ADS101X_GetInterruptSource.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetInterruptSource ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myIntSource )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_INT_SOURCE;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myIntSource->int_source  =  (uint8_t)( 0b10000111 & cmd );
 


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
 * @brief       ADS101X_GetFIFO_Status ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It reads the FIFO status register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOstatus:    FIFO threshold (watermark) level selection.
 *
 *
 * @return       Status of ADS101X_GetFIFO_Status.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetFIFO_Status ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myFIFOstatus )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_FIFO_STATUS;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFOstatus->fifo_status   =  cmd;
 


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
 * @brief       ADS101X_GetStatusRegister ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It reads the status register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStatusRegister:  Status register.
 *
 *
 * @return       Status of ADS101X_GetStatusRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetStatusRegister ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myStatusRegister )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   ADS101X_STATUS;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myStatusRegister->status  =  (uint8_t)( 0b00110011 & cmd );
 


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
 * @brief       ADS101X_GetRawPressure ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the raw pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawPressure:   Raw pressure.
 *
 *
 * @return       Status of ADS101X_GetRawPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetRawPressure ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myRawPressure )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_PRESS_OUT_XL;                                         
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
    return   ADS101X_SUCCESS;
  }
  else
  {
    return   ADS101X_FAILURE;
  }
}



/**
 * @brief       ADS101X_GetRawTemperature ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature.
 *
 *
 * @return       Status of ADS101X_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetRawTemperature ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myRawTemperature )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ADS101X_TEMP_OUT_L;                                        
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myRawTemperature->rawTemperature   =   cmd[1];
  myRawTemperature->rawTemperature <<=   8UL;
  myRawTemperature->rawTemperature  |=   cmd[0];
 


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
 * @brief       ADS101X_GetPressure ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the current pressure in mbar.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPressure:        Current pressure in mbar.
 *
 *
 * @return       Status of ADS101X_GetPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetPressure ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myPressure )
{
  ADS101X_status_t aux;

  /* Read raw pressure   */
  aux  =   ADS101X_GetRawPressure ( myI2Cparameters, &(*myPressure) );
  

  /* Check if the pressure value is negative   */
  if ( ( myPressure->rawPressure & 0x800000 ) == 0x800000 )
  {
    /* Negative pressure   */
    myPressure->rawPressure |=   0xFF000000;
  }
  else
  {
    /* Positive pressure   */
  }
  
  
  /* Calculate pressure  */
  myPressure->pressure   =   (float)( myPressure->rawPressure / 4096.0 );
  


  return aux;
}



/**
 * @brief       ADS101X_GetTemperature ( I2C_parameters_t , ADS101X_data_t* )
 *
 * @details     It gets the current temperature in Celsius degrees.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Current temperature in Celsius degrees.
 *
 *
 * @return       Status of ADS101X_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
ADS101X_status_t ADS101X_GetTemperature ( I2C_parameters_t myI2Cparameters, ADS101X_data_t* myTemperature )
{
  ADS101X_status_t aux;

  /* Read raw temperature   */
  aux  =   ADS101X_GetRawTemperature ( myI2Cparameters, &(*myTemperature) );
  

  /* Calculate temperature  */
  myTemperature->temperature   =   (float)( myTemperature->rawTemperature / 100.0 );
  


  return aux;
}
