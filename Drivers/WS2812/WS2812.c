/**
 * @brief       LPS22HB.c
 * @details     MEMS nano pressure sensor: 260-1260 hPa absolute digital output barometer.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/June/2019
 * @version     15/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "LPS22HB.h"


/**
 * @brief       LPS22HB_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetInterruptMode ( I2C_parameters_t , LPS22HB_interrupt_cfg_autorifp_t , LPS22HB_interrupt_cfg_reset_arp_t , LPS22HB_interrupt_cfg_autozero_t ,
 *                                         LPS22HB_interrupt_cfg_reset_az_t , LPS22HB_interrupt_cfg_diff_en_t , LPS22HB_interrupt_cfg_lir_t , LPS22HB_interrupt_cfg_ple_t , LPS22HB_interrupt_cfg_phe_t )
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
 * @return       Status of LPS22HB_SetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetInterruptMode ( I2C_parameters_t myI2Cparameters, LPS22HB_interrupt_cfg_autorifp_t myAUTORIFP, LPS22HB_interrupt_cfg_reset_arp_t myResetARP, LPS22HB_interrupt_cfg_autozero_t myAutoZero,
                                            LPS22HB_interrupt_cfg_reset_az_t myResetAZ, LPS22HB_interrupt_cfg_diff_en_t myDiffEN, LPS22HB_interrupt_cfg_lir_t myLIR, LPS22HB_interrupt_cfg_ple_t myPLE, LPS22HB_interrupt_cfg_phe_t myPHE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =    LPS22HB_INTERRUPT_CFG;
  cmd[1]   =   ( myAUTORIFP | myResetARP | myAutoZero | myResetAZ | myDiffEN | myLIR | myPLE | myPHE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetInterruptMode ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the Interrupt CFG register, raw value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInterruptCFG:  InterruptCFG register, raw value.
 *
 *
 * @return       Status of LPS22HB_GetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetInterruptMode ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myInterruptCFG )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_INTERRUPT_CFG;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myInterruptCFG->interruptCFG   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetPressureThreshold ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets the threshold value for pressure interrupt event.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myThs_P:         Pressure threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetPressureThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         This functions uses auto-increment.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetPressureThreshold ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myThs_P )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( LPS22HB_THS_P_L | 0x80 );    // Auto-increment
  cmd[1]  =   (uint8_t)( myThs_P.ths_p & 0xFF );
  cmd[2]  =   (uint8_t)( myThs_P.ths_p >> 8U );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetPressureThreshold ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the threshold value for pressure interrupt event.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myThs_P:         Pressure threshold value.
 *
 *
 * @return       Status of LPS22HB_GetPressureThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetPressureThreshold ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myThs_P )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( LPS22HB_THS_P_L | 0x80 );    // Auto-increment
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myThs_P->ths_p   =   cmd[0];
  myThs_P->ths_p <<=   8U;
  myThs_P->ths_p  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetDeviceID ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myID:            Device ID.
 *
 *
 * @return       Status of LPS22HB_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetDeviceID ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Write the register   */
  cmd   =  LPS22HB_WHO_AM_I;                                              
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse data  */
  myID->deviceID   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetOutputDataRate ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets the output data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myODR:           Output data rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetOutputDataRate ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myODR )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_ODR_MASK );
  cmd[1] |=   myODR.odr;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetOutputDataRate ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the output data rate.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myODR:           Output data rate.
 *
 *
 * @return       Status of LPS22HB_GetOutputDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetOutputDataRate ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myODR )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_CTRL_REG1;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myODR->odr   =   (LPS22HB_ctrl_reg1_odr_t)( cmd & CTRL_REG1_ODR_MASK );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_ConfLowPassFilter ( I2C_parameters_t , LPS22HB_ctrl_reg1_en_lpfp_t , LPS22HB_ctrl_reg1_lpfp_cfg_t )
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
 * @return       Status of LPS22HB_ConfLowPassFilter.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_ConfLowPassFilter ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_en_lpfp_t myEN_LPFP, LPS22HB_ctrl_reg1_lpfp_cfg_t myLPFP_CFG )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  /* Update the register   */  
  cmd[1] &=  ~( CTRL_REG1_EN_LPFP_MASK | CTRL_REG1_LPFP_CFG_MASK );
  cmd[1] |=   ( myEN_LPFP | myLPFP_CFG );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetBlockDataUpdate ( I2C_parameters_t , LPS22HB_ctrl_reg1_bdu_t )
 *
 * @details     It sets the block data update.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBDU:           Block data update.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2019
 * @version     22/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg1_bdu_t myBDU )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG1;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG1_BDU_MASK );
  cmd[1] |=   myBDU;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetRebootMemoryContent ( I2C_parameters_t )
 *
 * @details     It sets the reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetRebootMemoryContent ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_BOOT_MASK );
  cmd[1] |=   CTRL_REG2_BOOT_REBOOT_MODE;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetRebootMemoryContent ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the reboot memory content.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myBOOT:          Reboot memory content value.
 *
 *
 * @return       Status of LPS22HB_GetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetRebootMemoryContent ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myBOOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myBOOT->boot   =  (LPS22HB_ctrl_reg2_boot_t)( CTRL_REG2_BOOT_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetFIFOEnable ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFO_EN:       FIFO enable/disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetFIFOEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetFIFOEnable ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFO_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_FIFO_EN_MASK );
  cmd[1] |=   myFIFO_EN.fifo_en;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetFIFOEnable ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFO_EN:       FIFO enable/disable.
 *
 *
 * @return       Status of LPS22HB_GetFIFOEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetFIFOEnable ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFO_EN )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFO_EN->fifo_en   =  (LPS22HB_ctrl_reg2_fifo_en_t)( CTRL_REG2_FIFO_EN_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetFIFOWatermarkLevel ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets the FIFO watermark level use.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySTOP_ON_FTH:   FIFO watermark level use flag.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetFIFOWatermarkLevel.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetFIFOWatermarkLevel ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t mySTOP_ON_FTH )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_STOP_ON_FTH_MASK );
  cmd[1] |=   mySTOP_ON_FTH.stopOnFTH;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetFIFOWatermarkLevel ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the FIFO enable/disable.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySTOP_ON_FTH:   FIFO watermark level use flag.
 *
 *
 * @return       Status of LPS22HB_GetFIFOWatermarkLevel.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetFIFOWatermarkLevel ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* mySTOP_ON_FTH )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  mySTOP_ON_FTH->stopOnFTH   =  (LPS22HB_ctrl_reg2_stop_on_fth_t)( CTRL_REG2_STOP_ON_FTH_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetSoftwareReset ( I2C_parameters_t )
 *
 * @details     It sets the software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetSoftwareReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_SWRESET_MASK );
  cmd[1] |=   CTRL_REG2_SWRESET_SW_RESET;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetSoftwareReset ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the software reset flag value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySWRESET:       Software reset flag value.
 *
 *
 * @return       Status of LPS22HB_GetSoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetSoftwareReset ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* mySWRESET )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  mySWRESET->swreset   =  (LPS22HB_ctrl_reg2_swreset_t)( CTRL_REG2_SWRESET_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_TriggerOneShot ( I2C_parameters_t )
 *
 * @details     It triggers the one-shot mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_TriggerOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_TriggerOneShot ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG2;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( CTRL_REG2_ONE_SHOT_MASK );
  cmd[1] |=   CTRL_REG2_ONE_SHOT_NEW_DATASET;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetOneShot ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the one-shot mode flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myONE_SHOT:      One-shot flag value.
 *
 *
 * @return       Status of LPS22HB_GetOneShot.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetOneShot ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myONE_SHOT )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_CTRL_REG2;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myONE_SHOT->one_shot   =  (LPS22HB_ctrl_reg2_one_shot_t)( CTRL_REG2_ONE_SHOT_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetInterruptGeneration ( I2C_parameters_t , LPS22HB_ctrl_reg3_int_h_l_t , LPS22HB_ctrl_reg3_pp_od_t , LPS22HB_ctrl_reg3_f_fss5_t ,
 *                                               LPS22HB_ctrl_reg3_f_fth_t , LPS22HB_ctrl_reg3_f_ovr_t , LPS22HB_ctrl_reg3_drdy_t , LPS22HB_ctrl_reg3_int_s2_t )
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
 * @return       Status of LPS22HB_SetInterruptGeneration.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetInterruptGeneration   ( I2C_parameters_t myI2Cparameters, LPS22HB_ctrl_reg3_int_h_l_t myINT_H_L, LPS22HB_ctrl_reg3_pp_od_t myPP_OD, LPS22HB_ctrl_reg3_f_fss5_t myF_FSS5,
                                                    LPS22HB_ctrl_reg3_f_fth_t myF_FTH, LPS22HB_ctrl_reg3_f_ovr_t myF_OVR, LPS22HB_ctrl_reg3_drdy_t myDRDY, LPS22HB_ctrl_reg3_int_s2_t myINT_S )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_CTRL_REG3;                                                     
  cmd[1]  =   ( myINT_H_L | myPP_OD | myF_FSS5 | myF_FTH | myF_OVR | myDRDY | myINT_S );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetFIFO_Mode ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets the FIFO mode selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOmode:      FIFO mode selection.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetFIFO_Mode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetFIFO_Mode ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFOmode )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_FIFO_CTRL;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( FIFO_CTRL_F_MODE_MASK );
  cmd[1] |=   myFIFOmode.f_mode;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetFIFO_Mode ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the FIFO mode selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOmode:      FIFO mode selection.
 *
 *
 * @return       Status of LPS22HB_GetFIFO_Mode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetFIFO_Mode ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOmode )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_FIFO_CTRL;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFOmode->f_mode   =  (LPS22HB_fifo_ctrl_f_mode_t)( FIFO_CTRL_F_MODE_MASK & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetFIFO_Threshold ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets the FIFO threshold (watermark) level selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOthreshold: FIFO threshold (watermark) level selection ( 31 max. ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetFIFO_Threshold.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetFIFO_Threshold ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myFIFOthreshold )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* It cannot be greater than 31 level  */
  if ( myFIFOthreshold.wtm > 31U )
  {
    return   LPS22HB_FAILURE;
  }
  else
  {
    /* Update the register   */
    cmd[0]  =   LPS22HB_FIFO_CTRL;                                                     
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
    cmd[1] &=  ~( 0b11111 );
    cmd[1] |=   myFIFOthreshold.wtm;
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetFIFO_Threshold ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the FIFO threshold (watermark) level selection.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOthreshold: FIFO threshold (watermark) level selection.
 *
 *
 * @return       Status of LPS22HB_GetFIFO_Threshold.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetFIFO_Threshold ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOthreshold )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_FIFO_CTRL;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFOthreshold->wtm   =  (uint8_t)( 0x1F & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetReferencePressure ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets raw reference pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myREFL:          Raw reference pressure.
 *
 *
 * @return       Status of LPS22HB_GetReferencePressure.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         This function uses auto-increment to read more than one register in a raw.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetReferencePressure ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myREFL )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_REF_P_XL;                                             
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
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetReferencePressure ( I2C_parameters_t , LPS22HB_data_t )
 *
 * @details     It sets raw reference pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myREFL:          Raw reference pressure.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetReferencePressure.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         This function uses auto-increment to write more than one register in a raw.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetReferencePressure ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myREFL )
{
  uint8_t      cmd[4]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_REF_P_XL;                            
  cmd[1]  =   (uint8_t)( myREFL.ref_p );                         // REF_P_XL
  cmd[2]  =   (uint8_t)( myREFL.ref_p >> 8UL );                  // REF_P_L
  cmd[3]  =   (uint8_t)( myREFL.ref_p >> 16UL );                 // REF_P_H
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetPressureOffset ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the Pressure offset value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPressureOffset:  Pressure offset.
 *
 *
 * @return       Status of LPS22HB_GetPressureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         This function implemets auto-increment.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetPressureOffset ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myPressureOffset )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_RPDS_L;                                   
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myPressureOffset->rpds   =   cmd[1];
  myPressureOffset->rpds <<=   8U;
  myPressureOffset->rpds  |=   cmd[0];
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetPressureOffset ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It sets the Pressure offset value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPressureOffset:  Pressure offset.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetPressureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         This function implements auto-increment.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetPressureOffset ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t myPressureOffset )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_RPDS_L;                                   
  cmd[1]  =   (uint8_t)( myPressureOffset.rpds & 0xFF );
  cmd[2]  =   (uint8_t)( ( myPressureOffset.rpds >> 8U ) & 0xFF );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

  

  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_SetPowerMode ( I2C_parameters_t , LPS22HB_ctrl_reg1_pd_t )
 *
 * @details     It sets power mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPD:            Power mode: Normal mode (low-noise mode)/Low-current mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LPS22HB_SetPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_SetPowerMode ( I2C_parameters_t myI2Cparameters, LPS22HB_res_conf_lc_en_t myLC_EN )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]  =   LPS22HB_RES_CONF;                                                     
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );
  
  cmd[1] &=  ~( RES_CONF_LC_EN_MASK );
  cmd[1] |=   myLC_EN;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetInterruptSource ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It reads the interrupt source register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntSource:     Interrupt source.
 *
 *
 * @return       Status of LPS22HB_GetInterruptSource.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetInterruptSource ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myIntSource )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_INT_SOURCE;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myIntSource->int_source  =  (uint8_t)( 0b10000111 & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetFIFO_Status ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It reads the FIFO status register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOstatus:    FIFO threshold (watermark) level selection.
 *
 *
 * @return       Status of LPS22HB_GetFIFO_Status.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetFIFO_Status ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myFIFOstatus )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_FIFO_STATUS;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFIFOstatus->fifo_status   =  cmd;
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetStatusRegister ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It reads the status register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStatusRegister:  Status register.
 *
 *
 * @return       Status of LPS22HB_GetStatusRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetStatusRegister ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myStatusRegister )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   LPS22HB_STATUS;                                                     
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myStatusRegister->status  =  (uint8_t)( 0b00110011 & cmd );
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetRawPressure ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the raw pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawPressure:   Raw pressure.
 *
 *
 * @return       Status of LPS22HB_GetRawPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetRawPressure ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRawPressure )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_PRESS_OUT_XL;                                         
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
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetRawTemperature ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature.
 *
 *
 * @return       Status of LPS22HB_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetRawTemperature ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myRawTemperature )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   LPS22HB_TEMP_OUT_L;                                        
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myRawTemperature->rawTemperature   =   cmd[1];
  myRawTemperature->rawTemperature <<=   8UL;
  myRawTemperature->rawTemperature  |=   cmd[0];
 


  if ( aux == I2C_SUCCESS )
  {
    return   LPS22HB_SUCCESS;
  }
  else
  {
    return   LPS22HB_FAILURE;
  }
}



/**
 * @brief       LPS22HB_GetPressure ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the current pressure in mbar.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPressure:        Current pressure in mbar.
 *
 *
 * @return       Status of LPS22HB_GetPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetPressure ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myPressure )
{
  LPS22HB_status_t aux;

  /* Read raw pressure   */
  aux  =   LPS22HB_GetRawPressure ( myI2Cparameters, &(*myPressure) );
  

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
 * @brief       LPS22HB_GetTemperature ( I2C_parameters_t , LPS22HB_data_t* )
 *
 * @details     It gets the current temperature in Celsius degrees.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Current temperature in Celsius degrees.
 *
 *
 * @return       Status of LPS22HB_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2019
 * @version     23/June/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
LPS22HB_status_t LPS22HB_GetTemperature ( I2C_parameters_t myI2Cparameters, LPS22HB_data_t* myTemperature )
{
  LPS22HB_status_t aux;

  /* Read raw temperature   */
  aux  =   LPS22HB_GetRawTemperature ( myI2Cparameters, &(*myTemperature) );
  

  /* Calculate temperature  */
  myTemperature->temperature   =   (float)( myTemperature->rawTemperature / 100.0 );
  


  return aux;
}
